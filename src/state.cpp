/*
 * File: state.cpp
 * Author: dgrubb
 * Date:25/04/2018
 */

/* Library includes */
#include <stddef.h>
#include <string>
#include <pthread.h>

/* Project includes */
#include "acorn/A3000.h"
#include "lock.h"
#include "state.h"

using namespace std;

pthread_mutex_t lock;
State* State::m_pInterfaces = NULL;

typedef struct {
    string  config_file;
    Timers  *pTimers;
    Display *pDisplay;
    int     cpu_frequency;
    int     ram_size;
    string  rom_file;
} InterfacesTable;

InterfacesTable DefaultTable = {
    SETTINGS_DEFAULT_FILE,  // Configuration file path
    NULL,                   // Timers
    NULL,                   // Display
    A3000_CPU_FREQUENCY,    // CPU frequency
    A3000_RAM_SIZE          // RAM size
};

static InterfacesTable table = DefaultTable;

State* State::Interfaces()
{
    if (!m_pInterfaces) {
        m_pInterfaces = new State;
        pthread_mutex_init(&lock, NULL);
    }

    return m_pInterfaces;
}

int
State::SetConfigFile(string config_file)
{
    Lock locker(&lock);
    table.config_file = config_file;
    return 0;
}

int
State::GetConfigFile(string *config_file)
{
    Lock locker(&lock);
    *config_file = table.config_file;
    return 0;
}

int
State::SetCPUFrequency(int cpu_frequency)
{
    Lock locker(&lock);
    table.cpu_frequency = cpu_frequency;
    return 0;
}

int
State::GetCPUFrequency(int *cpu_frequency)
{
    Lock locker(&lock);
    *cpu_frequency = table.cpu_frequency;
    return 0;
}

int
State::SetDisplayPtr(Display *display)
{
    Lock locker(&lock);
    table.pDisplay = display;
    return 0;
}

int
State::GetDisplayPtr(Display * &display)
{
    Lock locker(&lock);
    display = table.pDisplay;
    return 0;
}

int
State::SetRAMSize(int ram_size)
{
    Lock locker(&lock);
    table.ram_size = ram_size;
    return 0;
}

int
State::GetRAMSize(int *ram_size)
{
    Lock locker(&lock);
    *ram_size = table.ram_size;
    return 0;
}


int
State::SetROMFile(string rom_file)
{
    Lock locker(&lock);
    table.rom_file = rom_file;
    return 0;
}

int
State::GetROMFile(string *rom_file)
{
    Lock locker(&lock);
    *rom_file = table.rom_file;
    return 0;
}

int
State::SetTimersPtr(Timers *timers)
{
    Lock locker(&lock);
    table.pTimers = timers;
    return 0;
}

int
State::GetTimersPtr(Timers * &timers)
{
    Lock locker(&lock);
    timers = table.pTimers;
    return 0;
}

State::~State()
{
    pthread_mutex_destroy(&lock);
}
