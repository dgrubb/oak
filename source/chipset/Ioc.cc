// File: IOC.cc
// Author: dgrubb
// Date: 22/12/2022
//
// Provides a class for describing the A3000's
// Input-output controller

// Implementation header
#include "Ioc.h"

// Project includes
#include "Log.h"

Ioc::Ioc(std::shared_ptr<Device::SystemBus> systemBus_)
  : Device(systemBus_)
{
    DEBUG("IOC initialised");
}

void Ioc::DoTick()
{
}

Ioc::~Ioc()
{
    DEBUG("IOC uninitialised");
}
