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

#include "krnl_automata.hpp"
#include "host/util.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

#define EDIT_DISTANCE (0b00000001) // Set edit distance to 1 for now

int main()
{

  // Grab the input filename
  std::string input_filename = "/home/tjt7a/src/ReLev_Artifact/input/chr1.txt.first250k";
  auto input = file2CharVector(input_filename);
  size_t fsize = input.size();
  std::cout << "Input file size: " << input.size() << std::endl;

  // Grab the pattern filename
  std::string pattern_filename = "/home/tjt7a/src/ReLev_Artifact/patterns/128guides.txt";
  auto patterns = read_patterns(pattern_filename);
  std::cout << "Read " << patterns.size() << " patterns." << std::endl;
  std::cout << "Using " << NUM_AUTOMATA << " patterns." << std::endl;
  assert(NUM_AUTOMATA <= patterns.size());

  // Create buffer for patterns and input
  int pattern_buffer_size = 32 * NUM_AUTOMATA;
  int PADDED_BUFFER_SIZE = (((int)fsize + (pattern_buffer_size)) / IO_READ_BURST) * IO_READ_BURST + IO_READ_BURST;
  std::cout << "Padded file size: " << PADDED_BUFFER_SIZE << std::endl;

  char *in_buffer = new char[PADDED_BUFFER_SIZE];
  std::cout << "Filling in buffer with 0s" << std::endl;
  memset(in_buffer, 0, sizeof(PADDED_BUFFER_SIZE));

  // Write patterns into beginning of input buffer
  for (int i = 0; i < NUM_AUTOMATA; i++)
  {
    for (int j = 0; j < 23; j++)
    {
      in_buffer[i * 32 + j] = patterns[i][j];
    }
    in_buffer[i * 32 + 31] = EDIT_DISTANCE; // Set edit distance to 1 for now
  }

  // Then write the genomic data after the patterns
  std::memcpy(in_buffer + (32 * NUM_AUTOMATA), input.data(), input.size());
  std::cout << "Finished reading file into buffer" << std::endl;

  // Write input buffer to FPGA global memory
  InputPack *bo_in = new InputPack[PADDED_BUFFER_SIZE / sizeof(InputPack)]();
  std::memcpy(bo_in, in_buffer, PADDED_BUFFER_SIZE);
  std::cout << "Finished allocating bo_in" << std::endl;

  char *out_buffer = new char[PADDED_BUFFER_SIZE];

  MatchPack *bo_out = new MatchPack[PADDED_BUFFER_SIZE / sizeof(InputPack)]();
  std::memcpy(bo_out, out_buffer, PADDED_BUFFER_SIZE);

  std::cout << "Running Kernel" << std::endl;

  // Start FPGA kernel
  krnl_automata(bo_in, bo_out, PADDED_BUFFER_SIZE);

  std::cout << "Done with Kernel" << std::endl;

  int j = 0;
  // Collecting results
  bool done = false;
  std::set<std::pair<int, int>> matches_set;

  // Read output buffer until we hit a packet with valid bit = 0, which indicates end of results
  while (!done)
  {
    MatchPack out = bo_out[j++];
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

    // Sort matches by position
    std::sort(matches_vec.begin(), matches_vec.end(), comp);

    // Write out results
    for (auto match : matches_vec)
    {
        std::cout << std::to_string(match.first) << ":" << std::to_string(match.second) << std::endl;
    }

  std::cout << "Test passed.\n";
  return EXIT_SUCCESS;
}
