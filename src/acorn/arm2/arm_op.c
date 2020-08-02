/*
 * File: arm_op.c
 * Author: dgrubb
 * Date: 11/03/2019
 */

/* Project includes */
#include "arm2.h"
#include "debug.h"

ARM2_Op
arm2_parse_op(uint32_t op)
{
    // NOOP
    if (0xffffffff == op) {
        return NONE;
    }

    // Bit 27 is always 1 on
    if (op & (1 << 27)) {
        return BRANCH;
    }

    // Bit 26 is always 1
    if (op & (1 << 26)) {
        return DATA_TRANSFER;
    }

    // Immediate flag is set which isn't supported for multiply so we know
    // this must be a data processing instruction
    if (op & (1 << 25)) {
        return DATA_PROCESSING;
    }

    // Bit 7 is always a 1 in a multiply
    if (!(op & (1<<7))) {
        return DATA_PROCESSING;
    }

    // Bit 4 is also always a 1 in a multiply
    if (!(op & (1<<4))) {
        return DATA_PROCESSING;
    }

    // ... I guess?
    return MULTIPLY;
}

