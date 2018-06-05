#ifndef BEACON_ENV_OPERATOR_OVERLOAD_H
#define BEACON_ENV_OPERATOR_OVERLOAD_H
#include "../ast/operator_type.h"
#include "../util/vector.h"
struct type;
struct enviroment;
typedef struct operator_overload {
	struct type* parent;
	operator_type type;
	vector* parameter_list;
	struct enviroment* env;
} operator_overload;

operator_overload* operator_overload_new(operator_type type);

void operator_overload_delete(operator_overload* self);
#endif