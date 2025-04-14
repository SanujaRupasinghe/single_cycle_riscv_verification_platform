module sim_top #(
    localparam INST_MEM_ADDR_SIZE = 10, // Address size of the instruction memory read port, 1KB memory
    localparam DATA_MEM_ADDR_SIZE = 10  // Address size of the data memory read/write port, 1KB memory
)(
    input  logic                            reset, clk,
    output logic                            result_valid, result_passed,

    // Instruction memory program logic
    input  logic [31:0]                     inst,                   // Instruction being programmed (instruction)
    input  logic [INST_MEM_ADDR_SIZE-1:0]   inst_mem_offset,        // Address of the instruction being programmed (where to write) incremented by 1
    input  logic                            programming_data_valid, // Data valid signal (is the instruction valid)
    input  logic                            programming_done        // Programming is finished, core can start execution 
);

    // Instruction memory programming logic
    logic instructions_valid;  // instruction memory is consists of good content   if 0 core resetting

    always_ff @(posedge clk) begin
        if (reset) instructions_valid                 <= 1'b0;  // At reset, instruction memory is invalid and needs programming
        else if (programming_done) instructions_valid <= 1'b1;  // Core can start execution after programming
    end

    // Instruction mem
    localparam INST_MEM_SIZE = 1 << (INST_MEM_ADDR_SIZE);   // INST_MEM_SIZE = 2^10, 32 bit words
    logic [31:0] instruction_memory [0:INST_MEM_SIZE-1];    

    // Instruction memory programming logic
    integer i;
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

    logic        core_clk;
    logic        core_reset;
    logic [31:0] instr;
    logic [31:0] read_data;
    logic [31:0] pc;
    logic [31:0] memory_address;
    logic [31:0] data_to_write;
    logic [2:0]  funct3;
    logic        write_data;

    assign core_clk   = clk;
    assign core_reset = reset || !instructions_valid;                 // core reset if reset or instruction memory is not valid
    assign instr      = instruction_memory[pc[INST_MEM_ADDR_SIZE+1:2]];
    assign read_data  = data_memory[memory_address[DATA_MEM_ADDR_SIZE-3:0]];
    
    core_v2 u_core (
        .clk(core_clk),                              // input 
        .rst(core_reset),                            // input 
        .instruction(instr),                         // input  // instruction to be executed // lower two bits are not considered as the instruction_memory is word accessible and pc is the byte address
        .read_data(read_data),                       // input  // read back for reg file // data from data_memory
        .pc(pc),                                     // output // pc of the above instruction
        .memory_address(memory_address),             // output // data_mem address to rd or write // used to index data_memory
        .data_to_write(data_to_write),               // output // data_mem data  
        .func3(funct3),                              // output // funct3 of current inst for store instructions
        .write_data(write_data)                      // output // write enable for data mem
    );

    // test results are given when "sw (x0)-1, rs2" is executed, //write 1 to last mem address
    // assign result_valid = (memory_address == 32'hFFFFFFFF) && (funct3 == 3'b010) && write_data;
    assign result_valid = (memory_address == 32'hFFFFFFFF) && (funct3 == 3'b000) && write_data;
    assign result_passed = data_to_write == 32'd1; 

    // Data mem
    localparam DATA_MEM_SIZE = 1 << (DATA_MEM_ADDR_SIZE - 2);    // DATA_MEM_SIZE = 2^8, 32 bit words 
    logic [31:0] data_memory [0: DATA_MEM_SIZE-1];             
    
    // Data memory programming logic
    logic [31:0] aligned_data_to_write = data_to_write << {memory_address[1:0], 3'b000};  //rs2 to  data_to_write
    logic [3:0] write_strb;

    always_comb begin
	case (funct3[1:0])
		2'b01: write_strb   = 4'b0011;
		2'b00: write_strb   = 4'b0001; 
		2'b10: write_strb   = 4'b1111;
		default: write_strb = 4'b0000;
	endcase
    end

    logic [3:0] write_strb_aligned = write_strb << memory_address[1:0];
    logic [31:0] word_after_store = {
    	write_strb_aligned[3] ? aligned_data_to_write[31:24] : read_data[31:24], 
	    write_strb_aligned[2] ? aligned_data_to_write[23:16] : read_data[23:16],
	    write_strb_aligned[1] ? aligned_data_to_write[15:8]  : read_data[15:8],
	    write_strb_aligned[0] ? aligned_data_to_write[7:0]   : read_data[7:0]
    };

    always_ff @(posedge clk) begin
    	if (write_data) data_memory[memory_address[DATA_MEM_ADDR_SIZE-3:0]] <= word_after_store;
    end

endmodule
