/*
 * File: arm2.c
 * Author: dgrubb
 * Date: 11/03/2019
 */

/* Library includes */
#include <stddef.h>

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
    // In most cases we simply want to set the register directly. However, many
    // system modes (e.g., supervisor, interrupt etc) have their own subset of
    // shadow registers stored separately. For example, a write to r0 in USER,
    // SVC, IRQ and FIQ modes will always write to the same register. However,
    // writing to r8 while in FIQ mode will write to a register which is distinct
    // from the instance of r8 written while in USER mode, r8_fiq.
    //
    // rX_user is initially assumed, but for registers with shadow registers a
    // call must be made to GetShadowRegister to set the correct register array
    // location for the current mode.
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
    // N.B: read comment in set_register(uint32_t reg, uint32_t value)
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
    DBG_PRINT((DBG_ULTRA_VERBOSE, "%s status flag: %s\n", (value ? "Setting" : "Clearing"), ARM2_StatusFlagStrings[flag]));
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

int
arm2_init()
{
    return 0;
}

