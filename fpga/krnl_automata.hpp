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

#ifndef _KRNL_AUTOMATA_H_
#define _KRNL_AUTOMATA_H_

// Includes
#include <iostream>
#include <ap_int.h>
#include <hls_stream.h>
#include "hls_task.h"
#include <bitset>
#include <hls_vector.h>


#define IO_READ_BURST (64)	// 64 bytes = 512 bits, max width of HBM
#define IO_WRITE_BURST (64)

#define INPUT_PACKETSIZE (32)
#define OUTPUT_PACKETSIZE (8)

#define NUM_AUTOMATA (128)
#define RAGG_SIZE (16)
#define NUM_RAGGS (8)

const int size = 1000;

typedef ap_uint<1> U1BIT; // 1-bit generic
typedef ap_uint<30> U30BIT; // 30-bit generic
typedef uint16_t USHORT; // 2 bytes
typedef uint8_t UBYTE;  // a byte
typedef uint32_t UINT; // an unsigned int
typedef bool BOOL;

// We send over <IO_READ_BURST> chunks of symbols
struct InputPack {
	UBYTE symbols[IO_READ_BURST];
};

struct InputPacket {
	UBYTE symbols[INPUT_PACKETSIZE];
	USHORT done;
	BOOL config;
	UBYTE ragg_id;
	UBYTE pattern_id;
};

/*
	For now, this match flit can index
	There are 256 possible Report Aggregator bins
	There are 16 one-hot bits per RAGG
	256 * 16 or 4k automata
*/
struct Match {
	UINT pos;		//  Detection position up to 1 billion
	USHORT ridPlusOne; // MATCH STATE ID + 1; 0 means invalid
	UBYTE ragg_id;		// index of the range of automata
	UBYTE valid { 0 };
};

// 8 matches (8 bytes per match) = 64 bytes = 512 bits wide
struct MatchPack {
	Match matches[OUTPUT_PACKETSIZE];
};

struct MarkedMatchPack{
	MatchPack matchpack;
	UBYTE done;
};

extern "C" {
	void krnl_automata(InputPack* input, MatchPack* output, int num_input_bytes);
}

#endif
