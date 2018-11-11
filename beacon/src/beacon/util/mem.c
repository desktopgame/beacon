#include "mem.h"
#include <string.h>

void* SafeMalloc(size_t size) {
	void* ret = malloc(size);
	if(ret == NULL) {
		abort();
	}
	memset(ret, 0, size);
	return ret;
}

void* SafeRealloc(void* block, size_t new_size) {
	void* ret = realloc(block, new_size);
	if(ret == NULL) {
		abort();
	}
	return ret;
}