// g++ -std=c++17 -O2 -o bloom_fpr_test bloom_fpr_test.cpp

#include "bloom_filter_hls.hpp"
#include "counting_bloom_filter_hls.hpp"
#include "cuckoo_filter_hls.hpp"
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

static double theoretical_fpr(uint32_t m, int k, uint32_t n) {
  double e = -static_cast<double>(k) * n / m;
  return std::pow(1.0 - std::exp(e), k);
}

template <uint32_t SIZE, int NUM_HASHES, HashType HT>
static double measure_fpr(uint32_t num_insert, uint32_t num_query) {
  uint8_t bits[SIZE / 8];
  std::memset(bits, 0, sizeof(bits));
  std::mt19937 rng(42);
  std::uniform_int_distribution<uint32_t> dist;

  for (uint32_t i = 0; i < num_insert; i++)
    hls_bloom_insert<SIZE, NUM_HASHES, HT>(bits, dist(rng) | 1u);

  std::mt19937 qrng(0xDEADBEEF);
  uint32_t fp = 0;
  for (uint32_t i = 0; i < num_query; i++)
    if (hls_bloom_query<SIZE, NUM_HASHES, HT>(bits, dist(qrng) & ~1u))
      fp++;

  return static_cast<double>(fp) / num_query;
}

template <uint32_t SIZE, int NUM_HASHES, HashType HT>
static void run(const char *label, uint32_t n, uint32_t nq) {
  double emp = measure_fpr<SIZE, NUM_HASHES, HT>(n, nq);
  double thy = theoretical_fpr(SIZE, NUM_HASHES, n);
  std::cout << "  " << std::left << std::setw(15) << label
            << std::fixed << std::setprecision(6)
            << "  emp=" << emp << "  thy=" << thy << '\n';
}

template <uint32_t SIZE, int NUM_HASHES, HashType HT>
static bool check_no_fn(uint32_t n) {
  uint8_t bits[SIZE / 8];
  std::memset(bits, 0, sizeof(bits));
  std::mt19937 rng(123);
  std::uniform_int_distribution<uint32_t> dist;
  std::vector<uint32_t> keys(n);
  for (uint32_t i = 0; i < n; i++) {
    keys[i] = dist(rng);
    hls_bloom_insert<SIZE, NUM_HASHES, HT>(bits, keys[i]);
  }
  for (uint32_t i = 0; i < n; i++)
    if (!hls_bloom_query<SIZE, NUM_HASHES, HT>(bits, keys[i]))
      return false;
  return true;
}

template <uint32_t SIZE, int NUM_HASHES, HashType HT>
static double measure_cbf_fpr(uint32_t num_insert, uint32_t num_remove,
                              uint32_t num_query) {
  uint8_t counters[SIZE];
  std::memset(counters, 0, sizeof(counters));
  std::mt19937 rng(42);
  std::uniform_int_distribution<uint32_t> dist;

  std::vector<uint32_t> keys(num_insert);
  for (uint32_t i = 0; i < num_insert; i++) {
    keys[i] = dist(rng) | 1u;
    hls_cbf_insert<SIZE, NUM_HASHES, HT>(counters, keys[i]);
  }

  for (uint32_t i = 0; i < num_remove; i++)
    hls_cbf_remove<SIZE, NUM_HASHES, HT>(counters, keys[i]);

  std::mt19937 qrng(0xDEADBEEF);
  uint32_t fp = 0;
  for (uint32_t i = 0; i < num_query; i++)
    if (hls_cbf_query<SIZE, NUM_HASHES, HT>(counters, dist(qrng) & ~1u))
      fp++;

  return static_cast<double>(fp) / num_query;
}

template <uint32_t SIZE, int NUM_HASHES, HashType HT>
static void run_cbf(const char *label, uint32_t n, uint32_t rem, uint32_t nq) {
  double emp = measure_cbf_fpr<SIZE, NUM_HASHES, HT>(n, rem, nq);
  double thy = theoretical_fpr(SIZE, NUM_HASHES, n - rem);
  std::cout << "  " << std::left << std::setw(15) << label
            << std::fixed << std::setprecision(6)
            << "  emp=" << emp << "  thy=" << thy << '\n';
}

template <uint32_t NUM_BUCKETS, int SLOTS, HashType HT>
static double measure_cf_fpr(uint32_t num_insert, uint32_t num_query) {
  uint8_t table[NUM_BUCKETS * SLOTS];
  std::memset(table, 0, sizeof(table));
  std::mt19937 rng(42);
  std::uniform_int_distribution<uint32_t> dist;

  for (uint32_t i = 0; i < num_insert; i++)
    hls_cuckoo_insert<NUM_BUCKETS, SLOTS, HT>(table, dist(rng) | 1u);

  std::mt19937 qrng(0xDEADBEEF);
  uint32_t fp = 0;
  for (uint32_t i = 0; i < num_query; i++)
    if (hls_cuckoo_query<NUM_BUCKETS, SLOTS, HT>(table, dist(qrng) & ~1u))
      fp++;

  return static_cast<double>(fp) / num_query;
}

