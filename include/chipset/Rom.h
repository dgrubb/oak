// File: Rom.h
// Author: dgrubb
// Date: 22/12/2022
//
// Provides a class for describing the A3000's
// ROM interface

#ifndef ROM_H
#define ROM_H

// C++ library includes
#include <cstdint>  // uint8_t, uint32_t
#include <memory>   // std::shared_ptr
#include <optional> // std::nullopt, std::optional
#include <vector>   // std::vector

// Project includes
#include "Device.h"

class Rom final: public Device
{
public:

    Rom(std::shared_ptr<Device::SystemBus> systemBus_);
    ~Rom();

    std::optional<uint8_t> ReadByte(uint32_t address);
    std::optional<uint32_t> ReadWord(uint32_t address);

    bool Load(std::string& romFilePath);

private:

    std::vector<uint8_t> rom;

    void DoTick() override;
};

#endif // ROM_H
