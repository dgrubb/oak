/*
 * File: display.cpp
 * Author: dgrubb
 * Date:25/04/2018
 */

/* Project includes */
#include "display.h"
#include "oak.h"
#include "debug.h"

int
Display::Init(int width, int height)
{
    DBG_PRINT((DBG_VERBOSE, "Creating application display, resolution: %dx%d\n", width, height));
    if (-1 != SDL_Init(SDL_INIT_VIDEO)) {
        DBG_PRINT((DBG_VERBOSE, "Initialised SDL\n"));
    } else {
        DBG_PRINT((DBG_ERROR, "Failed to initialise SDL: %s\n", SDL_GetError()));
        return -1;
    }

    this->m_window = SDL_CreateWindow(PROGRAM_NAME, SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (this->m_window != NULL) {
        DBG_PRINT((DBG_VERBOSE, "Created SDL window\n"));
    } else {
        DBG_PRINT((DBG_ERROR, "Failed to create SDL window: %s\n", SDL_GetError()));
        return -1;
    }

    this->m_surface = SDL_GetWindowSurface(this->m_window);
    if (this->m_surface != NULL) {
        DBG_PRINT((DBG_VERBOSE, "Retrieved SDL surface reference\n"));
    } else {
        DBG_PRINT((DBG_ERROR, "Failed to get SDL surface: %s\n", SDL_GetError()));
        return -1;
    }

    SDL_FillRect(this->m_surface, NULL, SDL_MapRGB(this->m_surface->format, 0x00, 0x00, 0x00));
    SDL_UpdateWindowSurface(this->m_window);
}

Display::Display()
{
    this->Init(DISPLAY_DEFAULT_WIDTH, DISPLAY_DEFAULT_HEIGHT);
}

Display::Display(int width, int height)
{
    this->Init(width, height);
}

Display::~Display()
{
    DBG_PRINT((DBG_VERBOSE, "Closing application display\n"));
    SDL_DestroyWindow(this->m_window);
}

