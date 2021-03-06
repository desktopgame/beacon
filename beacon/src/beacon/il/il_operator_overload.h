#ifndef BEACON_IL_IL_OPERATOR_OVERLOAD_H
#define BEACON_IL_IL_OPERATOR_OVERLOAD_H
#include "../ast/operator_type.h"
#include "../util/vector.h"
#include "../env/generic_cache.h"
#include "il_type_interface.h"
#include "../ast/access_level.h"
typedef struct il_operator_overload {
	operator_type op;
	vector* parameter_list;
	vector* statement_list;
	generic_cache* return_fqcn;
	access_level access;
} il_operator_overload;

il_operator_overload* il_operator_overload_new(operator_type type);

void il_operator_overload_dump(il_operator_overload* self, int depth);

void il_operator_overload_delete(il_operator_overload* self);
#endif