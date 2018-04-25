/*
 * File: lock.h
 * Author: dgrubb
 * Date:25/04/2018
 */

#ifndef _LOCK_H
#define _LOCK_H

#include <pthread.h>

class Lock {

public:

    // Constructors and destructors
    Lock(pthread_mutex_t *lock);
    ~Lock();

    // Methods
    void Relock();
    void Unlock();
    pthread_mutex_t* Mutex();

private:

    // Private data
    pthread_mutex_t *m_pLock;
    bool locked;
};

#endif // _LOCK_H
