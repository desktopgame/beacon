#ifndef BEACON_DEBUG_H
#define BEACON_DEBUG_H
#include <stdarg.h>

void bc_dprintf(const char* fmt, ...);

void bc_dvprintf(const char* fmt, va_list ap);
#endif