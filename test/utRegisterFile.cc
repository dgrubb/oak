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

TEST(RegisterFile, CanSetGetRegisterR1)
{
    auto registerFile = RegisterFile();
    registerFile.SetRegisterValue(RegisterFile::RegisterRef::R1, 1000);
    EXPECT_EQ(registerFile.GetRegisterValue(RegisterFile::RegisterRef::R1), 1000);
}

TEST(RegisterFile, CanSetGetRegisterR2)
{
    auto registerFile = RegisterFile();
    registerFile.SetRegisterValue(RegisterFile::RegisterRef::R2, 2000);
    EXPECT_EQ(registerFile.GetRegisterValue(RegisterFile::RegisterRef::R2), 2000);
}

TEST(RegisterFile, CanSetGetRegisterR3)
{
    auto registerFile = RegisterFile();
    registerFile.SetRegisterValue(RegisterFile::RegisterRef::R3, 3000);
    EXPECT_EQ(registerFile.GetRegisterValue(RegisterFile::RegisterRef::R3), 3000);
}

TEST(RegisterFile, CanSetGetRegisterR4)
{
    auto registerFile = RegisterFile();
    registerFile.SetRegisterValue(RegisterFile::RegisterRef::R4, 4000);
    EXPECT_EQ(registerFile.GetRegisterValue(RegisterFile::RegisterRef::R4), 4000);
}

TEST(RegisterFile, CanSetGetRegisterR5)
{
    auto registerFile = RegisterFile();
    registerFile.SetRegisterValue(RegisterFile::RegisterRef::R5, 5000);
    EXPECT_EQ(registerFile.GetRegisterValue(RegisterFile::RegisterRef::R5), 5000);
}

TEST(RegisterFile, CanSetGetRegisterR6)
{
    auto registerFile = RegisterFile();
    registerFile.SetRegisterValue(RegisterFile::RegisterRef::R6, 6000);
    EXPECT_EQ(registerFile.GetRegisterValue(RegisterFile::RegisterRef::R6), 6000);
}

TEST(RegisterFile, CanSetGetRegisterR7)
{
    auto registerFile = RegisterFile();
    registerFile.SetRegisterValue(RegisterFile::RegisterRef::R7, 7000);
    EXPECT_EQ(registerFile.GetRegisterValue(RegisterFile::RegisterRef::R7), 7000);
}

TEST(RegisterFile, CanSetGetRegisterR8)
{
    auto registerFile = RegisterFile();
    registerFile.SetRegisterValue(RegisterFile::RegisterRef::R8, 8000);
    EXPECT_EQ(registerFile.GetRegisterValue(RegisterFile::RegisterRef::R8), 8000);
}

TEST(RegisterFile, CanSetGetRegisterR9)
{
    auto registerFile = RegisterFile();
    registerFile.SetRegisterValue(RegisterFile::RegisterRef::R9, 9000);
    EXPECT_EQ(registerFile.GetRegisterValue(RegisterFile::RegisterRef::R9), 9000);
}

TEST(RegisterFile, CanSetGetRegisterR10)
{
    auto registerFile = RegisterFile();
    registerFile.SetRegisterValue(RegisterFile::RegisterRef::R10, 10000);
    EXPECT_EQ(registerFile.GetRegisterValue(RegisterFile::RegisterRef::R10), 10000);
}

TEST(RegisterFile, CanSetGetRegisterR11)
{
    auto registerFile = RegisterFile();
    registerFile.SetRegisterValue(RegisterFile::RegisterRef::R11, 11000);
    EXPECT_EQ(registerFile.GetRegisterValue(RegisterFile::RegisterRef::R11), 11000);
}

TEST(RegisterFile, CanSetGetRegisterR12)
{
    auto registerFile = RegisterFile();
    registerFile.SetRegisterValue(RegisterFile::RegisterRef::R12, 12000);
    EXPECT_EQ(registerFile.GetRegisterValue(RegisterFile::RegisterRef::R12), 12000);
}

TEST(RegisterFile, CanSetGetRegisterR13)
{
    auto registerFile = RegisterFile();
    registerFile.SetRegisterValue(RegisterFile::RegisterRef::R13, 13000);
    EXPECT_EQ(registerFile.GetRegisterValue(RegisterFile::RegisterRef::R13), 13000);
}

TEST(RegisterFile, CanSetGetRegisterR14)
{
    auto registerFile = RegisterFile();
    registerFile.SetRegisterValue(RegisterFile::RegisterRef::R14, 14000);
    EXPECT_EQ(registerFile.GetRegisterValue(RegisterFile::RegisterRef::R14), 14000);
}

TEST(RegisterFile, CanSetGetRegisterR15)
{
    auto registerFile = RegisterFile();
    registerFile.SetRegisterValue(RegisterFile::RegisterRef::R15, 15000);
    registerFile.PrintCPSR();
    EXPECT_EQ(registerFile.GetRegisterValue(RegisterFile::RegisterRef::R15), 15000);
    registerFile.PrintCPSR();
}
