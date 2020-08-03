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

static A3000_databus_t databus = { 0 };

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
    /* Read the address bus value from the processor and load it into the MEMC.
     * In most cases this will be combined with the R/W pin and translated into
     * memory mapped RAM, ROM, or peripheral device. However, there is some special
     * startup logic to account for where the MEMC is instructed to enable the
     * system memory map.
     */
    uint32_t cpu_address;
    arm2_get_address_bus(&cpu_address);
    memc_set_processor_address_bus(cpu_address);
    bool rw;
    arm2_get_read_write(&rw);
    memc_set_input_line(MEMC_INPUT_LINE_RW, rw);

    return 0;
}

int
A3000_get_databus(uint32_t *byte)
{
    *byte = databus.bus;
    return 0;
}

int
A3000_set_databus(uint32_t byte)
{
    databus.bus = byte;
    return 0;
}

