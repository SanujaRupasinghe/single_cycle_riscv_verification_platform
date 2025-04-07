module core_v2 (
	input clk,	// clock input
	input rst,	// reset (active high)
	input [31:0] instruction, // you need to execute this instruction
	output [31:0] pc, // the pc of the instruction that needs to execute
	
	output [31:0] memory_address, // memory address to read or write
	output [31:0] data_to_write, // data to write for store instructions
	output [2:0] func3, // simply the func3 of the store instruction 
	output write_data, // assert high to write to memory
	input [31:0] read_data // byte-aligned read back of the address memory_address
	
	//output [31:0] next_pc // pc of next instruction to execute
);

	// store instruction
	assign data_to_write = rs2;
	assign func3 = funct3;
	assign write_data = (opcode == 7'b0100011) ? 1'b1 : 1'b0; 

	integer i;
	initial begin
		for (i = 0; i < 32; i = i + 1) begin
			register_file[i] = 32'd0;
		end
		pc_reg = 32'd0;
		write_back_data = 32'd0;
		write_to_reg_file = 1'b0;
	end

	// All instructions in RV32I does one or more of the following
	// 1. Change the PC 
	// 2. Write to register file
	// 3. Write to memory
	//
	// To identify which instruction is being executed, we have to look
	// at the opcode(instruction[6:0]) first.
	// Looking at the opcode, we can determine the rest of the fields of
	// the instruction and decode the instruction further 

	// register file
	reg [31:0] register_file [31:0];

	// rs1 and rs2 have to be read for some instructions
	wire [31:0] rs1 = (instruction[19:15] == 5'd0) ? 32'd0 : register_file[instruction[19:15]];
	wire [31:0] rs2 = (instruction[24:20] == 5'd0) ? 32'd0 : register_file[instruction[24:20]];


	reg [31:0] pc_reg;

	// some instructions have a immediate type, encoding of the immediate
	// changes according to the type of instruction	
	wire [31:0] i_type_immediate = {{20{instruction[31]}}, instruction[31:20]};
	wire [31:0] s_type_immediate = {{20{instruction[31]}}, instruction[31:25], instruction[11:7]};
	wire [31:0] b_type_immediate = {{19{instruction[31]}}, instruction[31], instruction[7], instruction[30:25], instruction[11:8], 1'b0};
	wire [31:0] u_type_immediate = {instruction[31:12], 12'd0};
	wire [31:0] j_type_immediate = {{11{instruction[31]}}, instruction[31], instruction[19:12], instruction[20], instruction[30:21], 1'b0};
	wire [4:0] shamt = instruction[24:20];

	wire [6:0] opcode = instruction[6:0];
	wire [2:0] funct3 = instruction[14:12];
	wire [6:0] funct7 = instruction[31:25];

	// Changing the pc according to the instruction being executed
	reg [31:0] next_pc;

	always @(*) begin
		case (opcode)
			7'b1101111: next_pc = pc + j_type_immediate; // JAL
			7'b1100111: next_pc = pc + i_type_immediate; // JALR
			7'b1100011: begin // conditional branches
				case (funct3)
					3'b000: next_pc = (rs1 == rs2) ? (pc + b_type_immediate) : (pc + 32'd4); // BEQ
					3'b001: next_pc = (rs1 != rs2) ? (pc + b_type_immediate) : (pc + 32'd4); // BNE
					3'b100: next_pc = ($signed(rs1) < $signed(rs2)) ? (pc + b_type_immediate) : (pc + 32'd4); // BLT
					3'b101: next_pc = ($signed(rs1) >= $signed(rs2)) ? (pc + b_type_immediate) : (pc + 32'd4); // BGE
					3'b110: next_pc = (rs1 < rs2) ? (pc + b_type_immediate) : (pc + 32'd4); // BLTU
					3'b111: next_pc = (rs1 >= rs2) ? (pc + b_type_immediate) : (pc + 32'd4); // BGEU
					default: next_pc = (pc + 32'd4); // Should not happen
				endcase
			end
			default: next_pc = pc + 32'd4; // All the other instruction
		endcase
	end	

	always @(posedge clk) begin
		if (rst) begin
			pc_reg = 32'd0;
			write_back_data = 32'd0;
			write_to_reg_file = 1'b0;
			for (i = 0; i < 32; i = i + 1) begin
				register_file[i] = 32'd0;
			end
		end else begin
			pc_reg = next_pc;
		end
	end

	assign pc = pc_reg;
	// We have to get the write back data for instructions that write back
	// to the register file
	reg [31:0] write_back_data;

	// We will handle write back data for load instructions first. (lb,
	// lbu, lh, lhu, lw)
	// Some instructions read from memory and write to regsiter file, to
	// do that we need to give the memory address to memory
	// if load rs1 + i_type_immediate
	// if store rs1 + s_type_immediate

	assign memory_address = (opcode == 7'b0100011)? (rs1 + s_type_immediate): (rs1 + i_type_immediate); 

	// data for the address will be given in read_data, the needed data is
	// byte aligned. 
	//
	// e.g. If you request the byte on address 0x3, you will give 0x3 on
	// memory_address, and will receive the following on read_data
	// |read_data[31:24]|read_data[23:16]|read_data[15:8]|read_data[7:0]|
	// |--data you want-|---don't care---|---don't care--|--don't care--|
	// When that happens you have to right justify it.
	wire [31:0] read_data_right_justified = read_data >> {memory_address[1:0], 3'b000};

	// Once read_data is justified, it has to be sign extended
	reg [31:0] read_data_justified_sign_extended;

	always @(*) begin
		case (funct3) // funct3 field differentiates between load instructions
			3'b000: read_data_justified_sign_extended = {{24{read_data_right_justified[7]}}, read_data_right_justified[7:0]}; // LB
			3'b001: read_data_justified_sign_extended = {{16{read_data_right_justified[15]}}, read_data_right_justified[15:0]}; // LH
			3'b010: read_data_justified_sign_extended = read_data_right_justified; // LW	
			3'b100: read_data_justified_sign_extended = {24'd0, read_data_right_justified[7:0]}; // LBU
			3'b101: read_data_justified_sign_extended = {16'd0, read_data_right_justified[15:0]}; // LHU
			default: read_data_justified_sign_extended = 32'd0; // this case should not happen
		endcase
	end	

	always @(*) begin
		case (opcode)
			7'b0110111: write_back_data = u_type_immediate; // LUI
			7'b0010111: write_back_data = pc + u_type_immediate; // AUIPC
			7'b1101111: write_back_data = pc + 32'd4; // JAL
			7'b1100111: write_back_data = pc + 32'd4; // JALR
			7'b0000011: write_back_data = read_data_justified_sign_extended;
			7'b0010011: begin // arithmetic instructions with immediate
				case (funct3)
					3'b000: write_back_data = rs1 + i_type_immediate; // ADDI
					3'b010: write_back_data = {31'd0, $signed(rs1) < $signed(i_type_immediate)}; // SLTI
					3'b011: write_back_data = {31'd0, rs1 < i_type_immediate}; // SLTIU
					3'b100: write_back_data = rs1 ^ i_type_immediate; // XORI
					3'b110: write_back_data = rs1 | i_type_immediate; // ORI
					3'b111: write_back_data = rs1 & i_type_immediate; // ANDI
					3'b001: write_back_data = rs1 << shamt; // SLLI
					3'b101: write_back_data = (funct7 != 7'd0) ? ($signed(rs1) >> shamt) : (rs1 >> shamt); // (funct7 != 0) ? SRAI : SRLI;
				endcase
			end
			7'b0110011: begin // arithmetic instructions with immediate
				case (funct3)
					3'b000: write_back_data = (funct7 == 7'd0) ? (rs1 + rs2) : (rs1 - rs2); // funct7 == 0 ? ADD : SUB;
					3'b010: write_back_data = {31'd0, $signed(rs1) < $signed(rs2)}; // SLT
					3'b011: write_back_data = {31'd0, rs1 < rs2}; // SLTU
					3'b100: write_back_data = rs1 ^ rs2; // XOR
					3'b110: write_back_data = rs1 | rs2; // OR
					3'b111: write_back_data = rs1 & rs2; // AND
					3'b001: write_back_data = rs1 << rs2[4:0]; // SLL
					3'b101: write_back_data = (funct7 != 7'd0) ? ($signed(rs1) >> rs2[4:0]) : (rs1 >> rs2[4:0]); // (funct7 != 0) ? SRA : SRL;
				endcase
			end
			default: write_back_data = 32'd0; // We really don't care about other instructions
		endcase
	end

	// not all instructions write to register file
	reg write_to_reg_file;

	always @(*) begin
		case (opcode)
			7'b0110111: write_to_reg_file = 1'b1; // LUI
			7'b0010111: write_to_reg_file = 1'b1; // AUIPC
			7'b1101111: write_to_reg_file = 1'b1; // JAL
			7'b1100111: write_to_reg_file = 1'b1; // JALR
			7'b0000011: write_to_reg_file = 1'b1; // LB, LBU, LH, LHU, LW
			7'b0010011: write_to_reg_file = 1'b1; // ADDI, SLTI, SLTIU, XORI, ORI, ANDI, SLLI, SRLI, SRAI
			7'b0110011: write_to_reg_file = 1'b1; // ADD, SUB, SLL, SLT, SLTU, XOR, SRL, SRA, OR, AND
			default: write_to_reg_file = 1'b0; // don't write to reg file on other instructions
		endcase
	end

	always @(posedge clk) begin
		if (write_to_reg_file && (instruction[11:7] != 5'd0)) begin
		// if (write_to_reg_file) begin
			register_file[instruction[11:7]] <= write_back_data;
		end
	end
endmodule