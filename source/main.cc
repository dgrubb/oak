// File: main.cc
// Author: dgrubb
// Date: 21/12/2022
//
// Initial starting point for application

// C++ standard includes
#include <csignal>    // SIGABRT, SIGTERM, SIGINT, std::signal, strsignal
#include <cstdlib>    // EXIT_n macros
#include <iostream>   // std::cout
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

void PrintHelp()
{
    std::cout << std::endl << Oak::name << " "
        << Oak_VERSION_MAJOR << "." << Oak_VERSION_MINOR
        << " " << Oak::author << std::endl;
    std::cout << Oak::usage <<std::endl;
}

bool ParseArguments(int argc, char* argv[])
{
    int c;
    opterr = 0;

    std::string logLevel{""};

    while (-1 != (c = getopt(argc, argv, "hl:r:")))
    {
        switch (c)
        {
            case 'h':
                PrintHelp();
                return false;
            case 'l':
                logLevel = optarg;
                if (auto newLogLevel = Log::GetLogLevelFromString(logLevel))
                {
                    Log::SetCurrentLevel(newLogLevel.value());
                }
                else
                {
                    ERROR("Invalid log level selection entered: ", logLevel);
                    PrintHelp();
                    return false;
                }
                break;
            case 'r':
                romFilePath = optarg;
                break;
            default:
                break;
        }
    }

    return true;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    signal(SIGABRT, &signalHandler);
    signal(SIGTERM, &signalHandler);
    signal(SIGINT, &signalHandler);

    if (!ParseArguments(argc, argv))
    {
        return EXIT_SUCCESS;
    }

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
