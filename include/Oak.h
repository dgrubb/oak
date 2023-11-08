// File: Oak.h
// Author: dgrubb
// Date: 21/12/2022
//
// Top-level header for application-wide definitions and defaults

#ifndef OAK_H
#define OAK_H

// C++ library includes
#include <cstdint> // uint32_t

// Project includes
#include "Log.h"
#include "Version.h"

namespace Oak
{
    static constexpr char name[] = "Oak";
    static constexpr Log::Levels defaultLogLevel = Log::INFO;
    static constexpr uint32_t defaultWindowWidth = 800;
    static constexpr uint32_t defaultWindowHeight = 600;
}

#endif // OAK_H
