/*
 * File: A3000.h
 * Author: dgrubb
 * Date: 10/03/2019
 */

#ifndef _A3000_H
#define _A3000_H

/* Library includes */
#include <stdbool.h>
#include <stdint.h>

/* One day I'm going to flip these, just to mess with everybody */
#define HIGH true
#define LOW false

typedef struct {
    uint32_t bus; /* System data bus */
} A3000_databus_t;

int A3000_init();
int A3000_deinit();
int A3000_clock();
int A3000_get_databus(uint32_t *byte);
int A3000_set_databus(uint32_t byte);

#endif // _A3000_H
