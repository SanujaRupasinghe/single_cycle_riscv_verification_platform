// this is a simple multiply and adder module which is
// // pipelined. It has 4 stages
// // handle ready valid handshake input and output side

module pipelined_mul_acc (
    input  logic clk, reset,          
    input  logic [7:0] in_a, in_b, 
    input  logic [15:0] in_c,
    input  logic valid_in,   // Externally driven input valid signal
    output logic ready_out,  // Ready to accept new input
    output logic [15:0] result,
    output logic valid_out,  // Output valid signal
    input  logic ready_in    // Externally driven ready signal
);

    logic [7:0]  a_reg, b_reg;
    logic [15:0] c_reg_1, c_reg_2;
    logic [15:0] mul_reg, acc_reg;

    logic [3:0]  valid_out_reg_shift;
    logic        input_buffers_full;
    logic        valid_out_validate;

    assign ready_out = !input_buffers_full;         // ready to accept new data if input buffers are not full
    assign valid_out = valid_out_reg_shift[0] && valid_out_validate;      // output is valid if the oldest data is valid

    always_ff @(posedge clk) begin
        if (reset) begin
            a_reg    <= 0;
            b_reg    <= 0;
            c_reg_1  <= 0;
            c_reg_2  <= 0;
            mul_reg  <= 0;
            acc_reg  <= 0;
            result   <= 0;

            valid_out_reg_shift <= 0;
            input_buffers_full  <= 0;
            
        end else begin
            //allways shift left to right 3 -> 2 -> 1 -> 0  (if data taken inside we will shift)
            valid_out_reg_shift <= {valid_in, valid_out_reg_shift[3:1]}; 

            //valid and ready both high, then accept new data and input buffers are full
            //input buffer toggles 1 -> 0 -> 1 -> 0 ->
            if (ready_out && valid_in) begin
                a_reg               <= in_a;
                b_reg               <= in_b;
                c_reg_1             <= in_c;
                input_buffers_full  <= 1;
                

            end else begin
                input_buffers_full  <= 0;
            end

            //multiply a data with b data and take the old c data forword to the next stage to add
            mul_reg <= a_reg * b_reg;
            c_reg_2 <= c_reg_1;

            //add the old c data with the multiplied data
            acc_reg <= mul_reg + c_reg_2;

            //output the result and valid signal is driven by assign statement by the valid_out_reg_shift register 4 th value 
            result  <= acc_reg;        

            //check weather the output is duplicated
            valid_out_validate <= result != acc_reg;    
        end
    end

endmodule
