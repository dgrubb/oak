// File: OpFactory.h
// Author: dgrubb
// Date: 03/24/2023
//
// Provides a factory class for generating instances of
// different instruction types.

#ifndef OPFACTORY_H
#define OPFACTORY_H

// C++ header includes
#include <cstdint>  // uint32_t
#include <memory>   // std::shared_ptr, std::unique_ptr
#include <optional> // std::optional

// Project includes
#include "Op.h"
#include "RegisterFile.h"

class OpFactory final
{
public:

    OpFactory();
    ~OpFactory();

    static std::optional<std::unique_ptr<Op>> Create(uint32_t opCode, std::shared_ptr<RegisterFile> registerFile);

private:

    static bool IsBranch(uint32_t opCode);
    static bool IsDataProcessing(uint32_t opCode);
    static bool IsMultiply(uint32_t opCode);
    static bool IsSingleDataTransfer(uint32_t opCode);
    static bool IsBlockDataTransfer(uint32_t opCode);
};

#endif // OPFACTORY_H
