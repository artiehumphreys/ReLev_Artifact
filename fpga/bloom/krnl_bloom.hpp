#pragma once

#include <cstdint>
#include <hls_stream.h>

// Key width: compile with -DKEY_BITS=16 or -DKEY_BITS=32
#ifndef KEY_BITS
#define KEY_BITS 32
#endif

#if KEY_BITS == 16
typedef uint16_t bloom_key_t;
#define KEYS_PER_BURST 32    // 64 / 2
#define TUPLES_PER_BURST 10  // 64 / (3*2)
#define RESULTS_PER_BURST 32 // 64 / 2
#elif KEY_BITS == 32
typedef uint32_t bloom_key_t;
#define KEYS_PER_BURST 16    // 64 / 4
#define TUPLES_PER_BURST 5   // 64 / (3*4)
#define RESULTS_PER_BURST 16 // 64 / 4
#else
#error "KEY_BITS must be 16 or 32"
#endif

// IO burst sizes matching HBM 512-bit width
#define IO_READ_BURST 64
#define IO_WRITE_BURST 64

// CBF & BF parameters (must be power of 2)
#define BF_SIZE 8192
#define BF_NUM_HASHES 3
#define BF_NUM_BYTES (BF_SIZE / 8)

#define CBF_SIZE 8192
#define CBF_NUM_HASHES 3

// Cuckoo filter parameters (NUM_BUCKETS must be power of 2)
#define CF_NUM_BUCKETS 2048
#define CF_SLOTS_PER_BUCKET 4
#define CF_TABLE_BYTES (CF_NUM_BUCKETS * CF_SLOTS_PER_BUCKET)

// Edge tuple: pid, ppid, is_target
#define TUPLE_FIELDS 3

// Operation modes
#define MODE_BF_CLEAR 0
#define MODE_BF_INSERT 1
#define MODE_BF_QUERY 2
#define MODE_CBF_CLEAR 3
#define MODE_CBF_INSERT 4
#define MODE_CBF_REMOVE 5
#define MODE_CBF_QUERY 6
#define MODE_BF_SUBTREE 7 // stream mode
#define MODE_CBF_SUBTREE 8
#define MODE_CF_CLEAR 9
#define MODE_CF_INSERT 10
#define MODE_CF_QUERY 11
#define MODE_CF_REMOVE 12
#define MODE_CF_SUBTREE 13

struct KeyPack {
  bloom_key_t keys[KEYS_PER_BURST];
};

struct ResultPack {
  bloom_key_t results[RESULTS_PER_BURST];
};

struct KeyItem {
  bloom_key_t key;
  uint8_t done;
};

struct ResultItem {
  bloom_key_t result; // 0 = no match; for subtree mode, matched pid
  uint8_t done;
};

// Edge tuple for streaming subtree mode (host-side convenience)
struct EdgeItem {
  bloom_key_t pid;
  bloom_key_t ppid;
  bloom_key_t is_target; // nonzero = target node type (e.g. shell)
};

extern "C" {
void krnl_bloom(KeyPack *input, ResultPack *output, uint32_t num_keys,
                uint8_t mode);
}
