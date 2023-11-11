// File: Log.h
// Author: dgrubb
// Date: 21/12/2022
//
// Implements basic log formatting and log level application

#ifndef LOG_H
#define LOG_H

// C++ standard includes
#include <cstring>  // std::strrchr
#include <iostream> // std::cout, std::endl
#include <optional> // std::optional, std::nullopt
#include <sstream>  // std::ostringstream

#define __FILENAME__ (std::strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define TRACE(...) if (Log::Levels::TRACE >= Log::GetCurrentLevel()) \
    Log::Log("TRACE", __LINE__, __FILENAME__, __FUNCTION__, __VA_ARGS__)

#define DEBUG(...) if (Log::Levels::DEBUG >= Log::GetCurrentLevel()) \
    Log::Log("DEBUG", __LINE__, __FILENAME__, __FUNCTION__, __VA_ARGS__)

#define INFO(...) if (Log::Levels::INFO >= Log::GetCurrentLevel()) \
    Log::Log("INFO", __LINE__, __FILENAME__, __FUNCTION__, __VA_ARGS__)

#define WARN(...) if (Log::Levels::WARN >= Log::GetCurrentLevel()) \
    Log::Log("WARN", __LINE__, __FILENAME__, __FUNCTION__, __VA_ARGS__)

#define ERROR(...) if (Log::Levels::ERROR >= Log::GetCurrentLevel()) \
    Log::Log("ERROR", __LINE__, __FILENAME__, __FUNCTION__, __VA_ARGS__)

#define CRITICAL(...) if (Log::Levels::CRITICAL >= Log::GetCurrentLevel()) \
    Log::Log("CRITICAL", __LINE__, __FILENAME__, __FUNCTION__, __VA_ARGS__)

namespace Log {

    enum Levels {
        TRACE = 0,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        CRITICAL
    };

    static const char* logLevelStrings[] = {
        "TRACE",
        "DEBUG",
        "INFO",
        "WARN",
        "ERROR",
        "CRITICAL"
    };

    static inline std::string_view GetLogLevelString(Levels level) { return logLevelStrings[level]; }
    static inline std::optional<Levels> GetLogLevelFromString(std::string& level)
    {
        int logLevelIdx{0};
        for (auto& logLevelStr: logLevelStrings)
        {
            if (level == logLevelStr)
            {
                return static_cast<Levels>(logLevelIdx);
            }
            logLevelIdx++;
        }
        return std::nullopt;
    }
    template <typename ...Args>
    void Log(const char* level, int line, const char* file, const char* function, Args&& ... args)
    {
        std::ostringstream ss;
        ss << "[ " << level << " ] " << file << ":" << line << " ( " << function << " ) ";
        (ss << ... << std::forward<Args>(args)) << std::endl;
        std::cout << ss.str().c_str();
    }

    Levels GetCurrentLevel();
    void SetCurrentLevel(Levels level);

} // namespace Log

#endif // LOG_H
