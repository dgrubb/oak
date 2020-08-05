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
static uint32_t ram_address = 0;
static const memc_device_map_entry_t read_memory_map[] = {
    { LOGICAL_RAM,  MEMC_MEMMAP_LOGICAL_RAM_START,    MEMC_MEMMAP_LOGICAL_RAM_END},
    { PHYSICAL_RAM, MEMC_MEMMAP_PHYSICAL_RAM_START,   MEMC_MEMMAP_PHYSICAL_RAM_END},
    { IOC,          MEMC_MEMMAP_IO_CONTROLLERS_START, MEMC_MEMMAP_IO_CONTROLLERS_END},
    { LOW_ROM,      MEMC_MEMMAP_ROM_LOW_START,        MEMC_MEMMAP_ROM_LOW_END},
    { HIGH_ROM,     MEMC_MEMMAP_ROM_HIGH_START,       MEMC_MEMMAP_ROM_HIGH_END}
};
static const memc_device_map_entry_t write_memory_map[] = {
    { LOGICAL_RAM,  MEMC_MEMMAP_LOGICAL_RAM_START,      MEMC_MEMMAP_LOGICAL_RAM_END},
    { PHYSICAL_RAM, MEMC_MEMMAP_PHYSICAL_RAM_START,     MEMC_MEMMAP_PHYSICAL_RAM_END},
    { IOC,          MEMC_MEMMAP_IO_CONTROLLERS_START,   MEMC_MEMMAP_IO_CONTROLLERS_END},
    { VIDC,         MEMC_MEMMAP_VIDEO_CONTROLLER_START, MEMC_MEMMAP_VIDEO_CONTROLLER_END},
    { MEMC,         MEMC_MEMMAP_MEMC_CTRL_DMA_START,    MEMC_MEMMAP_ADDRESS_TRANS_END}
};

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

    return 0;
}

int
memc_map_address_to_device(uint32_t address, bool rw, A3000_device_t *device)
{
    if (rw) {
       return memc_map_write_address_to_device(address, device);
    } else {
       return memc_map_read_address_to_device(address, device);
    }
}

int
memc_map_read_address_to_device(uint32_t address, A3000_device_t *device)
{
    int i;
    for (i=0; i<sizeof(read_memory_map)/sizeof(memc_device_map_entry_t); i++) {
        if (read_memory_map[i].start_addr <= address && read_memory_map[i].end_addr >= address) {
            *device = read_memory_map[i].device;
            return 0;
        }
    }
    DBG_PRINT((DBG_ERROR, "Unable to find read address mapping for: 0x%X\n", address));
    return -1;
}

int
memc_map_write_address_to_device(uint32_t address, A3000_device_t *device)
{
    int i;
    for (i=0; i<sizeof(write_memory_map)/sizeof(memc_device_map_entry_t); i++) {
        if (write_memory_map[i].start_addr <= address && write_memory_map[i].end_addr >= address) {
            *device = write_memory_map[i].device;
            return 0;
        }
    }
    DBG_PRINT((DBG_ERROR, "Unable to find write address mapping for: 0x%X\n", address));
    return -1;
}
int
memc_set_RAM_address_bus(uint32_t value)
{
    ram_address = value;
    return 0;
}

int
memc_get_RAM_address_bus(uint32_t *value)
{
    *value= ram_address;
    return 0;
}

