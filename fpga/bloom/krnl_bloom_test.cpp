#include <iostream>
#include <cstring>
#include <cstdlib>
#include "krnl_bloom.hpp"

int main()
{
    const int NUM_TEST_KEYS = 32;
    const int NUM_INPUT_BURSTS = (NUM_TEST_KEYS + KEYS_PER_BURST - 1) / KEYS_PER_BURST;
    const int NUM_OUTPUT_PACKS = (NUM_TEST_KEYS + IO_WRITE_BURST - 1) / IO_WRITE_BURST;

    KeyPack input[NUM_INPUT_BURSTS];
    ResultPack output[NUM_OUTPUT_PACKS];

    memset(input, 0, sizeof(input));
    memset(output, 0, sizeof(output));

    // Fill with test keys: 100, 200, 300, ..., 3200
    for (int i = 0; i < NUM_TEST_KEYS; i++)
    {
        input[i / KEYS_PER_BURST].keys[i % KEYS_PER_BURST] = (i + 1) * 100;
    }

    // --- Test Standard Bloom Filter ---
    std::cout << "=== Standard Bloom Filter Test ===" << std::endl;

    // Clear
    krnl_bloom(input, output, NUM_TEST_KEYS, MODE_BF_CLEAR);
    std::cout << "BF Clear: OK" << std::endl;

    // Insert
    krnl_bloom(input, output, NUM_TEST_KEYS, MODE_BF_INSERT);
    std::cout << "BF Insert: OK" << std::endl;

    // Query inserted keys (should all be FOUND)
    memset(output, 0, sizeof(output));
    krnl_bloom(input, output, NUM_TEST_KEYS, MODE_BF_QUERY);

    int bf_hits = 0;
    for (int i = 0; i < NUM_TEST_KEYS; i++)
    {
        uint8_t result = output[i / IO_WRITE_BURST].results[i % IO_WRITE_BURST];
        if (result)
            bf_hits++;
    }
    std::cout << "BF Query (inserted): " << bf_hits << "/" << NUM_TEST_KEYS << " found" << std::endl;
    if (bf_hits != NUM_TEST_KEYS)
    {
        std::cerr << "FAIL: Expected all inserted keys to be found!" << std::endl;
        return EXIT_FAILURE;
    }

    // Query keys NOT inserted (should mostly be NOT FOUND)
    KeyPack input_miss[NUM_INPUT_BURSTS];
    memset(input_miss, 0, sizeof(input_miss));
    for (int i = 0; i < NUM_TEST_KEYS; i++)
    {
        input_miss[i / KEYS_PER_BURST].keys[i % KEYS_PER_BURST] = (i + 1) * 100 + 7;
    }

    memset(output, 0, sizeof(output));
    krnl_bloom(input_miss, output, NUM_TEST_KEYS, MODE_BF_QUERY);

    int bf_false_pos = 0;
    for (int i = 0; i < NUM_TEST_KEYS; i++)
    {
        uint8_t result = output[i / IO_WRITE_BURST].results[i % IO_WRITE_BURST];
        if (result)
            bf_false_pos++;
    }
    std::cout << "BF Query (not inserted): " << bf_false_pos << "/" << NUM_TEST_KEYS << " false positives" << std::endl;

    // --- Test Counting Bloom Filter ---
    std::cout << "\n=== Counting Bloom Filter Test ===" << std::endl;

    // Clear
    krnl_bloom(input, output, NUM_TEST_KEYS, MODE_CBF_CLEAR);
    std::cout << "CBF Clear: OK" << std::endl;

    // Insert
    krnl_bloom(input, output, NUM_TEST_KEYS, MODE_CBF_INSERT);
    std::cout << "CBF Insert: OK" << std::endl;

    // Query inserted keys
    memset(output, 0, sizeof(output));
    krnl_bloom(input, output, NUM_TEST_KEYS, MODE_CBF_QUERY);

    int cbf_hits = 0;
    for (int i = 0; i < NUM_TEST_KEYS; i++)
    {
        uint8_t result = output[i / IO_WRITE_BURST].results[i % IO_WRITE_BURST];
        if (result)
            cbf_hits++;
    }
    std::cout << "CBF Query (inserted): " << cbf_hits << "/" << NUM_TEST_KEYS << " found" << std::endl;
    if (cbf_hits != NUM_TEST_KEYS)
    {
        std::cerr << "FAIL: Expected all inserted keys to be found!" << std::endl;
        return EXIT_FAILURE;
    }

    // Remove keys
    krnl_bloom(input, output, NUM_TEST_KEYS, MODE_CBF_REMOVE);
    std::cout << "CBF Remove: OK" << std::endl;

    // Query after removal (should be NOT FOUND)
    memset(output, 0, sizeof(output));
    krnl_bloom(input, output, NUM_TEST_KEYS, MODE_CBF_QUERY);

    int cbf_after_remove = 0;
    for (int i = 0; i < NUM_TEST_KEYS; i++)
    {
        uint8_t result = output[i / IO_WRITE_BURST].results[i % IO_WRITE_BURST];
        if (result)
            cbf_after_remove++;
    }
    std::cout << "CBF Query (after remove): " << cbf_after_remove << "/" << NUM_TEST_KEYS << " found" << std::endl;
    if (cbf_after_remove != 0)
    {
        std::cerr << "FAIL: Expected no keys after removal!" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "\n=== All tests passed ===" << std::endl;
    return EXIT_SUCCESS;
}
