#include "krnl_bloom.hpp"
#include "bloom_filter_hls.hpp"
#include "counting_bloom_filter_hls.hpp"

// Read KeyPack bursts from HBM and unpack individual keys into a stream.
static void read_input(KeyPack *in, hls::stream<KeyItem> &keyStream,
                       uint32_t num_keys) {
  uint32_t num_burst_reads = (num_keys + KEYS_PER_BURST - 1) / KEYS_PER_BURST;
  uint32_t key_counter = 0;

  for (uint32_t burst = 0; burst < num_burst_reads; burst++) {
    KeyPack pack = in[burst];

    for (int i = 0; i < KEYS_PER_BURST; i++) {
#pragma HLS pipeline II = 1

      if (key_counter < num_keys) {
        KeyItem item;
        item.key = pack.keys[i];
        item.done = 0;
        keyStream << item;
        key_counter++;
      }
    }
  }

  // Send done sentinel
  KeyItem sentinel;
  sentinel.key = 0;
  sentinel.done = 1;
  keyStream << sentinel;
}

// Process keys through the bloom filter / counting bloom filter.
// Uses static BRAM arrays that persist across kernel invocations.
static void bloom_process(hls::stream<KeyItem> &keyStream,
                          hls::stream<ResultItem> &resultStream, uint8_t mode) {
  static uint8_t bf_bits[BF_NUM_BYTES];
#pragma HLS BIND_STORAGE variable = bf_bits type = ram_2p impl = bram
#pragma HLS ARRAY_PARTITION variable = bf_bits cyclic factor = 4

  static uint8_t cbf_counters[CBF_SIZE];
#pragma HLS BIND_STORAGE variable = cbf_counters type = ram_2p impl = bram
#pragma HLS ARRAY_PARTITION variable = cbf_counters cyclic factor = 4

  if (mode == MODE_BF_CLEAR) {
    for (uint32_t i = 0; i < BF_NUM_BYTES; i++) {
#pragma HLS pipeline II = 1
      bf_bits[i] = 0;
    }

    // read until done sentinel
    while (1) {
      KeyItem item;
      keyStream >> item;
      if (item.done)
        break;
    }

    // Push a single done sentinel to the result stream
    ResultItem done_item;
    done_item.result = 0;
    done_item.done = 1;
    resultStream << done_item;
    return;
  }

  if (mode == MODE_CBF_CLEAR) {
    for (uint32_t i = 0; i < CBF_SIZE; i++) {
#pragma HLS pipeline II = 1
      cbf_counters[i] = 0;
    }

    while (1) {
      KeyItem item;
      keyStream >> item;
      if (item.done)
        break;
    }

    ResultItem done_item;
    done_item.result = 0;
    done_item.done = 1;
    resultStream << done_item;
    return;
  }

  // Subtree mode: stream (pid, ppid, is_target) tuples.
  // Query ppid in BF; if found AND is_target, insert pid and emit alert.
  if (mode == MODE_BF_SUBTREE) {
    while (1) {
      KeyItem pid_item;
      keyStream >> pid_item;
      if (pid_item.done) {
        ResultItem done_item;
        done_item.result = 0;
        done_item.done = 1;
        resultStream << done_item;
        break;
      }

      KeyItem ppid_item;
      keyStream >> ppid_item;

      KeyItem target_item;
      keyStream >> target_item;

      bool ppid_found =
          hls_bloom_query<BF_SIZE, BF_NUM_HASHES>(bf_bits, ppid_item.key);

      ResultItem res;
      res.done = 0;

      if (ppid_found && (target_item.key != 0)) {
        hls_bloom_insert<BF_SIZE, BF_NUM_HASHES>(bf_bits, pid_item.key);
        res.result = pid_item.key; // alert: emit matched pid
      } else {
        res.result = 0;
      }

      resultStream << res;
    }
    return;
  }

  // Process keys for INSERT/REMOVE/QUERY modes
  while (1) {
#pragma HLS pipeline II = 1

    KeyItem item;
    keyStream >> item;

    if (item.done) {
      ResultItem done_item;
      done_item.result = 0;
      done_item.done = 1;
      resultStream << done_item;
      break;
    }

    ResultItem res;
    res.done = 0;

    switch (mode) {
    case MODE_BF_INSERT:
      hls_bloom_insert<BF_SIZE, BF_NUM_HASHES>(bf_bits, item.key);
      res.result = 1;
      break;
    case MODE_BF_QUERY:
      res.result =
          hls_bloom_query<BF_SIZE, BF_NUM_HASHES>(bf_bits, item.key) ? 1 : 0;
      break;
    case MODE_CBF_INSERT:
      hls_cbf_insert<CBF_SIZE, CBF_NUM_HASHES>(cbf_counters, item.key);
      res.result = 1;
      break;
    case MODE_CBF_REMOVE:
      hls_cbf_remove<CBF_SIZE, CBF_NUM_HASHES>(cbf_counters, item.key);
      res.result = 1;
      break;
    case MODE_CBF_QUERY:
      res.result =
          hls_cbf_query<CBF_SIZE, CBF_NUM_HASHES>(cbf_counters, item.key) ? 1
                                                                          : 0;
      break;
    default:
      res.result = 0;
      break;
    }

    resultStream << res;
  }
}

// Pack individual results into 64-byte bursts and write to HBM.
static void write_result(ResultPack *out,
                         hls::stream<ResultItem> &resultStream) {
  int next_index = 0;
  int result_i = 0;
  ResultPack pack = {};

  while (1) {
#pragma HLS pipeline II = 1

    ResultItem item;
    resultStream >> item;

    if (item.done) {
      // Flush any partial pack
      if (result_i > 0) {
        out[next_index] = pack;
      }
      break;
    }

    pack.results[result_i++] = item.result;

    if (result_i == RESULTS_PER_BURST) {
      out[next_index++] = pack;
      pack = {};
      result_i = 0;
    }
  }
}

extern "C" {
/*
    Bloom Filter Kernel using dataflow architecture.
    Arguments:
        input    (input)  --> Key data from HBM
        output   (output) --> Query results to HBM
        num_keys (input)  --> Number of keys to process
        mode     (input)  --> Operation mode
*/
void krnl_bloom(KeyPack *input, ResultPack *output, uint32_t num_keys,
                uint8_t mode) {
#pragma HLS INTERFACE mode = m_axi depth = 1024 port = input bundle = gmem0
#pragma HLS INTERFACE mode = m_axi depth = 1024 port = output bundle = gmem1
#pragma HLS INTERFACE ap_ctrl_chain port = return

  hls::stream<KeyItem, 32> keyStream("key_stream");
  hls::stream<ResultItem, 32> resultStream("result_stream");

#pragma HLS dataflow

  read_input(input, keyStream, num_keys);
  bloom_process(keyStream, resultStream, mode);
  write_result(output, resultStream);
}
}
