/*
 * File: arm2.h
 * Author: dgrubb
 * Date: 11/03/2019
 */

#ifndef _ACORN_ARM2_H
#define _ACORN_ARM2_H

/* Library includes */
#include <stdbool.h>
#include <stdint.h>

#define ARM2_STATUS_MASK_NEGATIVE    0x80000000
#define ARM2_STATUS_MASK_ZERO        0x40000000
#define ARM2_STATUS_MASK_CARRY       0x20000000
#define ARM2_STATUS_MASK_OVERFLOW    0x10000000
#define ARM2_STATUS_MASK_IRQ_DISABLE 0x08000000
#define ARM2_STATUS_MASK_FIQ_DISABLE 0x04000000

#define ARM2_STATUS_MASK_MODE_USER   0x0
#define ARM2_STATUS_MASK_MODE_FIQ    0x1
#define ARM2_STATUS_MASK_MODE_IRQ    0x2
#define ARM2_STATUS_MASK_MODE_SVC    0x3
#define ARM2_STATUS_MASK_MODE_ALL    ARM2_STATUS_MASK_MODE_SVC

#define ARM2_STATUS_MASK_PC          0x3FFFFFC
#define ARM2_WORD_BYTES_LENGTH       4

#define ARM2_CONDITION_EQ            0x0  /* EQ - Z set (equal) */
#define ARM2_CONDITION_NE            0x1  /* NE - Z clear (not equal) */
#define ARM2_CONDITION_CS            0x2  /* CS - C set (unsigned higher or lower) */
#define ARM2_CONDITION_CC            0x3  /* CC - C clear (unsigned lower) */
#define ARM2_CONDITION_MI            0x4  /* N set (negative) */
#define ARM2_CONDITION_PL            0x5  /* N clear (positive or zero) */
#define ARM2_CONDITION_VS            0x6  /* V set (overflow) */
#define ARM2_CONDITION_VC            0x7  /* V clear (no overflow) */
#define ARM2_CONDITION_HI            0x8  /* C set and Z clear (unsigned higher) */
#define ARM2_CONDITION_LS            0x9  /* C clear or Z set (unsigned lower or same) */
#define ARM2_CONDITION_GE            0xA  /* N set and V set, or N clear and V clear (greater or equal) */
#define ARM2_CONDITION_LT            0xB  /* N set and V clear, or N clear and V set (less than) */
#define ARM2_CONDITION_GT            0xC  /* Z clear and either N set or V set, or N clear and V clear (greater than) */
#define ARM2_CONDITION_LE            0xD  /* Z set, or N set and V clear, or N clear and V set (less than or equal) */
#define ARM2_CONDITION_AL            0xE  /* Always */
#define ARM2_CONDITION_NV            0xF  /* Never */
#define ARM2_CONDITION_MASK          0xF0000000

/* N.B: These need to be kept in the current order to correctly
 * derive whether the modes have shadow registers, see get_shadow_register()
 */
typedef enum {
    USER = 0,
    FIQ,
    IRQ,
    SVC,
    ALL
} ARM2_Mode;

#define FIQ_LEN FIQ+1
#define SVC_LEN SVC+1

typedef enum {
    NONE,
    BRANCH,
    DATA_PROCESSING,
    MULTIPLY,
    DATA_TRANSFER,
    BLOCK_DATA_TRANSFER,
    SOFTWARE_INTERRUPT,
    CO_PRO_DATA_TRANSFER,
    CO_PRO_DATA_OP,
    CO_PRO_REGISTER_TRANSFER,
    OP_TABLE_SIZE
} ARM2_Op;

typedef enum {
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
} ARM2_Register;

typedef enum {
    NEGATIVE = 0,
    ZERO,
    CARRY,
    OVERFLOW,
    IRQ_DISABLE,
    FIQ_DISABLE
} ARM2_StatusFlag;

typedef struct {
    uint32_t fetch, decode, execute;
} ARM2_Pipeline;

typedef struct {
    ARM2_Mode mode;
    /* User mode accessible registers */
    uint32_t r0, r1, r2, r3, r4, r5, r6, r7;
    /* Registers with FIQ shadowed registers
     * E.g.,
     * rX[0] = rX_user
     * rX[1] = rX_fiq
     */
    uint32_t r8[FIQ_LEN];
    uint32_t r9[FIQ_LEN];
    uint32_t r10[FIQ_LEN];
    uint32_t r11[FIQ_LEN];
    uint32_t r12[FIQ_LEN];
    /* Registers with FIQ, IRQ and SVC shadowed registers
     * E.g.,
     * rX[0] = rX_user
     * rX[1] = rX_fiq
     * rX[1] = rX_irq
     * rX[1] = rX_svc
     */
    uint32_t r13[SVC_LEN];
    uint32_t r14[SVC_LEN];
    uint32_t cpsr;
    bool fiq;
    bool irq;
    /* Low/false for processor read, high/true for write */
    bool rw;
    /* Buses */
    uint32_t address;
    uint32_t data;
    ARM2_Pipeline pipeline;
} ARM2_State;

/* Functions for testing/parsing/decoding ops */
ARM2_Op arm2_parse_op(uint32_t op);

/* Quick references for interfaces */
uint32_t get_r0(); int set_r0(uint32_t value);
uint32_t get_r1(); int set_r1(uint32_t value);
uint32_t get_r2(); int set_r2(uint32_t value);
uint32_t get_r3(); int set_r3(uint32_t value);
uint32_t get_r4(); int set_r4(uint32_t value);
uint32_t get_r5(); int set_r5(uint32_t value);
uint32_t get_r6(); int set_r6(uint32_t value);
uint32_t get_r7(); int set_r7(uint32_t value);
uint32_t get_r8(); int set_r8(uint32_t value);
uint32_t get_r9(); int set_r9(uint32_t value);
uint32_t get_r10(); int set_r10(uint32_t value);
uint32_t get_r11(); int set_r11(uint32_t value);
uint32_t get_r12(); int set_r12(uint32_t value);
uint32_t get_r13(); int set_r13(uint32_t value);
uint32_t get_r14(); int set_r14(uint32_t value);
uint32_t get_cpsr(); int set_cpsr(uint32_t value);

/* External interfaces */
int arm2_get_address_bus(uint32_t *addr);
int arm2_get_data_bus(uint32_t *data);
int arm2_set_data_bus(uint32_t data);
int arm2_get_read_write(bool *rw);

/* Logical interfaces */
int arm2_set_PC(uint32_t value);
int arm2_get_PC(uint32_t *value);
int arm2_set_mode(ARM2_Mode mode);
int arm2_get_mode(ARM2_Mode *mode);
int arm2_set_status_flag(ARM2_StatusFlag flag, bool value);
int arm2_get_status_flag(ARM2_StatusFlag flag, bool *value);
int arm2_get_shadow_register(uint32_t reg[], ARM2_Mode *mode);

/* Worker functions which advance or otherwise interact
 * with the state machine
 */
int arm2_clock();
int arm2_init();
int arm2_reset();
int arm2_fetch();
int arm2_decode();
int arm2_execute();
int arm2_flush_pipeline();
int arm2_print_status();
bool arm2_test_conditions(uint32_t condition_flags);
bool arm2_test_status_flag(ARM2_StatusFlag flag);

#endif /* _ACORN_ARM2_H */
