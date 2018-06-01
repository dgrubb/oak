/*
 * File: arm.cpp
 * Author: dgrubb
 * Date:26/04/2018
 */

/* Project includes */
#include "arm.h"
#include "debug.h"

const char *ARM_ModeStrings[] = {
    "USER",
    "FIQ",
    "IRQ",
    "SVC",
    "ALL"
};

const uint32_t ARM_ModeMasks[] = {
    ARM_STATUS_MASK_MODE_USER,
    ARM_STATUS_MASK_MODE_FIQ,
    ARM_STATUS_MASK_MODE_IRQ,
    ARM_STATUS_MASK_MODE_SVC,
    ARM_STATUS_MASK_MODE_ALL
};

const char *ARM_RegisterStrings[] = {
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

const char *ARM_StatusFlagStrings[] = {
    "Negative",
    "Zero",
    "Carry",
    "Overflow",
    "IRQ disable",
    "FIQ disable"
};

int
ARM::Init()
{
    this->ClearAllRegisters();
    this->Reset();
}

int
ARM::ClearAllRegisters()
{
    DBG_PRINT((DBG_ULTRA_VERBOSE, "Clearing all registers\n"));
    this->m_state.r0 = 0;
    this->m_state.r1 = 0;
    this->m_state.r2 = 0;
    this->m_state.r3 = 0;
    this->m_state.r4 = 0;
    this->m_state.r5 = 0;
    this->m_state.r6 = 0;
    this->m_state.r7 = 0;
    this->m_state.r8[USER]  = 0;
    this->m_state.r9[USER]  = 0;
    this->m_state.r10[USER] = 0;
    this->m_state.r11[USER] = 0;
    this->m_state.r12[USER] = 0;
    this->m_state.r13[USER] = 0;
    this->m_state.r14[USER] = 0;
    this->m_state.r8[FIQ]   = 0;
    this->m_state.r9[FIQ]   = 0;
    this->m_state.r10[FIQ]  = 0;
    this->m_state.r11[FIQ]  = 0;
    this->m_state.r12[FIQ]  = 0;
    this->m_state.r13[FIQ]  = 0;
    this->m_state.r14[FIQ]  = 0;
    this->m_state.r13[SVC]  = 0;
    this->m_state.r14[SVC]  = 0;
    this->m_state.r13[IRQ]  = 0;
    this->m_state.r14[IRQ]  = 0;
    this->m_state.cpsr      = 0;
    return 0;
}

int
ARM::StatusFlag(ARM_StatusFlag flag, bool value)
{
    DBG_PRINT((DBG_ULTRA_VERBOSE, "%s status flag: %s\n", (value ? "Setting" : "Clearing"), ARM_StatusFlagStrings[flag]));
    uint32_t cpsr = this->cpsr();
    if (value) {
        cpsr |= ARM_StatusFlagMasks[flag];
    } else {
        cpsr &= ~ARM_StatusFlagMasks[flag];
    }
    return this->cpsr(cpsr);
}

int
ARM::StatusFlag(ARM_StatusFlag flag, bool *value)
{
    *value = (this->cpsr() & ARM_StatusFlagMasks[flag]);
    DBG_PRINT((DBG_ULTRA_VERBOSE, "Reading status flag %s: %s\n", ARM_StatusFlagStrings[flag], (value ? "set" : "clear")));
    return 0;
}

int
ARM::PC(uint32_t value)
{
    uint32_t cpsr = this->cpsr();
    cpsr &= ~ARM_STATUS_MASK_PC;
    cpsr &= (value << 2);
    return this->cpsr(cpsr);
}

int
ARM::PC(uint32_t *value)
{
    uint32_t cpsr = this->cpsr();
    *value = (cpsr & ARM_STATUS_MASK_PC);
    *value = (*value >> 2);
    return 0;
}

int
ARM::Mode(ARM_Mode mode)
{
    DBG_PRINT((DBG_ULTRA_VERBOSE, "Setting processor mode: %s\n", ARM_ModeStrings[mode]));
    uint32_t cpsr = this->cpsr();
    cpsr &= ~ARM_ModeMasks[ALL];
    cpsr &= ARM_ModeMasks[mode];
    return this->cpsr(cpsr);
}

int
ARM::Mode(ARM_Mode *mode)
{
    uint32_t cpsr = this->cpsr();
    cpsr &= ARM_ModeMasks[ALL];
    switch (cpsr) {
        case ARM_STATUS_MASK_MODE_USER: *mode = USER; break;
        case ARM_STATUS_MASK_MODE_FIQ: *mode = FIQ; break;
        case ARM_STATUS_MASK_MODE_IRQ: *mode = IRQ; break;
        case ARM_STATUS_MASK_MODE_SVC: *mode = SVC; break;
        default:
            DBG_PRINT((DBG_ERROR, "Unknown mode mask: 0x%X\n", cpsr));
            return -1;
    }
    DBG_PRINT((DBG_ULTRA_VERBOSE, "Reading processor mode: %s\n", ARM_ModeStrings[*mode]));
    return 0;
}

int
ARM::Register(uint32_t reg, uint32_t value)
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
    ARM_Mode mode_select = this->m_state.mode;
    DBG_PRINT((DBG_ULTRA_VERBOSE, "Setting register [ %s ]: 0x%X\n", ARM_RegisterStrings[reg], value));
    switch (reg) {
        case R0:
            this->m_state.r0 = value;
            break;
        case R1:
            this->m_state.r1 = value;
            break;
        case R2:
            this->m_state.r2 = value;
            break;
        case R3:
            this->m_state.r3 = value;
            break;
        case R4:
            this->m_state.r4 = value;
            break;
        case R5:
            this->m_state.r5 = value;
            break;
        case R6:
            this->m_state.r6 = value;
            break;
        case R7:
            this->m_state.r7 = value;
            break;
        case R8:
            this->GetShadowRegister(this->m_state.r8, &mode_select);
            this->m_state.r8[mode_select] = value;
            break;
        case R9:
            this->GetShadowRegister(this->m_state.r9, &mode_select);
            this->m_state.r9[mode_select] = value;
            break;
        case R10:
            this->GetShadowRegister(this->m_state.r10, &mode_select);
            this->m_state.r10[mode_select] = value;
            break;
        case R11:
            this->GetShadowRegister(this->m_state.r11, &mode_select);
            this->m_state.r11[mode_select] = value;
            break;
        case R12:
            this->GetShadowRegister(this->m_state.r12, &mode_select);
            this->m_state.r12[mode_select] = value;
            break;
        case R13:
            this->GetShadowRegister(this->m_state.r13, &mode_select);
            this->m_state.r13[mode_select] = value;
            break;
        case R14:
            this->GetShadowRegister(this->m_state.r14, &mode_select);
            this->m_state.r14[mode_select] = value;
            break;
        case CPSR:
            this->m_state.cpsr = value;
            break;
        default:
            DBG_PRINT((DBG_ERROR, "Unknown register: %d", reg));
            return -1;
    }
    return 0;
}

