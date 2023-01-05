// File: Op.h
// Author: dgrubb
// Date: 02/01/2023
//
// Base class for all op-codes to implement common operations
// such as checking condition flags.

// Implementation header
#include "Op.h"

// Project includes
#include "Log.h"

Op::Op(uint32_t opcode_, std::shared_ptr<RegisterFile> registerFile_)
  :  opcode{opcode_},
     registerFile{registerFile_}
{
    conditionField = ((opcode & ConditionFieldMask) >> 28);
}

bool Op::CheckConditions()
{
    auto cpsr = registerFile->GetCPSR();

    switch (conditionField)
    {
        case EQ:
            // ZERO flag is set
            return (cpsr & Cpsr::statusFlagsMasks[Cpsr::StatusFlag::ZERO]);
        case NE:
            // ZERO flag is clear
            return !(cpsr & Cpsr::statusFlagsMasks[Cpsr::StatusFlag::ZERO]);
        case CS:
            // CARRY flag is set
            return (cpsr & Cpsr::statusFlagsMasks[Cpsr::StatusFlag::CARRY]);
        case CC:
            // CARRY flag is clear
            return !(cpsr & Cpsr::statusFlagsMasks[Cpsr::StatusFlag::CARRY]);
        case MI:
            // NEGATIVE flag is set
            return (cpsr & Cpsr::statusFlagsMasks[Cpsr::StatusFlag::NEGATIVE]);
        case PL:
            // NEGATIVE flag is clear
            return !(cpsr & Cpsr::statusFlagsMasks[Cpsr::StatusFlag::NEGATIVE]);
        case VS:
            // OVERFLOW is set
            return (cpsr & Cpsr::statusFlagsMasks[Cpsr::StatusFlag::OVERFLOW]);
        case VC:
            // OVERFLOW is clear
            return !(cpsr & Cpsr::statusFlagsMasks[Cpsr::StatusFlag::OVERFLOW]);
        case HI:
            // CARRY is set and ZERO is clear
            return  (cpsr & Cpsr::statusFlagsMasks[Cpsr::StatusFlag::CARRY]) &&
                   !(cpsr & Cpsr::statusFlagsMasks[Cpsr::StatusFlag::ZERO]);
        case LS:
            // CARRY is clear or ZERO is set
            return  !(cpsr & Cpsr::statusFlagsMasks[Cpsr::StatusFlag::CARRY]) ||
                    (cpsr & Cpsr::statusFlagsMasks[Cpsr::StatusFlag::ZERO]);
        case GE:
            // NEGATIVE is set and OVERFLOW is set, or NEGATIVE is clear and
            // OVERFLOW is set
            return ((cpsr & Cpsr::statusFlagsMasks[Cpsr::StatusFlag::NEGATIVE]) &&
                     (cpsr & Cpsr::statusFlagsMasks[Cpsr::StatusFlag::OVERFLOW])) ||
                   (!(cpsr & Cpsr::statusFlagsMasks[Cpsr::StatusFlag::NEGATIVE]) &&
                     (cpsr & Cpsr::statusFlagsMasks[Cpsr::StatusFlag::OVERFLOW]));
        case LT: return true;
        case GT: return true;
        case LE: return true;
        case AL: return true;
        case NV: return false;
    }

    return false;
}

bool Op::Execute()
{
    if (executionCompleted)
    {
        TRACE("Op execution completed, no further execution reqiured");
        return true;
    }

    // Check the cycle count first before re-checking all the potential
    // condition fields again
    if (!cycleCount && !CheckConditions())
    {
        TRACE("Op conditions not met, no further execution required");
        executionCompleted = true;
        return true;
    }
    return DoExecute();
}

Op::~Op()
{
}
