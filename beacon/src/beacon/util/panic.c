#include "panic.h"
#include <stdio.h>
#include <stdlib.h>
#include "string_buffer.h"
#include "io.h"

static string_view gPanicFile;

void save(string_view filenamev) {
#if defined(DEBUG)
	gPanicFile = filenamev;
#endif
}

void panic() {
#if defined(DEBUG)
	FILE* fp = fopen("panic.dbg", "w");
	if(fp == NULL) {
		return;
	}
	fprintf(fp, "%s", string_pool_ref2str(gPanicFile));
	fclose(fp);
#else
	abort();
#endif
}

string_view load() {
#if defined(DEBUG)
	char* text = io_read_text("panic.dbg");
	return string_pool_intern(text);
#else
	return NULL_VIEW;
#endif
}