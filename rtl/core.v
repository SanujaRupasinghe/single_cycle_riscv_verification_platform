module core (
	input 			clk,			// clock input
	input 			rst,			// reset (active high)
	input 	[31:0] 	instruction, 	// current executing instruction
	input 	[31:0] 	read_data, 		// byte-aligned read back of the address memory_address
	output 	[31:0] 	pc, 			// the pc of the instruction that needs to execute
	output 	[31:0] 	memory_address, // memory address to read or write
	output 	[31:0] 	data_to_write,  // data to write for store instructions
	output 	[2:0] 	func3, 			// simply the func3 of the store instruction 
	output 			write_data  	// assert high to write to memory
);
	
	reg [31:0] register_file [0:31];

	reg [31:0] pc_reg;
	assign pc = pc_reg;

	integer i;

	initial begin
		pc_reg = 32'b0;
		for (i = 0; i < 32; i = i + 1) begin
			register_file[i] = 32'b10101010101010101010101010101010;
		end
	end

	always @(posedge clk) begin
		if (rst) begin
			pc_reg <= 32'b0;
		end else begin
			pc_reg <= pc_reg + 4;
		end
	end

endmodule
