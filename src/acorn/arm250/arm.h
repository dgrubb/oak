/*
 * File: arm.h
 * Author: dgrubb
 * Date:26/04/2018
 */

#ifndef _ARM_H
#define _ARM_H

#include <cstdint> // Fixed-width integer types

#define ARM_STATUS_MASK_NEGATIVE    0x80000000
#define ARM_STATUS_MASK_ZERO        0x40000000
#define ARM_STATUS_MASK_CARRY       0x20000000
#define ARM_STATUS_MASK_OVERFLOW    0x10000000
#define ARM_STATUS_MASK_IRQ_DISABLE 0x08000000
#define ARM_STATUS_MASK_FIQ_DISABLE 0x04000000

#define ARM_STATUS_MASK_MODE_USER   0x0
#define ARM_STATUS_MASK_MODE_FIQ    0x1
#define ARM_STATUS_MASK_MODE_IRQ    0x3
#define ARM_STATUS_MASK_MODE_SVC    0x4
#define ARM_STATUS_MASK_MODE_ALL    0xF

#define ARM_STATUS_MASK_PC          0x3FFFFFC

using namespace std;

// N.B: These need to be kept in the current order to correctly
// derive whether the modes have shadow registers, see GetShadowRegister()
enum ARM_Mode {
    USER = 0,
    FIQ,
    IRQ,
    SVC
};

const uint32_t FIQ_LEN = FIQ+1;
const uint32_t SVC_LEN = SVC+1;

enum ARM_Register {
    R0 = 0,
    R1,
    R2,
    R3,
    R4,
    R5,
    R6,
    R7,
    R8,
    R9,
    R10,
    R11,
    R12,
    R13,
    R14,
    CPSR
};

enum ARM_StatusFlag {
    NEGATIVE = 0,
    ZERO,
    CARRY,
    OVERFLOW,
    IRQ_DISABLE,
    FIQ_DISABLE
};

const uint32_t ARM_StatusFlagMasks[] = {
    ARM_STATUS_MASK_NEGATIVE,
    ARM_STATUS_MASK_ZERO,
    ARM_STATUS_MASK_CARRY,
    ARM_STATUS_MASK_OVERFLOW,
    ARM_STATUS_MASK_IRQ_DISABLE,
    ARM_STATUS_MASK_FIQ_DISABLE
};

typedef struct {
    uint32_t fetch, decode, execute;
} ARM_Pipeline;

typedef struct {
    ARM_Mode mode;
    // User mode accessible registers
    uint32_t r0, r1, r2, r3, r4, r5, r6, r7;
    // Registers with FIQ shadowed registers
    // E.g.,
    // rX[0] = rX_user
    // rX[1] = rX_fiq
    uint32_t r8[FIQ_LEN];
    uint32_t r9[FIQ_LEN];
    uint32_t r10[FIQ_LEN];
    uint32_t r11[FIQ_LEN];
    uint32_t r12[FIQ_LEN];
    // Registers with FIQ, IRQ and SVC shadowed registers
    // E.g.,
    // rX[0] = rX_user
    // rX[1] = rX_fiq
    // rX[1] = rX_irq
    // rX[1] = rX_svc
    uint32_t r13[SVC_LEN];
    uint32_t r14[SVC_LEN];
    uint32_t cpsr;
    ARM_Pipeline pieline;
} ARM_State;

class ARM {

public:

    // Constructors and destructors
    ARM();
    ~ARM();

    // Methods
    int Init();
    int Reset();
    int Tick();
    int Register(uint32_t reg, uint32_t value);
    int Register(uint32_t reg, uint32_t *value);

    int StatusFlag(ARM_StatusFlag flag, bool value);
    int StatusFlag(ARM_StatusFlag flag, bool *value);

    int Mode(ARM_Mode mode);
    int Mode(ARM_Mode *mode);

    int PC(uint32_t value);
    int PC(uint32_t *value);

    uint32_t r0(); int r0(uint32_t value);
    uint32_t r1(); int r1(uint32_t value);
    uint32_t r2(); int r2(uint32_t value);
    uint32_t r3(); int r3(uint32_t value);
    uint32_t r4(); int r4(uint32_t value);
    uint32_t r5(); int r5(uint32_t value);
    uint32_t r6(); int r6(uint32_t value);
    uint32_t r7(); int r7(uint32_t value);
    uint32_t r8(); int r8(uint32_t value);
    uint32_t r9(); int r9(uint32_t value);
    uint32_t r10(); int r10(uint32_t value);
    uint32_t r11(); int r11(uint32_t value);
    uint32_t r12(); int r12(uint32_t value);
    uint32_t r13(); int r13(uint32_t value);
    uint32_t r14(); int r14(uint32_t value);
    uint32_t cpsr(); int cpsr(uint32_t value);

private:

    // Data
    ARM_State m_state;

    // Methods
    int GetShadowRegister(uint32_t reg[], ARM_Mode *mode);
};

#endif // _ARM_H
