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
#include "automata_single_file.hpp"

// Read Data from Global Memory and write into Stream inStream
static void read_input(InputPack *in, hls::stream<InputPacket> &outStream, int num_input_bytes)
{
    InputPacket inPacket = {};

    // Break the total input into large enough bursts to amortize read cost
    UINT num_burst_reads = (num_input_bytes / IO_READ_BURST);

    // Calculate number of input packets pushed into FIFO per burst read
    UINT num_packets_per_burst = IO_READ_BURST / INPUT_PACKETSIZE;

    for (UINT burst = 0; burst < num_burst_reads; burst++)
    {

        InputPack inBurst = in[burst];

        for (int packet_i = 0; packet_i < num_packets_per_burst; packet_i++)
        {
#pragma HLS pipeline II = 1

            int packet_offset = (packet_i * INPUT_PACKETSIZE);

            for (int symbol = 0; symbol < INPUT_PACKETSIZE; symbol++)
            {

                inPacket.symbols[symbol] = inBurst.symbols[packet_offset + symbol];
            }

            inPacket.done = 0;
            outStream << inPacket;
        }
    }

    // We're done
    inPacket.done = 1;
    outStream << inPacket;
}

// Mark input data as either configuration data or genome data
static void mark_input_packets(hls::stream<InputPacket> &inStream, hls::stream<InputPacket> &inStreamMarked)
{
    static UINT packetcounter = 0;
    static UBYTE ragg_id = 0;
    static UBYTE pattern_id = 0;

    while (1)
    {
#pragma HLS pipeline II = 1

        InputPacket inPack;
        inStream.read(inPack);
        InputPacket outPack = {};

        if (packetcounter < NUM_AUTOMATA)
        {
            ragg_id = packetcounter / RAGG_SIZE;
            pattern_id = packetcounter % RAGG_SIZE;

            outPack.ragg_id = ragg_id;
            outPack.pattern_id = pattern_id;
            outPack.config = true;
        }
        else
        {
            outPack.config = false;
            outPack.done = inPack.done;
        }
        for (int i = 0; i < INPUT_PACKETSIZE; i++)
        {
#pragma HLS UNROLL
            outPack.symbols[i] = inPack.symbols[i];
        }

        inStreamMarked.write(outPack);
        packetcounter += 1;

        if (outPack.done == 1)
        {
            break;
        }
    }
}

// Split input stream data into seperate FIFOS for automata groups, or send config data to specific group
static void splitter(hls::stream<InputPacket> &inStreamMarked, hls::stream<InputPacket> inStreamArray[NUM_RAGGS])
{
    InputPacket inPack;
    while (1)
    {
#pragma HLS pipeline II = 1
        inStreamMarked.read(inPack);

        // If config packet, send to specific automata group
        if (inPack.config)
        {
            UBYTE ragg_id = inPack.ragg_id;
            inStreamArray[ragg_id].write(inPack);
        }
        // Otherwise duplicate input packet among all groups
        else
        {
            for (UBYTE ragg_id = 0; ragg_id < NUM_RAGGS; ragg_id++)
            {
#pragma HLS UNROLL
                inStreamArray[ragg_id].write(inPack);
            }
        }

        if (inPack.done == 1)
        {
            break;
        }
    }
}

