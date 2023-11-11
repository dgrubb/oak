// File: RegisterFile.h
// Author: dgrubb
// Date: 22/12/2022
//
// Provides an implementation of the ARM2's register file with access controlled
// by processor mode (e.g., Supervisor, User, IRQ, etc).

#ifndef REGISTERFILE_H
#define REGISTERFILE_H

// C++ library includes
#include <cstdint> // uint32_t
#include <vector>  // std::vector

// Project includes
#include "Cpsr.h"  // Mode, StatusFlag
#include "Register.h"

class RegisterFile
{
public:

    enum class RegisterRef : uint32_t
    {
        R0 = 0,
        R1,
        R2,
        R3,
        R4,
        R5,
        R6,
        R7,
        R8,
        R9,
        R10,
        R11,
        R12,
        R13,
        R14,
        R15  // PC/PSR
    };

    RegisterFile();
    ~RegisterFile();

    uint32_t GetCPSR();
    Cpsr::Mode GetMode();
    uint32_t GetProgramCounter();
    uint32_t GetRegisterValue(RegisterRef reg);
    bool GetStatusFlag(Cpsr::StatusFlag flag);

    void PrintCPSR();
    void SetCPSR(uint32_t value);
    void SetMode(Cpsr::Mode mode);
    void SetProgramCounter(uint32_t counter);
    void SetRegisterValue(RegisterRef reg, uint32_t value);
    void SetStatusFlag(Cpsr::StatusFlag flag, bool set);

private:

    static const char* registerNameStrings[];

    std::vector<Register> registers;

    // R15 is a special register which contains both
    // the Program Counter (PC) and Status Register (PSR)
    Cpsr cpsr{};

    void Init();
};

#endif // REGISTERFILE_H
