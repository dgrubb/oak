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
#include "lock.h"
#include "state.h"

using namespace std;

pthread_mutex_t lock;
State* State::m_pInterfaces = NULL;

typedef struct {
    string  config_file;
    Timers  *pTimers;
    Display *pDisplay;
} InterfacesTable;

InterfacesTable DefaultTable = {
    SETTINGS_DEFAULT_FILE,  // Configuration file path
    NULL,                   // Timers
    NULL                    // Display
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

State::~State()
{
    pthread_mutex_destroy(&lock);
}
