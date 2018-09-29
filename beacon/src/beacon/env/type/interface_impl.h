#pragma once
#ifndef BEACON_ENV_TYPE_IINTERFACE_H
#define BEACON_ENV_TYPE_IINTERFACE_H
#include "../type_interface.h"
#include "../namespace.h"
#include "../vtable.h"
#include "../../il/call_context.h"
#include "../../util/vector.h"
#include "../../util/string_pool.h"
#include "interface_validate.h"
struct method;
struct property;
struct enviroment;
struct generic_type;
struct type;
/**
 * インターフェースを表す構造体.
 */
typedef struct interface_ {
	struct type* parent;
	string_view namev;
	Vector* impl_list;
	Vector* prop_list;
	Vector* method_list;
	namespace_* location;
	vtable* vt;
	Vector* type_parameter_list;
} interface_;

/**
 * インターフェイスをスーパーセットにラップします.
 * @param self
 * @return
 */
type* type_wrap_interface(interface_* self);

/** 
 * インターフェイスを作成します.
 * @param namev
 * @return
 */
interface_* interface_new(string_view namev);

/**
 * インターフェイスにメソッドを追加します.
 * @param self
 * @param m
 */
void interface_add_method(interface_* self, struct method* m);

/**
 * プロパティを追加します.
 * @param self
 * @param p
 */
void interface_add_property(interface_* self, struct property* p);

/**
 * インターフェイスからメソッドを検索します.
 * @param self
 * @param namev
 * @param args
 * @param env
 * @param cctx
 * @param outIndex
 * @return
 */
struct method* interface_ilfind_method(interface_* self, string_view namev, Vector * args, struct enviroment * env, call_context* cctx, int * outIndex);

/**
 * インターフェイスからメソッドを検索します.
 * @param self
 * @param namev
 * @param gargs
 * @param outIndex
 * @return
 */
struct method* interface_gfind_method(interface_* self, string_view namev, Vector* gargs, int* outIndex);

/**
 * 全てのインターフェイスに定義されたメソッドをフラットにして返します.
 * @param inter_list
 * @return
 */
Vector* interface_method_flatten_list(Vector* inter_list);

/**
 * あるインターフェイスとそれ自体が実装しているインターフェイスの一覧の
 * メソッドを一つのリストにして返します.
 * @param self
 * @return 呼び出し側で開放してください
 */
Vector* interface_method_flatten(interface_* self);

/**
 * メソッドの一覧から vtable を作成します.
 * @param self
 */
void interface_create_vtable(interface_* self);

/**
 * 型情報を残してメソッドやフィールドなどのみを開放します.
 * @param self
 */
void interface_unlink(interface_* self);

/**
 * インターフェイスを開放します.
 * @param self
 */
void interface_delete(interface_* self);

/**
 * self に find が含まれるなら NULL 以外の値を返します.
 * @param source
 * @param find
 * @return
 */
struct generic_type* interface_contains(struct generic_type* source, interface_* find);

/**
 * 関数型インターフェイスであるならtrue.
 * @param self
 * @return
 */
bool interface_is_functional(interface_* self);

/**
 * 関数型インターフェイスであるなら一つだけ定義されたメソッドを返します.
 * @param self
 * @return
 */
struct method* interface_get_function(interface_* self);

/**
 * このインターフェイスを除く継承された全てのインターフェイスを返します.
 * @param self
 * @return
 */
Vector* interface_get_generic_interface_tree(interface_* self);

/**
 * @param self
 * @param tiner
 * @param out_baseline
 * @return
 */
struct generic_type* interface_find_interface(interface_* self, type* tinter);
#endif // !SIGNAL_ENV_TYPE_IINTERFACE_H
