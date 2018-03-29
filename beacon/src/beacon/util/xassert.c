#include "xassert.h"
#include "text.h"
#include "mem.h"
#include <string.h>

bool xassert_break(bool condition) {
	if(condition) {
		return true;
	}
	return false;
}

bool xassert_breakstreq(const char* a, const char* b) {
	return xassert_break(!strcmp(a, b));
}

bool xassert_breakptreq(const void* a, const void* b) {
	return xassert_break(a == b);
}

bool xassert_streq(const char* a, const char* b) {
	return !strcmp(a, b);
}