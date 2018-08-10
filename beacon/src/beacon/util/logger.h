#ifndef BEACON_UTIL_LOGGER_H
#define BEACON_UTIL_LOGGER_H
#include "text.h"
#include <stdio.h>
#include <stdarg.h>

typedef enum log_level {
	log_debug_T,
	log_warn_T,
	log_fetal_T,
} log_level;

//#if defined(DEBUG)
//#define LOG(fmt, ...) (logger_log(log_debug_T, __FILE__, __LINE__, fmt, __VA_ARGS__))

//#else
#define LOG(fmt, ...) (void)(0)
//#endif

void logger_init();

int logger_flog(log_level level, FILE* fp, const char* filename, int lineno, const char* fmt, ...);

int logger_vflog(log_level level, FILE* fp, const char* filename, int lineno, const char* fmt, va_list ap);

int logger_log(log_level level, const char* filename, int lineno, const char* fmt, ...);

void logger_destroy();
#endif