template <uint32_t NUM_BUCKETS, int SLOTS, HashType HT>
static void run_cf(const char *label, uint32_t n, uint32_t nq) {
  double emp = measure_cf_fpr<NUM_BUCKETS, SLOTS, HT>(n, nq);
  std::cout << "  " << std::left << std::setw(15) << label
            << std::fixed << std::setprecision(6)
            << "  emp=" << emp << '\n';
}

template <uint32_t NUM_BUCKETS, int SLOTS, HashType HT>
static double measure_cf_fpr_remove(uint32_t num_insert, uint32_t num_remove,
                                    uint32_t num_query) {
  uint8_t table[NUM_BUCKETS * SLOTS];
  std::memset(table, 0, sizeof(table));
  std::mt19937 rng(42);
  std::uniform_int_distribution<uint32_t> dist;

  std::vector<uint32_t> keys(num_insert);
  for (uint32_t i = 0; i < num_insert; i++) {
    keys[i] = dist(rng) | 1u;
    hls_cuckoo_insert<NUM_BUCKETS, SLOTS, HT>(table, keys[i]);
  }

  for (uint32_t i = 0; i < num_remove; i++)
    hls_cuckoo_remove<NUM_BUCKETS, SLOTS, HT>(table, keys[i]);

  std::mt19937 qrng(0xDEADBEEF);
  uint32_t fp = 0;
  for (uint32_t i = 0; i < num_query; i++)
    if (hls_cuckoo_query<NUM_BUCKETS, SLOTS, HT>(table, dist(qrng) & ~1u))
      fp++;

  return static_cast<double>(fp) / num_query;
}

template <uint32_t NUM_BUCKETS, int SLOTS, HashType HT>
static void run_cf_rem(const char *label, uint32_t n, uint32_t rem,
                       uint32_t nq) {
  double emp = measure_cf_fpr_remove<NUM_BUCKETS, SLOTS, HT>(n, rem, nq);
  std::cout << "  " << std::left << std::setw(15) << label
            << std::fixed << std::setprecision(6)
            << "  emp=" << emp << '\n';
}

template <uint32_t NUM_BUCKETS, int SLOTS, HashType HT>
static bool check_cf_no_fn(uint32_t n) {
  uint8_t table[NUM_BUCKETS * SLOTS];
  std::memset(table, 0, sizeof(table));
  std::mt19937 rng(123);
  std::uniform_int_distribution<uint32_t> dist;
  std::vector<uint32_t> keys(n);
  for (uint32_t i = 0; i < n; i++) {
    keys[i] = dist(rng);
    hls_cuckoo_insert<NUM_BUCKETS, SLOTS, HT>(table, keys[i]);
  }
  for (uint32_t i = 0; i < n; i++)
    if (!hls_cuckoo_query<NUM_BUCKETS, SLOTS, HT>(table, keys[i]))
      return false;
  return true;
}

