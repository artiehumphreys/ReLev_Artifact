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

#ifndef _AUTOMATA_SINGLE_FILE_HPP_
#define _AUTOMATA_SINGLE_FILE_HPP_

#include "krnl_automata.hpp"

struct automata_0 {

	// Pattern for the automaton
	uint8_t symbolset[23] = {};

	// Max edit distance for the automaton
	ap_uint<8> lev_distance = 0b00000001;	

	// States
	uint8_t input_r = 0;
	const ap_uint<1> start_state = 1;

	// Match state enables
	ap_uint<1> ste_0_match_1_0_enable = 1;	// The enable for the first match state is always 1
	ap_uint<1> ste_0_match_1_1_enable = 0;
	ap_uint<1> ste_0_match_1_2_enable = 0;
	ap_uint<1> ste_0_match_1_3_enable = 0;
	ap_uint<1> ste_0_match_1_4_enable = 0;
	ap_uint<1> ste_0_match_1_5_enable = 0;
	ap_uint<1> ste_0_match_1_6_enable = 0;

	ap_uint<1> ste_0_match_2_0_enable = 0;
	ap_uint<1> ste_0_match_2_1_enable = 1;	// The enable for the second match state, but with 1 error is always 1
	ap_uint<1> ste_0_match_2_2_enable = 0;
	ap_uint<1> ste_0_match_2_3_enable = 0;
	ap_uint<1> ste_0_match_2_4_enable = 0;
	ap_uint<1> ste_0_match_2_5_enable = 0;
	ap_uint<1> ste_0_match_2_6_enable = 0;

	ap_uint<1> ste_0_match_3_0_enable = 0;
	ap_uint<1> ste_0_match_3_1_enable = 0;
	ap_uint<1> ste_0_match_3_2_enable = 1;	// The enable for the third match state, but with 2 errors is always 1
	ap_uint<1> ste_0_match_3_3_enable = 0;
	ap_uint<1> ste_0_match_3_4_enable = 0;
	ap_uint<1> ste_0_match_3_5_enable = 0;
	ap_uint<1> ste_0_match_3_6_enable = 0;

	ap_uint<1> ste_0_match_4_0_enable = 0;
	ap_uint<1> ste_0_match_4_1_enable = 0;
	ap_uint<1> ste_0_match_4_2_enable = 0;
	ap_uint<1> ste_0_match_4_3_enable = 1;	// The enable for the fourth match state, but with 3 errors is always 1
	ap_uint<1> ste_0_match_4_4_enable = 0;
	ap_uint<1> ste_0_match_4_5_enable = 0;
	ap_uint<1> ste_0_match_4_6_enable = 0;

	ap_uint<1> ste_0_match_5_0_enable = 0;
	ap_uint<1> ste_0_match_5_1_enable = 0;
	ap_uint<1> ste_0_match_5_2_enable = 0;
	ap_uint<1> ste_0_match_5_3_enable = 0;
	ap_uint<1> ste_0_match_5_4_enable = 1;	// The enable for the fifth match state, but with 4 errors is always 1
	ap_uint<1> ste_0_match_5_5_enable = 0;
	ap_uint<1> ste_0_match_5_6_enable = 0;

	ap_uint<1> ste_0_match_6_0_enable = 0;
	ap_uint<1> ste_0_match_6_1_enable = 0;
	ap_uint<1> ste_0_match_6_2_enable = 0;
	ap_uint<1> ste_0_match_6_3_enable = 0;
	ap_uint<1> ste_0_match_6_4_enable = 0;
	ap_uint<1> ste_0_match_6_5_enable = 1;	// The enable for the sixth match state, but with 5 errors is always 1
	ap_uint<1> ste_0_match_6_6_enable = 0;