template <UBYTE ragg_id>
void compute_automata(hls::stream<InputPacket> &inStream, hls::stream<Match> &outStream)
{
#pragma HLS INLINE OFF
#pragma HLS FUNCTION_INSTANTIATE variable = ragg_id

    InputPacket inPack;
    UBYTE symbols[INPUT_PACKETSIZE];
    Match donematch = {0, 0, ragg_id};
    static UINT packetcounter = 0;
    static UINT counter = 0; //[NUM_RAGGS] = {0};

    static automata_0 automata0[RAGG_SIZE] = {};
#pragma HLS array_partition variable = automata0 type = complete

    while (1)
    {

        inStream.read(inPack);
        uint8_t pattern_id = inPack.pattern_id;

        if (inPack.done)
        {
            outStream.write(donematch);
            break;
        }
        else
        {

            for (int i = 0; i < INPUT_PACKETSIZE; i++)
            {
#pragma HLS unroll

                symbols[i] = inPack.symbols[i];
            }

            // This configuration pack is for me
            if (inPack.config)
            {
                if (inPack.ragg_id == ragg_id)
                {
                    UBYTE lev_distance = inPack.symbols[31];

                    for (int i = 0; i < 23; i++)
                    {
#pragma HLS pipeline II = 1

                        automata0[pattern_id].configure(symbols[i], i, pattern_id);
                    }

                    automata0[pattern_id].reset(pattern_id);
                    automata0[pattern_id].set_lev_distance(lev_distance);
                }
            }
            else
            {

                for (int symbol_i = 0; symbol_i < INPUT_PACKETSIZE; symbol_i++)
                {
#pragma HLS pipeline II = 1

                    UBYTE symbol = symbols[symbol_i];

                    ap_uint<1> result[RAGG_SIZE] = {0};
#pragma HLS array_partition variable = result type = complete

                    ap_uint<RAGG_SIZE> combined_result = 0;

                    for (int automata_id = 0; automata_id < RAGG_SIZE; automata_id++)
                    {
#pragma HLS UNROLL
                        automata0[automata_id].step(symbol, result[automata_id], automata_id);

                    }

                    for (int automata_id = 0; automata_id < RAGG_SIZE; automata_id++)
                    {
#pragma HLS UNROLL
                        combined_result[automata_id] = result[automata_id];
                    }

                    USHORT ridPlusOne = combined_result.to_int();

                    if (ridPlusOne != 0)
                    {

                        Match match;
                        match.ridPlusOne = ridPlusOne;
                        match.ragg_id = ragg_id;
                        match.valid = 1;
                        match.pos = counter;
                        outStream.write(match);
                    }

                    counter += 1;
                }
            }
        }
        packetcounter += 1;
    }
}

#define LOOP(n)                                                   \
    for (int i = 0; i < n; i++)                                   \
    {                                                             \
        compute_automata<i>(inStreamArray[i], outStreamArray[i]); \
    }

