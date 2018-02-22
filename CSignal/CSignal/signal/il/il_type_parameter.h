#pragma once
#ifndef SIGNAL_IL_IL_TYPE_PARAMETER_H
#define SIGNAL_IL_IL_TYPE_PARAMETER_H
#include "../util/vector.h"

typedef enum il_type_parameter_kind {
	il_type_parameter_kind_default,
	il_type_parameter_kind_in,
	il_type_parameter_kind_out,
} il_type_parameter_kind;

typedef struct il_type_parameter {
	il_type_parameter_kind kind;
	char* name;
} il_type_parameter;

il_type_parameter* il_type_parameter_new(char* name);

void il_type_parameter_list_print(vector* v);

void il_type_parameter_delete(il_type_parameter* self);
#endif // !SIGNAL_IL_IL_TYPE_PARAMETER_H
