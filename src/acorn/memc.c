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

