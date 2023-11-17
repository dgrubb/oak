// File: Memc.h
// Author: dgrubb
// Date: 22/12/2022
//
// Provides a class for describing the A3000's
// memory controller

#ifndef MEMC_H
#define MEMC_H

// C++ header includes
#include <array>      // std::array
#include <functional> // std::function
#include <utility>    // std::pair

// Project includes
#include "Device.h"

class Memc final: public Device
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

    Memc(std::shared_ptr<Device::SystemBus> systemBus_);
    ~Memc();

    void Reset();

private:

    enum class MapRegions : int
    {
        LOGICAL_RAM = 0,
        PHYSICAL_RAM,
        IO,
        LOW_ROM,
        HIGH_ROM
    };

    static constexpr uint32_t AddressLookupTableSize = 128;
    static constexpr uint32_t PageSizeMask = 0x00000005;
    static constexpr uint32_t OSModeSelectMask = 0x00001000;
    static constexpr std::array<std::pair<uint32_t, uint32_t>, 5> ReadMap = {{
        // Start,   End
        {0x0000000, 0x2000000}, // Logically mapped RAM
        {0x2000001, 0x3000000}, // Physically mapped RAM
        {0x3000001, 0x3400000}, // Input/output controllers
        {0x3400001, 0x3800000}, // ROM (low)
        {0x3800001, 0x3FFFFFF}  // ROM (high)
    }};
    struct AddressTranslator
    {
        std::array<uint32_t, AddressLookupTableSize> lookupTable = {0};
    };

    static const char* osModeSelectStrings[];
    static const char* pageSizeStrings[];

    AddressTranslator addressTranslator;
    uint32_t controlRegister{0};
    std::function<MapRegions(void)> mapFunction;

    void EnableDefaultMemoryMap();
    OSModeSelect GetOSModeSelect();
    PageSize GetPageSize();
    MapRegions GetResetMemoryMapRegion();
    MapRegions GetDefaultMemoryMapRegion();
    void SetOSModeSelect(OSModeSelect select);
    void SetPageSize(PageSize size);

    void DoTick() override;
};

#endif // MEMC_H
