/*
 * File: memc.cpp
 * Author: dgrubb
 * Date:26/04/2018
 */

/* Library includes */
#include <cstdint> // Fixed-width integer types

/* Project includes */
#include "memc.h"
#include "debug.h"

int
MEMC::Init()
{
    this->m_configured = false;
}

int
MEMC::Read(uint32_t address, uint32_t *value)
{
    // When the A3000 is first started the ARM will start requesting program data
    // beginning at address 0x0. Typically, the MEMC maps ROM to 0x340000, except
    // when first started and ROM will be mapped to 0x0. See MEMC datasheet
    // section 5.4.
    if (!this->m_configured) {
        
    }
}

int
MEMC::Write(uint32_t address, uint32_t value)
{
}

MEMC::MEMC()
{
    this->Init();
}

MEMC::~MEMC()
{}
