// File: BlockTransfer.h
// Author: dgrubb
// Date: 11/17/2023
//
// Implements a class to exeute a Block data transfer instruction.
//
// LDM - Loads several registers from a block of memory.
//
// STM - Stores the content of several registers into a block
//       of memory.

#ifndef BLOCKTRANSFER_H
#define BLOCKTRANSFER_H

// C++ header includes
#include <cstdint> // uint32_t
#include <memory>  // std::shared_ptr

// Project includes
#include "Op.h"

class BlockTransfer final: public Op
{
public:

    enum class BlockTransferInstruction : int
    {
        LOAD_MEMORY = 0,
        STORE_MEMORY
    };

    BlockTransfer(uint32_t opCode_, std::shared_ptr<RegisterFile> registerFile_);
    ~BlockTransfer();

private:

    static const char* instructionNameStrings[];

    void ParseInstruction();
    bool DoExecute() override;
};

#endif // BLOCKTRANSFER_H
