/*
 * File: memc.h
 * Author: dgrubb
 * Date: 26/06/2019
 */

#ifndef _ACORN_MEMC_H
#define _ACORN_MEMC_H

/* Library includes */
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

/* Archimedes/ARM2 address bus is only 26-bits wide. A uint32_t
 * is used for convenience so this mask is defined to access only 
 * the bits that are actually used. */
#define MEMC_ADDRESS_BUS                   0x0FFFFFFF

typedef struct {
    A3000_device_t device;
    uint32_t start_addr;
    uint32_t end_addr;
} memc_device_map_entry_t;

/* MEMC worker functions */
int memc_init();
int memc_reset();
int memc_map_address_to_device(uint32_t address, bool rw, A3000_device_t *device);
int memc_set_RAM_address_bus(uint32_t value);
int memc_get_RAM_address_bus(uint32_t *value);

#endif /* _ACORN_MEMC_H */
