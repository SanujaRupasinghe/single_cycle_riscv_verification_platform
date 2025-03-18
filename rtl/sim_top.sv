module sim_top #(
    localparam INST_MEM_ADDR_SIZE = 10 // Address size of the instruction memory read port, 1Kb memory
)(
    input  logic                            reset, clk,
    output logic                            result_valid, result_passed,

    // Instruction memory program logic
    input  logic [31:0]                     inst,                   // Instruction being programmed (instruction)
    input  logic [INST_MEM_ADDR_SIZE-1:0]   inst_mem_offset,        // Address of the instruction being programmed (where to write)
    input  logic                            programming_data_valid, // Data valid signal (is the instruction valid)
    input  logic                            programming_done        // Programming is finished, core can start execution 
);

    logic instructions_valid;  // instruction memory is consists of good content

    always_ff @(posedge clk) begin
        if (reset) instructions_valid                 <= 1'b0;  // At reset, instruction memory is invalid and needs programming
        else if (programming_done) instructions_valid <= 1'b1;  // Core can start execution after programming
    end

    localparam INST_MEM_SIZE = 1 << INST_MEM_ADDR_SIZE;   // INST_MEM_SIZE = 2^10
    logic [31:0] instruction_memory [0:INST_MEM_SIZE-1];  // Instruction memory as an array of 32-bit registers

    integer i;
    // Instruction memory programming logic
    always_ff @(posedge clk) begin
        if (!instructions_valid) begin
            if (reset) begin
                for (int i = 0; i < INST_MEM_SIZE; i++)
                    instruction_memory[i] <= 32'b0;
            end
            else if (programming_data_valid) begin
                instruction_memory[inst_mem_offset] <= inst; 
            end
        end
    end
endmodule
