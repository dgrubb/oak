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

TEST(Cpsr, CanSetGetDirectly)
{
    auto cpsr = Cpsr();
    cpsr.Set(50);
    EXPECT_EQ(50, cpsr.Get());
}

TEST(Cpsr, CanGetModeStringUSER)
{
    auto cpsr = Cpsr();
    EXPECT_EQ("USER", cpsr.GetModeString(Cpsr::Mode::USER));
}

TEST(Cpsr, CanGetModeStringFIQ)
{
    auto cpsr = Cpsr();
    EXPECT_EQ("FIQ", cpsr.GetModeString(Cpsr::Mode::FIQ));
}

TEST(Cpsr, CanGetModeStringIRQ)
{
    auto cpsr = Cpsr();
    EXPECT_EQ("IRQ", cpsr.GetModeString(Cpsr::Mode::IRQ));
}

TEST(Cpsr, CanGetModeStringSVC)
{
    auto cpsr = Cpsr();
    EXPECT_EQ("SVC", cpsr.GetModeString(Cpsr::Mode::SVC));
}

TEST(Cpsr, CanSetModeUSER)
{
    auto cpsr = Cpsr();
    cpsr.SetMode(Cpsr::Mode::USER);
    EXPECT_EQ(Cpsr::Mode::USER, cpsr.GetMode());
}

TEST(Cpsr, CanSetModeFIQ)
{
    auto cpsr = Cpsr();
    cpsr.SetMode(Cpsr::Mode::FIQ);
    EXPECT_EQ(Cpsr::Mode::FIQ, cpsr.GetMode());
}

TEST(Cpsr, CanSetModeIRQ)
{
    auto cpsr = Cpsr();
    cpsr.SetMode(Cpsr::Mode::IRQ);
    EXPECT_EQ(Cpsr::Mode::IRQ, cpsr.GetMode());
}

TEST(Cpsr, CanSetModeSVC)
{
    auto cpsr = Cpsr();
    cpsr.SetMode(Cpsr::Mode::SVC);
    EXPECT_EQ(Cpsr::Mode::SVC, cpsr.GetMode());
}
