// File: utRegister.h
// Author: dgrubb
// Date: 28/12/2022
//
// Define tests for basic register component

// Implementation include
#include "Register.h"

// Library includes
#include <gmock/gmock.h>
#include <gtest/gtest.h>

// C++ library includes
#include "memory" // std::shared_ptr

// Project includes
#include "Cpsr.h"
#include "Oak.h"

TEST(Register, UserCanGetSet)
{
    auto reg = Register(Cpsr::Mode::USER);
    reg.Set(Cpsr::Mode::USER, 1000);
    EXPECT_EQ(1000, reg.Get(Cpsr::Mode::USER));
}
