/*
 * File: display.cpp
 * Author: dgrubb
 * Date: 06/03/2019
 */

/* Library includes */
#include <stdbool.h>
#include <stddef.h>

/* Project includes */
#include "display.h"
#include "oak.h"
#include "state.h"
#include "debug.h"

SDL_Window* p_window = NULL;
SDL_Surface* p_surface = NULL;
SDL_Surface* p_logo = NULL;

int
display_process_events()
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
                    state_set_mouse_focus(true);
                    break;
                case SDL_WINDOWEVENT_LEAVE:
                    state_set_mouse_focus(false);
                    break;
                case SDL_WINDOWEVENT_FOCUS_GAINED:
                    state_set_keyboard_focus(true);
                    break;
                case SDL_WINDOWEVENT_FOCUS_LOST:
                    state_set_keyboard_focus(false);
                    break;
                case SDL_WINDOWEVENT_MINIMIZED:
                    state_set_minimised(true);
                    break;
                case SDL_WINDOWEVENT_MAXIMIZED:
                    state_set_minimised(false);
                    break;
                case SDL_WINDOWEVENT_RESTORED:
                    state_set_minimised(false);
                    break;
            }
        }
        if (SDL_KEYDOWN == e.type && !e.key.repeat) {
            switch (e.key.keysym.sym) {
                case SDLK_SPACE:
                    DBG_PRINT((DBG_INFO, "Space bar pressed\n"));
                    display_toggle_fullscreen();
                    break;
            }
        }
    }
    return 0;
}

int
display_init(int width, int height)
{
    DBG_PRINT((DBG_VERBOSE, "Creating application display, resolution: %dx%d\n", width, height));
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        DBG_PRINT((DBG_VERBOSE, "Initialised SDL\n"));
    } else {
        DBG_PRINT((DBG_ERROR, "Failed to initialise SDL: %s\n", SDL_GetError()));
        display_deinit();
        return -1;
    }

    p_window = SDL_CreateWindow(PROGRAM_NAME, SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (p_window != NULL) {
        DBG_PRINT((DBG_VERBOSE, "Created SDL window\n"));
    } else {
        DBG_PRINT((DBG_ERROR, "Failed to create SDL window: %s\n", SDL_GetError()));
        display_deinit();
        return -1;
    }

    int image_flags = IMG_INIT_PNG;
    if (!(IMG_Init(image_flags) & image_flags)) {
        DBG_PRINT((DBG_ERROR, "SDL_Image failed to initialise: %s\n", IMG_GetError()));
        display_deinit();
        return -1;
    }

    p_surface = SDL_GetWindowSurface(p_window);
    if (p_surface != NULL) {
        DBG_PRINT((DBG_VERBOSE, "Retrieved SDL surface reference\n"));
    } else {
        DBG_PRINT((DBG_ERROR, "Failed to get SDL surface: %s\n", SDL_GetError()));
        display_deinit();
        return -1;
    }

    display_clear();
    return 0;
}

void
display_deinit()
{
    DBG_PRINT((DBG_VERBOSE, "Closing application display\n"));
    SDL_FreeSurface(p_surface);
    SDL_FreeSurface(p_logo);
    SDL_DestroyWindow(p_window);
    SDL_Quit();
}

int
display_clear()
{
    DBG_PRINT((DBG_INFO, "Clearing screen\n"));
    if (NULL == p_surface) {
        DBG_PRINT((DBG_ERROR, "Error getting reference to main window surface\n"));
        return -1;
    }
    SDL_FillRect(p_surface, NULL, SDL_MapRGB(p_surface->format, 0x00, 0x00, 0x00));
    SDL_UpdateWindowSurface(p_window);
    return 0;
}

int
display_splash_screen()
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
    if (NULL == p_surface) {
        DBG_PRINT((DBG_ERROR, "Error getting reference to main window surface\n"));
        return -1;
    }
    p_logo = SDL_ConvertSurface(image_surface, p_surface->format, 0);
    if (NULL == p_logo) {
        DBG_PRINT((DBG_ERROR, "Error converting image surface to main window surface format: %s\n", SDL_GetError()));
        return -1;
    }
    SDL_FreeSurface(image_surface);
    SDL_FillRect(p_surface, NULL, SDL_MapRGB(p_surface->format,
                DISPLAY_BACKGROUND_RED, DISPLAY_BACKGROUND_GREEN, DISPLAY_BACKGROUND_BLUE));
    SDL_BlitSurface(p_logo, NULL, p_surface, &logo_destination);
    SDL_UpdateWindowSurface(p_window);

    return 0;
}

int
display_toggle_fullscreen()
{
    bool fullscreen;
    state_get_fullscreen(&fullscreen);
    return display_set_fullscreen(!fullscreen);
}

int
display_set_fullscreen(bool fullscreen)
{
    DBG_PRINT((DBG_INFO, "Setting fullscreen: %s\n", (fullscreen ? "true" : "false")));
    if (NULL == p_window) {
        DBG_PRINT((DBG_ERROR, "Unable to set fullscreen, no window pointer\n"));
        return -1;
    }
    if (SDL_SetWindowFullscreen(p_window, (fullscreen ? SDL_TRUE : SDL_FALSE))) {
        DBG_PRINT((DBG_ERROR, "Failed to set fullscreen: %s\n", SDL_GetError()));
        return -1;
    }
    state_set_fullscreen(fullscreen);
    return 0;
}

void*
display_run(void* args)
{
    return NULL;
}
