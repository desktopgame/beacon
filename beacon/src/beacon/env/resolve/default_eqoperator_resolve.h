#ifndef BEACON_ENV_RESOLVE_DEFAULT_EQOPERATOR_RESOLVE_H
#define BEACON_ENV_RESOLVE_DEFAULT_EQOPERATOR_RESOLVE_H
struct lazy_int;
struct type;

typedef struct default_eqoperator_resolve {
	struct lazy_int* lazyi_ref;
	struct type* type_ref;
} default_eqoperator_resolve;

default_eqoperator_resolve* default_eqoperator_resolve_new();

void default_eqoperator_resolve_apply(default_eqoperator_resolve* self);

void default_eqoperator_resolve_delete(default_eqoperator_resolve* self);
#endif