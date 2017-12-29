#include <stdlib.h>
#include <stdio.h>
#include "mem.h"
#include "logger.h"

//割り当て回数
static int allocCount = 0;

void * mem_malloc(size_t size, const char * filename, int lineno) {
	void* ret = malloc(size);
	if (ret == NULL) {
		sg_log(log_fatal, filename, lineno, "failed malloc");
	}
	allocCount++;
	return ret;
}

void * mem_realloc(void * block, size_t newSize, const char * filename, int lineno) {
	void* ret = realloc(block, newSize);
	if (ret == NULL) {
		sg_log(log_fatal, filename, lineno, "failed realloc");
	}
	//allocCount++;
	return ret;
}

void mem_free(void * block, const char * filename, int lineno) {
	free(block);
	allocCount--;
}

void mem_inc() {
	allocCount++;
}

void mem_dec() {
	allocCount--;
}

void mem_check() {
#ifdef DEBUG
	if (allocCount > 0) {
		printf("detected of memory leaks: %d", allocCount);
	}
#endif
}
