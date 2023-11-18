// File: OpFactory.cc
// Author: dgrubb
// Date: 03/24/2023
//
// Provides a factory class for generating instances of
// different instruction types.

// Implementation header
#include "OpFactory.h"

// Project headers
#include "BlockTransfer.h"
#include "Branch.h"

OpFactory::OpFactory() = default;
OpFactory::~OpFactory() = default;

std::optional<std::unique_ptr<Op>> OpFactory::Create(uint32_t opCode, std::shared_ptr<RegisterFile> registerFile)
{
    if (IsBranch(opCode)) return std::make_unique<Branch>(opCode, registerFile);
    if (IsDataProcessing(opCode)) return std::make_unique<Branch>(opCode, registerFile);
    if (IsMultiply(opCode)) return std::make_unique<Branch>(opCode, registerFile);
    if (IsSingleDataTransfer(opCode)) return std::make_unique<Branch>(opCode, registerFile);
    if (IsBlockDataTransfer(opCode)) return std::make_unique<BlockTransfer>(opCode, registerFile);

    return std::nullopt;
}

bool OpFactory::IsBranch(uint32_t opCode)
{
    // Identified by bits 25 through 27 having a value
    // of 101. ARM datasheet, page 15
    opCode >>= 25;
    return (opCode & 0x5);
}

bool OpFactory::IsDataProcessing(uint32_t opCode)
{
    // Identified by bits 26 and 27 being 0.
    // ARM datasheet, page 17
    opCode >>= 26;
    return (opCode & 0x3) == 0;
}

bool OpFactory::IsMultiply(uint32_t opCode)
{
    // Identified by bits 22 through 27 being 0.
    // ARM datasheet, page 23
    opCode >>= 22;
    return (opCode & 0x3F) == 0;
}

bool OpFactory::IsSingleDataTransfer(uint32_t opCode)
{
    // Identified by bits 26 being 1 and 27 being 0.
    // ARM datasheet, page 25
    opCode >>= 26;
    return (opCode & 0x3) == 0x1;
}

bool OpFactory::IsBlockDataTransfer(uint32_t opCode)
{
    // Identified by bits 25 through 27 being 100.
    // ARM datasheet, page 29
    opCode >>= 25;
    return (opCode & 0x7) == 0x4;
}
