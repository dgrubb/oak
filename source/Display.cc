// File: Display.cc
// Author: dgrubb
// Date: 21/12/2022
//
// Provides a class for handling display output
// through SDL2.

// Implementation include
#include "Display.h"

// C++ library includes
#include <stdexcept> // std::runtime_error

// Project includes
#include "Log.h"

bool Display::started{false};

bool Display::StartRenderer()
{
    if (started) return true;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        ERROR("Failed to initialise SDL: ", SDL_GetError());
        return false;
    }

    started = true;
    DEBUG("Initialised SDL");
    return true;
}

void Display::StopRenderer()
{
    DEBUG("Closing SDL");
    SDL_Quit();
}

Display::Display(std::string_view name, unsigned int width, unsigned int height)
  : window(
        SDL_CreateWindow(
            name.data(),
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width, height,
            SDL_WINDOW_OPENGL
        ),
        SDL_DestroyWindow
    ),
    surface(
        SDL_GetWindowSurface(window.get()),
        SDL_FreeSurface
    )
{
    Clear();
}

void Display::Clear()
{
    SDL_FillRect(surface.get(), NULL, SDL_MapRGB(surface.get()->format, 0x00, 0x00, 0x00));
    SDL_UpdateWindowSurface(window.get());
}

bool Display::SetFullscreen(const bool fullscreen_)
{
    if (SDL_SetWindowFullscreen(window.get(), (fullscreen_ ? SDL_TRUE : SDL_FALSE)))
    {
        ERROR("Failure setting window fullscreen [ ", fullscreen_, " ]: ", SDL_GetError());
        return false;
    }
    fullscreen = fullscreen_;
    DEBUG("Set fullscreen [ ", fullscreen, " ]");
    return true;
}

bool Display::ProcessEventQueue(std::vector<SDL_Event>& events)
{
    SDL_Event e;
    while (0 != SDL_PollEvent(&e))
    {
        if (SDL_QUIT == e.type)
        {
            INFO("Received SDL quit");
            return false;
        }
        events.push_back(e);
    }
    return true;
}

bool Display::ToggleFullscreen()
{
    DEBUG("Toggling fullscreen");
    return SetFullscreen(!fullscreen);
}

Display::~Display()
{
    DEBUG("Closing window");
}
