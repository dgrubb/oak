/*
 * File: state.h
 * Author: dgrubb
 * Date:25/04/2018
 */

#ifndef _STATE_H
#define _STATE_H

#include "timers.h"

class State {

public:

    // Constructors and destructors
    static State *Interfaces();
    ~State();

    // Methods
    int SetTimersPtr(Timers *timers);
    int GetTimersPtr(Timers * &timers);

private:

    State(){};
    State(State const&){};
    State& operator=(State const&){};
    static State *m_pInterfaces;
};

#endif // _STATE_H
