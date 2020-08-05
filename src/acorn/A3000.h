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
int A3000_get_data_bus(uint32_t *byte);
int A3000_set_data_bus(uint32_t byte);
const char* A3000_device_to_string(A3000_device_t device);

#endif // _A3000_H
