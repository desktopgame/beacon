#ifndef BEACON_ENV_RESOLVE_DEFAULT_NOTEQOPERATOR_RESOLVE_H
#define BEACON_ENV_RESOLVE_DEFAULT_NOTEQOPERATOR_RESOLVE_H
struct lazy_int;
struct type;

typedef struct default_noteqoperator_resolve {
	struct lazy_int* lazyi_ref;
	struct type* type_ref;
} default_noteqoperator_resolve;

default_noteqoperator_resolve* default_noteqoperator_resolve_new();

void default_noteqoperator_resolve_apply(default_noteqoperator_resolve* self);

void default_noteqoperator_resolve_delete(default_noteqoperator_resolve* self);
#endif