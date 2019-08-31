/*
 * File: memc.h
 * Author: dgrubb
 * Date: 26/06/2019
 */

#ifndef _ACORN_MEMC_H
#define _ACORN_MEMC_H

#include <stdbool.h> /* bool */
#include <stdint.h>  /* uint32_t */

/* MEMC interfaces */

/* Inputs */
uint32_t memc_i_a; /* Processor address bus */
bool memc_i_rw;    /* Processor read/write select */
bool memc_i_bw;    /* Processor byte/word access */
bool memc_i_mreq;  /* Processor memory request (n.b., next cycle) */
bool memc_i_seq;   /* Processor sequential access (n.b., next cycle) */
bool memc_i_spvmd; /* Processor set supervisor mode */

/* Outputs */
bool memc_o_ph1;    /* Processor clock, phase 1 */
bool memc_o_ph2;    /* Processor clock, phase 2 */
uint32_t memc_o_ra; /* RAM address bus (n.b., RA[0:9]) */
bool memc_o_romcs;  /* ROM select. LOW to access ROM */

/* MEMC worker functions */
int memc_init();
int memc_reset();

#endif /* _ACORN_MEMC_H */
