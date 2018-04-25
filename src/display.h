/*
 * File: display.h
 * Author: dgrubb
 * Date:25/04/2018
 */

#ifndef _DISPLAY_H
#define _DISPLAY_H

/* Library includes */
#include <SDL2/SDL.h>

#define DISPLAY_DEFAULT_WIDTH  800
#define DISPLAY_DEFAULT_HEIGHT 600

class Display {

public:

    // Constructors and destructors
    Display();
    Display(int width, int height);
    ~Display();

    // Methods
    int ProcessEvents();
    bool GetFullscreen();
    int SetFullscreen(bool fullscreen);
    int ToggleFullscreen();
    bool GetMinimised();
    bool GetFocused();


private:

    // Methods
    int Init();

    // Private data
    SDL_Window* m_window = NULL;
    SDL_Surface* m_surface = NULL;
    int m_width = DISPLAY_DEFAULT_WIDTH;
    int m_height = DISPLAY_DEFAULT_HEIGHT;
    bool m_mouse_focus = false;
    bool m_keyboard_focus = false;
    bool m_fullscreen = false;
    bool m_minimised = false;
};


#endif // _DISPLAY_H

