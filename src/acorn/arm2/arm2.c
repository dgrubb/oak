/*
 * File: arm2.c
 * Author: dgrubb
 * Date: 11/03/2019
 */

/* Library includes */
#include <stddef.h>
#include <string.h> /* memset() */

/* Project includes */
#include "arm2.h"
#include "debug.h"

static ARM2_State state = {0};

const char *ARM2_ModeStrings[] = {
    "USER",
    "FIQ",
    "IRQ",
    "SVC",
    "ALL"
};

const uint32_t ARM2_ModeMasks[] = {
    ARM2_STATUS_MASK_MODE_USER,
    ARM2_STATUS_MASK_MODE_FIQ,
    ARM2_STATUS_MASK_MODE_IRQ,
    ARM2_STATUS_MASK_MODE_SVC,
    ARM2_STATUS_MASK_MODE_ALL
};

const uint32_t ARM2_StatusFlagMasks[] = {
    ARM2_STATUS_MASK_NEGATIVE,
    ARM2_STATUS_MASK_ZERO,
    ARM2_STATUS_MASK_CARRY,
    ARM2_STATUS_MASK_OVERFLOW,
    ARM2_STATUS_MASK_IRQ_DISABLE,
    ARM2_STATUS_MASK_FIQ_DISABLE
};

const char *ARM2_RegisterStrings[] = {
    "r0",
    "r1",
    "r2",
    "r3",
    "r4",
    "r5",
    "r6",
    "r7",
    "r8",
    "r9",
    "r10",
    "r11",
    "r12",
    "r13",
    "r14",
    "cpsr"
};

const char *ARM2_StatusFlagStrings[] = {
    "Negative",
    "Zero",
    "Carry",
    "Overflow",
    "IRQ disable",
    "FIQ disable"
};

int
arm2_set_register(uint32_t reg, uint32_t value)
{
    /* In most cases we simply want to set the register directly. However, many
     * system modes (e.g., supervisor, interrupt etc) have their own subset of
     * shadow registers stored separately. For example, a write to r0 in USER,
     * SVC, IRQ and FIQ modes will always write to the same register. However,
     * writing to r8 while in FIQ mode will write to a register which is distinct
     * from the instance of r8 written while in USER mode, r8_fiq.
     *
     * rX_user is initially assumed, but for registers with shadow registers a
     * call must be made to GetShadowRegister to set the correct register array
     * location for the current mode.
     */
    ARM2_Mode mode_select = state.mode;
    DBG_PRINT((DBG_ULTRA_VERBOSE, "Setting register [ %s ]: 0x%X\n", ARM2_RegisterStrings[reg], value));
    switch (reg) {
        case R0:
            state.r0 = value;
            break;
        case R1:
            state.r1 = value;
            break;
        case R2:
            state.r2 = value;
            break;
        case R3:
            state.r3 = value;
            break;
        case R4:
            state.r4 = value;
            break;
        case R5:
            state.r5 = value;
            break;
        case R6:
            state.r6 = value;
            break;
        case R7:
            state.r7 = value;
            break;
        case R8:
            arm2_get_shadow_register(state.r8, &mode_select);
            state.r8[mode_select] = value;
            break;
        case R9:
            arm2_get_shadow_register(state.r9, &mode_select);
            state.r9[mode_select] = value;
            break;
        case R10:
            arm2_get_shadow_register(state.r10, &mode_select);
            state.r10[mode_select] = value;
            break;
        case R11:
            arm2_get_shadow_register(state.r11, &mode_select);
            state.r11[mode_select] = value;
            break;
        case R12:
            arm2_get_shadow_register(state.r12, &mode_select);
            state.r12[mode_select] = value;
            break;
        case R13:
            arm2_get_shadow_register(state.r13, &mode_select);
            state.r13[mode_select] = value;
            break;
        case R14:
            arm2_get_shadow_register(state.r14, &mode_select);
            state.r14[mode_select] = value;
            break;
        case CPSR:
            state.cpsr = value;
            break;
        default:
            DBG_PRINT((DBG_ERROR, "Unknown register: %d", reg));
            return -1;
    }
    return 0;
}

