#pragma once
#ifndef SIGNAL_ENV_GENERIC_CACHE_H
#define SIGNAL_ENV_GENERIC_CACHE_H
#include "fqcn_cache.h"
#include "../util/vector.h"

typedef struct generic_cache {
	fqcn_cache* fqcn;
	vector* type_args;
} generic_cache;

generic_cache* generic_cache_new();

void generic_cache_delete(generic_cache* self);
#endif // !SIGNAL_ENV_GENERIC_CACHE_H
