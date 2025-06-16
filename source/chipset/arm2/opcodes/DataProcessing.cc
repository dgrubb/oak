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
    ParseInstruction();
}

DataProcessing::~DataProcessing()
{
}

uint32_t DataProcessing::GetOperand2()
{
    // The second operand may be either the contents of another
    // register or an immediate value, depending on whether
    // Immediate Value (bit 25) is set.
    auto immediate = ((opCode >> 24) & 0b1);
    if (immediate)
    {
        TRACE("Instruction uses an immediate value");
        // "The immediate value is zero extended to 32 bits, and then
        // subject to a rotate right by twice the value in the rotate
        // field. This enabled many common constants to be generated,
        // such as powers of 2. Another example is the the 8 bit constant
        // may be aligned with the PSR flags"
        // - ARM Datasheet, page 21
        //auto immediateValue = (opCode & 0xFF) << 26;
        // TODO: Complete this section with rotations applied.
    }
    else
    {
        TRACE("Instruction uses a register value");
    }
    return 0;
}

void DataProcessing::ParseInstruction()
{
    auto instruction = static_cast<DataProcessingInstruction>((opCode & instructionMask) >> 21);
    switch(instruction)
    {
        case DataProcessingInstruction::AND: execute = [this]() { return AND(); }; return;
        case DataProcessingInstruction::EOR: execute = [this]() { return EOR(); }; return;
        case DataProcessingInstruction::SUB: execute = [this]() { return SUB(); }; return;
        case DataProcessingInstruction::RSB: execute = [this]() { return RSB(); }; return;
        case DataProcessingInstruction::ADD: execute = [this]() { return ADD(); }; return;
        case DataProcessingInstruction::ADC: execute = [this]() { return ADC(); }; return;
        case DataProcessingInstruction::SBC: execute = [this]() { return SBC(); }; return;
        case DataProcessingInstruction::RSC: execute = [this]() { return RSC(); }; return;
        case DataProcessingInstruction::TST: execute = [this]() { return TST(); }; return;
        case DataProcessingInstruction::TEQ: execute = [this]() { return TEQ(); }; return;
        case DataProcessingInstruction::CMP: execute = [this]() { return CMP(); }; return;
        case DataProcessingInstruction::CMN: execute = [this]() { return CMN(); }; return;
        case DataProcessingInstruction::ORR: execute = [this]() { return ORR(); }; return;
        case DataProcessingInstruction::MOV: execute = [this]() { return MOV(); }; return;
        case DataProcessingInstruction::BIC: execute = [this]() { return BIC(); }; return;
        case DataProcessingInstruction::MVN: execute = [this]() { return MVN(); }; return;
        default:
            throw std::runtime_error("Unrecognised instruction: " + std::to_string(static_cast<int>(instruction)));
    }
}

bool DataProcessing::AND()
{
    TRACE("Executing: ", instructionNameStrings[ToIntegral(DataProcessing::DataProcessingInstruction::AND)]);
    return true;
}

bool DataProcessing::EOR()
{
    TRACE("Executing: ", instructionNameStrings[ToIntegral(DataProcessing::DataProcessingInstruction::EOR)]);
    return true;
}

bool DataProcessing::SUB()
{
    TRACE("Executing: ", instructionNameStrings[ToIntegral(DataProcessing::DataProcessingInstruction::SUB)]);
    return true;
}

bool DataProcessing::RSB()
{
    TRACE("Executing: ", instructionNameStrings[ToIntegral(DataProcessing::DataProcessingInstruction::RSB)]);
    return true;
}

bool DataProcessing::ADD()
{
    TRACE("Executing: ", instructionNameStrings[ToIntegral(DataProcessing::DataProcessingInstruction::ADD)]);
    return true;
    return true;
}

bool DataProcessing::ADC()
{
    TRACE("Executing: ", instructionNameStrings[ToIntegral(DataProcessing::DataProcessingInstruction::ADC)]);
    return true;
}

bool DataProcessing::SBC()
{
    TRACE("Executing: ", instructionNameStrings[ToIntegral(DataProcessing::DataProcessingInstruction::SBC)]);
    return true;
}

bool DataProcessing::RSC()
{
    TRACE("Executing: ", instructionNameStrings[ToIntegral(DataProcessing::DataProcessingInstruction::RSC)]);
    return true;
}

bool DataProcessing::TST()
{
    TRACE("Executing: ", instructionNameStrings[ToIntegral(DataProcessing::DataProcessingInstruction::TST)]);
    return true;
}

bool DataProcessing::TEQ()
{
    TRACE("Executing: ", instructionNameStrings[ToIntegral(DataProcessing::DataProcessingInstruction::TEQ)]);
    return true;
}

bool DataProcessing::CMP()
{
    TRACE("Executing: ", instructionNameStrings[ToIntegral(DataProcessing::DataProcessingInstruction::CMP)]);
    return true;
}

bool DataProcessing::CMN()
{
    TRACE("Executing: ", instructionNameStrings[ToIntegral(DataProcessing::DataProcessingInstruction::CMN)]);
    return true;
}

bool DataProcessing::ORR()
{
    TRACE("Executing: ", instructionNameStrings[ToIntegral(DataProcessing::DataProcessingInstruction::ORR)]);
    return true;
}

bool DataProcessing::MOV()
{
    TRACE("Executing: ", instructionNameStrings[ToIntegral(DataProcessing::DataProcessingInstruction::MOV)]);
    return true;
}

bool DataProcessing::BIC()
{
    TRACE("Executing: ", instructionNameStrings[ToIntegral(DataProcessing::DataProcessingInstruction::BIC)]);
    return true;
}

bool DataProcessing::MVN()
{
    TRACE("Executing: ", instructionNameStrings[ToIntegral(DataProcessing::DataProcessingInstruction::MVN)]);
    return true;
}
