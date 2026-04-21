#pragma once

#include <cstdint>
#include <hls_stream.h>

// Key width: compile with -DKEY_BITS=16 or -DKEY_BITS=32
#ifndef KEY_BITS
#define KEY_BITS 32
#endif

#if KEY_BITS == 16
typedef uint16_t key_t;
#define KEYS_PER_BURST 32  // 64 / 2
#define TUPLES_PER_BURST 10 // 64 / (3*2)
#elif KEY_BITS == 32
typedef uint32_t key_t;
#define KEYS_PER_BURST 16  // 64 / 4
#define TUPLES_PER_BURST 5 // 64 / (3*4)
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
#define MODE_BF_SUBTREE 7

struct KeyPack {
  key_t keys[KEYS_PER_BURST];
};

struct ResultPack {
  uint8_t results[IO_WRITE_BURST];
};

struct KeyItem {
  key_t key;
  uint8_t done;
};

struct ResultItem {
  uint8_t result;
  uint8_t done;
};

// Edge tuple for streaming subtree mode (host-side convenience)
struct EdgeItem {
  key_t pid;
  key_t ppid;
  key_t is_target; // nonzero = target node type (e.g. shell)
};

extern "C" {
void krnl_bloom(KeyPack *input, ResultPack *output, uint32_t num_keys,
                uint8_t mode);
}
