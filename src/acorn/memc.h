/*
 * File: memc.h
 * Author: dgrubb
 * Date: 26/06/2019
 */

#ifndef _ACORN_MEMC_H
#define _ACORN_MEMC_H

#include <stdbool.h> /* bool */
#include <stdint.h>  /* uint32_t */

/* System memory map
 * See MEMC Datasheet, page 9
 */
#define MEMC_MEMMAP_LOGICAL_RAM_START      0x00000000
#define MEMC_MEMMAP_LOGICAL_RAM_END        0x01FFFFFF
#define MEMC_MEMMAP_PHYSICAL_RAM_START     0x02000000
#define MEMC_MEMMAP_PHYSICAL_RAM_END       0x02FFFFFF
#define MEMC_MEMMAP_IO_CONTROLLERS_START   0x03000000
#define MEMC_MEMMAP_IO_CONTROLLERS_END     0x03FFFFFF
/* VIDC, DMA address generators and address translators
 * share the same memory address mapping as the ROM. MEMC
 * delegates access to each depending on whether it's a
 * read (ROM) or write (everything else) cycle.
 */
/* R/W = Read */
#define MEMC_MEMMAP_ROM_LOW_START          0x03400000
#define MEMC_MEMMAP_ROM_LOW_END            0x037FFFFF
#define MEMC_MEMMAP_ROM_HIGH_START         0x03800000
#define MEMC_MEMMAP_ROM_HIGH_END           0x03FFFFFF
/* R/W = Write */
#define MEMC_MEMMAP_VIDEO_CONTROLLER_START 0x03400000
#define MEMC_MEMMAP_VIDEO_CONTROLLER_END   0x035FFFFF
#define MEMC_MEMMAP_MEMC_CTRL_DMA_START    0x03600000
#define MEMC_MEMMAP_MEMC_CTRL_DMA_END      0x037FFFFF
#define MEMC_MEMMAP_ADDRESS_TRANS_START    0x03800000
#define MEMC_MEMMAP_ADDRESS_TRANS_END      0x03FFFFFF

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
