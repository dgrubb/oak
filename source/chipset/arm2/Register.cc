// File: Register.cc
// Author: dgrubb
// Date: 27/12/2022
//
// Provides an implementation of the ARM2's basic register component.

// Implementation header
#include "Register.h"

Register::Register(Cpsr::Mode highestAccessMode_)
  : highestAccessMode(highestAccessMode_)
{
    shadowRegisters.resize(highestAccessMode);
}

uint32_t Register::Get(Cpsr::Mode mode)
{
    if (mode > highestAccessMode)
    {
        return shadowRegisters[Cpsr::Mode::USER];
    }
    return shadowRegisters[mode];
}

void Register::Set(Cpsr::Mode mode, uint32_t value)
{
    if (mode > highestAccessMode)
    {
        mode = Cpsr::Mode::USER;
    }
    shadowRegisters[mode] = value;
}

Register::~Register()
{
}
