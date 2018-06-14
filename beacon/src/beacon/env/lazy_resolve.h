#ifndef BEACON_ENV_LAZY_RESOLVE_H
#define BEACON_ENV_LAZY_RESOLVE_H
#include <stdbool.h>
struct default_eqoperator_resolve;
struct default_noteqoperator_resolve;

typedef enum lazy_resolve_tag {
	resolve_default_eqoperator,
	resolve_default_noteqoperator,
} lazy_resolve_tag;

typedef struct lazy_resolve {
	lazy_resolve_tag tag;
	bool active;
	union {
		struct default_eqoperator_resolve* def_eqoperator;
		struct default_noteqoperator_resolve* def_noteqoperator;
//		struct default_operator_resolve* def_operator;
	} u;
} lazy_resolve;

lazy_resolve* lazy_resolve_new(lazy_resolve_tag tag);

void lazy_resolve_apply(lazy_resolve* self);

void lazy_resolve_delete(lazy_resolve* self);
#endif