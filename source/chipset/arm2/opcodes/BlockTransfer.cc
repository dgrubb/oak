// File: BlockTransfer.cc
// Author: dgrubb
// Date: 11/17/2023
//
// Implements a class to exeute a Block data transfer instruction.
//
// LDM - Loads several registers from a block of memory.
//
// STM - Stores the content of several registers into a block
//       of memory.

// Implementation header
#include "BlockTransfer.h"

// Project includes
#include "Integral.h"
#include "Log.h"

const char* BlockTransfer::instructionNameStrings[] = {
    "[LDM] LOAD MEMORY",
    "[STM] STORE MEMORY"
};

BlockTransfer::BlockTransfer(uint32_t opCode_, std::shared_ptr<RegisterFile> registerFile_)
  : Op(opCode_, registerFile_)
{

}

BlockTransfer::~BlockTransfer()
{
}

bool BlockTransfer::ExecuteLoadMemory()
{
    TRACE("Executing: ",
          instructionNameStrings[ToIntegral(BlockTransfer::BlockTransferInstruction::LOAD_MEMORY)]);
    return true;
}

bool BlockTransfer::ExecuteStoreMemory()
{
    TRACE("Executing: ",
          instructionNameStrings[ToIntegral(BlockTransfer::BlockTransferInstruction::STORE_MEMORY)]);
    return true;
}

void BlockTransfer::ParseInstruction()
{
    execute = [this](){ return ExecuteLoadMemory(); };
}
