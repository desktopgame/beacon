#pragma once
#ifndef SIGNAL_IL_IL_TYPE_PARAMETER_RULE_H
#define SIGNAL_IL_IL_TYPE_PARAMETER_RULE_H
#include "../env/fqcn_cache.h"
struct vector;

typedef enum il_type_parameter_rule_tag {
	il_type_parameter_rule_polymorphic,
	il_type_parameter_rule_neweable,
} il_type_parameter_rule_tag;

typedef struct il_type_parameter_rule {
	il_type_parameter_rule_tag tag;
	union {
		fqcn_cache* fqcn_;
	} u;
} il_type_parameter_rule;

il_type_parameter_rule* il_type_parameter_rule_new();

void il_type_parameter_rule_list_print(struct vector* v);

void il_type_parameter_rule_delete(il_type_parameter_rule* self);
#endif // !SIGNAL_IL_IL_TYPE_PARAMETER_RULE_H