int
ARM::Register(uint32_t reg, uint32_t *value)
{
    // N.B: read comment in Register(uint32_t reg, uint32_t value)
    ARM_Mode mode_select = this->m_state.mode;
    switch (reg) {
        case R0:
            *value = this->m_state.r0;
            break;
        case R1:
            *value = this->m_state.r1;
            break;
        case R2:
            *value = this->m_state.r2;
            break;
        case R3:
            *value = this->m_state.r3;
            break;
        case R4:
            *value = this->m_state.r4;
            break;
        case R5:
            *value = this->m_state.r5;
            break;
        case R6:
            *value = this->m_state.r6;
            break;
        case R7:
            *value = this->m_state.r7;
            break;
        case R8:
            this->GetShadowRegister(this->m_state.r8, &mode_select);
            *value = this->m_state.r8[mode_select];
            break;
        case R9:
            this->GetShadowRegister(this->m_state.r9, &mode_select);
            *value = this->m_state.r8[mode_select];
            break;
        case R10:
            this->GetShadowRegister(this->m_state.r10, &mode_select);
            *value = this->m_state.r8[mode_select];
            break;
        case R11:
            this->GetShadowRegister(this->m_state.r11, &mode_select);
            *value = this->m_state.r8[mode_select];
            break;
        case R12:
            this->GetShadowRegister(this->m_state.r12, &mode_select);
            *value = this->m_state.r8[mode_select];
            break;
        case R13:
            this->GetShadowRegister(this->m_state.r13, &mode_select);
            *value = this->m_state.r8[mode_select];
            break;
        case R14:
            this->GetShadowRegister(this->m_state.r14, &mode_select);
            *value = this->m_state.r8[mode_select];
            break;
        case CPSR:
            *value = this->m_state.cpsr;
            break;
        default:
            DBG_PRINT((DBG_ERROR, "Unknown register: %d", reg));
            return -1;
    }
    DBG_PRINT((DBG_ULTRA_VERBOSE, "Getting register [ %s ]: 0x%X\n", ARM_RegisterStrings[reg], *value));
    return 0;
}

int
ARM::GetShadowRegister(uint32_t reg[], ARM_Mode *mode)
{
    if (*mode > sizeof(*reg)/sizeof(reg[0])) {
        *mode = USER;
    }
    return 0;
}

int
ARM::Fetch()
{
    
}

int
ARM::Decode()
{

}

int
ARM::Execute()
{
    
}

/* Simulate input signals as setters */
int
ARM::PH1_Tick()
{

}

int
ARM::PH2_Tick()
{

}

int
ARM::DataBus(uint32_t data)
{
    this->m_state.data = data;
}

int
ARM::AddressBus(uint32_t address)
{
    this->m_state.address = address;
}

int
ARM::AddressBus(uint32_t *address)
{
    *address = this->m_state.address;
}

int
ARM::DataBus(uint32_t *data)
{
    *data = this->m_state.data;
}

