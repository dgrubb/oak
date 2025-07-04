// File: Cpsr.cc
// Author: dgrubb
// Date: 27/12/2022
//
// Provides an implementation of the ARM2's special status and program
// counter register (CPSR).

// Implementation header
#include "Cpsr.h"

// C++ header includes
#include <iomanip> // std::setfill, std::setw

// Project includes
#include "Log.h"

const char* Cpsr::modeNameStrings[] = {
    "USER",
    "FIQ",
    "IRQ",
    "SVC"
};
const char* Cpsr::statusFlagsNameStrings[] = {
    "FIQ_DISABLE",
    "IRQ_DISABLE",
    "OVERFLOW",
    "CARRY",
    "ZERO",
    "NEGATIVE"
};

Cpsr::Cpsr()
{
    DEBUG("Initialised Cpsr");
}

Cpsr::Mode Cpsr::GetMode()
{
    Mode mode = static_cast<Mode>(value & ModeMask);
    TRACE("Fetched current Mode: ", modeNameStrings[ToIntegral(mode)]);
    return mode;
}

uint32_t Cpsr::GetProgramCounter()
{
    std::stringstream valHex;
    uint32_t counter{0};

    counter = ((value & ProgramCounterMask) >> 2);

    valHex << std::hex << counter;
    TRACE("Fetched Program Counter value: ", counter);
    return counter;
}

uint32_t Cpsr::IncrementProgramCounter()
{
    TRACE("Incrementing program counter");
    SetProgramCounter(GetProgramCounter()+1);
    return GetProgramCounter();
}

bool Cpsr::GetStatusFlag(StatusFlag flag)
{
    bool set = value & statusFlagsMasks[ToIntegral(flag)];
    TRACE("Fetched status flag [ ", statusFlagsNameStrings[ToIntegral(flag)], " ], set: ", set);
    return set;
}

void Cpsr::PrintState()
{
    std::stringstream pcHex;
    pcHex << std::hex << std::setw(8) << std::setfill('0') << ((value & ProgramCounterMask) >> 2);
    uint32_t mode = value & ModeMask;

    TRACE(" | N | Z | C | V | I | F |     PC     | MODE");
    TRACE(" | ", bool{0 != (value & statusFlagsMasks[ToIntegral(StatusFlag::NEGATIVE)])},
          " | ", bool{0 != (value & statusFlagsMasks[ToIntegral(StatusFlag::ZERO)])},
          " | ", bool{0 != (value & statusFlagsMasks[ToIntegral(StatusFlag::CARRY)])},
          " | ", bool{0 != (value & statusFlagsMasks[ToIntegral(StatusFlag::OVERFLOW)])},
          " | ", bool{0 != (value & statusFlagsMasks[ToIntegral(StatusFlag::IRQ_DISABLE)])},
          " | ", bool{0 != (value & statusFlagsMasks[ToIntegral(StatusFlag::FIQ_DISABLE)])},
          " | 0x", pcHex.str(),
          " | ", modeNameStrings[mode]);
}

void Cpsr::SetMode(Mode mode)
{
    value &= ~ModeMask;
    value |= ToIntegral(mode);
    TRACE("Set current Mode: ", modeNameStrings[ToIntegral(mode)]);
}

void Cpsr::SetProgramCounter(uint32_t counter)
{
    if (counter > 0x00FFFFFF)
    {
        // PC is only 24-bits wide
        ERROR("Attempt to set Program Counter higher than 0x00FFFFFF");
        return;
    }
    std::stringstream valHex;

    value &= ~ProgramCounterMask;
    value |= (counter << 2);

    valHex << std::hex << counter;
    TRACE("Set Program Counter value: ", counter);
}

void Cpsr::SetStatusFlag(StatusFlag flag, bool set)
{
    if (set)
    {
        value |= statusFlagsMasks[ToIntegral(flag)];
    }
    else
    {
        value &= ~statusFlagsMasks[ToIntegral(flag)];
    }
    TRACE("Set status flag [ ", statusFlagsNameStrings[ToIntegral(flag)], " ], set: ", set);
}

Cpsr::~Cpsr()
{
    DEBUG("Unintialised Cpsr");
}

