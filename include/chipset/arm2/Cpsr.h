// File: Cpsr.h
// Author: dgrubb
// Date: 27/12/2022
//
// Provides an implementation of the ARM2's special status and program
// counter register (CPSR).

#ifndef CPSR_H
#define CPSR_H

// C++ library includes
#include <cstdint>     // uint32_t
#include <string_view> // std::string_view

// Project includes
#include "Integral.h"

class Cpsr
{
public:

    enum class Mode : int
    {
        USER = 0, // 00
        FIQ,      // 01
        IRQ,      // 10
        SVC       // 11
    };

    enum class StatusFlag : int
    {
        FIQ_DISABLE = 0,
        IRQ_DISABLE,
        OVERFLOW,
        CARRY,
        ZERO,
        NEGATIVE
    };

    static constexpr uint32_t statusFlagsMasks[] = {
        0x04000000, // FIQ_DISABLE
        0x08000000, // IRQ_DISABLE
        0x10000000, // OVERFLOW
        0x20000000, // CARRY
        0x40000000, // ZERO
        0x80000000  // NEGATIVE
    };

    Cpsr();
    ~Cpsr();

    static inline std::string_view GetModeString(Mode mode) { return modeNameStrings[ToIntegral(mode)]; }
    uint32_t Get() { return value; }
    Mode GetMode();
    uint32_t GetProgramCounter();
    bool GetStatusFlag(StatusFlag flag);
    uint32_t IncrementProgramCounter();

    void PrintState();

    void Set(uint32_t value_) { value = value_; }
    void SetMode(Mode mode);
    void SetProgramCounter(uint32_t programCounter);
    void SetStatusFlag(StatusFlag flag, bool set);

private:

    static constexpr uint32_t ModeMask = 0x00000003;
    static constexpr uint32_t ProgramCounterMask = 0x03FFFFFC;
    static const char* modeNameStrings[];
    static const char* statusFlagsNameStrings[];

    uint32_t value{0};
};

#endif // CPSR_H
