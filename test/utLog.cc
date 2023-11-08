// File: utLog.h
// Author: dgrubb
// Date: 21/12/2022
//
// Define tests for logging functions

// Implementation include
#include "Log.h"

// Library includes
#include <gmock/gmock.h>
#include <gtest/gtest.h>

// Project includes
#include "Oak.h"

// N.B., subsequent tests will adjust log level state so this
// test must be executed before all others
TEST(Log, DefaultLevel)
{
    auto currentLogLevel = Log::GetCurrentLevel();
    EXPECT_EQ(currentLogLevel, Oak::defaultLogLevel);
}

TEST(Log, CanSetCurrentLevelTrace)
{
    Log::SetCurrentLevel(Log::Levels::TRACE);
    EXPECT_EQ(Log::Levels::TRACE, Log::GetCurrentLevel());
}

TEST(Log, CanSetCurrentLevelDebug)
{
    Log::SetCurrentLevel(Log::Levels::DEBUG);
    EXPECT_EQ(Log::Levels::DEBUG, Log::GetCurrentLevel());
}

TEST(Log, CanSetCurrentLevelInfo)
{
    Log::SetCurrentLevel(Log::Levels::INFO);
    EXPECT_EQ(Log::Levels::INFO, Log::GetCurrentLevel());
}

TEST(Log, CanSetCurrentLevelWarn)
{
    Log::SetCurrentLevel(Log::Levels::WARN);
    EXPECT_EQ(Log::Levels::WARN, Log::GetCurrentLevel());
}

TEST(Log, CanSetCurrentLevelError)
{
    Log::SetCurrentLevel(Log::Levels::ERROR);
    EXPECT_EQ(Log::Levels::ERROR, Log::GetCurrentLevel());
}

TEST(Log, CanSetCurrentLevelCritical)
{
    Log::SetCurrentLevel(Log::Levels::CRITICAL);
    EXPECT_EQ(Log::Levels::CRITICAL, Log::GetCurrentLevel());
}

// The rest of the test suite will have this value persist
// so applying the default will prevent a lot of log spew.
// Adjust to more detailed levels when debugging
TEST(Log, ResumeDefaultLevel)
{
    Log::SetCurrentLevel(Oak::defaultLogLevel);
    EXPECT_EQ(Oak::defaultLogLevel, Log::GetCurrentLevel());
}
