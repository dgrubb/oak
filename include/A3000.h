// File: A3000.h
// Author: dgrubb
// Date: 22/12/2022
//
// Provides a class for describing the system-level
// design of an A3000.

#ifndef A3000_H
#define A3000_H

// C++ library includes
#include <cstdint> // uint32_t
#include <memory>  // std::shared_ptr

// Project includes
#include "Arm2.h"
#include "Device.h"
#include "Ioc.h"
#include "Memc.h"
#include "Ram.h"
#include "Rom.h"

class A3000
{
public:

    A3000();
    ~A3000();

    A3000(const A3000 &orig)          = delete;
    A3000(A3000 &&orig)               = delete;
    A3000 &operator=(const A3000 &)   = delete;
    A3000 &operator=(A3000 &&)        = delete;

    bool LoadROM(std::string& romFilePath);
    void PrintState();
    void Reset();
    void Tick();

private:

    std::shared_ptr<Device::SystemBus> systemBus;
    Arm2 arm2;
    Ioc ioc;
    Memc memc;
    Ram ram;
    Rom rom;

};

#endif // A3000_H
