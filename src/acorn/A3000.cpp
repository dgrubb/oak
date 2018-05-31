/*
 * File: A3000.cpp
 * Author: dgrubb
 * Date:24/04/2018
 */

/* Library includes */
#include <fstream>
#include <iterator>

/* Project includes */
#include "A3000.h"
#include "debug.h"

using namespace std;

int
A3000::Reset()
{
    return 0;
}

int
A3000::Init(int cpu_frequency, int ram_size, string rom_path)
{
    DBG_PRINT((DBG_INFO, "Starting A3000 emulation with %d MHz CPU and %d Mbytes RAM\n",
                cpu_frequency/1000000, ram_size/1000000));
    this->m_cpu_frequency = cpu_frequency;
    this->m_ram_size = ram_size;
    this->m_cpu = new ARM();
    this->m_ioc = new IOC();
    this->m_memc = new MEMC();
    this->m_vidc = new VIDC();
    this->m_ram.reserve(this->m_ram_size);
    if (this->LoadROM(rom_path)) {
        this->m_init_error = true;
        return -1;
    }
    return 0;
}

int
A3000::InitError()
{
    if (this->m_init_error) {
        return -1;
    }
    return 0;
}

int
A3000::LoadROM(string rom_path)
{
    streampos rom_size;
    // Validate file
    ifstream rom_file(rom_path, ios::binary);
    if (rom_file.fail()) {
        DBG_PRINT((DBG_ERROR, "Could not open ROM file: %s\n", rom_path.c_str()));
        return -1;
    }
    rom_file.unsetf(ios::skipws);
    rom_file.seekg(0, ios::end);
    rom_size = rom_file.tellg();
    this->m_rom.reserve(rom_size);
    DBG_PRINT((DBG_INFO, "Loading ROM file [ %s ], size [ %d bytes ]\n",
                rom_path.c_str(), rom_size));

    // Now load it directly into a vector. Slower performance, but cross-platform?
    rom_file.seekg(0, ios::beg);
    this->m_rom.insert(this->m_rom.begin(), istream_iterator<uint8_t>(rom_file), istream_iterator<uint8_t>());

    return 0;
}

A3000::A3000(int cpu_frequency, int ram_size, string rom_path)
{
    this->Init(cpu_frequency, ram_size, rom_path);
}

A3000::A3000()
{
    // Default to A3000 specifications. However, defaults should already be
    // present courtesy of settings.cpp or through ingesting a configuration
    // file so, ideally, this should never be invoked. It's present for
    // completeness of this class.
    this->Init(A3000_CPU_FREQUENCY, A3000_RAM_SIZE, string("./risocs-3.71.rom"));
}

A3000::~A3000()
{
    delete this->m_cpu;
    delete this->m_ioc;
    delete this->m_memc;
    delete this->m_vidc;
}

