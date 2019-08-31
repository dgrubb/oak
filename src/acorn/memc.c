/*
 * File: memc.c
 * Author: dgrubb
 * Date: 26/06/2019
 */

/* Project includes */
#include "A3000.h"
#include "memc.h"

static memc_input_interface_t input = {0};
static memc_output_interface_t output = {0};

int
memc_init()
{
    return memc_reset();
}

int
memc_reset()
{
    input.lines[MEMC_INPUT_LINE_RW] = LOW;
    input.lines[MEMC_INPUT_LINE_BW] = LOW;
    input.lines[MEMC_INPUT_LINE_MREQ] = LOW;
    input.lines[MEMC_INPUT_LINE_SEQ] = LOW;
    input.lines[MEMC_INPUT_LINE_SPVMD] = LOW;
    input.addr_bus = 0;

    /* From the MEMC datasheet, page 12:
     * "The ARM processor starts executing code from location 0000000H after
     * RESET goes inactive. To ensure that the processor always finds valid code
     * at this location (which is normally Logically mapped RAM), MEMC continually
     * enables ROM."
     */
    output.lines[MEMC_OUTPUT_LINE_PH1] = HIGH;
    output.lines[MEMC_OUTPUT_LINE_PH2] = LOW;
    output.lines[MEMC_OUTPUT_LINE_ROMCS] = LOW;
    output.ra_bus = 0;

    return 0;
}

int
memc_set_input_line(memc_input_line_t line, bool state)
{
    input.lines[line] = state;
    return 0;
}

int
memc_get_input_line(memc_input_line_t line, bool *state)
{
    *state = input.lines[line];
    return 0;
}

int
memc_set_processor_address_bus(uint32_t value)
{
    input.addr_bus = value;
    return 0;
}

int
memc_get_processor_address_bus(uint32_t *value)
{
    *value= input.addr_bus;
    return 0;
}

int
memc_set_output_line(memc_output_line_t line, bool state)
{
    output.lines[line] = state;
    return 0;
}

int
memc_get_output_line(memc_output_line_t line, bool *state)
{
    *state = output.lines[line];
    return 0;
}

int
memc_set_RAM_address_bus(uint32_t value)
{
    output.ra_bus = value;
    return 0;
}

int
memc_get_RAM_address_bus(uint32_t *value)
{
    *value= output.ra_bus;
    return 0;
}

