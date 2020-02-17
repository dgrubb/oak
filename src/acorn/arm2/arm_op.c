/*
 * File: arm_op.c
 * Author: dgrubb
 * Date: 11/03/2019
 */

/* Project includes */
#include "arm2.h"
#include "debug.h"

ARM2_Op_Test op_test_table[OP_TABLE_SIZE];

void
arm2_populate_op_test_table()
{
    op_test_table[BRANCH].op = BRANCH;
    op_test_table[BRANCH].test = arm2_is_branch_op;

    op_test_table[DATA_PROCESSING].op = DATA_PROCESSING;
    op_test_table[DATA_PROCESSING].test = arm2_is_data_processing_op;

    op_test_table[MULTIPLY].op = MULTIPLY;
    op_test_table[MULTIPLY].test = arm2_is_multiply_op;

    op_test_table[DATA_TRANSFER].op = DATA_TRANSFER;
    op_test_table[DATA_TRANSFER].test = arm2_is_single_data_transfer_op;

    op_test_table[BLOCK_DATA_TRANSFER].op = BLOCK_DATA_TRANSFER;
    op_test_table[BLOCK_DATA_TRANSFER].test = arm2_is_block_transfer_op;

    op_test_table[SOFTWARE_INTERRUPT].op = SOFTWARE_INTERRUPT;
    op_test_table[SOFTWARE_INTERRUPT].test = arm2_is_software_interrupt_op;

    op_test_table[CO_PRO_DATA_TRANSFER].op = CO_PRO_DATA_TRANSFER;
    op_test_table[CO_PRO_DATA_TRANSFER].test = arm2_is_co_pro_data_transfer_op;

    op_test_table[CO_PRO_DATA_OP].op = CO_PRO_DATA_OP;
    op_test_table[CO_PRO_DATA_OP].test = arm2_is_co_pro_data_op_op;

    op_test_table[CO_PRO_REGISTER_TRANSFER].op = CO_PRO_REGISTER_TRANSFER;
    op_test_table[CO_PRO_REGISTER_TRANSFER].test = arm2_is_co_pro_register_transfer_op;
}

ARM2_Op
arm2_parse_op(uint32_t op)
{
    int i;
    for (i=0; i<OP_TABLE_SIZE; i++) {
        if (op_test_table[i].test(op)) {
            return op_test_table[i].op;
        }
    }
    return NONE;
}

bool
arm2_is_data_processing_op(uint32_t op)
{
}

bool
arm2_is_multiply_op(uint32_t op)
{
}

bool
arm2_is_single_data_transfer_op(uint32_t op)
{
}

bool
arm2_is_block_transfer_op(uint32_t op)
{
}

bool
arm2_is_branch_op(uint32_t op)
{
}

bool
arm2_is_co_pro_data_transfer_op(uint32_t op)
{
}

bool
arm2_is_co_pro_data_op_op(uint32_t op)
{
}

bool
arm2_is_co_pro_register_transfer_op(uint32_t op)
{
}

bool
arm2_is_software_interrupt_op(uint32_t op)
{

}
