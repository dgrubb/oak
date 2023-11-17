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
    static constexpr unsigned int defaultWindowWidth = 800;
    static constexpr unsigned int defaultWindowHeight = 600;
    static constexpr char usage[] =
        "Usage: Oak [arguments]\n\n"
        "Arguments:\n\n"
        "\t-h\tShow usage\n"
        "\t-l\tSet log level (e.g., ./Oak -l DEBUG). Default INFO. Options:\n"
        "\t\t\tTRACE\n"
        "\t\t\tDEBUG\n"
        "\t\t\tINFO\n"
        "\t\t\tWARN\n"
        "\t\t\tERROR\n"
        "\t\t\tCRITICAL\n"
        "\t-r\tSpecify ROM file (e.g., ./Oak -r myROM). Defaults to ./riscos-3.71.rom\n";
}

#endif // OAK_H
