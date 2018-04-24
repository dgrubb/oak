/*
 * File: oak.cpp
 * Author: dgrubb
 * Date:24/04/2018
 */

using namespace std;

bool running = true;

void
exit_handler(int sig)
{
    printf("Exiting ...\n");
    running = false;
}

int
main (int argc, char* argv[])
{

    if (-1 == parse_arguments(argc, argv)) {
        printf("Failed to parse arguments\n");
        print_usage();
        goto fail;
    }
    // Catch these signals to allwo for cleaning up before exiting
    signal(SIGABRT, &exit_handler);
    signal(SIGTERM, &exit_handler);
    signal(SIGINT, &exit_handler);

    while (running) {
        // Main program loop
    }

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
                } else {
                    print_usage()
                }
        }
    }
}
