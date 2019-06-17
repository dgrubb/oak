/*
 * File: settings.c
 * Author: dgrubb
 * Date: 05/03/2019
 */

/* Library includes */
#include <libconfig.h>
#include <string.h>

/* Project includes */
#include "settings.h"
#include "state.h"
#include "debug.h"

int
settings_read_file(char *config_file)
{
    config_t cfg;
    int log_level, ram_size, cpu_frequency;
    bool arg_override;
    const char *rom_file;

    DBG_PRINT((DBG_INFO, "Reading configuration file: %s\n", config_file));

    config_init(&cfg);
    if (!config_read_file(&cfg, config_file)) {
        DBG_PRINT((DBG_ERROR, "Unable to read configuration file: %s\n", config_file));
        DBG_PRINT((DBG_ERROR, "%s:%d - %s\n",
                    config_error_file(&cfg),
                    config_error_line(&cfg),
                    config_error_text(&cfg)));
        config_destroy(&cfg);
        return -1;
    }

    /* If the user has supplied the location of a ROM file via command line
     * arguments then don't attempt to read one from the configuration file.
     * Supplying the argument is a concious action so implies that's a better
     * signal of the user's intentions.
     */
    state_get_ROM_file_arg_override(&arg_override);
    if (!arg_override) {
        if (config_lookup_string(&cfg, "rom_file", &rom_file)) {
            state_set_ROM_file(rom_file);
            DBG_PRINT((DBG_VERBOSE, "New ROM file location loaded from config file: %s\n", rom_file));
        } else {
            DBG_PRINT((DBG_VERBOSE, "No ROM file specified in config file, using default.\n"));
        }
    }
    /* See previous note regarding user override */
    state_get_debug_arg_override(&arg_override);
    if (!arg_override) {
        if (config_lookup_int(&cfg, "log_level", &log_level)) {
            if (-1 != validate_debug_level(log_level)) {
                set_debug_level(log_level);
            } else {
                DBG_PRINT((DBG_WARNING, "Config file supplies an invalid log level: %d\n", log_level));
            }
        } else {
            DBG_PRINT((DBG_VERBOSE, "No log level specified in config file, using default.\n"));
        }
    }

    /* Load emulator settings */
    if (config_lookup_int(&cfg, "ram_size", &ram_size)) {
        state_set_ram_size((uint32_t)ram_size);
        DBG_PRINT((DBG_VERBOSE, "New RAM size loaded from config file: %d bytes\n", ram_size));
    } else {
        DBG_PRINT((DBG_VERBOSE, "No RAM size specified in config file, using default.\n"));
    }
    if (config_lookup_int(&cfg, "cpu_frequency", &cpu_frequency)) {
        state_set_cpu_frequency((uint32_t)cpu_frequency);
        DBG_PRINT((DBG_VERBOSE, "New CPU frequency loaded from config file: %d Hz\n", cpu_frequency));
    } else {
        DBG_PRINT((DBG_VERBOSE, "No CPU frequency specified in config file, using default.\n"));
    }

    config_destroy(&cfg);
    return 0;
}

int
settings_print()
{
    uint32_t ram_size, cpu_frequency;
    int log_level;
    char rom_file[STATE_MAX_PATH_LEN];

    state_get_ROM_file(rom_file);
    state_get_ram_size(&ram_size);
    state_get_cpu_frequency(&cpu_frequency);
    get_debug_level(&log_level);

    DBG_PRINT((DBG_INFO, SETTINGS_PRINT_TEMPLATE,
        rom_file,
        ram_size,
        cpu_frequency,
        get_debug_level_string(log_level)
    ));
    return 0;
}
