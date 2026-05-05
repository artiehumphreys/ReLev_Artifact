#include "krnl_bloom.hpp"
#include "bloom_filter_hls.hpp"
#include "counting_bloom_filter_hls.hpp"
#include "cuckoo_filter_hls.hpp"

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

// Per-root state for *_SUBTREE modes -- dim 1 partitioned so all NUM_ROOTS
// banks read in parallel for query_all.
static inline int popcount64(uint64_t v) {
#pragma HLS INLINE
  int c = 0;
  for (int i = 0; i < 64; i++) {
#pragma HLS UNROLL
    if (v & (static_cast<uint64_t>(1) << i))
      c++;
  }
  return c;
}

static inline uint32_t first_set64(uint64_t v) {
#pragma HLS INLINE
  for (uint32_t i = 0; i < 64; i++) {
#pragma HLS UNROLL
    if (v & (static_cast<uint64_t>(1) << i))
      return i;
  }
  return 64;
}

static void bloom_process(hls::stream<KeyItem> &keyStream,
                          hls::stream<ResultItem> &resultStream, uint8_t mode) {
  static uint8_t bf_bits[BF_NUM_BYTES];
#pragma HLS BIND_STORAGE variable = bf_bits type = ram_2p impl = bram
#pragma HLS ARRAY_PARTITION variable = bf_bits cyclic factor = 4

  static uint8_t cbf_counters[CBF_SIZE];
#pragma HLS BIND_STORAGE variable = cbf_counters type = ram_2p impl = bram
#pragma HLS ARRAY_PARTITION variable = cbf_counters cyclic factor = 4

  static uint8_t cf_table[CF_TABLE_BYTES];
#pragma HLS BIND_STORAGE variable = cf_table type = ram_2p impl = bram
#pragma HLS ARRAY_PARTITION variable = cf_table cyclic factor =                \
    CF_SLOTS_PER_BUCKET

  static uint8_t bf_roots[NUM_ROOTS][BF_NUM_BYTES_PER_ROOT];
#pragma HLS BIND_STORAGE variable = bf_roots type = ram_2p impl = bram
#pragma HLS ARRAY_PARTITION variable = bf_roots dim = 1 complete

  static uint8_t cbf_roots[NUM_ROOTS][CBF_SIZE_PER_ROOT];
#pragma HLS BIND_STORAGE variable = cbf_roots type = ram_2p impl = bram
#pragma HLS ARRAY_PARTITION variable = cbf_roots dim = 1 complete

  static uint8_t cf_roots[NUM_ROOTS][CF_TABLE_BYTES_PER_ROOT];
#pragma HLS BIND_STORAGE variable = cf_roots type = ram_2p impl = bram
#pragma HLS ARRAY_PARTITION variable = cf_roots dim = 1 complete

  static uint32_t next_root_bf = 0;
  static uint32_t next_root_cbf = 0;
  static uint32_t next_root_cf = 0;

  if (mode == MODE_BF_CLEAR) {
    for (uint32_t i = 0; i < BF_NUM_BYTES; i++) {
#pragma HLS pipeline II = 1
      bf_bits[i] = 0;
    }
    for (uint32_t r = 0; r < NUM_ROOTS; r++) {
#pragma HLS UNROLL
      for (uint32_t i = 0; i < BF_NUM_BYTES_PER_ROOT; i++) {
#pragma HLS pipeline II = 1
        bf_roots[r][i] = 0;
      }
    }
    next_root_bf = 0;

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
    for (uint32_t r = 0; r < NUM_ROOTS; r++) {
#pragma HLS UNROLL
      for (uint32_t i = 0; i < CBF_SIZE_PER_ROOT; i++) {
#pragma HLS pipeline II = 1
        cbf_roots[r][i] = 0;
      }
    }
    next_root_cbf = 0;

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

  if (mode == MODE_CF_CLEAR) {
    for (uint32_t i = 0; i < CF_TABLE_BYTES; i++) {
#pragma HLS pipeline II = 1
      cf_table[i] = 0;
    }
    for (uint32_t r = 0; r < NUM_ROOTS; r++) {
#pragma HLS UNROLL
      for (uint32_t i = 0; i < CF_TABLE_BYTES_PER_ROOT; i++) {
#pragma HLS pipeline II = 1
        cf_roots[r][i] = 0;
      }
    }
    next_root_cf = 0;

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

  // Per-root subtree mode: stream (pid, ppid, is_target) tuples.
  //   ppid == 0          -> seed: allocate next root, insert pid there.
  //   target == REMOVE   -> BF cannot delete; skip.
  //   else               -> parallel query_all on ppid across all NUM_ROOTS BFs.
  //                        Permissive policy: on any hit AND target != 0,
  //                        insert pid into every hit root and emit alert.
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

      ResultItem res;
      res.done = 0;
      res.result = 0;

      if (ppid_item.key == 0) {
        uint32_t r = next_root_bf & (NUM_ROOTS - 1);
        next_root_bf++;
        hls_bloom_insert_at<NUM_ROOTS, BF_SIZE_PER_ROOT, BF_NUM_HASHES>(
            bf_roots, r, pid_item.key);
        // seed: no alert
      } else if (target_item.key == TUPLE_REMOVE) {
        // BF cannot delete -- drop
      } else {
        uint64_t hits =
            hls_bloom_query_all<NUM_ROOTS, BF_SIZE_PER_ROOT, BF_NUM_HASHES>(
                bf_roots, ppid_item.key);
        if (hits != 0 && target_item.key != 0) {
          for (uint32_t r = 0; r < NUM_ROOTS; r++) {
#pragma HLS UNROLL
            if (hits & (static_cast<uint64_t>(1) << r)) {
              hls_bloom_insert_at<NUM_ROOTS, BF_SIZE_PER_ROOT, BF_NUM_HASHES>(
                  bf_roots, r, pid_item.key);
            }
          }
          res.result = pid_item.key;
        }
      }

      resultStream << res;
    }
    return;
  }

  // Per-root CBF subtree mode: same protocol, supports removal.
  // Permissive policy: insert into / remove from every hit root.
  if (mode == MODE_CBF_SUBTREE) {
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

      ResultItem res;
      res.done = 0;
      res.result = 0;

      if (ppid_item.key == 0) {
        uint32_t r = next_root_cbf & (NUM_ROOTS - 1);
        next_root_cbf++;
        hls_cbf_insert_at<NUM_ROOTS, CBF_SIZE_PER_ROOT, CBF_NUM_HASHES>(
            cbf_roots, r, pid_item.key);
        // seed: no alert
      } else if (target_item.key == TUPLE_REMOVE) {
        uint64_t hits =
            hls_cbf_query_all<NUM_ROOTS, CBF_SIZE_PER_ROOT, CBF_NUM_HASHES>(
                cbf_roots, pid_item.key);
        for (uint32_t r = 0; r < NUM_ROOTS; r++) {
#pragma HLS UNROLL
          if (hits & (static_cast<uint64_t>(1) << r)) {
            hls_cbf_remove_at<NUM_ROOTS, CBF_SIZE_PER_ROOT, CBF_NUM_HASHES>(
                cbf_roots, r, pid_item.key);
          }
        }
      } else {
        uint64_t hits =
            hls_cbf_query_all<NUM_ROOTS, CBF_SIZE_PER_ROOT, CBF_NUM_HASHES>(
                cbf_roots, ppid_item.key);
        if (hits != 0 && target_item.key != 0) {
          for (uint32_t r = 0; r < NUM_ROOTS; r++) {
#pragma HLS UNROLL
            if (hits & (static_cast<uint64_t>(1) << r)) {
              hls_cbf_insert_at<NUM_ROOTS, CBF_SIZE_PER_ROOT, CBF_NUM_HASHES>(
                  cbf_roots, r, pid_item.key);
            }
          }
          res.result = pid_item.key;
        }
      }

      resultStream << res;
    }
    return;
  }

  // Per-root cuckoo subtree mode: supports exact removal.
  // Permissive policy: on >=1 hits, insert pid into every hit root; on remove,
  // remove from every hit root.
  if (mode == MODE_CF_SUBTREE) {
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

      ResultItem res;
      res.done = 0;
      res.result = 0;

      if (ppid_item.key == 0) {
        uint32_t r = next_root_cf & (NUM_ROOTS - 1);
        next_root_cf++;
        hls_cuckoo_insert_at<NUM_ROOTS, CF_NUM_BUCKETS_PER_ROOT,
                             CF_SLOTS_PER_BUCKET>(cf_roots, r, pid_item.key);
        // seed: no alert
      } else if (target_item.key == TUPLE_REMOVE) {
        uint64_t hits =
            hls_cuckoo_query_all<NUM_ROOTS, CF_NUM_BUCKETS_PER_ROOT,
                                 CF_SLOTS_PER_BUCKET>(cf_roots, pid_item.key);
        for (uint32_t r = 0; r < NUM_ROOTS; r++) {
#pragma HLS UNROLL
          if (hits & (static_cast<uint64_t>(1) << r)) {
            hls_cuckoo_remove_at<NUM_ROOTS, CF_NUM_BUCKETS_PER_ROOT,
                                 CF_SLOTS_PER_BUCKET>(cf_roots, r,
                                                      pid_item.key);
          }
        }
      } else {
        uint64_t hits =
            hls_cuckoo_query_all<NUM_ROOTS, CF_NUM_BUCKETS_PER_ROOT,
                                 CF_SLOTS_PER_BUCKET>(cf_roots, ppid_item.key);
        if (hits != 0 && target_item.key != 0) {
          for (uint32_t r = 0; r < NUM_ROOTS; r++) {
#pragma HLS UNROLL
            if (hits & (static_cast<uint64_t>(1) << r)) {
              hls_cuckoo_insert_at<NUM_ROOTS, CF_NUM_BUCKETS_PER_ROOT,
                                   CF_SLOTS_PER_BUCKET>(cf_roots, r,
                                                        pid_item.key);
            }
          }
          res.result = pid_item.key;
        }
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
    case MODE_CF_INSERT:
      res.result = hls_cuckoo_insert<CF_NUM_BUCKETS, CF_SLOTS_PER_BUCKET>(
                       cf_table, item.key)
                       ? 1
                       : 0;
      break;
    case MODE_CF_QUERY:
      res.result = hls_cuckoo_query<CF_NUM_BUCKETS, CF_SLOTS_PER_BUCKET>(
                       cf_table, item.key)
                       ? 1
                       : 0;
      break;
    case MODE_CF_REMOVE:
      res.result = hls_cuckoo_remove<CF_NUM_BUCKETS, CF_SLOTS_PER_BUCKET>(
                       cf_table, item.key)
                       ? 1
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
