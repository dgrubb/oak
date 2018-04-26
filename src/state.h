/*
 * File: state.h
 * Author: dgrubb
 * Date:25/04/2018
 */

#ifndef _STATE_H
#define _STATE_H

#include "display.h"
#include "settings.h"
#include "timers.h"

using namespace std;

class State {

public:

    // Constructors and destructors
    static State *Interfaces();
    ~State();

    // Methods
    int SetConfigFile(string config_file);
    int GetConfigFile(string *config_file);
    int SetDisplayPtr(Display *display);
    int GetDisplayPtr(Display * &display);
    int SetTimersPtr(Timers *timers);
    int GetTimersPtr(Timers * &timers);

private:

    State(){};
    State(State const&){};
    State& operator=(State const&){};
    static State *m_pInterfaces;
};

#endif // _STATE_H