	ap_uint<1> ste_0_match_7_0_enable = 0;
	ap_uint<1> ste_0_match_7_1_enable = 0;
	ap_uint<1> ste_0_match_7_2_enable = 0;
	ap_uint<1> ste_0_match_7_3_enable = 0;
	ap_uint<1> ste_0_match_7_4_enable = 0;
	ap_uint<1> ste_0_match_7_5_enable = 0;
	ap_uint<1> ste_0_match_7_6_enable = 1;	// The enable for the seventh match state, but with 6 errors is always 1

	ap_uint<1> ste_0_match_8_0_enable = 0;
	ap_uint<1> ste_0_match_8_1_enable = 0;
	ap_uint<1> ste_0_match_8_2_enable = 0;
	ap_uint<1> ste_0_match_8_3_enable = 0;
	ap_uint<1> ste_0_match_8_4_enable = 0;
	ap_uint<1> ste_0_match_8_5_enable = 0;
	ap_uint<1> ste_0_match_8_6_enable = 0;

	ap_uint<1> ste_0_match_9_0_enable = 0;
	ap_uint<1> ste_0_match_9_1_enable = 0;
	ap_uint<1> ste_0_match_9_2_enable = 0;
	ap_uint<1> ste_0_match_9_3_enable = 0;
	ap_uint<1> ste_0_match_9_4_enable = 0;
	ap_uint<1> ste_0_match_9_5_enable = 0;
	ap_uint<1> ste_0_match_9_6_enable = 0;

	ap_uint<1> ste_0_match_10_0_enable = 0;
	ap_uint<1> ste_0_match_10_1_enable = 0;
	ap_uint<1> ste_0_match_10_2_enable = 0;
	ap_uint<1> ste_0_match_10_3_enable = 0;
	ap_uint<1> ste_0_match_10_4_enable = 0;
	ap_uint<1> ste_0_match_10_5_enable = 0;
	ap_uint<1> ste_0_match_10_6_enable = 0;

	ap_uint<1> ste_0_match_11_0_enable = 0;
	ap_uint<1> ste_0_match_11_1_enable = 0;
	ap_uint<1> ste_0_match_11_2_enable = 0;
	ap_uint<1> ste_0_match_11_3_enable = 0;
	ap_uint<1> ste_0_match_11_4_enable = 0;
	ap_uint<1> ste_0_match_11_5_enable = 0;
	ap_uint<1> ste_0_match_11_6_enable = 0;

	ap_uint<1> ste_0_match_12_0_enable = 0;
	ap_uint<1> ste_0_match_12_1_enable = 0;
	ap_uint<1> ste_0_match_12_2_enable = 0;
	ap_uint<1> ste_0_match_12_3_enable = 0;
	ap_uint<1> ste_0_match_12_4_enable = 0;
	ap_uint<1> ste_0_match_12_5_enable = 0;
	ap_uint<1> ste_0_match_12_6_enable = 0;

	ap_uint<1> ste_0_match_13_0_enable = 0;
	ap_uint<1> ste_0_match_13_1_enable = 0;
	ap_uint<1> ste_0_match_13_2_enable = 0;
	ap_uint<1> ste_0_match_13_3_enable = 0;
	ap_uint<1> ste_0_match_13_4_enable = 0;
	ap_uint<1> ste_0_match_13_5_enable = 0;
	ap_uint<1> ste_0_match_13_6_enable = 0;

	ap_uint<1> ste_0_match_14_0_enable = 0;
	ap_uint<1> ste_0_match_14_1_enable = 0;
	ap_uint<1> ste_0_match_14_2_enable = 0;
	ap_uint<1> ste_0_match_14_3_enable = 0;
	ap_uint<1> ste_0_match_14_4_enable = 0;
	ap_uint<1> ste_0_match_14_5_enable = 0;
	ap_uint<1> ste_0_match_14_6_enable = 0;

