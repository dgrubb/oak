// File: Multiply.h
// Author: dgrubb
// Date: 11/18/2023
//
// Implements a class to exeute a Multiply or Multiply-Accumulate
// instruction.
//
// MUL - Multiplication between two operands of the form
//       Rd = Rm*Rs.
//
// MLA - Multiplication between two operands followed by
//       an addition with a third operand of the form:
//       Rd = Rm*Rs+Rn

#ifndef MULTIPLY_H
#define MULTIPLY_H

// C++ header includes
#include <cstdint> // uint32_t
#include <memory>  // std::shared_ptr

// Project includes
#include "Op.h"

class Multiply final: public Op
{
public:

    enum class MultiplyInstruction : int
    {
        MULTIPLY = 0,
        MULTIPLY_ACCUMULATE
    };

    Multiply(uint32_t opCode_, std::shared_ptr<RegisterFile> registerFile_);
    ~Multiply();

private:

    static const char* instructionNameStrings[];

    bool ExecuteMultiply();
    bool ExecuteMultiplyAccumulate();
    void ParseInstruction();
};

#endif // MULTIPLY_H
