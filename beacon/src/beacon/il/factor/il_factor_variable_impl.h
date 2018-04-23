#pragma once
#ifndef BEACON_IL_IL_FACTOR_VARIABLE_H
#define BEACON_IL_IL_FACTOR_VARIABLE_H
#include "../il_factor_interface.h"
#include "../../env/fqcn_cache.h"
#include "../../env/generic_type.h"
#include "../../util/vector.h"
#include "variable/il_factor_variable_local_impl.h"
#include "variable/il_factor_variable_static_impl.h"
#include <stdbool.h>
#define IL_FACT2VAR(fact) (il_factor_cast_variable(fact))
//struct opcode_buf;
struct generic_type;
struct field;

/**
 * 変数の種類を判別する列挙.
 * beaconの構文定義では、次のものは全て一度 il_Variable として変換されます。
 * <code>
 * variable Namespace::Class variable<|T|> Namespace::Class<|T|>
 * </code>
 */
typedef enum il_variable_type {
	ilvariable_type_local,
	ilvariable_type_static,
	ilvariable_type_undefined
} il_variable_type;

/**
 * 変数を表す要素.
 */
typedef struct il_factor_variable {
	fqcn_cache* fqcn;
	vector* type_args;
	int index;
	il_variable_type type;
	union {
		il_factor_variable_local* local_;
		il_factor_variable_static* static_;
	} u;
} il_factor_variable;

/**
 * 変数をスーパーセットにラップします.
 * @param self
 * @return
 */
il_factor* il_factor_wrap_variable(il_factor_variable* self);

/**
 * 変数を作成します.
 * @return
 */
il_factor_variable* il_factor_variable_new();

/**
 * 変数を出力します.
 * @param self
 * @param depth
 */
void il_factor_variable_dump(il_factor_variable* self, int depth);

/**
 * 変数を生成します.
 * @param self
 * @param env
 * @param cache
 */
void il_factor_variable_generate(il_factor_variable* self, struct enviroment* env, il_context* ilctx);

/**
 * 変数を読み込みます.
 * @param self
 * @param env
 * @param cache
 * @param eh
 */
void il_factor_variable_load(il_factor_variable* self, struct enviroment* env, il_context* ilctx);

/**
 * 変数の型を返します.
 * @param self
 * @param env
 * @param cache
 * @return
 */
generic_type* il_factor_variable_eval(il_factor_variable* self, struct enviroment* env, il_context* ilctx);

/**
 * 変数を開放します.
 */
void il_factor_variable_delete(il_factor_variable* self);

il_factor_variable* il_factor_cast_variable(il_factor* fact);
#endif // !SIGNAL_IL_IL_FACTOR_VARIABLE_H
