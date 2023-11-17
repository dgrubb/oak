// File: Ram.h
// Author: dgrubb
// Date: 22/12/2022
//
// Provides a class for describing the A3000's
// RAM interface

#ifndef RAM_H
#define RAM_H

// C++ library includes
#include <array>    // std::array
#include <cstdint>  // uint8_t
#include <memory>   // std::shared_ptr
#include <optional> // std::nullopt, std::optional

// Project includes
#include "Device.h"

class Ram final: public Device
{
public:

    static constexpr uint32_t RamSize{1000000};

    Ram(std::shared_ptr<Device::SystemBus> systemBus_);
    ~Ram();

    Ram(const Ram &orig)          = delete;
    Ram(Ram &&orig)               = delete;
    Ram &operator=(const Ram &)   = delete;
    Ram &operator=(Ram &&)        = delete;

    std::optional<uint8_t> Read(uint32_t address);
    bool Write(uint32_t address, uint8_t byte);

private:

    std::array<uint8_t, RamSize> ram = {0};

    void DoTick() override;
};

#endif // RAM_H
