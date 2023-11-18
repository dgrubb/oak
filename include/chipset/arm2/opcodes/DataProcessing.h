// File: DataProcessing.h
// Author: dgrubb
// Date: 11/18/2023
//
// Implements a class to execute ALU data processing functions.
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

#ifndef DATAPROCESSING_H
#define DATAPROCESSING_H

// C++ header includes
#include <cstdint> // uint32_t
#include <memory>  // std::shared_ptr

// Project includes
#include "Op.h"

class DataProcessing final: public Op
{
public:

    enum class DataProcessingInstruction : int
    {
        AND = 0b0000,
        EOR = 0b0001,
        SUB = 0b0010,
        RSB = 0b0011,
        ADD = 0b0100,
        ADC = 0b0101,
        SBC = 0b0110,
        RSC = 0b0111,
        TST = 0b1000,
        TEQ = 0b1001,
        CMP = 0b1010,
        CMN = 0b1011,
        ORR = 0b1100,
        MOV = 0b1101,
        BIC = 0b1110,
        MVN = 0b1111
    };

    DataProcessing(uint32_t opCode_, std::shared_ptr<RegisterFile> registerFile_);
    ~DataProcessing();

private:

    static const char* instructionNameStrings[];

    void ParseInstruction();
    bool DoExecute() override;
};

#endif // DATAPROCESSING_H
