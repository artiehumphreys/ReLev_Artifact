# ReLev_Artifact
A runtime-reconfigurable Levenshtein Automata Overlay for accelerating edit distance computations on an Alveo FPGA.
This repository contains all of the code you will need to duplicate our ReLev results and evaluate them against
Hyperscan.

# Some Prerequisites
This project targets the AMD Vitis Platform, and has been tested on the AMD Alveo U280. The other Alveo cards can also be used, but make sure that the HBM_connectivity.cfg file is updated with Global Memory mappings; the U280 has HBM2. Other cards do not, so target DDR instead.

This code can be ported to the new Versal platform and run on the V80, but this requires copying over the HLS components from Vitis to the Alveo Versal Example Design (AVED).

All experiments were performed on a Linux workstation with the following configuration:

## Hardware
- AMD Ryzen Threadripper PRO 5955WX 16-Cores (any x86 CPU should be fine)
- 512GB DRAM (64GB should be sufficient)
- AMD Alveo U280 FPGA

## Software
- Ubuntu 22.04.05 with the Linux 5.15 kernel
- GCC version 11.4
- Vitis HLS version 2023.2

# To reproduce Hyperscan Results:
1. Install Hyperscan from https://github.com/intel/hyperscan; IMPORTANT: this can only be done on an x86 machine; also make sure all dependencies are installed for hsbench. We will use Hyperscan's benchmarking program (hsbench) for comparison.
2. Update the location of Hyperscan in scripts/relev_experiments.sh to reflect your install location

# To reproduce FPGA Results:
1. Make sure the Makefile variables are correctly set, especially the DEVICE variable.
2. Unzip chr1.txt.gz - `cd input; gunzip chr1.txt.gz`
3. Unzip chr1.db.gz - `cd input; gunzip chr1.db.gz`
4. Compile the relev overlay - `make automata && make xclbin`
5. Compile the host executable - `make host`
6. Run the reproducibility script - `cd scripts; ./relev_experiments.sh`

# For additional debugging and development

The project is broken up in several key components:

## The Kernel ##

The FPGA kernel is implemented in the krnl_automata.cpp file. This file implements the dataflow architecture and the FIFOs that connect HLS functions.

## The Levenshtein Automaton ##

The Levenshtein Automaton is implemented in automata_single_file.cpp. This file implements the Levenshtein Automaton overlay in HLS.

## For Simulation ##

fpga/run_hls.tcl contains the TCL script for simulating the overlay on the full design, but for a small part of the first human chromosome for testing and debugging. To run:
1. Update the input_filename and pattern_filename in fpga/kernel_automata_test.cpp to reflect the location of the repository and input files.
2. Run the simulation; this will take several minutes - `cd fpga; vitis_hls -f run_hls.tcl`