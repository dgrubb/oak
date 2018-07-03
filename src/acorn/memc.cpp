/*
 * File: memc.cpp
 * Author: dgrubb
 * Date:26/04/2018
 */

/* Library includes */
#include <cstdint> // Fixed-width integer types

/* Project includes */
#include "memc.h"
#include "state.h"
#include "debug.h"

int
MEMC::Init()
{
    this->m_configured = false;
}

//  TODO: the ARM can address in byte or word mode, with a mix of either MEMC or
//  the processor itself handling translation and alignment. Details are in the 
//  ARM and MEMC datasheets which will be handled at this place in code. For the
//  interim this shall be very hacky.
int
MEMC::Read(uint32_t address, uint32_t *value)
{
    A3000* a3000;
    State::Interfaces()->GetA3000Ptr(a3000);
    if (!a3000) {
        DBG_PRINT((DBG_ERROR, "Error fetching A3000 pointer\n"));
        return -1;
    }
    // When the A3000 is first started the ARM will start requesting program data
    // beginning at address 0x0. Typically, the MEMC maps ROM to 0x340000, except
    // when first started and ROM will be mapped to 0x0. See MEMC datasheet
    // section 5.4.
    if (!this->m_configured) {
        a3000->ReadROM(address, value);
        DBG_PRINT((DBG_INFO, "ROM test: address 0x%X, data 0x%X\n", address, value));
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
