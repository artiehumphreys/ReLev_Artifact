/*************************************************************************
MIT License

Copyright (c) 2025 Tommy Tracy II, University of Virginia

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
**************************************************************************/

#include <iostream>
#include <cstring>
#include <chrono>
#include <thread>
#include "util.h"
#include "../krnl_automata.hpp"
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

// XRT includes
#include "experimental/xrt_bo.h"
#include "experimental/xrt_device.h"
#include "experimental/xrt_kernel.h"

int main(int argc, char **argv)
{

    // We're expecting 5 arguments XCLBIN and INPUT
    if (argc != 5)
    {
        std::cout << "Usage: " << argv[0] << " <XCLBIN File> <INPUT File> <Pattern File> <Edit Distance (0-6)>" << std::endl;
        return EXIT_FAILURE;
    }

    // Read xlcbin argument
    std::string binaryFile = argv[1];
    int device_index = 0;

    // Load the xclbin
    std::cout << "Open the device" << device_index << std::endl;
    auto device = xrt::device(device_index);
    std::cout << "Load the xclbin " << binaryFile << std::endl;
    auto uuid = device.load_xclbin(binaryFile);

    // Load the kernel and instantiate input and output buffers
    xrt::kernel krnl = xrt::kernel(device, uuid, "krnl_automata");

    // Grab the input filename
    std::string input_filename = argv[2];
    auto input = file2CharVector(input_filename);
    size_t fsize = input.size();
    std::cout << "Input file size: " << input.size() << std::endl;

    // Grab the pattern filename
    std::string pattern_filename = argv[3];
    auto patterns = read_patterns(pattern_filename);
    std::cout << "Read " << patterns.size() << " patterns." << std::endl;
    std::cout << "Using " << NUM_AUTOMATA << " patterns." << std::endl;

    assert(NUM_AUTOMATA <= patterns.size());

    // For now, we're only going to accept a single byte as the edit distance
    char edit_distance = edit_distance_byte(atoi(argv[4]));

    // We're going to represent each pattern with 32 bytes for now
    int pattern_buffer_size = 32 * NUM_AUTOMATA;

    // Find nearest multiple of IO_READ_BURST > fsize
    int PADDED_BUFFER_SIZE = (((int)fsize + (pattern_buffer_size)) / IO_READ_BURST) * IO_READ_BURST + IO_READ_BURST;
    std::cout << "Padded file size: " << PADDED_BUFFER_SIZE << std::endl;

    // For now, lets just read it all into host DRAM
    char *in_buffer;
    if (posix_memalign((void **)&in_buffer, 4096, PADDED_BUFFER_SIZE))
    {
        std::cout << "Failed to memalign in_buffer" << std::endl;
        return -1;
    }
    std::cout << "Filling in buffer with 0s" << std::endl;
    memset(in_buffer, 0, sizeof(PADDED_BUFFER_SIZE));

    // Populate patterns
    for (int i = 0; i < NUM_AUTOMATA; i++)
    {
        for (int j = 0; j < 23; j++)
        {
            in_buffer[i * 32 + j] = patterns[i][j];
        }
        // Populate edit distance
        in_buffer[i * 32 + 31] = edit_distance; // Set last byte of LEV config to edit distance
    }

    std::memcpy(in_buffer + (32 * NUM_AUTOMATA), input.data(), input.size());
    std::cout << "Finished reading file into buffer" << std::endl;

    std::cout << "Allocating buffer" << std::endl;
    xrt::bo bo_in = xrt::bo(device, PADDED_BUFFER_SIZE, krnl.group_id(0));
    std::cout << "Filling host in buffer" << std::endl;
    bo_in.write(in_buffer); // contents of the file
    std::cout << "Finished allocating bo_in" << std::endl;

    char *out_buffer;
    if (posix_memalign((void **)&out_buffer, 4096, PADDED_BUFFER_SIZE))
    {
        std::cout << "Failed to memalign out_buffer" << std::endl;
        return -1;
    }

    std::cout << "Filling out buffer with 0s" << std::endl;
    memset(out_buffer, 0, sizeof(PADDED_BUFFER_SIZE));

    std::cout << "Allocating buffer" << std::endl;
    xrt::bo bo_out = xrt::bo(device, PADDED_BUFFER_SIZE, krnl.group_id(1));
    std::cout << "Finished allocating bo_out" << std::endl;
    std::cout << "Filling host out buffer" << std::endl;
    bo_out.write(out_buffer); // zeroes

    MatchPack *bo_out_map = bo_out.map<MatchPack *>();

    std::cout << "Time to start the clock" << std::endl;

    // memcpy into the maps
    std::cout << "Running Kernel" << std::endl;

// Start the clock
#ifndef KERNEL
    std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();
#endif

    // Send input and output to FPGA
    bo_in.sync(XCL_BO_SYNC_BO_TO_DEVICE);

#ifdef KERNEL
    std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();
#endif

    auto run = krnl(bo_in, bo_out, PADDED_BUFFER_SIZE);
    // Wait on response
    run.wait();

#ifdef KERNEL
    std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();
#endif

    //  Send results back
    bo_out.sync(XCL_BO_SYNC_BO_FROM_DEVICE);

#ifndef KERNEL
    std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();
#endif

    std::cout << "Done with Kernel" << std::endl;

    // Walk through the output buffer and read match data
    int j = 0;
    int num_matches = 0;
    bool done = false;

    // We'll use a std::set to enforce uniqueness
    std::set<std::pair<int, int>> matches_set;

    while (!done)
    {
        MatchPack out = bo_out_map[j++];
        Match result;

        for (int k = 0; k < OUTPUT_PACKETSIZE; k++)
        {

            Match m = out.matches[k];
            if (m.valid)
            {
                if (m.ridPlusOne)
                {
                    std::vector<int> indexes = getIndexes(m.ragg_id, m.ridPlusOne);
                    for (int id : indexes)
                    {
                        matches_set.insert({m.pos, id});
                    }
                }
            }
            else
            {
                done = true;
                break;
            }
        }
    }

    std::vector<std::pair<int, int>> matches_vec;
    matches_vec.assign(matches_set.begin(), matches_set.end());

    auto comp = [](std::pair<int, int> a, std::pair<int, int> b)
    {
        return a.first < b.first;
    };

    std::sort(matches_vec.begin(), matches_vec.end(), comp);

    for (auto match : matches_vec)
    {
        std::cout << "Match " << std::to_string(match.first) << " for " << std::to_string(match.second) << std::endl;
    }

    // Clean up buffers
    free(out_buffer);
    free(in_buffer);

    // Compute duration between start and end
    double duration = std::chrono::duration<double, std::milli>(end_time - start_time).count();

    // Summarize results to std::out
    std::cout << "Automata Processing Time: " << duration << " ms" << std::endl
              << std::endl;
    std::cout << "To process " << PADDED_BUFFER_SIZE << " bytes" << std::endl;
    std::cout << "Throughput: " << (PADDED_BUFFER_SIZE / 1000) / (duration) << " MB/s" << std::endl;

    return 0;
}
