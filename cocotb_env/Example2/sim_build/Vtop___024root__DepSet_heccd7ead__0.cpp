// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"
#include "Vtop___024root.h"

void Vtop___024root___ico_sequent__TOP__0(Vtop___024root* vlSelf);

void Vtop___024root___eval_ico(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_ico\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        Vtop___024root___ico_sequent__TOP__0(vlSelf);
    }
}

VL_INLINE_OPT void Vtop___024root___ico_sequent__TOP__0(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ico_sequent__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.pipelined_adder__DOT__clk = vlSelfRef.clk;
    vlSelfRef.pipelined_adder__DOT__reset = vlSelfRef.reset;
    vlSelfRef.pipelined_adder__DOT__in_a = vlSelfRef.in_a;
    vlSelfRef.pipelined_adder__DOT__in_b = vlSelfRef.in_b;
    vlSelfRef.pipelined_adder__DOT__in_c = vlSelfRef.in_c;
    vlSelfRef.pipelined_adder__DOT__valid_in = vlSelfRef.valid_in;
    vlSelfRef.pipelined_adder__DOT__ready_in = vlSelfRef.ready_in;
    vlSelfRef.result = vlSelfRef.pipelined_adder__DOT__result;
    vlSelfRef.pipelined_adder__DOT__ready_out = (1U 
                                                 & (~ (IData)(vlSelfRef.pipelined_adder__DOT__input_buffers_full)));
    vlSelfRef.pipelined_adder__DOT__valid_out = ((IData)(vlSelfRef.pipelined_adder__DOT__valid_out_reg_shift) 
                                                 & (IData)(vlSelfRef.pipelined_adder__DOT__valid_out_validate));
    vlSelfRef.ready_out = vlSelfRef.pipelined_adder__DOT__ready_out;
    vlSelfRef.valid_out = vlSelfRef.pipelined_adder__DOT__valid_out;
}

void Vtop___024root___eval_triggers__ico(Vtop___024root* vlSelf);