	ap_uint<1> ste_0_match_15_0_enable = 0;
	ap_uint<1> ste_0_match_15_1_enable = 0;
	ap_uint<1> ste_0_match_15_2_enable = 0;
	ap_uint<1> ste_0_match_15_3_enable = 0;
	ap_uint<1> ste_0_match_15_4_enable = 0;
	ap_uint<1> ste_0_match_15_5_enable = 0;
	ap_uint<1> ste_0_match_15_6_enable = 0;

	ap_uint<1> ste_0_match_16_0_enable = 0;
	ap_uint<1> ste_0_match_16_1_enable = 0;
	ap_uint<1> ste_0_match_16_2_enable = 0;
	ap_uint<1> ste_0_match_16_3_enable = 0;
	ap_uint<1> ste_0_match_16_4_enable = 0;
	ap_uint<1> ste_0_match_16_5_enable = 0;
	ap_uint<1> ste_0_match_16_6_enable = 0;

	ap_uint<1> ste_0_match_17_0_enable = 0;
	ap_uint<1> ste_0_match_17_1_enable = 0;
	ap_uint<1> ste_0_match_17_2_enable = 0;
	ap_uint<1> ste_0_match_17_3_enable = 0;
	ap_uint<1> ste_0_match_17_4_enable = 0;
	ap_uint<1> ste_0_match_17_5_enable = 0;
	ap_uint<1> ste_0_match_17_6_enable = 0;

	ap_uint<1> ste_0_match_18_0_enable = 0;
	ap_uint<1> ste_0_match_18_1_enable = 0;
	ap_uint<1> ste_0_match_18_2_enable = 0;
	ap_uint<1> ste_0_match_18_3_enable = 0;
	ap_uint<1> ste_0_match_18_4_enable = 0;
	ap_uint<1> ste_0_match_18_5_enable = 0;
	ap_uint<1> ste_0_match_18_6_enable = 0;

	ap_uint<1> ste_0_match_19_0_enable = 0;
	ap_uint<1> ste_0_match_19_1_enable = 0;
	ap_uint<1> ste_0_match_19_2_enable = 0;
	ap_uint<1> ste_0_match_19_3_enable = 0;
	ap_uint<1> ste_0_match_19_4_enable = 0;
	ap_uint<1> ste_0_match_19_5_enable = 0;
	ap_uint<1> ste_0_match_19_6_enable = 0;

	ap_uint<1> ste_0_match_20_0_enable = 0;
	ap_uint<1> ste_0_match_20_1_enable = 0;
	ap_uint<1> ste_0_match_20_2_enable = 0;
	ap_uint<1> ste_0_match_20_3_enable = 0;
	ap_uint<1> ste_0_match_20_4_enable = 0;
	ap_uint<1> ste_0_match_20_5_enable = 0;
	ap_uint<1> ste_0_match_20_6_enable = 0;

	ap_uint<1> ste_0_match_21_0_enable = 0;
	ap_uint<1> ste_0_match_21_1_enable = 0;
	ap_uint<1> ste_0_match_21_2_enable = 0;
	ap_uint<1> ste_0_match_21_3_enable = 0;
	ap_uint<1> ste_0_match_21_4_enable = 0;
	ap_uint<1> ste_0_match_21_5_enable = 0;
	ap_uint<1> ste_0_match_21_6_enable = 0;

	ap_uint<1> ste_0_match_22_0_enable = 0;
	ap_uint<1> ste_0_match_22_1_enable = 0;
	ap_uint<1> ste_0_match_22_2_enable = 0;
	ap_uint<1> ste_0_match_22_3_enable = 0;
	ap_uint<1> ste_0_match_22_4_enable = 0;
	ap_uint<1> ste_0_match_22_5_enable = 0;
	ap_uint<1> ste_0_match_22_6_enable = 0;

