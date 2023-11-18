// File: DataProcessing.cc
// Author: dgrubb
// Date: 11/18/2023
//
// Implements a class to exeute ALU data processing functions.
// Referenced from Acorn RISC (ARM) Family Data Manual document,
// page 2-32.
//
// AND - AND comaprison.
// EOR - Exclusive OR comparison.
// SUB - Subtract operand 2 from operand 1.
// RSB - Subtract operand 1 from operand 2.
// ADD - Add operands.
// ADC - Add operands plus carry (PSR C flag).
// SBC - Subtract operand 2 from operand 1 plus carry.
// RSC - Subtract operand 1 from operand 2 plus carry.
// TST - AND, but result not written.
// TEQ - EOR, but result not written.
// CMP - SUB, but result not written.
// CMN - ADD, but result not written.
// ORR - Logical OR comparison.
// MOV - Move operand 2 (operand 1 is ignored).
// BIC - Bit clear (bitwise AND of operand 1 and NOR operand 2).
// MVN - Move NOT operand 2 (operand 1 is ignored).

// Implementation header
#include "DataProcessing.h"

// Project includes
#include "Integral.h"
#include "Log.h"

const char* DataProcessing::instructionNameStrings[] = {
    "[AND] LOGICAL AND",
    "[EOR] LOGICAL EOR",
    "[SUB] SUBTRACT OP 2 FROM OP 1",
    "[RSB] SUBTRACT OP 1 FROM OP 2",
    "[ADD] ADDITION",
    "[SBC] SUBTRACT OP 2 FROM OP 1 WITH CARRY",
    "[RSC] SUBTRACT OP 1 FROM OP 2 WITH CARRY",
    "[TST] LOGICAL AND, RESULT NOT WRITTEN",
    "[TEQ] LOGICAL EOR, RESULT NOT WRITTEN",
    "[CMP] SUBTRACTION, RESULT NOT WRITTEN",
    "[CMN] ADDITION, RESULT NOT WRITTEN",
    "[ORR] LOGICAL OR",
    "[MOV] MOVE OP 2",
    "[BIC] BIT CLEAR",
    "[MVN] MOVE NOT OP 2"
};

DataProcessing::DataProcessing(uint32_t opCode_, std::shared_ptr<RegisterFile> registerFile_)
  : Op(opCode_, registerFile_)
{

}

DataProcessing::~DataProcessing()
{
}

bool DataProcessing::DoExecute()
{
    return true;
}

void DataProcessing::ParseInstruction()
{
}
