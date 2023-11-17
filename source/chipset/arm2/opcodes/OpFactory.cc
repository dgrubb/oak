// File: OpFactory.cc
// Author: dgrubb
// Date: 03/24/2023
//
// Provides a factory class for generating instances of
// different instruction types.

// Implementation header
#include "OpFactory.h"

// Project headers
#include "Branch.h"

OpFactory::OpFactory() = default;
OpFactory::~OpFactory() = default;

std::optional<std::unique_ptr<Op>> OpFactory::Create(uint32_t opCode, std::shared_ptr<RegisterFile> registerFile)
{
    if (IsBranch(opCode)) return std::make_unique<Branch>(opCode, registerFile);
    if (IsDataProcessing(opCode)) return std::make_unique<Branch>(opCode, registerFile);
    if (IsSingleDataTransfer(opCode)) return std::make_unique<Branch>(opCode, registerFile);
    if (IsMultipleDataTransfer(opCode)) return std::make_unique<Branch>(opCode, registerFile);

    return std::nullopt;
}

bool OpFactory::IsBranch(uint32_t opCode)
{
    return false;
}

bool OpFactory::IsDataProcessing(uint32_t opCode)
{
    return false;
}

bool OpFactory::IsSingleDataTransfer(uint32_t opCode)
{
    return false;
}

bool OpFactory::IsMultipleDataTransfer(uint32_t opCode)
{
    return false;
}
