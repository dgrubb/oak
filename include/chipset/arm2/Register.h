// File: Register.h
// Author: dgrubb
// Date: 27/12/2022
//
// Provides an implementation of the ARM2's basic register component.

#ifndef REGISTER_H
#define REGISTER_H

// C++ library includes
#include <cstdint> // uint32_t
#include <vector>  // std::vector

// Project includes
#include "Cpsr.h"  // Mode, StatusFlag

class Register
{
public:

    Register(Cpsr::Mode highestAccessMode_);
    ~Register();

    Register(const Register &orig)          = delete;
    // N.b., allow usage with emplace_back of vectors
    Register(Register &&orig)               = default;
    Register &operator=(const Register &)   = delete;
    Register &operator=(Register &&)        = delete;

    uint32_t Get(Cpsr::Mode mode);

    void Set(Cpsr::Mode mode, uint32_t value);

private:

    std::vector<uint32_t> shadowRegisters;
    Cpsr::Mode highestAccessMode{Cpsr::Mode::USER};
};

#endif // REGISTER_H
