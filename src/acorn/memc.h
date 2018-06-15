/*
 * File: memc.h
 * Author: dgrubb
 * Date:26/04/2018
 */

#ifndef _MEMC_H
#define _MEMC_H

enum MEMC_Mode {
    MEMC_SVC = 0,
    MEMC_OS,
    MEMC_USER
};

enum MEMC_MemoryMap {
    MEMC_LOGICAL_RAM        = 0x0000000,
    MEMC_PHYSICAL_RAM       = 0x2000000,
    MEMC_IO_CONTROLLERS     = 0x3000000,
    MEMC_ROM_LOW            = 0x3400000,
    MEMC_ROM_HIGH           = 0x3800000,
    MEMC_VIDC               = 0x3400000,
    MEMC_CONTROL_DMA_ACCESS = 0x3600000,
    MEMC_ADDRESS_TRANSLATOR = 0x3800000,
    MEMC_END                = 0x3FFFFFF
};

class MEMC {

public:

    // Constructors and destructors
    MEMC();
    ~MEMC();

    // Methods
    int Init();
    int Write(uint32_t address, uint32_t value);
    int Read(uint32_t address, uint32_t *value);

private:

    // Data
    MEMC_Mode m_mode;
    bool m_configured;

    // Methods
};

#endif // _MEMC_h
