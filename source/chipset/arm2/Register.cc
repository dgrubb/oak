// File: Register.cc
// Author: dgrubb
// Date: 27/12/2022
//
// Provides an implementation of the ARM2's basic register component.

// Implementation header
#include "Register.h"

// C++ library includes
#include <algorithm> // std::fill

Register::Register(Cpsr::Mode highestAccessMode_)
  : highestAccessMode(highestAccessMode_)
{
    // N.b., access modes are zero indexed, so +1 when allocating
    // size so the basic level (Cpsr::Mode::USER == 0) results in
    // at least one register
    shadowRegisters.resize(highestAccessMode+1);
    std::fill(shadowRegisters.begin(), shadowRegisters.end(), 0);
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
