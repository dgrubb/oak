// File: Memc.cc
// Author: dgrubb
// Date: 22/12/2022
//
// Provides a class for describing the A3000's
// memory controller

// Implementation header
#include "Memc.h"

// Project includes
#include "Log.h"

const char* Memc::osModeSelectStrings[] ={
    "Deselected",
    "Selected"
};

const char* Memc::pageSizeStrings[] = {
    "4KBytes",
    "8KBytes",
    "16KBytes",
    "32KBytes"
};

Memc::Memc(std::shared_ptr<Device::SystemBus> systemBus_)
  : Device(systemBus_)
{
    DEBUG("MEMC initialised");
}

void Memc::DoTick()
{
    auto addressedMemoryRegion = mapFunction();

    if (addressedMemoryRegion == MapRegions::LOW_ROM || addressedMemoryRegion == MapRegions::HIGH_ROM)
    {
        systemBus->enableROM = true;
    }
    else
    {
        systemBus->enableROM = false;
    }
}

void Memc::EnableDefaultMemoryMap()
{
    mapFunction = [&]() {
        return GetDefaultMemoryMapRegion();
    };
}

Memc::MapRegions Memc::GetDefaultMemoryMapRegion()
{
    // TODO: Populate the rest of the map
    return MapRegions::LOGICAL_RAM;
}

Memc::OSModeSelect Memc::GetOSModeSelect()
{
    auto select = static_cast<OSModeSelect>((controlRegister & OSModeSelectMask) >> 12);
    DEBUG("Getting OS mode select: ", osModeSelectStrings[select]);
    return select;
}

Memc::PageSize Memc::GetPageSize()
{
    auto size = static_cast<PageSize>((controlRegister & PageSizeMask) >> 2);
    DEBUG("Getting memory page size: ", pageSizeStrings[size]);
    return size;
}

Memc::MapRegions Memc::GetResetMemoryMapRegion()
{
    // TODO: Decide if low and high ROM needs to be distinguished
    return MapRegions::LOW_ROM;
}

void Memc::Reset()
{
    DEBUG("Reset");
    // When the system is put into reset the ARM2 will begin
    // executing code located at location 0x000000. When the
    // normal memory map is enabled this correpsonds to the
    // start of RAM so, to ensure real code from ROM can be
    // accessed, the ROM is enabled and the normal memory
    // map is disabled. To restore the memory map the CPU
    // programs MEMC through a sequence of address invocations.
    // See MEMC Datasheet, page 12 for more information.
    mapFunction = [&]() {
        return GetResetMemoryMapRegion();
    };
}

void Memc::SetOSModeSelect(OSModeSelect select)
{
    DEBUG("Setting OS mode select: ", osModeSelectStrings[select]);
    controlRegister &= ~OSModeSelectMask;
    controlRegister |= (select << 12);
}

void Memc::SetPageSize(PageSize size)
{
    DEBUG("Setting memory page size: ", pageSizeStrings[size]);
    controlRegister &= ~PageSizeMask;
    controlRegister |= (size << 2);
}

Memc::~Memc()
{
    DEBUG("MEMC uninitialised");
}
