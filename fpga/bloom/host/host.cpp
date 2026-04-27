#include "../krnl_bloom.hpp"
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// XRT includes
#include "experimental/xrt_bo.h"
#include "experimental/xrt_device.h"
#include "experimental/xrt_kernel.h"

// Read log file.  Each line: pid ppid is_shell
// ppid==0 means seed (insert pid directly into BF).
// Everything else is an edge tuple for subtree streaming.
static void read_log(const std::string &filename,
                     std::vector<bloom_key_t> &seeds,
                     std::vector<bloom_key_t> &edges,
                     uint32_t &num_tuples) {
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    std::cerr << "Failed to open log file: " << filename << std::endl;
    std::exit(EXIT_FAILURE);
  }
  bloom_key_t pid, ppid, is_target;
  num_tuples = 0;
  while (infile >> pid >> ppid >> is_target) {
    if (ppid == 0) {
      seeds.push_back(pid);
    } else {
      edges.push_back(pid);
      edges.push_back(ppid);
      edges.push_back(is_target);
      num_tuples++;
    }
  }
}

static void run_kernel(xrt::kernel &krnl, xrt::device &device,
                       const std::vector<bloom_key_t> &data, uint8_t mode) {
  uint32_t num_keys = data.size();

  uint32_t input_bytes = num_keys * sizeof(bloom_key_t);
  uint32_t padded_input =
      ((input_bytes + IO_READ_BURST - 1) / IO_READ_BURST) * IO_READ_BURST;

  bool is_subtree = (mode == MODE_BF_SUBTREE || mode == MODE_CBF_SUBTREE ||
                     mode == MODE_CF_SUBTREE);
  uint32_t num_results = is_subtree ? num_keys / TUPLE_FIELDS : num_keys;
  uint32_t output_bytes = num_results * sizeof(bloom_key_t);
  uint32_t padded_output =
      ((output_bytes + IO_WRITE_BURST - 1) / IO_WRITE_BURST) * IO_WRITE_BURST;

  char *in_buffer;
  if (posix_memalign((void **)&in_buffer, 4096, padded_input)) {
    std::cerr << "Failed to memalign in_buffer" << std::endl;
    std::exit(EXIT_FAILURE);
  }
  memset(in_buffer, 0, padded_input);
  memcpy(in_buffer, data.data(), input_bytes);

  char *out_buffer;
  if (posix_memalign((void **)&out_buffer, 4096, padded_output)) {
    std::cerr << "Failed to memalign out_buffer" << std::endl;
    std::exit(EXIT_FAILURE);
  }
  memset(out_buffer, 0, padded_output);

  xrt::bo bo_in = xrt::bo(device, padded_input, krnl.group_id(0));
  xrt::bo bo_out = xrt::bo(device, padded_output, krnl.group_id(1));

  bo_in.write(in_buffer);
  bo_out.write(out_buffer);
  bo_in.sync(XCL_BO_SYNC_BO_TO_DEVICE);

  auto start_time = std::chrono::high_resolution_clock::now();
  auto run = krnl(bo_in, bo_out, num_keys, mode);
  run.wait();
  auto end_time = std::chrono::high_resolution_clock::now();

  bo_out.sync(XCL_BO_SYNC_BO_FROM_DEVICE);

  bloom_key_t *results = bo_out.map<bloom_key_t *>();

  if (is_subtree) {
    int alerts = 0;
    for (uint32_t i = 0; i < num_results; i++) {
      if (results[i] != 0) {
        bloom_key_t pid = results[i];
        bloom_key_t ppid = data[i * TUPLE_FIELDS + 1];
        std::cout << "ALERT: shell spawn detected pid=" << pid << " ppid="
                  << ppid << '\n';
        alerts++;
      }
    }
    std::cout << "Total alerts: " << alerts << "/" << num_results << '\n';
  }

  double duration =
      std::chrono::duration<double, std::milli>(end_time - start_time).count();
  std::cout << "Kernel time: " << duration << " ms" << std::endl;
  std::cout << "Throughput: " << (num_results / (duration / 1000.0))
            << " keys/s" << std::endl;

  free(in_buffer);
  free(out_buffer);
}

int main(int argc, char **argv) {
  if (argc < 3 || argc > 4) {
    std::cerr << "Usage: " << argv[0] << " <XCLBIN> <log_file> [bf|cbf|cf]\n"
              << "  log_file: one \"pid ppid is_target\" per line\n"
              << "            ppid=0 marks a seed (root of suspicious tree)\n"
              << "  filter:   bf (default), cbf, cf\n"
              << "  KEY_BITS=" << KEY_BITS << '\n';
    return EXIT_FAILURE;
  }

  std::string binaryFile = argv[1];
  std::string logFile = argv[2];
  std::string filter = (argc == 4) ? argv[3] : "bf";

  uint8_t mode_clear, mode_insert, mode_subtree;
  if (filter == "bf") {
    mode_clear = MODE_BF_CLEAR;
    mode_insert = MODE_BF_INSERT;
    mode_subtree = MODE_BF_SUBTREE;
  } else if (filter == "cbf") {
    mode_clear = MODE_CBF_CLEAR;
    mode_insert = MODE_CBF_INSERT;
    mode_subtree = MODE_CBF_SUBTREE;
  } else if (filter == "cf") {
    mode_clear = MODE_CF_CLEAR;
    mode_insert = MODE_CF_INSERT;
    mode_subtree = MODE_CF_SUBTREE;
  } else {
    std::cerr << "Unknown filter: " << filter << " (use bf, cbf, or cf)\n";
    return EXIT_FAILURE;
  }

  int device_index = 0;
  std::cout << "Opening device " << device_index << '\n';
  auto device = xrt::device(device_index);
  std::cout << "Loading xclbin: " << binaryFile << '\n';
  auto uuid = device.load_xclbin(binaryFile);
  xrt::kernel krnl = xrt::kernel(device, uuid, "krnl_bloom");

  std::cout << "filter=" << filter << "  KEY_BITS=" << KEY_BITS << '\n';

  std::vector<bloom_key_t> seeds;
  std::vector<bloom_key_t> edges;
  uint32_t num_tuples = 0;
  read_log(logFile, seeds, edges, num_tuples);
  std::cout << "Seeds: " << seeds.size() << "  Edges: " << num_tuples << '\n';

  std::cout << "\n--- Clearing filter ---\n";
  run_kernel(krnl, device, seeds, mode_clear);

  std::cout << "\n--- Seeding " << seeds.size() << " root PIDs ---\n";
  run_kernel(krnl, device, seeds, mode_insert);

  std::cout << "\n--- Streaming " << num_tuples << " edges ---\n";
  run_kernel(krnl, device, edges, mode_subtree);

  return 0;
}
