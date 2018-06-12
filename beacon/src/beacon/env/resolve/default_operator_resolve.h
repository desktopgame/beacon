#ifndef BEACON_ENV_RESOLVE_DEFAULT_OPERATOR_RESOLVE_H
#define BEACON_ENV_RESOLVE_DEFAULT_OPERATOR_RESOLVE_H
struct lazy_int;
struct type;

typedef struct default_operator_resolve {
	struct lazy_int* lazyi_ref;
	struct type* type_ref;
} default_operator_resolve;

default_operator_resolve* default_operator_resolve_new();

void default_operator_resolve_apply(default_operator_resolve* self);

void default_operator_resolve_delete(default_operator_resolve* self);
#endif