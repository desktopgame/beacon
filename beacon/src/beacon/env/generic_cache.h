#pragma once
#ifndef BEACON_ENV_GENERIC_CACHE_H
#define BEACON_ENV_GENERIC_CACHE_H
#include "fqcn_cache.h"
#include "../il/il_context.h"
#include "../util/vector.h"

struct generic_type;
struct type;
struct class_;
struct interface_;
struct namespace_;

typedef struct generic_cache {
	fqcn_cache* fqcn;
	vector* type_args;
} generic_cache;

generic_cache* generic_cache_new();

#define generic_cache_gtype(self, scope, ilctx) (generic_cache_gtypeloc(self, scope, ilctx, __FILE__, __LINE__))

//struct generic_type* generic_cache_gtype(generic_cache* self, struct namespace_* scope, il_context* ilctx);

struct generic_type* generic_cache_gtypeloc(generic_cache* self, struct namespace_* scope, il_context* ilctx, const char* filename, int lineno);

struct type* generic_cache_type(generic_cache* self, struct namespace_* scope);

struct class_* generic_cache_class(generic_cache* self, struct namespace_* scope);

struct interface_* generic_cache_interface(generic_cache* self, struct namespace_* scope);

void generic_cache_print(generic_cache* self);

void generic_cache_dump(generic_cache* self, int depth);

void generic_cache_delete(generic_cache* self);
#endif // !SIGNAL_ENV_GENERIC_CACHE_H
