// File: Arm2.h
// Author: dgrubb
// Date: 22/12/2022
//
// Implements an ARM2 CPU.

#ifndef ARM2_H
#define ARM2_H

// C++ header includes
#include <memory> // std::shared_ptr

// Project includes
#include "Device.h"
#include "RegisterFile.h"

class Arm2: public Device
{
public:

    Arm2(std::shared_ptr<Device::SystemBus> systemBus_);
    ~Arm2();

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
    RegisterFile registerFile;

    void AdvancePipeline();
    void FlushPipeline();

    void DoTick() override;
};

#endif // ARM2_H
