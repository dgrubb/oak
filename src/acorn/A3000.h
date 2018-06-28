/*
 * File: A3000.h
 * Author: dgrubb
 * Date:24/04/2018
 */

#ifndef _A3000_H
#define _A3000_H

/* Library includes */
#include <cstddef> // NULL
#include <string>
#include <vector>

/* Project includes */
#include "arm.h"
#include "ioc.h"
#include "memc.h"
#include "vidc.h"

using namespace std;

#define A3000_SCREEN_WIDTH  800     // pixels
#define A3000_SCREEN_HEIGHT 600     // pixels
#define A3000_CPU_FREQUENCY 8000000 // Hz
#define A3000_RAM_SIZE      2048    // bytes

#define NS_PER_CYCLE        1000000000

class A3000 {

public:

    // Constructors and destructors
    A3000(int cpu_frequency, int ram_size, string rom_path);
    A3000();
    ~A3000();

    // Methods
    int Init(int cpu_frequency, int ram_size, string rom_path);
    int InitError();
    int LoadROM(string rom_path);
    int ClockTick();
    int ReadRAM(uint32_t address, uint32_t *value);
    int WriteRAM(uint32_t address, uint32_t value);
    int ReadROM(uint32_t address, uint32_t *value);
    int Reset();

private:

    // Data
    ARM *m_cpu = NULL;
    IOC *m_ioc = NULL;
    MEMC *m_memc = NULL;
    VIDC *m_vidc = NULL;
    bool m_init_error = false;
    bool m_master_clock = false;
    int m_cpu_frequency;
    int m_ram_size;
    int m_clock_timer_index;
    vector<uint8_t> m_ram;
    vector<uint8_t> m_rom;
};

#endif // _A3000_H
