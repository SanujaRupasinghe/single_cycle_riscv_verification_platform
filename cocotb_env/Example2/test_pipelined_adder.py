import cocotb
from cocotb.triggers import Timer, RisingEdge
from tabulate import tabulate
import random

async def generate_clock(dut):
    """Generate clock pulses and log signals at both edges."""
    while True:
        dut.clk.value = 0
        await Timer(1, units="ns")
        dut.clk.value = 1
        await Timer(1, units="ns")
        log_signals(dut)  # Log at rising edge


def log_signals(dut):
    """Log all relevant DUT signals."""
    dut._log.info(
        f"reset={dut.reset.value}, "
        f"in_a={int(dut.in_a.value)}, "
        f"in_b={int(dut.in_b.value)}, "
        f"in_c={int(dut.in_c.value)}, "
        f"ready_out={dut.ready_out.value}, "
        f"result={int(dut.result.value)}, "
        f"valid_out={dut.valid_out.value}, "
        f"valid_out_reg_shift={dut.valid_out_reg_shift.value}"
    )


log_data = []  # Store logged values

def log_signals_file(dut):
    """Log all relevant DUT signals in a structured format."""
    global log_data
    row = [
        int(dut.reset.value),
        int(dut.in_a.value),
        int(dut.in_b.value),
        int(dut.in_c.value),
        int(dut.ready_out.value),
        int(dut.result.value),
        int(dut.valid_out.value),
        format(int(dut.valid_out_reg_shift.value), '04b')
    ]
    log_data.append(row)


def save_log(filename="log_output.txt"):
    """Save logged data using tabulate."""
    headers = ["reset", "in_a", "in_b", "in_c", "ready_out", "result", "valid_out", "valid_out_shift"]
    table = tabulate(log_data, headers=headers, tablefmt="plain")
    
    with open(filename, "w") as f:
        f.write(table)


@cocotb.test()
async def pipelined_adder_test(dut):
    """Test the pipelined adder with ready-valid handshaking, logging all signals at every clock edge."""

    cocotb.start_soon(generate_clock(dut)) 

    dut.ready_in.value = 1
    dut.valid_in.value = 1 

    for i in range(20): 
        await RisingEdge(dut.clk)

        if i == 10:
            dut.reset.value = 1
        else:
            dut.reset.value = 0 

        dut.in_a.value = i + 10
        dut.in_b.value = i + 10
        dut.in_c.value = i + 10

        # Call log function to store values
        log_signals_file(dut)

    dut._log.info("Test completed.")

    save_log()  # Save data to file after the test
