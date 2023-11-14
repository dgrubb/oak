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

void Device::Tick()
{
    DoTick();
}

Device::~Device()
{
}
