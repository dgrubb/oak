// File: Log.cc
// Author: dgrubb
// Date: 21/12/2022
//
// Implements logging functionality

// Implementation include
#include "Log.h"

// Project includes
#include "Oak.h"

namespace Log
{

    Levels current = Oak::defaultLogLevel;

    Levels GetCurrentLevel()
    {
        return current;
    }

    void SetCurrentLevel(Levels level)
    {
        current = level;
    }

} // namespace Log
