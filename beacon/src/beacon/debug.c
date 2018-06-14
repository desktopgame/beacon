#include "debug.h"
#include <stdio.h>

void bc_dprintf(const char* fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	bc_dvprintf(fmt, ap);
	va_end(ap);
}

void bc_dvprintf(const char* fmt, va_list ap) {
	#if DEBUG
	vprintf(fmt, ap);
	fflush(stdout);
	#endif
}