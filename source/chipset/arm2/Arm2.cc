// File: Arm2.cc
// Author: dgrubb
// Date: 22/12/2022
//
// Implements an ARM2 CPU.

// Implementation header
#include "Arm2.h"

// Project includes
#include "Cpsr.h" // Mode, StatusFlag
#include "Log.h"
#include "Register.h"

Arm2::Arm2(std::shared_ptr<Device::SystemBus> systemBus_)
  : Device(systemBus_)
{
    INFO("ARM2 initialised");
}

void Arm2::AdvancePipeline()
{
    // TODO: copy object from one step to the next
}

void Arm2::DoTick()
{
    // TODO: check if current instruction is single shot or
    // sequential clocks (e.g., block transfer)

    // TODO: Step Op

    // TODO: test is op is completed, return if not

    // TODO: advance pipeline
}

void Arm2::FlushPipeline()
{
    pipeline.fetch = 0;
    pipeline.decode = 0;
    pipeline.execute = 0;
}

void Arm2::PrintState()
{
    registerFile.PrintCPSR();
}

void Arm2::Reset()
{
    DEBUG("Reset");

    // Backup CPSR content into R14
    uint32_t cpsr = registerFile.GetCPSR();
    registerFile.SetMode(Cpsr::Mode::SVC);
    registerFile.SetRegisterValue(RegisterFile::RegisterRef::R14, cpsr);

    // Execute reset sequence, see page 12 of ARM datasheet
    FlushPipeline();
    registerFile.SetProgramCounter(0);
    registerFile.SetStatusFlag(Cpsr::StatusFlag::IRQ_DISABLE, true);
    registerFile.SetStatusFlag(Cpsr::StatusFlag::FIQ_DISABLE, true);
    SetReadWrite(Device::SystemBus::READ);
}

Arm2::~Arm2()
{
}
