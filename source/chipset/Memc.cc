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
}

Memc::OSModeSelect Memc::GetOSModeSelect()
{
    auto select = static_cast<OSModeSelect>((controlRegister & OSModeSelectMask) >> 12);
    DEBUG("Getting OS mode select: ", osModeSelectStrings[select]);
    return select;
}

void Memc::SetOSModeSelect(OSModeSelect select)
{
    DEBUG("Setting OS mode select: ", osModeSelectStrings[select]);
    controlRegister &= ~OSModeSelectMask;
    controlRegister |= (select << 12);
}

Memc::PageSize Memc::GetPageSize()
{
    auto size = static_cast<PageSize>((controlRegister & PageSizeMask) >> 2);
    DEBUG("Getting memory page size: ", pageSizeStrings[size]);
    return size;
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
