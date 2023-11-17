// File: Ioc.h
// Author: dgrubb
// Date: 22/12/2022
//
// Provides a class for describing the A3000's
// Input-output controller

#ifndef IOC_H
#define IOC_H

// C++ library includes
#include <cstdint> // uint32_t
#include <memory>  // std::shared_ptr

// Project includes
#include "Device.h"

class Ioc final: public Device
{
public:

    Ioc(std::shared_ptr<Device::SystemBus> systemBus_);
    ~Ioc();

    Ioc(const Ioc &orig)          = delete;
    Ioc(Ioc &&orig)               = delete;
    Ioc &operator=(const Ioc &)   = delete;
    Ioc &operator=(Ioc &&)        = delete;

private:

    void DoTick() override;
};

#endif // IOC_H
