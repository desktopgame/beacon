#pragma once
#ifndef BEACON_ENV_TYPE_PARAMETER_RULE_H
#define BEACON_ENV_TYPE_PARAMETER_RULE_H
#include "../util/vector.h"
struct generic_type;
struct il_type_parameter_rule;
struct il_load_cache;

typedef enum type_parameter_rule_tag {
	type_parameter_rule_tag_polymorphic,
	type_parameter_rule_tag_neweable,
} type_parameter_rule_tag;

typedef struct type_parameter_rule {
	type_parameter_rule_tag tag;
	union {
		struct generic_type* gtype_;
	} u;
} type_parameter_rule;

type_parameter_rule* type_parameter_rule_new();

type_parameter_rule* type_parameter_rule_dup(struct il_type_parameter_rule* src, struct il_load_cache* cache);

void type_parameter_rule_list_dup(vector* ilSource, vector* sgDest, struct il_load_cache* cache);

void type_parameter_rule_list_print(vector* v);

void type_parameter_rule_delete(type_parameter_rule* self);
#endif // !SIGNAL_ENV_TYPE_PARAMETER_RULE_H
