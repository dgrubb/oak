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
    static constexpr char author[] = "dgrubb";
    static constexpr Log::Levels defaultLogLevel = Log::INFO;
    static constexpr uint32_t defaultWindowWidth = 800;
    static constexpr uint32_t defaultWindowHeight = 600;
    static constexpr char usage[] =
        "Usage: Oak [arguments]\n\n"
        "Arguments:\n\n"
        "\t-h\tShow usage\n"
        "\t-l\tSet log level (e.g., ./Oak -l 3). Default 2 (INFO). Options:\n"
        "\t\t\t0 - TRACE\n"
        "\t\t\t1 - DEBUG\n"
        "\t\t\t2 - INFO\n"
        "\t\t\t3 - WARN\n"
        "\t\t\t4 - ERROR\n"
        "\t\t\t5 - CRITICAL\n"
        "\t-r\tSpecify ROM file (e.g., ./Oak -r myROM). Defaults to ./riscos-3.71.rom\n";
}

#endif // OAK_H
