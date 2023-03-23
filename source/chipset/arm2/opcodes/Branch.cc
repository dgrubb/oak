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
    "[B] BRANCH",
    "[BL] BRANCH WITH LINK"
};

Branch::Branch(uint32_t opCode_, std::shared_ptr<RegisterFile> registerFile_)
  : Op(opCode_, registerFile_)
{
    ParseInstruction();
}

Branch::~Branch()
{
}

void Branch::ExecuteBranch()
{
    TRACE("Executing: ",
          instructionNameStrings[Branch::BranchInstruction::BRANCH],
          ", offset: ",
          branchOffset);

    // The current PC content is summed with the offset specified
    // in the instruction to create a jump address to be written
    // into the PC
    auto pc = registerFile->GetProgramCounter();
    pc = (pc + branchOffset) & Branch::OffsetMask;

    // Reload the appropriate register contents
    registerFile->SetProgramCounter(pc);
}

void Branch::ExecuteBranchWithLink()
{
    TRACE("Executing: ",
          instructionNameStrings[Branch::BranchInstruction::BRANCH_WITH_LINK],
          ", offset: ",
          branchOffset);

    auto pc = registerFile->GetProgramCounter();
    // The link address is the next address in the program counter, so that
    // on completion of the branch subroutine the CPU can resume where it left
    // off by simply writing that address back into the PC
    auto linkAddress = pc+1;

    // Meanwhile, the current PC content is summed with the
    // offset specified in the instruction to create a jump
    // address to be written into the PC
    pc = (pc + branchOffset) & Branch::OffsetMask;

    // Reload the appropriate register contents
    registerFile->SetRegisterValue(RegisterFile::RegisterRef::R14, linkAddress);
    registerFile->SetProgramCounter(pc);
}

bool Branch::DoExecute()
{
    branchExecution();
    return true;
}

void Branch::ParseInstruction()
{
    branchOffset = (Branch::OffsetMask & opCode);
    if (Branch::LinkBitMask & opCode)
    {
        branchExecution = [this](){ ExecuteBranchWithLink(); };
    }
    else
    {
        branchExecution = [this](){ ExecuteBranch(); };
    }

}
