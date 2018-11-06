/*
 * File: arm.h
 * Author: dgrubb
 * Date:26/04/2018
 */

#ifndef _ARM_H
#define _ARM_H

#include <cstdint> // Fixed-width integer types
#include <map>

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
#define ARM_WORD_BYTES_LENGTH       4

#define ARM_CONDITION_EQ            0b0000  // EQ - Z set (equal)
#define ARM_CONDITION_NE            0b0001  // NE - Z clear (not equal)
#define ARM_CONDITION_CS            0b0010  // CS - C set (unsigned higher or lower)
#define ARM_CONDITION_CC            0b0011  // CC - C clear (unsigned lower)
#define ARM_CONDITION_MI            0b0100  // N set (negative)
#define ARM_CONDITION_PL            0b0101  // N clear (positive or zero)
#define ARM_CONDITION_VS            0b0110  // V set (overflow)
#define ARM_CONDITION_VC            0b0111  // V clear (no overflow)
#define ARM_CONDITION_HI            0b1000  // C set and Z clear (unsigned higher)
#define ARM_CONDITION_LS            0b1001  // C clear or Z set (unsigned lower or same)
#define ARM_CONDITION_GE            0b1010  // N set and V set, or N clear and V clear (greater or equal)
#define ARM_CONDITION_LT            0b1011  // N set and V clear, or N clear and V set (less than)
#define ARM_CONDITION_GT            0b1100  // Z clear and either N set or V set, or N clear and V clear (greater than)
#define ARM_CONDITION_LE            0b1101  // Z set, or N set and V clear, or N clear and V set (less than or equal)
#define ARM_CONDITION_AL            0b1110  // Always
#define ARM_CONDITION_NV            0b1111  // Never
#define ARM_CONDITION_MASK          0xF0000000

#define ARM_OP_MASK                     0x0E0000000
#define ARM_OP_WITH_CODE_MASK           0x0FE000000

using namespace std;

enum ARM_Op_Instruction {
    ARM_OP_INSTRUCTION_DATA_PROCESSING = 0,
    ARM_OP_INSTRUCTION_BRANCH,
    ARM_OP_INSTRUCTION_MULTIPLY,
    ARM_OP_INSTRUCTION_SINGLE_DATA_TRANSFER,
    ARM_OP_INSTRUCTION_BLOCK_DATA_TRANSFER,
    ARM_OP_INSTRUCTION_SOFTWARE_INTERRUPT,
    ARM_OP_INSTRUCTION_COPROCESSOR_DATA_OP,
    ARM_OP_INSTRUCTION_COPROCESSOR_DATA_TRANSFER,
    ARM_OP_INSTRUCTION_COPROCESSOR_REGISTER_TRANSFER,
    ARM_OP_INSTRUCTION_UNDEFINED
};

enum ARM_Op_Type {
    ARM_OP_TYPE_DATA_PROCESSING_REG   = 0x0,
    ARM_OP_TYPE_MOVE_REG              = 0x1,
    ARM_OP_TYPE_DATA_PROCESSING_IMM   = 0x2,
    ARM_OP_TYPE_MOVE_IMM              = 0x3,
    ARM_OP_TYPE_LOAD_STORE_POST_IMM   = 0x4,
    ARM_OP_TYPE_LOAD_STORE_PRE_IMM    = 0x5,
    ARM_OP_TYPE_LOAD_STORE_POST_REG   = 0x6,
    ARM_OP_TYPE_LOAD_STORE_PRE_REG    = 0x7,
    ARM_OP_TYPE_MULTI_LOAD_STORE_POST = 0x8,
    ARM_OP_TYPE_MULTI_LOAD_STORE_PRE  = 0x9,
    ARM_OP_TYPE_BRANCH                = 0xA,
    ARM_OP_TYPE_BRANCH_LINK           = 0xB,
    ARM_OP_TYPE_COPRO_LOAD_STORE_POST = 0xC,
    ARM_OP_TYPE_COPRO_LOAD_STORE_PRE  = 0xD,
    ARM_OP_TYPE_COPRO_DATA_PROCESSING = 0xE,
    ARM_OP_TYPE_SWI                   = 0xF
};

