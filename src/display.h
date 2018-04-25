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

private:

    // Methods
    int Init(int width, int height);

    // Private data
    SDL_Window* m_window = NULL;
    SDL_Surface* m_surface = NULL;
};


#endif // _DISPLAY_H

