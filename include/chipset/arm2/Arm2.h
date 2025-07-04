// File: Arm2.h
// Author: dgrubb
// Date: 22/12/2022
//
// Implements an ARM2 CPU.

#ifndef ARM2_H
#define ARM2_H

// C++ header includes
#include <memory> // std::shared_ptr, std::unique_ptr

// Project includes
#include "Device.h"
#include "Op.h"
#include "RegisterFile.h"

class Arm2 final: public Device
{
public:

    Arm2(std::shared_ptr<Device::SystemBus> systemBus_);
    ~Arm2();

    Arm2(const Arm2 &orig)          = delete;
    Arm2(Arm2 &&orig)               = delete;
    Arm2 &operator=(const Arm2 &)   = delete;
    Arm2 &operator=(Arm2 &&)        = delete;

    void PrintState();
    void Reset();

private:

    struct Pipeline
    {
        uint32_t fetch{0};
        uint32_t decode{0};
        uint32_t execute{0};
    };

    Pipeline pipeline;
    std::shared_ptr<RegisterFile> registerFile;
    std::unique_ptr<Op> currentInstruction;

    void AdvancePipeline();
    void FlushPipeline();
    void UpdateAddressBus();

    void DoTick() override;
};

#endif // ARM2_H
