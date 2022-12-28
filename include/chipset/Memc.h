// File: Memc.h
// Author: dgrubb
// Date: 22/12/2022
//
// Provides a class for describing the A3000's
// memory controller

#ifndef MEMC_H
#define MEMC_H

// C++ header includes
#include <array> // std::array

// Project includes
#include "Device.h"

class Memc: public Device
{
public:

    enum PageSize
    {
        FourKBytes = 0, // 00
        EightKBytes,    // 01
        SixteenKBytes,  // 10
        ThirtyTwoKBytes // 11
    };

    enum OSModeSelect
    {
        OSModeDeselected = 0,
        OSModeSelected
    };

    static constexpr uint32_t AddressLookupTableSize = 128;
    static constexpr uint32_t PageSizeMask = 0x00000005;
    static constexpr uint32_t OSModeSelectMask = 0x00001000;

    struct AddressTranslator
    {
        std::array<uint32_t, AddressLookupTableSize> lookupTable = {0};
    };

    Memc(std::shared_ptr<Device::SystemBus> systemBus_);
    ~Memc();

private:

    static const char* osModeSelectStrings[];
    static const char* pageSizeStrings[];

    AddressTranslator addressTranslator;
    uint32_t controlRegister{0};

    OSModeSelect GetOSModeSelect();
    void SetOSModeSelect(OSModeSelect select);
    PageSize GetPageSize();
    void SetPageSize(PageSize size);

    void DoTick() override;
};

#endif // MEMC_H