int
arm2_get_register(uint32_t reg, uint32_t *value)
{
    /* N.B: read comment in set_register(uint32_t reg, uint32_t value) */
    ARM2_Mode mode_select = state.mode;
    switch (reg) {
        case R0:
            *value = state.r0;
            break;
        case R1:
            *value = state.r1;
            break;
        case R2:
            *value = state.r2;
            break;
        case R3:
            *value = state.r3;
            break;
        case R4:
            *value = state.r4;
            break;
        case R5:
            *value = state.r5;
            break;
        case R6:
            *value = state.r6;
            break;
        case R7:
            *value = state.r7;
            break;
        case R8:
            arm2_get_shadow_register(state.r8, &mode_select);
            *value = state.r8[mode_select];
            break;
        case R9:
            arm2_get_shadow_register(state.r9, &mode_select);
            *value = state.r8[mode_select];
            break;
        case R10:
            arm2_get_shadow_register(state.r10, &mode_select);
            *value = state.r8[mode_select];
            break;
        case R11:
            arm2_get_shadow_register(state.r11, &mode_select);
            *value = state.r8[mode_select];
            break;
        case R12:
            arm2_get_shadow_register(state.r12, &mode_select);
            *value = state.r8[mode_select];
            break;
        case R13:
            arm2_get_shadow_register(state.r13, &mode_select);
            *value = state.r8[mode_select];
            break;
        case R14:
            arm2_get_shadow_register(state.r14, &mode_select);
            *value = state.r8[mode_select];
            break;
        case CPSR:
            *value = state.cpsr;
            break;
        default:
            DBG_PRINT((DBG_ERROR, "Unknown register: %d", reg));
            return -1;
    }
    DBG_PRINT((DBG_ULTRA_VERBOSE, "Getting register [ %s ]: 0x%X\n", ARM2_RegisterStrings[reg], *value));
    return 0;
}

int
arm2_get_shadow_register(uint32_t reg[], ARM2_Mode *mode)
{
    if (*mode > sizeof(*reg)/sizeof(reg[0])) {
        *mode = USER;
    }
    return 0;
}

int
arm2_set_status_flag(ARM2_StatusFlag flag, bool value)
{
    DBG_PRINT((DBG_VERBOSE, "%s status flag: %s\n", (value ? "Setting" : "Clearing"), ARM2_StatusFlagStrings[flag]));
    uint32_t cpsr = get_cpsr();
    if (value) {
        cpsr |= ARM2_StatusFlagMasks[flag];
    } else {
        cpsr &= ~ARM2_StatusFlagMasks[flag];
    }
    return set_cpsr(cpsr);
}

int
arm2_get_status_flag(ARM2_StatusFlag flag, bool *value)
{
    *value = (get_cpsr() & ARM2_StatusFlagMasks[flag]);
    DBG_PRINT((DBG_ULTRA_VERBOSE, "Reading status flag %s: %s\n", ARM2_StatusFlagStrings[flag], (value ? "set" : "clear")));
    return 0;
}

int
arm2_set_PC(uint32_t value)
{
    uint32_t cpsr = get_cpsr();
    cpsr &= ~ARM2_STATUS_MASK_PC;
    cpsr |= (value << 2);
    return set_cpsr(cpsr);
}

int
arm2_get_PC(uint32_t *value)
{
    uint32_t cpsr = get_cpsr();
    *value = (cpsr & ARM2_STATUS_MASK_PC);
    *value = (*value >> 2);
    return 0;
}

int
arm2_set_mode(ARM2_Mode mode)
{
    DBG_PRINT((DBG_VERBOSE, "Setting processor mode: %s\n", ARM2_ModeStrings[mode]));
    uint32_t cpsr = get_cpsr();
    cpsr &= ~ARM2_ModeMasks[ALL];
    cpsr &= ARM2_ModeMasks[mode];
    return set_cpsr(cpsr);
}

int
arm2_get_mode(ARM2_Mode *mode)
{
    uint32_t cpsr = get_cpsr();
    cpsr &= ARM2_ModeMasks[ALL];
    switch (cpsr) {
        case ARM2_STATUS_MASK_MODE_USER: *mode = USER; break;
        case ARM2_STATUS_MASK_MODE_FIQ:  *mode = FIQ; break;
        case ARM2_STATUS_MASK_MODE_IRQ:  *mode = IRQ; break;
        case ARM2_STATUS_MASK_MODE_SVC:  *mode = SVC; break;
        default:
            DBG_PRINT((DBG_ERROR, "Unknown mode mask: 0x%X\n", cpsr));
            return -1;
    }
    DBG_PRINT((DBG_ULTRA_VERBOSE, "Reading processor mode: %s\n", ARM2_ModeStrings[*mode]));
    return 0;
}

