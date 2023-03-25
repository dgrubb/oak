// File: OpFactory.h
// Author: dgrubb
// Date: 03/24/2023
//
// Provides a factory class for generating instances of
// different instruction types.

#ifndef OPFACTORY_H
#define OPFACTORY_H

// C++ header includes
#include <cstdint> // uint32_t
#include <memory>  // std::shared_ptr, std::unique_ptr

// Project includes
#include "Op.h"
#include "RegisterFile.h"

class OpFactory final
{
public:

    OpFactory();
    ~OpFactory();

    static std::unique_ptr<Op> Create(uint32_t opCode, std::shared_ptr<RegisterFile> registerFile);
};

#endif // OPFACTORY_H