// N.B: These need to be kept in the current order to correctly
// derive whether the modes have shadow registers, see GetShadowRegister()
enum ARM_Mode {
    USER = 0,
    FIQ,
    IRQ,
    SVC,
    ALL
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

enum ARM_DataProcessingOpCode {
    AND = 0,
    EOR,
    SUB,
    RSB,
    ADD,
    ADC,
    SBC,
    RSC,
    TST,
    TEQ,
    CMP,
    CMN,
    ORR,
    MOV,
    BIC,
    MVN,
    ALL_DATA_PROCESSING
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
    bool fiq;
    bool irq;
    bool rw;
    // Clock phase: 
    // true - PH2
    // false - PH2
    bool clock_phase;
    // Buses
    uint32_t address;
    uint32_t data;
    ARM_Pipeline pipeline;
} ARM_State;

typedef uint32_t (*dst_reg)();
typedef int (*src_reg)(uint32_t);
typedef int (*opcode)(dst_reg, src_reg, uint32_t);

class ARM_Op {

public:

    // Constructors and destructors
    ARM_Op(ARM_Op_Instruction instruction);
    ~ARM_Op();

    // Methods
    int execute();

private:

    // Data
    ARM_Op_Type type;
    ARM_Op_Instruction instruction;
    dst_reg destination;
    src_reg source;
    bool immediate;
    bool set_conditions;
};

class ARM {

public:

    // Constructors and destructors
    ARM();
    ~ARM();

    // Methods
    int Init();
    int ClearAllRegisters();
    int PrintStatus();
    bool TestConditions(uint32_t condition_flags);
    bool TestStatusFlag(ARM_StatusFlag flag);
    ARM_Op ParseOp(uint32_t instruction);

    // Accessors for internal state
    int Register(uint32_t reg, uint32_t value);
    int Register(uint32_t reg, uint32_t *value);
    int StatusFlag(ARM_StatusFlag flag, bool value);
    int StatusFlag(ARM_StatusFlag flag, bool *value);
    int Mode(ARM_Mode mode);
    int Mode(ARM_Mode *mode);
    int PC(uint32_t value);
    int PC(uint32_t *value);

    // State updates
    int Fetch();
    int Decode();
    int Execute();
    int UndefinedInstruction();
    int Exception();
    int FlushPipeline();

    // Input/output signals
    int Reset();
    int Abort();
    int Interrupt(bool assert);
    int FastInterrupt(bool assert);
    int ReadWrite(bool *read_write);
    int AddressBus(uint32_t *address);
    int AddressBus(uint32_t address);
    int DataBus(uint32_t *data);
    int DataBus(uint32_t data);
    int ClockTick();

    // Quick references for interfaces
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

    // Op-codes

    // Data processing operations
    int OpAND(dst_reg dst, src_reg src, uint32_t op2);
    int OpEOR(dst_reg dst, src_reg src, uint32_t op2);
    int OpSUB(dst_reg dst, src_reg src, uint32_t op2);
    int OpRSB(dst_reg dst, src_reg src, uint32_t op2);
    int OpADD(dst_reg dst, src_reg src, uint32_t op2);
    int OpADC(dst_reg dst, src_reg src, uint32_t op2);
    int OpSBC(dst_reg dst, src_reg src, uint32_t op2);
    int OpRSC(dst_reg dst, src_reg src, uint32_t op2);
    int OpTST(dst_reg dst, src_reg src, uint32_t op2);
    int OpTEQ(dst_reg dst, src_reg src, uint32_t op2);
    // Move-compare operations
    int OpCMP(dst_reg dst, src_reg src, uint32_t op2);
    int OpCMN(dst_reg dst, src_reg src, uint32_t op2);
    int OpORR(dst_reg dst, src_reg src, uint32_t op2);
    int OpMOV(dst_reg dst, src_reg src, uint32_t op2);
    int OpBIC(dst_reg dst, src_reg src, uint32_t op2);
    int OpMVN(dst_reg dst, src_reg src, uint32_t op2);
    // Branch and link instructions
    int OpB(dst_reg dst, src_reg src, uint32_t op2);
    int OpBL(dst_reg dst, src_reg src, uint32_t op2);
    // Multiply and multiply-accumulate
    int OpMUL(dst_reg dst, src_reg src, uint32_t op2);
    int OpMLA(dst_reg dst, src_reg src, uint32_t op2);
    // Single data transfer
    int OpLDR(dst_reg dst, src_reg src, uint32_t op2);
    int OpSTR(dst_reg dst, src_reg src, uint32_t op2);
    // Block data transfer
    int OpLDM(dst_reg dst, src_reg src, uint32_t op2);
    int OpSTM(dst_reg dst, src_reg src, uint32_t op2);


private:

    // Data
    ARM_State m_state;
    opcode *m_ISA_data_processing[ALL_DATA_PROCESSING];

    // Methods
    int GetShadowRegister(uint32_t reg[], ARM_Mode *mode);
};

#endif // _ARM_H
