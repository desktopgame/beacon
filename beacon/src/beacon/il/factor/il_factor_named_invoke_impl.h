#pragma once
#ifndef SIGNAL_IL_IL_FACTOR_STATIC_INVOKE_H
#define SIGNAL_IL_IL_FACTOR_STATIC_INVOKE_H
#include "../../env/type_interface.h"
#include "../../util/vector.h"
#include "../../vm/enviroment.h"
#include "../il_factor_interface.h"
#include "../../env/generic_cache.h"
struct method;
struct generic_type;
/**
 * 名前付き呼び出しの種類を表します.
 */
typedef enum il_named_invoke_type {
	ilnamed_invoke_variable,
	ilnamed_invoke_static
} il_named_invoke_type;

/**
 * 完全に修飾されたメソッド呼び出し.
 * 厳密には、修飾のない規則にもマッチする場合があります。
 *
 * 例えば:
 * XX::YY::C.Foo();
 * C.Foo();
 *
 * この二つはどちらも同じ規則でマッチします。
 * 末尾の identifier を区別できないので、
 * とりあえずこのままにしています。
 */
typedef struct il_factor_named_invoke {
	char* method_name;
	//vector* scope_vec;
	//char* class_name;
	generic_cache* fqcn;
	struct generic_type* return_type;
	vector* argument_list;
	vector* type_argument_list;
	il_named_invoke_type type;
	struct method* m;
	int method_index;
	bool find;
	union {
		struct type* type;
		il_factor* factor;
	} u;
} il_factor_named_invoke;
/**
 * 完全に修飾されたメソッド呼び出しをスーパーセットにラップします.
 * @param self
 * @return
 */
il_factor* il_factor_wrap_named_invoke(il_factor_named_invoke* self);

/**
 * 完全に修飾されたメソッド呼び出しを作成します.
 * @param method_name
 * @return
 */
il_factor_named_invoke* il_factor_named_invoke_new(const char* method_name);

/**
 * 完全に修飾されたメソッド呼び出しを出力します.
 * @param self
 * @param depth
 */
void il_factor_named_invoke_dump(il_factor_named_invoke* self, int depth);

/**
 * 完全に修飾されたメソッド呼び出しを開放します.
 * @param self
 * @param env
 * @param cache
 */
void il_factor_named_invoke_generate(il_factor_named_invoke* self, enviroment* env, il_load_cache* cache);

/**
 * メソッド呼び出しを読み込みます.
 * @param self
 * @param env
 * @param cache
 * @param eh
 */
void il_factor_named_invoke_load(il_factor_named_invoke* self, enviroment* env, il_load_cache* cache, il_ehandler* eh);

/**
 * メソッド呼び出しの戻り値の型を返します.
 * @param self
 * @param env
 * @param cache
 * @return
 */
generic_type* il_factor_named_invoke_eval(il_factor_named_invoke* self, enviroment* env, il_load_cache* cache);

/**
 * 完全に修飾されたメソッド呼び出しを開放します.
 * @param self
 */
void il_factor_named_invoke_delete(il_factor_named_invoke* self);
#endif // !SIGNAL_IL_IL_FACTOR_STATIC_INVOKE_H