int main() {
  constexpr uint32_t NQ = 100000;

  std::cout << "=== FPR (m=8192, k=3) ===\n";

  std::cout << "\nn=500:\n";
  run<8192, 3, HASH_XOR_SHIFT>("xor-shift-mul", 500, NQ);
  run<8192, 3, HASH_MURMUR3>("murmur3", 500, NQ);
  run<8192, 3, HASH_PIM>("pim (no mul)", 500, NQ);

  std::cout << "\nn=2000:\n";
  run<8192, 3, HASH_XOR_SHIFT>("xor-shift-mul", 2000, NQ);
  run<8192, 3, HASH_MURMUR3>("murmur3", 2000, NQ);
  run<8192, 3, HASH_PIM>("pim (no mul)", 2000, NQ);

  std::cout << "\nn=4000:\n";
  run<8192, 3, HASH_XOR_SHIFT>("xor-shift-mul", 4000, NQ);
  run<8192, 3, HASH_MURMUR3>("murmur3", 4000, NQ);
  run<8192, 3, HASH_PIM>("pim (no mul)", 4000, NQ);

  std::cout << "\n=== CBF insert/remove (m=8192, k=3) ===\n";

  std::cout << "\ninsert 4000, remove 2000 (2000 remain):\n";
  run_cbf<8192, 3, HASH_XOR_SHIFT>("xor-shift-mul", 4000, 2000, NQ);
  run_cbf<8192, 3, HASH_MURMUR3>("murmur3", 4000, 2000, NQ);
  run_cbf<8192, 3, HASH_PIM>("pim (no mul)", 4000, 2000, NQ);

  std::cout << "\ninsert 4000, remove 3500 (500 remain):\n";
  run_cbf<8192, 3, HASH_XOR_SHIFT>("xor-shift-mul", 4000, 3500, NQ);
  run_cbf<8192, 3, HASH_MURMUR3>("murmur3", 4000, 3500, NQ);
  run_cbf<8192, 3, HASH_PIM>("pim (no mul)", 4000, 3500, NQ);

  std::cout << "\ninsert 6000, remove 5000 (1000 remain):\n";
  run_cbf<8192, 3, HASH_XOR_SHIFT>("xor-shift-mul", 6000, 5000, NQ);
  run_cbf<8192, 3, HASH_MURMUR3>("murmur3", 6000, 5000, NQ);
  run_cbf<8192, 3, HASH_PIM>("pim (no mul)", 6000, 5000, NQ);

  // CF: 2048 buckets * 4 slots = 8192 entries, 8-bit fingerprints
  std::cout << "\n=== CF FPR (buckets=2048, slots=4) ===\n";

  std::cout << "\nn=500:\n";
  run_cf<2048, 4, HASH_XOR_SHIFT>("xor-shift-mul", 500, NQ);
  run_cf<2048, 4, HASH_MURMUR3>("murmur3", 500, NQ);
  run_cf<2048, 4, HASH_PIM>("pim (no mul)", 500, NQ);

  std::cout << "\nn=2000:\n";
  run_cf<2048, 4, HASH_XOR_SHIFT>("xor-shift-mul", 2000, NQ);
  run_cf<2048, 4, HASH_MURMUR3>("murmur3", 2000, NQ);
  run_cf<2048, 4, HASH_PIM>("pim (no mul)", 2000, NQ);

  std::cout << "\nn=4000:\n";
  run_cf<2048, 4, HASH_XOR_SHIFT>("xor-shift-mul", 4000, NQ);
  run_cf<2048, 4, HASH_MURMUR3>("murmur3", 4000, NQ);
  run_cf<2048, 4, HASH_PIM>("pim (no mul)", 4000, NQ);

  std::cout << "\n=== CF insert/remove (buckets=2048, slots=4) ===\n";

  std::cout << "\ninsert 4000, remove 2000 (2000 remain):\n";
  run_cf_rem<2048, 4, HASH_XOR_SHIFT>("xor-shift-mul", 4000, 2000, NQ);
  run_cf_rem<2048, 4, HASH_MURMUR3>("murmur3", 4000, 2000, NQ);
  run_cf_rem<2048, 4, HASH_PIM>("pim (no mul)", 4000, 2000, NQ);

  std::cout << "\ninsert 4000, remove 3500 (500 remain):\n";
  run_cf_rem<2048, 4, HASH_XOR_SHIFT>("xor-shift-mul", 4000, 3500, NQ);
  run_cf_rem<2048, 4, HASH_MURMUR3>("murmur3", 4000, 3500, NQ);
  run_cf_rem<2048, 4, HASH_PIM>("pim (no mul)", 4000, 3500, NQ);

  std::cout << "\ninsert 6000, remove 5000 (1000 remain):\n";
  run_cf_rem<2048, 4, HASH_XOR_SHIFT>("xor-shift-mul", 6000, 5000, NQ);
  run_cf_rem<2048, 4, HASH_MURMUR3>("murmur3", 6000, 5000, NQ);
  run_cf_rem<2048, 4, HASH_PIM>("pim (no mul)", 6000, 5000, NQ);

  std::cout << "\n=== No False Negatives (m=16384, k=3, n=1000) ===\n";
  std::cout << "  xor-shift-mul   " << (check_no_fn<16384, 3, HASH_XOR_SHIFT>(1000) ? "PASS" : "FAIL") << '\n';
  std::cout << "  murmur3         " << (check_no_fn<16384, 3, HASH_MURMUR3>(1000) ? "PASS" : "FAIL") << '\n';
  std::cout << "  pim (no mul)    " << (check_no_fn<16384, 3, HASH_PIM>(1000) ? "PASS" : "FAIL") << '\n';

  std::cout << "\n=== CF No False Negatives (buckets=2048, slots=4, n=1000) ===\n";
  std::cout << "  xor-shift-mul   " << (check_cf_no_fn<2048, 4, HASH_XOR_SHIFT>(1000) ? "PASS" : "FAIL") << '\n';
  std::cout << "  murmur3         " << (check_cf_no_fn<2048, 4, HASH_MURMUR3>(1000) ? "PASS" : "FAIL") << '\n';
  std::cout << "  pim (no mul)    " << (check_cf_no_fn<2048, 4, HASH_PIM>(1000) ? "PASS" : "FAIL") << '\n';

  return 0;
}
