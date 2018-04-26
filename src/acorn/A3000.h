/*
 * File: A3000.h
 * Author: dgrubb
 * Date:24/04/2018
 */

#ifndef _A3000_H
#define _A3000_H

/* Library includes */
#include <cstddef> // NULL

/* Project includes */
#include "arm.h"
#include "ioc.h"
#include "memc.h"
#include "vidc.h"

#define A3000_SCREEN_WIDTH  800     // pixels
#define A3000_SCREEN_HEIGHT 600     // pixels
#define A3000_CPU_FREQUENCY 8000000 // Hz
#define A3000_RAM_SIZE      2048    // bytes

class A3000 {

public:

    // Constructors and destructors
    A3000(int cpu_frequency, int ram_size);
    A3000();
    ~A3000();

    // Methods
    int Init(int cpu_frequency, int ram_size);
    int Reset();

private:

    // Data
    ARM *m_cpu = NULL;
    IOC *m_ioc = NULL;
    MEMC *m_memc = NULL;
    VIDC *m_vidc = NULL;
    int m_cpu_frequency;
    int m_ram_size;
};

#endif // _A3000_H
