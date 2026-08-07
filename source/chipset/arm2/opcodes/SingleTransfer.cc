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

SingleTransfer::SingleTransfer(uint32_t opCode_, std::shared_ptr<RegisterFile> registerFile_, std::shared_ptr<Device::SystemBus> systemBus_)
  : Op(opCode_, registerFile_, systemBus_)
{
    ParseInstruction();
}

SingleTransfer::~SingleTransfer()
{
}

void SingleTransfer::ParseInstruction()
{
    immediate = !Field(25, 1);
    preIndexed = Field(24, 1);
    addOffset = Field(23, 4);
    byte = Field(22, 1);
    writeBack = Field(21, 1);
    load = Field(20, 1);
    Rn = Field(16, 4);
    Rd = Field(12, 4);
    offset = Field(0, 12);

    if (load) {
        execute = [this]() { return LDR(); };
    }
    else {
        execute = [this]() { return STR(); };
    }
}

bool SingleTransfer::LDR()
{
    TRACE("Executing: ", instructionNameStrings[ToIntegral(SingleTransfer::SingleTransferInstruction::LOAD_MEMORY)]);
    return true;
}

bool SingleTransfer::STR()
{
    TRACE("Executing: ", instructionNameStrings[ToIntegral(SingleTransfer::SingleTransferInstruction::STORE_MEMORY)]);
    return true;
}
