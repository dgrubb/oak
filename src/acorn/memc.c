/*
 * File: memc.c
 * Author: dgrubb
 * Date: 26/06/2019
 */

/* Project includes */
#include "A3000.h"
#include "memc.h"
#include "debug.h"

static uint32_t rom_start_address = 0x0000000;
static const memc_device_map_entry_t read_memory_map[] = {
    { LOGICAL_RAM,  MEMC_MEMMAP_LOGICAL_RAM_START,      MEMC_MEMMAP_LOGICAL_RAM_END},
    { PHYSICAL_RAM, MEMC_MEMMAP_PHYSICAL_RAM_START,     MEMC_MEMMAP_PHYSICAL_RAM_END},
    { IOC,          MEMC_MEMMAP_IO_CONTROLLERS_START,   MEMC_MEMMAP_IO_CONTROLLERS_END},
    { LOW_ROM,      MEMC_MEMMAP_ROM_LOW_START,          MEMC_MEMMAP_ROM_LOW_END},
    { HIGH_ROM,     MEMC_MEMMAP_ROM_HIGH_START,         MEMC_MEMMAP_ROM_HIGH_END},
    { ALL_DEVICES,  0,                                  0}
};
static const memc_device_map_entry_t write_memory_map[] = {
    { LOGICAL_RAM,  MEMC_MEMMAP_LOGICAL_RAM_START,      MEMC_MEMMAP_LOGICAL_RAM_END},
    { PHYSICAL_RAM, MEMC_MEMMAP_PHYSICAL_RAM_START,     MEMC_MEMMAP_PHYSICAL_RAM_END},
    { IOC,          MEMC_MEMMAP_IO_CONTROLLERS_START,   MEMC_MEMMAP_IO_CONTROLLERS_END},
    { VIDC,         MEMC_MEMMAP_VIDEO_CONTROLLER_START, MEMC_MEMMAP_VIDEO_CONTROLLER_END},
    { MEMC,         MEMC_MEMMAP_MEMC_CTRL_DMA_START,    MEMC_MEMMAP_ADDRESS_TRANS_END},
    { ALL_DEVICES,  0,                                  0}
};
static const memc_device_map_entry_t reset_read_memory_map[] = {
    { LOGICAL_RAM,  MEMC_MEMMAP_LOGICAL_RAM_START,      MEMC_MEMMAP_LOGICAL_RAM_END},
    { PHYSICAL_RAM, MEMC_MEMMAP_PHYSICAL_RAM_START,     MEMC_MEMMAP_PHYSICAL_RAM_END},
    { IOC,          MEMC_MEMMAP_IO_CONTROLLERS_START,   MEMC_MEMMAP_IO_CONTROLLERS_END},
    { LOW_ROM,      MEMC_MEMMAP_ROM_LOW_START,          MEMC_MEMMAP_ROM_LOW_END},
    { HIGH_ROM,     MEMC_MEMMAP_ROM_HIGH_START,         MEMC_MEMMAP_ROM_HIGH_END},
    { ALL_DEVICES,  0,                                  0}
};
static const memc_device_map_entry_t reset_write_memory_map[] = {
    { LOGICAL_RAM,  MEMC_MEMMAP_LOGICAL_RAM_START,      MEMC_MEMMAP_LOGICAL_RAM_END},
    { PHYSICAL_RAM, MEMC_MEMMAP_PHYSICAL_RAM_START,     MEMC_MEMMAP_PHYSICAL_RAM_END},
    { IOC,          MEMC_MEMMAP_IO_CONTROLLERS_START,   MEMC_MEMMAP_IO_CONTROLLERS_END},
    { VIDC,         MEMC_MEMMAP_VIDEO_CONTROLLER_START, MEMC_MEMMAP_VIDEO_CONTROLLER_END},
    { MEMC,         MEMC_MEMMAP_MEMC_CTRL_DMA_START,    MEMC_MEMMAP_ADDRESS_TRANS_END},
    { ALL_DEVICES,  0,                                  0}
};

static entry_map_t *write_map = &reset_write_memory_map;
static entry_map_t *read_map = &reset_write_memory_map;
static memc_mode_t current_mode = MEMC_MODE_SUPERVISOR;

int
memc_init()
{
    return memc_reset();
}

int
memc_reset()
{
    DBG_PRINT((DBG_VERBOSE, "Reset\n"));

    /* From the MEMC datasheet, page 12:
     * "The ARM processor starts executing code from location 0000000H after
     * RESET goes inactive. To ensure that the processor always finds valid code
     * at this location (which is normally Logically mapped RAM), MEMC continually
     * enables ROM."
     */
    rom_start_address = 0x0000000;
    write_map = &reset_write_memory_map;
    read_map = &reset_read_memory_map;

    return 0;
}

int
memc_init_system_memory_map()
{
    write_map = &write_memory_map;
    read_map = &read_memory_map;
    return 0;
}

int
memc_map_address_to_device(uint32_t address, bool rw, A3000_device_t *device)
{
    int i = 0;
    entry_map_t *map;
    if (rw) {
        map = write_map;
    } else {
        map = read_map;
    }
    while ((*map)[i].device != ALL_DEVICES) {
        if ((*map)[i].start_addr <= address && (*map)[i].end_addr >= address) {
            *device = (*map)[i].device;
            DBG_PRINT((DBG_ULTRA_VERBOSE, "Mapped address: 0x%X to device %s\n",
                        address, A3000_device_to_string(*device)));
            return 0;
        }
        i++;
    }
    DBG_PRINT((DBG_ERROR, "Unable to find read address mapping for: 0x%X\n", address));
    return -1;
}

int
memc_read(uint32_t address, uint32_t *data)
{
    return 0;
}

int
memc_write(uint32_t address, uint32_t data)
{
    return 0;
}

int
memc_get_mode(memc_mode_t *mode)
{
    *mode = current_mode;
    return 0;
}

int
memc_set_mode(memc_mode_t mode)
{
    current_mode = mode;
    return 0;
}
