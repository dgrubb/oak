/*
 * File: lock.cpp
 * Author: dgrubb
 * Date:25/04/2018
 */

/* Project includes */
#include "lock.h"
#include "debug.h"

void
Lock::Relock()
{
    pthread_mutex_lock(this->m_pLock);
    return;
}

void
Lock::Unlock()
{
    pthread_mutex_unlock(this->m_pLock);
}

pthread_mutex_t*
Lock::Mutex()
{
    return this->m_pLock;
}

Lock::Lock(pthread_mutex_t *lock)
{
    this->m_pLock = lock;
    Relock();
}

Lock::~Lock()
{
    Unlock();
}
