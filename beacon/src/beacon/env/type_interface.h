#pragma once
#ifndef BEACON_ENV_TYPE_INTERFACE_H
#define BEACON_ENV_TYPE_INTERFACE_H
#include <stdbool.h>
#include "../util/vector.h"
#include "../il/il_context.h"

#define TYPE2CLASS(type) (type_cast_class(type))
#define TYPE2INTERFACE(type) (type_cast_interface(type))
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
struct generic_type;

/**
 * 型を表す構造体.
 */
typedef struct type {
	type_tag tag;
	struct namespace_* location;
	struct generic_type* generic_self;
	int absolute_index;
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
 * この型を表す generic_type を作成します.
 * @param self
 * @return
 */
struct generic_type* type_init_generic(type* self, int counts);

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
struct method* type_find_method(type* self, const char* name, vector* args, struct enviroment* env, il_context* ilctx, int* outIndex);

/**
 * この型から静的メソッドを検索します.
 * @param self
 * @param name
 * @param args
 * @param env
 * @param outIndex
 * @return
 */
struct method* type_find_smethod(type* self, const char* name, vector* args, struct enviroment* env, il_context* ilctx, int* outIndex);

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
 * 指定の名前の型変数が何番目に表れるかを返します.
 * @param self
 * @param name
 * @return
 */
int type_for_generic_index(type* self, char* name);

/**
 * selfの継承クラスや実装インターフェイスに a が現れるなら型変数付きで返します.
 * 例えば
 *
 * class IntList : List<Int>
 * を表すクラスに List<T> を渡すと List<Int> が返ります。
 * @param self
 * @param a
 * @return
 */
struct generic_type* type_find_impl(type* self, type* a);

/**
 * この型がクラス/インターフェイスを表すとき、
 * 指定位置の型変数を返します.
 * @param self
 * @param index
 * @return
 */
struct generic_type* type_type_parameter_at(type* self, int index);

/**
 * 型を開放します.
 * @param self
 */
void type_delete(type* self);

struct class_* type_cast_class(type* self);
struct interface_* type_cast_interface(type* self);
#endif // !SIGNAL_ENV_TYPE_INTERFACE_H
