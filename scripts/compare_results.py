# *************************************************************************
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
# **************************************************************************
import sys
from collections import OrderedDict

def get_hyperscan_results(filename):

    results = OrderedDict()

    with open(filename, "r") as f:
        for line in f:
            if 'for' in line:
                # Extract the pattern ID and the number of matches
                parts = line.split()
                location = int(parts[1].split(':')[-1])
                pattern_id = int(parts[3])
                
                if location in results:
                    results[location].add(pattern_id)
                else:
                    results[location] = set([pattern_id])

    return results

def get_relev_results(filename):

    results = OrderedDict()

    with open(filename, "r") as f:
        for line in f:
            if 'Match' in line:
                # Extract the pattern ID and the number of matches
                parts = line.split()
                location = int(parts[1])
                pattern_id = int(parts[3])

                if location in results:
                    results[location].add(pattern_id)
                else:
                    results[location] = set([pattern_id])
    
    return results

if __name__ == "__main__":

    if len(sys.argv) != 3:
        print("Usage: python compare_results.py <hyperscan_results_file> <relev_results_file>")
        sys.exit(1)
        
    hyperscan_results_file = sys.argv[1]
    relev_results_file = sys.argv[2]
    hyperscan_results = get_hyperscan_results(hyperscan_results_file)
    relev_results = get_relev_results(relev_results_file)

    # Compare the results
    for hs_location, relev_location in zip(hyperscan_results, relev_results):
        if hs_location != relev_location:
            print(f"Location mismatch: Hyperscan found matches at location {hs_location} but Relev found matches at location {relev_location}")
            sys.exit(1)
        
        hs_pattern_ids = hyperscan_results[hs_location]
        relev_pattern_ids = relev_results[relev_location]

        for hs_pattern_id in hs_pattern_ids:
            
            if (hs_pattern_id - 1) not in relev_pattern_ids:
                print(f"Pattern ID mismatch at location {hs_location}: Hyperscan found pattern IDs {hs_pattern_ids} but Relev found pattern IDs {relev_pattern_ids}")
                sys.exit(1)
            
        for relev_pattern_id in relev_pattern_ids:
            if (relev_pattern_id + 1) not in hs_pattern_ids:
                print(f"Pattern ID mismatch at location {hs_location}: Hyperscan found pattern IDs {hs_pattern_ids} but Relev found pattern IDs {relev_pattern_ids}")
                sys.exit(1)

    print("All results match!")
    sys.exit(0)