bool Vtop___024root___eval_phase__ico(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__ico\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VicoExecute;
    // Body
    Vtop___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = vlSelfRef.__VicoTriggered.any();
    if (__VicoExecute) {
        Vtop___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vtop___024root___eval_act(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_act\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

void Vtop___024root___nba_sequent__TOP__0(Vtop___024root* vlSelf);

void Vtop___024root___eval_nba(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_nba\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtop___024root___nba_sequent__TOP__0(vlSelf);
    }
}

VL_INLINE_OPT void Vtop___024root___nba_sequent__TOP__0(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    SData/*15:0*/ __Vdly__pipelined_adder__DOT__result;
    __Vdly__pipelined_adder__DOT__result = 0;
    // Body
    __Vdly__pipelined_adder__DOT__result = vlSelfRef.pipelined_adder__DOT__result;
    if (vlSelfRef.reset) {
        vlSelfRef.pipelined_adder__DOT__valid_out_reg_shift = 0U;
        __Vdly__pipelined_adder__DOT__result = 0U;
        vlSelfRef.pipelined_adder__DOT__acc_reg = 0U;
        vlSelfRef.pipelined_adder__DOT__c_reg_2 = 0U;
        vlSelfRef.pipelined_adder__DOT__mul_reg = 0U;
        vlSelfRef.pipelined_adder__DOT__c_reg_1 = 0U;
        vlSelfRef.pipelined_adder__DOT__a_reg = 0U;
        vlSelfRef.pipelined_adder__DOT__b_reg = 0U;
    } else {
        vlSelfRef.pipelined_adder__DOT__valid_out_reg_shift 
            = (((IData)(vlSelfRef.valid_in) << 3U) 
               | (7U & ((IData)(vlSelfRef.pipelined_adder__DOT__valid_out_reg_shift) 
                        >> 1U)));
        vlSelfRef.pipelined_adder__DOT__valid_out_validate 
            = ((IData)(vlSelfRef.pipelined_adder__DOT__result) 
               != (IData)(vlSelfRef.pipelined_adder__DOT__acc_reg));
        __Vdly__pipelined_adder__DOT__result = vlSelfRef.pipelined_adder__DOT__acc_reg;
        vlSelfRef.pipelined_adder__DOT__acc_reg = (0xffffU 
                                                   & ((IData)(vlSelfRef.pipelined_adder__DOT__mul_reg) 
                                                      + (IData)(vlSelfRef.pipelined_adder__DOT__c_reg_2)));
        vlSelfRef.pipelined_adder__DOT__c_reg_2 = vlSelfRef.pipelined_adder__DOT__c_reg_1;
        vlSelfRef.pipelined_adder__DOT__mul_reg = (0xffffU 
                                                   & ((IData)(vlSelfRef.pipelined_adder__DOT__a_reg) 
                                                      * (IData)(vlSelfRef.pipelined_adder__DOT__b_reg)));
        if (((IData)(vlSelfRef.pipelined_adder__DOT__ready_out) 
             & (IData)(vlSelfRef.valid_in))) {
            vlSelfRef.pipelined_adder__DOT__c_reg_1 
                = vlSelfRef.in_c;
            vlSelfRef.pipelined_adder__DOT__a_reg = vlSelfRef.in_a;
            vlSelfRef.pipelined_adder__DOT__b_reg = vlSelfRef.in_b;
        }
    }
    vlSelfRef.pipelined_adder__DOT__input_buffers_full 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && ((IData)(vlSelfRef.pipelined_adder__DOT__ready_out) 
                                                   & (IData)(vlSelfRef.valid_in)));
    vlSelfRef.pipelined_adder__DOT__result = __Vdly__pipelined_adder__DOT__result;
    vlSelfRef.result = vlSelfRef.pipelined_adder__DOT__result;
    vlSelfRef.pipelined_adder__DOT__valid_out = ((IData)(vlSelfRef.pipelined_adder__DOT__valid_out_reg_shift) 
                                                 & (IData)(vlSelfRef.pipelined_adder__DOT__valid_out_validate));
    vlSelfRef.valid_out = vlSelfRef.pipelined_adder__DOT__valid_out;
    vlSelfRef.pipelined_adder__DOT__ready_out = (1U 
                                                 & (~ (IData)(vlSelfRef.pipelined_adder__DOT__input_buffers_full)));
    vlSelfRef.ready_out = vlSelfRef.pipelined_adder__DOT__ready_out;
}

void Vtop___024root___eval_triggers__act(Vtop___024root* vlSelf);

bool Vtop___024root___eval_phase__act(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__act\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<1> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vtop___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelfRef.__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelfRef.__VactTriggered, vlSelfRef.__VnbaTriggered);
        vlSelfRef.__VnbaTriggered.thisOr(vlSelfRef.__VactTriggered);
        Vtop___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vtop___024root___eval_phase__nba(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__nba\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelfRef.__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vtop___024root___eval_nba(vlSelf);
        vlSelfRef.__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__ico(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__nba(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(Vtop___024root* vlSelf);
#endif  // VL_DEBUG

void Vtop___024root___eval(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VicoIterCount;
    CData/*0:0*/ __VicoContinue;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VicoIterCount = 0U;
    vlSelfRef.__VicoFirstIteration = 1U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        if (VL_UNLIKELY(((0x64U < __VicoIterCount)))) {
#ifdef VL_DEBUG
            Vtop___024root___dump_triggers__ico(vlSelf);
#endif
            VL_FATAL_MT("/media/sanuja/Storage/RISCV_ENTC_SIG/single_cycle_riscv_verification_platform/cocotb_env/Example2/pipelined_adder.sv", 5, "", "Input combinational region did not converge.");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        __VicoContinue = 0U;
        if (Vtop___024root___eval_phase__ico(vlSelf)) {
            __VicoContinue = 1U;
        }
        vlSelfRef.__VicoFirstIteration = 0U;
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY(((0x64U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vtop___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("/media/sanuja/Storage/RISCV_ENTC_SIG/single_cycle_riscv_verification_platform/cocotb_env/Example2/pipelined_adder.sv", 5, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelfRef.__VactIterCount = 0U;
        vlSelfRef.__VactContinue = 1U;
        while (vlSelfRef.__VactContinue) {
            if (VL_UNLIKELY(((0x64U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vtop___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("/media/sanuja/Storage/RISCV_ENTC_SIG/single_cycle_riscv_verification_platform/cocotb_env/Example2/pipelined_adder.sv", 5, "", "Active region did not converge.");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactContinue = 0U;
            if (Vtop___024root___eval_phase__act(vlSelf)) {
                vlSelfRef.__VactContinue = 1U;
            }
        }
        if (Vtop___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vtop___024root___eval_debug_assertions(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_debug_assertions\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY(((vlSelfRef.reset & 0xfeU)))) {
        Verilated::overWidthError("reset");}
    if (VL_UNLIKELY(((vlSelfRef.valid_in & 0xfeU)))) {
        Verilated::overWidthError("valid_in");}
    if (VL_UNLIKELY(((vlSelfRef.ready_in & 0xfeU)))) {
        Verilated::overWidthError("ready_in");}
}
#endif  // VL_DEBUG
