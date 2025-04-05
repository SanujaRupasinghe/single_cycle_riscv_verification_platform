import cocotb
from cocotb.triggers import Timer, RisingEdge
from tabulate import tabulate
import random

############################################################# test 1

# generate clock signals with logging at each posedge
async def generate_clock_verbose(dut):
    while True:
        dut.clk.value = 0
        await Timer(1, units="ns")
        dut.clk.value = 1
        await Timer(1, units="ns")
        log_signals(dut)  # Log signal data at rising edge

# print log data at each posedge
def log_signals(dut):
    """Log all relevant DUT signals."""
    dut._log.info(
        f"reset={dut.reset.value}, "
        f"in_a={int(dut.in_a.value)}, "
        # f"in_b={int(dut.in_b.value)}, "
        # f"in_c={int(dut.in_c.value)}, "
        f"result={int(dut.result.value)}, "
        f"ready_out={dut.ready_out.value}, "
        f"valid_in={dut.valid_in.value}, "
        f"valid_out={dut.valid_out.value}, "
        f"ready_in={dut.ready_in.value}, "
        f"valid_out_reg_shift={dut.valid_out_reg_shift.value}"
    )

# log data to a list
log_data_t1 = [] 

def log_signals_list_t1(dut):
    global log_data_t1
    row = [
        int(dut.reset.value),
        int(dut.in_a.value),
        int(dut.in_b.value),
        int(dut.in_c.value),
        int(dut.ready_out.value),
        int(dut.valid_in.value),
        int(dut.result.value),
        int(dut.valid_out.value),
        int(dut.ready_in.value),
        format(int(dut.valid_out_reg_shift.value), '04b')
    ]
    log_data_t1.append(row)

# save log data to a file
def save_log_t1(filename="pipelined_test_1.txt", data_list=log_data_t1):
    headers = ["reset", "in_a", "in_b", "in_c", "ready_out", "valid_in", "result", "valid_out", "ready_in", "valid_out_shift"]
    table = tabulate(data_list, headers=headers, tablefmt="plain")
    
    with open(filename, "w") as f:
        f.write(table)


# basic test to check if the module is working as expected by providing some input values and observing the logged data
@cocotb.test()
async def pipeline_test_1(dut):
    cocotb.start_soon(generate_clock_verbose(dut)) 

    dut.ready_in.value = 1     #always ready to accept output data from the module 

    for i in range(20): 
        await RisingEdge(dut.clk)

        if i == 10 or i == 0:
            dut.reset.value = 1
        else:
            dut.reset.value = 0 

        dut.in_a.value = i + 10
        dut.in_b.value = i + 10
        dut.in_c.value = i + 10
        dut.valid_in.value = 1

        # Call log function to store values
        log_signals_list_t1(dut)
    
    # Save data to file after the test
    save_log_t1("pipeline_test_1.txt", log_data_t1)  

    dut._log.info("pipeline_test_1 Test completed.")



############################################################# test 2

# generate clock signals no logging
async def generate_clock(dut):
    while True:
        dut.clk.value = 0
        await Timer(1, units="ns")
        dut.clk.value = 1
        await Timer(1, units="ns")

# log data to a list
log_data_t2 = []  

# log data to a list
def log_signals_list_t2(dut):
    global log_data_t2
    row = [
        int(dut.reset.value),
        int(dut.in_a.value),
        int(dut.in_b.value),
        int(dut.in_c.value),
        int(dut.ready_out.value),
        int(dut.valid_in.value),
        int(dut.result.value),
        int(dut.valid_out.value),
        int(dut.ready_in.value),
        format(int(dut.valid_out_reg_shift.value), '04b')
    ]
    log_data_t2.append(row)


# insert random values to model and compare predicted/ expected value vs actual value
@cocotb.test()
async def pipeline_test_2(dut):
    cocotb.start_soon(generate_clock(dut))

    dut.ready_in.value = 1     #always ready to accept output data from the module 

    for i in range(50): 
        await RisingEdge(dut.clk)

        if i == 0:
            dut.reset.value = 1
        else:
            dut.reset.value = 0 

        dut.in_a.value = random.randint(0, 2**8 - 1)
        dut.in_b.value = random.randint(0, 2**8 - 1)
        dut.in_c.value = random.randint(0, 2**8 -1)
        dut.valid_in.value = random.choices([1, 0], weights=[90, 10])[0]  # 80% of valid_ins are 1

        # Call log function to store values
        log_signals_list_t2(dut)

    # iterate through logged data if the ouptput is valid, then compare
    for item in range(5, len(log_data_t2)):
        if (log_data_t2[item][7] == 1):   
            dut._log.info(f"calculated by DUT= {log_data_t2[item][6]}, expected = {log_data_t2[item-4][1] * log_data_t2[item-4][2] + log_data_t2[item-4][3]}")
            assert (log_data_t2[item][6] == log_data_t2[item-4][1] * log_data_t2[item-4][2] + log_data_t2[item-4][3]), "Error in calculation"

    # Save data to file after the test
    save_log_t1("pipeline_test_2.txt", log_data_t2)  

    dut._log.info("pipeline_test_2 Test completed.")
