#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include "krnl_bloom.hpp"

static std::vector<uint32_t> read_keys(const std::string &filename) {
  std::vector<uint32_t> keys;
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    std::cerr << "Failed to open key file: " << filename << std::endl;
    std::exit(EXIT_FAILURE);
  }

  uint32_t key;
  while (infile >> key) {
    keys.push_back(key);
  }

  return keys;
}

static void pack_keys(const std::vector<uint32_t> &keys, KeyPack *input) {
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
  int num_output_packs = (num_keys + IO_WRITE_BURST - 1) / IO_WRITE_BURST;

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
    uint8_t result = output[i / IO_WRITE_BURST].results[i % IO_WRITE_BURST];
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
    uint8_t result = output[i / IO_WRITE_BURST].results[i % IO_WRITE_BURST];
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
    uint8_t result = output[i / IO_WRITE_BURST].results[i % IO_WRITE_BURST];
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

  std::cout << "\n=== All tests passed ===" << std::endl;
  delete[] input;
  delete[] output;
  return EXIT_SUCCESS;
}
