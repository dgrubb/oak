/*
 * File: arm2.c
 * Author: dgrubb
 * Date: 11/03/2019
 */

/* Project includes */
#include "arm2.h"
#include "debug.h"

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


