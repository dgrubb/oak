/*
 * File: oak.cpp
 * Author: dgrubb
 * Date:24/04/2018
 */

/* Library includes */
#include <cstdlib> // getopt()
#include <unistd.h> // opterr, sleep()
#include <signal.h>
#include <cstring>
#include <iostream>
#include <string>

/* Project includes */
#include "acorn/A3000.h"
#include "oak.h"
#include "settings.h"
#include "state.h"
#include "timers.h"
#include "debug.h"

using namespace std;

volatile bool running = true;

void
exit_handler(int sig)
{
    printf("Signal [ %s ], exiting ...\n", strsignal(sig));
    running = false;
}

int
main (int argc, char* argv[])
{
    Settings settings;
    Display *display;
    string config_file;

    if (-1 == parse_arguments(argc, argv)) {
        printf("Failed to parse arguments\n");
        print_usage();
        goto fail;
    }
    // Catch these signals to allow for cleaning up before exiting
    signal(SIGABRT, &exit_handler);
    signal(SIGTERM, &exit_handler);
    signal(SIGINT, &exit_handler);

    print_banner();
    init_interfaces();

    State::Interfaces()->GetConfigFile(&config_file);
    if (-1 == settings_read_file(config_file.c_str(), settings)) {
        settings_get_defaults(settings);
    }
    settings_print(settings);
    settings_apply(settings);

    // Just an aesthetic touch
    State::Interfaces()->GetDisplayPtr(display);
    display->ShowSplash();
    sleep(3);
    display->Clear();

    while (running) {
        // Main program loop
        if ((NULL == display) || (-1 == display->ProcessEvents())) {
            running = false;
        }
    }

    deinit_interfaces();
    return EXIT_SUCCESS;

fail: ;
    return EXIT_FAILURE;
}

int
parse_arguments(int argc, char* argv[])
{
    int c;
    opterr = 0;

    while (-1 != (c = getopt(argc, argv, "hd:c:"))) {
        switch (c) {
            case 'c':
                State::Interfaces()->SetConfigFile(string(optarg));
                break;
            case 'd':
                if (-1 != validate_debug_level(atoi(optarg))) {
                    set_debug_level(atoi(optarg));
                } else {
                    print_usage();
                    return -1;
                }
                break;
            case 'h':
                print_usage();
                exit(EXIT_SUCCESS);
            default:
                return -1;
        }
    }

    return 0;
}

void
init_interfaces()
{
    DBG_PRINT((DBG_INFO, "Initialising interfaces\n"));
    Timers *timers = new Timers();
    State::Interfaces()->SetTimersPtr(timers);
    Display *display = new Display();
    State::Interfaces()->SetDisplayPtr(display);
}

void
deinit_interfaces()
{
    DBG_PRINT((DBG_INFO, "Destroying interfaces\n"));
    Timers *timers;
    if (-1 != State::Interfaces()->GetTimersPtr(timers)) {
        delete timers;
    }
    Display *display;
    if (-1 != State::Interfaces()->GetDisplayPtr(display)) {
        delete display;
    }
}

void
print_banner()
{
    printf("======================================\n");
    printf("%s, version: %s\n", PROGRAM_NAME, PROGRAM_VERSION);
    printf("Author: %s\n", PROGRAM_AUTHOR);
    printf("Website: %s\n", PROGRAM_WEBSITE);
    printf("======================================\n");
}

void
print_usage()
{
    print_banner();
    printf("%s\n", PROGRAM_USAGE);
}
