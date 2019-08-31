/*
 * File: memc.c
 * Author: dgrubb
 * Date: 26/06/2019
 */

/* Library includes */
#include <stddef.h>

/* Project includes */
#include "memc.h"

int
memc_init()
{
    return memc_reset();
}

int
memc_reset()
{
    /* TODO: Read the datasheet more thoroughly to figure out
     * what these should really be on RESET condition. For the time
     * being just put them to something sensible.
     */
    memc_i_a = 0;
    memc_i_rw = false;
    memc_i_bw = false;
    memc_i_seq = false;
    memc_i_spvmd = false;

    memc_o_ph1 = false;
    memc_o_ph2 = false;
    memc_o_ra = 0;
    /* From the MEMC datasheet, page 12:
     * "The ARM processor starts executing code from location 0000000H after
     * RESET goes inactive. To ensure that the processor always finds valid code
     * at this location (which is normally Logically mapped RAM), MEMC continually
     * enables ROM."
     */
    memc_o_romcs = true;

    return 0;
}
