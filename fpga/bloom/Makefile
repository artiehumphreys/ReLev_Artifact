VPP := $(XILINX_VITIS)/bin/v++
EMCONFIGUTIL := $(XILINX_VITIS)/bin/emconfigutil
TARGET := hw
DEVICE := /opt/xilinx/platforms/xilinx_u280_gen3x16_xdma_1_202211_1/xilinx_u280_gen3x16_xdma_1_202211_1.xpfm

# Key width: 16 or 32.  Must match between kernel and host.
#   make all KEY_BITS=16
#   make all KEY_BITS=32   (default)
KEY_BITS ?= 32

# kernel targets
BLOOM_XO := bloom.$(TARGET).xo
XCLBIN := bloom.$(TARGET).xclbin

# host target
HOST_EXE := host.exe

# config files target
EMCONFIG_FILE := emconfig.json

VPP_OPTS := -s -t $(TARGET) --platform $(DEVICE)
VPP_OPTS += --temp_dir ./all_builds/$(TARGET)
VPP_OPTS += --report_dir ./all_logs/$(TARGET)
VPP_OPTS += --log_dir ./all_logs/$(TARGET)
VPP_LINK_OPTS += --config HBM_connectivity.cfg

CFLAGS := -g -std=c++1y -DKEY_BITS=$(KEY_BITS) -I$(XILINX_XRT)/include -I$(XILINX_HLS)/include
LFLAGS := -L$(XILINX_XRT)/lib -lOpenCL -lxrt_coreutil -lrt -luuid

# Input: single log file — one "pid ppid is_shell" per line
# ppid=0 marks seed PIDs (roots of suspicious subtrees)
CMD_ARGS := bloom.$(TARGET).xclbin log.txt

# primary build targets
.PHONY: bloom xclbin host all clean cleanall

bloom: $(BLOOM_XO)
xclbin: $(XCLBIN)
host: $(HOST_EXE)

all: xclbin host

clean:
	-$(RM) $(EMCONFIG_FILE) $(HOST_EXE) $(XCLBIN)

cleanall: clean
	rm -rf all_* *.log *.xclbin *.compile_summary *.link_summary *.info *.xo *.hw.* *.hw_emu.*

# kernel rules
$(BLOOM_XO): krnl_bloom.cpp
	$(RM) $@
	$(VPP) $(VPP_OPTS) -c --hls.clock 500000000:krnl_bloom -k krnl_bloom -DKEY_BITS=$(KEY_BITS) -I'$(<D)' -o $@ $+

$(XCLBIN): $(BLOOM_XO)
	$(VPP) $(VPP_OPTS) $(VPP_LINK_OPTS) -l -o $@ $(BLOOM_XO)

# host rules
$(HOST_EXE): ./host/host.cpp
	g++ $(CFLAGS) -o $@ $+ $(LFLAGS)
	@echo 'Compiled Host Executable: $(HOST_EXE) (KEY_BITS=$(KEY_BITS))'

$(EMCONFIG_FILE):
	$(EMCONFIGUTIL) --nd 1 --od . --platform $(DEVICE)

run: $(XCLBIN) $(HOST_EXE) $(EMCONFIG_FILE)
	XCL_EMULATION_MODE=$(TARGET) ./$(HOST_EXE) $(CMD_ARGS)
