import cocotb
from cocotb.triggers import Timer, RisingEdge

# Generate clock signals
async def generate_clock(dut):
    while True:
        dut.clk.value = 0
        await Timer(1, units="ns")
        dut.clk.value = 1
        await Timer(1, units="ns")
        log_signals(dut)

# Log signals at each clock cycle
def log_signals(dut):
    # Log signals (add signals as needed)
    dut._log.info(
        f"reset={dut.rst.value}, "
        f"result_pass={dut.result_pass.value}, "
        f"result_valid={dut.result_valid.value}"
    )

@cocotb.test()
async def core_test_(dut):
    cocotb.start_soon(generate_clock(dut))
    
    dut.rst.value = 1
    await RisingEdge(dut.clk)
    dut.rst.value = 0
    
    # Run for a few cycles
    for _ in range(20):
        await RisingEdge(dut.clk)
        # insert insturction here
    
    dut._log.info("Core simple test completed.")
