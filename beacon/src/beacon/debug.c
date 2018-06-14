#include "debug.h"
#include <stdio.h>
#define DEBUG

void bc_dprintf(const char* fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	bc_dvprintf(fmt, ap);
	va_end(ap);
}

void bc_dvprintf(const char* fmt, va_list ap) {
	#ifdef DEBUG
	vprintf(fmt, ap);
	fflush(stdout);
	#endif
}

void bc_dprintfln(const char* fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	bc_dvprintfln(fmt, ap);
	va_end(ap);
}

void bc_dvprintfln(const char* fmt, va_list ap) {
	bc_dvprintf(fmt, ap);
	printf("\n");
}