#ifndef _DEBUG_H
#define _DEBUG_H

int extern DBG_DebugLevel;

#define DEBUG_MAX_STRING 2048
#define DBG_LVL_CRITICAL        0
#define DBG_LVL_ERROR           1
#define DBG_LVL_ALWAYS          2
#define DBG_LVL_WARNING         3
#define DBG_LVL_INFO            4
#define DBG_LVL_VERBOSE         5
#define DBG_LVL_ULTRA_VERBOSE   6
#define DBG_LVL_NEVER           99

#define DBG_PRINT_INFO(x) ((x) <= DBG_DebugLevel),(x),__FILE__,__LINE__

#define DBG_CRITICAL      DBG_PRINT_INFO(DBG_LVL_CRITICAL)
#define DBG_ERROR         DBG_PRINT_INFO(DBG_LVL_ERROR)
#define DBG_ALWAYS        DBG_PRINT_INFO(DBG_LVL_ALWAYS)
#define DBG_WARNING       DBG_PRINT_INFO(DBG_LVL_WARNING)
#define DBG_INFO          DBG_PRINT_INFO(DBG_LVL_INFO)
#define DBG_VERBOSE       DBG_PRINT_INFO(DBG_LVL_VERBOSE)
#define DBG_ULTRA_VERBOSE DBG_PRINT_INFO(DBG_LVL_ULTRA_VERBOSE)
#define DBG_NEVER         DBG_PRINT_INFO(DBG_LVL_NEVER)

#define DBG_PRINT(x) debug_print x

int get_debug_level(int &dbg_level);
int set_debug_level(int dbg_level);
int validate_debug_level(int dbg_level);
void debug_print(bool enable, int dbg_level, const char *file,
        int line, const char *text, ...);
const char * get_debug_level_string(int dbg_level);

#endif // _DEBUG_H
