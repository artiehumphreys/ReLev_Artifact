#pragma once

#include "hls_hash.hpp"
#include <cstdint>

// 0 = empty slot
static constexpr uint8_t CUCKOO_EMPTY = 0;

template <HashType HT> inline uint8_t cuckoo_fingerprint(uint32_t key) {
#pragma HLS INLINE
  uint8_t fp = static_cast<uint8_t>(hls_hash_dispatch<HT>(key, 0x9E3779B9));
  return fp + (fp == 0); // map 0 -> 1
}

template <uint32_t NUM_BUCKETS, HashType HT>
inline uint32_t cuckoo_index(uint32_t key) {
#pragma HLS INLINE
  return hls_hash_dispatch<HT>(key, 0) & (NUM_BUCKETS - 1);
}

template <uint32_t NUM_BUCKETS>
inline uint32_t cuckoo_alt_index(uint32_t i, uint8_t fp) {
#pragma HLS INLINE
  // partial-key cuckoo: i2 = i1 XOR hash(fp)
  // use a simple mix so fp=0 case never arises (already excluded)
  uint32_t h = fp;
  h ^= h << 5;
  h ^= h >> 3;
  return (i ^ h) & (NUM_BUCKETS - 1);
}

template <uint32_t NUM_BUCKETS, int SLOTS, HashType HT = HASH_XOR_SHIFT,
          int MAX_KICKS = 100>
bool hls_cuckoo_insert(uint8_t table[NUM_BUCKETS * SLOTS], uint32_t key) {
#pragma HLS INLINE off
  static_assert((NUM_BUCKETS & (NUM_BUCKETS - 1)) == 0,
                "NUM_BUCKETS must be power of 2");

  uint8_t fp = cuckoo_fingerprint<HT>(key);
  uint32_t i1 = cuckoo_index<NUM_BUCKETS, HT>(key);
  uint32_t i2 = cuckoo_alt_index<NUM_BUCKETS>(i1, fp);

  // try both buckets
  for (int s = 0; s < SLOTS; s++) {
#pragma HLS UNROLL
    if (table[i1 * SLOTS + s] == CUCKOO_EMPTY) {
      table[i1 * SLOTS + s] = fp;
      return true;
    }
  }
  for (int s = 0; s < SLOTS; s++) {
#pragma HLS UNROLL
    if (table[i2 * SLOTS + s] == CUCKOO_EMPTY) {
      table[i2 * SLOTS + s] = fp;
      return true;
    }
  }

  // eviction loop
  uint32_t i = i1;
  for (int kick = 0; kick < MAX_KICKS; kick++) {
    int slot = kick % SLOTS;
    uint8_t evicted = table[i * SLOTS + slot];
    table[i * SLOTS + slot] = fp;
    fp = evicted;
    i = cuckoo_alt_index<NUM_BUCKETS>(i, fp);

    for (int s = 0; s < SLOTS; s++) {
#pragma HLS UNROLL
      if (table[i * SLOTS + s] == CUCKOO_EMPTY) {
        table[i * SLOTS + s] = fp;
        return true;
      }
    }
  }

  return false; // table full
}

template <uint32_t NUM_BUCKETS, int SLOTS, HashType HT = HASH_XOR_SHIFT>
bool hls_cuckoo_query(const uint8_t table[NUM_BUCKETS * SLOTS], uint32_t key) {
#pragma HLS INLINE
  uint8_t fp = cuckoo_fingerprint<HT>(key);
  uint32_t i1 = cuckoo_index<NUM_BUCKETS, HT>(key);
  uint32_t i2 = cuckoo_alt_index<NUM_BUCKETS>(i1, fp);

  for (int s = 0; s < SLOTS; s++) {
#pragma HLS UNROLL
    if (table[i1 * SLOTS + s] == fp)
      return true;
    if (table[i2 * SLOTS + s] == fp)
      return true;
  }
  return false;
}

template <uint32_t NUM_BUCKETS, int SLOTS, HashType HT = HASH_XOR_SHIFT>
bool hls_cuckoo_remove(uint8_t table[NUM_BUCKETS * SLOTS], uint32_t key) {
#pragma HLS INLINE
  uint8_t fp = cuckoo_fingerprint<HT>(key);
  uint32_t i1 = cuckoo_index<NUM_BUCKETS, HT>(key);
  uint32_t i2 = cuckoo_alt_index<NUM_BUCKETS>(i1, fp);

  for (int s = 0; s < SLOTS; s++) {
#pragma HLS UNROLL
    if (table[i1 * SLOTS + s] == fp) {
      table[i1 * SLOTS + s] = CUCKOO_EMPTY;
      return true;
    }
  }
  for (int s = 0; s < SLOTS; s++) {
#pragma HLS UNROLL
    if (table[i2 * SLOTS + s] == fp) {
      table[i2 * SLOTS + s] = CUCKOO_EMPTY;
      return true;
    }
  }
  return false;
}

// Per-root helpers: operate on tables[NR][NUM_BUCKETS * SLOTS].
// Caller partitions dim 1 complete so each root lives in its own BRAM bank.

template <uint32_t NR, uint32_t NUM_BUCKETS, int SLOTS,
          HashType HT = HASH_XOR_SHIFT>
uint64_t hls_cuckoo_query_all(const uint8_t tables[NR][NUM_BUCKETS * SLOTS],
                              uint32_t key) {
#pragma HLS INLINE
  uint8_t fp = cuckoo_fingerprint<HT>(key);
  uint32_t i1 = cuckoo_index<NUM_BUCKETS, HT>(key);
  uint32_t i2 = cuckoo_alt_index<NUM_BUCKETS>(i1, fp);
  uint64_t hits = 0;
  for (uint32_t r = 0; r < NR; r++) {
#pragma HLS UNROLL
    bool found = false;
    for (int s = 0; s < SLOTS; s++) {
#pragma HLS UNROLL
      if (tables[r][i1 * SLOTS + s] == fp)
        found = true;
      if (tables[r][i2 * SLOTS + s] == fp)
        found = true;
    }
    if (found)
      hits |= (static_cast<uint64_t>(1) << r);
  }
  return hits;
}

template <uint32_t NR, uint32_t NUM_BUCKETS, int SLOTS,
          HashType HT = HASH_XOR_SHIFT, int MAX_KICKS = 100>
bool hls_cuckoo_insert_at(uint8_t tables[NR][NUM_BUCKETS * SLOTS],
                          uint32_t root, uint32_t key) {
#pragma HLS INLINE
  return hls_cuckoo_insert<NUM_BUCKETS, SLOTS, HT, MAX_KICKS>(tables[root],
                                                              key);
}

template <uint32_t NR, uint32_t NUM_BUCKETS, int SLOTS,
          HashType HT = HASH_XOR_SHIFT>
bool hls_cuckoo_remove_at(uint8_t tables[NR][NUM_BUCKETS * SLOTS],
                          uint32_t root, uint32_t key) {
#pragma HLS INLINE
  return hls_cuckoo_remove<NUM_BUCKETS, SLOTS, HT>(tables[root], key);
}
