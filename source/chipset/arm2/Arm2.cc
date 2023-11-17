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
#include "OpFactory.h"
#include "Register.h"

Arm2::Arm2(std::shared_ptr<Device::SystemBus> systemBus_)
  : Device(systemBus_)
{
    registerFile = std::make_shared<RegisterFile>();
    DEBUG("ARM2 initialised");
}

void Arm2::AdvancePipeline()
{
    TRACE("Advancing pipeline");

    // Advance fetched instructions through the
    // mocked up pipeline and poulate the fetch
    // step with the content of the data bus
    pipeline.execute = pipeline.decode;
    pipeline.decode = pipeline.fetch;
    pipeline.fetch = systemBus->dataBus;

    // Decode the instruction which landed in
    // the execute step of the pipeline
    if (auto instruction = OpFactory::Create(pipeline.execute, registerFile))
    {
        currentInstruction = std::move(instruction.value());
    }
    else
    {
        throw std::runtime_error("Failed to parse instruction from op code");
    }
}

void Arm2::DoTick()
{
    // TODO: Check for MEMC abort here

    // Execute() will return "true" to indicate computation was
    // completed in this clock tick. This is so instructions which
    // require multiple clock ticks to execute fully can be simulated
    // accurately.
    if (currentInstruction && !currentInstruction->Execute())
    {
        return;
    }

    // Once the current instruction has completed execution the CPU
    // will fetch the next instruction from the data bus.
    AdvancePipeline();
}

void Arm2::FlushPipeline()
{
    pipeline.fetch = 0;
    pipeline.decode = 0;
    pipeline.execute = 0;
}

void Arm2::PrintState()
{
    registerFile->PrintCPSR();
}

void Arm2::Reset()
{
    DEBUG("Reset");

    // Backup CPSR content into R14
    uint32_t cpsr = registerFile->GetCPSR();
    registerFile->SetMode(Cpsr::Mode::SVC);
    registerFile->SetRegisterValue(RegisterFile::RegisterRef::R14, cpsr);

    // Execute reset sequence, see page 12 of ARM datasheet
    FlushPipeline();
    registerFile->SetProgramCounter(0);
    registerFile->SetStatusFlag(Cpsr::StatusFlag::IRQ_DISABLE, true);
    registerFile->SetStatusFlag(Cpsr::StatusFlag::FIQ_DISABLE, true);
    systemBus->readWrite = Device::SystemBus::ReadWrite::READ;
    systemBus->byteWord = Device::SystemBus::ByteWord::WORD;
}

Arm2::~Arm2()
{
    DEBUG("ARM2 uninitialised");
}
