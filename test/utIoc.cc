// File: utIoc.h
// Author: dgrubb
// Date: 22/12/2022
//
// Define tests for the I/O controller

// Implementation include
#include "Ioc.h"

// Library includes
#include <gmock/gmock.h>
#include <gtest/gtest.h>

// C++ library includes
#include "memory" // std::shared_ptr

// Project includes
#include "Oak.h"

TEST(IOC, CanReadWriteAddressBus)
{
    uint32_t address = 0x50;
    auto systemBus = std::make_shared<Device::SystemBus>();
    auto ioc = Ioc(systemBus);
}
