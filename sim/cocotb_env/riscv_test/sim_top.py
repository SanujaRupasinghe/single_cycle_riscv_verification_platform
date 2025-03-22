import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge
import struct
from riscvmodel.code import decode


# Load instructions from file (add.text)
def load_instructions(filename):
    with open(filename, "rb") as f:
        data = f.read()
    instructions = [data[i:i+4] for i in range(0, len(data), 4)]  # Read 4-byte (32-bit) chunks
    return [struct.unpack("<I", inst)[0] for inst in instructions]  # Convert to integer

@cocotb.test()
async def test_instruction_memory(dut):
    """Test instruction memory programming"""
    
    # Start the clock (10 ns period -> 100 MHz)
    cocotb.start_soon(Clock(dut.clk, 10, units="ns").start())

    # Reset DUT for x cycles
    x = 5  # Change x to any number of cycles
    dut.reset.value = 1
    dut.programming_data_valid.value = 0
    dut.programming_done.value = 0

    for _ in range(x):
        await RisingEdge(dut.clk)  # Wait for x clock cycles

    # Load instructions from the file
    instructions = load_instructions("add.text")

    dut.reset.value = 0
    # Program the instruction memory
    for i, inst in enumerate(instructions):
        dut.inst_mem_offset.value = i  # Address to write
        dut.inst.value = inst           # Instruction value
        dut.programming_data_valid.value = 1
        await RisingEdge(dut.clk)

    # Mark programming as done
    dut.programming_data_valid.value = 0
    dut.programming_done.value = 1
    await RisingEdge(dut.clk)
    dut.programming_done.value = 0

    # Verify if instructions were written correctly
    for i, expected_inst in enumerate(instructions):
        assert int(dut.instruction_memory[i]) == expected_inst, f"Mismatch at {i}: Expected {expected_inst}, got {int(dut.instruction_memory[i])}"
        try:
            decodedInst = decode(expected_inst)
            dut._log.info(f"Instruction {i}: {expected_inst:08x} == {int(dut.instruction_memory[i]):08x} == {decodedInst}")
        except:
            dut._log.info(f"Instruction {i}: {expected_inst:08x} == {int(dut.instruction_memory[i]):08x}")

    print("Instruction Memory Programmed Successfully")