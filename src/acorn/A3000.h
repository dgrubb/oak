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

typedef enum {
    ARM = 0,
    MEMC,
    IOC,
    LOGICAL_RAM,
    PHYSICAL_RAM,
    LOW_ROM,
    HIGH_ROM,
    VIDC,
    DMA_ADDRESS_GENERATORS,
    LOGICAL_TO_PHYSICAL_TRANSLATOR,
    ALL_DEVICES
} A3000_device_t;

int A3000_init();
int A3000_deinit();
int A3000_clock();
int A3000_read_data_from_peripheral(uint32_t address, uint32_t *data);
int A3000_write_data_to_peripheral(uint32_t address, uint32_t data);
const char* A3000_device_to_string(A3000_device_t device);

#endif // _A3000_H
