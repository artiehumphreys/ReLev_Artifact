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

#include "automata_single_file.hpp"

#define PRINTF (0)

void automata_0::configure(uint8_t config_symbol, uint8_t config_addr, uint8_t pattern_id)
{
#pragma HLS FUNCTION_INSTANTIATE variable = pattern_id
#pragma HLS pipeline II = 1

	symbolset[config_addr] = config_symbol;
}

void automata_0::set_lev_distance(ap_uint<8> lev_d)
{
#pragma HLS pipeline II = 1
	lev_distance = lev_d;
}

void automata_0::print_symbolset(uint8_t pattern_id)
{
#pragma HLS FUNCTION_INSTANTIATE variable = pattern_id

	for (int i = 0; i < 23; i++)
	{
		std::cout << symbolset[i];
	}
	std::cout << std::endl
			  << std::flush;
}

void automata_0::print_lev_distance(uint8_t pattern_id)
{
#pragma HLS FUNCTION_INSTANTIATE variable = pattern_id	

	std::cout << (lev_distance[0] == 1) << (lev_distance[1] == 1) << (lev_distance[2] == 1) << (lev_distance[3] == 1)
			  << (lev_distance[4] == 1) << (lev_distance[5] == 1) << (lev_distance[6] == 1) << (lev_distance[7] == 1)
			  << std::endl
			  << std::flush;
}

void automata_0::print_state(uint8_t pattern_id)
{
#pragma HLS FUNCTION_INSTANTIATE variable = pattern_id
	// Print top-most line
	std::cout << (ste_0_match_1_6_enable == 1) << (ste_0_match_2_6_enable == 1) << (ste_0_match_3_6_enable == 1) << (ste_0_match_4_6_enable == 1)
			  << (ste_0_match_5_6_enable == 1) << (ste_0_match_6_6_enable == 1) << (ste_0_match_7_6_enable == 1) << (ste_0_match_8_6_enable == 1)
			  << (ste_0_match_9_6_enable == 1) << (ste_0_match_10_6_enable == 1) << (ste_0_match_11_6_enable == 1) << (ste_0_match_12_6_enable == 1)
			  << (ste_0_match_13_6_enable == 1) << (ste_0_match_14_6_enable == 1) << (ste_0_match_15_6_enable == 1) << (ste_0_match_16_6_enable == 1)
			  << (ste_0_match_17_6_enable == 1) << (ste_0_match_18_6_enable == 1) << (ste_0_match_19_6_enable == 1) << (ste_0_match_20_6_enable == 1)
			  << (ste_0_match_21_6_enable == 1) << (ste_0_match_22_6_enable == 1) << (ste_0_match_23_6_enable == 1)
			  << std::endl;
	std::cout << (ste_0_match_1_5_enable == 1) << (ste_0_match_2_5_enable == 1) << (ste_0_match_3_5_enable == 1) << (ste_0_match_4_5_enable == 1)
			  << (ste_0_match_5_5_enable == 1) << (ste_0_match_6_5_enable == 1) << (ste_0_match_7_5_enable == 1) << (ste_0_match_8_5_enable == 1)
			  << (ste_0_match_9_5_enable == 1) << (ste_0_match_10_5_enable == 1) << (ste_0_match_11_5_enable == 1) << (ste_0_match_12_5_enable == 1)
			  << (ste_0_match_13_5_enable == 1) << (ste_0_match_14_5_enable == 1) << (ste_0_match_15_5_enable == 1) << (ste_0_match_16_5_enable == 1)
			  << (ste_0_match_17_5_enable == 1) << (ste_0_match_18_5_enable == 1) << (ste_0_match_19_5_enable == 1) << (ste_0_match_20_5_enable == 1)
			  << (ste_0_match_21_5_enable == 1) << (ste_0_match_22_5_enable == 1) << (ste_0_match_23_5_enable == 1)
			  << std::endl;
	std::cout << (ste_0_match_1_4_enable == 1) << (ste_0_match_2_4_enable == 1) << (ste_0_match_3_4_enable == 1) << (ste_0_match_4_4_enable == 1)
			  << (ste_0_match_5_4_enable == 1) << (ste_0_match_6_4_enable == 1) << (ste_0_match_7_4_enable == 1) << (ste_0_match_8_4_enable == 1)
			  << (ste_0_match_9_4_enable == 1) << (ste_0_match_10_4_enable == 1) << (ste_0_match_11_4_enable == 1) << (ste_0_match_12_4_enable == 1)
			  << (ste_0_match_13_4_enable == 1) << (ste_0_match_14_4_enable == 1) << (ste_0_match_15_4_enable == 1) << (ste_0_match_16_4_enable == 1)
			  << (ste_0_match_17_4_enable == 1) << (ste_0_match_18_4_enable == 1) << (ste_0_match_19_4_enable == 1) << (ste_0_match_20_4_enable == 1)
			  << (ste_0_match_21_4_enable == 1) << (ste_0_match_22_4_enable == 1) << (ste_0_match_23_4_enable == 1)
			  << std::endl;
	std::cout << (ste_0_match_1_3_enable == 1) << (ste_0_match_2_3_enable == 1) << (ste_0_match_3_3_enable == 1) << (ste_0_match_4_3_enable == 1)
			  << (ste_0_match_5_3_enable == 1) << (ste_0_match_6_3_enable == 1) << (ste_0_match_7_3_enable == 1) << (ste_0_match_8_3_enable == 1)
			  << (ste_0_match_9_3_enable == 1) << (ste_0_match_10_3_enable == 1) << (ste_0_match_11_3_enable == 1) << (ste_0_match_12_3_enable == 1)
			  << (ste_0_match_13_3_enable == 1) << (ste_0_match_14_3_enable == 1) << (ste_0_match_15_3_enable == 1) << (ste_0_match_16_3_enable == 1)
			  << (ste_0_match_17_3_enable == 1) << (ste_0_match_18_3_enable == 1) << (ste_0_match_19_3_enable == 1) << (ste_0_match_20_3_enable == 1)
			  << (ste_0_match_21_3_enable == 1) << (ste_0_match_22_3_enable == 1) << (ste_0_match_23_3_enable == 1)
			  << std::endl;
	std::cout << (ste_0_match_1_2_enable == 1) << (ste_0_match_2_2_enable == 1) << (ste_0_match_3_2_enable == 1) << (ste_0_match_4_2_enable == 1)
			  << (ste_0_match_5_2_enable == 1) << (ste_0_match_6_2_enable == 1) << (ste_0_match_7_2_enable == 1) << (ste_0_match_8_2_enable == 1)
			  << (ste_0_match_9_2_enable == 1) << (ste_0_match_10_2_enable == 1) << (ste_0_match_11_2_enable == 1) << (ste_0_match_12_2_enable == 1)
			  << (ste_0_match_13_2_enable == 1) << (ste_0_match_14_2_enable == 1) << (ste_0_match_15_2_enable == 1) << (ste_0_match_16_2_enable == 1)
			  << (ste_0_match_17_2_enable == 1) << (ste_0_match_18_2_enable == 1) << (ste_0_match_19_2_enable == 1) << (ste_0_match_20_2_enable == 1)
			  << (ste_0_match_21_2_enable == 1) << (ste_0_match_22_2_enable == 1) << (ste_0_match_23_2_enable == 1)
			  << std::endl;
	std::cout << (ste_0_match_1_1_enable == 1) << (ste_0_match_2_1_enable == 1) << (ste_0_match_3_1_enable == 1) << (ste_0_match_4_1_enable == 1)
			  << (ste_0_match_5_1_enable == 1) << (ste_0_match_6_1_enable == 1) << (ste_0_match_7_1_enable == 1) << (ste_0_match_8_1_enable == 1)
			  << (ste_0_match_9_1_enable == 1) << (ste_0_match_10_1_enable == 1) << (ste_0_match_11_1_enable == 1) << (ste_0_match_12_1_enable == 1)
			  << (ste_0_match_13_1_enable == 1) << (ste_0_match_14_1_enable == 1) << (ste_0_match_15_1_enable == 1) << (ste_0_match_16_1_enable == 1)
			  << (ste_0_match_17_1_enable == 1) << (ste_0_match_18_1_enable == 1) << (ste_0_match_19_1_enable == 1) << (ste_0_match_20_1_enable == 1)
			  << (ste_0_match_21_1_enable == 1) << (ste_0_match_22_1_enable == 1) << (ste_0_match_23_1_enable == 1)
			  << std::endl;
	std::cout << (ste_0_match_1_0_enable == 1) << (ste_0_match_2_0_enable == 1) << (ste_0_match_3_0_enable == 1) << (ste_0_match_4_0_enable == 1)
			  << (ste_0_match_5_0_enable == 1) << (ste_0_match_6_0_enable == 1) << (ste_0_match_7_0_enable == 1) << (ste_0_match_8_0_enable == 1)
			  << (ste_0_match_9_0_enable == 1) << (ste_0_match_10_0_enable == 1) << (ste_0_match_11_0_enable == 1) << (ste_0_match_12_0_enable == 1)
			  << (ste_0_match_13_0_enable == 1) << (ste_0_match_14_0_enable == 1) << (ste_0_match_15_0_enable == 1) << (ste_0_match_16_0_enable == 1)
			  << (ste_0_match_17_0_enable == 1) << (ste_0_match_18_0_enable == 1) << (ste_0_match_19_0_enable == 1) << (ste_0_match_20_0_enable == 1)
			  << (ste_0_match_21_0_enable == 1) << (ste_0_match_22_0_enable == 1) << (ste_0_match_23_0_enable == 1)
			  << std::endl << std::flush;
}

void automata_0::reset(uint8_t pattern_id)
{
#pragma HLS FUNCTION_INSTANTIATE variable = pattern_id

	input_r = 0;
	ste_0_match_1_0_enable = 0;
	ste_0_match_1_1_enable = 0;
	ste_0_match_1_2_enable = 0;
	ste_0_match_1_3_enable = 0;
	ste_0_match_1_4_enable = 0;
	ste_0_match_1_5_enable = 0;
	ste_0_match_1_6_enable = 0;
	ste_0_match_2_0_enable = 0;
	ste_0_match_2_1_enable = 0;
	ste_0_match_2_2_enable = 0;
	ste_0_match_2_3_enable = 0;
	ste_0_match_2_4_enable = 0;
	ste_0_match_2_5_enable = 0;
	ste_0_match_2_6_enable = 0;
	ste_0_match_3_0_enable = 0;
	ste_0_match_3_1_enable = 0;
	ste_0_match_3_2_enable = 0;
	ste_0_match_3_3_enable = 0;
	ste_0_match_3_4_enable = 0;
	ste_0_match_3_5_enable = 0;
	ste_0_match_3_6_enable = 0;
	ste_0_match_4_0_enable = 0;
	ste_0_match_4_1_enable = 0;
	ste_0_match_4_2_enable = 0;
	ste_0_match_4_3_enable = 0;
	ste_0_match_4_4_enable = 0;
	ste_0_match_4_5_enable = 0;
	ste_0_match_4_6_enable = 0;
	ste_0_match_5_0_enable = 0;
	ste_0_match_5_1_enable = 0;
	ste_0_match_5_2_enable = 0;
	ste_0_match_5_3_enable = 0;
	ste_0_match_5_4_enable = 0;
	ste_0_match_5_5_enable = 0;
	ste_0_match_5_6_enable = 0;
	ste_0_match_6_0_enable = 0;
	ste_0_match_6_1_enable = 0;
	ste_0_match_6_2_enable = 0;
	ste_0_match_6_3_enable = 0;
	ste_0_match_6_4_enable = 0;
	ste_0_match_6_5_enable = 0;
	ste_0_match_6_6_enable = 0;
	ste_0_match_7_0_enable = 0;
	ste_0_match_7_1_enable = 0;
	ste_0_match_7_2_enable = 0;
	ste_0_match_7_3_enable = 0;
	ste_0_match_7_4_enable = 0;
	ste_0_match_7_5_enable = 0;
	ste_0_match_7_6_enable = 0;
	ste_0_match_8_0_enable = 0;
	ste_0_match_8_1_enable = 0;
	ste_0_match_8_2_enable = 0;
	ste_0_match_8_3_enable = 0;
	ste_0_match_8_4_enable = 0;
	ste_0_match_8_5_enable = 0;
	ste_0_match_8_6_enable = 0;
	ste_0_match_9_0_enable = 0;
	ste_0_match_9_1_enable = 0;
	ste_0_match_9_2_enable = 0;
	ste_0_match_9_3_enable = 0;
	ste_0_match_9_4_enable = 0;
	ste_0_match_9_5_enable = 0;
	ste_0_match_9_6_enable = 0;
	ste_0_match_10_0_enable = 0;
	ste_0_match_10_1_enable = 0;
	ste_0_match_10_2_enable = 0;
	ste_0_match_10_3_enable = 0;
	ste_0_match_10_4_enable = 0;
	ste_0_match_10_5_enable = 0;
	ste_0_match_10_6_enable = 0;
	ste_0_match_11_0_enable = 0;
	ste_0_match_11_1_enable = 0;
	ste_0_match_11_2_enable = 0;
	ste_0_match_11_3_enable = 0;
	ste_0_match_11_4_enable = 0;
	ste_0_match_11_5_enable = 0;
	ste_0_match_11_6_enable = 0;
	ste_0_match_12_0_enable = 0;
	ste_0_match_12_1_enable = 0;
	ste_0_match_12_2_enable = 0;
	ste_0_match_12_3_enable = 0;
	ste_0_match_12_4_enable = 0;
	ste_0_match_12_5_enable = 0;
	ste_0_match_12_6_enable = 0;
	ste_0_match_13_0_enable = 0;
	ste_0_match_13_1_enable = 0;
	ste_0_match_13_2_enable = 0;
	ste_0_match_13_3_enable = 0;
	ste_0_match_13_4_enable = 0;
	ste_0_match_13_5_enable = 0;
	ste_0_match_13_6_enable = 0;
	ste_0_match_14_0_enable = 0;
	ste_0_match_14_1_enable = 0;
	ste_0_match_14_2_enable = 0;
	ste_0_match_14_3_enable = 0;
	ste_0_match_14_4_enable = 0;
	ste_0_match_14_5_enable = 0;
	ste_0_match_14_6_enable = 0;
	ste_0_match_15_0_enable = 0;
	ste_0_match_15_1_enable = 0;
	ste_0_match_15_2_enable = 0;
	ste_0_match_15_3_enable = 0;
	ste_0_match_15_4_enable = 0;
	ste_0_match_15_5_enable = 0;
	ste_0_match_15_6_enable = 0;
	ste_0_match_16_0_enable = 0;
	ste_0_match_16_1_enable = 0;
	ste_0_match_16_2_enable = 0;
	ste_0_match_16_3_enable = 0;
	ste_0_match_16_4_enable = 0;
	ste_0_match_16_5_enable = 0;
	ste_0_match_16_6_enable = 0;
	ste_0_match_17_0_enable = 0;
	ste_0_match_17_1_enable = 0;
	ste_0_match_17_2_enable = 0;
	ste_0_match_17_3_enable = 0;
	ste_0_match_17_4_enable = 0;
	ste_0_match_17_5_enable = 0;
	ste_0_match_17_6_enable = 0;
	ste_0_match_18_0_enable = 0;
	ste_0_match_18_1_enable = 0;
	ste_0_match_18_2_enable = 0;
	ste_0_match_18_3_enable = 0;
	ste_0_match_18_4_enable = 0;
	ste_0_match_18_5_enable = 0;
	ste_0_match_18_6_enable = 0;
	ste_0_match_19_0_enable = 0;
	ste_0_match_19_1_enable = 0;
	ste_0_match_19_2_enable = 0;
	ste_0_match_19_3_enable = 0;
	ste_0_match_19_4_enable = 0;
	ste_0_match_19_5_enable = 0;
	ste_0_match_19_6_enable = 0;
	ste_0_match_20_0_enable = 0;
	ste_0_match_20_1_enable = 0;
	ste_0_match_20_2_enable = 0;
	ste_0_match_20_3_enable = 0;
	ste_0_match_20_4_enable = 0;
	ste_0_match_20_5_enable = 0;
	ste_0_match_20_6_enable = 0;
	ste_0_match_21_0_enable = 0;
	ste_0_match_21_1_enable = 0;
	ste_0_match_21_2_enable = 0;
	ste_0_match_21_3_enable = 0;
	ste_0_match_21_4_enable = 0;
	ste_0_match_21_5_enable = 0;
	ste_0_match_21_6_enable = 0;
	ste_0_match_22_0_enable = 0;
	ste_0_match_22_1_enable = 0;
	ste_0_match_22_2_enable = 0;
	ste_0_match_22_3_enable = 0;
	ste_0_match_22_4_enable = 0;
	ste_0_match_22_5_enable = 0;
	ste_0_match_22_6_enable = 0;
	ste_0_match_23_0_enable = 0;
	ste_0_match_23_1_enable = 0;
	ste_0_match_23_2_enable = 0;
	ste_0_match_23_3_enable = 0;
	ste_0_match_23_4_enable = 0;
	ste_0_match_23_5_enable = 0;
	ste_0_match_23_6_enable = 0;

	ste_0_mismatch_0_1_enable = 0;
	ste_0_mismatch_0_2_enable = 0;
	ste_0_mismatch_0_3_enable = 0;
	ste_0_mismatch_0_4_enable = 0;
	ste_0_mismatch_0_5_enable = 0;
	ste_0_mismatch_0_6_enable = 0;
	ste_0_mismatch_1_1_enable = 0;
	ste_0_mismatch_1_2_enable = 0;
	ste_0_mismatch_1_3_enable = 0;
	ste_0_mismatch_1_4_enable = 0;
	ste_0_mismatch_1_5_enable = 0;
	ste_0_mismatch_1_6_enable = 0;
	ste_0_mismatch_2_1_enable = 0;
	ste_0_mismatch_2_2_enable = 0;
	ste_0_mismatch_2_3_enable = 0;
	ste_0_mismatch_2_4_enable = 0;
	ste_0_mismatch_2_5_enable = 0;
	ste_0_mismatch_2_6_enable = 0;
	ste_0_mismatch_3_1_enable = 0;
	ste_0_mismatch_3_2_enable = 0;
	ste_0_mismatch_3_3_enable = 0;
	ste_0_mismatch_3_4_enable = 0;
	ste_0_mismatch_3_5_enable = 0;
	ste_0_mismatch_3_6_enable = 0;
	ste_0_mismatch_4_1_enable = 0;
	ste_0_mismatch_4_2_enable = 0;
	ste_0_mismatch_4_3_enable = 0;
	ste_0_mismatch_4_4_enable = 0;
	ste_0_mismatch_4_5_enable = 0;
	ste_0_mismatch_4_6_enable = 0;
	ste_0_mismatch_5_1_enable = 0;
	ste_0_mismatch_5_2_enable = 0;
	ste_0_mismatch_5_3_enable = 0;
	ste_0_mismatch_5_4_enable = 0;
	ste_0_mismatch_5_5_enable = 0;
	ste_0_mismatch_5_6_enable = 0;
	ste_0_mismatch_6_1_enable = 0;
	ste_0_mismatch_6_2_enable = 0;
	ste_0_mismatch_6_3_enable = 0;
	ste_0_mismatch_6_4_enable = 0;
	ste_0_mismatch_6_5_enable = 0;
	ste_0_mismatch_6_6_enable = 0;
	ste_0_mismatch_7_1_enable = 0;
	ste_0_mismatch_7_2_enable = 0;
	ste_0_mismatch_7_3_enable = 0;
	ste_0_mismatch_7_4_enable = 0;
	ste_0_mismatch_7_5_enable = 0;
	ste_0_mismatch_7_6_enable = 0;
	ste_0_mismatch_8_1_enable = 0;
	ste_0_mismatch_8_2_enable = 0;
	ste_0_mismatch_8_3_enable = 0;
	ste_0_mismatch_8_4_enable = 0;
	ste_0_mismatch_8_5_enable = 0;
	ste_0_mismatch_8_6_enable = 0;
	ste_0_mismatch_9_1_enable = 0;
	ste_0_mismatch_9_2_enable = 0;
	ste_0_mismatch_9_3_enable = 0;
	ste_0_mismatch_9_4_enable = 0;
	ste_0_mismatch_9_5_enable = 0;
	ste_0_mismatch_9_6_enable = 0;
	ste_0_mismatch_10_1_enable = 0;
	ste_0_mismatch_10_2_enable = 0;
	ste_0_mismatch_10_3_enable = 0;
	ste_0_mismatch_10_4_enable = 0;
	ste_0_mismatch_10_5_enable = 0;
	ste_0_mismatch_10_6_enable = 0;
	ste_0_mismatch_11_1_enable = 0;
	ste_0_mismatch_11_2_enable = 0;
	ste_0_mismatch_11_3_enable = 0;
	ste_0_mismatch_11_4_enable = 0;
	ste_0_mismatch_11_5_enable = 0;
	ste_0_mismatch_11_6_enable = 0;
	ste_0_mismatch_12_1_enable = 0;
	ste_0_mismatch_12_2_enable = 0;
	ste_0_mismatch_12_3_enable = 0;
	ste_0_mismatch_12_4_enable = 0;
	ste_0_mismatch_12_5_enable = 0;
	ste_0_mismatch_12_6_enable = 0;
	ste_0_mismatch_13_1_enable = 0;
	ste_0_mismatch_13_2_enable = 0;
	ste_0_mismatch_13_3_enable = 0;
	ste_0_mismatch_13_4_enable = 0;
	ste_0_mismatch_13_5_enable = 0;
	ste_0_mismatch_13_6_enable = 0;
	ste_0_mismatch_14_1_enable = 0;
	ste_0_mismatch_14_2_enable = 0;
	ste_0_mismatch_14_3_enable = 0;
	ste_0_mismatch_14_4_enable = 0;
	ste_0_mismatch_14_5_enable = 0;
	ste_0_mismatch_14_6_enable = 0;
	ste_0_mismatch_15_1_enable = 0;
	ste_0_mismatch_15_2_enable = 0;
	ste_0_mismatch_15_3_enable = 0;
	ste_0_mismatch_15_4_enable = 0;
	ste_0_mismatch_15_5_enable = 0;
	ste_0_mismatch_15_6_enable = 0;
	ste_0_mismatch_16_1_enable = 0;
	ste_0_mismatch_16_2_enable = 0;
	ste_0_mismatch_16_3_enable = 0;
	ste_0_mismatch_16_4_enable = 0;
	ste_0_mismatch_16_5_enable = 0;
	ste_0_mismatch_16_6_enable = 0;
	ste_0_mismatch_17_1_enable = 0;
	ste_0_mismatch_17_2_enable = 0;
	ste_0_mismatch_17_3_enable = 0;
	ste_0_mismatch_17_4_enable = 0;
	ste_0_mismatch_17_5_enable = 0;
	ste_0_mismatch_17_6_enable = 0;
	ste_0_mismatch_18_1_enable = 0;
	ste_0_mismatch_18_2_enable = 0;
	ste_0_mismatch_18_3_enable = 0;
	ste_0_mismatch_18_4_enable = 0;
	ste_0_mismatch_18_5_enable = 0;
	ste_0_mismatch_18_6_enable = 0;
	ste_0_mismatch_19_1_enable = 0;
	ste_0_mismatch_19_2_enable = 0;
	ste_0_mismatch_19_3_enable = 0;
	ste_0_mismatch_19_4_enable = 0;
	ste_0_mismatch_19_5_enable = 0;
	ste_0_mismatch_19_6_enable = 0;
	ste_0_mismatch_20_1_enable = 0;
	ste_0_mismatch_20_2_enable = 0;
	ste_0_mismatch_20_3_enable = 0;
	ste_0_mismatch_20_4_enable = 0;
	ste_0_mismatch_20_5_enable = 0;
	ste_0_mismatch_20_6_enable = 0;
	ste_0_mismatch_21_1_enable = 0;
	ste_0_mismatch_21_2_enable = 0;
	ste_0_mismatch_21_3_enable = 0;
	ste_0_mismatch_21_4_enable = 0;
	ste_0_mismatch_21_5_enable = 0;
	ste_0_mismatch_21_6_enable = 0;
	ste_0_mismatch_22_1_enable = 0;
	ste_0_mismatch_22_2_enable = 0;
	ste_0_mismatch_22_3_enable = 0;
	ste_0_mismatch_22_4_enable = 0;
	ste_0_mismatch_22_5_enable = 0;
	ste_0_mismatch_22_6_enable = 0;
	ste_0_mismatch_23_1_enable = 0;
	ste_0_mismatch_23_2_enable = 0;
	ste_0_mismatch_23_3_enable = 0;
	ste_0_mismatch_23_4_enable = 0;
	ste_0_mismatch_23_5_enable = 0;
	ste_0_mismatch_23_6_enable = 0;

#if PRINTF
	print_state();
#endif
}

