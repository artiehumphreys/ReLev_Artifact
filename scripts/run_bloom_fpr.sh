#!/usr/bin/env bash
set -euo pipefail

BLOOM_DIR="$(cd "$(dirname "$0")/../fpga/bloom" && pwd)"
BIN="$BLOOM_DIR/bloom_fpr_test"

g++ -std=c++23 -O2 -o "$BIN" "$BLOOM_DIR/bloom_fpr_test.cpp"

echo ""
"$BIN"
