// File: Device.cc
// Author: dgrubb
// Date: 22/12/2022
//
// Provides a base class describing common properties of A3000's
// chipset devices which can be derived by specific chips.

// Implementation header
#include "Device.h"

// Project includes
#include "Log.h"

Device::Device(std::shared_ptr<Device::SystemBus> systemBus_)
  : systemBus{systemBus_}
{
}

uint32_t Device::GetAddressBus()
{
    return (Device::AddressBusMask & systemBus.get()->addressBus);
}

uint32_t Device::GetDataBus()
{
    return systemBus->dataBus;
}

Device::SystemBus::RW Device::GetReadWrite()
{
    return systemBus->rw;
}

void Device::SetAddressBus(uint32_t addr)
{
    systemBus->addressBus = (Device::AddressBusMask & addr);
}

void Device::SetDataBus(uint32_t data)
{
    systemBus->dataBus = data;
}

void Device::SetReadWrite(SystemBus::RW direction)
{
    systemBus->rw = direction;
}

void Device::Tick()
{
    DoTick();
}

Device::~Device()
{
}
