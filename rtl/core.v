module core (
	input clk,	// clock input
	input rst,	// reset (active high)
	input [31:0] instruction, // you need to execute this instruction
	input [31:0] pc, // the pc of the instruction that needs to execute
	
	output [31:0] memory_address, // memory address to read or write
	output [31:0] data_to_write, // data to write for store instructions
	output [2:0] func3, // simply the func3 of the store instruction 
	output write_data, // assert high to write to memory
	input [31:0] read_data, // byte-aligned read back of the address memory_address
	
	output [31:0] next_pc // pc of next instruction to execute
);
	// wires and outputs are initialized with default value so
	// that the simulations work.

	// register file
	reg [31:0] register_file [31:0]

	// just provide rs1 + immediate
	// When the address is given the data corresponding to that address
	// will be on read_data. This data will be byte-aligned. Please search
	// this term before implmenting and load instructions
	assign memory_address = 32'b0;
	// just provide rs2
	assign data_to_write = 32'b0;
	// just provide the func3 of the instruction
	assign func3 = 3'b0;

	assign next_pc = 32'b0;


endmodule
