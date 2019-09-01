/*
 * File: rom.h
 * Author: dgrubb
 * Date: 01/09/2019
 */

#ifndef _ACORN_ROM_H
#define _ACORN_ROM_H

#define ROM_SIZE 4194304

int rom_init(char* rom_file);
int rom_load(char* rom_file);
int rom_read(uint32_t addr, uint8_t *byte);
int rom_boundry_check(uint32_t addr);

#endif /* _ACORN_ROM_H */
