/*
 * File: settings.cpp
 * Author: dgrubb
 * Date:26/04/2018
 */

/* Library includes */
#include <libconfig.h++>

/* Project includes */
#include "settings.h"
#include "debug.h"

using namespace std;
using namespace libconfig;

Settings DefaultSettings = {
    "./risocs-3.71.rom",    // rom_file
    2048,                   // ram_size
    8000000,                // cpu_frequency
    DBG_LVL_INFO,           // log_level
};

int
settings_get_defaults(Settings &settings)
{
    settings.rom_file = DefaultSettings.rom_file;
    settings.ram_size = DefaultSettings.ram_size;
    settings.cpu_frequency = DefaultSettings.cpu_frequency;
    settings.log_level = DefaultSettings.log_level;
    return 0;
}

int
settings_read_file(const char* file_path, Settings &settings)
{
    Config cfg;
    settings_get_defaults(settings);
    // N.B: the user may have invoked a specific log level through the
    // command line, so don't overwrite this value but use the current setting
    get_debug_level(settings.log_level);

    DBG_PRINT((DBG_INFO, "Reading configuration file: %s\n", file_path));

    try {
        cfg.readFile(file_path);
    } catch (const FileIOException &fioex){
        DBG_PRINT((DBG_ERROR, "I/O error reading settings file: %s\n", file_path));
        return -1;
    } catch (const ParseException &pex) {
        DBG_PRINT((DBG_ERROR, "Error parsing settings file [ %s ]:\n\t%d: %s\n",
                    file_path, pex.getLine(), pex.getError()));
        return -1;
    }

    try {
        cfg.lookupValue("rom_file", settings.rom_file);
    } catch (const SettingNotFoundException &nfex) {
        DBG_PRINT((DBG_VERBOSE, "rom_file argument absent from configuration file\n"));
    }

    try {
        cfg.lookupValue("ram_size", settings.ram_size);
    } catch (const SettingNotFoundException &nfex) {
        DBG_PRINT((DBG_VERBOSE, "ram_size argument absent from configuration file\n"));
    }

    try {
        cfg.lookupValue("cpu_frequency", settings.cpu_frequency);
    } catch (const SettingNotFoundException &nfex) {
        DBG_PRINT((DBG_VERBOSE, "cpu_frequency argument absent from configuration file\n"));
    }


    if (DBG_LVL_DEFAULT == settings.log_level) {
        // Only read this setting if the user hasn't intentionally overriden it
        // at the command line
        try {
            cfg.lookupValue("log_level", settings.log_level);
        } catch (const SettingNotFoundException &nfex) {
            DBG_PRINT((DBG_VERBOSE, "log_level argument absent from configuration file\n"));
        }
    }

    return 0;
}

int
settings_apply(Settings &settings)
{
}

int
settings_print(Settings &settings)
{
    DBG_PRINT((DBG_INFO, SETTINGS_PRINT_TEMPLATE,
        settings.rom_file.c_str(),
        settings.ram_size,
        settings.cpu_frequency,
        settings.log_level
    ));
    return 0;
}
