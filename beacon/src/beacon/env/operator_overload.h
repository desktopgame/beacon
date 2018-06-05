#ifndef BEACON_ENV_OPERATOR_OVERLOAD_H
#define BEACON_ENV_OPERATOR_OVERLOAD_H
#include "../ast/operator_type.h"
#include "../util/vector.h"
#include "../ast/access_level.h"
struct type;
struct enviroment;
struct generic_type;
typedef struct operator_overload {
	struct type* parent;
	struct generic_type* return_gtype;
	operator_type type;
	vector* parameter_list;
	struct enviroment* env;
	access_level access;
} operator_overload;

operator_overload* operator_overload_new(operator_type type);

void operator_overload_delete(operator_overload* self);
#endif