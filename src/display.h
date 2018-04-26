/*
 * File: display.h
 * Author: dgrubb
 * Date:25/04/2018
 */

#ifndef _DISPLAY_H
#define _DISPLAY_H

/* Library includes */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define DISPLAY_DEFAULT_WIDTH  800
#define DISPLAY_DEFAULT_HEIGHT 600

#define DISPLAY_BACKGROUND_RED   0x01
#define DISPLAY_BACKGROUND_GREEN 0xA9
#define DISPLAY_BACKGROUND_BLUE  0xE7

#define DISPLAY_LOGO_PATH "./res/oak_logo.png"
#define DISPLAY_LOGO_WIDTH 400
#define DISPLAY_LOGO_HEIGHT 342
#define DISPLAY_LOGO_X 200
#define DISPLAY_LOGO_Y 129

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
    int ShowSplash();
    int Clear();

private:

    // Methods
    int Init();

    // Private data
    SDL_Window* m_window = NULL;
    SDL_Surface* m_surface = NULL;
    SDL_Surface* m_logo = NULL;
    int m_width = DISPLAY_DEFAULT_WIDTH;
    int m_height = DISPLAY_DEFAULT_HEIGHT;
    bool m_mouse_focus = false;
    bool m_keyboard_focus = false;
    bool m_fullscreen = false;
    bool m_minimised = false;
};


#endif // _DISPLAY_H