void automata_0::step(uint8_t input, ap_uint<1> &result, uint8_t pattern_id)
{
#pragma HLS INLINE OFF
#pragma HLS pipeline II = 1
#pragma HLS array_partition variable = symbolset type = complete
#pragma HLS FUNCTION_INSTANTIATE variable = pattern_id

	// State Logic
	ap_uint<1> ste_0_match_1_0 = (lev_distance[0]) &&  (ste_0_match_1_0_enable) && ((input_r == symbolset[0]));
	ap_uint<1> ste_0_match_1_1 = (lev_distance[1]) &&  (ste_0_match_1_1_enable) && ((input_r == symbolset[0]));
	ap_uint<1> ste_0_match_1_2 = (lev_distance[2]) &&  (ste_0_match_1_2_enable) && ((input_r == symbolset[0]));
	ap_uint<1> ste_0_match_1_3 = (lev_distance[3]) &&  (ste_0_match_1_3_enable) && ((input_r == symbolset[0]));
	ap_uint<1> ste_0_match_1_4 = (lev_distance[4]) &&  (ste_0_match_1_4_enable) && ((input_r == symbolset[0]));
	ap_uint<1> ste_0_match_1_5 = (lev_distance[5]) &&  (ste_0_match_1_5_enable) && ((input_r == symbolset[0]));
	ap_uint<1> ste_0_match_1_6 = (lev_distance[6]) &&  (ste_0_match_1_6_enable) && ((input_r == symbolset[0]));
	ap_uint<1> ste_0_match_2_0 = (lev_distance[0]) &&  (ste_0_match_2_0_enable) && ((input_r == symbolset[1]));
	ap_uint<1> ste_0_match_2_1 = (lev_distance[1]) &&  (ste_0_match_2_1_enable) && ((input_r == symbolset[1]));
	ap_uint<1> ste_0_match_2_2 = (lev_distance[2]) &&  (ste_0_match_2_2_enable) && ((input_r == symbolset[1]));
	ap_uint<1> ste_0_match_2_3 = (lev_distance[3]) &&  (ste_0_match_2_3_enable) && ((input_r == symbolset[1]));
	ap_uint<1> ste_0_match_2_4 = (lev_distance[4]) &&  (ste_0_match_2_4_enable) && ((input_r == symbolset[1]));
	ap_uint<1> ste_0_match_2_5 = (lev_distance[5]) &&  (ste_0_match_2_5_enable) && ((input_r == symbolset[1]));
	ap_uint<1> ste_0_match_2_6 = (lev_distance[6]) &&  (ste_0_match_2_6_enable) && ((input_r == symbolset[1]));
	ap_uint<1> ste_0_match_3_0 = (lev_distance[0]) &&  (ste_0_match_3_0_enable) && ((input_r == symbolset[2]));
	ap_uint<1> ste_0_match_3_1 = (lev_distance[1]) &&  (ste_0_match_3_1_enable) && ((input_r == symbolset[2]));
	ap_uint<1> ste_0_match_3_2 = (lev_distance[2]) &&  (ste_0_match_3_2_enable) && ((input_r == symbolset[2]));
	ap_uint<1> ste_0_match_3_3 = (lev_distance[3]) &&  (ste_0_match_3_3_enable) && ((input_r == symbolset[2]));
	ap_uint<1> ste_0_match_3_4 = (lev_distance[4]) &&  (ste_0_match_3_4_enable) && ((input_r == symbolset[2]));
	ap_uint<1> ste_0_match_3_5 = (lev_distance[5]) &&  (ste_0_match_3_5_enable) && ((input_r == symbolset[2]));
	ap_uint<1> ste_0_match_3_6 = (lev_distance[6]) &&  (ste_0_match_3_6_enable) && ((input_r == symbolset[2]));
	ap_uint<1> ste_0_match_4_0 = (lev_distance[0]) &&  (ste_0_match_4_0_enable) && ((input_r == symbolset[3]));
	ap_uint<1> ste_0_match_4_1 = (lev_distance[1]) &&  (ste_0_match_4_1_enable) && ((input_r == symbolset[3]));
	ap_uint<1> ste_0_match_4_2 = (lev_distance[2]) &&  (ste_0_match_4_2_enable) && ((input_r == symbolset[3]));
	ap_uint<1> ste_0_match_4_3 = (lev_distance[3]) &&  (ste_0_match_4_3_enable) && ((input_r == symbolset[3]));
	ap_uint<1> ste_0_match_4_4 = (lev_distance[4]) &&  (ste_0_match_4_4_enable) && ((input_r == symbolset[3]));
	ap_uint<1> ste_0_match_4_5 = (lev_distance[5]) &&  (ste_0_match_4_5_enable) && ((input_r == symbolset[3]));
	ap_uint<1> ste_0_match_4_6 = (lev_distance[6] ) &&  (ste_0_match_4_6_enable) && ((input_r == symbolset[3]));
	ap_uint<1> ste_0_match_5_0 = (lev_distance[0]) &&  (ste_0_match_5_0_enable) && ((input_r == symbolset[4]));
	ap_uint<1> ste_0_match_5_1 = (lev_distance[1]) &&  (ste_0_match_5_1_enable) && ((input_r == symbolset[4]));
	ap_uint<1> ste_0_match_5_2 = (lev_distance[2]) &&  (ste_0_match_5_2_enable) && ((input_r == symbolset[4]));
	ap_uint<1> ste_0_match_5_3 = (lev_distance[3]) &&  (ste_0_match_5_3_enable) && ((input_r == symbolset[4]));
	ap_uint<1> ste_0_match_5_4 = (lev_distance[4]) &&  (ste_0_match_5_4_enable) && ((input_r == symbolset[4]));
	ap_uint<1> ste_0_match_5_5 = (lev_distance[5]) &&  (ste_0_match_5_5_enable) && ((input_r == symbolset[4]));
	ap_uint<1> ste_0_match_5_6 = (lev_distance[6]) &&  (ste_0_match_5_6_enable) && ((input_r == symbolset[4]));
	ap_uint<1> ste_0_match_6_0 = (lev_distance[0]) &&  (ste_0_match_6_0_enable) && ((input_r == symbolset[5]));
	ap_uint<1> ste_0_match_6_1 = (lev_distance[1]) &&  (ste_0_match_6_1_enable) && ((input_r == symbolset[5]));
	ap_uint<1> ste_0_match_6_2 = (lev_distance[2]) &&  (ste_0_match_6_2_enable) && ((input_r == symbolset[5]));
	ap_uint<1> ste_0_match_6_3 = (lev_distance[3]) &&  (ste_0_match_6_3_enable) && ((input_r == symbolset[5]));
	ap_uint<1> ste_0_match_6_4 = (lev_distance[4]) &&  (ste_0_match_6_4_enable) && ((input_r == symbolset[5]));
	ap_uint<1> ste_0_match_6_5 = (lev_distance[5]) &&  (ste_0_match_6_5_enable) && ((input_r == symbolset[5]));
	ap_uint<1> ste_0_match_6_6 = (lev_distance[6]) &&  (ste_0_match_6_6_enable) && ((input_r == symbolset[5]));
	ap_uint<1> ste_0_match_7_0 = (lev_distance[0]) &&  (ste_0_match_7_0_enable) && ((input_r == symbolset[6]));
	ap_uint<1> ste_0_match_7_1 = (lev_distance[1]) &&  (ste_0_match_7_1_enable) && ((input_r == symbolset[6]));
	ap_uint<1> ste_0_match_7_2 = (lev_distance[2]) &&  (ste_0_match_7_2_enable) && ((input_r == symbolset[6]));
	ap_uint<1> ste_0_match_7_3 = (lev_distance[3]) &&  (ste_0_match_7_3_enable) && ((input_r == symbolset[6]));
	ap_uint<1> ste_0_match_7_4 = (lev_distance[4]) &&  (ste_0_match_7_4_enable) && ((input_r == symbolset[6]));
	ap_uint<1> ste_0_match_7_5 = (lev_distance[5]) &&  (ste_0_match_7_5_enable) && ((input_r == symbolset[6]));
	ap_uint<1> ste_0_match_7_6 = (lev_distance[6]) &&  (ste_0_match_7_6_enable) && ((input_r == symbolset[6]));
	ap_uint<1> ste_0_match_8_0 = (lev_distance[0]) &&  (ste_0_match_8_0_enable) && ((input_r == symbolset[7]));
	ap_uint<1> ste_0_match_8_1 = (lev_distance[1]) &&  (ste_0_match_8_1_enable) && ((input_r == symbolset[7]));
	ap_uint<1> ste_0_match_8_2 = (lev_distance[2]) &&  (ste_0_match_8_2_enable) && ((input_r == symbolset[7]));
	ap_uint<1> ste_0_match_8_3 = (lev_distance[3]) &&  (ste_0_match_8_3_enable) && ((input_r == symbolset[7]));
	ap_uint<1> ste_0_match_8_4 = (lev_distance[4]) &&  (ste_0_match_8_4_enable) && ((input_r == symbolset[7]));
	ap_uint<1> ste_0_match_8_5 = (lev_distance[5]) &&  (ste_0_match_8_5_enable) && ((input_r == symbolset[7]));
	ap_uint<1> ste_0_match_8_6 = (lev_distance[6]) &&  (ste_0_match_8_6_enable) && ((input_r == symbolset[7]));
	ap_uint<1> ste_0_match_9_0 = (lev_distance[0]) &&  (ste_0_match_9_0_enable) && ((input_r == symbolset[8]));
	ap_uint<1> ste_0_match_9_1 = (lev_distance[1]) &&  (ste_0_match_9_1_enable) && ((input_r == symbolset[8]));
	ap_uint<1> ste_0_match_9_2 = (lev_distance[2]) &&  (ste_0_match_9_2_enable) && ((input_r == symbolset[8]));
	ap_uint<1> ste_0_match_9_3 = (lev_distance[3]) &&  (ste_0_match_9_3_enable) && ((input_r == symbolset[8]));
	ap_uint<1> ste_0_match_9_4 = (lev_distance[4]) &&  (ste_0_match_9_4_enable) && ((input_r == symbolset[8]));
	ap_uint<1> ste_0_match_9_5 = (lev_distance[5]) &&  (ste_0_match_9_5_enable) && ((input_r == symbolset[8]));
	ap_uint<1> ste_0_match_9_6 = (lev_distance[6]) &&  (ste_0_match_9_6_enable) && ((input_r == symbolset[8]));
	ap_uint<1> ste_0_match_10_0 = (lev_distance[0]) &&  (ste_0_match_10_0_enable) && ((input_r == symbolset[9]));
	ap_uint<1> ste_0_match_10_1 = (lev_distance[1]) &&  (ste_0_match_10_1_enable) && ((input_r == symbolset[9]));
	ap_uint<1> ste_0_match_10_2 = (lev_distance[2]) &&  (ste_0_match_10_2_enable) && ((input_r == symbolset[9]));
	ap_uint<1> ste_0_match_10_3 = (lev_distance[3]) &&  (ste_0_match_10_3_enable) && ((input_r == symbolset[9]));
	ap_uint<1> ste_0_match_10_4 = (lev_distance[4]) &&  (ste_0_match_10_4_enable) && ((input_r == symbolset[9]));
	ap_uint<1> ste_0_match_10_5 = (lev_distance[5]) &&  (ste_0_match_10_5_enable) && ((input_r == symbolset[9]));
	ap_uint<1> ste_0_match_10_6 = (lev_distance[6]) &&  (ste_0_match_10_6_enable) && ((input_r == symbolset[9]));
	ap_uint<1> ste_0_match_11_0 = (lev_distance[0]) &&  (ste_0_match_11_0_enable) && ((input_r == symbolset[10]));
	ap_uint<1> ste_0_match_11_1 = (lev_distance[1]) &&  (ste_0_match_11_1_enable) && ((input_r == symbolset[10]));
	ap_uint<1> ste_0_match_11_2 = (lev_distance[2]) &&  (ste_0_match_11_2_enable) && ((input_r == symbolset[10]));
	ap_uint<1> ste_0_match_11_3 = (lev_distance[3]) &&  (ste_0_match_11_3_enable) && ((input_r == symbolset[10]));
	ap_uint<1> ste_0_match_11_4 = (lev_distance[4]) &&  (ste_0_match_11_4_enable) && ((input_r == symbolset[10]));
	ap_uint<1> ste_0_match_11_5 = (lev_distance[5]) &&  (ste_0_match_11_5_enable) && ((input_r == symbolset[10]));
	ap_uint<1> ste_0_match_11_6 = (lev_distance[6]) &&  (ste_0_match_11_6_enable) && ((input_r == symbolset[10]));
	ap_uint<1> ste_0_match_12_0 = (lev_distance[0]) &&  (ste_0_match_12_0_enable) && ((input_r == symbolset[11]));
	ap_uint<1> ste_0_match_12_1 = (lev_distance[1]) &&  (ste_0_match_12_1_enable) && ((input_r == symbolset[11]));
	ap_uint<1> ste_0_match_12_2 = (lev_distance[2]) &&  (ste_0_match_12_2_enable) && ((input_r == symbolset[11]));
	ap_uint<1> ste_0_match_12_3 = (lev_distance[3]) &&  (ste_0_match_12_3_enable) && ((input_r == symbolset[11]));
	ap_uint<1> ste_0_match_12_4 = (lev_distance[4]) &&  (ste_0_match_12_4_enable) && ((input_r == symbolset[11]));
	ap_uint<1> ste_0_match_12_5 = (lev_distance[5]) &&  (ste_0_match_12_5_enable) && ((input_r == symbolset[11]));
	ap_uint<1> ste_0_match_12_6 = (lev_distance[6]) &&  (ste_0_match_12_6_enable) && ((input_r == symbolset[11]));
	ap_uint<1> ste_0_match_13_0 = (lev_distance[0]) &&  (ste_0_match_13_0_enable) && ((input_r == symbolset[12]));
	ap_uint<1> ste_0_match_13_1 = (lev_distance[1]) &&  (ste_0_match_13_1_enable) && ((input_r == symbolset[12]));
	ap_uint<1> ste_0_match_13_2 = (lev_distance[2]) &&  (ste_0_match_13_2_enable) && ((input_r == symbolset[12]));
	ap_uint<1> ste_0_match_13_3 = (lev_distance[3]) &&  (ste_0_match_13_3_enable) && ((input_r == symbolset[12]));
	ap_uint<1> ste_0_match_13_4 = (lev_distance[4]) &&  (ste_0_match_13_4_enable) && ((input_r == symbolset[12]));
	ap_uint<1> ste_0_match_13_5 = (lev_distance[5]) &&  (ste_0_match_13_5_enable) && ((input_r == symbolset[12]));
	ap_uint<1> ste_0_match_13_6 = (lev_distance[6]) &&  (ste_0_match_13_6_enable) && ((input_r == symbolset[12]));
	ap_uint<1> ste_0_match_14_0 = (lev_distance[0]) &&  (ste_0_match_14_0_enable) && ((input_r == symbolset[13]));
	ap_uint<1> ste_0_match_14_1 = (lev_distance[1]) &&  (ste_0_match_14_1_enable) && ((input_r == symbolset[13]));
	ap_uint<1> ste_0_match_14_2 = (lev_distance[2]) &&  (ste_0_match_14_2_enable) && ((input_r == symbolset[13]));
	ap_uint<1> ste_0_match_14_3 = (lev_distance[3]) &&  (ste_0_match_14_3_enable) && ((input_r == symbolset[13]));
	ap_uint<1> ste_0_match_14_4 = (lev_distance[4]) &&  (ste_0_match_14_4_enable) && ((input_r == symbolset[13]));
	ap_uint<1> ste_0_match_14_5 = (lev_distance[5]) &&  (ste_0_match_14_5_enable) && ((input_r == symbolset[13]));
	ap_uint<1> ste_0_match_14_6 = (lev_distance[6] ) &&  (ste_0_match_14_6_enable) && ((input_r == symbolset[13]));
	ap_uint<1> ste_0_match_15_0 = (lev_distance[0]) &&  (ste_0_match_15_0_enable) && ((input_r == symbolset[14]));
	ap_uint<1> ste_0_match_15_1 = (lev_distance[1]) &&  (ste_0_match_15_1_enable) && ((input_r == symbolset[14]));
	ap_uint<1> ste_0_match_15_2 = (lev_distance[2]) &&  (ste_0_match_15_2_enable) && ((input_r == symbolset[14]));
	ap_uint<1> ste_0_match_15_3 = (lev_distance[3]) &&  (ste_0_match_15_3_enable) && ((input_r == symbolset[14]));
	ap_uint<1> ste_0_match_15_4 = (lev_distance[4]) &&  (ste_0_match_15_4_enable) && ((input_r == symbolset[14]));
	ap_uint<1> ste_0_match_15_5 = (lev_distance[5]) &&  (ste_0_match_15_5_enable) && ((input_r == symbolset[14]));
	ap_uint<1> ste_0_match_15_6 = (lev_distance[6]) &&  (ste_0_match_15_6_enable) && ((input_r == symbolset[14]));
	ap_uint<1> ste_0_match_16_0 = (lev_distance[0]) &&  (ste_0_match_16_0_enable) && ((input_r == symbolset[15]));
	ap_uint<1> ste_0_match_16_1 = (lev_distance[1]) &&  (ste_0_match_16_1_enable) && ((input_r == symbolset[15]));
	ap_uint<1> ste_0_match_16_2 = (lev_distance[2]) &&  (ste_0_match_16_2_enable) && ((input_r == symbolset[15]));
	ap_uint<1> ste_0_match_16_3 = (lev_distance[3]) &&  (ste_0_match_16_3_enable) && ((input_r == symbolset[15]));
	ap_uint<1> ste_0_match_16_4 = (lev_distance[4]) &&  (ste_0_match_16_4_enable) && ((input_r == symbolset[15]));
	ap_uint<1> ste_0_match_16_5 = (lev_distance[5]) &&  (ste_0_match_16_5_enable) && ((input_r == symbolset[15]));
	ap_uint<1> ste_0_match_16_6 = (lev_distance[6]) &&  (ste_0_match_16_6_enable) && ((input_r == symbolset[15]));
	ap_uint<1> ste_0_match_17_0 = (lev_distance[0]) &&  (ste_0_match_17_0_enable) && ((input_r == symbolset[16]));
	ap_uint<1> ste_0_match_17_1 = (lev_distance[1]) &&  (ste_0_match_17_1_enable) && ((input_r == symbolset[16]));
	ap_uint<1> ste_0_match_17_2 = (lev_distance[2]) &&  (ste_0_match_17_2_enable) && ((input_r == symbolset[16]));
	ap_uint<1> ste_0_match_17_3 = (lev_distance[3]) &&  (ste_0_match_17_3_enable) && ((input_r == symbolset[16]));
	ap_uint<1> ste_0_match_17_4 = (lev_distance[4]) &&  (ste_0_match_17_4_enable) && ((input_r == symbolset[16]));
	ap_uint<1> ste_0_match_17_5 = (lev_distance[5]) &&  (ste_0_match_17_5_enable) && ((input_r == symbolset[16]));
	ap_uint<1> ste_0_match_17_6 = (lev_distance[6]) &&  (ste_0_match_17_6_enable) && ((input_r == symbolset[16]));
	ap_uint<1> ste_0_match_18_0 = (lev_distance[0]) &&  (ste_0_match_18_0_enable) && ((input_r == symbolset[17]));
	ap_uint<1> ste_0_match_18_1 = (lev_distance[1]) &&  (ste_0_match_18_1_enable) && ((input_r == symbolset[17]));
	ap_uint<1> ste_0_match_18_2 = (lev_distance[2]) &&  (ste_0_match_18_2_enable) && ((input_r == symbolset[17]));
	ap_uint<1> ste_0_match_18_3 = (lev_distance[3]) &&  (ste_0_match_18_3_enable) && ((input_r == symbolset[17]));
	ap_uint<1> ste_0_match_18_4 = (lev_distance[4]) &&  (ste_0_match_18_4_enable) && ((input_r == symbolset[17]));
	ap_uint<1> ste_0_match_18_5 = (lev_distance[5]) &&  (ste_0_match_18_5_enable) && ((input_r == symbolset[17]));
	ap_uint<1> ste_0_match_18_6 = (lev_distance[6]) &&  (ste_0_match_18_6_enable) && ((input_r == symbolset[17]));
	ap_uint<1> ste_0_match_19_0 = (lev_distance[0]) &&  (ste_0_match_19_0_enable) && ((input_r == symbolset[18]));
	ap_uint<1> ste_0_match_19_1 = (lev_distance[1]) &&  (ste_0_match_19_1_enable) && ((input_r == symbolset[18]));
	ap_uint<1> ste_0_match_19_2 = (lev_distance[2]) &&  (ste_0_match_19_2_enable) && ((input_r == symbolset[18]));
	ap_uint<1> ste_0_match_19_3 = (lev_distance[3]) &&  (ste_0_match_19_3_enable) && ((input_r == symbolset[18]));
	ap_uint<1> ste_0_match_19_4 = (lev_distance[4]) &&  (ste_0_match_19_4_enable) && ((input_r == symbolset[18]));
	ap_uint<1> ste_0_match_19_5 = (lev_distance[5]) &&  (ste_0_match_19_5_enable) && ((input_r == symbolset[18]));
	ap_uint<1> ste_0_match_19_6 = (lev_distance[6]) &&  (ste_0_match_19_6_enable) && ((input_r == symbolset[18]));
	ap_uint<1> ste_0_match_20_0 = (lev_distance[0]) &&  (ste_0_match_20_0_enable) && ((input_r == symbolset[19]));
	ap_uint<1> ste_0_match_20_1 = (lev_distance[1]) &&  (ste_0_match_20_1_enable) && ((input_r == symbolset[19]));
	ap_uint<1> ste_0_match_20_2 = (lev_distance[2]) &&  (ste_0_match_20_2_enable) && ((input_r == symbolset[19]));
	ap_uint<1> ste_0_match_20_3 = (lev_distance[3]) &&  (ste_0_match_20_3_enable) && ((input_r == symbolset[19]));
	ap_uint<1> ste_0_match_20_4 = (lev_distance[4]) &&  (ste_0_match_20_4_enable) && ((input_r == symbolset[19]));
	ap_uint<1> ste_0_match_20_5 = (lev_distance[5]) &&  (ste_0_match_20_5_enable) && ((input_r == symbolset[19]));
	ap_uint<1> ste_0_match_20_6 = (lev_distance[6]) &&  (ste_0_match_20_6_enable) && ((input_r == symbolset[19]));

	ap_uint<1> ste_0_match_21_0 = (lev_distance[0]) &&  (ste_0_match_21_0_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));	// N
	ap_uint<1> ste_0_match_21_1 = (lev_distance[1]) &&  (ste_0_match_21_1_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));	// N
	ap_uint<1> ste_0_match_21_2 = (lev_distance[2]) &&  (ste_0_match_21_2_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));	// N
	ap_uint<1> ste_0_match_21_3 = (lev_distance[3]) &&  (ste_0_match_21_3_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));	// N
	ap_uint<1> ste_0_match_21_4 = (lev_distance[4]) &&  (ste_0_match_21_4_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));	// N
	ap_uint<1> ste_0_match_21_5 = (lev_distance[5]) &&  (ste_0_match_21_5_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));	// N
	ap_uint<1> ste_0_match_21_6 = (lev_distance[6]) &&  (ste_0_match_21_6_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));	// N

	ap_uint<1> ste_0_match_22_0 = (lev_distance[0]) &&  (ste_0_match_22_0_enable) && ((input_r == 71)); //symbolset[21]));	G
	ap_uint<1> ste_0_match_22_1 = (lev_distance[1]) &&  (ste_0_match_22_1_enable) && ((input_r == 71)); //symbolset[21]));	G
	ap_uint<1> ste_0_match_22_2 = (lev_distance[2]) &&  (ste_0_match_22_2_enable) && ((input_r == 71)); //symbolset[21]));	G
	ap_uint<1> ste_0_match_22_3 = (lev_distance[3]) &&  (ste_0_match_22_3_enable) && ((input_r == 71)); //symbolset[21]));	G
	ap_uint<1> ste_0_match_22_4 = (lev_distance[4]) &&  (ste_0_match_22_4_enable) && ((input_r == 71)); //symbolset[21]));	G
	ap_uint<1> ste_0_match_22_5 = (lev_distance[5]) &&  (ste_0_match_22_5_enable) && ((input_r == 71)); //symbolset[21]));	G
	ap_uint<1> ste_0_match_22_6 = (lev_distance[6]) &&  (ste_0_match_22_6_enable) && ((input_r == 71)); //symbolset[21]));	G

	ap_uint<1> ste_0_match_23_0 = (lev_distance[0]) &&  (ste_0_match_23_0_enable) && ((input_r == 71)); //symbolset[22]));	G
	ap_uint<1> ste_0_match_23_1 = (lev_distance[1]) &&  (ste_0_match_23_1_enable) && ((input_r == 71)); //symbolset[22]));	G
	ap_uint<1> ste_0_match_23_2 = (lev_distance[2]) &&  (ste_0_match_23_2_enable) && ((input_r == 71)); //symbolset[22]));	G
	ap_uint<1> ste_0_match_23_3 = (lev_distance[3]) &&  (ste_0_match_23_3_enable) && ((input_r == 71)); //symbolset[22]));	G
	ap_uint<1> ste_0_match_23_4 = (lev_distance[4]) &&  (ste_0_match_23_4_enable) && ((input_r == 71)); //symbolset[22]));	G
	ap_uint<1> ste_0_match_23_5 = (lev_distance[5]) &&  (ste_0_match_23_5_enable) && ((input_r == 71)); //symbolset[22]));	G
	ap_uint<1> ste_0_match_23_6 = (lev_distance[6]) &&  (ste_0_match_23_6_enable) && ((input_r == 71)); //symbolset[22]));	G

	// Edit distance: 1
	ap_uint<1> ste_0_mismatch_0_1 = (lev_distance[1]) &&  (ste_0_mismatch_0_1_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 2
	ap_uint<1> ste_0_mismatch_0_2 = (lev_distance[2]) &&  (ste_0_mismatch_0_2_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 3
	ap_uint<1> ste_0_mismatch_0_3 = (lev_distance[3]) &&  (ste_0_mismatch_0_3_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 4
	ap_uint<1> ste_0_mismatch_0_4 = (lev_distance[4]) &&  (ste_0_mismatch_0_4_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 5
	ap_uint<1> ste_0_mismatch_0_5 = (lev_distance[5]) &&  (ste_0_mismatch_0_5_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 6
	ap_uint<1> ste_0_mismatch_0_6 = (lev_distance[6]) &&  (ste_0_mismatch_0_6_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 1
	ap_uint<1> ste_0_mismatch_2_1 = (lev_distance[1]) &&  (ste_0_mismatch_2_1_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 2
	ap_uint<1> ste_0_mismatch_2_2 = (lev_distance[2]) &&  (ste_0_mismatch_2_2_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 3
	ap_uint<1> ste_0_mismatch_2_3 = (lev_distance[3]) &&  (ste_0_mismatch_2_3_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 4
	ap_uint<1> ste_0_mismatch_2_4 = (lev_distance[4]) &&  (ste_0_mismatch_2_4_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 5
	ap_uint<1> ste_0_mismatch_2_5 = (lev_distance[5]) &&  (ste_0_mismatch_2_5_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 6
	ap_uint<1> ste_0_mismatch_2_6 = (lev_distance[6]) &&  (ste_0_mismatch_2_6_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 1
	ap_uint<1> ste_0_mismatch_3_1 = (lev_distance[1]) &&  (ste_0_mismatch_3_1_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 2
	ap_uint<1> ste_0_mismatch_3_2 = (lev_distance[2]) &&  (ste_0_mismatch_3_2_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 3
	ap_uint<1> ste_0_mismatch_3_3 = (lev_distance[3]) &&  (ste_0_mismatch_3_3_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 4
	ap_uint<1> ste_0_mismatch_3_4 = (lev_distance[4]) &&  (ste_0_mismatch_3_4_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 5
	ap_uint<1> ste_0_mismatch_3_5 = (lev_distance[5]) &&  (ste_0_mismatch_3_5_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 6
	ap_uint<1> ste_0_mismatch_3_6 = (lev_distance[6]) &&  (ste_0_mismatch_3_6_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 1
	ap_uint<1> ste_0_mismatch_4_1 = (lev_distance[1]) &&  (ste_0_mismatch_4_1_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 2
	ap_uint<1> ste_0_mismatch_4_2 = (lev_distance[2]) &&  (ste_0_mismatch_4_2_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 3
	ap_uint<1> ste_0_mismatch_4_3 = (lev_distance[3]) &&  (ste_0_mismatch_4_3_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 4
	ap_uint<1> ste_0_mismatch_4_4 = (lev_distance[4]) &&  (ste_0_mismatch_4_4_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 5
	ap_uint<1> ste_0_mismatch_4_5 = (lev_distance[5]) &&  (ste_0_mismatch_4_5_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 6
	ap_uint<1> ste_0_mismatch_4_6 = (lev_distance[6]) &&  (ste_0_mismatch_4_6_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 1
	ap_uint<1> ste_0_mismatch_5_1 = (lev_distance[1]) &&  (ste_0_mismatch_5_1_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 2
	ap_uint<1> ste_0_mismatch_5_2 = (lev_distance[2]) &&  (ste_0_mismatch_5_2_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 3
	ap_uint<1> ste_0_mismatch_5_3 = (lev_distance[3]) &&  (ste_0_mismatch_5_3_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 4
	ap_uint<1> ste_0_mismatch_5_4 = (lev_distance[4]) &&  (ste_0_mismatch_5_4_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 5
	ap_uint<1> ste_0_mismatch_5_5 = (lev_distance[5]) &&  (ste_0_mismatch_5_5_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 6
	ap_uint<1> ste_0_mismatch_5_6 = (lev_distance[6]) &&  (ste_0_mismatch_5_6_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 1
	ap_uint<1> ste_0_mismatch_6_1 = (lev_distance[1]) &&  (ste_0_mismatch_6_1_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 2
	ap_uint<1> ste_0_mismatch_6_2 = (lev_distance[2]) &&  (ste_0_mismatch_6_2_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 3
	ap_uint<1> ste_0_mismatch_6_3 = (lev_distance[3]) &&  (ste_0_mismatch_6_3_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 4
	ap_uint<1> ste_0_mismatch_6_4 = (lev_distance[4]) &&  (ste_0_mismatch_6_4_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 5
	ap_uint<1> ste_0_mismatch_6_5 = (lev_distance[5]) &&  (ste_0_mismatch_6_5_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 6
	ap_uint<1> ste_0_mismatch_6_6 = (lev_distance[6]) &&  (ste_0_mismatch_6_6_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 1
	ap_uint<1> ste_0_mismatch_7_1 = (lev_distance[1]) &&  (ste_0_mismatch_7_1_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 2
	ap_uint<1> ste_0_mismatch_7_2 = (lev_distance[2]) &&  (ste_0_mismatch_7_2_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 3
	ap_uint<1> ste_0_mismatch_7_3 = (lev_distance[3]) &&  (ste_0_mismatch_7_3_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 4
	ap_uint<1> ste_0_mismatch_7_4 = (lev_distance[4]) &&  (ste_0_mismatch_7_4_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 5
	ap_uint<1> ste_0_mismatch_7_5 = (lev_distance[5]) &&  (ste_0_mismatch_7_5_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 6
	ap_uint<1> ste_0_mismatch_7_6 = (lev_distance[6]) &&  (ste_0_mismatch_7_6_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 1
	ap_uint<1> ste_0_mismatch_8_1 = (lev_distance[1]) &&  (ste_0_mismatch_8_1_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 2
	ap_uint<1> ste_0_mismatch_8_2 = (lev_distance[2]) &&  (ste_0_mismatch_8_2_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 3
	ap_uint<1> ste_0_mismatch_8_3 = (lev_distance[3]) &&  (ste_0_mismatch_8_3_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 4
	ap_uint<1> ste_0_mismatch_8_4 = (lev_distance[4]) &&  (ste_0_mismatch_8_4_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 5
	ap_uint<1> ste_0_mismatch_8_5 = (lev_distance[5]) &&  (ste_0_mismatch_8_5_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 6
	ap_uint<1> ste_0_mismatch_8_6 = (lev_distance[6]) &&  (ste_0_mismatch_8_6_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 1
	ap_uint<1> ste_0_mismatch_9_1 = (lev_distance[1]) &&  (ste_0_mismatch_9_1_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 2
	ap_uint<1> ste_0_mismatch_9_2 = (lev_distance[2]) &&  (ste_0_mismatch_9_2_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 3
	ap_uint<1> ste_0_mismatch_9_3 = (lev_distance[3]) &&  (ste_0_mismatch_9_3_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 4
	ap_uint<1> ste_0_mismatch_9_4 = (lev_distance[4]) &&  (ste_0_mismatch_9_4_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 5
	ap_uint<1> ste_0_mismatch_9_5 = (lev_distance[5]) &&  (ste_0_mismatch_9_5_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 6
	ap_uint<1> ste_0_mismatch_9_6 = (lev_distance[6]) &&  (ste_0_mismatch_9_6_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 1
	ap_uint<1> ste_0_mismatch_10_1 = (lev_distance[1]) &&  (ste_0_mismatch_10_1_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 2
	ap_uint<1> ste_0_mismatch_10_2 = (lev_distance[2]) &&  (ste_0_mismatch_10_2_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 3
	ap_uint<1> ste_0_mismatch_10_3 = (lev_distance[3]) &&  (ste_0_mismatch_10_3_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 4
	ap_uint<1> ste_0_mismatch_10_4 = (lev_distance[4]) &&  (ste_0_mismatch_10_4_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 5
	ap_uint<1> ste_0_mismatch_10_5 = (lev_distance[5]) &&  (ste_0_mismatch_10_5_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 6
	ap_uint<1> ste_0_mismatch_10_6 = (lev_distance[6]) &&  (ste_0_mismatch_10_6_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 1
	ap_uint<1> ste_0_mismatch_11_1 = (lev_distance[1]) &&  (ste_0_mismatch_11_1_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 2
	ap_uint<1> ste_0_mismatch_11_2 = (lev_distance[2]) &&  (ste_0_mismatch_11_2_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 3
	ap_uint<1> ste_0_mismatch_11_3 = (lev_distance[3]) &&  (ste_0_mismatch_11_3_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 4
	ap_uint<1> ste_0_mismatch_11_4 = (lev_distance[4]) &&  (ste_0_mismatch_11_4_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 5
	ap_uint<1> ste_0_mismatch_11_5 = (lev_distance[5]) &&  (ste_0_mismatch_11_5_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 6
	ap_uint<1> ste_0_mismatch_11_6 = (lev_distance[6]) &&  (ste_0_mismatch_11_6_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 1
	ap_uint<1> ste_0_mismatch_12_1 = (lev_distance[1]) &&  (ste_0_mismatch_12_1_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 2
	ap_uint<1> ste_0_mismatch_12_2 = (lev_distance[2]) &&  (ste_0_mismatch_12_2_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 3
	ap_uint<1> ste_0_mismatch_12_3 = (lev_distance[3]) &&  (ste_0_mismatch_12_3_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 4
	ap_uint<1> ste_0_mismatch_12_4 = (lev_distance[4]) &&  (ste_0_mismatch_12_4_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 5
	ap_uint<1> ste_0_mismatch_12_5 = (lev_distance[5]) &&  (ste_0_mismatch_12_5_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 6
	ap_uint<1> ste_0_mismatch_12_6 = (lev_distance[6]) &&  (ste_0_mismatch_12_6_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 1
	ap_uint<1> ste_0_mismatch_13_1 = (lev_distance[1]) &&  (ste_0_mismatch_13_1_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 2
	ap_uint<1> ste_0_mismatch_13_2 = (lev_distance[2]) &&  (ste_0_mismatch_13_2_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 3
	ap_uint<1> ste_0_mismatch_13_3 = (lev_distance[3]) &&  (ste_0_mismatch_13_3_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 4
	ap_uint<1> ste_0_mismatch_13_4 = (lev_distance[4]) &&  (ste_0_mismatch_13_4_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 5
	ap_uint<1> ste_0_mismatch_13_5 = (lev_distance[5]) &&  (ste_0_mismatch_13_5_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 6
	ap_uint<1> ste_0_mismatch_13_6 = (lev_distance[6]) &&  (ste_0_mismatch_13_6_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 1
	ap_uint<1> ste_0_mismatch_14_1 = (lev_distance[1]) &&  (ste_0_mismatch_14_1_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 2
	ap_uint<1> ste_0_mismatch_14_2 = (lev_distance[2]) &&  (ste_0_mismatch_14_2_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 3
	ap_uint<1> ste_0_mismatch_14_3 = (lev_distance[3]) &&  (ste_0_mismatch_14_3_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 4
	ap_uint<1> ste_0_mismatch_14_4 = (lev_distance[4]) &&  (ste_0_mismatch_14_4_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 5
	ap_uint<1> ste_0_mismatch_14_5 = (lev_distance[5]) &&  (ste_0_mismatch_14_5_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 6
	ap_uint<1> ste_0_mismatch_14_6 = (lev_distance[6]) &&  (ste_0_mismatch_14_6_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 1
	ap_uint<1> ste_0_mismatch_15_1 = (lev_distance[1]) &&  (ste_0_mismatch_15_1_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 2
	ap_uint<1> ste_0_mismatch_15_2 = (lev_distance[2]) &&  (ste_0_mismatch_15_2_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 3
	ap_uint<1> ste_0_mismatch_15_3 = (lev_distance[3]) &&  (ste_0_mismatch_15_3_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 4
	ap_uint<1> ste_0_mismatch_15_4 = (lev_distance[4]) &&  (ste_0_mismatch_15_4_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 5
	ap_uint<1> ste_0_mismatch_15_5 = (lev_distance[5]) &&  (ste_0_mismatch_15_5_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 6
	ap_uint<1> ste_0_mismatch_15_6 = (lev_distance[6]) &&  (ste_0_mismatch_15_6_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 1
	ap_uint<1> ste_0_mismatch_16_1 = (lev_distance[1]) &&  (ste_0_mismatch_16_1_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 2
	ap_uint<1> ste_0_mismatch_16_2 = (lev_distance[2]) &&  (ste_0_mismatch_16_2_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 3
	ap_uint<1> ste_0_mismatch_16_3 = (lev_distance[3]) &&  (ste_0_mismatch_16_3_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 4
	ap_uint<1> ste_0_mismatch_16_4 = (lev_distance[4]) &&  (ste_0_mismatch_16_4_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 5
	ap_uint<1> ste_0_mismatch_16_5 = (lev_distance[5]) &&  (ste_0_mismatch_16_5_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 6
	ap_uint<1> ste_0_mismatch_16_6 = (lev_distance[6]) &&  (ste_0_mismatch_16_6_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 1
	ap_uint<1> ste_0_mismatch_17_1 = (lev_distance[1]) &&  (ste_0_mismatch_17_1_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 2
	ap_uint<1> ste_0_mismatch_17_2 = (lev_distance[2]) &&  (ste_0_mismatch_17_2_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 3
	ap_uint<1> ste_0_mismatch_17_3 = (lev_distance[3]) &&  (ste_0_mismatch_17_3_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 4
	ap_uint<1> ste_0_mismatch_17_4 = (lev_distance[4]) &&  (ste_0_mismatch_17_4_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 5
	ap_uint<1> ste_0_mismatch_17_5 = (lev_distance[5]) &&  (ste_0_mismatch_17_5_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 6
	ap_uint<1> ste_0_mismatch_17_6 = (lev_distance[6]) &&  (ste_0_mismatch_17_6_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 1
	ap_uint<1> ste_0_mismatch_18_1 = (lev_distance[1]) &&  (ste_0_mismatch_18_1_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 2
	ap_uint<1> ste_0_mismatch_18_2 = (lev_distance[2]) &&  (ste_0_mismatch_18_2_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 3
	ap_uint<1> ste_0_mismatch_18_3 = (lev_distance[3]) &&  (ste_0_mismatch_18_3_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 4
	ap_uint<1> ste_0_mismatch_18_4 = (lev_distance[4]) &&  (ste_0_mismatch_18_4_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 5
	ap_uint<1> ste_0_mismatch_18_5 = (lev_distance[5]) &&  (ste_0_mismatch_18_5_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 6
	ap_uint<1> ste_0_mismatch_18_6 = (lev_distance[6]) &&  (ste_0_mismatch_18_6_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 1
	ap_uint<1> ste_0_mismatch_19_1 = (lev_distance[1]) &&  (ste_0_mismatch_19_1_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 2
	ap_uint<1> ste_0_mismatch_19_2 = (lev_distance[2]) &&  (ste_0_mismatch_19_2_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 3
	ap_uint<1> ste_0_mismatch_19_3 = (lev_distance[3]) &&  (ste_0_mismatch_19_3_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 4
	ap_uint<1> ste_0_mismatch_19_4 = (lev_distance[4]) &&  (ste_0_mismatch_19_4_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 5
	ap_uint<1> ste_0_mismatch_19_5 = (lev_distance[5]) &&  (ste_0_mismatch_19_5_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 6
	ap_uint<1> ste_0_mismatch_19_6 = (lev_distance[6] ) &&  (ste_0_mismatch_19_6_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 1
	ap_uint<1> ste_0_mismatch_1_1 = (lev_distance[1]) &&  (ste_0_mismatch_1_1_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 2
	ap_uint<1> ste_0_mismatch_1_2 = (lev_distance[2]) &&  (ste_0_mismatch_1_2_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 3
	ap_uint<1> ste_0_mismatch_1_3 = (lev_distance[3]) &&  (ste_0_mismatch_1_3_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 4
	ap_uint<1> ste_0_mismatch_1_4 = (lev_distance[4]) &&  (ste_0_mismatch_1_4_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 5
	ap_uint<1> ste_0_mismatch_1_5 = (lev_distance[5]) &&  (ste_0_mismatch_1_5_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 6
	ap_uint<1> ste_0_mismatch_1_6 = (lev_distance[6]) &&  (ste_0_mismatch_1_6_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 1
	ap_uint<1> ste_0_mismatch_20_1 = (lev_distance[1]) &&  (ste_0_mismatch_20_1_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 2
	ap_uint<1> ste_0_mismatch_20_2 = (lev_distance[2]) &&  (ste_0_mismatch_20_2_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 3
	ap_uint<1> ste_0_mismatch_20_3 = (lev_distance[3]) &&  (ste_0_mismatch_20_3_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 4
	ap_uint<1> ste_0_mismatch_20_4 = (lev_distance[4]) &&  (ste_0_mismatch_20_4_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 5
	ap_uint<1> ste_0_mismatch_20_5 = (lev_distance[5]) &&  (ste_0_mismatch_20_5_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 6
	ap_uint<1> ste_0_mismatch_20_6 = (lev_distance[6]) &&  (ste_0_mismatch_20_6_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 1
	ap_uint<1> ste_0_mismatch_21_1 = (lev_distance[1]) &&  (ste_0_mismatch_21_1_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 2
	ap_uint<1> ste_0_mismatch_21_2 = (lev_distance[2]) &&  (ste_0_mismatch_21_2_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 3
	ap_uint<1> ste_0_mismatch_21_3 = (lev_distance[3]) &&  (ste_0_mismatch_21_3_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 4
	ap_uint<1> ste_0_mismatch_21_4 = (lev_distance[4]) &&  (ste_0_mismatch_21_4_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 5
	ap_uint<1> ste_0_mismatch_21_5 = (lev_distance[5]) &&  (ste_0_mismatch_21_5_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 6
	ap_uint<1> ste_0_mismatch_21_6 = (lev_distance[6]) &&  (ste_0_mismatch_21_6_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 1
	ap_uint<1> ste_0_mismatch_22_1 = (lev_distance[1]) &&  (ste_0_mismatch_22_1_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 2
	ap_uint<1> ste_0_mismatch_22_2 = (lev_distance[2]) &&  (ste_0_mismatch_22_2_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 3
	ap_uint<1> ste_0_mismatch_22_3 = (lev_distance[3]) &&  (ste_0_mismatch_22_3_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 4
	ap_uint<1> ste_0_mismatch_22_4 = (lev_distance[4]) &&  (ste_0_mismatch_22_4_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 5
	ap_uint<1> ste_0_mismatch_22_5 = (lev_distance[5]) &&  (ste_0_mismatch_22_5_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 6
	ap_uint<1> ste_0_mismatch_22_6 = (lev_distance[6]) &&  (ste_0_mismatch_22_6_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 1
	ap_uint<1> ste_0_mismatch_23_1 = (lev_distance[1]) &&  (ste_0_mismatch_23_1_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 2
	ap_uint<1> ste_0_mismatch_23_2 = (lev_distance[2]) &&  (ste_0_mismatch_23_2_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 3
	ap_uint<1> ste_0_mismatch_23_3 = (lev_distance[3]) &&  (ste_0_mismatch_23_3_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 4
	ap_uint<1> ste_0_mismatch_23_4 = (lev_distance[4]) &&  (ste_0_mismatch_23_4_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 5
	ap_uint<1> ste_0_mismatch_23_5 = (lev_distance[5]) &&  (ste_0_mismatch_23_5_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));
	// Edit distance: 6
	ap_uint<1> ste_0_mismatch_23_6 = (lev_distance[6]) &&  (ste_0_mismatch_23_6_enable) && (((input_r == 65) || (input_r == 67) || (input_r == 71) || (input_r == 84)));

	// Edges
	input_r = input;
	ste_0_match_1_0_enable = start_state;
	ste_0_match_1_1_enable = (ste_0_mismatch_0_1);
	ste_0_match_1_2_enable = (ste_0_mismatch_0_2);
	ste_0_match_1_3_enable = (ste_0_mismatch_0_3);
	ste_0_match_1_4_enable = (ste_0_mismatch_0_4);
	ste_0_match_1_5_enable = (ste_0_mismatch_0_5);
	ste_0_match_1_6_enable = (ste_0_mismatch_0_6);
	ste_0_match_2_0_enable = (ste_0_match_1_0);
	ste_0_match_2_1_enable = start_state;
	ste_0_match_2_2_enable = (ste_0_match_1_2 || ste_0_mismatch_0_1 || ste_0_mismatch_1_2);
	ste_0_match_2_3_enable = (ste_0_match_1_3 || ste_0_mismatch_0_2 || ste_0_mismatch_1_3);
	ste_0_match_2_4_enable = (ste_0_match_1_4 || ste_0_mismatch_0_3 || ste_0_mismatch_1_4);
	ste_0_match_2_5_enable = (ste_0_match_1_5 || ste_0_mismatch_0_4 || ste_0_mismatch_1_5);
	ste_0_match_2_6_enable = (ste_0_match_1_6 || ste_0_mismatch_0_5 || ste_0_mismatch_1_6);
	ste_0_match_3_0_enable = (ste_0_match_2_0);
	ste_0_match_3_1_enable = (ste_0_match_1_0 || ste_0_match_2_1 || ste_0_mismatch_2_1);
	ste_0_match_3_2_enable = start_state;
	ste_0_match_3_3_enable = (ste_0_match_1_2 || ste_0_match_2_3 || ste_0_mismatch_0_1 || ste_0_mismatch_1_2 || ste_0_mismatch_2_3);
	ste_0_match_3_4_enable = (ste_0_match_1_3 || ste_0_match_2_4 || ste_0_mismatch_0_2 || ste_0_mismatch_1_3 || ste_0_mismatch_2_4);
	ste_0_match_3_5_enable = (ste_0_match_1_4 || ste_0_match_2_5 || ste_0_mismatch_0_3 || ste_0_mismatch_1_4 || ste_0_mismatch_2_5);
	ste_0_match_3_6_enable = (ste_0_match_1_5 || ste_0_match_2_6 || ste_0_mismatch_0_4 || ste_0_mismatch_1_5 || ste_0_mismatch_2_6);
	ste_0_match_4_0_enable = (ste_0_match_3_0);
	ste_0_match_4_1_enable = (ste_0_match_2_0 || ste_0_match_3_1 || ste_0_mismatch_3_1);
	ste_0_match_4_2_enable = (ste_0_match_1_0 || ste_0_match_2_1 || ste_0_match_3_2 || ste_0_mismatch_2_1 || ste_0_mismatch_3_2);
	ste_0_match_4_3_enable = start_state;
	ste_0_match_4_4_enable = (ste_0_match_1_2 || ste_0_match_2_3 || ste_0_match_3_4 || ste_0_mismatch_0_1 || ste_0_mismatch_1_2 || ste_0_mismatch_2_3 || ste_0_mismatch_3_4);
	ste_0_match_4_5_enable = (ste_0_match_1_3 || ste_0_match_2_4 || ste_0_match_3_5 || ste_0_mismatch_0_2 || ste_0_mismatch_1_3 || ste_0_mismatch_2_4 || ste_0_mismatch_3_5);
	ste_0_match_4_6_enable = (ste_0_match_1_4 || ste_0_match_2_5 || ste_0_match_3_6 || ste_0_mismatch_0_3 || ste_0_mismatch_1_4 || ste_0_mismatch_2_5 || ste_0_mismatch_3_6);
	ste_0_match_5_0_enable = (ste_0_match_4_0);
	ste_0_match_5_1_enable = (ste_0_match_3_0 || ste_0_match_4_1 || ste_0_mismatch_4_1);
	ste_0_match_5_2_enable = (ste_0_match_2_0 || ste_0_match_3_1 || ste_0_match_4_2 || ste_0_mismatch_3_1 || ste_0_mismatch_4_2);
	ste_0_match_5_3_enable = (ste_0_match_1_0 || ste_0_match_2_1 || ste_0_match_3_2 || ste_0_match_4_3 || ste_0_mismatch_2_1 || ste_0_mismatch_3_2 || ste_0_mismatch_4_3);
	ste_0_match_5_4_enable = start_state;
	ste_0_match_5_5_enable = (ste_0_match_1_2 || ste_0_match_2_3 || ste_0_match_3_4 || ste_0_match_4_5 || ste_0_mismatch_0_1 || ste_0_mismatch_1_2 || ste_0_mismatch_2_3 || ste_0_mismatch_3_4 || ste_0_mismatch_4_5);
	ste_0_match_5_6_enable = (ste_0_match_1_3 || ste_0_match_2_4 || ste_0_match_3_5 || ste_0_match_4_6 || ste_0_mismatch_0_2 || ste_0_mismatch_1_3 || ste_0_mismatch_2_4 || ste_0_mismatch_3_5 || ste_0_mismatch_4_6);
	ste_0_match_6_0_enable = (ste_0_match_5_0);
	ste_0_match_6_1_enable = (ste_0_match_4_0 || ste_0_match_5_1 || ste_0_mismatch_5_1);
	ste_0_match_6_2_enable = (ste_0_match_3_0 || ste_0_match_4_1 || ste_0_match_5_2 || ste_0_mismatch_4_1 || ste_0_mismatch_5_2);
	ste_0_match_6_3_enable = (ste_0_match_2_0 || ste_0_match_3_1 || ste_0_match_4_2 || ste_0_match_5_3 || ste_0_mismatch_3_1 || ste_0_mismatch_4_2 || ste_0_mismatch_5_3);
	ste_0_match_6_4_enable = (ste_0_match_1_0 || ste_0_match_2_1 || ste_0_match_3_2 || ste_0_match_4_3 || ste_0_match_5_4 || ste_0_mismatch_2_1 || ste_0_mismatch_3_2 || ste_0_mismatch_4_3 || ste_0_mismatch_5_4);
	ste_0_match_6_5_enable = start_state;
	ste_0_match_6_6_enable = (ste_0_match_1_2 || ste_0_match_2_3 || ste_0_match_3_4 || ste_0_match_4_5 || ste_0_match_5_6 || ste_0_mismatch_0_1 || ste_0_mismatch_1_2 || ste_0_mismatch_2_3 || ste_0_mismatch_3_4 || ste_0_mismatch_4_5 || ste_0_mismatch_5_6);
	ste_0_match_7_0_enable = (ste_0_match_6_0);
	ste_0_match_7_1_enable = (ste_0_match_5_0 || ste_0_match_6_1 || ste_0_mismatch_6_1);
	ste_0_match_7_2_enable = (ste_0_match_4_0 || ste_0_match_5_1 || ste_0_match_6_2 || ste_0_mismatch_5_1 || ste_0_mismatch_6_2);
	ste_0_match_7_3_enable = (ste_0_match_3_0 || ste_0_match_4_1 || ste_0_match_5_2 || ste_0_match_6_3 || ste_0_mismatch_4_1 || ste_0_mismatch_5_2 || ste_0_mismatch_6_3);
	ste_0_match_7_4_enable = (ste_0_match_2_0 || ste_0_match_3_1 || ste_0_match_4_2 || ste_0_match_5_3 || ste_0_match_6_4 || ste_0_mismatch_3_1 || ste_0_mismatch_4_2 || ste_0_mismatch_5_3 || ste_0_mismatch_6_4);
	ste_0_match_7_5_enable = (ste_0_match_1_0 || ste_0_match_2_1 || ste_0_match_3_2 || ste_0_match_4_3 || ste_0_match_5_4 || ste_0_match_6_5 || ste_0_mismatch_2_1 || ste_0_mismatch_3_2 || ste_0_mismatch_4_3 || ste_0_mismatch_5_4 || ste_0_mismatch_6_5);
	ste_0_match_7_6_enable = start_state;
	ste_0_match_8_0_enable = (ste_0_match_7_0);
	ste_0_match_8_1_enable = (ste_0_match_6_0 || ste_0_match_7_1 || ste_0_mismatch_7_1);
	ste_0_match_8_2_enable = (ste_0_match_5_0 || ste_0_match_6_1 || ste_0_match_7_2 || ste_0_mismatch_6_1 || ste_0_mismatch_7_2);
	ste_0_match_8_3_enable = (ste_0_match_4_0 || ste_0_match_5_1 || ste_0_match_6_2 || ste_0_match_7_3 || ste_0_mismatch_5_1 || ste_0_mismatch_6_2 || ste_0_mismatch_7_3);
	ste_0_match_8_4_enable = (ste_0_match_3_0 || ste_0_match_4_1 || ste_0_match_5_2 || ste_0_match_6_3 || ste_0_match_7_4 || ste_0_mismatch_4_1 || ste_0_mismatch_5_2 || ste_0_mismatch_6_3 || ste_0_mismatch_7_4);
	ste_0_match_8_5_enable = (ste_0_match_2_0 || ste_0_match_3_1 || ste_0_match_4_2 || ste_0_match_5_3 || ste_0_match_6_4 || ste_0_match_7_5 || ste_0_mismatch_3_1 || ste_0_mismatch_4_2 || ste_0_mismatch_5_3 || ste_0_mismatch_6_4 || ste_0_mismatch_7_5);
	ste_0_match_8_6_enable = (ste_0_match_1_0 || ste_0_match_2_1 || ste_0_match_3_2 || ste_0_match_4_3 || ste_0_match_5_4 || ste_0_match_6_5 || ste_0_match_7_6 || ste_0_mismatch_2_1 || ste_0_mismatch_3_2 || ste_0_mismatch_4_3 || ste_0_mismatch_5_4 || ste_0_mismatch_6_5 || ste_0_mismatch_7_6);
	ste_0_match_9_0_enable = (ste_0_match_8_0);
	ste_0_match_9_1_enable = (ste_0_match_7_0 || ste_0_match_8_1 || ste_0_mismatch_8_1);
	ste_0_match_9_2_enable = (ste_0_match_6_0 || ste_0_match_7_1 || ste_0_match_8_2 || ste_0_mismatch_7_1 || ste_0_mismatch_8_2);
	ste_0_match_9_3_enable = (ste_0_match_5_0 || ste_0_match_6_1 || ste_0_match_7_2 || ste_0_match_8_3 || ste_0_mismatch_6_1 || ste_0_mismatch_7_2 || ste_0_mismatch_8_3);
	ste_0_match_9_4_enable = (ste_0_match_4_0 || ste_0_match_5_1 || ste_0_match_6_2 || ste_0_match_7_3 || ste_0_match_8_4 || ste_0_mismatch_5_1 || ste_0_mismatch_6_2 || ste_0_mismatch_7_3 || ste_0_mismatch_8_4);
	ste_0_match_9_5_enable = (ste_0_match_3_0 || ste_0_match_4_1 || ste_0_match_5_2 || ste_0_match_6_3 || ste_0_match_7_4 || ste_0_match_8_5 || ste_0_mismatch_4_1 || ste_0_mismatch_5_2 || ste_0_mismatch_6_3 || ste_0_mismatch_7_4 || ste_0_mismatch_8_5);
	ste_0_match_9_6_enable = (ste_0_match_2_0 || ste_0_match_3_1 || ste_0_match_4_2 || ste_0_match_5_3 || ste_0_match_6_4 || ste_0_match_7_5 || ste_0_match_8_6 || ste_0_mismatch_3_1 || ste_0_mismatch_4_2 || ste_0_mismatch_5_3 || ste_0_mismatch_6_4 || ste_0_mismatch_7_5 || ste_0_mismatch_8_6);
	ste_0_match_10_0_enable = (ste_0_match_9_0);
	ste_0_match_10_1_enable = (ste_0_match_8_0 || ste_0_match_9_1 || ste_0_mismatch_9_1);
	ste_0_match_10_2_enable = (ste_0_match_7_0 || ste_0_match_8_1 || ste_0_match_9_2 || ste_0_mismatch_8_1 || ste_0_mismatch_9_2);
	ste_0_match_10_3_enable = (ste_0_match_6_0 || ste_0_match_7_1 || ste_0_match_8_2 || ste_0_match_9_3 || ste_0_mismatch_7_1 || ste_0_mismatch_8_2 || ste_0_mismatch_9_3);
	ste_0_match_10_4_enable = (ste_0_match_5_0 || ste_0_match_6_1 || ste_0_match_7_2 || ste_0_match_8_3 || ste_0_match_9_4 || ste_0_mismatch_6_1 || ste_0_mismatch_7_2 || ste_0_mismatch_8_3 || ste_0_mismatch_9_4);
	ste_0_match_10_5_enable = (ste_0_match_4_0 || ste_0_match_5_1 || ste_0_match_6_2 || ste_0_match_7_3 || ste_0_match_8_4 || ste_0_match_9_5 || ste_0_mismatch_5_1 || ste_0_mismatch_6_2 || ste_0_mismatch_7_3 || ste_0_mismatch_8_4 || ste_0_mismatch_9_5);
	ste_0_match_10_6_enable = (ste_0_match_3_0 || ste_0_match_4_1 || ste_0_match_5_2 || ste_0_match_6_3 || ste_0_match_7_4 || ste_0_match_8_5 || ste_0_match_9_6 || ste_0_mismatch_4_1 || ste_0_mismatch_5_2 || ste_0_mismatch_6_3 || ste_0_mismatch_7_4 || ste_0_mismatch_8_5 || ste_0_mismatch_9_6);
	ste_0_match_11_0_enable = (ste_0_match_10_0);
	ste_0_match_11_1_enable = (ste_0_match_10_1 || ste_0_match_9_0 || ste_0_mismatch_10_1);
	ste_0_match_11_2_enable = (ste_0_match_10_2 || ste_0_match_8_0 || ste_0_match_9_1 || ste_0_mismatch_10_2 || ste_0_mismatch_9_1);
	ste_0_match_11_3_enable = (ste_0_match_10_3 || ste_0_match_7_0 || ste_0_match_8_1 || ste_0_match_9_2 || ste_0_mismatch_10_3 || ste_0_mismatch_8_1 || ste_0_mismatch_9_2);
	ste_0_match_11_4_enable = (ste_0_match_10_4 || ste_0_match_6_0 || ste_0_match_7_1 || ste_0_match_8_2 || ste_0_match_9_3 || ste_0_mismatch_10_4 || ste_0_mismatch_7_1 || ste_0_mismatch_8_2 || ste_0_mismatch_9_3);
	ste_0_match_11_5_enable = (ste_0_match_10_5 || ste_0_match_5_0 || ste_0_match_6_1 || ste_0_match_7_2 || ste_0_match_8_3 || ste_0_match_9_4 || ste_0_mismatch_10_5 || ste_0_mismatch_6_1 || ste_0_mismatch_7_2 || ste_0_mismatch_8_3 || ste_0_mismatch_9_4);
	ste_0_match_11_6_enable = (ste_0_match_10_6 || ste_0_match_4_0 || ste_0_match_5_1 || ste_0_match_6_2 || ste_0_match_7_3 || ste_0_match_8_4 || ste_0_match_9_5 || ste_0_mismatch_10_6 || ste_0_mismatch_5_1 || ste_0_mismatch_6_2 || ste_0_mismatch_7_3 || ste_0_mismatch_8_4 || ste_0_mismatch_9_5);
	ste_0_match_12_0_enable = (ste_0_match_11_0);
	ste_0_match_12_1_enable = (ste_0_match_10_0 || ste_0_match_11_1 || ste_0_mismatch_11_1);
	ste_0_match_12_2_enable = (ste_0_match_10_1 || ste_0_match_11_2 || ste_0_match_9_0 || ste_0_mismatch_10_1 || ste_0_mismatch_11_2);
	ste_0_match_12_3_enable = (ste_0_match_10_2 || ste_0_match_11_3 || ste_0_match_8_0 || ste_0_match_9_1 || ste_0_mismatch_10_2 || ste_0_mismatch_11_3 || ste_0_mismatch_9_1);
	ste_0_match_12_4_enable = (ste_0_match_10_3 || ste_0_match_11_4 || ste_0_match_7_0 || ste_0_match_8_1 || ste_0_match_9_2 || ste_0_mismatch_10_3 || ste_0_mismatch_11_4 || ste_0_mismatch_8_1 || ste_0_mismatch_9_2);
	ste_0_match_12_5_enable = (ste_0_match_10_4 || ste_0_match_11_5 || ste_0_match_6_0 || ste_0_match_7_1 || ste_0_match_8_2 || ste_0_match_9_3 || ste_0_mismatch_10_4 || ste_0_mismatch_11_5 || ste_0_mismatch_7_1 || ste_0_mismatch_8_2 || ste_0_mismatch_9_3);
	ste_0_match_12_6_enable = (ste_0_match_10_5 || ste_0_match_11_6 || ste_0_match_5_0 || ste_0_match_6_1 || ste_0_match_7_2 || ste_0_match_8_3 || ste_0_match_9_4 || ste_0_mismatch_10_5 || ste_0_mismatch_11_6 || ste_0_mismatch_6_1 || ste_0_mismatch_7_2 || ste_0_mismatch_8_3 || ste_0_mismatch_9_4);
	ste_0_match_13_0_enable = (ste_0_match_12_0);
	ste_0_match_13_1_enable = (ste_0_match_11_0 || ste_0_match_12_1 || ste_0_mismatch_12_1);
	ste_0_match_13_2_enable = (ste_0_match_10_0 || ste_0_match_11_1 || ste_0_match_12_2 || ste_0_mismatch_11_1 || ste_0_mismatch_12_2);
	ste_0_match_13_3_enable = (ste_0_match_10_1 || ste_0_match_11_2 || ste_0_match_12_3 || ste_0_match_9_0 || ste_0_mismatch_10_1 || ste_0_mismatch_11_2 || ste_0_mismatch_12_3);
	ste_0_match_13_4_enable = (ste_0_match_10_2 || ste_0_match_11_3 || ste_0_match_12_4 || ste_0_match_8_0 || ste_0_match_9_1 || ste_0_mismatch_10_2 || ste_0_mismatch_11_3 || ste_0_mismatch_12_4 || ste_0_mismatch_9_1);
	ste_0_match_13_5_enable = (ste_0_match_10_3 || ste_0_match_11_4 || ste_0_match_12_5 || ste_0_match_7_0 || ste_0_match_8_1 || ste_0_match_9_2 || ste_0_mismatch_10_3 || ste_0_mismatch_11_4 || ste_0_mismatch_12_5 || ste_0_mismatch_8_1 || ste_0_mismatch_9_2);
	ste_0_match_13_6_enable = (ste_0_match_10_4 || ste_0_match_11_5 || ste_0_match_12_6 || ste_0_match_6_0 || ste_0_match_7_1 || ste_0_match_8_2 || ste_0_match_9_3 || ste_0_mismatch_10_4 || ste_0_mismatch_11_5 || ste_0_mismatch_12_6 || ste_0_mismatch_7_1 || ste_0_mismatch_8_2 || ste_0_mismatch_9_3);
	ste_0_match_14_0_enable = (ste_0_match_13_0);
	ste_0_match_14_1_enable = (ste_0_match_12_0 || ste_0_match_13_1 || ste_0_mismatch_13_1);
	ste_0_match_14_2_enable = (ste_0_match_11_0 || ste_0_match_12_1 || ste_0_match_13_2 || ste_0_mismatch_12_1 || ste_0_mismatch_13_2);
	ste_0_match_14_3_enable = (ste_0_match_10_0 || ste_0_match_11_1 || ste_0_match_12_2 || ste_0_match_13_3 || ste_0_mismatch_11_1 || ste_0_mismatch_12_2 || ste_0_mismatch_13_3);
	ste_0_match_14_4_enable = (ste_0_match_10_1 || ste_0_match_11_2 || ste_0_match_12_3 || ste_0_match_13_4 || ste_0_match_9_0 || ste_0_mismatch_10_1 || ste_0_mismatch_11_2 || ste_0_mismatch_12_3 || ste_0_mismatch_13_4);
	ste_0_match_14_5_enable = (ste_0_match_10_2 || ste_0_match_11_3 || ste_0_match_12_4 || ste_0_match_13_5 || ste_0_match_8_0 || ste_0_match_9_1 || ste_0_mismatch_10_2 || ste_0_mismatch_11_3 || ste_0_mismatch_12_4 || ste_0_mismatch_13_5 || ste_0_mismatch_9_1);
	ste_0_match_14_6_enable = (ste_0_match_10_3 || ste_0_match_11_4 || ste_0_match_12_5 || ste_0_match_13_6 || ste_0_match_7_0 || ste_0_match_8_1 || ste_0_match_9_2 || ste_0_mismatch_10_3 || ste_0_mismatch_11_4 || ste_0_mismatch_12_5 || ste_0_mismatch_13_6 || ste_0_mismatch_8_1 || ste_0_mismatch_9_2);
	ste_0_match_15_0_enable = (ste_0_match_14_0);
	ste_0_match_15_1_enable = (ste_0_match_13_0 || ste_0_match_14_1 || ste_0_mismatch_14_1);
	ste_0_match_15_2_enable = (ste_0_match_12_0 || ste_0_match_13_1 || ste_0_match_14_2 || ste_0_mismatch_13_1 || ste_0_mismatch_14_2);
	ste_0_match_15_3_enable = (ste_0_match_11_0 || ste_0_match_12_1 || ste_0_match_13_2 || ste_0_match_14_3 || ste_0_mismatch_12_1 || ste_0_mismatch_13_2 || ste_0_mismatch_14_3);
	ste_0_match_15_4_enable = (ste_0_match_10_0 || ste_0_match_11_1 || ste_0_match_12_2 || ste_0_match_13_3 || ste_0_match_14_4 || ste_0_mismatch_11_1 || ste_0_mismatch_12_2 || ste_0_mismatch_13_3 || ste_0_mismatch_14_4);
	ste_0_match_15_5_enable = (ste_0_match_10_1 || ste_0_match_11_2 || ste_0_match_12_3 || ste_0_match_13_4 || ste_0_match_14_5 || ste_0_match_9_0 || ste_0_mismatch_10_1 || ste_0_mismatch_11_2 || ste_0_mismatch_12_3 || ste_0_mismatch_13_4 || ste_0_mismatch_14_5);
	ste_0_match_15_6_enable = (ste_0_match_10_2 || ste_0_match_11_3 || ste_0_match_12_4 || ste_0_match_13_5 || ste_0_match_14_6 || ste_0_match_8_0 || ste_0_match_9_1 || ste_0_mismatch_10_2 || ste_0_mismatch_11_3 || ste_0_mismatch_12_4 || ste_0_mismatch_13_5 || ste_0_mismatch_14_6 || ste_0_mismatch_9_1);
	ste_0_match_16_0_enable = (ste_0_match_15_0);
	ste_0_match_16_1_enable = (ste_0_match_14_0 || ste_0_match_15_1 || ste_0_mismatch_15_1);
	ste_0_match_16_2_enable = (ste_0_match_13_0 || ste_0_match_14_1 || ste_0_match_15_2 || ste_0_mismatch_14_1 || ste_0_mismatch_15_2);
	ste_0_match_16_3_enable = (ste_0_match_12_0 || ste_0_match_13_1 || ste_0_match_14_2 || ste_0_match_15_3 || ste_0_mismatch_13_1 || ste_0_mismatch_14_2 || ste_0_mismatch_15_3);
	ste_0_match_16_4_enable = (ste_0_match_11_0 || ste_0_match_12_1 || ste_0_match_13_2 || ste_0_match_14_3 || ste_0_match_15_4 || ste_0_mismatch_12_1 || ste_0_mismatch_13_2 || ste_0_mismatch_14_3 || ste_0_mismatch_15_4);
	ste_0_match_16_5_enable = (ste_0_match_10_0 || ste_0_match_11_1 || ste_0_match_12_2 || ste_0_match_13_3 || ste_0_match_14_4 || ste_0_match_15_5 || ste_0_mismatch_11_1 || ste_0_mismatch_12_2 || ste_0_mismatch_13_3 || ste_0_mismatch_14_4 || ste_0_mismatch_15_5);
	ste_0_match_16_6_enable = (ste_0_match_10_1 || ste_0_match_11_2 || ste_0_match_12_3 || ste_0_match_13_4 || ste_0_match_14_5 || ste_0_match_15_6 || ste_0_match_9_0 || ste_0_mismatch_10_1 || ste_0_mismatch_11_2 || ste_0_mismatch_12_3 || ste_0_mismatch_13_4 || ste_0_mismatch_14_5 || ste_0_mismatch_15_6);
	ste_0_match_17_0_enable = (ste_0_match_16_0);
	ste_0_match_17_1_enable = (ste_0_match_15_0 || ste_0_match_16_1 || ste_0_mismatch_16_1);
	ste_0_match_17_2_enable = (ste_0_match_14_0 || ste_0_match_15_1 || ste_0_match_16_2 || ste_0_mismatch_15_1 || ste_0_mismatch_16_2);
	ste_0_match_17_3_enable = (ste_0_match_13_0 || ste_0_match_14_1 || ste_0_match_15_2 || ste_0_match_16_3 || ste_0_mismatch_14_1 || ste_0_mismatch_15_2 || ste_0_mismatch_16_3);
	ste_0_match_17_4_enable = (ste_0_match_12_0 || ste_0_match_13_1 || ste_0_match_14_2 || ste_0_match_15_3 || ste_0_match_16_4 || ste_0_mismatch_13_1 || ste_0_mismatch_14_2 || ste_0_mismatch_15_3 || ste_0_mismatch_16_4);
	ste_0_match_17_5_enable = (ste_0_match_11_0 || ste_0_match_12_1 || ste_0_match_13_2 || ste_0_match_14_3 || ste_0_match_15_4 || ste_0_match_16_5 || ste_0_mismatch_12_1 || ste_0_mismatch_13_2 || ste_0_mismatch_14_3 || ste_0_mismatch_15_4 || ste_0_mismatch_16_5);
	ste_0_match_17_6_enable = (ste_0_match_10_0 || ste_0_match_11_1 || ste_0_match_12_2 || ste_0_match_13_3 || ste_0_match_14_4 || ste_0_match_15_5 || ste_0_match_16_6 || ste_0_mismatch_11_1 || ste_0_mismatch_12_2 || ste_0_mismatch_13_3 || ste_0_mismatch_14_4 || ste_0_mismatch_15_5 || ste_0_mismatch_16_6);
	ste_0_match_18_0_enable = (ste_0_match_17_0);
	ste_0_match_18_1_enable = (ste_0_match_16_0 || ste_0_match_17_1 || ste_0_mismatch_17_1);
	ste_0_match_18_2_enable = (ste_0_match_15_0 || ste_0_match_16_1 || ste_0_match_17_2 || ste_0_mismatch_16_1 || ste_0_mismatch_17_2);
	ste_0_match_18_3_enable = (ste_0_match_14_0 || ste_0_match_15_1 || ste_0_match_16_2 || ste_0_match_17_3 || ste_0_mismatch_15_1 || ste_0_mismatch_16_2 || ste_0_mismatch_17_3);
	ste_0_match_18_4_enable = (ste_0_match_13_0 || ste_0_match_14_1 || ste_0_match_15_2 || ste_0_match_16_3 || ste_0_match_17_4 || ste_0_mismatch_14_1 || ste_0_mismatch_15_2 || ste_0_mismatch_16_3 || ste_0_mismatch_17_4);
	ste_0_match_18_5_enable = (ste_0_match_12_0 || ste_0_match_13_1 || ste_0_match_14_2 || ste_0_match_15_3 || ste_0_match_16_4 || ste_0_match_17_5 || ste_0_mismatch_13_1 || ste_0_mismatch_14_2 || ste_0_mismatch_15_3 || ste_0_mismatch_16_4 || ste_0_mismatch_17_5);
	ste_0_match_18_6_enable = (ste_0_match_11_0 || ste_0_match_12_1 || ste_0_match_13_2 || ste_0_match_14_3 || ste_0_match_15_4 || ste_0_match_16_5 || ste_0_match_17_6 || ste_0_mismatch_12_1 || ste_0_mismatch_13_2 || ste_0_mismatch_14_3 || ste_0_mismatch_15_4 || ste_0_mismatch_16_5 || ste_0_mismatch_17_6);
	ste_0_match_19_0_enable = (ste_0_match_18_0);
	ste_0_match_19_1_enable = (ste_0_match_17_0 || ste_0_match_18_1 || ste_0_mismatch_18_1);
	ste_0_match_19_2_enable = (ste_0_match_16_0 || ste_0_match_17_1 || ste_0_match_18_2 || ste_0_mismatch_17_1 || ste_0_mismatch_18_2);
	ste_0_match_19_3_enable = (ste_0_match_15_0 || ste_0_match_16_1 || ste_0_match_17_2 || ste_0_match_18_3 || ste_0_mismatch_16_1 || ste_0_mismatch_17_2 || ste_0_mismatch_18_3);
	ste_0_match_19_4_enable = (ste_0_match_14_0 || ste_0_match_15_1 || ste_0_match_16_2 || ste_0_match_17_3 || ste_0_match_18_4 || ste_0_mismatch_15_1 || ste_0_mismatch_16_2 || ste_0_mismatch_17_3 || ste_0_mismatch_18_4);
	ste_0_match_19_5_enable = (ste_0_match_13_0 || ste_0_match_14_1 || ste_0_match_15_2 || ste_0_match_16_3 || ste_0_match_17_4 || ste_0_match_18_5 || ste_0_mismatch_14_1 || ste_0_mismatch_15_2 || ste_0_mismatch_16_3 || ste_0_mismatch_17_4 || ste_0_mismatch_18_5);
	ste_0_match_19_6_enable = (ste_0_match_12_0 || ste_0_match_13_1 || ste_0_match_14_2 || ste_0_match_15_3 || ste_0_match_16_4 || ste_0_match_17_5 || ste_0_match_18_6 || ste_0_mismatch_13_1 || ste_0_mismatch_14_2 || ste_0_mismatch_15_3 || ste_0_mismatch_16_4 || ste_0_mismatch_17_5 || ste_0_mismatch_18_6);
	ste_0_match_20_0_enable = (ste_0_match_19_0);
	ste_0_match_20_1_enable = (ste_0_match_18_0 || ste_0_match_19_1 || ste_0_mismatch_19_1);
	ste_0_match_20_2_enable = (ste_0_match_17_0 || ste_0_match_18_1 || ste_0_match_19_2 || ste_0_mismatch_18_1 || ste_0_mismatch_19_2);
	ste_0_match_20_3_enable = (ste_0_match_16_0 || ste_0_match_17_1 || ste_0_match_18_2 || ste_0_match_19_3 || ste_0_mismatch_17_1 || ste_0_mismatch_18_2 || ste_0_mismatch_19_3);
	ste_0_match_20_4_enable = (ste_0_match_15_0 || ste_0_match_16_1 || ste_0_match_17_2 || ste_0_match_18_3 || ste_0_match_19_4 || ste_0_mismatch_16_1 || ste_0_mismatch_17_2 || ste_0_mismatch_18_3 || ste_0_mismatch_19_4);
	ste_0_match_20_5_enable = (ste_0_match_14_0 || ste_0_match_15_1 || ste_0_match_16_2 || ste_0_match_17_3 || ste_0_match_18_4 || ste_0_match_19_5 || ste_0_mismatch_15_1 || ste_0_mismatch_16_2 || ste_0_mismatch_17_3 || ste_0_mismatch_18_4 || ste_0_mismatch_19_5);
	ste_0_match_20_6_enable = (ste_0_match_13_0 || ste_0_match_14_1 || ste_0_match_15_2 || ste_0_match_16_3 || ste_0_match_17_4 || ste_0_match_18_5 || ste_0_match_19_6 || ste_0_mismatch_14_1 || ste_0_mismatch_15_2 || ste_0_mismatch_16_3 || ste_0_mismatch_17_4 || ste_0_mismatch_18_5 || ste_0_mismatch_19_6);
	ste_0_match_21_0_enable = (ste_0_match_20_0);
	ste_0_match_21_1_enable = (ste_0_match_19_0 || ste_0_match_20_1 || ste_0_mismatch_20_1);
	ste_0_match_21_2_enable = (ste_0_match_18_0 || ste_0_match_19_1 || ste_0_match_20_2 || ste_0_mismatch_19_1 || ste_0_mismatch_20_2);
	ste_0_match_21_3_enable = (ste_0_match_17_0 || ste_0_match_18_1 || ste_0_match_19_2 || ste_0_match_20_3 || ste_0_mismatch_18_1 || ste_0_mismatch_19_2 || ste_0_mismatch_20_3);
	ste_0_match_21_4_enable = (ste_0_match_16_0 || ste_0_match_17_1 || ste_0_match_18_2 || ste_0_match_19_3 || ste_0_match_20_4 || ste_0_mismatch_17_1 || ste_0_mismatch_18_2 || ste_0_mismatch_19_3 || ste_0_mismatch_20_4);
	ste_0_match_21_5_enable = (ste_0_match_15_0 || ste_0_match_16_1 || ste_0_match_17_2 || ste_0_match_18_3 || ste_0_match_19_4 || ste_0_match_20_5 || ste_0_mismatch_16_1 || ste_0_mismatch_17_2 || ste_0_mismatch_18_3 || ste_0_mismatch_19_4 || ste_0_mismatch_20_5);
	ste_0_match_21_6_enable = (ste_0_match_14_0 || ste_0_match_15_1 || ste_0_match_16_2 || ste_0_match_17_3 || ste_0_match_18_4 || ste_0_match_19_5 || ste_0_match_20_6 || ste_0_mismatch_15_1 || ste_0_mismatch_16_2 || ste_0_mismatch_17_3 || ste_0_mismatch_18_4 || ste_0_mismatch_19_5 || ste_0_mismatch_20_6);
	ste_0_match_22_0_enable = (ste_0_match_21_0);
	ste_0_match_22_1_enable = (ste_0_match_20_0 || ste_0_match_21_1 || ste_0_mismatch_21_1);
	ste_0_match_22_2_enable = (ste_0_match_19_0 || ste_0_match_20_1 || ste_0_match_21_2 || ste_0_mismatch_20_1 || ste_0_mismatch_21_2);
	ste_0_match_22_3_enable = (ste_0_match_18_0 || ste_0_match_19_1 || ste_0_match_20_2 || ste_0_match_21_3 || ste_0_mismatch_19_1 || ste_0_mismatch_20_2 || ste_0_mismatch_21_3);
	ste_0_match_22_4_enable = (ste_0_match_17_0 || ste_0_match_18_1 || ste_0_match_19_2 || ste_0_match_20_3 || ste_0_match_21_4 || ste_0_mismatch_18_1 || ste_0_mismatch_19_2 || ste_0_mismatch_20_3 || ste_0_mismatch_21_4);
	ste_0_match_22_5_enable = (ste_0_match_16_0 || ste_0_match_17_1 || ste_0_match_18_2 || ste_0_match_19_3 || ste_0_match_20_4 || ste_0_match_21_5 || ste_0_mismatch_17_1 || ste_0_mismatch_18_2 || ste_0_mismatch_19_3 || ste_0_mismatch_20_4 || ste_0_mismatch_21_5);
	ste_0_match_22_6_enable = (ste_0_match_15_0 || ste_0_match_16_1 || ste_0_match_17_2 || ste_0_match_18_3 || ste_0_match_19_4 || ste_0_match_20_5 || ste_0_match_21_6 || ste_0_mismatch_16_1 || ste_0_mismatch_17_2 || ste_0_mismatch_18_3 || ste_0_mismatch_19_4 || ste_0_mismatch_20_5 || ste_0_mismatch_21_6);
	ste_0_match_23_0_enable = (ste_0_match_22_0);
	ste_0_match_23_1_enable = (ste_0_match_21_0 || ste_0_match_22_1 || ste_0_mismatch_22_1);
	ste_0_match_23_2_enable = (ste_0_match_20_0 || ste_0_match_21_1 || ste_0_match_22_2 || ste_0_mismatch_21_1 || ste_0_mismatch_22_2);
	ste_0_match_23_3_enable = (ste_0_match_19_0 || ste_0_match_20_1 || ste_0_match_21_2 || ste_0_match_22_3 || ste_0_mismatch_20_1 || ste_0_mismatch_21_2 || ste_0_mismatch_22_3);
	ste_0_match_23_4_enable = (ste_0_match_18_0 || ste_0_match_19_1 || ste_0_match_20_2 || ste_0_match_21_3 || ste_0_match_22_4 || ste_0_mismatch_19_1 || ste_0_mismatch_20_2 || ste_0_mismatch_21_3 || ste_0_mismatch_22_4);
	ste_0_match_23_5_enable = (ste_0_match_17_0 || ste_0_match_18_1 || ste_0_match_19_2 || ste_0_match_20_3 || ste_0_match_21_4 || ste_0_match_22_5 || ste_0_mismatch_18_1 || ste_0_mismatch_19_2 || ste_0_mismatch_20_3 || ste_0_mismatch_21_4 || ste_0_mismatch_22_5);
	ste_0_match_23_6_enable = (ste_0_match_16_0 || ste_0_match_17_1 || ste_0_match_18_2 || ste_0_match_19_3 || ste_0_match_20_4 || ste_0_match_21_5 || ste_0_match_22_6 || ste_0_mismatch_17_1 || ste_0_mismatch_18_2 || ste_0_mismatch_19_3 || ste_0_mismatch_20_4 || ste_0_mismatch_21_5 || ste_0_mismatch_22_6);

	ste_0_mismatch_0_1_enable = start_state;
	ste_0_mismatch_0_2_enable = (ste_0_mismatch_0_1);
	ste_0_mismatch_0_3_enable = (ste_0_mismatch_0_2);
	ste_0_mismatch_0_4_enable = (ste_0_mismatch_0_3);
	ste_0_mismatch_0_5_enable = (ste_0_mismatch_0_4);
	ste_0_mismatch_0_6_enable = (ste_0_mismatch_0_5);
	ste_0_mismatch_1_1_enable = start_state;
	ste_0_mismatch_1_2_enable = (ste_0_match_1_1 || ste_0_mismatch_0_1 || ste_0_mismatch_1_1);
	ste_0_mismatch_1_3_enable = (ste_0_match_1_2 || ste_0_mismatch_0_2 || ste_0_mismatch_1_2);
	ste_0_mismatch_1_4_enable = (ste_0_match_1_3 || ste_0_mismatch_0_3 || ste_0_mismatch_1_3);
	ste_0_mismatch_1_5_enable = (ste_0_match_1_4 || ste_0_mismatch_0_4 || ste_0_mismatch_1_4);
	ste_0_mismatch_1_6_enable = (ste_0_match_1_5 || ste_0_mismatch_0_5 || ste_0_mismatch_1_5);
	ste_0_mismatch_2_1_enable = (ste_0_match_1_0 || ste_0_match_2_0);
	ste_0_mismatch_2_2_enable = (ste_0_match_1_1 || ste_0_match_2_1 || ste_0_mismatch_1_1 || ste_0_mismatch_2_1);
	ste_0_mismatch_2_3_enable = (ste_0_match_1_2 || ste_0_match_2_2 || ste_0_mismatch_0_1 || ste_0_mismatch_1_2 || ste_0_mismatch_2_2);
	ste_0_mismatch_2_4_enable = (ste_0_match_1_3 || ste_0_match_2_3 || ste_0_mismatch_0_2 || ste_0_mismatch_1_3 || ste_0_mismatch_2_3);
	ste_0_mismatch_2_5_enable = (ste_0_match_1_4 || ste_0_match_2_4 || ste_0_mismatch_0_3 || ste_0_mismatch_1_4 || ste_0_mismatch_2_4);
	ste_0_mismatch_2_6_enable = (ste_0_match_1_5 || ste_0_match_2_5 || ste_0_mismatch_0_4 || ste_0_mismatch_1_5 || ste_0_mismatch_2_5);
	ste_0_mismatch_3_1_enable = (ste_0_match_2_0 || ste_0_match_3_0);
	ste_0_mismatch_3_2_enable = (ste_0_match_1_0 || ste_0_match_2_1 || ste_0_match_3_1 || ste_0_mismatch_2_1 || ste_0_mismatch_3_1);
	ste_0_mismatch_3_3_enable = (ste_0_match_1_1 || ste_0_match_2_2 || ste_0_match_3_2 || ste_0_mismatch_1_1 || ste_0_mismatch_2_2 || ste_0_mismatch_3_2);
	ste_0_mismatch_3_4_enable = (ste_0_match_1_2 || ste_0_match_2_3 || ste_0_match_3_3 || ste_0_mismatch_0_1 || ste_0_mismatch_1_2 || ste_0_mismatch_2_3 || ste_0_mismatch_3_3);
	ste_0_mismatch_3_5_enable = (ste_0_match_1_3 || ste_0_match_2_4 || ste_0_match_3_4 || ste_0_mismatch_0_2 || ste_0_mismatch_1_3 || ste_0_mismatch_2_4 || ste_0_mismatch_3_4);
	ste_0_mismatch_3_6_enable = (ste_0_match_1_4 || ste_0_match_2_5 || ste_0_match_3_5 || ste_0_mismatch_0_3 || ste_0_mismatch_1_4 || ste_0_mismatch_2_5 || ste_0_mismatch_3_5);
	ste_0_mismatch_4_1_enable = (ste_0_match_3_0 || ste_0_match_4_0);
	ste_0_mismatch_4_2_enable = (ste_0_match_2_0 || ste_0_match_3_1 || ste_0_match_4_1 || ste_0_mismatch_3_1 || ste_0_mismatch_4_1);
	ste_0_mismatch_4_3_enable = (ste_0_match_1_0 || ste_0_match_2_1 || ste_0_match_3_2 || ste_0_match_4_2 || ste_0_mismatch_2_1 || ste_0_mismatch_3_2 || ste_0_mismatch_4_2);
	ste_0_mismatch_4_4_enable = (ste_0_match_1_1 || ste_0_match_2_2 || ste_0_match_3_3 || ste_0_match_4_3 || ste_0_mismatch_1_1 || ste_0_mismatch_2_2 || ste_0_mismatch_3_3 || ste_0_mismatch_4_3);
	ste_0_mismatch_4_5_enable = (ste_0_match_1_2 || ste_0_match_2_3 || ste_0_match_3_4 || ste_0_match_4_4 || ste_0_mismatch_0_1 || ste_0_mismatch_1_2 || ste_0_mismatch_2_3 || ste_0_mismatch_3_4 || ste_0_mismatch_4_4);
	ste_0_mismatch_4_6_enable = (ste_0_match_1_3 || ste_0_match_2_4 || ste_0_match_3_5 || ste_0_match_4_5 || ste_0_mismatch_0_2 || ste_0_mismatch_1_3 || ste_0_mismatch_2_4 || ste_0_mismatch_3_5 || ste_0_mismatch_4_5);
	ste_0_mismatch_5_1_enable = (ste_0_match_4_0 || ste_0_match_5_0);
	ste_0_mismatch_5_2_enable = (ste_0_match_3_0 || ste_0_match_4_1 || ste_0_match_5_1 || ste_0_mismatch_4_1 || ste_0_mismatch_5_1);
	ste_0_mismatch_5_3_enable = (ste_0_match_2_0 || ste_0_match_3_1 || ste_0_match_4_2 || ste_0_match_5_2 || ste_0_mismatch_3_1 || ste_0_mismatch_4_2 || ste_0_mismatch_5_2);
	ste_0_mismatch_5_4_enable = (ste_0_match_1_0 || ste_0_match_2_1 || ste_0_match_3_2 || ste_0_match_4_3 || ste_0_match_5_3 || ste_0_mismatch_2_1 || ste_0_mismatch_3_2 || ste_0_mismatch_4_3 || ste_0_mismatch_5_3);
	ste_0_mismatch_5_5_enable = (ste_0_match_1_1 || ste_0_match_2_2 || ste_0_match_3_3 || ste_0_match_4_4 || ste_0_match_5_4 || ste_0_mismatch_1_1 || ste_0_mismatch_2_2 || ste_0_mismatch_3_3 || ste_0_mismatch_4_4 || ste_0_mismatch_5_4);
	ste_0_mismatch_5_6_enable = (ste_0_match_1_2 || ste_0_match_2_3 || ste_0_match_3_4 || ste_0_match_4_5 || ste_0_match_5_5 || ste_0_mismatch_0_1 || ste_0_mismatch_1_2 || ste_0_mismatch_2_3 || ste_0_mismatch_3_4 || ste_0_mismatch_4_5 || ste_0_mismatch_5_5);
	ste_0_mismatch_6_1_enable = (ste_0_match_5_0 || ste_0_match_6_0);
	ste_0_mismatch_6_2_enable = (ste_0_match_4_0 || ste_0_match_5_1 || ste_0_match_6_1 || ste_0_mismatch_5_1 || ste_0_mismatch_6_1);
	ste_0_mismatch_6_3_enable = (ste_0_match_3_0 || ste_0_match_4_1 || ste_0_match_5_2 || ste_0_match_6_2 || ste_0_mismatch_4_1 || ste_0_mismatch_5_2 || ste_0_mismatch_6_2);
	ste_0_mismatch_6_4_enable = (ste_0_match_2_0 || ste_0_match_3_1 || ste_0_match_4_2 || ste_0_match_5_3 || ste_0_match_6_3 || ste_0_mismatch_3_1 || ste_0_mismatch_4_2 || ste_0_mismatch_5_3 || ste_0_mismatch_6_3);
	ste_0_mismatch_6_5_enable = (ste_0_match_1_0 || ste_0_match_2_1 || ste_0_match_3_2 || ste_0_match_4_3 || ste_0_match_5_4 || ste_0_match_6_4 || ste_0_mismatch_2_1 || ste_0_mismatch_3_2 || ste_0_mismatch_4_3 || ste_0_mismatch_5_4 || ste_0_mismatch_6_4);
	ste_0_mismatch_6_6_enable = (ste_0_match_1_1 || ste_0_match_2_2 || ste_0_match_3_3 || ste_0_match_4_4 || ste_0_match_5_5 || ste_0_match_6_5 || ste_0_mismatch_1_1 || ste_0_mismatch_2_2 || ste_0_mismatch_3_3 || ste_0_mismatch_4_4 || ste_0_mismatch_5_5 || ste_0_mismatch_6_5);
	ste_0_mismatch_7_1_enable = (ste_0_match_6_0 || ste_0_match_7_0);
	ste_0_mismatch_7_2_enable = (ste_0_match_5_0 || ste_0_match_6_1 || ste_0_match_7_1 || ste_0_mismatch_6_1 || ste_0_mismatch_7_1);
	ste_0_mismatch_7_3_enable = (ste_0_match_4_0 || ste_0_match_5_1 || ste_0_match_6_2 || ste_0_match_7_2 || ste_0_mismatch_5_1 || ste_0_mismatch_6_2 || ste_0_mismatch_7_2);
	ste_0_mismatch_7_4_enable = (ste_0_match_3_0 || ste_0_match_4_1 || ste_0_match_5_2 || ste_0_match_6_3 || ste_0_match_7_3 || ste_0_mismatch_4_1 || ste_0_mismatch_5_2 || ste_0_mismatch_6_3 || ste_0_mismatch_7_3);
	ste_0_mismatch_7_5_enable = (ste_0_match_2_0 || ste_0_match_3_1 || ste_0_match_4_2 || ste_0_match_5_3 || ste_0_match_6_4 || ste_0_match_7_4 || ste_0_mismatch_3_1 || ste_0_mismatch_4_2 || ste_0_mismatch_5_3 || ste_0_mismatch_6_4 || ste_0_mismatch_7_4);
	ste_0_mismatch_7_6_enable = (ste_0_match_1_0 || ste_0_match_2_1 || ste_0_match_3_2 || ste_0_match_4_3 || ste_0_match_5_4 || ste_0_match_6_5 || ste_0_match_7_5 || ste_0_mismatch_2_1 || ste_0_mismatch_3_2 || ste_0_mismatch_4_3 || ste_0_mismatch_5_4 || ste_0_mismatch_6_5 || ste_0_mismatch_7_5);
	ste_0_mismatch_8_1_enable = (ste_0_match_7_0 || ste_0_match_8_0);
	ste_0_mismatch_8_2_enable = (ste_0_match_6_0 || ste_0_match_7_1 || ste_0_match_8_1 || ste_0_mismatch_7_1 || ste_0_mismatch_8_1);
	ste_0_mismatch_8_3_enable = (ste_0_match_5_0 || ste_0_match_6_1 || ste_0_match_7_2 || ste_0_match_8_2 || ste_0_mismatch_6_1 || ste_0_mismatch_7_2 || ste_0_mismatch_8_2);
	ste_0_mismatch_8_4_enable = (ste_0_match_4_0 || ste_0_match_5_1 || ste_0_match_6_2 || ste_0_match_7_3 || ste_0_match_8_3 || ste_0_mismatch_5_1 || ste_0_mismatch_6_2 || ste_0_mismatch_7_3 || ste_0_mismatch_8_3);
	ste_0_mismatch_8_5_enable = (ste_0_match_3_0 || ste_0_match_4_1 || ste_0_match_5_2 || ste_0_match_6_3 || ste_0_match_7_4 || ste_0_match_8_4 || ste_0_mismatch_4_1 || ste_0_mismatch_5_2 || ste_0_mismatch_6_3 || ste_0_mismatch_7_4 || ste_0_mismatch_8_4);
	ste_0_mismatch_8_6_enable = (ste_0_match_2_0 || ste_0_match_3_1 || ste_0_match_4_2 || ste_0_match_5_3 || ste_0_match_6_4 || ste_0_match_7_5 || ste_0_match_8_5 || ste_0_mismatch_3_1 || ste_0_mismatch_4_2 || ste_0_mismatch_5_3 || ste_0_mismatch_6_4 || ste_0_mismatch_7_5 || ste_0_mismatch_8_5);
	ste_0_mismatch_9_1_enable = (ste_0_match_8_0 || ste_0_match_9_0);
	ste_0_mismatch_9_2_enable = (ste_0_match_7_0 || ste_0_match_8_1 || ste_0_match_9_1 || ste_0_mismatch_8_1 || ste_0_mismatch_9_1);
	ste_0_mismatch_9_3_enable = (ste_0_match_6_0 || ste_0_match_7_1 || ste_0_match_8_2 || ste_0_match_9_2 || ste_0_mismatch_7_1 || ste_0_mismatch_8_2 || ste_0_mismatch_9_2);
	ste_0_mismatch_9_4_enable = (ste_0_match_5_0 || ste_0_match_6_1 || ste_0_match_7_2 || ste_0_match_8_3 || ste_0_match_9_3 || ste_0_mismatch_6_1 || ste_0_mismatch_7_2 || ste_0_mismatch_8_3 || ste_0_mismatch_9_3);
	ste_0_mismatch_9_5_enable = (ste_0_match_4_0 || ste_0_match_5_1 || ste_0_match_6_2 || ste_0_match_7_3 || ste_0_match_8_4 || ste_0_match_9_4 || ste_0_mismatch_5_1 || ste_0_mismatch_6_2 || ste_0_mismatch_7_3 || ste_0_mismatch_8_4 || ste_0_mismatch_9_4);
	ste_0_mismatch_9_6_enable = (ste_0_match_3_0 || ste_0_match_4_1 || ste_0_match_5_2 || ste_0_match_6_3 || ste_0_match_7_4 || ste_0_match_8_5 || ste_0_match_9_5 || ste_0_mismatch_4_1 || ste_0_mismatch_5_2 || ste_0_mismatch_6_3 || ste_0_mismatch_7_4 || ste_0_mismatch_8_5 || ste_0_mismatch_9_5);
	ste_0_mismatch_10_1_enable = (ste_0_match_10_0 || ste_0_match_9_0);
	ste_0_mismatch_10_2_enable = (ste_0_match_10_1 || ste_0_match_8_0 || ste_0_match_9_1 || ste_0_mismatch_10_1 || ste_0_mismatch_9_1);
	ste_0_mismatch_10_3_enable = (ste_0_match_10_2 || ste_0_match_7_0 || ste_0_match_8_1 || ste_0_match_9_2 || ste_0_mismatch_10_2 || ste_0_mismatch_8_1 || ste_0_mismatch_9_2);
	ste_0_mismatch_10_4_enable = (ste_0_match_10_3 || ste_0_match_6_0 || ste_0_match_7_1 || ste_0_match_8_2 || ste_0_match_9_3 || ste_0_mismatch_10_3 || ste_0_mismatch_7_1 || ste_0_mismatch_8_2 || ste_0_mismatch_9_3);
	ste_0_mismatch_10_5_enable = (ste_0_match_10_4 || ste_0_match_5_0 || ste_0_match_6_1 || ste_0_match_7_2 || ste_0_match_8_3 || ste_0_match_9_4 || ste_0_mismatch_10_4 || ste_0_mismatch_6_1 || ste_0_mismatch_7_2 || ste_0_mismatch_8_3 || ste_0_mismatch_9_4);
	ste_0_mismatch_10_6_enable = (ste_0_match_10_5 || ste_0_match_4_0 || ste_0_match_5_1 || ste_0_match_6_2 || ste_0_match_7_3 || ste_0_match_8_4 || ste_0_match_9_5 || ste_0_mismatch_10_5 || ste_0_mismatch_5_1 || ste_0_mismatch_6_2 || ste_0_mismatch_7_3 || ste_0_mismatch_8_4 || ste_0_mismatch_9_5);
	ste_0_mismatch_11_1_enable = (ste_0_match_10_0 || ste_0_match_11_0);
	ste_0_mismatch_11_2_enable = (ste_0_match_10_1 || ste_0_match_11_1 || ste_0_match_9_0 || ste_0_mismatch_10_1 || ste_0_mismatch_11_1);
	ste_0_mismatch_11_3_enable = (ste_0_match_10_2 || ste_0_match_11_2 || ste_0_match_8_0 || ste_0_match_9_1 || ste_0_mismatch_10_2 || ste_0_mismatch_11_2 || ste_0_mismatch_9_1);
	ste_0_mismatch_11_4_enable = (ste_0_match_10_3 || ste_0_match_11_3 || ste_0_match_7_0 || ste_0_match_8_1 || ste_0_match_9_2 || ste_0_mismatch_10_3 || ste_0_mismatch_11_3 || ste_0_mismatch_8_1 || ste_0_mismatch_9_2);
	ste_0_mismatch_11_5_enable = (ste_0_match_10_4 || ste_0_match_11_4 || ste_0_match_6_0 || ste_0_match_7_1 || ste_0_match_8_2 || ste_0_match_9_3 || ste_0_mismatch_10_4 || ste_0_mismatch_11_4 || ste_0_mismatch_7_1 || ste_0_mismatch_8_2 || ste_0_mismatch_9_3);
	ste_0_mismatch_11_6_enable = (ste_0_match_10_5 || ste_0_match_11_5 || ste_0_match_5_0 || ste_0_match_6_1 || ste_0_match_7_2 || ste_0_match_8_3 || ste_0_match_9_4 || ste_0_mismatch_10_5 || ste_0_mismatch_11_5 || ste_0_mismatch_6_1 || ste_0_mismatch_7_2 || ste_0_mismatch_8_3 || ste_0_mismatch_9_4);
	ste_0_mismatch_12_1_enable = (ste_0_match_11_0 || ste_0_match_12_0);
	ste_0_mismatch_12_2_enable = (ste_0_match_10_0 || ste_0_match_11_1 || ste_0_match_12_1 || ste_0_mismatch_11_1 || ste_0_mismatch_12_1);
	ste_0_mismatch_12_3_enable = (ste_0_match_10_1 || ste_0_match_11_2 || ste_0_match_12_2 || ste_0_match_9_0 || ste_0_mismatch_10_1 || ste_0_mismatch_11_2 || ste_0_mismatch_12_2);
	ste_0_mismatch_12_4_enable = (ste_0_match_10_2 || ste_0_match_11_3 || ste_0_match_12_3 || ste_0_match_8_0 || ste_0_match_9_1 || ste_0_mismatch_10_2 || ste_0_mismatch_11_3 || ste_0_mismatch_12_3 || ste_0_mismatch_9_1);
	ste_0_mismatch_12_5_enable = (ste_0_match_10_3 || ste_0_match_11_4 || ste_0_match_12_4 || ste_0_match_7_0 || ste_0_match_8_1 || ste_0_match_9_2 || ste_0_mismatch_10_3 || ste_0_mismatch_11_4 || ste_0_mismatch_12_4 || ste_0_mismatch_8_1 || ste_0_mismatch_9_2);
	ste_0_mismatch_12_6_enable = (ste_0_match_10_4 || ste_0_match_11_5 || ste_0_match_12_5 || ste_0_match_6_0 || ste_0_match_7_1 || ste_0_match_8_2 || ste_0_match_9_3 || ste_0_mismatch_10_4 || ste_0_mismatch_11_5 || ste_0_mismatch_12_5 || ste_0_mismatch_7_1 || ste_0_mismatch_8_2 || ste_0_mismatch_9_3);
	ste_0_mismatch_13_1_enable = (ste_0_match_12_0 || ste_0_match_13_0);
	ste_0_mismatch_13_2_enable = (ste_0_match_11_0 || ste_0_match_12_1 || ste_0_match_13_1 || ste_0_mismatch_12_1 || ste_0_mismatch_13_1);
	ste_0_mismatch_13_3_enable = (ste_0_match_10_0 || ste_0_match_11_1 || ste_0_match_12_2 || ste_0_match_13_2 || ste_0_mismatch_11_1 || ste_0_mismatch_12_2 || ste_0_mismatch_13_2);
	ste_0_mismatch_13_4_enable = (ste_0_match_10_1 || ste_0_match_11_2 || ste_0_match_12_3 || ste_0_match_13_3 || ste_0_match_9_0 || ste_0_mismatch_10_1 || ste_0_mismatch_11_2 || ste_0_mismatch_12_3 || ste_0_mismatch_13_3);
	ste_0_mismatch_13_5_enable = (ste_0_match_10_2 || ste_0_match_11_3 || ste_0_match_12_4 || ste_0_match_13_4 || ste_0_match_8_0 || ste_0_match_9_1 || ste_0_mismatch_10_2 || ste_0_mismatch_11_3 || ste_0_mismatch_12_4 || ste_0_mismatch_13_4 || ste_0_mismatch_9_1);
	ste_0_mismatch_13_6_enable = (ste_0_match_10_3 || ste_0_match_11_4 || ste_0_match_12_5 || ste_0_match_13_5 || ste_0_match_7_0 || ste_0_match_8_1 || ste_0_match_9_2 || ste_0_mismatch_10_3 || ste_0_mismatch_11_4 || ste_0_mismatch_12_5 || ste_0_mismatch_13_5 || ste_0_mismatch_8_1 || ste_0_mismatch_9_2);
	ste_0_mismatch_14_1_enable = (ste_0_match_13_0 || ste_0_match_14_0);
	ste_0_mismatch_14_2_enable = (ste_0_match_12_0 || ste_0_match_13_1 || ste_0_match_14_1 || ste_0_mismatch_13_1 || ste_0_mismatch_14_1);
	ste_0_mismatch_14_3_enable = (ste_0_match_11_0 || ste_0_match_12_1 || ste_0_match_13_2 || ste_0_match_14_2 || ste_0_mismatch_12_1 || ste_0_mismatch_13_2 || ste_0_mismatch_14_2);
	ste_0_mismatch_14_4_enable = (ste_0_match_10_0 || ste_0_match_11_1 || ste_0_match_12_2 || ste_0_match_13_3 || ste_0_match_14_3 || ste_0_mismatch_11_1 || ste_0_mismatch_12_2 || ste_0_mismatch_13_3 || ste_0_mismatch_14_3);
	ste_0_mismatch_14_5_enable = (ste_0_match_10_1 || ste_0_match_11_2 || ste_0_match_12_3 || ste_0_match_13_4 || ste_0_match_14_4 || ste_0_match_9_0 || ste_0_mismatch_10_1 || ste_0_mismatch_11_2 || ste_0_mismatch_12_3 || ste_0_mismatch_13_4 || ste_0_mismatch_14_4);
	ste_0_mismatch_14_6_enable = (ste_0_match_10_2 || ste_0_match_11_3 || ste_0_match_12_4 || ste_0_match_13_5 || ste_0_match_14_5 || ste_0_match_8_0 || ste_0_match_9_1 || ste_0_mismatch_10_2 || ste_0_mismatch_11_3 || ste_0_mismatch_12_4 || ste_0_mismatch_13_5 || ste_0_mismatch_14_5 || ste_0_mismatch_9_1);
	ste_0_mismatch_15_1_enable = (ste_0_match_14_0 || ste_0_match_15_0);
	ste_0_mismatch_15_2_enable = (ste_0_match_13_0 || ste_0_match_14_1 || ste_0_match_15_1 || ste_0_mismatch_14_1 || ste_0_mismatch_15_1);
	ste_0_mismatch_15_3_enable = (ste_0_match_12_0 || ste_0_match_13_1 || ste_0_match_14_2 || ste_0_match_15_2 || ste_0_mismatch_13_1 || ste_0_mismatch_14_2 || ste_0_mismatch_15_2);
	ste_0_mismatch_15_4_enable = (ste_0_match_11_0 || ste_0_match_12_1 || ste_0_match_13_2 || ste_0_match_14_3 || ste_0_match_15_3 || ste_0_mismatch_12_1 || ste_0_mismatch_13_2 || ste_0_mismatch_14_3 || ste_0_mismatch_15_3);
	ste_0_mismatch_15_5_enable = (ste_0_match_10_0 || ste_0_match_11_1 || ste_0_match_12_2 || ste_0_match_13_3 || ste_0_match_14_4 || ste_0_match_15_4 || ste_0_mismatch_11_1 || ste_0_mismatch_12_2 || ste_0_mismatch_13_3 || ste_0_mismatch_14_4 || ste_0_mismatch_15_4);
	ste_0_mismatch_15_6_enable = (ste_0_match_10_1 || ste_0_match_11_2 || ste_0_match_12_3 || ste_0_match_13_4 || ste_0_match_14_5 || ste_0_match_15_5 || ste_0_match_9_0 || ste_0_mismatch_10_1 || ste_0_mismatch_11_2 || ste_0_mismatch_12_3 || ste_0_mismatch_13_4 || ste_0_mismatch_14_5 || ste_0_mismatch_15_5);
	ste_0_mismatch_16_1_enable = (ste_0_match_15_0 || ste_0_match_16_0);
	ste_0_mismatch_16_2_enable = (ste_0_match_14_0 || ste_0_match_15_1 || ste_0_match_16_1 || ste_0_mismatch_15_1 || ste_0_mismatch_16_1);
	ste_0_mismatch_16_3_enable = (ste_0_match_13_0 || ste_0_match_14_1 || ste_0_match_15_2 || ste_0_match_16_2 || ste_0_mismatch_14_1 || ste_0_mismatch_15_2 || ste_0_mismatch_16_2);
	ste_0_mismatch_16_4_enable = (ste_0_match_12_0 || ste_0_match_13_1 || ste_0_match_14_2 || ste_0_match_15_3 || ste_0_match_16_3 || ste_0_mismatch_13_1 || ste_0_mismatch_14_2 || ste_0_mismatch_15_3 || ste_0_mismatch_16_3);
	ste_0_mismatch_16_5_enable = (ste_0_match_11_0 || ste_0_match_12_1 || ste_0_match_13_2 || ste_0_match_14_3 || ste_0_match_15_4 || ste_0_match_16_4 || ste_0_mismatch_12_1 || ste_0_mismatch_13_2 || ste_0_mismatch_14_3 || ste_0_mismatch_15_4 || ste_0_mismatch_16_4);
	ste_0_mismatch_16_6_enable = (ste_0_match_10_0 || ste_0_match_11_1 || ste_0_match_12_2 || ste_0_match_13_3 || ste_0_match_14_4 || ste_0_match_15_5 || ste_0_match_16_5 || ste_0_mismatch_11_1 || ste_0_mismatch_12_2 || ste_0_mismatch_13_3 || ste_0_mismatch_14_4 || ste_0_mismatch_15_5 || ste_0_mismatch_16_5);
	ste_0_mismatch_17_1_enable = (ste_0_match_16_0 || ste_0_match_17_0);
	ste_0_mismatch_17_2_enable = (ste_0_match_15_0 || ste_0_match_16_1 || ste_0_match_17_1 || ste_0_mismatch_16_1 || ste_0_mismatch_17_1);
	ste_0_mismatch_17_3_enable = (ste_0_match_14_0 || ste_0_match_15_1 || ste_0_match_16_2 || ste_0_match_17_2 || ste_0_mismatch_15_1 || ste_0_mismatch_16_2 || ste_0_mismatch_17_2);
	ste_0_mismatch_17_4_enable = (ste_0_match_13_0 || ste_0_match_14_1 || ste_0_match_15_2 || ste_0_match_16_3 || ste_0_match_17_3 || ste_0_mismatch_14_1 || ste_0_mismatch_15_2 || ste_0_mismatch_16_3 || ste_0_mismatch_17_3);
	ste_0_mismatch_17_5_enable = (ste_0_match_12_0 || ste_0_match_13_1 || ste_0_match_14_2 || ste_0_match_15_3 || ste_0_match_16_4 || ste_0_match_17_4 || ste_0_mismatch_13_1 || ste_0_mismatch_14_2 || ste_0_mismatch_15_3 || ste_0_mismatch_16_4 || ste_0_mismatch_17_4);
	ste_0_mismatch_17_6_enable = (ste_0_match_11_0 || ste_0_match_12_1 || ste_0_match_13_2 || ste_0_match_14_3 || ste_0_match_15_4 || ste_0_match_16_5 || ste_0_match_17_5 || ste_0_mismatch_12_1 || ste_0_mismatch_13_2 || ste_0_mismatch_14_3 || ste_0_mismatch_15_4 || ste_0_mismatch_16_5 || ste_0_mismatch_17_5);
	ste_0_mismatch_18_1_enable = (ste_0_match_17_0 || ste_0_match_18_0);
	ste_0_mismatch_18_2_enable = (ste_0_match_16_0 || ste_0_match_17_1 || ste_0_match_18_1 || ste_0_mismatch_17_1 || ste_0_mismatch_18_1);
	ste_0_mismatch_18_3_enable = (ste_0_match_15_0 || ste_0_match_16_1 || ste_0_match_17_2 || ste_0_match_18_2 || ste_0_mismatch_16_1 || ste_0_mismatch_17_2 || ste_0_mismatch_18_2);
	ste_0_mismatch_18_4_enable = (ste_0_match_14_0 || ste_0_match_15_1 || ste_0_match_16_2 || ste_0_match_17_3 || ste_0_match_18_3 || ste_0_mismatch_15_1 || ste_0_mismatch_16_2 || ste_0_mismatch_17_3 || ste_0_mismatch_18_3);
	ste_0_mismatch_18_5_enable = (ste_0_match_13_0 || ste_0_match_14_1 || ste_0_match_15_2 || ste_0_match_16_3 || ste_0_match_17_4 || ste_0_match_18_4 || ste_0_mismatch_14_1 || ste_0_mismatch_15_2 || ste_0_mismatch_16_3 || ste_0_mismatch_17_4 || ste_0_mismatch_18_4);
	ste_0_mismatch_18_6_enable = (ste_0_match_12_0 || ste_0_match_13_1 || ste_0_match_14_2 || ste_0_match_15_3 || ste_0_match_16_4 || ste_0_match_17_5 || ste_0_match_18_5 || ste_0_mismatch_13_1 || ste_0_mismatch_14_2 || ste_0_mismatch_15_3 || ste_0_mismatch_16_4 || ste_0_mismatch_17_5 || ste_0_mismatch_18_5);
	ste_0_mismatch_19_1_enable = (ste_0_match_18_0 || ste_0_match_19_0);
	ste_0_mismatch_19_2_enable = (ste_0_match_17_0 || ste_0_match_18_1 || ste_0_match_19_1 || ste_0_mismatch_18_1 || ste_0_mismatch_19_1);
	ste_0_mismatch_19_3_enable = (ste_0_match_16_0 || ste_0_match_17_1 || ste_0_match_18_2 || ste_0_match_19_2 || ste_0_mismatch_17_1 || ste_0_mismatch_18_2 || ste_0_mismatch_19_2);
	ste_0_mismatch_19_4_enable = (ste_0_match_15_0 || ste_0_match_16_1 || ste_0_match_17_2 || ste_0_match_18_3 || ste_0_match_19_3 || ste_0_mismatch_16_1 || ste_0_mismatch_17_2 || ste_0_mismatch_18_3 || ste_0_mismatch_19_3);
	ste_0_mismatch_19_5_enable = (ste_0_match_14_0 || ste_0_match_15_1 || ste_0_match_16_2 || ste_0_match_17_3 || ste_0_match_18_4 || ste_0_match_19_4 || ste_0_mismatch_15_1 || ste_0_mismatch_16_2 || ste_0_mismatch_17_3 || ste_0_mismatch_18_4 || ste_0_mismatch_19_4);
	ste_0_mismatch_19_6_enable = (ste_0_match_13_0 || ste_0_match_14_1 || ste_0_match_15_2 || ste_0_match_16_3 || ste_0_match_17_4 || ste_0_match_18_5 || ste_0_match_19_5 || ste_0_mismatch_14_1 || ste_0_mismatch_15_2 || ste_0_mismatch_16_3 || ste_0_mismatch_17_4 || ste_0_mismatch_18_5 || ste_0_mismatch_19_5);
	ste_0_mismatch_20_1_enable = (ste_0_match_19_0 || ste_0_match_20_0);
	ste_0_mismatch_20_2_enable = (ste_0_match_18_0 || ste_0_match_19_1 || ste_0_match_20_1 || ste_0_mismatch_19_1 || ste_0_mismatch_20_1);
	ste_0_mismatch_20_3_enable = (ste_0_match_17_0 || ste_0_match_18_1 || ste_0_match_19_2 || ste_0_match_20_2 || ste_0_mismatch_18_1 || ste_0_mismatch_19_2 || ste_0_mismatch_20_2);
	ste_0_mismatch_20_4_enable = (ste_0_match_16_0 || ste_0_match_17_1 || ste_0_match_18_2 || ste_0_match_19_3 || ste_0_match_20_3 || ste_0_mismatch_17_1 || ste_0_mismatch_18_2 || ste_0_mismatch_19_3 || ste_0_mismatch_20_3);
	ste_0_mismatch_20_5_enable = (ste_0_match_15_0 || ste_0_match_16_1 || ste_0_match_17_2 || ste_0_match_18_3 || ste_0_match_19_4 || ste_0_match_20_4 || ste_0_mismatch_16_1 || ste_0_mismatch_17_2 || ste_0_mismatch_18_3 || ste_0_mismatch_19_4 || ste_0_mismatch_20_4);
	ste_0_mismatch_20_6_enable = (ste_0_match_14_0 || ste_0_match_15_1 || ste_0_match_16_2 || ste_0_match_17_3 || ste_0_match_18_4 || ste_0_match_19_5 || ste_0_match_20_5 || ste_0_mismatch_15_1 || ste_0_mismatch_16_2 || ste_0_mismatch_17_3 || ste_0_mismatch_18_4 || ste_0_mismatch_19_5 || ste_0_mismatch_20_5);
	ste_0_mismatch_21_1_enable = (ste_0_match_20_0 || ste_0_match_21_0);
	ste_0_mismatch_21_2_enable = (ste_0_match_19_0 || ste_0_match_20_1 || ste_0_match_21_1 || ste_0_mismatch_20_1 || ste_0_mismatch_21_1);
	ste_0_mismatch_21_3_enable = (ste_0_match_18_0 || ste_0_match_19_1 || ste_0_match_20_2 || ste_0_match_21_2 || ste_0_mismatch_19_1 || ste_0_mismatch_20_2 || ste_0_mismatch_21_2);
	ste_0_mismatch_21_4_enable = (ste_0_match_17_0 || ste_0_match_18_1 || ste_0_match_19_2 || ste_0_match_20_3 || ste_0_match_21_3 || ste_0_mismatch_18_1 || ste_0_mismatch_19_2 || ste_0_mismatch_20_3 || ste_0_mismatch_21_3);
	ste_0_mismatch_21_5_enable = (ste_0_match_16_0 || ste_0_match_17_1 || ste_0_match_18_2 || ste_0_match_19_3 || ste_0_match_20_4 || ste_0_match_21_4 || ste_0_mismatch_17_1 || ste_0_mismatch_18_2 || ste_0_mismatch_19_3 || ste_0_mismatch_20_4 || ste_0_mismatch_21_4);
	ste_0_mismatch_21_6_enable = (ste_0_match_15_0 || ste_0_match_16_1 || ste_0_match_17_2 || ste_0_match_18_3 || ste_0_match_19_4 || ste_0_match_20_5 || ste_0_match_21_5 || ste_0_mismatch_16_1 || ste_0_mismatch_17_2 || ste_0_mismatch_18_3 || ste_0_mismatch_19_4 || ste_0_mismatch_20_5 || ste_0_mismatch_21_5);
	ste_0_mismatch_22_1_enable = (ste_0_match_21_0 || ste_0_match_22_0);
	ste_0_mismatch_22_2_enable = (ste_0_match_20_0 || ste_0_match_21_1 || ste_0_match_22_1 || ste_0_mismatch_21_1 || ste_0_mismatch_22_1);
	ste_0_mismatch_22_3_enable = (ste_0_match_19_0 || ste_0_match_20_1 || ste_0_match_21_2 || ste_0_match_22_2 || ste_0_mismatch_20_1 || ste_0_mismatch_21_2 || ste_0_mismatch_22_2);
	ste_0_mismatch_22_4_enable = (ste_0_match_18_0 || ste_0_match_19_1 || ste_0_match_20_2 || ste_0_match_21_3 || ste_0_match_22_3 || ste_0_mismatch_19_1 || ste_0_mismatch_20_2 || ste_0_mismatch_21_3 || ste_0_mismatch_22_3);
	ste_0_mismatch_22_5_enable = (ste_0_match_17_0 || ste_0_match_18_1 || ste_0_match_19_2 || ste_0_match_20_3 || ste_0_match_21_4 || ste_0_match_22_4 || ste_0_mismatch_18_1 || ste_0_mismatch_19_2 || ste_0_mismatch_20_3 || ste_0_mismatch_21_4 || ste_0_mismatch_22_4);
	ste_0_mismatch_22_6_enable = (ste_0_match_16_0 || ste_0_match_17_1 || ste_0_match_18_2 || ste_0_match_19_3 || ste_0_match_20_4 || ste_0_match_21_5 || ste_0_match_22_5 || ste_0_mismatch_17_1 || ste_0_mismatch_18_2 || ste_0_mismatch_19_3 || ste_0_mismatch_20_4 || ste_0_mismatch_21_5 || ste_0_mismatch_22_5);
	ste_0_mismatch_23_1_enable = (ste_0_match_22_0 || ste_0_match_23_0);
	ste_0_mismatch_23_2_enable = (ste_0_match_21_0 || ste_0_match_22_1 || ste_0_match_23_1 || ste_0_mismatch_22_1 || ste_0_mismatch_23_1);
	ste_0_mismatch_23_3_enable = (ste_0_match_20_0 || ste_0_match_21_1 || ste_0_match_22_2 || ste_0_match_23_2 || ste_0_mismatch_21_1 || ste_0_mismatch_22_2 || ste_0_mismatch_23_2);
	ste_0_mismatch_23_4_enable = (ste_0_match_19_0 || ste_0_match_20_1 || ste_0_match_21_2 || ste_0_match_22_3 || ste_0_match_23_3 || ste_0_mismatch_20_1 || ste_0_mismatch_21_2 || ste_0_mismatch_22_3 || ste_0_mismatch_23_3);
	ste_0_mismatch_23_5_enable = (ste_0_match_18_0 || ste_0_match_19_1 || ste_0_match_20_2 || ste_0_match_21_3 || ste_0_match_22_4 || ste_0_match_23_4 || ste_0_mismatch_19_1 || ste_0_mismatch_20_2 || ste_0_mismatch_21_3 || ste_0_mismatch_22_4 || ste_0_mismatch_23_4);
	ste_0_mismatch_23_6_enable = (ste_0_match_17_0 || ste_0_match_18_1 || ste_0_match_19_2 || ste_0_match_20_3 || ste_0_match_21_4 || ste_0_match_22_5 || ste_0_match_23_5 || ste_0_mismatch_18_1 || ste_0_mismatch_19_2 || ste_0_mismatch_20_3 || ste_0_mismatch_21_4 || ste_0_mismatch_22_5 || ste_0_mismatch_23_5);

	result = (
		// Edit distance 0 so no mismatches
		(ste_0_match_23_0 && (lev_distance[0])) ||
		(ste_0_match_22_0 && (lev_distance[1])) ||
		(ste_0_match_21_0 && (lev_distance[2])) ||
		(ste_0_match_20_0 && (lev_distance[3])) ||
		(ste_0_match_19_0 && (lev_distance[4])) ||
		(ste_0_match_18_0 && (lev_distance[5])) ||
		(ste_0_match_17_0 && (lev_distance[6])) ||

		// Edit distance 1
		((ste_0_match_23_1 || ste_0_mismatch_23_1) && (lev_distance[1])) ||
		((ste_0_match_22_1 || ste_0_mismatch_22_1) && (lev_distance[2])) ||
		((ste_0_match_21_1 || ste_0_mismatch_21_1) && (lev_distance[3])) ||
		((ste_0_match_20_1 || ste_0_mismatch_20_1) && (lev_distance[4])) ||
		((ste_0_match_19_1 || ste_0_mismatch_19_1) && (lev_distance[5])) ||
		((ste_0_match_18_1 || ste_0_mismatch_18_1) && (lev_distance[6])) ||

		// Edit distance 2
		((ste_0_match_23_2 || ste_0_mismatch_23_2) && (lev_distance[2])) ||
		((ste_0_match_22_2 || ste_0_mismatch_22_2) && (lev_distance[3])) ||
		((ste_0_match_21_2 || ste_0_mismatch_21_2) && (lev_distance[4])) ||
		((ste_0_match_20_2 || ste_0_mismatch_20_2) && (lev_distance[5])) ||
		((ste_0_match_19_2 || ste_0_mismatch_19_2) && (lev_distance[6])) ||

		// Edit distance 3
		((ste_0_match_23_3 || ste_0_mismatch_23_3) && (lev_distance[3])) ||
		((ste_0_match_22_3 || ste_0_mismatch_22_3) && (lev_distance[4])) ||
		((ste_0_match_21_3 || ste_0_mismatch_21_3) && (lev_distance[5])) ||
		((ste_0_match_20_3 || ste_0_mismatch_20_3) && (lev_distance[6])) ||

		// Edit distance 4
		((ste_0_match_23_4 || ste_0_mismatch_23_4) && (lev_distance[4])) ||
		((ste_0_match_22_4 || ste_0_mismatch_22_4) && (lev_distance[5])) ||
		((ste_0_match_21_4 || ste_0_mismatch_21_4) && (lev_distance[6])) ||

		// Edit distance 5
		((ste_0_match_23_5 || ste_0_mismatch_23_5) && (lev_distance[5])) ||
		((ste_0_match_22_5 || ste_0_mismatch_22_5) && (lev_distance[6])) ||

		// Edit distance 6
		((ste_0_match_23_6 || ste_0_mismatch_23_6) && (lev_distance[6])));
}
