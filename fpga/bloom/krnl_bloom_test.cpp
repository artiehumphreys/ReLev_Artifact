#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include "krnl_bloom.hpp"

static std::vector<key_t> read_keys(const std::string &filename) {
  std::vector<key_t> keys;
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    std::cerr << "Failed to open key file: " << filename << std::endl;
    std::exit(EXIT_FAILURE);
  }

  key_t key;
  while (infile >> key) {
    keys.push_back(key);
  }

  return keys;
}

static void pack_keys(const std::vector<key_t> &keys, KeyPack *input) {
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
    key_t result = output[i / RESULTS_PER_BURST].results[i % RESULTS_PER_BURST];
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
    key_t result = output[i / RESULTS_PER_BURST].results[i % RESULTS_PER_BURST];
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
    key_t result = output[i / RESULTS_PER_BURST].results[i % RESULTS_PER_BURST];
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

  // --- Streaming Subtree (shell-spawn path detection) ---
  std::cout << "\n=== Subtree Streaming Test ===" << std::endl;

  // Clear BF, then seed PID 100 as known-bad root
  {
    std::vector<key_t> seed = {100};
    int seed_n = seed.size();
    int seed_bursts = (seed_n + KEYS_PER_BURST - 1) / KEYS_PER_BURST;
    KeyPack *seed_in = new KeyPack[seed_bursts]();
    ResultPack *seed_out = new ResultPack[1]();

    pack_keys(seed, seed_in);
    krnl_bloom(seed_in, seed_out, seed_n, MODE_BF_CLEAR);
    krnl_bloom(seed_in, seed_out, seed_n, MODE_BF_INSERT);
    std::cout << "Seeded PID 100 into BF" << std::endl;

    // Edge tuples: (pid, ppid, is_target)
    // Flattened into key_t stream — 3 values per tuple
    std::vector<key_t> edges = {
        200, 100, 1, // child 200 of 100, shell → alert, insert 200
        300, 200, 1, // child 300 of 200, shell → alert, insert 300
        400, 200, 0, // child 400 of 200, NOT shell → no alert, no insert
        500, 999, 1, // child 500 of 999 (not in BF) → no alert
    };

    int num_values = edges.size();
    int num_tuples = num_values / TUPLE_FIELDS;
    int edge_bursts = (num_values + KEYS_PER_BURST - 1) / KEYS_PER_BURST;
    int edge_out_packs = (num_tuples + RESULTS_PER_BURST - 1) / RESULTS_PER_BURST;

    KeyPack *edge_in = new KeyPack[edge_bursts]();
    ResultPack *edge_out = new ResultPack[edge_out_packs]();

    pack_keys(edges, edge_in);
    krnl_bloom(edge_in, edge_out, num_values, MODE_BF_SUBTREE);

    // Expected: matched pid on alert, 0 on no match
    key_t expected[] = {200, 300, 0, 0};
    bool pass = true;
    for (int i = 0; i < num_tuples; i++) {
      key_t r =
          edge_out[i / RESULTS_PER_BURST].results[i % RESULTS_PER_BURST];
      std::cout << "  edge " << i << ": match_pid=" << r
                << " expected=" << expected[i] << std::endl;
      if (r != expected[i])
        pass = false;
    }

    if (!pass) {
      std::cerr << "FAIL: Subtree alerts mismatch!" << std::endl;
      delete[] seed_in;
      delete[] seed_out;
      delete[] edge_in;
      delete[] edge_out;
      delete[] input;
      delete[] output;
      return EXIT_FAILURE;
    }
    std::cout << "Subtree test: PASS" << std::endl;

    delete[] seed_in;
    delete[] seed_out;
    delete[] edge_in;
    delete[] edge_out;
  }

  std::cout << "\n=== All tests passed ===" << std::endl;
  delete[] input;
  delete[] output;
  return EXIT_SUCCESS;
}
