/*
 * File: A3000.cpp
 * Author: dgrubb
 * Date:24/04/2018
 */

/* Project includes */
#include "A3000.h"
#include "arm.h"
#include "debug.h"

using namespace std;

int
A3000::Reset()
{
    return 0;
}

int
A3000::Init(int cpu_frequency, int ram_size)
{
    DBG_PRINT((DBG_INFO, "Starting A3000 emulation with %d MHz CPU and %d bytes RAM\n",
                cpu_frequency, ram_size));
    this->m_cpu_frequency = cpu_frequency;
    this->m_ram_size = ram_size;
}

A3000::A3000(int cpu_frequency, int ram_size)
{
    Init(cpu_frequency, ram_size);
}

A3000::A3000()
{
    Init(A3000_CPU_FREQUENCY, A3000_RAM_SIZE);
}

A3000::~A3000()
{
}

