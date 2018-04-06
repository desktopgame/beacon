#pragma once
#ifndef BEACON_ENV_GENERIC_TYPE_H
#define BEACON_ENV_GENERIC_TYPE_H
#include "../util/vector.h"
#include <stdbool.h>
struct type;
struct method;
struct enviroment;
struct il_context;

typedef enum generic_type_tag {
	generic_type_tag_none,
	generic_type_tag_class,
	generic_type_tag_method,
} generic_type_tag;

typedef struct generic_type {
	struct type* core_type;
	vector* type_args_list;
	//このジェネリックタイプの紐づけたられたコンテナ
	union {
		struct type* type_;
		struct method* method_;
	} u;
	//もしこの型が List<T> の Tを表すなら、
	//外側のクラスの何番目の型変数かを格納する。
	int virtual_type_index;
	int ref_count;
	generic_type_tag tag;
} generic_type;

generic_type* generic_type_new(struct type* core_type);

void generic_type_fixtype(generic_type* self);

void generic_type_addargs(generic_type* self, generic_type* a);

bool generic_type_castable(generic_type* a, generic_type* b);

int generic_type_distance(generic_type* a, generic_type* b);

void generic_type_print(generic_type* self);

void generic_type_delete(generic_type* self);

bool generic_type_int(generic_type* self);

bool generic_type_double(generic_type* self);

bool generic_type_bool(generic_type* self);

generic_type* generic_type_apply(generic_type* self, struct il_context* ilctx);

struct method* generic_type_find_method(generic_type* self, const char* name, vector* args, struct enviroment* env, struct il_context* ilctx, int* outIndex);
#endif // !SIGNAL_ENV_GENERIC_TYPE_H
