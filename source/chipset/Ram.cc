// File: Ram.cc
// Author: dgrubb
// Date: 22/12/2022
//
// Provides a class for describing the A3000's
// RAM interface

// Implementation header
#include "Ram.h"

// Project includes
#include "Log.h"

Ram::Ram(std::shared_ptr<Device::SystemBus> systemBus_)
  : Device(systemBus_)
{
    DEBUG("RAM initialised");
}

void Ram::DoTick()
{
}

std::optional<uint8_t> Ram::Read(uint32_t address)
{
    try
    {
        return ram.at(address);
    }
    catch(std::out_of_range&)
    {
        ERROR("Failed to read RAM, address out of range: ", address);
    }
    return std::nullopt;
}

bool Ram::Write(uint32_t address, uint8_t byte)
{
    try
    {
        ram.at(address) = byte;
        return true;
    }
    catch(std::out_of_range&)
    {
        ERROR("Failed to write RAM, address out of range: ", address);
    }
    return false;
}

Ram::~Ram()
{
    DEBUG("RAM uninitialised");
}
