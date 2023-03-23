// File: Branch.cc
// Author: dgrubb
// Date: 03/22/2023
//
// Implements a class to exeute a Branch or Branch-With-Link
// instruction.
//
// B - Manipulates the PC directly by taking an offset value
//     from the lower 24 bits of the instruction, left shifting
//     by two bits to align with the PC field in the CPSR register,
//     and adding the two.
//
// BL - Performs the same offset additon as B, but also stores the
//      current CPSR value in R14. Writing R14 back into the CPSR
//      at the end of the routine allows for a quick return back
//      into the program flow.


// Implementation header
#include "Branch.h"

// Project includes
#include "Log.h"

const char* Branch::instructionNameStrings[] = {
    "BRANCH",
    "BRANCH WITH LINK"
};

Branch::Branch(uint32_t opCode_, std::shared_ptr<RegisterFile> registerFile_)
  : Op(opCode_, registerFile_)
{
    ParseInstruction();
}

Branch::~Branch()
{
}

bool Branch::DoExecute()
{
    return true;
}

void Branch::ParseInstruction()
{
    if (Branch::LinkBitMask & opCode)
    {
        branchInstruction = Branch::BranchInstruction::BRANCH_WITH_LINK;
    }
    else
    {
        branchInstruction = Branch::BranchInstruction::BRANCH;
    }
    branchOffset = (Branch::OffsetMask & opCode);

    DEBUG("Branch instruction parsed: ", instructionNameStrings[branchInstruction], ", offset: ", branchOffset);
}
