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
#include <memory> // std::shared_ptr

// Project includes
#include "Cpsr.h"
#include "Oak.h"

TEST(Register, UserCanSetGet)
{
    auto reg = Register(Cpsr::Mode::USER);
    reg.Set(Cpsr::Mode::USER, 1000);
    EXPECT_EQ(1000, reg.Get(Cpsr::Mode::USER));
}

TEST(Register, FIQCanSetGet)
{
    auto reg = Register(Cpsr::Mode::FIQ);
    reg.Set(Cpsr::Mode::FIQ, 2000);
    EXPECT_EQ(2000, reg.Get(Cpsr::Mode::FIQ));
}

TEST(Register, IRQCanSetGet)
{
    auto reg = Register(Cpsr::Mode::IRQ);
    reg.Set(Cpsr::Mode::IRQ, 3000);
    EXPECT_EQ(3000, reg.Get(Cpsr::Mode::IRQ));
}

TEST(Register, SVCCanSetGet)
{
    auto reg = Register(Cpsr::Mode::SVC);
    reg.Set(Cpsr::Mode::SVC, 4000);
    EXPECT_EQ(4000, reg.Get(Cpsr::Mode::SVC));
}

TEST(Register, UserCanSetFIQCannotGet)
{
    auto reg = Register(Cpsr::Mode::SVC);
    reg.Set(Cpsr::Mode::USER, 1000);
    EXPECT_NE(1000, reg.Get(Cpsr::Mode::FIQ));
}

TEST(Register, UserCanSetIRQCannotGet)
{
    auto reg = Register(Cpsr::Mode::SVC);
    reg.Set(Cpsr::Mode::USER, 1000);
    EXPECT_NE(1000, reg.Get(Cpsr::Mode::IRQ));
}

TEST(Register, UserCanSetSVCCannotGet)
{
    auto reg = Register(Cpsr::Mode::SVC);
    reg.Set(Cpsr::Mode::USER, 1000);
    EXPECT_NE(1000, reg.Get(Cpsr::Mode::SVC));
}

TEST(Register, FIQCanSetUserCannotGet)
{
    auto reg = Register(Cpsr::Mode::SVC);
    reg.Set(Cpsr::Mode::FIQ, 1000);
    EXPECT_NE(1000, reg.Get(Cpsr::Mode::USER));
}

TEST(Register, FIQCanSetIRQCannotGet)
{
    auto reg = Register(Cpsr::Mode::SVC);
    reg.Set(Cpsr::Mode::FIQ, 1000);
    EXPECT_NE(1000, reg.Get(Cpsr::Mode::IRQ));
}

TEST(Register, FIQCanSetSVCCannotGet)
{
    auto reg = Register(Cpsr::Mode::SVC);
    reg.Set(Cpsr::Mode::FIQ, 1000);
    EXPECT_NE(1000, reg.Get(Cpsr::Mode::SVC));
}

TEST(Register, IRQCanSetUserCannotGet)
{
    auto reg = Register(Cpsr::Mode::SVC);
    reg.Set(Cpsr::Mode::IRQ, 1000);
    EXPECT_NE(1000, reg.Get(Cpsr::Mode::USER));
}

TEST(Register, IRQCanSetFIQCannotGet)
{
    auto reg = Register(Cpsr::Mode::SVC);
    reg.Set(Cpsr::Mode::IRQ, 1000);
    EXPECT_NE(1000, reg.Get(Cpsr::Mode::FIQ));
}

TEST(Register, IRQCanSetSVCCannotGet)
{
    auto reg = Register(Cpsr::Mode::SVC);
    reg.Set(Cpsr::Mode::IRQ, 1000);
    EXPECT_NE(1000, reg.Get(Cpsr::Mode::SVC));
}

TEST(Register, WhenFIQIsInvalidUserIsSetGet)
{
    auto reg = Register(Cpsr::Mode::USER);
    reg.Set(Cpsr::Mode::USER, 1000);
    reg.Set(Cpsr::Mode::FIQ, 2000);
    EXPECT_NE(1000, reg.Get(Cpsr::Mode::FIQ));
    EXPECT_EQ(2000, reg.Get(Cpsr::Mode::USER));
    EXPECT_EQ(2000, reg.Get(Cpsr::Mode::FIQ));
}

TEST(Register, WhenIRQIsInvalidUserIsSetGet)
{
    auto reg = Register(Cpsr::Mode::FIQ);
    reg.Set(Cpsr::Mode::FIQ, 1000);
    reg.Set(Cpsr::Mode::IRQ, 2000);
    EXPECT_EQ(2000, reg.Get(Cpsr::Mode::USER));
    EXPECT_EQ(1000, reg.Get(Cpsr::Mode::FIQ));
    EXPECT_EQ(2000, reg.Get(Cpsr::Mode::IRQ));
}

TEST(Register, WhenSVCIsInvalidUserIsSetGet)
{
    auto reg = Register(Cpsr::Mode::IRQ);
    reg.Set(Cpsr::Mode::FIQ, 1000);
    reg.Set(Cpsr::Mode::IRQ, 2000);
    reg.Set(Cpsr::Mode::SVC, 3000);
    EXPECT_EQ(3000, reg.Get(Cpsr::Mode::USER));
    EXPECT_EQ(1000, reg.Get(Cpsr::Mode::FIQ));
    EXPECT_EQ(2000, reg.Get(Cpsr::Mode::IRQ));
    EXPECT_EQ(3000, reg.Get(Cpsr::Mode::SVC));
}