/* Quick reference getters */
uint32_t get_r0() { uint32_t ret_val; arm2_get_register(R0, &ret_val); return ret_val; }
uint32_t get_r1() { uint32_t ret_val; arm2_get_register(R1, &ret_val); return ret_val; }
uint32_t get_r2() { uint32_t ret_val; arm2_get_register(R2, &ret_val); return ret_val; }
uint32_t get_r3() { uint32_t ret_val; arm2_get_register(R3, &ret_val); return ret_val; }
uint32_t get_r4() { uint32_t ret_val; arm2_get_register(R4, &ret_val); return ret_val; }
uint32_t get_r5() { uint32_t ret_val; arm2_get_register(R5, &ret_val); return ret_val; }
uint32_t get_r6() { uint32_t ret_val; arm2_get_register(R6, &ret_val); return ret_val; }
uint32_t get_r7() { uint32_t ret_val; arm2_get_register(R7, &ret_val); return ret_val; }
uint32_t get_r8() { uint32_t ret_val; arm2_get_register(R8, &ret_val); return ret_val; }
uint32_t get_r9() { uint32_t ret_val; arm2_get_register(R9, &ret_val); return ret_val; }
uint32_t get_r10() { uint32_t ret_val; arm2_get_register(R10, &ret_val); return ret_val; }
uint32_t get_r11() { uint32_t ret_val; arm2_get_register(R11, &ret_val); return ret_val; }
uint32_t get_r12() { uint32_t ret_val; arm2_get_register(R12, &ret_val); return ret_val; }
uint32_t get_r13() { uint32_t ret_val; arm2_get_register(R13, &ret_val); return ret_val; }
uint32_t get_r14() { uint32_t ret_val; arm2_get_register(R14, &ret_val); return ret_val; }
uint32_t get_cpsr() { uint32_t ret_val; arm2_get_register(CPSR, &ret_val); return ret_val; }

/* Quick reference setters */
int set_r0(uint32_t value) { return arm2_set_register(R0, value); }
int set_r1(uint32_t value) { return arm2_set_register(R1, value); }
int set_r2(uint32_t value) { return arm2_set_register(R2, value); }
int set_r3(uint32_t value) { return arm2_set_register(R3, value); }
int set_r4(uint32_t value) { return arm2_set_register(R4, value); }
int set_r5(uint32_t value) { return arm2_set_register(R5, value); }
int set_r6(uint32_t value) { return arm2_set_register(R6, value); }
int set_r7(uint32_t value) { return arm2_set_register(R7, value); }
int set_r8(uint32_t value) { return arm2_set_register(R8, value); }
int set_r9(uint32_t value) { return arm2_set_register(R9, value); }
int set_r10(uint32_t value) { return arm2_set_register(R10, value); }
int set_r11(uint32_t value) { return arm2_set_register(R11, value); }
int set_r12(uint32_t value) { return arm2_set_register(R12, value); }
int set_r13(uint32_t value) { return arm2_set_register(R13, value); }
int set_r14(uint32_t value) { return arm2_set_register(R14, value); }
int set_cpsr(uint32_t value) { return arm2_set_register(CPSR, value); }

bool
arm2_test_status_flag(ARM2_StatusFlag flag)
{
    bool flag_value = false;
    arm2_get_status_flag(flag, &flag_value);
    return flag_value;
}

