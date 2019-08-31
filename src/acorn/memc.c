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
    memc_o_romcs = false;

    return 0;
}
