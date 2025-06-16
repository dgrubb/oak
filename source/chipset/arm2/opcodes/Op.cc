// File: Op.cc
// Author: dgrubb
// Date: 02/01/2023
//
// Base class for all op-codes to implement common operations
// such as checking condition flags.

// Implementation header
#include "Op.h"

// Project includes
#include "Integral.h"
#include "Log.h"

const char* Op::conditionFieldsNameStrings[] = {
    "0000, EQ, Z set (equal)",
    "0001, NE, Z clear (not equal)",
    "0010, CS, C set (unsigned higher or same)",
    "0011, CC, C clear (unsigned lower)",
    "0100, MI, N set (negative)",
    "0101, PL, N clear (negative)",
    "0110, VS, V set (overflow)",
    "0111, VC, V clear (no overflow)",
    "1000, HI, C set and Z clear (unsigned higher)",
    "1001, LS, C clear or Z set (unsigned lower or same)",
    "1010, GE, N set and V set, or N clear and V clear (greater or equal)",
    "1011, LT, N set and V clear, or N clear and V set (less than)",
    "1100, GT, Z clear, and either N set and V set, or N clear and V clear (greater than)",
    "1101, LE, Z set, or N set and V clear, or N clear and V set (less than or equal)",
    "1110, AL, always",
    "1111, NV, never"
};

Op::Op(uint32_t opCode_, std::shared_ptr<RegisterFile> registerFile_)
  :  opCode{opCode_},
     registerFile{registerFile_}
{
    conditionField = ((opCode & ConditionFieldMask) >> 28);
}

Op::~Op()
{
}

bool Op::CheckConditions()
{
    TRACE("Checking: ", conditionFieldsNameStrings[conditionField]);
    auto& cpsr = registerFile->GetCPSR();

    switch (conditionField)
    {
        case EQ:
            // ZERO flag is set
            return cpsr.GetStatusFlag(Cpsr::StatusFlag::ZERO);
        case NE:
            // ZERO flag is clear
            return !cpsr.GetStatusFlag(Cpsr::StatusFlag::ZERO);
        case CS:
            // CARRY flag is set
            return cpsr.GetStatusFlag(Cpsr::StatusFlag::CARRY);
        case CC:
            // CARRY flag is clear
            return !cpsr.GetStatusFlag(Cpsr::StatusFlag::CARRY);
        case MI:
            // NEGATIVE flag is set
            return cpsr.GetStatusFlag(Cpsr::StatusFlag::NEGATIVE);
        case PL:
            // NEGATIVE flag is clear
            return !cpsr.GetStatusFlag(Cpsr::StatusFlag::NEGATIVE);
        case VS:
            // OVERFLOW is set
            return cpsr.GetStatusFlag(Cpsr::StatusFlag::OVERFLOW);
        case VC:
            // OVERFLOW is clear
            return !cpsr.GetStatusFlag(Cpsr::StatusFlag::OVERFLOW);
        case HI:
            // CARRY is set and ZERO is clear
            return cpsr.GetStatusFlag(Cpsr::StatusFlag::CARRY) &&
                   !cpsr.GetStatusFlag(Cpsr::StatusFlag::ZERO);
        case LS:
            // CARRY is clear or ZERO is set
            return !cpsr.GetStatusFlag(Cpsr::StatusFlag::CARRY) ||
                   cpsr.GetStatusFlag(Cpsr::StatusFlag::ZERO);
        case GE:
            // NEGATIVE equals OVERFLOW
            return cpsr.GetStatusFlag(Cpsr::StatusFlag::NEGATIVE) ==
                   cpsr.GetStatusFlag(Cpsr::StatusFlag::OVERFLOW);
        case LT:
            // NEGATIVE not equal to OVERFLOW
            return cpsr.GetStatusFlag(Cpsr::StatusFlag::NEGATIVE) !=
                   cpsr.GetStatusFlag(Cpsr::StatusFlag::OVERFLOW);
        case GT:
            // ZERO is clear, and either NEGATIVE is set and OVERFLOW is set, or NEGATIVE
            // is clear and OVERFLOW clear
            return !cpsr.GetStatusFlag(Cpsr::StatusFlag::ZERO) &&
                   (cpsr.GetStatusFlag(Cpsr::StatusFlag::NEGATIVE) ==
                    cpsr.GetStatusFlag(Cpsr::StatusFlag::OVERFLOW));
        case LE:
            // ZERO is set, or NEGATIVE not equal to OVERFLOW
            return cpsr.GetStatusFlag(Cpsr::StatusFlag::ZERO) ||
                   (cpsr.GetStatusFlag(Cpsr::StatusFlag::NEGATIVE) !=
                    cpsr.GetStatusFlag(Cpsr::StatusFlag::OVERFLOW));
        case AL:
            // Always
            return true;
        case NV:
            // Never
            return false;
        default:
            ERROR("Unknown condition field: ", conditionField);
            return false;
    }
}

bool Op::Execute()
{
    // If this is the first tick for this instruction it's necessary to
    // ensure conditions are valid prior to attempting any further computation.
    // If the condition fields denote the instruction can't be executed at
    // this time then indicate this instruction is completed.
    if (0 == cycleCount && !conditionsMet)
    {
        if (!CheckConditions())
        {
            TRACE("Op conditions not met, no further execution required");
            return true;
        }
        else
        {
            conditionsMet = true;
        }
    }

    // Execute a tick of the derived instruction
    cycleCount++;
    TRACE("Instruction cycle count: ", cycleCount);
    return execute();
}
