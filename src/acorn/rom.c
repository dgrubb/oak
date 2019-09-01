/*
 * File: rom.c
 * Author: dgrubb
 * Date: 01/09/2019
 */

/* Library includes */
#include <errno.h>  /* errno */
#include <stdint.h> /* uint8_t */
#include <stdio.h>  /* FILE, fread(), feof(), ferror(), fclose(), perror() */
#include <string.h> /* strerror() */

/* Project includes */
#include "rom.h"
#include "debug.h"

static uint8_t rom[ROM_SIZE] = {0};

int
rom_init(char* rom_file)
{
    return rom_load(rom_file);
}

int
rom_load(char *rom_file)
{
    errno = 0;
    int bytes = 0;
    int index = 0;
    FILE *fp;

    DBG_PRINT((DBG_INFO, "Opening ROM file: %s\n", rom_file));
    fp = fopen(rom_file, "rb");
    if (NULL == fp) {
        DBG_PRINT((DBG_ERROR, "Unable to open ROM file [ %s ]: %s\n", rom_file, strerror(errno)));
        return -1;
    }

    while (bytes += fread(&rom[index], sizeof(uint8_t), 1, fp), !feof(fp) && !ferror(fp)) {
        index++;
    }

    if (ferror(fp)) {
        perror("Failed to read from ROM file");
        fclose(fp);
        return -1;
    }

    fclose(fp);

    DBG_PRINT((DBG_VERBOSE, "Read [ %d bytes ] from  ROM file: %s\n", bytes, rom_file));
    return 0;
}
