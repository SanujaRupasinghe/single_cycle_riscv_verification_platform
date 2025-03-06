// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vtop__pch.h"
#include "Vtop.h"
#include "Vtop___024root.h"

// FUNCTIONS
Vtop__Syms::~Vtop__Syms()
{

    // Tear down scope hierarchy
    __Vhier.remove(0, &__Vscope_pipelined_adder);

}

Vtop__Syms::Vtop__Syms(VerilatedContext* contextp, const char* namep, Vtop* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup module instances
    , TOP{this, namep}
{
        // Check resources
        Verilated::stackCheck(25);
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-9);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
    // Setup scopes
    __Vscope_TOP.configure(this, name(), "TOP", "TOP", "<null>", 0, VerilatedScope::SCOPE_OTHER);
    __Vscope_pipelined_adder.configure(this, name(), "pipelined_adder", "pipelined_adder", "pipelined_adder", -9, VerilatedScope::SCOPE_MODULE);

    // Set up scope hierarchy
    __Vhier.add(0, &__Vscope_pipelined_adder);

    // Setup export functions
    for (int __Vfinal = 0; __Vfinal < 2; ++__Vfinal) {
        __Vscope_TOP.varInsert(__Vfinal,"clk", &(TOP.clk), false, VLVT_UINT8,VLVD_IN|VLVF_PUB_RW,0,0);
        __Vscope_TOP.varInsert(__Vfinal,"in_a", &(TOP.in_a), false, VLVT_UINT8,VLVD_IN|VLVF_PUB_RW,0,1 ,7,0);
        __Vscope_TOP.varInsert(__Vfinal,"in_b", &(TOP.in_b), false, VLVT_UINT8,VLVD_IN|VLVF_PUB_RW,0,1 ,7,0);
        __Vscope_TOP.varInsert(__Vfinal,"in_c", &(TOP.in_c), false, VLVT_UINT16,VLVD_IN|VLVF_PUB_RW,0,1 ,15,0);
        __Vscope_TOP.varInsert(__Vfinal,"ready_in", &(TOP.ready_in), false, VLVT_UINT8,VLVD_IN|VLVF_PUB_RW,0,0);
        __Vscope_TOP.varInsert(__Vfinal,"ready_out", &(TOP.ready_out), false, VLVT_UINT8,VLVD_OUT|VLVF_PUB_RW,0,0);
        __Vscope_TOP.varInsert(__Vfinal,"reset", &(TOP.reset), false, VLVT_UINT8,VLVD_IN|VLVF_PUB_RW,0,0);
        __Vscope_TOP.varInsert(__Vfinal,"result", &(TOP.result), false, VLVT_UINT16,VLVD_OUT|VLVF_PUB_RW,0,1 ,15,0);
        __Vscope_TOP.varInsert(__Vfinal,"valid_in", &(TOP.valid_in), false, VLVT_UINT8,VLVD_IN|VLVF_PUB_RW,0,0);
        __Vscope_TOP.varInsert(__Vfinal,"valid_out", &(TOP.valid_out), false, VLVT_UINT8,VLVD_OUT|VLVF_PUB_RW,0,0);
        __Vscope_pipelined_adder.varInsert(__Vfinal,"a_reg", &(TOP.pipelined_adder__DOT__a_reg), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,1 ,7,0);
        __Vscope_pipelined_adder.varInsert(__Vfinal,"acc_reg", &(TOP.pipelined_adder__DOT__acc_reg), false, VLVT_UINT16,VLVD_NODIR|VLVF_PUB_RW,0,1 ,15,0);
        __Vscope_pipelined_adder.varInsert(__Vfinal,"b_reg", &(TOP.pipelined_adder__DOT__b_reg), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,1 ,7,0);
        __Vscope_pipelined_adder.varInsert(__Vfinal,"c_reg_1", &(TOP.pipelined_adder__DOT__c_reg_1), false, VLVT_UINT16,VLVD_NODIR|VLVF_PUB_RW,0,1 ,15,0);
        __Vscope_pipelined_adder.varInsert(__Vfinal,"c_reg_2", &(TOP.pipelined_adder__DOT__c_reg_2), false, VLVT_UINT16,VLVD_NODIR|VLVF_PUB_RW,0,1 ,15,0);
        __Vscope_pipelined_adder.varInsert(__Vfinal,"clk", &(TOP.pipelined_adder__DOT__clk), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_pipelined_adder.varInsert(__Vfinal,"in_a", &(TOP.pipelined_adder__DOT__in_a), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,1 ,7,0);
        __Vscope_pipelined_adder.varInsert(__Vfinal,"in_b", &(TOP.pipelined_adder__DOT__in_b), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,1 ,7,0);
        __Vscope_pipelined_adder.varInsert(__Vfinal,"in_c", &(TOP.pipelined_adder__DOT__in_c), false, VLVT_UINT16,VLVD_NODIR|VLVF_PUB_RW,0,1 ,15,0);
        __Vscope_pipelined_adder.varInsert(__Vfinal,"input_buffers_full", &(TOP.pipelined_adder__DOT__input_buffers_full), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_pipelined_adder.varInsert(__Vfinal,"mul_reg", &(TOP.pipelined_adder__DOT__mul_reg), false, VLVT_UINT16,VLVD_NODIR|VLVF_PUB_RW,0,1 ,15,0);
        __Vscope_pipelined_adder.varInsert(__Vfinal,"ready_in", &(TOP.pipelined_adder__DOT__ready_in), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_pipelined_adder.varInsert(__Vfinal,"ready_out", &(TOP.pipelined_adder__DOT__ready_out), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_pipelined_adder.varInsert(__Vfinal,"reset", &(TOP.pipelined_adder__DOT__reset), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_pipelined_adder.varInsert(__Vfinal,"result", &(TOP.pipelined_adder__DOT__result), false, VLVT_UINT16,VLVD_NODIR|VLVF_PUB_RW,0,1 ,15,0);
        __Vscope_pipelined_adder.varInsert(__Vfinal,"valid_in", &(TOP.pipelined_adder__DOT__valid_in), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_pipelined_adder.varInsert(__Vfinal,"valid_out", &(TOP.pipelined_adder__DOT__valid_out), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_pipelined_adder.varInsert(__Vfinal,"valid_out_reg_shift", &(TOP.pipelined_adder__DOT__valid_out_reg_shift), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,1 ,3,0);
    }
}
