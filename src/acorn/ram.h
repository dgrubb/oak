/*
 * File: ram.h
 * Author: dgrubb
 * Date: 01/09/2019
 */

#ifndef _ACORN_RAM_H
#define _ACORN_RAM_H

int ram_init(uint32_t ram_size);
int ram_boundry_check(uint32_t addr);
int ram_get_size(uint32_t *size);
int ram_read_byte(uint32_t addr, uint8_t *byte);
int ram_write_byte(uint32_t addr, uint8_t byte);

#endif /* _ACORN_RAM_H */
