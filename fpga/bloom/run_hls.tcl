# Args: vitis_hls -f run_hls.tcl [KEY_BITS] [FILTER_TYPE]
# Example: vitis_hls -f run_hls.tcl 32 BF_ONLY

if {$argc > 2} {
    set KEY_BITS [lindex $argv 2]
} else {
    set KEY_BITS 32
}

# New logic to handle the Filter Flag
if {$argc > 3} {
    set FILTER_TYPE [lindex $argv 3]
} else {
    set FILTER_TYPE "FULL"
}

set CFLAGS "-DKEY_BITS=${KEY_BITS}"
if {$FILTER_TYPE == "BF_ONLY"} {
    append CFLAGS " -DBUILD_BF_ONLY"
} elseif {$FILTER_TYPE == "CBF_ONLY"} {
    append CFLAGS " -DBUILD_CBF_ONLY"
} elseif {$FILTER_TYPE == "CF_ONLY"} {
    append CFLAGS " -DBUILD_CF_ONLY"
}

open_project -reset proj_bloom

# Add files with the updated CFLAGS
add_files krnl_bloom.cpp -cflags "$CFLAGS"
add_files -tb krnl_bloom_test.cpp -cflags "$CFLAGS"

set_top krnl_bloom

open_solution -reset solution1
set_part {xcu280-fsvh2892-2L-e}

# Using 2.0ns for 500 MHz (your hardware goal) 
# Note: Your current script says 1.25 (800 MHz), which is very aggressive!
create_clock -period 2.0

set curr_dir [pwd]
csim_design -clean -argv "$curr_dir/log.txt"
