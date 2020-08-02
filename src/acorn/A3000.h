/*
 * File: A3000.h
 * Author: dgrubb
 * Date: 10/03/2019
 */

#ifndef _A3000_H
#define _A3000_H

/* Library includes */
#include <stdbool.h>

/* One day I'm going to flip these, just to mess with everybody */
#define HIGH true
#define LOW false

int A3000_init();
int A3000_deinit();
int A3000_clock();

#endif // _A3000_H
