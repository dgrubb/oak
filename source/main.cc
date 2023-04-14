// File: main.cc
// Author: dgrubb
// Date: 21/12/2022
//
// Initial starting point for application

// C++ standard includes
#include <csignal>    // SIGABRT, SIGTERM, SIGINT, std::signal, strsignal
#include <cstdlib>    // EXIT_n macros
#include <string>     // std::string
#include <unistd.h>   // opterr
#include <vector>     // std::vector

// Library includes
#include <SDL2/SDL.h> // SDL_n()

// Project includes
#include "A3000.h"
#include "Display.h"
#include "Log.h"
#include "Oak.h"
#include "Version.h"

static bool running{true};
static std::string romFilePath{"./risocs-3.71.rom"};

void signalHandler(int signal)
{
    INFO("Signal raised [ ", strsignal(signal), " ], exiting ...");
    running = false;
}

bool ParseRomFilePath(int argc, char* argv[])
{
    int c;
    opterr = 0;

    while (-1 != (c = getopt(argc, argv, "r:")))
    {
        switch (c)
        {
            case 'r':
                romFilePath = optarg;
                return true;
            default:
                break;
        }
    }

    return false;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    signal(SIGABRT, &signalHandler);
    signal(SIGTERM, &signalHandler);
    signal(SIGINT, &signalHandler);

    ParseRomFilePath(argc, argv);

    if (!Display::StartRenderer())
    {
        ERROR("Could not start renderer");
        return EXIT_FAILURE;
    }

    // Brace scope to ensure things instantiated within this block
    // are automatically destroyed cleanly before manually
    // stopping the renderer.
    {
        auto display = Display(Oak::name, Oak::defaultWindowWidth, Oak::defaultWindowHeight);
        auto a3000 = A3000();
        a3000.Reset();
        a3000.LoadROM(romFilePath);

        INFO("Initialised Oak v", Oak_VERSION_MAJOR, ".", Oak_VERSION_MINOR);

        std::vector<SDL_Event> events;
        while (running && display.ProcessEventQueue(events))
        {
            if (!events.empty())
            {
                for (auto& ev: events)
                {
                    if ((SDL_KEYDOWN == ev.type) && (SDLK_RIGHT == ev.key.keysym.sym))
                    {
                        a3000.Tick();
                    }
                    if ((SDL_KEYDOWN == ev.type) && (SDLK_p == ev.key.keysym.sym))
                    {
                        a3000.PrintState();
                    }
                    if ((SDL_KEYDOWN == ev.type) && (SDLK_q == ev.key.keysym.sym))
                    {
                        INFO("Quit requested");
                        running = false;
                    }
                }
                events.clear();
            }
        }
        INFO("Shutting down");
    }

    Display::StopRenderer();
    return EXIT_SUCCESS;
} // main()
