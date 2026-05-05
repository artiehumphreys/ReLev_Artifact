#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include "krnl_bloom.hpp"

static std::vector<bloom_key_t> read_keys(const std::string &filename) {
  std::vector<bloom_key_t> keys;
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    std::cerr << "Failed to open key file: " << filename << std::endl;
    std::exit(EXIT_FAILURE);
  }

  bloom_key_t key;
  while (infile >> key) {
    keys.push_back(key);
  }

  return keys;
}

static void pack_keys(const std::vector<bloom_key_t> &keys, KeyPack *input) {
  for (size_t i = 0; i < keys.size(); i++) {
    input[i / KEYS_PER_BURST].keys[i % KEYS_PER_BURST] = keys[i];
  }
}

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " <keys_file>" << std::endl;
    return EXIT_FAILURE;
  }

  auto keys = read_keys(argv[1]);
  int num_keys = keys.size();
  std::cout << "Read " << num_keys << " keys from " << argv[1] << std::endl;

  int num_input_bursts = (num_keys + KEYS_PER_BURST - 1) / KEYS_PER_BURST;
  int num_output_packs = (num_keys + RESULTS_PER_BURST - 1) / RESULTS_PER_BURST;

  KeyPack *input = new KeyPack[num_input_bursts]();
  ResultPack *output = new ResultPack[num_output_packs]();

  pack_keys(keys, input);

  // --- Standard Bloom Filter ---
  std::cout << "=== Standard Bloom Filter Test ===" << std::endl;

  krnl_bloom(input, output, num_keys, MODE_BF_CLEAR);
  std::cout << "BF Clear: OK" << std::endl;

  krnl_bloom(input, output, num_keys, MODE_BF_INSERT);
  std::cout << "BF Insert: OK" << std::endl;

  memset(output, 0, num_output_packs * sizeof(ResultPack));
  krnl_bloom(input, output, num_keys, MODE_BF_QUERY);

  int bf_hits = 0;
  for (int i = 0; i < num_keys; i++) {
    bloom_key_t result = output[i / RESULTS_PER_BURST].results[i % RESULTS_PER_BURST];
    if (result)
      bf_hits++;
  }
  std::cout << "BF Query (inserted): " << bf_hits << "/" << num_keys
            << " found" << std::endl;
  if (bf_hits != num_keys) {
    std::cerr << "FAIL: Expected all inserted keys to be found!" << std::endl;
    delete[] input;
    delete[] output;
    return EXIT_FAILURE;
  }

  // --- Counting Bloom Filter ---
  std::cout << "\n=== Counting Bloom Filter Test ===" << std::endl;

  krnl_bloom(input, output, num_keys, MODE_CBF_CLEAR);
  std::cout << "CBF Clear: OK" << std::endl;

  krnl_bloom(input, output, num_keys, MODE_CBF_INSERT);
  std::cout << "CBF Insert: OK" << std::endl;

  memset(output, 0, num_output_packs * sizeof(ResultPack));
  krnl_bloom(input, output, num_keys, MODE_CBF_QUERY);

  int cbf_hits = 0;
  for (int i = 0; i < num_keys; i++) {
    bloom_key_t result = output[i / RESULTS_PER_BURST].results[i % RESULTS_PER_BURST];
    if (result)
      cbf_hits++;
  }
  std::cout << "CBF Query (inserted): " << cbf_hits << "/" << num_keys
            << " found" << std::endl;
  if (cbf_hits != num_keys) {
    std::cerr << "FAIL: Expected all inserted keys to be found!" << std::endl;
    delete[] input;
    delete[] output;
    return EXIT_FAILURE;
  }

  krnl_bloom(input, output, num_keys, MODE_CBF_REMOVE);
  std::cout << "CBF Remove: OK" << std::endl;

  memset(output, 0, num_output_packs * sizeof(ResultPack));
  krnl_bloom(input, output, num_keys, MODE_CBF_QUERY);

  int cbf_after_remove = 0;
  for (int i = 0; i < num_keys; i++) {
    bloom_key_t result = output[i / RESULTS_PER_BURST].results[i % RESULTS_PER_BURST];
    if (result)
      cbf_after_remove++;
  }
  std::cout << "CBF Query (after remove): " << cbf_after_remove << "/"
            << num_keys << " found" << std::endl;
  if (cbf_after_remove != 0) {
    std::cerr << "FAIL: Expected no keys after removal!" << std::endl;
    delete[] input;
    delete[] output;
    return EXIT_FAILURE;
  }

  // --- Streaming Subtree (shell-spawn path detection, per-root BFs) ---
  std::cout << "\n=== Subtree Streaming Test (NUM_ROOTS=" << NUM_ROOTS
            << ") ===" << std::endl;
  {
    // Clear pass needs a non-empty buffer.
    std::vector<bloom_key_t> dummy = {0};
    int dummy_bursts = 1;
    KeyPack *clear_in = new KeyPack[dummy_bursts]();
    ResultPack *clear_out = new ResultPack[1]();
    pack_keys(dummy, clear_in);
    krnl_bloom(clear_in, clear_out, 1, MODE_BF_CLEAR);
    delete[] clear_in;
    delete[] clear_out;

    // All tuples -- including seed (100, 0, 1) -- flow through one subtree pass.
    // Seeds emit 0 (no alert); edges emit pid on hit, 0 otherwise.
    std::vector<bloom_key_t> tuples = {
        100, 0,   1, // seed: alloc root, insert 100  -> 0
        200, 100, 1, // child of 100, target -> alert -> 200
        300, 200, 1, // child of 200, target -> alert -> 300
        400, 200, 0, // child of 200, not target      -> 0
        500, 999, 1, // 999 not tracked               -> 0
    };

    int num_values = tuples.size();
    int num_tuples = num_values / TUPLE_FIELDS;
    int edge_bursts = (num_values + KEYS_PER_BURST - 1) / KEYS_PER_BURST;
    int edge_out_packs = (num_tuples + RESULTS_PER_BURST - 1) / RESULTS_PER_BURST;

    KeyPack *edge_in = new KeyPack[edge_bursts]();
    ResultPack *edge_out = new ResultPack[edge_out_packs]();

    pack_keys(tuples, edge_in);
    krnl_bloom(edge_in, edge_out, num_values, MODE_BF_SUBTREE);

    bloom_key_t expected[] = {0, 200, 300, 0, 0};
    bool pass = true;
    for (int i = 0; i < num_tuples; i++) {
      bloom_key_t r =
          edge_out[i / RESULTS_PER_BURST].results[i % RESULTS_PER_BURST];
      std::cout << "  tuple " << i << ": result=" << r
                << " expected=" << expected[i] << std::endl;
      if (r != expected[i])
        pass = false;
    }

    if (!pass) {
      std::cerr << "FAIL: Subtree alerts mismatch!" << std::endl;
      delete[] edge_in;
      delete[] edge_out;
      delete[] input;
      delete[] output;
      return EXIT_FAILURE;
    }
    std::cout << "Subtree test: PASS" << std::endl;

    delete[] edge_in;
    delete[] edge_out;
  }

  std::cout << "\n=== All tests passed ===" << std::endl;
  delete[] input;
  delete[] output;
  return EXIT_SUCCESS;
}
