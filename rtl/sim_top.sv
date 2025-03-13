module sim_top (
    input logic reset, clk,
    output logic result_valid, result_passed
);

    assign result_valid = 1'b0;
    assign result_passed = 1'b0;
endmodule