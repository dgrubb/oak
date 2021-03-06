/*
 * File: A3000.cpp
 * Author: dgrubb
 * Date: 10/03/2019
 */

/* Library includes */
#include <stdbool.h>

/* State machine project includes */
#include "A3000.h"
#include "arm2/arm2.h"
#include "ioc.h"
#include "memc.h"
#include "ram.h"
#include "rom.h"
#include "vidc.h"

/* Project includes */
#include "display.h"
#include "oak.h"
#include "state.h"
#include "debug.h"

int
A3000_init()
{
    uint32_t ram_size;
    /* Ingest ROM file */
    char rom_file[STATE_MAX_PATH_LEN] = { 0 };
    state_get_ROM_file(rom_file);
    if (rom_init(rom_file)) {
        DBG_PRINT((DBG_ERROR, "Unable to initialise ROM.\n"));
        return -1;
    }

    /* Start emulated components */
    state_get_ram_size(&ram_size);
    if (ram_init(ram_size)) {
        DBG_PRINT((DBG_ERROR, "Unable to initialise RAM.\n"));
        return -1;
    }
    if (arm2_init()) {
        DBG_PRINT((DBG_ERROR, "Unable to initialise ARM2.\n"));
        return -1;
    }
    if (ioc_init()) {
        DBG_PRINT((DBG_ERROR, "Unable to initialise input/output controller.\n"));
        return -1;
    }
    if (memc_init()) {
        DBG_PRINT((DBG_ERROR, "Unable to initialise memory controller.\n"));
        return -1;
    }
    if (vidc_init()) {
        DBG_PRINT((DBG_ERROR, "Unable to initialise video controller.\n"));
        return -1;
    }

    return 0;
}

int
A3000_deinit()
{
    return 0;
}

int
A3000_clock()
{
    uint32_t address, data;
    bool rw;

    /* ARM generates all the addressing and, when in write mode, the content
     * of the data bus so clock it first
     */
    arm2_clock();

    /* Read the address bus value from the processor and load it into the MEMC.
     * In most cases this will be combined with the R/W pin and translated into
     * memory mapped RAM, ROM, or peripheral device.
     */
    arm2_get_address_bus(&address);

    /* Read from our source of data - the direction of which is defined by the RW
     * pin on the ARM
     */
    arm2_get_read_write(&rw);
    if (rw) {
        /* Reading from the CPU to send data or instruction to a device */
        if (arm2_get_data_bus(&data)) {
            DBG_PRINT((DBG_ERROR, "Failed to read data from CPU\n"));
            return -1;
        }
        if (A3000_write_data_to_peripheral(address, data)) {
            DBG_PRINT((DBG_ERROR, "Failed to write to address: 0x%X\n", address));
            return -1;
        }
    } else {
        /* Reading from a device at the request of the CPU */
        if (A3000_read_data_from_peripheral(address, &data)) {
            DBG_PRINT((DBG_ERROR, "Failed to read from address: 0x%X\n", address));
            return -1;
        }
        if (arm2_set_data_bus(data)) {
            DBG_PRINT((DBG_ERROR, "Failed to write data to CPU\n"));
            return -1;
        }
    }

    /* TODO: clock all the chips now that address and data bus state have been delegated appropriately */

    

    return 0;
}

int
A3000_read_data_from_peripheral(uint32_t address, uint32_t *data)
{
    A3000_device_t addressed_device;
    memc_map_address_to_device(address, false, &addressed_device);
    switch (addressed_device)
    {
        case IOC:
            /* TODO: Access IOC's data bus facing interface */
            break;
        case LOGICAL_RAM: /* Intentional fall-through */
        case PHYSICAL_RAM:
            /* TODO: Access RAM's data bus facing interface */
            break;
        case LOW_ROM:     /* Intentional fall-through */
        case HIGH_ROM:
            break;
        case VIDC:
            /* TODO: Access VIDC's data bus facing interface */
            break;
        case DMA_ADDRESS_GENERATORS:
            /* TODO: Access DMA's data bus facing interface */
            break;
        case LOGICAL_TO_PHYSICAL_TRANSLATOR:
            /* TODO: Access translator's data bus facing interface */
            break;
        case MEMC:
            /* TODO: Access MEMC*/
            break;
        case ARM:         /* Intentional fall-through */
        case ALL_DEVICES: /* Intentional fall-through */
        default:
            DBG_PRINT((DBG_ERROR, "Illegal device requested: %d", addressed_device));
            return -1;
    }

    return 0;
}

int
A3000_write_data_to_peripheral(uint32_t address, uint32_t data)
{
    A3000_device_t addressed_device;
    memc_map_address_to_device(address, false, &addressed_device);
    switch (addressed_device)
    {
        case IOC:
            /* TODO: Access IOC's data bus facing interface */
            break;
        case LOGICAL_RAM: /* Intentional fall-through */
        case PHYSICAL_RAM:
            /* TODO: Access RAM's data bus facing interface */
            break;
        case LOW_ROM:     /* Intentional fall-through */
        case HIGH_ROM:
            break;
        case VIDC:
            /* TODO: Access VIDC's data bus facing interface */
            break;
        case DMA_ADDRESS_GENERATORS:
            /* TODO: Access DMA's data bus facing interface */
            break;
        case LOGICAL_TO_PHYSICAL_TRANSLATOR:
            /* TODO: Access translator's data bus facing interface */
            break;
        case MEMC:
            /* TODO: Access MEMC*/
            break;
        case ARM:         /* Intentional fall-through */
        case ALL_DEVICES: /* Intentional fall-through */
        default:
            DBG_PRINT((DBG_ERROR, "Illegal device requested: %d", addressed_device));
            return -1;
    }
    return 0;
}

const char* A3000_device_to_string(A3000_device_t device)
{
    switch (device)
    {
        case ARM: return "ARM";
        case MEMC: return "MEMC";
        case IOC: return "IOC";
        case LOGICAL_RAM: return "Logical RAM";
        case PHYSICAL_RAM: return "Physical RAM";
        case LOW_ROM: return "Low ROM";
        case HIGH_ROM: return "High ROM";
        case VIDC: return "VIDC";
        case DMA_ADDRESS_GENERATORS: return "DMA addresses";
        case LOGICAL_TO_PHYSICAL_TRANSLATOR: return "Logical to physical translator";
        case ALL_DEVICES: /* Intentional fall-through */
        default: return "Unknown";
    }
}
