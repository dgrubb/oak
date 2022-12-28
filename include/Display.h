// File: Display.h
// Author: dgrubb
// Date: 21/12/2022
//
// Provides a class for handling display output
// through SDL2.

#ifndef DISPLAY_H
#define DISPLAY_H

// Library includes
#include <SDL2/SDL.h>  // SDL_n()

// C++ library includes
#include <cstdint>     // uint32_t
#include <functional>  // std::function
#include <memory>      // std::unique_ptr
#include <string_view> // std::string_view

class Display
{
public:

    static bool StartRenderer();
    static void StopRenderer();

    Display(std::string_view name, uint32_t width, uint32_t height);
    ~Display();

    void Clear();
    bool ProcessEventQueue(std::vector<SDL_Event>& events);
    bool SetFullscreen(const bool fullscreen_);
    bool ToggleFullscreen();

private:
    typedef std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> Window;
    typedef std::unique_ptr<SDL_Surface, void(*)(SDL_Surface*)> Surface;

    // SDL_Init() and SDL_Quit() are global in scope, so this guard
    // condition applies to a program-wide state of whether SDL has
    // been init'd or not, hence static although it logically fits
    // within Display's purview
    static bool started;

    bool fullscreen{false};
    Window window;
    Surface surface;
};

#endif // DISPLAY_H
