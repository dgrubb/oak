// File: SingleTransfer.h
// Author: dgrubb
// Date: 11/18/2023
//
// Implements a class to exeute a single data transfer instruction.
//
// LDR - Stores a memory location content into a register.
//
// STR - Loads a register's content into memory.

#ifndef SINGLETRANSFER_H
#define SINGLETRANSFER_H

// C++ header includes
#include <cstdint> // uint32_t
#include <memory>  // std::shared_ptr

// Project includes
#include "Op.h"

class SingleTransfer final: public Op
{
public:

    enum class SingleTransferInstruction : int
    {
        LOAD_MEMORY = 0,
        STORE_MEMORY
    };

    SingleTransfer(uint32_t opCode_, std::shared_ptr<RegisterFile> registerFile_);
    ~SingleTransfer();

private:

    static const char* instructionNameStrings[];

    bool ExecuteLoadMemory();
    bool ExecuteStoreMemory();
    void ParseInstruction();
};

#endif // SINGLETRANSFER_H
