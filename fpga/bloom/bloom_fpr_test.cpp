#include "bloom_filter_hls.hpp"
#include "counting_bloom_filter_hls.hpp"
#include "cuckoo_filter_hls.hpp"
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>

struct LCG {
  // linear congruential generator for a psuedorandom sequence
  uint32_t state;
  explicit LCG(uint32_t seed) : state(seed) {}
  uint32_t next() {
    // https://www.columbia.edu/~ks20/4106-18-Fall/Simulation-LCG.pdf
    state = state * 1664525u + 1013904223u;
    return state;
  }
  void reset(uint32_t seed) { state = seed; }
};

static constexpr uint32_t SEED = 0xBEEF;
static constexpr uint32_t NQ = 100000;

static double theoretical_fpr(uint32_t m, int k, uint32_t n) {
  double e = -static_cast<double>(k) * n / m;
  return std::pow(1.0 - std::exp(e), k);
}

static void print_row(const char *tag, uint32_t n, double emp,
                      double thy = -1.0) {
  std::cout << "    " << std::left << std::setw(22) << tag
            << "(n=" << std::setw(5) << std::right << n << "):" << std::fixed
            << std::setprecision(6) << "  emp=" << emp;
  if (thy >= 0.0)
    std::cout << "  thy=" << thy;
  std::cout << '\n';
}

template <uint32_t SIZE, int NUM_HASHES, HashType HT>
static void bloom_sawtooth(const char *label) {
  uint8_t bits[SIZE / 8];
  std::memset(bits, 0, sizeof(bits));
  LCG gen(SEED);

  int loads[] = {25, 50, 75, 95};
  uint32_t prev_n = 0;

  std::cout << "  " << label << ":\n";
  for (int pct : loads) {
    uint32_t n = static_cast<uint32_t>(pct / 100.0 * SIZE / NUM_HASHES);
    for (uint32_t i = prev_n; i < n; i++)
      hls_bloom_insert<SIZE, NUM_HASHES, HT>(bits, gen.next());

    uint32_t saved = gen.state;
    uint32_t fp = 0;
    for (uint32_t i = 0; i < NQ; i++)
      if (hls_bloom_query<SIZE, NUM_HASHES, HT>(bits, gen.next()))
        fp++;
    gen.state = saved;

    char tag[32];
    std::snprintf(tag, sizeof(tag), "%d%% load", pct);
    print_row(tag, n, static_cast<double>(fp) / NQ,
              theoretical_fpr(SIZE, NUM_HASHES, n));
    prev_n = n;
  }
  std::cout << '\n';
}

template <uint32_t SIZE, int NUM_HASHES, HashType HT>
static void cbf_sawtooth(const char *label) {
  uint8_t counters[SIZE];
  std::memset(counters, 0, sizeof(counters));
  LCG gen(SEED);

  int loads[] = {25, 50, 75, 95};
  uint32_t prev_n = 0;

  std::cout << "  " << label << ":\n";
  for (int pct : loads) {
    uint32_t n = static_cast<uint32_t>(pct / 100.0 * SIZE / NUM_HASHES);
    for (uint32_t i = prev_n; i < n; i++)
      hls_cbf_insert<SIZE, NUM_HASHES, HT>(counters, gen.next());

    uint32_t saved = gen.state;
    uint32_t fp = 0;
    for (uint32_t i = 0; i < NQ; i++)
      if (hls_cbf_query<SIZE, NUM_HASHES, HT>(counters, gen.next()))
        fp++;
    gen.state = saved;

    char tag[32];
    std::snprintf(tag, sizeof(tag), "%d%% load", pct);
    print_row(tag, n, static_cast<double>(fp) / NQ,
              theoretical_fpr(SIZE, NUM_HASHES, n));
    prev_n = n;
  }

  uint32_t n_peak = prev_n;
  uint32_t n_target = static_cast<uint32_t>(50 / 100.0 * SIZE / NUM_HASHES);
  uint32_t to_remove = n_peak - n_target;

  gen.reset(SEED);
  for (uint32_t i = 0; i < to_remove; i++)
    hls_cbf_remove<SIZE, NUM_HASHES, HT>(counters, gen.next());

  uint32_t fp = 0;
  for (uint32_t i = 0; i < NQ; i++)
    if (hls_cbf_query<SIZE, NUM_HASHES, HT>(counters, gen.next()))
      fp++;

  print_row("del to 50%", n_target, static_cast<double>(fp) / NQ,
            theoretical_fpr(SIZE, NUM_HASHES, n_target));

  gen.reset(SEED);
  for (uint32_t i = 0; i < to_remove; i++)
    gen.next();
  uint32_t fn = 0;
  for (uint32_t i = 0; i < n_target; i++)
    if (!hls_cbf_query<SIZE, NUM_HASHES, HT>(counters, gen.next()))
      fn++;
  std::cout << "    false negatives after del: " << fn << "/" << n_target
            << '\n' << '\n';
}

