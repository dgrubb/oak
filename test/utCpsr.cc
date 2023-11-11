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

TEST(Cpsr, CanSetGetProgramCounter)
{
    auto cpsr = Cpsr();
    cpsr.SetProgramCounter(0x500);
    EXPECT_EQ(0x500, cpsr.GetProgramCounter());
}

TEST(Cpsr, CanSetGetClearStatusFlag_FIQ_DISABLE)
{
    auto cpsr = Cpsr();
    cpsr.SetStatusFlag(Cpsr::StatusFlag::FIQ_DISABLE, true);
    EXPECT_TRUE(cpsr.GetStatusFlag(Cpsr::StatusFlag::FIQ_DISABLE));

    cpsr.SetStatusFlag(Cpsr::StatusFlag::FIQ_DISABLE, false);
    EXPECT_FALSE(cpsr.GetStatusFlag(Cpsr::StatusFlag::FIQ_DISABLE));
}

TEST(Cpsr, CanSetGetClearStatusFlag_IRQ_DISABLE)
{
    auto cpsr = Cpsr();
    cpsr.SetStatusFlag(Cpsr::StatusFlag::IRQ_DISABLE, true);
    EXPECT_TRUE(cpsr.GetStatusFlag(Cpsr::StatusFlag::IRQ_DISABLE));

    cpsr.SetStatusFlag(Cpsr::StatusFlag::IRQ_DISABLE, false);
    EXPECT_FALSE(cpsr.GetStatusFlag(Cpsr::StatusFlag::IRQ_DISABLE));
}

TEST(Cpsr, CanSetGetClearStatusFlag_OVERFLOW)
{
    auto cpsr = Cpsr();
    cpsr.SetStatusFlag(Cpsr::StatusFlag::OVERFLOW, true);
    EXPECT_TRUE(cpsr.GetStatusFlag(Cpsr::StatusFlag::OVERFLOW));

    cpsr.SetStatusFlag(Cpsr::StatusFlag::OVERFLOW, false);
    EXPECT_FALSE(cpsr.GetStatusFlag(Cpsr::StatusFlag::OVERFLOW));
}

TEST(Cpsr, CanSetGetClearStatusFlag_CARRY)
{
    auto cpsr = Cpsr();
    cpsr.SetStatusFlag(Cpsr::StatusFlag::CARRY, true);
    EXPECT_TRUE(cpsr.GetStatusFlag(Cpsr::StatusFlag::CARRY));

    cpsr.SetStatusFlag(Cpsr::StatusFlag::CARRY, false);
    EXPECT_FALSE(cpsr.GetStatusFlag(Cpsr::StatusFlag::CARRY));
}

TEST(Cpsr, CanSetGetClearStatusFlag_ZERO)
{
    auto cpsr = Cpsr();
    cpsr.SetStatusFlag(Cpsr::StatusFlag::ZERO, true);
    EXPECT_TRUE(cpsr.GetStatusFlag(Cpsr::StatusFlag::ZERO));

    cpsr.SetStatusFlag(Cpsr::StatusFlag::ZERO, false);
    EXPECT_FALSE(cpsr.GetStatusFlag(Cpsr::StatusFlag::ZERO));
}

TEST(Cpsr, CanSetGetClearStatusFlag_NEGATIVE)
{
    auto cpsr = Cpsr();
    cpsr.SetStatusFlag(Cpsr::StatusFlag::NEGATIVE, true);
    EXPECT_TRUE(cpsr.GetStatusFlag(Cpsr::StatusFlag::NEGATIVE));

    cpsr.SetStatusFlag(Cpsr::StatusFlag::NEGATIVE, false);
    EXPECT_FALSE(cpsr.GetStatusFlag(Cpsr::StatusFlag::NEGATIVE));
}

// Because the program counter is embedded in the
// same register as the status bits it's important
// to ensure that setting one doesn't affect the
// other values. These tests ensures the bitwise logic
// and masks are correct by verifying changing unrelated
// fields don't impact each other

TEST(Cpsr, ModeAndProgramCounterAreOrthogonal)
{
    auto cpsr = Cpsr();

    // Set testable PC state
    cpsr.SetProgramCounter(0x500);
    EXPECT_EQ(0x500, cpsr.GetProgramCounter());

    // Changing mode has no impact on PC
    cpsr.SetMode(Cpsr::Mode::SVC);
    EXPECT_EQ(Cpsr::Mode::SVC, cpsr.GetMode());
    EXPECT_EQ(0x500, cpsr.GetProgramCounter());

    // Changing PC has no impact on mode
    cpsr.SetProgramCounter(0x2000);
    EXPECT_EQ(Cpsr::Mode::SVC, cpsr.GetMode());
    EXPECT_EQ(0x2000, cpsr.GetProgramCounter());
}

TEST(Cpsr, ModeAndStatusFlagsAreOrthogonal)
{
    auto cpsr = Cpsr();

    // Set testable mode state
    cpsr.SetMode(Cpsr::Mode::SVC);
    EXPECT_EQ(Cpsr::Mode::SVC, cpsr.GetMode());

    // Changing status flag has no impact on mode
    cpsr.SetStatusFlag(Cpsr::StatusFlag::FIQ_DISABLE, true);
    EXPECT_TRUE(cpsr.GetStatusFlag(Cpsr::StatusFlag::FIQ_DISABLE));
    EXPECT_EQ(Cpsr::Mode::SVC, cpsr.GetMode());

    cpsr.SetStatusFlag(Cpsr::StatusFlag::FIQ_DISABLE, false);
    EXPECT_FALSE(cpsr.GetStatusFlag(Cpsr::StatusFlag::FIQ_DISABLE));
    EXPECT_EQ(Cpsr::Mode::SVC, cpsr.GetMode());

    // Changing mode has no impact on status flag
    cpsr.SetMode(Cpsr::Mode::USER);
    EXPECT_EQ(Cpsr::Mode::USER, cpsr.GetMode());
    EXPECT_FALSE(cpsr.GetStatusFlag(Cpsr::StatusFlag::FIQ_DISABLE));
}

TEST(Cpsr, StatusFlagsAndProgramCounterAreOrthogonal)
{
    auto cpsr = Cpsr();

    cpsr.SetStatusFlag(Cpsr::StatusFlag::ZERO, true);
    EXPECT_TRUE(cpsr.GetStatusFlag(Cpsr::StatusFlag::ZERO));

    // Changing program counter has no impact on status flag
    cpsr.SetProgramCounter(0x500);
    EXPECT_EQ(0x500, cpsr.GetProgramCounter());
    EXPECT_TRUE(cpsr.GetStatusFlag(Cpsr::StatusFlag::ZERO));

    cpsr.SetProgramCounter(0x900);
    EXPECT_EQ(0x900, cpsr.GetProgramCounter());
    EXPECT_TRUE(cpsr.GetStatusFlag(Cpsr::StatusFlag::ZERO));

    // Changing status flag has no impact on prorgam counter
    cpsr.SetStatusFlag(Cpsr::StatusFlag::NEGATIVE, true);
    EXPECT_TRUE(cpsr.GetStatusFlag(Cpsr::StatusFlag::NEGATIVE));
    EXPECT_EQ(0x900, cpsr.GetProgramCounter());
}
