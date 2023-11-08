// File: RegisterFile.cc
// Author: dgrubb
// Date: 22/12/2022
//
// Provides an implementation of the ARM2's register file with access controlled
// by processor mode (e.g., Supervisor, User, IRQ, etc).

// Implementation header
#include "RegisterFile.h"

// C++ library includes
#include <iomanip> // std::hex
#include <sstream> // std::stringstream

// Project includes
#include "Log.h"

const char* RegisterFile::registerNameStrings[] = {
    "R0",
    "R1",
    "R2",
    "R3",
    "R4",
    "R5",
    "R6",
    "R7",
    "R8",
    "R9",
    "R10",
    "R11",
    "R12",
    "R13",
    "R14",
    "R15/CPSR"
};

RegisterFile::RegisterFile()
{
    Init();
    DEBUG("RegisterFile initialised");
}

void RegisterFile::Init()
{
    registers.clear();

    // Index in vector corresponds to the
    // register's numeric designation
    registers.emplace_back(Cpsr::Mode::USER); // R0
    registers.emplace_back(Cpsr::Mode::USER); // R1
    registers.emplace_back(Cpsr::Mode::USER); // R2
    registers.emplace_back(Cpsr::Mode::USER); // R3
    registers.emplace_back(Cpsr::Mode::USER); // R4
    registers.emplace_back(Cpsr::Mode::USER); // R5
    registers.emplace_back(Cpsr::Mode::USER); // R6
    registers.emplace_back(Cpsr::Mode::USER); // R7
    registers.emplace_back(Cpsr::Mode::FIQ);  // R8
    registers.emplace_back(Cpsr::Mode::FIQ);  // R9
    registers.emplace_back(Cpsr::Mode::FIQ);  // R10
    registers.emplace_back(Cpsr::Mode::FIQ);  // R11
    registers.emplace_back(Cpsr::Mode::FIQ);  // R12
    registers.emplace_back(Cpsr::Mode::SVC);  // R13
    registers.emplace_back(Cpsr::Mode::SVC);  // R14

    cpsr = Cpsr();
}

uint32_t RegisterFile::GetCPSR()
{
    return cpsr.Get();
}

Cpsr::Mode RegisterFile::GetMode()
{
    return cpsr.GetMode();
}

uint32_t RegisterFile::GetProgramCounter()
{
    return cpsr.GetProgramCounter();
}

uint32_t RegisterFile::GetRegisterValue(RegisterRef reg)
{
    std::stringstream valHex;
    uint32_t value{0};
    size_t regIdx = static_cast<size_t>(reg);
    Cpsr::Mode mode = GetMode();

    if (RegisterRef::R15 == reg)
    {
        // R15 is the CPSR which can accessed by any mode
        // and has no shadow registers
        value = cpsr.Get();
    }
    else
    {
        // Fetch the current mode for debug printing and for determining
        // whether a shadow register should be accessed
        try
        {
            value = registers.at(regIdx).Get(mode);
        }
        catch (std::out_of_range const& e)
        {
            std::string msg{"Failed to access register: "};
            msg += registerNameStrings[regIdx];
            CRITICAL(msg);
            throw std::runtime_error(msg);
        }
    }

    valHex << std::hex << value;
    TRACE("Fetched 0x", valHex.str(), " from [ ", registerNameStrings[regIdx], " ], mode: ", Cpsr::GetModeString(mode));
    return value;
}

bool RegisterFile::GetStatusFlag(Cpsr::StatusFlag flag)
{
    return cpsr.GetStatusFlag(flag);
}

void RegisterFile::PrintCPSR()
{
    cpsr.PrintState();
}

void RegisterFile::SetCPSR(uint32_t value)
{
    cpsr.Set(value);
}

void RegisterFile::SetMode(Cpsr::Mode mode)
{
    cpsr.SetMode(mode);
}

void RegisterFile::SetProgramCounter(uint32_t counter)
{
    cpsr.SetProgramCounter(counter);
}

void RegisterFile::SetRegisterValue(RegisterRef reg, uint32_t value)
{
    std::stringstream valHex;
    size_t regIdx = static_cast<size_t>(reg);
    Cpsr::Mode mode = GetMode();

    if (RegisterRef::R15 == reg)
    {
        // R15 is the CPSR which can accessed by any mode
        // and has no shadow registers
        cpsr.Set(value);
    }
    else
    {
        // Fetch the current mode for debug printing and for determining
        // whether a shadow register should be accessed
        try
        {
            registers.at(regIdx).Set(mode, value);
        }
        catch (std::out_of_range const& e)
        {
            std::string msg{"Failed to access register: "};
            msg += registerNameStrings[regIdx];
            CRITICAL(msg);
            throw std::runtime_error(msg);
        }
    }

    valHex << std::hex << value;
    TRACE("Set register [ ", registerNameStrings[regIdx], " ] to 0x", valHex.str(), ", mode: ", Cpsr::GetModeString(mode));
}

void RegisterFile::SetStatusFlag(Cpsr::StatusFlag flag, bool set)
{
    cpsr.SetStatusFlag(flag, set);
}

RegisterFile::~RegisterFile()
{
    DEBUG("RegisterFile uninitialised");
}
