// File: Op.h
// Author: dgrubb
// Date: 02/01/2023
//
// Base class for all op-codes to implement common operations
// such as checking condition flags.

#ifndef OP_H
#define OP_H

// C++ library includes
#include <cstdint> // uint32_t
#include <memory>  // std::shared_ptr

// Project includes
#include "RegisterFile.h"

class Op
{
public:

    Op(uint32_t opcode_, std::shared_ptr<RegisterFile> registerFile_);
    ~Op();

    bool Execute();

protected:

    bool GetExecutionCompleted() { return executionCompleted; }

private:

    enum ConditionFields
    {
        EQ = 0, // 0000, EQ, Z set (equal)
        NE,     // 0001, NE, Z clear (not equal)
        CS,     // 0010, CS, C set (unsigned higher or same)
        CC,     // 0011, CC, C clear (unsigned lower)
        MI,     // 0100, MI, N set (negative)
        PL,     // 0101, PL, N clear (negative)
        VS,     // 0110, VS, V set (overflow)
        VC,     // 0111, VC, V clear (no overflow)
        HI,     // 1000, HI, C set and Z clear (unsigned higher)
        LS,     // 1001, LS, C clear or Z set (unsigned lower or same)
        GE,     // 1010, GE, N set and V set, or N clear and V clear (greater or equal)
        LT,     // 1011, LT, N set and V clear, or N clear and V set (less than)
        GT,     // 1100, GT, Z clear, and either N set and V set, or N clear and V clear (greater than)
        LE,     // 1101, LE, Z set, or N set and V clear, or N clear and V set (less than or equal)
        AL,     // 1110, AL, always
        NV,     // 1111, NV, never
    };

    static constexpr uint32_t ConditionFieldMask = 0xF0000000;

    uint32_t conditionField{0};
    uint32_t cycleCount{0};
    bool executionCompleted{false};
    uint32_t opcode{0};
    std::shared_ptr<RegisterFile> registerFile;

    bool CheckConditions();

    virtual bool DoExecute() = 0;

};

#endif // OP_H
