/*
 * File: ram.c
 * Author: dgrubb
 * Date: 01/09/2019
 */

/* Library includes */
#include <stdint.h> /* uint8_t */
#include <stdlib.h> /* calloc() */

/* Project includes */
#include "ram.h"
#include "debug.h"

static uint8_t *ram;
static uint32_t ram_size;

int
ram_init(uint32_t new_ram_size)
{
    ram_size = new_ram_size;
    ram = (uint8_t*)calloc(ram_size, sizeof(uint8_t));
    if (NULL == ram) {
        DBG_PRINT((DBG_ERROR, "Failed to allocate [ %d ] bytes for RAM\n", ram_size));
        return -1;
    }
    return 0;
}

int
ram_get_size(uint32_t *size)
{
    *size = ram_size;
    return 0;
}

int
ram_read_byte(uint32_t addr, uint8_t *byte)
{
    if (ram_boundry_check(addr)) return -1;
    *byte = ram[addr];
    DBG_PRINT((DBG_ULTRA_VERBOSE, "Read byte [ 0x%X ] from RAM address: 0x%X\n", addr, *byte));
    return 0;
}

int
ram_write_byte(uint32_t addr, uint8_t byte)
{
    if (ram_boundry_check(addr)) return -1;
    ram[addr] = byte;
    DBG_PRINT((DBG_ULTRA_VERBOSE, "Wrote byte [ 0x%X ] to RAM address: 0x%X\n", addr, byte));
    return 0;
}

int
ram_boundry_check(uint32_t addr)
{
    if (addr > ram_size) {
        DBG_PRINT((DBG_ERROR, "Attempting RAM access outside range [ %d ]: 0x%X\n", ram_size, addr));
        return -1;
    }
    return 0;

}
