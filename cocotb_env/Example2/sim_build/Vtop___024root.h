// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop.h for the primary calling header

#ifndef VERILATED_VTOP___024ROOT_H_
#define VERILATED_VTOP___024ROOT_H_  // guard

#include "verilated.h"


class Vtop__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtop___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(reset,0,0);
    VL_IN8(in_a,7,0);
    VL_IN8(in_b,7,0);
    VL_IN8(valid_in,0,0);
    VL_OUT8(ready_out,0,0);
    VL_OUT8(valid_out,0,0);
    VL_IN8(ready_in,0,0);
    CData/*0:0*/ pipelined_adder__DOT__clk;
    CData/*0:0*/ pipelined_adder__DOT__reset;
    CData/*7:0*/ pipelined_adder__DOT__in_a;
    CData/*7:0*/ pipelined_adder__DOT__in_b;
    CData/*0:0*/ pipelined_adder__DOT__valid_in;
    CData/*0:0*/ pipelined_adder__DOT__ready_out;
    CData/*0:0*/ pipelined_adder__DOT__valid_out;
    CData/*0:0*/ pipelined_adder__DOT__ready_in;
    CData/*7:0*/ pipelined_adder__DOT__a_reg;
    CData/*7:0*/ pipelined_adder__DOT__b_reg;
    CData/*3:0*/ pipelined_adder__DOT__valid_out_reg_shift;
    CData/*0:0*/ pipelined_adder__DOT__input_buffers_full;
    CData/*0:0*/ pipelined_adder__DOT__valid_out_validate;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VicoFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __VactContinue;
    VL_IN16(in_c,15,0);
    VL_OUT16(result,15,0);
    SData/*15:0*/ pipelined_adder__DOT__in_c;
    SData/*15:0*/ pipelined_adder__DOT__result;
    SData/*15:0*/ pipelined_adder__DOT__c_reg_1;
    SData/*15:0*/ pipelined_adder__DOT__c_reg_2;
    SData/*15:0*/ pipelined_adder__DOT__mul_reg;
    SData/*15:0*/ pipelined_adder__DOT__acc_reg;
    IData/*31:0*/ __VactIterCount;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vtop__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vtop___024root(Vtop__Syms* symsp, const char* v__name);
    ~Vtop___024root();
    VL_UNCOPYABLE(Vtop___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
