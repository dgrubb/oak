// File: Branch.h
// Author: dgrubb
// Date: 03/22/2023
//
// Implements a class to exeute a Branch or Branch-With-Link
// instruction.

#ifndef BRANCH_H
#define BRANCH_H

// C++ header includes
#include <cstdint> // uint32_t
#include <memory>  // std::shared_ptr

// Project includes
#include "Op.h"

class Branch: public Op
{
public:

    enum BranchInstruction
    {
        BRANCH = 0,
        BRANCH_WITH_LINK
    };

    Branch(uint32_t opCode_, std::shared_ptr<RegisterFile> reigsterFile_);
    ~Branch();

private:

    // TODO figure out bitmask here
    static constexpr uint32_t LinkBitMask = 0x00000000;

    BranchInstruction ParseInstruction();
    bool DoExecute() override;
};

#endif // BRANCH_H
