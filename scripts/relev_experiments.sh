# /*************************************************************************
# MIT License

# Copyright (c) 2025 Tommy Tracy II, University of Virginia

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
# **************************************************************************/

# This script will run Hyperscan and ReLev experiments and compare results for correctness
# as well as generating throughput results for both.
# This may take several hours to complete!

# DEBUGGING: If you get FPGA runtime errors, you may have to insert a longer sleep between runs
# The hot-reset takes several seconds

# WARNING: The throughput results for ReLev are in Mega BYTES per second, 
# while the throughput results for Hyperscan are in Mega BITS per second

# Change this to the location where you have installed hyperscan and built hsbench
HSBENCHLOCATION=/home/tjt7a/src/hyperscan/build/bin/hsbench

# Experiments to verify correctness of Relev results
for e in {0..6}; do

    # For now, we need to hot-reset the FPGA between runs, because the counter won't go back to 0 between kernel calls
    xbutil reset --device 61:00.1 --force > /dev/null
    sleep 5
    echo "Running experiment with edit distance $e"
    ../fpga/host.exe ../fpga/automata.hw.xclbin ../input/chr1.txt ../patterns/128guides.txt $e > relev_out_ed$e
    echo "ReLev throughput in Mega BYTES/sec: "
    cat relev_out_ed$e | grep Throughput
    echo ""
    $HSBENCHLOCATION -e ../patterns/128guides.out -c ../input/chr1.db -n 1 -E $e > hyperscan_output_ed$e
    $HSBENCHLOCATION -e ../patterns/128guides.out -c ../input/chr1.db -n 1 -E $e -T0-15 > hyperscan_16core_output_ed$e
    echo "Hyperscan (1 core) throughput in Mega BITS/sec: "
    cat hyperscan_output_ed$e | grep "Mean throughput"
    echo "Hyperscan (16 cores) throughput in Mega BITS/sec: "
    cat hyperscan_16core_output_ed$e | grep "Mean throughput"
    echo ""
    python3 compare_results.py hyperscan_output_ed$e relev_out_ed$e

    # Remove the output files
    rm relev_out_ed$e hyperscan_output_ed$e hyperscan_16core_output_ed$e

    if [ $? -ne 0 ]; then
        echo "Experiment $e failed: Results do not match!"
        exit 1
    else
        echo "Experiment $e passed: Results match!"
        echo "--------------------------------"
    fi
done
