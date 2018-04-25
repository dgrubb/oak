/*
 * File: oak.cpp
 * Author: dgrubb
 * Date:24/04/2018
 */

/* Library includes */
#include <cstdlib> // getopt()
#include <unistd.h> // opterr
#include <signal.h>
#include <iostream>
#include <cstring>

/* Project includes */
#include "A3000.h"
#include "oak.h"
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
    A3000 archimedes();

    if (-1 == parse_arguments(argc, argv)) {
        printf("Failed to parse arguments\n");
        print_usage();
        goto fail;
    }
    // Catch these signals to allwo for cleaning up before exiting
    signal(SIGABRT, &exit_handler);
    signal(SIGTERM, &exit_handler);
    signal(SIGINT, &exit_handler);

    print_banner();

    init_interfaces();

    while (running) {
        // Main program loop
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

    while (-1 != (c = getopt(argc, argv, "hd:"))) {
        switch (c) {
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
    DBG_PRINT((DBG_VERBOSE, "Initialising interfaces\n"));
    Timers *timers = new Timers();
    State::Interfaces()->SetTimersPtr(timers);
}

void
deinit_interfaces()
{
    DBG_PRINT((DBG_VERBOSE, "Destroying interfaces\n"));
    Timers *timers;
    if (-1 != State::Interfaces()->GetTimersPtr(timers)) {
        delete timers;
    }
}

void
print_banner()
{
    printf("=====\n");
    printf("%s\n", PROGRAM_NAME);
    printf("%s\n", PROGRAM_VERSION);
    printf("=====\n");
}

void
print_usage()
{
    print_banner();
    printf("%s\n", PROGRAM_USAGE);
}