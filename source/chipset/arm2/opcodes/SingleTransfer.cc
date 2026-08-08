// File: SingleTransfer.cc
// Author: dgrubb
// Date: 11/18/2023
//
// Implements a class to exeute a single data transfer instruction.
//
// LDR - Stores a memory location content into a register.
//
// STR - Loads a register's content into memory.

// Implementation header
#include "SingleTransfer.h"

// C++ library includes
#include <string>   // to_string

// Project includes
#include "Integral.h"
#include "Log.h"

const char* SingleTransfer::instructionNameStrings[] = {
    "[LDR] LOAD MEMORY",
    "[STR] STORE MEMORY"
};

SingleTransfer::SingleTransfer(uint32_t opCode_, std::shared_ptr<RegisterFile> registerFile_, std::shared_ptr<Device::SystemBus> systemBus_)
  : Op(opCode_, registerFile_, systemBus_)
{
    ParseInstruction();
}

SingleTransfer::~SingleTransfer()
{
}

uint32_t SingleTransfer::CalculateImmediateAddress()
{
    uint32_t calculatedAddress = registerFile->GetRegisterValue(Rn);
    if (addOffset) {
        calculatedAddress += offset;
    } else {
        calculatedAddress -= offset;
    }
    return calculatedAddress;
}

void SingleTransfer::ParseInstruction()
{
    // I - Immediate.
    // When 0 the address accessed is formed by adding, or subtracting, depending
    // on the value of U, the address stored in the register specifed in the base
    // register (Rn) with the offset value. E.g.,
    // Effective address = Rn +/- offset
    // When 1 the address accessed is formed by adding, or subtracing, depending
    // on the valye of U, the address stored in a register specified in the base
    // register (Rn) with the address stored in the offset with a possible shift
    // applied. Eg.,
    // Effective address = Rn +/- (Rm shifted by shift amount)
    immediate = !Field(25, 1);

    // P - Pre/Post indexed.
    //
    preIndexed = Field(24, 1);

    // U - Up/Down
    //
    addOffset = Field(23, 4);

    // B - Byte/Word
    byte = Field(22, 1);

    // W - Write-back
    writeBack = Field(21, 1);

    // L - Load/Store
    load = Field(20, 1);

    // Base register
    Rn = Field(16, 4);

    // Source/Destination register
    Rd = Field(12, 4);

    // Offset
    offset = Field(0, 12);

    if (load) {
        execute = [this]() { return LDR(); };
    }
    else {
        execute = [this]() { return STR(); };
    }
}

bool SingleTransfer::LDR()
{
    TRACE("Executing: ", instructionNameStrings[ToIntegral(SingleTransfer::SingleTransferInstruction::LOAD_MEMORY)]);

    static uint32_t value{0};

    systemBus->memoryAccess = true;

    switch (cycleCount)
    {
        case 0:
            // Calculate read address and apply to buses
            systemBus->addressBus = CalculateImmediateAddress();
            systemBus->byteWord = (byte ? Device::SystemBus::ByteWord::BYTE : Device::SystemBus::ByteWord::WORD);
            return false;
        case 1:
            value = systemBus->dataBus;
            return false;
        case 2:
            // Write to destination register
            registerFile->SetRegisterValue(Rd, value);
            systemBus->memoryAccess = false;
            value = 0;
            return true;
        default:
            std::string msg{"Invalid cycle count [ "};
            msg += std::to_string(cycleCount);
            msg += " ] for instruction: ";
            msg += instructionNameStrings[ToIntegral(SingleTransfer::SingleTransferInstruction::LOAD_MEMORY)];
            ERROR(msg);
            throw std::runtime_error(msg);
    }
    return true;
}

bool SingleTransfer::STR()
{
    TRACE("Executing: ", instructionNameStrings[ToIntegral(SingleTransfer::SingleTransferInstruction::STORE_MEMORY)]);
    return true;
}
