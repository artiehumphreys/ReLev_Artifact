#pragma once

#include <cstdint>
#include <hls_stream.h>

// IO burst sizes matching HBM 512-bit width
#define IO_READ_BURST 64
#define IO_WRITE_BURST 64

// CBF & BF parameters (must be power of 2)
#define BF_SIZE 8192
#define BF_NUM_HASHES 3
#define BF_NUM_BYTES (BF_SIZE / 8)

#define CBF_SIZE 8192
#define CBF_NUM_HASHES 3

// Number of uint32_t keys that can fit in one 64-byte HBM burst
#define KEYS_PER_BURST (IO_READ_BURST / 4) // 16

#define MODE_BF_CLEAR 0
#define MODE_BF_INSERT 1
#define MODE_BF_QUERY 2
#define MODE_CBF_CLEAR 3
#define MODE_CBF_INSERT 4
#define MODE_CBF_REMOVE 5
#define MODE_CBF_QUERY 6

// 16 keys x 4 bytes = 64 bytes (HBM bus width)
struct KeyPack {
  uint32_t keys[KEYS_PER_BURST];
};

struct ResultPack {
  uint8_t results[IO_WRITE_BURST];
};

struct KeyItem {
  uint32_t key;
  uint8_t done;
};

struct ResultItem {
  uint8_t result;
  uint8_t done;
};

extern "C" {
void krnl_bloom(KeyPack *input, ResultPack *output, uint32_t num_keys,
                uint8_t mode);
}
