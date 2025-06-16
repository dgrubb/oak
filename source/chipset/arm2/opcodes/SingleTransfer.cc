// File: SingleTransfer.cc
// Author: dgrubb
// Date: 11/18/2023
//
// Implements a class to exeute a single data transfer instruction.
//
// LDR - Stores a memory location content into a register.
//
// STR - Loads a register's content into memory.

// Implementation header
#include "SingleTransfer.h"

// Project includes
#include "Integral.h"
#include "Log.h"

const char* SingleTransfer::instructionNameStrings[] = {
    "[LDR] LOAD MEMORY",
    "[STR] STORE MEMORY"
};

SingleTransfer::SingleTransfer(uint32_t opCode_, std::shared_ptr<RegisterFile> registerFile_)
  : Op(opCode_, registerFile_)
{

}

SingleTransfer::~SingleTransfer()
{
}

bool SingleTransfer::ExecuteLoadMemory()
{
    TRACE("Executing: ",
          instructionNameStrings[ToIntegral(SingleTransfer::SingleTransferInstruction::LOAD_MEMORY)]);
    return true;
}

bool SingleTransfer::ExecuteStoreMemory()
{
    TRACE("Executing: ",
          instructionNameStrings[ToIntegral(SingleTransfer::SingleTransferInstruction::STORE_MEMORY)]);
    return true;
}

void SingleTransfer::ParseInstruction()
{
}
