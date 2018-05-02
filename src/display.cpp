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
        if (SDL_KEYDOWN == e.type) {
            switch (e.key.keysym.sym) {
                case SDLK_SPACE:
                    DBG_PRINT((DBG_INFO, "Space bar pressed\n"));
                    this->ToggleFullscreen();
                    break;
            }
        }
    }
    return 0;
}

int
Display::SetFullscreen(bool fullscreen)
{
    this->m_fullscreen = fullscreen;
    if (NULL != this->m_window) {
        DBG_PRINT((DBG_INFO, "Setting fullscreen: %s\n", (this->m_fullscreen ? "true" : "false")));
        SDL_SetWindowFullscreen(this->m_window, (this->m_fullscreen ? SDL_TRUE : SDL_FALSE));
        return 0;
    } else {
        DBG_PRINT((DBG_ERROR, "Unable to set fullscreen, no window pointer\n"));
        return -1;
    }
}

int
Display::ToggleFullscreen()
{
    this->SetFullscreen(!this->m_fullscreen);
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

    int image_flags = IMG_INIT_PNG;
    if (!(IMG_Init(image_flags) & image_flags)) {
        DBG_PRINT((DBG_ERROR, "SDL_Image failed to initialise: %s\n", IMG_GetError()));
        return -1;
    }

    this->m_surface = SDL_GetWindowSurface(this->m_window);
    if (this->m_surface != NULL) {
        DBG_PRINT((DBG_VERBOSE, "Retrieved SDL surface reference\n"));
    } else {
        DBG_PRINT((DBG_ERROR, "Failed to get SDL surface: %s\n", SDL_GetError()));
        return -1;
    }

    Clear();

    return 0;
}

int
Display::ShowSplash()
{
    DBG_PRINT((DBG_INFO, "Displaying splash screen\n"));
    SDL_Rect logo_destination = {
        DISPLAY_LOGO_X,
        DISPLAY_LOGO_Y,
        DISPLAY_LOGO_WIDTH,
        DISPLAY_LOGO_HEIGHT
    };
    SDL_Surface* image_surface = IMG_Load(DISPLAY_LOGO_PATH);
    if (NULL == image_surface) {
        DBG_PRINT((DBG_ERROR, "Error loading image [ %s ]: %s\n", DISPLAY_LOGO_PATH, IMG_GetError()));
        return -1;
    }
    if (NULL == this->m_surface) {
        DBG_PRINT((DBG_ERROR, "Error getting reference to main window surface\n"));
        return -1;
    }
    this->m_logo = SDL_ConvertSurface(image_surface, this->m_surface->format, 0);
    if (NULL == this->m_logo) {
        DBG_PRINT((DBG_ERROR, "Error converting image surface to main window surface format: %s\n", SDL_GetError()));
        return -1;
    }
    SDL_FreeSurface(image_surface);
    SDL_FillRect(this->m_surface, NULL, SDL_MapRGB(this->m_surface->format,
                DISPLAY_BACKGROUND_RED, DISPLAY_BACKGROUND_GREEN, DISPLAY_BACKGROUND_BLUE));

    SDL_BlitSurface(this->m_logo, NULL, this->m_surface, &logo_destination);
    SDL_UpdateWindowSurface(this->m_window);

    return 0;
}

int
Display::Clear()
{
    DBG_PRINT((DBG_INFO, "Clearing screen\n"));
    if (NULL == this->m_surface) {
        DBG_PRINT((DBG_ERROR, "Error getting reference to main window surface\n"));
        return -1;
    }
    SDL_FillRect(this->m_surface, NULL, SDL_MapRGB(this->m_surface->format, 0x00, 0x00, 0x00));
    SDL_UpdateWindowSurface(this->m_window);
    return 0;
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
    SDL_FreeSurface(this->m_surface);
    SDL_FreeSurface(this->m_logo);
    SDL_DestroyWindow(this->m_window);
    SDL_Quit();
}

