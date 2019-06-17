/*
 * File: util.c
 * Author: dgrubb
 * Date: 05/03/2019
 */

/* Library includes */
#include <string.h>

/* Project includes */
#include "state.h"
#include "util.h"

int
util_copy_file_path_string(char *dest, const char *src)
{
    memset(dest, 0, STATE_MAX_PATH_LEN);
    strncpy(dest, src, STATE_MAX_PATH_LEN);
    dest[STATE_MAX_PATH_LEN-1] = '\0';
    return 0;
}