bool
arm2_test_conditions(uint32_t condition_flags)
{
    bool execute = false;
    switch (condition_flags) {
        case ARM2_CONDITION_EQ:
            execute = arm2_test_status_flag(ZERO);
            break;
        case ARM2_CONDITION_NE:
            execute = !arm2_test_status_flag(ZERO);
            break;
        case ARM2_CONDITION_CS:
            execute = arm2_test_status_flag(CARRY);
            break;
        case ARM2_CONDITION_CC:
            execute = !arm2_test_status_flag(CARRY);
            break;
        case ARM2_CONDITION_MI:
            execute = arm2_test_status_flag(NEGATIVE);
            break;
        case ARM2_CONDITION_PL:
            execute = !arm2_test_status_flag(NEGATIVE);
            break;
        case ARM2_CONDITION_VS:
            execute = arm2_test_status_flag(OVERFLOW);
            break;
        case ARM2_CONDITION_VC:
            execute = !arm2_test_status_flag(OVERFLOW);
            break;
        case ARM2_CONDITION_HI:
            execute = (arm2_test_status_flag(CARRY) && !arm2_test_status_flag(ZERO));
            break;
        case ARM2_CONDITION_LS:
            execute = (!arm2_test_status_flag(CARRY) || arm2_test_status_flag(ZERO));
            break;
        case ARM2_CONDITION_GE:
            execute = (
                (arm2_test_status_flag(NEGATIVE) && arm2_test_status_flag(OVERFLOW)) ||
                (!arm2_test_status_flag(NEGATIVE) && !arm2_test_status_flag(OVERFLOW))
            );
            break;
        case ARM2_CONDITION_LT:
            execute = (
                (arm2_test_status_flag(NEGATIVE) && !arm2_test_status_flag(OVERFLOW)) ||
                (!arm2_test_status_flag(NEGATIVE) && arm2_test_status_flag(OVERFLOW))
            );
            break;
        case ARM2_CONDITION_GT:
            execute = (
                (!arm2_test_status_flag(ZERO) && (arm2_test_status_flag(NEGATIVE) || arm2_test_status_flag(OVERFLOW))) ||
                (!arm2_test_status_flag(NEGATIVE) && !arm2_test_status_flag(OVERFLOW))
            );
            break;
        case ARM2_CONDITION_LE:
            execute = (
                (arm2_test_status_flag(ZERO)) ||
                (arm2_test_status_flag(NEGATIVE) && !arm2_test_status_flag(OVERFLOW)) ||
                (!arm2_test_status_flag(NEGATIVE) && arm2_test_status_flag(OVERFLOW))
            );
            break;
        case ARM2_CONDITION_AL:
            execute = true;
            break;
        case ARM2_CONDITION_NV:
            execute = false;
            break;
        default:
            DBG_PRINT((DBG_ERROR, "Unhandled condition flags: 0x%X\n", condition_flags));
            execute = false;
    }
    return execute;
}


int
arm2_flush_pipeline()
{
    state.pipeline.fetch = 0;
    state.pipeline.decode = 0;
    state.pipeline.execute = 0;
    return 0;
}

int
arm2_fetch()
{
    return 0;
}

int
arm2_decode()
{
    return 0;
}

int
arm2_execute()
{
    return 0;
}

int
arm2_init()
{
    arm2_reset();
    return 0;
}

int
arm2_reset()
{
    DBG_PRINT((DBG_VERBOSE, "Reset\n"));
    /* Reset behaviour defined on page 12 of ARM datasheet */
    memset(&state, 0, sizeof(state));
    arm2_flush_pipeline();
    arm2_set_PC(0);
    arm2_set_mode(SVC);
    arm2_set_status_flag(IRQ_DISABLE, true);
    arm2_set_status_flag(FIQ_DISABLE, true);
    arm2_print_status();

    return 0;
}
int
arm2_print_status()
{
    bool negative, zero, carry, overflow, irq_disable, fiq_disable;
    ARM2_Mode mode = USER;
    uint32_t pc;
    arm2_get_status_flag(NEGATIVE, &negative);
    arm2_get_status_flag(ZERO, &zero);
    arm2_get_status_flag(CARRY, &carry);
    arm2_get_status_flag(OVERFLOW, &overflow);
    arm2_get_status_flag(IRQ_DISABLE, &irq_disable);
    arm2_get_status_flag(FIQ_DISABLE, &fiq_disable);
    arm2_get_mode(&mode);
    arm2_get_PC(&pc);
    DBG_PRINT((DBG_VERBOSE, "| Negative | Zero | Carry | Overflow | IRQ Disable | FIQ Disable | Program Counter |  Mode  |\n"));
    DBG_PRINT((DBG_VERBOSE, "|     %s    |   %s  |   %s   |    %s     |      %s      |      %s      |       0x%X       |  %s  |\n",
               (negative ? "1" : "0"),
               (zero ? "1" : "0"),
               (carry ? "1" : "0"),
               (overflow ? "1" : "0"),
               (irq_disable ? "1" : "0"),
               (fiq_disable ? "1" : "0"),
               pc,
               ARM2_ModeStrings[mode]));
    return 0;
}
