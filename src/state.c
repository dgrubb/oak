/*
 * File: state.cpp
 * Author: dgrubb
 * Date: 05/03/2019
 */

/* Library includes */
#include <stddef.h>
#include <string.h>
#include <pthread.h>

/* Project includes */
#include "state.h"
#include "util.h"

pthread_mutex_t lock;

const InterfacesTable DefaultTable = {
    DEFAULT_CONFIG_FILE,
    DEFAULT_ROM_FILE,
    A3000_CPU_FREQUENCY,
    A3000_RAM_SIZE,
    false,                  // Rom file overriden
    false,                  // Log level overriden
    false,                  // Fullscreen
    false,                  // Minimised
    false,                  // Mouse focus
    false                   // Keyboard focus
};

InterfacesTable state_table;

int
state_init()
{
    state_table = DefaultTable;
    return 0;
}

int
state_set_config_file(const char *config_file)
{
    pthread_mutex_lock(&lock);
    util_copy_file_path_string(state_table.config_file, config_file);
    pthread_mutex_unlock(&lock);
    return 0;
}

int
state_get_config_file(char *config_file)
{
    pthread_mutex_lock(&lock);
    util_copy_file_path_string(config_file, state_table.config_file);
    pthread_mutex_unlock(&lock);
    return 0;
}

int
state_set_ROM_file(const char *rom_file)
{
    pthread_mutex_lock(&lock);
    util_copy_file_path_string(state_table.rom_file, rom_file);
    pthread_mutex_unlock(&lock);
    return 0;
}

int
state_get_ROM_file(char *rom_file)
{
    pthread_mutex_lock(&lock);
    util_copy_file_path_string(rom_file, state_table.rom_file);
    pthread_mutex_unlock(&lock);
    return 0;
}

int
state_set_ROM_file_arg_override(bool arg_override)
{
    pthread_mutex_lock(&lock);
    state_table.rom_file_arg_override = arg_override;
    pthread_mutex_unlock(&lock);
    return 0;
}

int
state_get_ROM_file_arg_override(bool *arg_override)
{
    pthread_mutex_lock(&lock);
    *arg_override = state_table.rom_file_arg_override;
    pthread_mutex_unlock(&lock);
    return 0;
}

int
state_set_debug_arg_override(bool arg_override)
{
    pthread_mutex_lock(&lock);
    state_table.debug_arg_override = arg_override;
    pthread_mutex_unlock(&lock);
    return 0;
}

int
state_get_debug_arg_override(bool *arg_override)
{
    pthread_mutex_lock(&lock);
    *arg_override = state_table.debug_arg_override;
    pthread_mutex_unlock(&lock);
    return 0;
}

int
state_set_ram_size(uint32_t ram_size)
{
    pthread_mutex_lock(&lock);
    state_table.ram_size = ram_size;
    pthread_mutex_unlock(&lock);
    return 0;
}

int
state_get_ram_size(uint32_t *ram_size)
{
    pthread_mutex_lock(&lock);
    *ram_size = state_table.ram_size;
    pthread_mutex_unlock(&lock);
    return 0;
}

int
state_set_cpu_frequency(uint32_t cpu_frequency)
{
    pthread_mutex_lock(&lock);
    state_table.cpu_frequency = cpu_frequency;
    pthread_mutex_unlock(&lock);
    return 0;
}

int
state_get_cpu_frequency(uint32_t *cpu_frequency)
{
    pthread_mutex_lock(&lock);
    *cpu_frequency = state_table.cpu_frequency;
    pthread_mutex_unlock(&lock);
    return 0;
}

int
state_set_fullscreen(bool fullscreen)
{
    pthread_mutex_lock(&lock);
    state_table.fullscreen = fullscreen;
    pthread_mutex_unlock(&lock);
    return 0;
}

int
state_get_fullscreen(bool *fullscreen)
{
    pthread_mutex_lock(&lock);
    *fullscreen = state_table.fullscreen;
    pthread_mutex_unlock(&lock);
    return 0;
}

int
state_set_minimised(bool minimised)
{
    pthread_mutex_lock(&lock);
    state_table.minimised = minimised;
    pthread_mutex_unlock(&lock);
    return 0;
}

int
state_get_minimised(bool *minimised)
{
    pthread_mutex_lock(&lock);
    *minimised = state_table.minimised;
    pthread_mutex_unlock(&lock);
    return 0;
}

int
state_set_mouse_focus(bool mouse_focus)
{
    pthread_mutex_lock(&lock);
    state_table.mouse_focus = mouse_focus;
    pthread_mutex_unlock(&lock);
    return 0;
}

int
state_get_mouse_focus(bool *mouse_focus)
{
    pthread_mutex_lock(&lock);
    *mouse_focus = state_table.mouse_focus;
    pthread_mutex_unlock(&lock);
    return 0;
}

int
state_set_keyboard_focus(bool keyboard_focus)
{
    pthread_mutex_lock(&lock);
    state_table.keyboard_focus = keyboard_focus;
    pthread_mutex_unlock(&lock);
    return 0;
}

int
state_get_keyboard_focus(bool *keyboard_focus)
{
    pthread_mutex_lock(&lock);
    *keyboard_focus = state_table.keyboard_focus;
    pthread_mutex_unlock(&lock);
    return 0;
}
