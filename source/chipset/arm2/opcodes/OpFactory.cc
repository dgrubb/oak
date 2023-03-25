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

std::unique_ptr<Op> OpFactory::Create(uint32_t opCode, std::shared_ptr<RegisterFile> registerFile)
{
    // TODO: For the time being only one instruction type
    // has been defined so just return that by default. This
    // shall be fleshed out when the others are implemented
    // as well
    return std::make_unique<Branch>(opCode, registerFile);
}

