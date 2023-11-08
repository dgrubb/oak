// File: utRegisterFile.h
// Author: dgrubb
// Date: 23/12/2022
//
// Define tests to provide consistency of the reigster file.

// Implementation include
#include "RegisterFile.h"

// Library includes
#include <gmock/gmock.h>
#include <gtest/gtest.h>

// Project includes
#include "Oak.h"

TEST(RegisterFile, CanSetModeUSER)
{
    Cpsr::Mode mode{Cpsr::Mode::USER};
    auto registerFile = RegisterFile();
    registerFile.SetMode(mode);
    EXPECT_EQ(registerFile.GetMode(), mode);
}

TEST(RegisterFile, CanSetModeFIQ)
{
    Cpsr::Mode mode{Cpsr::Mode::FIQ};
    auto registerFile = RegisterFile();
    registerFile.SetMode(mode);
    EXPECT_EQ(registerFile.GetMode(), mode);
}

TEST(RegisterFile, CanSetModeIRQ)
{
    Cpsr::Mode mode{Cpsr::Mode::IRQ};
    auto registerFile = RegisterFile();
    registerFile.SetMode(mode);
    EXPECT_EQ(registerFile.GetMode(), mode);
}

TEST(RegisterFile, CanSetModeSVC)
{
    Cpsr::Mode mode{Cpsr::Mode::SVC};
    auto registerFile = RegisterFile();
    registerFile.SetMode(mode);
    EXPECT_EQ(registerFile.GetMode(), mode);
}

TEST(RegisterFile, CanSetGetProgramCounter)
{
    auto registerFile = RegisterFile();
    registerFile.SetProgramCounter(1000);
    EXPECT_EQ(registerFile.GetProgramCounter(), 1000);
}

TEST(RegisterFile, CanSetGetRegisterR0)
{
    auto registerFile = RegisterFile();
    registerFile.SetRegisterValue(RegisterFile::RegisterRef::R0, 1000);
    EXPECT_EQ(registerFile.GetRegisterValue(RegisterFile::RegisterRef::R0), 1000);
}

