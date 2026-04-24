#pragma once

#include <cstdint>

enum HashType {
  HASH_XOR_SHIFT = 0,
  HASH_MURMUR3 = 1,
  HASH_PIM = 2,
};

// XOR-shift multiply
inline uint32_t hls_hash_xorshift(uint32_t key, uint32_t seed) {
#pragma HLS INLINE
  uint32_t h = key ^ seed;
  h ^= h >> 16;
  h *= 0x45d9f3b;
  h ^= h >> 16;
  return h;
}

// MurmurHash3
inline uint32_t hls_hash_murmur3(uint32_t key, uint32_t seed) {
#pragma HLS INLINE
  uint32_t h = key ^ seed;
  h ^= h >> 16;
  h *= 0x85ebca6b;
  h ^= h >> 13;
  h *= 0xc2b2ae35;
  h ^= h >> 16;
  return h;
}

// PIM-friendly hash
inline uint32_t hls_hash_pim(uint32_t key, uint32_t seed) {
#pragma HLS INLINE
  uint32_t h = key ^ seed;
  h += h << 10;
  h ^= h >> 6;
  h += h << 3;
  h ^= h >> 11;
  h += h << 15;
  // second round for better avalanche on 32-bit input
  h ^= h >> 16;
  h += h << 5;
  h ^= h >> 12;
  return h;
}

// Compile-time dispatch by HashType template parameter.
template <HashType HT>
inline uint32_t hls_hash_dispatch(uint32_t key, uint32_t seed) {
#pragma HLS INLINE
  if (HT == HASH_MURMUR3)
    return hls_hash_murmur3(key, seed);
  if (HT == HASH_PIM)
    return hls_hash_pim(key, seed);
  return hls_hash_xorshift(key, seed);
}

// Backward-compatible alias: default to xor-shift-multiply.
inline uint32_t hls_hash(uint32_t key, uint32_t seed) {
#pragma HLS INLINE
  return hls_hash_xorshift(key, seed);
}