static void parallel_automata(hls::stream<InputPacket> inStreamArray[NUM_RAGGS], hls::stream<Match> outStreamArray[NUM_RAGGS])
{
#pragma HLS inline
#pragma HLS array_partition variable = inStreamArray type = complete
#pragma HLS array_partition variable = outStreamArray type = complete

    compute_automata<0>(inStreamArray[0], outStreamArray[0]);
    compute_automata<1>(inStreamArray[1], outStreamArray[1]);
    compute_automata<2>(inStreamArray[2], outStreamArray[2]);
    compute_automata<3>(inStreamArray[3], outStreamArray[3]);
    compute_automata<4>(inStreamArray[4], outStreamArray[4]);
    compute_automata<5>(inStreamArray[5], outStreamArray[5]);
    compute_automata<6>(inStreamArray[6], outStreamArray[6]);
    compute_automata<7>(inStreamArray[7], outStreamArray[7]);

    // For additional Groups, add more streams
    /*
    compute_automata<8>(inStreamArray[8], outStreamArray[8]);
    compute_automata<9>(inStreamArray[9], outStreamArray[9]);
    compute_automata<10>(inStreamArray[10], outStreamArray[10]);
    compute_automata<11>(inStreamArray[11], outStreamArray[11]);
    compute_automata<12>(inStreamArray[12], outStreamArray[12]);
    compute_automata<13>(inStreamArray[13], outStreamArray[13]);
    compute_automata<14>(inStreamArray[14], outStreamArray[14]);
    compute_automata<15>(inStreamArray[15], outStreamArray[15]);
    compute_automata<16>(inStreamArray[16], outStreamArray[16]);
    compute_automata<17>(inStreamArray[17], outStreamArray[17]);
    compute_automata<18>(inStreamArray[18], outStreamArray[18]);
    compute_automata<19>(inStreamArray[19], outStreamArray[19]);
    compute_automata<20>(inStreamArray[20], outStreamArray[20]);
    compute_automata<21>(inStreamArray[21], outStreamArray[21]);
    compute_automata<22>(inStreamArray[22], outStreamArray[22]);
    compute_automata<23>(inStreamArray[23], outStreamArray[23]);
    compute_automata<24>(inStreamArray[24], outStreamArray[24]);
    compute_automata<25>(inStreamArray[25], outStreamArray[25]);
    compute_automata<26>(inStreamArray[26], outStreamArray[26]);
    compute_automata<27>(inStreamArray[27], outStreamArray[27]);
    compute_automata<28>(inStreamArray[28], outStreamArray[28]);
    compute_automata<29>(inStreamArray[29], outStreamArray[29]);
    compute_automata<30>(inStreamArray[30], outStreamArray[30]);
    compute_automata<31>(inStreamArray[31], outStreamArray[31]);
    compute_automata<32>(inStreamArray[32], outStreamArray[32]);
    compute_automata<33>(inStreamArray[33], outStreamArray[33]);
    compute_automata<34>(inStreamArray[34], outStreamArray[34]);
    compute_automata<35>(inStreamArray[35], outStreamArray[35]);
    compute_automata<36>(inStreamArray[36], outStreamArray[36]);
    compute_automata<37>(inStreamArray[37], outStreamArray[37]);
    compute_automata<38>(inStreamArray[38], outStreamArray[38]);
    compute_automata<39>(inStreamArray[39], outStreamArray[39]);
    compute_automata<40>(inStreamArray[40], outStreamArray[40]);
    compute_automata<41>(inStreamArray[41], outStreamArray[41]);
    compute_automata<42>(inStreamArray[42], outStreamArray[42]);
    compute_automata<43>(inStreamArray[43], outStreamArray[43]);
    compute_automata<44>(inStreamArray[44], outStreamArray[44]);
    compute_automata<45>(inStreamArray[45], outStreamArray[45]);
    compute_automata<46>(inStreamArray[46], outStreamArray[46]);
    compute_automata<47>(inStreamArray[47], outStreamArray[47]);
    compute_automata<48>(inStreamArray[48], outStreamArray[48]);
    compute_automata<49>(inStreamArray[49], outStreamArray[49]);
    compute_automata<50>(inStreamArray[50], outStreamArray[50]);
    compute_automata<51>(inStreamArray[51], outStreamArray[51]);
    compute_automata<52>(inStreamArray[52], outStreamArray[52]);
    compute_automata<53>(inStreamArray[53], outStreamArray[53]);
    compute_automata<54>(inStreamArray[54], outStreamArray[54]);
    compute_automata<55>(inStreamArray[55], outStreamArray[55]);
    compute_automata<56>(inStreamArray[56], outStreamArray[56]);
    compute_automata<57>(inStreamArray[57], outStreamArray[57]);
    compute_automata<58>(inStreamArray[58], outStreamArray[58]);
    compute_automata<59>(inStreamArray[59], outStreamArray[59]);
    compute_automata<60>(inStreamArray[60], outStreamArray[60]);
    compute_automata<61>(inStreamArray[61], outStreamArray[61]);
    compute_automata<62>(inStreamArray[62], outStreamArray[62]);
    compute_automata<63>(inStreamArray[63], outStreamArray[63]);*/
}

