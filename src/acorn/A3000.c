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
    /* Ingest ROM file */
    char rom_file[STATE_MAX_PATH_LEN] = { 0 };
    state_get_ROM_file(rom_file);
    if (rom_init(rom_file)) {
        DBG_PRINT((DBG_ERROR, "Unable to initialise ROM.\n"));
        return -1;
    }

    /* Start emulated components */
    if (ram_init()) {
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
A3000_run()
{
    return 0;
}
