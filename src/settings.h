/*
 * File: settings.h
 * Author: dgrubb
 * Date:26/04/2018
 */

#ifndef _SETTINGS_H
#define _SETTINGS_H

#include <string>

#define SETTINGS_DEFAULT_FILE "./oak.cfg"
#define SETTINGS_PRINT_TEMPLATE "Using settings:\n" \
"\tROM file      [ %s ]\n" \
"\tRAM size      [ %d bytes ]\n" \
"\tCPU frequency [ %d Hz ]\n" \
"\tLogging level [ %d ]\n"
#define SETTINGS_DEFAULT_ROM "./risocs-3.71.rom"

using namespace std;

typedef struct {
    string    rom_file;
    int       ram_size;
    int       cpu_frequency;
    int       log_level;
} Settings;

int settings_apply(Settings &settings);
int settings_get_defaults(Settings &settings);
int settings_read_file(const char* file_path, Settings &settings);
int settings_print(Settings &settings);

#endif // _SETTINGS_H

