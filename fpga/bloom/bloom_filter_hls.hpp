#pragma once

#include "hls_hash.hpp"
#include <cstdint>

// HLS-friendly Bloom filter helpers.
// UNROLL on the hash loop for parallel BRAM access
// INLINE so the caller's PIPELINE pragma governs scheduling

// HashType HT selects the hash function (default: xor-shift-multiply).

template <uint32_t SIZE, int NUM_HASHES, HashType HT = HASH_XOR_SHIFT>
void hls_bloom_insert(uint8_t bits[SIZE / 8], uint32_t key) {
#pragma HLS INLINE
  const uint32_t MASK = SIZE - 1;
  uint32_t h1 = hls_hash_dispatch<HT>(key, 0);
  uint32_t h2 = hls_hash_dispatch<HT>(key, h1);
  for (int i = 0; i < NUM_HASHES; i++) {
#pragma HLS UNROLL
    uint32_t idx = (h1 + static_cast<uint32_t>(i) * h2) & MASK;
    bits[idx >> 3] |= static_cast<uint8_t>(1u << (idx & 7));
  }
}

template <uint32_t SIZE, int NUM_HASHES, HashType HT = HASH_XOR_SHIFT>
bool hls_bloom_query(const uint8_t bits[SIZE / 8], uint32_t key) {
#pragma HLS INLINE
  const uint32_t MASK = SIZE - 1;
  uint32_t h1 = hls_hash_dispatch<HT>(key, 0);
  uint32_t h2 = hls_hash_dispatch<HT>(key, h1);
  bool found = true;
  for (int i = 0; i < NUM_HASHES; i++) {
#pragma HLS UNROLL
    uint32_t idx = (h1 + static_cast<uint32_t>(i) * h2) & MASK;
    if (!(bits[idx >> 3] & (1u << (idx & 7)))) {
      found = false;
    }
  }
  return found;
}

// Per-root helpers: operate on a 2D array bf[NR][SIZE/8].
// Caller partitions dim 1 complete so each root lives in its own BRAM bank
// and the unrolled loop hits all banks in parallel.

template <uint32_t NR, uint32_t SIZE, int NUM_HASHES,
          HashType HT = HASH_XOR_SHIFT>
uint64_t hls_bloom_query_all(const uint8_t bits[NR][SIZE / 8], uint32_t key) {
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
      if (!(bits[r][idx >> 3] & (1u << (idx & 7)))) {
        found = false;
      }
    }
    if (found)
      hits |= (static_cast<uint64_t>(1) << r);
  }
  return hits;
}

template <uint32_t NR, uint32_t SIZE, int NUM_HASHES,
          HashType HT = HASH_XOR_SHIFT>
void hls_bloom_insert_at(uint8_t bits[NR][SIZE / 8], uint32_t root,
                         uint32_t key) {
#pragma HLS INLINE
  hls_bloom_insert<SIZE, NUM_HASHES, HT>(bits[root], key);
}
