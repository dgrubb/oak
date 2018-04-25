/*
 * File: timers.h
 * Author: dgrubb
 * Date:24/04/2018
 */

#ifndef _TIMERS_H
#define _TIMERS_H

#include <map>
#include <time.h>

#define NS_IN_MS 1000000

typedef void (*callback)(void*);
typedef struct {
    timer_t     timer;
    callback    func;
    void*       data;
} TimerCallback;

class Timers {

public:

    // Constructors and destructors
    Timers();
    ~Timers();

    // Methods
    int CreateTimer(int expire_ns, int interval_ns, void (*callback)(void*), void* data);
    int DestroyTimer(int timer_index);
    int SetTimer(int timer_index, struct itimerspec set_timer);
    int StopTimer(int timer_index);
    void ListTimers();
    int ExecuteCallback(int timer_index);

private:

    // Methods
    int GetTimerCallbackEntry(int timer_index, TimerCallback &callback);

    // Data
    map<int, TimerCallback> m_timers;
};

#endif // _TIMERS_H
