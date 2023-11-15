// File: A3000.cc
// Author: dgrubb
// Date: 22/12/2022
//
// Provides a class for describing the system-level
// design of an A3000.

// Implementation header
#include "A3000.h"

// Project includes
#include "Log.h"

A3000::A3000()
  : systemBus{std::make_shared<Device::SystemBus>()},
    arm2{systemBus},
    ioc{systemBus},
    memc{systemBus},
    ram{systemBus},
    rom{systemBus}
{
    DEBUG("A3000 initialised");
}

bool A3000::LoadROM(std::string& romFilePath)
{
    return rom.Load(romFilePath);
}

void A3000::PrintState()
{
    arm2.PrintState();
}

void A3000::Reset()
{
    memc.Reset();
    arm2.Reset();
}

void A3000::Tick()
{
    TRACE("Stepping A3000");
    try
    {
        arm2.Tick();
        memc.Tick();
        rom.Tick();
    }
    catch(std::exception& e)
    {
        arm2.PrintState();
        throw std::runtime_error(e.what());
    }
}

A3000::~A3000()
{
    DEBUG("A3000 uninitialised");
}

