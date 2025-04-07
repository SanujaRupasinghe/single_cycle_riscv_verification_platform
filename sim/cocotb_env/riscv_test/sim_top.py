import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer
import struct
from tabulate import tabulate
from riscvmodel.code import decode


@cocotb.test()
async def processor_test(dut):
    target_text = "target_texts/jal.text"
    global instructions
    instructions = load_instructions(target_text)
    dut._log.info(f"Testing {target_text}")

    # Start the clock (10 ns period -> 100 MHz)
    clock1 = cocotb.start_soon(Clock(dut.clk, 10, units="ns").start())

    # Reset DUT for x cycles
    x = 5  # Change x to any number of cycles
    dut.reset.value = 1
    dut.programming_data_valid.value = 0
    dut.programming_done.value = 0

    for _ in range(x):
        await RisingEdge(dut.clk)  # Wait for x clock cycles

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

    verify_instruction_memory(dut, verbose=1)
    
    clock1.cancel()
    cocotb.start_soon(generate_clock(dut))

    # for i in range(8):
    #     await RisingEdge(dut.clk)

    while True:
        await RisingEdge(dut.clk)
        if (dut.result_valid.value and dut.result_passed.value) or dut.pc.value == len(instructions) * 4:
            if dut.result_valid.value and dut.result_passed.value:
                dut._log.info("Test passed")
            else:
                dut._log.error("Test failed")
            break

    save_log_signals("log_signals.txt", log_signal_table)
    read_reg_file(dut)
    

# Load instructions from file (add.text)
def load_instructions(filename):
    with open(filename, "rb") as f:
        data = f.read()
    instructions = [data[i:i+4] for i in range(0, len(data), 4)]  # Read 4-byte (32-bit) chunks
    return [struct.unpack("<I", inst)[0] for inst in instructions]  # Convert to integer


def read_reg_file(dut, filename="reg_file.text"):
    with open(filename, "w") as f:
        for i in range(32):
            reg_value = int(dut.u_core.register_file[i])
            f.write(f"x{i:02d}: {reg_value:08x}\n")
    dut._log.info("reg_file written successfully")



def verify_instruction_memory(dut, verbose=0):
    for i, expected_inst in enumerate(instructions):
        if verbose:
            try:
                decodedInst = decode(expected_inst)
                dut._log.info(f"PC {i*4:08x}: {expected_inst:08x} == {int(dut.instruction_memory[i]):08x} == {decodedInst}")
            except:
                dut._log.info(f"PC {i*4:08x}: {expected_inst:08x} == {int(dut.instruction_memory[i]):08x}")
        if int(dut.instruction_memory[i]) != expected_inst:
            dut._log.error(f"Mismatch at {i}: Expected {expected_inst:08x}, got {int(dut.instruction_memory[i]):08x}")
            raise AssertionError(f"Mismatch at {i}: Expected {expected_inst:08x}, got {int(dut.instruction_memory[i]):08x}")
    else:
        dut._log.info("All instructions verified successfully.")
        

# generate clock signals with logging at each posedge
async def generate_clock(dut):
    while True:
        dut.clk.value = 0
        await Timer(10, units="ns")
        dut.clk.value = 1
        await Timer(10, units="ns")
        log_signals(dut)  # Log signal data at rising edge


log_signal_table = []

def log_signals(dut):
    """Log all relevant DUT signals to a list."""
    global log_signal_table
    row = [
        f"{int(dut.pc.value):08x}",
        f"{int(dut.u_core.next_pc.value):08x}",
        f"{int(dut.instr.value):08x}",
        f"{int(dut.u_core.write_back_data.value):08x}",
        f"{int(dut.u_core.write_to_reg_file.value)}",
        f"{int(dut.memory_address.value):08x}",
        f"{int(dut.read_data.value):08x}",
        f"{int(dut.write_data.value)}",
        f"{int(dut.data_to_write.value):08x}",
        f"{int(dut.u_core.i_type_immediate.value)}",
        f"{int(dut.u_core.funct3.value):03x}",
    ]
    log_signal_table.append(row)

def save_log_signals(filename="log_signals.txt", data_list=log_signal_table):
    headers = ["pc", "next_pc", "instr", "writeData_to_reg", "reg_write_en?", "mem_addr", "mem_readData", "mem_write_en?", "mem_writeData", "i_imm", "func3"]
    table = tabulate(data_list, headers=headers, tablefmt="plain")
    
    with open(filename, "w") as f:
        f.write(table)