#pragma once
#ifndef BEACON_ENV_TYPE_PARAMETER_H
#define BEACON_ENV_TYPE_PARAMETER_H
struct vector;
struct il_type_parameter;
struct il_context;

typedef enum type_parameter_kind {
	type_parameter_kind_default,
	type_parameter_kind_in,
	type_parameter_kind_out,
} type_parameter_kind;

typedef struct type_parameter {
	char* name;
	type_parameter_kind kind;
//	struct vector* rule_vec;
} type_parameter;

type_parameter* type_parameter_new(char* name);

type_parameter* type_parameter_dup(struct il_type_parameter* src, struct il_context* ilctx);

void type_parameter_list_dup(struct vector* ilSource, struct vector* sgDest, struct il_context* ilctx);

void type_parameter_print(struct vector* v);

void type_parameter_delete(type_parameter* self);
#endif // !SIGNAL_ENV_TYPE_PARAMETER_H
