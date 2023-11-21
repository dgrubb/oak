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

bool DataProcessing::DoExecute()
{
    dataExecution();
    return true;
}

void DataProcessing::ParseInstruction()
{
    auto instruction = static_cast<DataProcessingInstruction>((opCode & instructionMask) >> 21);
    switch(instruction)
    {
        case DataProcessingInstruction::AND: dataExecution = [this]() { AND(); }; return;
        case DataProcessingInstruction::EOR: dataExecution = [this]() { EOR(); }; return;
        case DataProcessingInstruction::SUB: dataExecution = [this]() { SUB(); }; return;
        case DataProcessingInstruction::RSB: dataExecution = [this]() { RSB(); }; return;
        case DataProcessingInstruction::ADD: dataExecution = [this]() { ADD(); }; return;
        case DataProcessingInstruction::ADC: dataExecution = [this]() { ADC(); }; return;
        case DataProcessingInstruction::SBC: dataExecution = [this]() { SBC(); }; return;
        case DataProcessingInstruction::RSC: dataExecution = [this]() { RSC(); }; return;
        case DataProcessingInstruction::TST: dataExecution = [this]() { TST(); }; return;
        case DataProcessingInstruction::TEQ: dataExecution = [this]() { TEQ(); }; return;
        case DataProcessingInstruction::CMP: dataExecution = [this]() { CMP(); }; return;
        case DataProcessingInstruction::CMN: dataExecution = [this]() { CMN(); }; return;
        case DataProcessingInstruction::ORR: dataExecution = [this]() { ORR(); }; return;
        case DataProcessingInstruction::MOV: dataExecution = [this]() { MOV(); }; return;
        case DataProcessingInstruction::BIC: dataExecution = [this]() { BIC(); }; return;
        case DataProcessingInstruction::MVN: dataExecution = [this]() { MVN(); }; return;
        default:
            throw std::runtime_error("Unrecognised instruction: " + std::to_string(static_cast<int>(instruction)));
    }
}

void DataProcessing::AND()
{
    TRACE("Executing: ", instructionNameStrings[ToIntegral(DataProcessing::DataProcessingInstruction::AND)]);
}

void DataProcessing::EOR()
{
    TRACE("Executing: ", instructionNameStrings[ToIntegral(DataProcessing::DataProcessingInstruction::EOR)]);
}

void DataProcessing::SUB()
{
    TRACE("Executing: ", instructionNameStrings[ToIntegral(DataProcessing::DataProcessingInstruction::SUB)]);
}

void DataProcessing::RSB()
{
    TRACE("Executing: ", instructionNameStrings[ToIntegral(DataProcessing::DataProcessingInstruction::RSB)]);
}

void DataProcessing::ADD()
{
    TRACE("Executing: ", instructionNameStrings[ToIntegral(DataProcessing::DataProcessingInstruction::ADD)]);
}

void DataProcessing::ADC()
{
    TRACE("Executing: ", instructionNameStrings[ToIntegral(DataProcessing::DataProcessingInstruction::ADC)]);
}

void DataProcessing::SBC()
{
    TRACE("Executing: ", instructionNameStrings[ToIntegral(DataProcessing::DataProcessingInstruction::SBC)]);
}

void DataProcessing::RSC()
{
    TRACE("Executing: ", instructionNameStrings[ToIntegral(DataProcessing::DataProcessingInstruction::RSC)]);
}

void DataProcessing::TST()
{
    TRACE("Executing: ", instructionNameStrings[ToIntegral(DataProcessing::DataProcessingInstruction::TST)]);
}

void DataProcessing::TEQ()
{
    TRACE("Executing: ", instructionNameStrings[ToIntegral(DataProcessing::DataProcessingInstruction::TEQ)]);
}

void DataProcessing::CMP()
{
    TRACE("Executing: ", instructionNameStrings[ToIntegral(DataProcessing::DataProcessingInstruction::CMP)]);
}

void DataProcessing::CMN()
{
    TRACE("Executing: ", instructionNameStrings[ToIntegral(DataProcessing::DataProcessingInstruction::CMN)]);
}

void DataProcessing::ORR()
{
    TRACE("Executing: ", instructionNameStrings[ToIntegral(DataProcessing::DataProcessingInstruction::ORR)]);
}

void DataProcessing::MOV()
{
    TRACE("Executing: ", instructionNameStrings[ToIntegral(DataProcessing::DataProcessingInstruction::MOV)]);
}

void DataProcessing::BIC()
{
    TRACE("Executing: ", instructionNameStrings[ToIntegral(DataProcessing::DataProcessingInstruction::BIC)]);
}

void DataProcessing::MVN()
{
    TRACE("Executing: ", instructionNameStrings[ToIntegral(DataProcessing::DataProcessingInstruction::MVN)]);
}
