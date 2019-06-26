/*
 * File: A3000.cpp
 * Author: dgrubb
 * Date: 10/03/2019
 */

/* Library includes */
#include <stdbool.h>

/* State machine project includes */
#include "A3000.h"
#include "arm2/arm2.h"
#include "ioc.h"
#include "memc.h"
#include "vidc.h"

/* Project includes */
#include "display.h"
#include "oak.h"
#include "state.h"
#include "debug.h"

int
A3000_init()
{
    return 0;
}

int
A3000_deinit()
{
    return 0;
}

int
A3000_run()
{
    pthread_t A3000_threads[A3000_COUNT];
    int i;
    for (i=0; i<A3000_COUNT; i++) {
        pthread_join(A3000_threads[i], NULL);
    }
    return 0;
}
