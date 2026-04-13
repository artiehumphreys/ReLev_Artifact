# Create a project
open_project -reset proj_bloom

# Add design files
add_files krnl_bloom.cpp

# Add test bench
add_files -tb krnl_bloom_test.cpp

# Set the top-level function
set_top krnl_bloom

# Create a solution
open_solution -reset solution1
# Target Alveo U280
set_part {xcu280-fsvh2892-2L-e}
create_clock -period 1.25

# Run C-simulation (pass keys file as argument)
set curr_dir [pwd]
csim_design -clean -argv "$curr_dir/keys.txt"
