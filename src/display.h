/*
 * File: display.h
 * Author: dgrubb
 * Date: 06/03/2019
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

#define DISPLAY_LOGO_PATH   "./res/oak_logo.png"
#define DISPLAY_LOGO_WIDTH  400
#define DISPLAY_LOGO_HEIGHT 342
#define DISPLAY_LOGO_X      200
#define DISPLAY_LOGO_Y      129

int display_init();
void display_deinit();
int display_clear();
int display_splash_screen();
int display_process_events();
int display_set_fullscreen(bool fullscreen);
int display_toggle_fullscreen();

#endif // _DISPLAY_H

