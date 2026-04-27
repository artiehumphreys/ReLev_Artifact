#!/usr/bin/env bash
set -euo pipefail

BLOOM_DIR="$(cd "$(dirname "$0")/../fpga/bloom" && pwd)"
LOG_FILE="${1:?usage: $0 <log_file> [csim|hw_emu|hw]}"
TARGET="${2:-hw}"

if [ "$TARGET" = "csim" ]; then
  cd "$BLOOM_DIR"
  vitis_hls -f run_hls.tcl
else
  cd "$BLOOM_DIR"
  make host TARGET="$TARGET"
  XCLBIN="bloom.${TARGET}.xclbin"
  if [ "$TARGET" = "hw_emu" ]; then
    make emconfig.json
    export XCL_EMULATION_MODE="$TARGET"
  fi
  ./host.exe "$XCLBIN" "$LOG_FILE" cf
fi
