/*
 * File: Timers.cpp
 * Author: dgrubb
 * Date:24/04/2018
 */

/* Library includes */
#include <errno.h>
#include <signal.h>
#include <cstring>

/* Project includes */
#include "timers.h"
#include "state.h"
#include "debug.h"

using namespace std;

static void info_signal_handler(int sig, siginfo_t *si, void *uc)
{
    Timers *timers;
    DBG_PRINT((DBG_ULTRA_VERBOSE, "Timer signal handler called, index: %d\n",
                si->si_value.sival_int));
    if (-1 != State::Interfaces()->GetTimersPtr(timers)) {
        timers->ExecuteCallback(si->si_value.sival_int);
    } else {
        DBG_PRINT((DBG_ERROR, "Error executing signal handler, no timers instance\n"));
    }
}

int
Timers::CreateTimer(int expire_ns, int interval_ns, void (*callback)(void*), void* data)
{
    DBG_PRINT((DBG_INFO,
        "Creating timer, interval [ %dns, %2.2fms ], expiration [ %dns, %2.2fms ]\n",
        interval_ns, (float)(interval_ns/NS_IN_MS), expire_ns,
        (float)(expire_ns/NS_IN_MS)));
    timer_t timer;
    struct sigevent alarm;
    struct itimerspec timer_settings;
    struct sigaction sig_action;
    int sig_num = SIGRTMIN;
    int timer_index = this->m_timers.size();

    sigemptyset(&sig_action.sa_mask);
    sig_action.sa_flags = SA_SIGINFO;
    sig_action.sa_sigaction = info_signal_handler;
    if (-1 == sigaction(sig_num, &sig_action, NULL)) {
        DBG_PRINT((DBG_ERROR, "Error setting up timer signal [ %s ]\n", strerror(errno)));
        return -1;
    }

    alarm.sigev_notify = SIGEV_SIGNAL;
    alarm.sigev_signo = sig_num;
    alarm.sigev_value.sival_ptr = &this->m_timers;
    alarm.sigev_value.sival_int = timer_index;
    if (-1 == timer_create(CLOCK_MONOTONIC, &alarm, &timer)) {
        DBG_PRINT((DBG_ERROR, "Error creating timer [ %s ]\n",
            strerror(errno)));
        return -1;
    }

    timer_settings.it_interval.tv_sec = 0;
    timer_settings.it_interval.tv_nsec = interval_ns;
    timer_settings.it_value.tv_sec = 0;
    timer_settings.it_value.tv_nsec = expire_ns;

    if (-1 == timer_settime(timer, 0, &timer_settings, NULL)) {
        DBG_PRINT((DBG_ERROR, "Error set timer [ %s ]\n", strerror(errno)));
        return -1;
    }

    TimerCallback callback_container = {timer, callback, data};

    this->m_timers[timer_index] = callback_container;

    return timer_index;
}

int
Timers::GetTimerCallbackEntry(int timer_index, TimerCallback &callback)
{
    map<int, TimerCallback>::iterator it = this->m_timers.find(timer_index);
    if (it != this->m_timers.end()) {
        callback = this->m_timers.find(timer_index)->second;
        return 0;
    } else {
        DBG_PRINT((DBG_ERROR, "Cannot find timer with index [ %d ]\n", timer_index));
    }
    return -1;
}

int
Timers::ExecuteCallback(int timer_index)
{
    TimerCallback timer_callback;
    if (-1 == GetTimerCallbackEntry(timer_index, timer_callback)) {
        DBG_PRINT((DBG_ERROR, "Unable to find callback entry\n"));
        return -1;
    }

    if (NULL == timer_callback.func) {
        DBG_PRINT((DBG_ERROR, "Callback entry has no callback function\n"));
        return -1;
    }

    timer_callback.func(timer_callback.data);
    return 0;
}

int
Timers::SetTimer(int timer_index, struct itimerspec set_timer)
{
    TimerCallback timer_callback;
    if (-1 == GetTimerCallbackEntry(timer_index, timer_callback)) {
        return -1;
    }

    if (-1 != timer_settime(timer_callback.timer, 0, &set_timer, NULL)) {
        DBG_PRINT((DBG_INFO, "Set timer [ %d ]\n", timer_index));
        return 0;
    } else {
        DBG_PRINT((DBG_INFO, "Error starting timer [ %d ]:\n%s\n", timer_index, strerror(errno)));
    }
    return -1;
}

int
Timers::StopTimer(int timer_index)
{
    struct itimerspec clear_timer = {0,0};
    TimerCallback timer_callback;
    if (-1 == GetTimerCallbackEntry(timer_index, timer_callback)) {
        return -1;
    }

    if (-1 != timer_settime(timer_callback.timer, 0, &clear_timer, NULL)) {
        DBG_PRINT((DBG_INFO, "Stopped timer [ %d ]\n", timer_index));
        return 0;
    } else {
        DBG_PRINT((DBG_INFO, "Error stopping timer [ %d ]:\n%s\n", timer_index, strerror(errno)));
    }
    return -1;
}

int
Timers::DestroyTimer(int timer_index)
{
    StopTimer(timer_index);

    TimerCallback timer_callback;
    if (-1 == GetTimerCallbackEntry(timer_index, timer_callback)) {
        return -1;
    }

    if (-1 != timer_delete(timer_callback.timer)) {
        map<int, TimerCallback>::iterator it = this->m_timers.find(timer_index);
        if (it != this->m_timers.end()) {
            this->m_timers.erase(it);
        }
        DBG_PRINT((DBG_INFO, "Deleted timer [ %d ]\n", timer_index));
        return 0;
    } else {
        DBG_PRINT((DBG_ERROR, "Error deleting timer [ %d ]\n%s\n", timer_index, strerror(errno)));
    }
    return -1;
}

void
Timers::ListTimers()
{
    DBG_PRINT((DBG_INFO, "Timer count: %d\n", this->m_timers.size()));
    for (map<int, TimerCallback>::iterator it=this->m_timers.begin(); it != this->m_timers.end(); ++it) {
        DBG_PRINT((DBG_INFO, "Timer ID: [ %d ] [ %d ]\n", it->first, it->second));
    }
}

Timers::Timers()
{
    DBG_PRINT((DBG_VERBOSE, "Creating Timers object\n"));
    this->m_timers.clear();
}

Timers::~Timers()
{
    DBG_PRINT((DBG_VERBOSE, "Destroyed Timers object\n"));
    while (!this->m_timers.empty()) {
        DestroyTimer(this->m_timers.rbegin()->first);
    }
}

