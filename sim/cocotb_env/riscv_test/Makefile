# This file is public domain, it can be freely copied without restrictions.
# SPDX-License-Identifier: CC0-1.0

# Makefile

# defaults
SIM ?= verilator
TOPLEVEL_LANG ?= verilog

VERILOG_SOURCES += $(PWD)/../../../rtl/sim_top.sv  # Add sim_top module (sim_top.sv) file
VERILOG_SOURCES += $(PWD)/../../../rtl/core.v  # Add core module (core.v) file


# TOPLEVEL is the name of the toplevel module in your Verilog or VHDL file
TOPLEVEL = sim_top

# MODULE is the basename of the Python test file
MODULE = sim_top

EXTRA_ARGS += --trace

# include cocotb's make rules to take care of the simulator setup
include $(shell cocotb-config --makefiles)/Makefile.sim
