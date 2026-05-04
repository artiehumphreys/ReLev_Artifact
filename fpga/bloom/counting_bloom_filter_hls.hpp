#pragma once

#include "hls_hash.hpp"
#include <cstdint>

// HLS-friendly Counting Bloom filter helpers.
// One uint8_t counter per slot, saturating at 0/255.
// Same double-hashing as the software version with HLS pragmas.

// HashType HT selects the hash function (default: xor-shift-multiply).

template <uint32_t SIZE, int NUM_HASHES, HashType HT = HASH_XOR_SHIFT>
void hls_cbf_insert(uint8_t counters[SIZE], uint32_t key) {
#pragma HLS INLINE
  const uint32_t MASK = SIZE - 1;
  uint32_t h1 = hls_hash_dispatch<HT>(key, 0);
  uint32_t h2 = hls_hash_dispatch<HT>(key, h1);
  for (int i = 0; i < NUM_HASHES; i++) {
#pragma HLS UNROLL
    uint32_t idx = (h1 + static_cast<uint32_t>(i) * h2) & MASK;
    if (counters[idx] < 255)
      counters[idx]++;
  }
}

template <uint32_t SIZE, int NUM_HASHES, HashType HT = HASH_XOR_SHIFT>
void hls_cbf_remove(uint8_t counters[SIZE], uint32_t key) {
#pragma HLS INLINE
  const uint32_t MASK = SIZE - 1;
  uint32_t h1 = hls_hash_dispatch<HT>(key, 0);
  uint32_t h2 = hls_hash_dispatch<HT>(key, h1);
  for (int i = 0; i < NUM_HASHES; i++) {
#pragma HLS UNROLL
    uint32_t idx = (h1 + static_cast<uint32_t>(i) * h2) & MASK;
    if (counters[idx] > 0)
      counters[idx]--;
  }
}

template <uint32_t SIZE, int NUM_HASHES, HashType HT = HASH_XOR_SHIFT>
bool hls_cbf_query(const uint8_t counters[SIZE], uint32_t key) {
#pragma HLS INLINE
  const uint32_t MASK = SIZE - 1;
  uint32_t h1 = hls_hash_dispatch<HT>(key, 0);
  uint32_t h2 = hls_hash_dispatch<HT>(key, h1);
  bool found = true;
  for (int i = 0; i < NUM_HASHES; i++) {
#pragma HLS UNROLL
    uint32_t idx = (h1 + static_cast<uint32_t>(i) * h2) & MASK;
    if (counters[idx] == 0)
      found = false;
  }
  return found;
}

// Per-root helpers: operate on a 2D array cbf[NR][SIZE].
// Caller partitions dim 1 complete so each root lives in its own BRAM bank.

template <uint32_t NR, uint32_t SIZE, int NUM_HASHES,
          HashType HT = HASH_XOR_SHIFT>
uint64_t hls_cbf_query_all(const uint8_t counters[NR][SIZE], uint32_t key) {
#pragma HLS INLINE
  const uint32_t MASK = SIZE - 1;
  uint32_t h1 = hls_hash_dispatch<HT>(key, 0);
  uint32_t h2 = hls_hash_dispatch<HT>(key, h1);
  uint64_t hits = 0;
  for (uint32_t r = 0; r < NR; r++) {
#pragma HLS UNROLL
    bool found = true;
    for (int i = 0; i < NUM_HASHES; i++) {
#pragma HLS UNROLL
      uint32_t idx = (h1 + static_cast<uint32_t>(i) * h2) & MASK;
      if (counters[r][idx] == 0)
        found = false;
    }
    if (found)
      hits |= (static_cast<uint64_t>(1) << r);
  }
  return hits;
}

template <uint32_t NR, uint32_t SIZE, int NUM_HASHES,
          HashType HT = HASH_XOR_SHIFT>
void hls_cbf_insert_at(uint8_t counters[NR][SIZE], uint32_t root,
                       uint32_t key) {
#pragma HLS INLINE
  hls_cbf_insert<SIZE, NUM_HASHES, HT>(counters[root], key);
}

template <uint32_t NR, uint32_t SIZE, int NUM_HASHES,
          HashType HT = HASH_XOR_SHIFT>
void hls_cbf_remove_at(uint8_t counters[NR][SIZE], uint32_t root,
                       uint32_t key) {
#pragma HLS INLINE
  hls_cbf_remove<SIZE, NUM_HASHES, HT>(counters[root], key);
}