// Combine match results across automata groups and keep track of DONE packets
static void combiner(hls::stream<Match> outStreamArray[NUM_RAGGS], hls::stream<Match> &matchStream)
{
    Match inMatch[NUM_RAGGS] = {};
#pragma HLS array_partition variable = inMatch type = complete

    BOOL valid_read[NUM_RAGGS] = {};
#pragma HLS array_partition variable = valid_read type = complete

    BOOL dones[NUM_RAGGS] = {};
#pragma HLS array_partition variable = dones type = complete

    Match donematch = {0, 0, 0};

    while (true)
    {

        BOOL done = true;

        for (int ragg_id = 0; ragg_id < NUM_RAGGS; ragg_id++)
        {
#pragma HLS UNROLL

            valid_read[ragg_id] = outStreamArray[ragg_id].read_nb(inMatch[ragg_id]);
        }

        for (int ragg_id = 0; ragg_id < NUM_RAGGS; ragg_id++)
        {
#pragma HLS UNROLL

            if (valid_read[ragg_id])
            {
                // Set the ragg's done bit to true if it ever receives an invalid flit
                dones[ragg_id] |= !(inMatch[ragg_id].valid);
            }
        }

        for (int ragg_id = 0; ragg_id < NUM_RAGGS; ragg_id++)
        {
#pragma HLS UNROLL
            done &= dones[ragg_id];
        }

        if (done)
        {
            matchStream.write(donematch);
            break;
        }

        for (int ragg_id = 0; ragg_id < NUM_RAGGS; ragg_id++)
        {
            if (valid_read[ragg_id])
            {
                if (inMatch[ragg_id].valid)
                    matchStream.write(inMatch[ragg_id]);
            }
        }
    }
}

// Read result from outStream and write the result to Global Memory
static void write_result(MatchPack *out, hls::stream<Match> &matchStream)
{
    // Auto-pipeline is going to apply pipeline to this loop
    int next_index = 0;
    int match_i = 0;
    Match match;
    MatchPack matchpack = {};
    hls::vector<BOOL, NUM_RAGGS> done_vector = false;

    while (1)
    {
#pragma HLS pipeline II = 1

        matchStream.read(match);
        matchpack.matches[match_i++] = match;

        if (match.valid == 0)
        {
            out[next_index++] = matchpack;
            break;
        }
        else
        {
            if (match_i == OUTPUT_PACKETSIZE)
            {
                out[next_index++] = matchpack;
                matchpack = {};
                match_i = 0;
            }
        }
    }

    return;
}

extern "C"
{
    /*
        Levenshtein Automata Matching Kernel Implementation using dataflow
        Arguments:
            in   (input)  --> Input Vector (configuration and genomic data)
            out  (output) --> Output Vector (matching results)
            vSize (input)  --> Size of Vector in Integer (number of inputs)
    */
    void krnl_automata(InputPack *in, MatchPack *out, int num_input)
    {
#pragma HLS INTERFACE mode = m_axi depth = 1024 port = in bundle = gmem0
#pragma HLS INTERFACE mode = m_axi depth = 1024 port = out bundle = gmem1
#pragma HLS INTERFACE ap_ctrl_chain port = return

        // These FIFO are hls::stream objects that synthesize to FIFOs on the FPGA. 
        // They are used to connect the different stages of the dataflow.
        hls::stream<InputPacket, 16> inStream("input_stream");
        hls::stream<InputPacket, 16> inStreamMarked("input_stream_marked");

        // These are arrays of streams that allow us to have multiple parallel 
        // groups of Levenshtein automata
        static hls::stream<InputPacket> inStreamArray[NUM_RAGGS];
        static hls::stream<Match> outStreamArray[NUM_RAGGS];
        hls::stream<Match, 16> matchStream("match_stream");

#pragma HLS dataflow

        // dataflow pragma instruct compiler to run following six functions in parallel
        read_input(in, inStream, num_input);
        mark_input_packets(inStream, inStreamMarked);
        splitter(inStreamMarked, inStreamArray);
        parallel_automata(inStreamArray, outStreamArray);
        combiner(outStreamArray, matchStream);
        write_result(out, matchStream);
    }
}
