// File: Branch.cc
// Author: dgrubb
// Date: 03/22/2023
//
// Implements a class to exeute a Branch or Branch-With-Link
// instruction.

// Implementation header
#include "Branch.h"

// Project includes
#include "Log.h"

Branch::Branch(uint32_t opCode_, std::shared_ptr<RegisterFile> registerFile_)
  : Op(opCode_, registerFile_)
{
}

Branch::~Branch()
{
}

bool Branch::DoExecute()
{
    return true;
}

Branch::BranchInstruction Branch::ParseInstruction()
{
    if (Branch::LinkBitMask & opCode)
    {
        return Branch::BranchInstruction::BRANCH_WITH_LINK;
    }
    return Branch::BranchInstruction::BRANCH;
}
