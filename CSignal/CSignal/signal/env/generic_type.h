#pragma once
#ifndef SIGNAL_ENV_GENERIC_TYPE_H
#define SIGNAL_ENV_GENERIC_TYPE_H
#include "../util/vector.h"
#include <stdbool.h>
struct type;

typedef struct generic_type {
	struct type* core_type;
	vector* type_args_list;
	//もしこの型が List<T> の Tを表すなら、
	//外側のクラスの何番目の型変数かを格納する。
	int virtual_type_index;
} generic_type;

generic_type* generic_type_new(struct type* core_type);

bool generic_type_assignable(generic_type* left, generic_type* right);

void generic_type_print(generic_type* self);

void generic_type_delete(generic_type* self);
#endif // !SIGNAL_ENV_GENERIC_TYPE_H
