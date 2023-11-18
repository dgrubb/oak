// File: Multiply.cc
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

// Implementation header
#include "Multiply.h"

// Project includes
#include "Integral.h"
#include "Log.h"

const char* Multiply::instructionNameStrings[] = {
    "[MUL] MULTIPLY",
    "[MLA] MULTIPLY ACCUMULATE"
};

Multiply::Multiply(uint32_t opCode_, std::shared_ptr<RegisterFile> registerFile_)
  : Op(opCode_, registerFile_)
{

}

Multiply::~Multiply()
{
}

bool Multiply::DoExecute()
{
    return true;
}

void Multiply::ParseInstruction()
{
}
