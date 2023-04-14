// File: utCpsr.h
// Author: dgrubb
// Date: 11/04/2023
//
// Define tests for special CPSR (status+PC) register

// Implementation include
#include "Cpsr.h"

// Library includes
#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(Cpsr, CanSetModeUSER)
{
    auto cpsr = Cpsr();
    cpsr.SetMode(Cpsr::Mode::USER);
    EXPECT_EQ(Cpsr::Mode::USER, cpsr.GetMode());
}


