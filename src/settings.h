/*
 * File: settings.h
 * Author: dgrubb
 * Date: 05/03/2010
 */

#ifndef _SETTINGS_H
#define _SETTINGS_H

#define SETTINGS_MAX_ITEM_LEN 200
#define SETTINGS_PRINT_TEMPLATE "Using settings:\n" \
"\tROM file      [ %s ]\n" \
"\tRAM size      [ %d bytes ]\n" \
"\tCPU frequency [ %d Hz ]\n" \
"\tLogging level [ %s ]\n"

int settings_read_file(char *config_file);
int settings_print();

#endif /* _SETTINGS_H */
