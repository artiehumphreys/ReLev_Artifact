#*************************************************************************
# MIT License
# 
# Copyright (c) 2025 Tommy Tracy II, University of Virginia
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#**************************************************************************

# Create a project
open_project -reset proj_automata

# Add design files
add_files krnl_automata.cpp 
add_files automata_single_file.cpp
add_files host/util.cpp

# Add test bench & files
add_files -tb krnl_automata_test.cpp

# Set the top-level function
set_top krnl_automata 

# ########################################################
# Create a solution
open_solution -reset solution1
# Define technology and clock rate
set_part  {xcu280-fsvh2892-2L-e}
create_clock -period 1.25 

# Set variable to select which steps to execute
set hls_exec 0

csim_design -clean
exit

