// File: Op.cc
// Author: dgrubb
// Date: 02/01/2023
//
// Base class for all op-codes to implement common operations
// such as checking condition flags.

// Implementation header
#include "Op.h"

// Project includes
#include "Log.h"

Op::Op(uint32_t opCode_, std::shared_ptr<RegisterFile> registerFile_)
  :  opCode{opCode_},
     registerFile{registerFile_}
{
    conditionField = ((opCode & ConditionFieldMask) >> 28);
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
            // NEGATIVE equals OVERFLOW
            return ((cpsr & Cpsr::statusFlagsMasks[Cpsr::StatusFlag::NEGATIVE]) ==
                    (cpsr & Cpsr::statusFlagsMasks[Cpsr::StatusFlag::OVERFLOW]));
        case LT:
            // NEGATIVE not equal to OVERFLOW
            return ((cpsr & Cpsr::statusFlagsMasks[Cpsr::StatusFlag::NEGATIVE]) !=
                    (cpsr & Cpsr::statusFlagsMasks[Cpsr::StatusFlag::OVERFLOW]));
        case GT:
            // ZERO is clear, and either NEGATIVE is set and OVERFLOW is set, or NEGATIVE
            // is clear and OVERFLOW clear
            return (!(cpsr & Cpsr::statusFlagsMasks[Cpsr::StatusFlag::ZERO]) &&
                    ((cpsr & Cpsr::statusFlagsMasks[Cpsr::StatusFlag::NEGATIVE]) ==
                     (cpsr & Cpsr::statusFlagsMasks[Cpsr::StatusFlag::OVERFLOW])));
        case LE:
            // ZERO is set, or NEGATIVE not equal to OVERFLOW
            return ((cpsr & Cpsr::statusFlagsMasks[Cpsr::StatusFlag::ZERO]) ||
                    ((cpsr & Cpsr::statusFlagsMasks[Cpsr::StatusFlag::NEGATIVE]) !=
                    (cpsr & Cpsr::statusFlagsMasks[Cpsr::StatusFlag::OVERFLOW])));
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