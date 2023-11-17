// File: Branch.h
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

#ifndef BRANCH_H
#define BRANCH_H

// C++ header includes
#include <cstdint>    // uint32_t
#include <functional> // std::function
#include <memory>     // std::shared_ptr

// Project includes
#include "Op.h"

class Branch: public Op
{
public:

    enum class BranchInstruction : int
    {
        BRANCH = 0,
        BRANCH_WITH_LINK
    };

    Branch(uint32_t opCode_, std::shared_ptr<RegisterFile> registerFile_);
    ~Branch();

private:

    static constexpr uint32_t LinkBitMask = 0x01000000;
    static constexpr uint32_t OffsetMask = 0x00FFFFFF;
    static const char* instructionNameStrings[];

    BranchInstruction branchInstruction{BranchInstruction::BRANCH};
    uint32_t branchOffset{0};
    std::function<void(void)> branchExecution;

    void ExecuteBranch();
    void ExecuteBranchWithLink();
    void ParseInstruction();
    bool DoExecute() override;
};

#endif // BRANCH_H
