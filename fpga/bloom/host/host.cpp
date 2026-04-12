#include "../krnl_bloom.hpp"
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

// XRT includes
#include "experimental/xrt_bo.h"
#include "experimental/xrt_device.h"
#include "experimental/xrt_kernel.h"

static uint8_t parse_mode(const std::string &mode_str) {
  if (mode_str == "bf_clear")
    return MODE_BF_CLEAR;
  if (mode_str == "bf_insert")
    return MODE_BF_INSERT;
  if (mode_str == "bf_query")
    return MODE_BF_QUERY;
  if (mode_str == "cbf_clear")
    return MODE_CBF_CLEAR;
  if (mode_str == "cbf_insert")
    return MODE_CBF_INSERT;
  if (mode_str == "cbf_remove")
    return MODE_CBF_REMOVE;
  if (mode_str == "cbf_query")
    return MODE_CBF_QUERY;
  std::cerr << "Unknown mode: " << mode_str << std::endl;
  std::exit(EXIT_FAILURE);
}

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

static void run_kernel(xrt::kernel &krnl, xrt::device &device,
                       const std::vector<uint32_t> &keys, uint8_t mode) {
  uint32_t num_keys = keys.size();

  // Pad input buffer to a multiple of IO_READ_BURST (64 bytes)
  uint32_t input_bytes = num_keys * sizeof(uint32_t);
  uint32_t padded_input =
      ((input_bytes + IO_READ_BURST - 1) / IO_READ_BURST) * IO_READ_BURST;

  // Output buffer: one byte per key, padded to IO_WRITE_BURST
  uint32_t output_bytes = num_keys;
  uint32_t padded_output =
      ((output_bytes + IO_WRITE_BURST - 1) / IO_WRITE_BURST) * IO_WRITE_BURST;

  // Allocate aligned host buffers
  char *in_buffer;
  if (posix_memalign((void **)&in_buffer, 4096, padded_input)) {
    std::cerr << "Failed to memalign in_buffer" << std::endl;
    std::exit(EXIT_FAILURE);
  }
  memset(in_buffer, 0, padded_input);
  memcpy(in_buffer, keys.data(), input_bytes);

  char *out_buffer;
  if (posix_memalign((void **)&out_buffer, 4096, padded_output)) {
    std::cerr << "Failed to memalign out_buffer" << std::endl;
    std::exit(EXIT_FAILURE);
  }
  memset(out_buffer, 0, padded_output);

  // Allocate device buffers
  xrt::bo bo_in = xrt::bo(device, padded_input, krnl.group_id(0));
  xrt::bo bo_out = xrt::bo(device, padded_output, krnl.group_id(1));

  bo_in.write(in_buffer);
  bo_out.write(out_buffer);

  // Transfer input to device
  bo_in.sync(XCL_BO_SYNC_BO_TO_DEVICE);

  // Run kernel with timing
  auto start_time = std::chrono::high_resolution_clock::now();
  auto run = krnl(bo_in, bo_out, num_keys, mode);
  run.wait();
  auto end_time = std::chrono::high_resolution_clock::now();

  // Transfer results from device
  bo_out.sync(XCL_BO_SYNC_BO_FROM_DEVICE);

  uint8_t *results = bo_out.map<uint8_t *>();

  // Print results for query modes
  if (mode == MODE_BF_QUERY || mode == MODE_CBF_QUERY) {
    for (uint32_t i = 0; i < num_keys; i++) {
      std::cout << "Key " << keys[i] << ": "
                << (results[i] ? "FOUND" : "NOT FOUND") << std::endl;
    }
  }

  double duration =
      std::chrono::duration<double, std::milli>(end_time - start_time).count();
  std::cout << "Kernel time: " << duration << " ms" << std::endl;
  std::cout << "Keys processed: " << num_keys << std::endl;
  std::cout << "Throughput: " << (num_keys / (duration / 1000.0)) << " keys/s"
            << std::endl;

  free(in_buffer);
  free(out_buffer);
}

int main(int argc, char **argv) {
  if (argc < 4) {
    std::cout << "Usage: " << argv[0]
              << " <XCLBIN> <keys_file> <mode> [mode2] [mode3] ..."
              << std::endl;
    std::cout << "Modes: bf_clear, bf_insert, bf_query, cbf_clear, cbf_insert, "
                 "cbf_remove, cbf_query"
              << std::endl;
    return EXIT_FAILURE;
  }

  std::string binaryFile = argv[1];
  std::string keysFile = argv[2];

  // Open device and load xclbin
  int device_index = 0;
  std::cout << "Opening device " << device_index << std::endl;
  auto device = xrt::device(device_index);
  std::cout << "Loading xclbin: " << binaryFile << std::endl;
  auto uuid = device.load_xclbin(binaryFile);

  xrt::kernel krnl = xrt::kernel(device, uuid, "krnl_bloom");

  // Read keys from file
  auto keys = read_keys(keysFile);
  std::cout << "Read " << keys.size() << " keys from " << keysFile << std::endl;

  // Execute each mode in sequence (e.g., bf_clear bf_insert bf_query)
  for (int i = 3; i < argc; i++) {
    std::string mode_str = argv[i];
    uint8_t mode = parse_mode(mode_str);
    std::cout << "\n--- Running mode: " << mode_str << " ---" << std::endl;
    run_kernel(krnl, device, keys, mode);
  }

  return 0;
}
