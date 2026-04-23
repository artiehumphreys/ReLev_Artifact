# Key width: override with 2nd arg
#   vitis_hls -f run_hls.tcl 16
if {$argc > 2} {
    set KEY_BITS [lindex $argv 2]
} else {
    set KEY_BITS 32
}

# Create a project
open_project -reset proj_bloom

# Add design files
add_files krnl_bloom.cpp -cflags "-DKEY_BITS=${KEY_BITS}"

# Add test bench
add_files -tb krnl_bloom_test.cpp -cflags "-DKEY_BITS=${KEY_BITS}"

# Set the top-level function
set_top krnl_bloom

# Create a solution
open_solution -reset solution1
# Target Alveo U280
set_part {xcu280-fsvh2892-2L-e}
create_clock -period 1.25

# Run C-simulation (pass keys file as argument)
set curr_dir [pwd]
csim_design -clean -argv "$curr_dir/log.txt"
