#pragma once
#ifndef BEACON_UTIL_POOL_H
#define BEACON_UTIL_POOL_H
#include <stdlib.h>

typedef struct pool {
	size_t cursor;
	void* memory;
	struct pool* next;
	struct pool* prev;
} pool;

pool* pool_new();

void* pool_ref(pool* self, size_t size);
#endif // !SIGNAL_UTIL_POOL_H
