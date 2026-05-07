#include "krnl_bloom.hpp"
#include "bloom_filter_hls.hpp"
#include "counting_bloom_filter_hls.hpp"
#include "cuckoo_filter_hls.hpp"

// =====================================================================
// DATA MOVEMENT: READ INPUT
// =====================================================================
// Unpacks 64-byte bursts from HBM into a 500 MHz stream of keys.
static void read_input(KeyPack *in, hls::stream<KeyItem> &keyStream, uint32_t num_keys) {
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

    // Send done sentinel to stop downstream processes
    KeyItem sentinel;
    sentinel.key = 0;
    sentinel.done = 1;
    keyStream << sentinel;
}

// =====================================================================
// PROCESSING ENGINE: BLOOM PROCESS
// =====================================================================
static void bloom_process(hls::stream<KeyItem> &keyStream, 
                          hls::stream<ResultItem> &resultStream, 
                          uint8_t mode) {

    // --- CONDITIONALLY ALLOCATED HARDWARE RESOURCES ---
    // These static arrays map to BRAM/URAM. Macros prune unused filters.

    #if defined(BUILD_BF_ONLY) || (!defined(BUILD_CBF_ONLY) && !defined(BUILD_CF_ONLY))
    static uint8_t bf_roots[NUM_ROOTS][BF_NUM_BYTES_PER_ROOT];
    #pragma HLS BIND_STORAGE variable = bf_roots type = ram_2p impl = bram
    #pragma HLS ARRAY_PARTITION variable = bf_roots dim = 1 complete
    static uint32_t next_root_bf = 0;
    #endif

    #if defined(BUILD_CBF_ONLY) || (!defined(BUILD_BF_ONLY) && !defined(BUILD_CF_ONLY))
    static uint8_t cbf_roots[NUM_ROOTS][CBF_SIZE_PER_ROOT];
    #pragma HLS BIND_STORAGE variable = cbf_roots type = ram_2p impl = bram
    #pragma HLS ARRAY_PARTITION variable = cbf_roots dim = 1 complete
    static uint32_t next_root_cbf = 0;
    #endif

    #if defined(BUILD_CF_ONLY) || (!defined(BUILD_BF_ONLY) && !defined(BUILD_CBF_ONLY))
    static uint8_t cf_roots[NUM_ROOTS][CF_TABLE_BYTES_PER_ROOT];
    #pragma HLS BIND_STORAGE variable = cf_roots type = ram_2p impl = bram
    #pragma HLS ARRAY_PARTITION variable = cf_roots dim = 1 complete
    static uint32_t next_root_cf = 0;
    #endif

    // --- CLEAR PASSES ---
    
    if (mode == MODE_BF_CLEAR) {
        #if defined(BUILD_BF_ONLY) || (!defined(BUILD_CBF_ONLY) && !defined(BUILD_CF_ONLY))
        for (uint32_t r = 0; r < NUM_ROOTS; r++) {
            #pragma HLS UNROLL
            for (uint32_t i = 0; i < BF_NUM_BYTES_PER_ROOT; i++) {
                #pragma HLS pipeline II = 1
                bf_roots[r][i] = 0;
            }
        }
        next_root_bf = 0;
        #endif
        while (1) { KeyItem item; keyStream >> item; if (item.done) break; }
        ResultItem res; res.result = 0; res.done = 1; resultStream << res;
        return;
    }

    if (mode == MODE_CBF_CLEAR) {
        #if defined(BUILD_CBF_ONLY) || (!defined(BUILD_BF_ONLY) && !defined(BUILD_CF_ONLY))
        for (uint32_t r = 0; r < NUM_ROOTS; r++) {
            #pragma HLS UNROLL
            for (uint32_t i = 0; i < CBF_SIZE_PER_ROOT; i++) {
                #pragma HLS pipeline II = 1
                cbf_roots[r][i] = 0;
            }
        }
        next_root_cbf = 0;
        #endif
        while (1) { KeyItem item; keyStream >> item; if (item.done) break; }
        ResultItem res; res.result = 0; res.done = 1; resultStream << res;
        return;
    }

    if (mode == MODE_CF_CLEAR) {
        #if defined(BUILD_CF_ONLY) || (!defined(BUILD_BF_ONLY) && !defined(BUILD_CBF_ONLY))
        for (uint32_t r = 0; r < NUM_ROOTS; r++) {
            #pragma HLS UNROLL
            for (uint32_t i = 0; i < CF_TABLE_BYTES_PER_ROOT; i++) {
                #pragma HLS pipeline II = 1
                cf_roots[r][i] = 0;
            }
        }
        next_root_cf = 0;
        #endif
        while (1) { KeyItem item; keyStream >> item; if (item.done) break; }
        ResultItem res; res.result = 0; res.done = 1; resultStream << res;
        return;
    }

    // --- SUBTREE STREAMING (ANCESTRY PROPAGATION) ---

    // BF Implementation
    if (mode == MODE_BF_SUBTREE) {
        while (1) {
            KeyItem pid_item; keyStream >> pid_item;
            if (pid_item.done) { ResultItem d; d.result=0; d.done=1; resultStream << d; break; }
            KeyItem ppid_item; keyStream >> ppid_item;
            KeyItem target_item; keyStream >> target_item;

            ResultItem res; res.done = 0; res.result = 0;

            #if defined(BUILD_BF_ONLY) || (!defined(BUILD_CBF_ONLY) && !defined(BUILD_CF_ONLY))
            if (ppid_item.key == 0) { // Seed Logic
                uint32_t r = next_root_bf & (NUM_ROOTS - 1);
                next_root_bf++;
                hls_bloom_insert_at<NUM_ROOTS, BF_SIZE_PER_ROOT, BF_NUM_HASHES>(bf_roots, r, pid_item.key);
                res.result = pid_item.key; // Seed return
            } else if (target_item.key != TUPLE_REMOVE) {
                uint64_t hits = hls_bloom_query_all<NUM_ROOTS, BF_SIZE_PER_ROOT, BF_NUM_HASHES>(bf_roots, ppid_item.key);
                if (hits != 0 && target_item.key != 0) {
                    for (uint32_t r = 0; r < NUM_ROOTS; r++) {
                        #pragma HLS UNROLL
                        if (hits & (static_cast<uint64_t>(1) << r)) {
                            hls_bloom_insert_at<NUM_ROOTS, BF_SIZE_PER_ROOT, BF_NUM_HASHES>(bf_roots, r, pid_item.key);
                        }
                    }
                    res.result = pid_item.key; // Alert Trigger
                }
            }
            #endif
            resultStream << res;
        }
        return;
    }

    // CBF Implementation (Supports Removal)
    if (mode == MODE_CBF_SUBTREE) {
        while (1) {
            KeyItem pid_item; keyStream >> pid_item;
            if (pid_item.done) { ResultItem d; d.result=0; d.done=1; resultStream << d; break; }
            KeyItem ppid_item; keyStream >> ppid_item;
            KeyItem target_item; keyStream >> target_item;

            ResultItem res; res.done = 0; res.result = 0;

            #if defined(BUILD_CBF_ONLY) || (!defined(BUILD_BF_ONLY) && !defined(BUILD_CF_ONLY))
            if (ppid_item.key == 0) {
                uint32_t r = next_root_cbf & (NUM_ROOTS - 1);
                next_root_cbf++;
                hls_cbf_insert_at<NUM_ROOTS, CBF_SIZE_PER_ROOT, CBF_NUM_HASHES>(cbf_roots, r, pid_item.key);
                res.result = pid_item.key;
            } else if (target_item.key == TUPLE_REMOVE) {
                uint64_t hits = hls_cbf_query_all<NUM_ROOTS, CBF_SIZE_PER_ROOT, CBF_NUM_HASHES>(cbf_roots, pid_item.key);
                for (uint32_t r = 0; r < NUM_ROOTS; r++) {
                    #pragma HLS UNROLL
                    if (hits & (static_cast<uint64_t>(1) << r))
                        hls_cbf_remove_at<NUM_ROOTS, CBF_SIZE_PER_ROOT, CBF_NUM_HASHES>(cbf_roots, r, pid_item.key);
                }
            } else {
                uint64_t hits = hls_cbf_query_all<NUM_ROOTS, CBF_SIZE_PER_ROOT, CBF_NUM_HASHES>(cbf_roots, ppid_item.key);
                if (hits != 0 && target_item.key != 0) {
                    for (uint32_t r = 0; r < NUM_ROOTS; r++) {
                        #pragma HLS UNROLL
                        if (hits & (static_cast<uint64_t>(1) << r))
                            hls_cbf_insert_at<NUM_ROOTS, CBF_SIZE_PER_ROOT, CBF_NUM_HASHES>(cbf_roots, r, pid_item.key);
                    }
                    res.result = pid_item.key;
                }
            }
            #endif
            resultStream << res;
        }
        return;
    }

    // Cuckoo Implementation
    if (mode == MODE_CF_SUBTREE) {
        while (1) {
            KeyItem pid_item; keyStream >> pid_item;
            if (pid_item.done) { ResultItem d; d.result=0; d.done=1; resultStream << d; break; }
            KeyItem ppid_item; keyStream >> ppid_item;
            KeyItem target_item; keyStream >> target_item;

            ResultItem res; res.done = 0; res.result = 0;

            #if defined(BUILD_CF_ONLY) || (!defined(BUILD_BF_ONLY) && !defined(BUILD_CBF_ONLY))
            if (ppid_item.key == 0) {
                uint32_t r = next_root_cf & (NUM_ROOTS - 1);
                next_root_cf++;
                hls_cuckoo_insert_at<NUM_ROOTS, CF_NUM_BUCKETS_PER_ROOT, CF_SLOTS_PER_BUCKET>(cf_roots, r, pid_item.key);
                res.result = pid_item.key;
            } else if (target_item.key == TUPLE_REMOVE) {
                uint64_t hits = hls_cuckoo_query_all<NUM_ROOTS, CF_NUM_BUCKETS_PER_ROOT, CF_SLOTS_PER_BUCKET>(cf_roots, pid_item.key);
                for (uint32_t r = 0; r < NUM_ROOTS; r++) {
                    #pragma HLS UNROLL
                    if (hits & (static_cast<uint64_t>(1) << r))
                        hls_cuckoo_remove_at<NUM_ROOTS, CF_NUM_BUCKETS_PER_ROOT, CF_SLOTS_PER_BUCKET>(cf_roots, r, pid_item.key);
                }
            } else {
                uint64_t hits = hls_cuckoo_query_all<NUM_ROOTS, CF_NUM_BUCKETS_PER_ROOT, CF_SLOTS_PER_BUCKET>(cf_roots, ppid_item.key);
                if (hits != 0 && target_item.key != 0) {
                    for (uint32_t r = 0; r < NUM_ROOTS; r++) {
                        #pragma HLS UNROLL
                        if (hits & (static_cast<uint64_t>(1) << r))
                            hls_cuckoo_insert_at<NUM_ROOTS, CF_NUM_BUCKETS_PER_ROOT, CF_SLOTS_PER_BUCKET>(cf_roots, r, pid_item.key);
                    }
                    res.result = pid_item.key;
                }
            }
            #endif
            resultStream << res;
        }
        return;
    }
}