template <uint32_t NUM_BUCKETS, int SLOTS, HashType HT>
static void cuckoo_sawtooth(const char *label) {
  constexpr uint32_t CAP = NUM_BUCKETS * SLOTS;
  uint8_t table[CAP];
  std::memset(table, 0, sizeof(table));
  LCG gen(SEED);

  int loads[] = {25, 50, 75, 95};
  uint32_t prev_n = 0;

  std::cout << "  " << label << ":\n";
  for (int pct : loads) {
    uint32_t n = static_cast<uint32_t>(pct / 100.0 * CAP);
    for (uint32_t i = prev_n; i < n; i++)
      hls_cuckoo_insert<NUM_BUCKETS, SLOTS, HT>(table, gen.next());

    uint32_t saved = gen.state;
    uint32_t fp = 0;
    for (uint32_t i = 0; i < NQ; i++)
      if (hls_cuckoo_query<NUM_BUCKETS, SLOTS, HT>(table, gen.next()))
        fp++;
    gen.state = saved;

    char tag[32];
    std::snprintf(tag, sizeof(tag), "%d%% load", pct);
    print_row(tag, n, static_cast<double>(fp) / NQ);
    prev_n = n;
  }

  uint32_t n_peak = prev_n;
  uint32_t n_target = static_cast<uint32_t>(0.50 * CAP);
  uint32_t to_remove = n_peak - n_target;

  gen.reset(SEED);
  for (uint32_t i = 0; i < to_remove; i++)
    hls_cuckoo_remove<NUM_BUCKETS, SLOTS, HT>(table, gen.next());

  uint32_t fp = 0;
  for (uint32_t i = 0; i < NQ; i++)
    if (hls_cuckoo_query<NUM_BUCKETS, SLOTS, HT>(table, gen.next()))
      fp++;

  print_row("del to 50%", n_target, static_cast<double>(fp) / NQ);

  gen.reset(SEED);
  for (uint32_t i = 0; i < to_remove; i++)
    gen.next();
  uint32_t fn = 0;
  for (uint32_t i = 0; i < n_target; i++)
    if (!hls_cuckoo_query<NUM_BUCKETS, SLOTS, HT>(table, gen.next()))
      fn++;
  std::cout << "    false negatives after del: " << fn << "/" << n_target
            << '\n' << '\n';
}

int main() {
  std::cout << "=== Bloom Filter (m=16384, k=3) ===\n\n";
  bloom_sawtooth<16384, 3, HASH_XOR_SHIFT>("xor-shift-mul");
  bloom_sawtooth<16384, 3, HASH_MURMUR3>("murmur3");
  bloom_sawtooth<16384, 3, HASH_PIM>("pim (no mul)");

  std::cout << "=== Counting Bloom Filter (m=16384, k=3) ===\n\n";
  cbf_sawtooth<16384, 3, HASH_XOR_SHIFT>("xor-shift-mul");
  cbf_sawtooth<16384, 3, HASH_MURMUR3>("murmur3");
  cbf_sawtooth<16384, 3, HASH_PIM>("pim (no mul)");

  std::cout << "=== Cuckoo Filter (buckets=4096, slots=4) ===\n\n";
  cuckoo_sawtooth<4096, 4, HASH_XOR_SHIFT>("xor-shift-mul");
  cuckoo_sawtooth<4096, 4, HASH_MURMUR3>("murmur3");
  cuckoo_sawtooth<4096, 4, HASH_PIM>("pim (no mul)");

  return 0;
}
