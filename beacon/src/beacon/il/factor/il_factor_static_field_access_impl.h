#pragma once
#ifndef BEACON_IL_IL_FACTOR_STATIC_FIELD_ACCESS_H
#define BEACON_IL_IL_FACTOR_STATIC_FIELD_ACCESS_H
#include "../../env/generic_cache.h"
#include "../../util/vector.h"
#include "../il_factor_interface.h"
struct enviroment;
struct type;
struct field;
//NOTE:これについては型変数は不要
//でもほとんどのインターフェイスがジェネリックで受け取るのでラップしておく
/**
 * X::Y.a のようなフィールドアクセスを表す要素.
 */
typedef struct il_factor_static_field_access {
	generic_cache* fqcn;
	char* name;
	struct field* f;
	int field_index;
	//構文規則のために、フィールドアクセスが
	//実型引数をもつ。
	//namespace::foo<Int>
	vector* type_argument_list;
} il_factor_static_field_access;

/**
 * 静的フィールドアクセスをスーパーセットにラップします.
 * @param self
 * @return
 */
il_factor* il_factor_wrap_static_field_access(il_factor_static_field_access* self);

/**
 * 静的フィールドアクセスを表す要素を作成します.
 * @param name
 * @return
 */
il_factor_static_field_access* il_factor_static_field_access_new(const char* name);

/**
 * 静的フィールドアクセスを表す要素を出力します.
 * @param self
 * @param depth
 */
void il_factor_static_field_access_dump(il_factor_static_field_access* self, int depth);

/**
 * 静的フィールドアクセスを表す要素を生成します.
 * @param self
 * @param env
 * @param cache
 */
void il_factor_static_field_access_generate(il_factor_static_field_access* self, struct enviroment* env, il_load_cache* cache);

/**
 * 静的フィールドアクセスを表す要素の結果の型を返します.
 * @param self
 * @param env
 * @param cache
 * @return
 */
generic_type* il_factor_static_field_access_eval(il_factor_static_field_access* self, struct enviroment* env, il_load_cache* cache);

/**
 * 静的フィールドアクセスを表す要素を読み込みます.
 * @param self
 * @param env
 * @param cache
 * @param eh
 */
void il_factor_static_field_access_load(il_factor_static_field_access* self, struct enviroment* env, il_load_cache* cache, il_ehandler* eh);

/**
 * 静的フィールドを表す要素を削除します.
 * @param self
 */
void il_factor_static_field_access_delete(il_factor_static_field_access* self);
#endif // !SIGNAL_IL_IL_FACTOR_STATIC_FIELD_ACCESS_H
