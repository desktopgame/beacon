#ifndef BEACON_IL_IL_OPERATOR_OVERLOAD_H
#define BEACON_IL_IL_OPERATOR_OVERLOAD_H
#include "../ast/operator_type.h"
#include "../util/vector.h"
#include "../env/generic_cache.h"
#include "il_type_interface.h"
#include "../ast/access_level.h"
typedef struct il_operator_overload {
	operator_type op;
	Vector* parameter_list;
	Vector* statement_list;
	generic_cache* return_fqcn;
	AccessLevel access;
} il_operator_overload;

il_operator_overload* NewILOperatorOverload(operator_type type);

void DeleteILOperatorOverload(il_operator_overload* self);
#endif