	ap_uint<1> ste_0_match_23_0_enable = 0;
	ap_uint<1> ste_0_match_23_1_enable = 0;
	ap_uint<1> ste_0_match_23_2_enable = 0;
	ap_uint<1> ste_0_match_23_3_enable = 0;
	ap_uint<1> ste_0_match_23_4_enable = 0;
	ap_uint<1> ste_0_match_23_5_enable = 0;
	ap_uint<1> ste_0_match_23_6_enable = 0;

	// Mismatch state enables
	ap_uint<1> ste_0_mismatch_0_1_enable = 1;
	ap_uint<1> ste_0_mismatch_0_2_enable = 0;
	ap_uint<1> ste_0_mismatch_0_3_enable = 0;
	ap_uint<1> ste_0_mismatch_0_4_enable = 0;
	ap_uint<1> ste_0_mismatch_0_5_enable = 0;
	ap_uint<1> ste_0_mismatch_0_6_enable = 0;

	ap_uint<1> ste_0_mismatch_1_1_enable = 1;
	ap_uint<1> ste_0_mismatch_1_2_enable = 0;
	ap_uint<1> ste_0_mismatch_1_3_enable = 0;
	ap_uint<1> ste_0_mismatch_1_4_enable = 0;
	ap_uint<1> ste_0_mismatch_1_5_enable = 0;
	ap_uint<1> ste_0_mismatch_1_6_enable = 0;

	ap_uint<1> ste_0_mismatch_2_1_enable = 0;
	ap_uint<1> ste_0_mismatch_2_2_enable = 0;
	ap_uint<1> ste_0_mismatch_2_3_enable = 0;
	ap_uint<1> ste_0_mismatch_2_4_enable = 0;
	ap_uint<1> ste_0_mismatch_2_5_enable = 0;
	ap_uint<1> ste_0_mismatch_2_6_enable = 0;

	ap_uint<1> ste_0_mismatch_3_1_enable = 0;
	ap_uint<1> ste_0_mismatch_3_2_enable = 0;
	ap_uint<1> ste_0_mismatch_3_3_enable = 0;
	ap_uint<1> ste_0_mismatch_3_4_enable = 0;
	ap_uint<1> ste_0_mismatch_3_5_enable = 0;
	ap_uint<1> ste_0_mismatch_3_6_enable = 0;

	ap_uint<1> ste_0_mismatch_4_1_enable = 0;
	ap_uint<1> ste_0_mismatch_4_2_enable = 0;
	ap_uint<1> ste_0_mismatch_4_3_enable = 0;
	ap_uint<1> ste_0_mismatch_4_4_enable = 0;
	ap_uint<1> ste_0_mismatch_4_5_enable = 0;
	ap_uint<1> ste_0_mismatch_4_6_enable = 0;

	ap_uint<1> ste_0_mismatch_5_1_enable = 0;
	ap_uint<1> ste_0_mismatch_5_2_enable = 0;
	ap_uint<1> ste_0_mismatch_5_3_enable = 0;
	ap_uint<1> ste_0_mismatch_5_4_enable = 0;
	ap_uint<1> ste_0_mismatch_5_5_enable = 0;
	ap_uint<1> ste_0_mismatch_5_6_enable = 0;

	ap_uint<1> ste_0_mismatch_6_1_enable = 0;
	ap_uint<1> ste_0_mismatch_6_2_enable = 0;
	ap_uint<1> ste_0_mismatch_6_3_enable = 0;
	ap_uint<1> ste_0_mismatch_6_4_enable = 0;
	ap_uint<1> ste_0_mismatch_6_5_enable = 0;
	ap_uint<1> ste_0_mismatch_6_6_enable = 0;

	ap_uint<1> ste_0_mismatch_7_1_enable = 0;
	ap_uint<1> ste_0_mismatch_7_2_enable = 0;
	ap_uint<1> ste_0_mismatch_7_3_enable = 0;
	ap_uint<1> ste_0_mismatch_7_4_enable = 0;
	ap_uint<1> ste_0_mismatch_7_5_enable = 0;
	ap_uint<1> ste_0_mismatch_7_6_enable = 0;

