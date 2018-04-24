#include <string>
#include <cstdarg>
#include <string.h>
#include <stdio.h>
#include "debug.h"

int DBG_DebugLevel = DBG_LVL_ALWAYS;

int set_debug_level(int dbg_level)
{
	DBG_DebugLevel = dbg_level;
	return 0;
}

int get_debug_level(int &dbg_level)
{
	dbg_level = DBG_DebugLevel;
	return 0;
}

int validate_debug_level(int dbg_level)
{
	if ((dbg_level == DBG_LVL_CRITICAL) ||
			(dbg_level == DBG_LVL_ERROR) ||
			(dbg_level == DBG_LVL_ALWAYS) ||
			(dbg_level == DBG_LVL_WARNING) ||
			(dbg_level == DBG_LVL_INFO) ||
			(dbg_level == DBG_LVL_VERBOSE) ||
			(dbg_level == DBG_LVL_ULTRA_VERBOSE) ||
			(dbg_level == DBG_LVL_NEVER)) {
		return 0;
	}
	return -1;
}

const char * get_debug_level_string(int dbg_level)
{
	switch (dbg_level) {
		case DBG_LVL_CRITICAL: return "CRITICAL";
		case DBG_LVL_ERROR: return "ERROR";
		case DBG_LVL_ALWAYS: return "ALWAYS";
		case DBG_LVL_WARNING: return "WARNING";
		case DBG_LVL_INFO: return "INFO";
		case DBG_LVL_VERBOSE: return "VERBOSE";
		case DBG_LVL_ULTRA_VERBOSE: return "ULTRA_VERBOSE";
		case DBG_LVL_NEVER: return "NEVER";
		default: return "UNKNOWN";
	}
}

// Function: debug_print
//
// Description: Prints a normalised debug message to stdout.
//
// Parameters:
// bool enable - True to enable printing.
// int dbg_level - Debug level of message.
// const char *file - Name of the source file which generated the message.
// int line - Line number which generated the message.
// const char * text - Message to write.
// ... - List of further data to format into message.
void debug_print(bool enable, int dbg_level, const char *file,
		int line, const char *text, ...)
{
	if (enable) {
		va_list ap;
		char str[DEBUG_MAX_STRING];
		char filename[DEBUG_MAX_STRING];
		char *tmp;
		char tmpFile[strlen(file)];
		strcpy(tmpFile, file);
		tmp = strrchr(tmpFile, '/');
		if (tmp == NULL) {
			tmp = (char *)file;
		} else {
			tmp = &(tmp[1]);
		}
		strcpy(filename, tmp);
		tmp = strrchr(filename, '.');
		if (tmp != NULL) {
			*tmp = 0;
		}
		snprintf((char *) str, sizeof(str),
			"[ %8.8s: %15.15s:%5d ] ",
			get_debug_level_string(dbg_level), (char *)filename, line);
		va_start(ap, text);
		vsnprintf((char *)(str + strlen(str)), sizeof(str) - strlen(str),
			text, ap);
		va_end(ap);
		fprintf(stdout, "%s", str);
	}
}

