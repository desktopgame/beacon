#pragma once
#ifndef SIGNAL_ENV_GENERIC_TYPE_H
#define SIGNAL_ENV_GENERIC_TYPE_H
#include "../util/vector.h"
struct type;

typedef struct generic_type {
	struct type* core_type;
	vector* type_args_list;
} generic_type;

generic_type* generic_type_new(struct type* core_type);

void generic_type_delete(generic_type* self);
#endif // !SIGNAL_ENV_GENERIC_TYPE_H