	ap_uint<1> ste_0_mismatch_8_1_enable = 0;
	ap_uint<1> ste_0_mismatch_8_2_enable = 0;
	ap_uint<1> ste_0_mismatch_8_3_enable = 0;
	ap_uint<1> ste_0_mismatch_8_4_enable = 0;
	ap_uint<1> ste_0_mismatch_8_5_enable = 0;
	ap_uint<1> ste_0_mismatch_8_6_enable = 0;

	ap_uint<1> ste_0_mismatch_9_1_enable = 0;
	ap_uint<1> ste_0_mismatch_9_2_enable = 0;
	ap_uint<1> ste_0_mismatch_9_3_enable = 0;
	ap_uint<1> ste_0_mismatch_9_4_enable = 0;
	ap_uint<1> ste_0_mismatch_9_5_enable = 0;
	ap_uint<1> ste_0_mismatch_9_6_enable = 0;

	ap_uint<1> ste_0_mismatch_10_1_enable = 0;
	ap_uint<1> ste_0_mismatch_10_2_enable = 0;
	ap_uint<1> ste_0_mismatch_10_3_enable = 0;
	ap_uint<1> ste_0_mismatch_10_4_enable = 0;
	ap_uint<1> ste_0_mismatch_10_5_enable = 0;
	ap_uint<1> ste_0_mismatch_10_6_enable = 0;

	ap_uint<1> ste_0_mismatch_11_1_enable = 0;
	ap_uint<1> ste_0_mismatch_11_2_enable = 0;
	ap_uint<1> ste_0_mismatch_11_3_enable = 0;
	ap_uint<1> ste_0_mismatch_11_4_enable = 0;
	ap_uint<1> ste_0_mismatch_11_5_enable = 0;
	ap_uint<1> ste_0_mismatch_11_6_enable = 0;

	ap_uint<1> ste_0_mismatch_12_1_enable = 0;
	ap_uint<1> ste_0_mismatch_12_2_enable = 0;
	ap_uint<1> ste_0_mismatch_12_3_enable = 0;
	ap_uint<1> ste_0_mismatch_12_4_enable = 0;
	ap_uint<1> ste_0_mismatch_12_5_enable = 0;
	ap_uint<1> ste_0_mismatch_12_6_enable = 0;

	ap_uint<1> ste_0_mismatch_13_1_enable = 0;
	ap_uint<1> ste_0_mismatch_13_2_enable = 0;
	ap_uint<1> ste_0_mismatch_13_3_enable = 0;
	ap_uint<1> ste_0_mismatch_13_4_enable = 0;
	ap_uint<1> ste_0_mismatch_13_5_enable = 0;
	ap_uint<1> ste_0_mismatch_13_6_enable = 0;

	ap_uint<1> ste_0_mismatch_14_1_enable = 0;
	ap_uint<1> ste_0_mismatch_14_2_enable = 0;
	ap_uint<1> ste_0_mismatch_14_3_enable = 0;
	ap_uint<1> ste_0_mismatch_14_4_enable = 0;
	ap_uint<1> ste_0_mismatch_14_5_enable = 0;
	ap_uint<1> ste_0_mismatch_14_6_enable = 0;

	ap_uint<1> ste_0_mismatch_15_1_enable = 0;
	ap_uint<1> ste_0_mismatch_15_2_enable = 0;
	ap_uint<1> ste_0_mismatch_15_3_enable = 0;
	ap_uint<1> ste_0_mismatch_15_4_enable = 0;
	ap_uint<1> ste_0_mismatch_15_5_enable = 0;
	ap_uint<1> ste_0_mismatch_15_6_enable = 0;

