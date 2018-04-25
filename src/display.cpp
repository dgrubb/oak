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
Display::ProcessEvents()
{
    SDL_Event e;
    while (0 != SDL_PollEvent(&e)) {
        if (SDL_QUIT == e.type) {
            DBG_PRINT((DBG_INFO, "Received SDL quit\n"));
            return -1;
        }
        // TODO: map keyboard and mouse inputs to emulated state machine
        if (SDL_WINDOWEVENT == e.type) {
            switch (e.window.event) {
                case SDL_WINDOWEVENT_ENTER:
                    this->m_mouse_focus = true;
                    break;
                case SDL_WINDOWEVENT_LEAVE:
                    this->m_mouse_focus = false;
                    break;
                case SDL_WINDOWEVENT_FOCUS_GAINED:
                    this->m_keyboard_focus = true;
                    break;
                case SDL_WINDOWEVENT_FOCUS_LOST:
                    this->m_keyboard_focus = false;
                    break;
                case SDL_WINDOWEVENT_MINIMIZED:
                    this->m_minimised = true;
                    break;
                case SDL_WINDOWEVENT_MAXIMIZED:
                    this->m_minimised = false;
                    break;
                case SDL_WINDOWEVENT_RESTORED:
                    this->m_minimised = false;
                    break;
            }
        }
    }
    return 0;
}

int
Display::SetFullscreen(bool fullscreen)
{
    return 0;
}

bool
Display::GetFullscreen()
{
    return this->m_fullscreen;
}

bool
Display::GetFocused()
{
    return (this->m_mouse_focus && this->m_keyboard_focus);
}

bool
Display::GetMinimised()
{
    return this->m_minimised;
}

int
Display::Init()
{
    DBG_PRINT((DBG_VERBOSE, "Creating application display, resolution: %dx%d\n", this->m_width, this->m_height));
    if (-1 != SDL_Init(SDL_INIT_VIDEO)) {
        DBG_PRINT((DBG_VERBOSE, "Initialised SDL\n"));
    } else {
        DBG_PRINT((DBG_ERROR, "Failed to initialise SDL: %s\n", SDL_GetError()));
        return -1;
    }

    this->m_window = SDL_CreateWindow(PROGRAM_NAME, SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, this->m_width, this->m_height, SDL_WINDOW_SHOWN);
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
    this->m_width = DISPLAY_DEFAULT_WIDTH;
    this->m_height = DISPLAY_DEFAULT_HEIGHT;
    this->Init();
}

Display::Display(int width, int height)
{
    this->m_width = width;
    this->m_height = height;
    this->Init();
}

Display::~Display()
{
    DBG_PRINT((DBG_VERBOSE, "Closing application display\n"));
    SDL_DestroyWindow(this->m_window);
}

