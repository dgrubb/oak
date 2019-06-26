/*
 * File: A3000.h
 * Author: dgrubb
 * Date: 10/03/2019
 */

#ifndef _A3000_H
#define _A3000_H

/* Library includes */
#include <pthread.h>

/* These are the application threads responsible for:
 * EVENT: Query and enqueue input events via SDL, also update output display.
 * ARM: State machine for ARM processor.
 * IOC: State machine for input/output controller chip.
 * MEMC: State machine for memory controller.
 * VIDC: State machine for video controller.
 */
typedef enum {
    A3000_EVENT = 0,
    A3000_ARM,
    A3000_IOC,
    A3000_MEMC,
    A3000_VIDC,
    A3000_COUNT
} A3000_thread;

int A3000_init();
int A3000_deinit();
int A3000_run();

#endif // _A3000_H
