/*
 * File: oak.h
 * Author: dgrubb
 * Date:24/04/2018
 */

#define PROGRAM_NAME "Oak"
#define PROGRAM_VERSION "0.0.1"
#define PROGRAM_AUTHOR "dgrubb"
#define PROGRAM_WEBSITE "https://github.com/dgrubb/oak"
#define PROGRAM_USAGE "An Acorn Archimedes A3000 emulator.\n\n" \
"Usage:\n$ ./oak -d 4 -r <ROM FILE>\n" \
"\t-h\tPrint usage.\n" \
"\t-d\tSet debug level:\n\n" \
"\t\t0 - Critical\n" \
"\t\t1 - Error\n" \
"\t\t2 - Always\n" \
"\t\t3 - Warning\n" \
"\t\t4 - Info\n" \
"\t\t5 - Verbose\n" \
"\t\t6 - Ultra verbose\n" \
"\t\t99- Never\n"

void init_interfaces();
void deinit_interfaces();
int parse_arguments(int argc, char* argv[]);
void print_banner();
void print_usage();