// =====================================================================
// DATA MOVEMENT: WRITE RESULTS
// =====================================================================
// Packs individual alerts back into 64-byte bursts for HBM efficiency.
static void write_result(ResultPack *out, hls::stream<ResultItem> &resultStream) {
    int next_index = 0;
    int result_i = 0;
    ResultPack pack = {};

    while (1) {
        #pragma HLS pipeline II = 1
        ResultItem item;
        resultStream >> item;

        if (item.done) {
            if (result_i > 0) out[next_index] = pack;
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

// =====================================================================
// TOP-LEVEL KERNEL (V++ ENTRY POINT)
// =====================================================================
extern "C" {
void krnl_bloom(KeyPack *input, ResultPack *output, uint32_t num_keys, uint8_t mode) {
    #pragma HLS INTERFACE mode = m_axi depth = 1024 port = input bundle = gmem0
    #pragma HLS INTERFACE mode = m_axi depth = 1024 port = output bundle = gmem1
    #pragma HLS INTERFACE ap_ctrl_chain port = return

    hls::stream<KeyItem, 32> keyStream("key_stream");
    hls::stream<ResultItem, 32> resultStream("result_stream");

    // DATAFLOW pragma enables concurrent execution of Read, Process, and Write
    #pragma HLS dataflow
    read_input(input, keyStream, num_keys);
    bloom_process(keyStream, resultStream, mode);
    write_result(output, resultStream);
}
}