int
ARM::ReadWrite(bool *read_write)
{
    *read_write = this->m_state.rw;
}

int
ARM::Interrupt(bool assert)
{
     this->m_state.irq = assert;
}

int
ARM::FastInterrupt(bool assert)
{
    this->m_state.fiq = assert;
}

/* Quick reference getters */
uint32_t ARM::r0() { uint32_t ret_val; this->Register(R0, &ret_val); return ret_val; }
uint32_t ARM::r1() { uint32_t ret_val; this->Register(R1, &ret_val); return ret_val; }
uint32_t ARM::r2() { uint32_t ret_val; this->Register(R2, &ret_val); return ret_val; }
uint32_t ARM::r3() { uint32_t ret_val; this->Register(R3, &ret_val); return ret_val; }
uint32_t ARM::r4() { uint32_t ret_val; this->Register(R4, &ret_val); return ret_val; }
uint32_t ARM::r5() { uint32_t ret_val; this->Register(R5, &ret_val); return ret_val; }
uint32_t ARM::r6() { uint32_t ret_val; this->Register(R6, &ret_val); return ret_val; }
uint32_t ARM::r7() { uint32_t ret_val; this->Register(R7, &ret_val); return ret_val; }
uint32_t ARM::r8() { uint32_t ret_val; this->Register(R8, &ret_val); return ret_val; }
uint32_t ARM::r9() { uint32_t ret_val; this->Register(R9, &ret_val); return ret_val; }
uint32_t ARM::r10() { uint32_t ret_val; this->Register(R10, &ret_val); return ret_val; }
uint32_t ARM::r11() { uint32_t ret_val; this->Register(R11, &ret_val); return ret_val; }
uint32_t ARM::r12() { uint32_t ret_val; this->Register(R12, &ret_val); return ret_val; }
uint32_t ARM::r13() { uint32_t ret_val; this->Register(R13, &ret_val); return ret_val; }
uint32_t ARM::r14() { uint32_t ret_val; this->Register(R14, &ret_val); return ret_val; }
uint32_t ARM::cpsr() { uint32_t ret_val; this->Register(CPSR, &ret_val); return ret_val; }

/* Quick reference setters */
int ARM::r0(uint32_t value) { return this->Register(R0, value); }
int ARM::r1(uint32_t value) { return this->Register(R1, value); }
int ARM::r2(uint32_t value) { return this->Register(R2, value); }
int ARM::r3(uint32_t value) { return this->Register(R3, value); }
int ARM::r4(uint32_t value) { return this->Register(R4, value); }
int ARM::r5(uint32_t value) { return this->Register(R5, value); }
int ARM::r6(uint32_t value) { return this->Register(R6, value); }
int ARM::r7(uint32_t value) { return this->Register(R7, value); }
int ARM::r8(uint32_t value) { return this->Register(R8, value); }
int ARM::r9(uint32_t value) { return this->Register(R9, value); }
int ARM::r10(uint32_t value) { return this->Register(R10, value); }
int ARM::r11(uint32_t value) { return this->Register(R11, value); }
int ARM::r12(uint32_t value) { return this->Register(R12, value); }
int ARM::r13(uint32_t value) { return this->Register(R13, value); }
int ARM::r14(uint32_t value) { return this->Register(R14, value); }
int ARM::cpsr(uint32_t value) { return this->Register(CPSR, value); }

int
ARM::Reset()
{
    // Reset behaviour defined on page 12 of ARM datasheet
    this->m_state = ARM_State();
    this->DataBus((uint32_t)0);
    this->AddressBus((uint32_t)0);
    this->Mode(SVC);
    this->StatusFlag(IRQ_DISABLE, true);
    this->StatusFlag(FIQ_DISABLE, true);
    this->PrintStatus();
}

int
ARM::PrintStatus()
{
    bool negative, zero, carry, overflow, irq_disable, fiq_disable;
    ARM_Mode mode;
    this->StatusFlag(NEGATIVE, &negative);
    this->StatusFlag(ZERO, &zero);
    this->StatusFlag(CARRY, &carry);
    this->StatusFlag(OVERFLOW, &overflow);
    this->StatusFlag(IRQ_DISABLE, &irq_disable);
    this->StatusFlag(FIQ_DISABLE, &fiq_disable);
    this->Mode(&mode);
    DBG_PRINT((DBG_INFO, "| Negative | Zero | Carry | Overflow | IRQ Disable | FIQ Disable | Program Counter |  Mode  |\n"));
    DBG_PRINT((DBG_INFO, "|     %s    |   %s  |   %s   |    %s     |      %s      |      %s      |       0x%X       |  %s  |\n",
               (negative ? "1" : "0"),
               (zero ? "1" : "0"),
               (carry ? "1" : "0"),
               (overflow ? "1" : "0"),
               (irq_disable ? "1" : "0"),
               (fiq_disable ? "1" : "0"),
               0,
               ARM_ModeStrings[mode]));
    return 0;
}

ARM::ARM()
{
    Init();
}

ARM::~ARM()
{
}
