/*
 * File: state.h
 * Author: dgrubb
 * Date: 05/03/2010
 */

#ifndef _STATE_H
#define _STATE_H

#include <stdbool.h>
#include <stdint.h>

#define DEFAULT_CONFIG_FILE "./oak.cfg"
#define DEFAULT_ROM_FILE    "./riscos-3.71.rom"
#define STATE_MAX_PATH_LEN  200
#define A3000_CPU_FREQUENCY 2000000
#define A3000_RAM_SIZE      8000000

typedef struct {
    char        config_file[STATE_MAX_PATH_LEN];
    char        rom_file[STATE_MAX_PATH_LEN];
    uint32_t    cpu_frequency;
    uint32_t    ram_size;
    bool        rom_file_arg_override;
    bool        debug_arg_override;
    bool        fullscreen;
    bool        minimised;
    bool        mouse_focus;
    bool        keyboard_focus;
} InterfacesTable;

int state_init();

/* Application state and information */
int state_set_config_file(const char *config_file);
int state_get_config_file(char *config_file);
int state_set_ROM_file(const char *rom_file);
int state_get_ROM_file(char *rom_file);
int state_set_ROM_file_arg_override(bool arg_override);
int state_get_ROM_file_arg_override(bool *arg_override);
int state_set_debug_arg_override(bool arg_override);
int state_get_debug_arg_override(bool *arg_override);
int state_set_fullscreen(bool fullscreen);
int state_get_fullscreen(bool *fullscreen);
int state_set_minimised(bool minimised);
int state_get_mouse_focus(bool *mouse_focus);
int state_set_mouse_focus(bool mouse_focus);
int state_get_keyboard_focus(bool *keyboard_focus);
int state_set_keyboard_focus(bool keyboard_focus);

/* Emulation information */
int state_set_ram_size(uint32_t ram_size);
int state_get_ram_size(uint32_t *ram_size);
int state_set_cpu_frequency(uint32_t cpu_frequency);
int state_get_cpu_frequency(uint32_t *cpu_frequency);

#endif /* _STATE_H */