	ap_uint<1> ste_0_mismatch_16_1_enable = 0;
	ap_uint<1> ste_0_mismatch_16_2_enable = 0;
	ap_uint<1> ste_0_mismatch_16_3_enable = 0;
	ap_uint<1> ste_0_mismatch_16_4_enable = 0;
	ap_uint<1> ste_0_mismatch_16_5_enable = 0;
	ap_uint<1> ste_0_mismatch_16_6_enable = 0;

	ap_uint<1> ste_0_mismatch_17_1_enable = 0;
	ap_uint<1> ste_0_mismatch_17_2_enable = 0;
	ap_uint<1> ste_0_mismatch_17_3_enable = 0;
	ap_uint<1> ste_0_mismatch_17_4_enable = 0;
	ap_uint<1> ste_0_mismatch_17_5_enable = 0;
	ap_uint<1> ste_0_mismatch_17_6_enable = 0;

	ap_uint<1> ste_0_mismatch_18_1_enable = 0;
	ap_uint<1> ste_0_mismatch_18_2_enable = 0;
	ap_uint<1> ste_0_mismatch_18_3_enable = 0;
	ap_uint<1> ste_0_mismatch_18_4_enable = 0;
	ap_uint<1> ste_0_mismatch_18_5_enable = 0;
	ap_uint<1> ste_0_mismatch_18_6_enable = 0;

	ap_uint<1> ste_0_mismatch_19_1_enable = 0;
	ap_uint<1> ste_0_mismatch_19_2_enable = 0;
	ap_uint<1> ste_0_mismatch_19_3_enable = 0;
	ap_uint<1> ste_0_mismatch_19_4_enable = 0;
	ap_uint<1> ste_0_mismatch_19_5_enable = 0;
	ap_uint<1> ste_0_mismatch_19_6_enable = 0;

	ap_uint<1> ste_0_mismatch_20_1_enable = 0;
	ap_uint<1> ste_0_mismatch_20_2_enable = 0;
	ap_uint<1> ste_0_mismatch_20_3_enable = 0;
	ap_uint<1> ste_0_mismatch_20_4_enable = 0;
	ap_uint<1> ste_0_mismatch_20_5_enable = 0;
	ap_uint<1> ste_0_mismatch_20_6_enable = 0;

	ap_uint<1> ste_0_mismatch_21_1_enable = 0;
	ap_uint<1> ste_0_mismatch_21_2_enable = 0;
	ap_uint<1> ste_0_mismatch_21_3_enable = 0;
	ap_uint<1> ste_0_mismatch_21_4_enable = 0;
	ap_uint<1> ste_0_mismatch_21_5_enable = 0;
	ap_uint<1> ste_0_mismatch_21_6_enable = 0;

	ap_uint<1> ste_0_mismatch_22_1_enable = 0;
	ap_uint<1> ste_0_mismatch_22_2_enable = 0;
	ap_uint<1> ste_0_mismatch_22_3_enable = 0;
	ap_uint<1> ste_0_mismatch_22_4_enable = 0;
	ap_uint<1> ste_0_mismatch_22_5_enable = 0;
	ap_uint<1> ste_0_mismatch_22_6_enable = 0;

	ap_uint<1> ste_0_mismatch_23_1_enable = 0;
	ap_uint<1> ste_0_mismatch_23_2_enable = 0;
	ap_uint<1> ste_0_mismatch_23_3_enable = 0;
	ap_uint<1> ste_0_mismatch_23_4_enable = 0;
	ap_uint<1> ste_0_mismatch_23_5_enable = 0;
	ap_uint<1> ste_0_mismatch_23_6_enable = 0;
	
	// Functions
	void configure(uint8_t config_symbol, uint8_t config_addr, uint8_t pattern_id);
	void set_lev_distance(ap_uint<8> lev_d);
	void reset(uint8_t pattern_id);
	void step(uint8_t input, ap_uint<1> &result, uint8_t pattern_id);
	void print_symbolset(uint8_t pattern_id);
	void print_state(uint8_t pattern_id);
	void print_lev_distance(uint8_t pattern_id);

};

#endif