/*
 * File: oak.cc
 * Author: dgrubb
 * Date: 05/03/2019
 */

#define _GNU_SOURCE

/* Library includes */
#include <sys/types.h>
#include <unistd.h> // opterr, sleep()
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Project includes */
#include "oak.h"
#include "acorn/A3000.h"
#include "display.h"
#include "settings.h"
#include "state.h"
#include "debug.h"

void
exit_handler(int sig)
{
    printf("\nSignal [ %s ], exiting ...\n", strsignal(sig));
}

int
main (int argc, char* argv[])
{
    char config_file[STATE_MAX_PATH_LEN];
    state_init();
    if (-1 == parse_arguments(argc, argv)) {
        printf("Failed to parse arguments\n");
        print_usage();
        return EXIT_FAILURE;
    }
    /* Catch these signals to allow for cleaning up before exiting */
    signal(SIGABRT, &exit_handler);
    signal(SIGTERM, &exit_handler);
    signal(SIGINT, &exit_handler);

    /* Work out what the initial state of application and emulation should be */
    print_banner();
    state_get_config_file(config_file);
    settings_read_file(config_file);
    settings_print();

    /* Initialise video display and show splash screen */
    if (display_init(DISPLAY_DEFAULT_WIDTH, DISPLAY_DEFAULT_HEIGHT)) {
        DBG_PRINT((DBG_ERROR, "Unable to start display, exiting.\n"));
        return EXIT_FAILURE;
    }
    display_splash_screen();
    sleep(3);
    display_clear();

    if (A3000_init()) {
        DBG_PRINT((DBG_ERROR, "Unable to start A3000, exiting.\n"));
        display_deinit();
        return EXIT_FAILURE;
    }

    /* This will block until application exits */
    /* TODO: main game loop */

    display_deinit();
    return EXIT_SUCCESS;
}

int
parse_arguments(int argc, char* argv[])
{
    int c;
    opterr = 0;

    while (-1 != (c = getopt(argc, argv, "hd:c:r:"))) {
        switch (c) {
            case 'c':
                state_set_config_file(optarg);
                break;
            case 'r':
                state_set_ROM_file(optarg);
                state_set_ROM_file_arg_override(true);
                break;
            case 'd':
                if (-1 != validate_debug_level(atoi(optarg))) {
                    set_debug_level(atoi(optarg));
                    state_set_debug_arg_override(true);
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
