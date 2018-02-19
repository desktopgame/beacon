#pragma once
#ifndef SIGNAL_ENV_TYPE_INTERFACE_H
#define SIGNAL_ENV_TYPE_INTERFACE_H
#include <stdbool.h>
#include "../util/vector.h"
#include "../il/il_load_cache.h"
/**
 * 型の種類を表すタグ.
 */
typedef enum type_tag {
	type_class,
	type_interface,
	type_enum
} type_tag;

struct namespace_;
struct class_;
struct interface_;
struct field;
struct method;
struct enviroment;
struct vtable;

/**
 * 型を表す構造体.
 */
typedef struct type {
	type_tag tag;
	struct namespace_* location;
	int absoluteIndex;
	union {
		struct class_* class_;
		struct interface_* interface_;
	} u;
} type;

/**
 * 型を作成します.
 * @return
 */
type* type_new();

/**
 * この型の名前を返します.
 * @param self
 * @return
 */
char* type_name(type* self);

/**
 * この型にフィールドを追加します.
 * @param self
 * @param f
 */
void type_add_field(type* self, struct field* f);

/**
 * この型にメソッドを追加します.
 * @param self
 * @param m
 */
void type_add_method(type* self, struct method* m);

/**
 * この型からメソッドを検索します.
 * @param self
 * @param name
 * @param args
 * @param env
 * @param outIndex
 * @return
 */
struct method* type_find_method(type* self, const char* name, vector* args, struct enviroment* env, il_load_cache* cache, int* outIndex);

/**
 * 仮想関数の一覧を返します.
 * @param self
 * @return
 */
struct vtable* type_vtable(type* self);

/**
 * この型の名前を出力します.
 * @param self
 * @param depth
 */
void type_dump(type* self, int depth);

/**
 * 型の距離を返します.
 * @param a
 * @param b
 * @return
 */
int type_distance(type* a, type* b);

/**
 * self を other に変換出来るなら true.
 * @param self
 * @param other
 * @return
 */
bool type_castable(type* self, type* other);

/**
 * 型情報を残してメソッドやフィールドなどのみを開放します.
 * @param self
 */
void type_unlink(type* self);

/**
 * 型を開放します.
 * @param self
 */
void type_delete(type* self);
#endif // !SIGNAL_ENV_TYPE_INTERFACE_H
