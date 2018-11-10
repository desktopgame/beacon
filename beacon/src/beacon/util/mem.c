#include "mem.h"
#include <string.h>

void* SafeMalloc(size_t size) {
	void* ret = malloc(size);
	memset(ret, 0, size);
	return ret;
}