#pragma once
#ifndef BEACON_IL_IL_FACTOR_VARIABLE_H
#define BEACON_IL_IL_FACTOR_VARIABLE_H
#include "../il_factor_interface.h"
#include "../../env/fqcn_cache.h"
#include "../../env/generic_type.h"
#include "../../util/vector.h"
#include <stdbool.h>
#define IL_FACT2VAR(fact) (il_factor_cast_variable(fact))
//struct opcode_buf;
struct generic_type;
struct field;
/**
 * 変数を表す要素.
 */
typedef struct il_factor_variable {
	fqcn_cache* fqcn;
	vector* type_args;
	int index;
} il_factor_variable;

/**
 * 変数をスーパーセットにラップします.
 * @param self
 * @return
 */
il_factor* il_factor_wrap_variable(il_factor_variable* self);

/**
 * 変数を作成します.
 * @param name
 * @return
 */
il_factor_variable* il_factor_variable_new(const char* name);

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
void il_factor_variable_generate(il_factor_variable* self, struct enviroment* env, il_load_cache* cache);

/**
 * 変数を読み込みます.
 * @param self
 * @param env
 * @param cache
 * @param eh
 */
void il_factor_variable_load(il_factor_variable* self, struct enviroment* env, il_load_cache* cache, il_ehandler* eh);

/**
 * 変数の型を返します.
 * @param self
 * @param env
 * @param cache
 * @return
 */
generic_type* il_factor_variable_eval(il_factor_variable* self, struct enviroment* env, il_load_cache* cache);

/**
 * 変数を開放します.
 */
void il_factor_variable_delete(il_factor_variable* self);

il_factor_variable* il_factor_cast_variable(il_factor* fact);
#endif // !SIGNAL_IL_IL_FACTOR_VARIABLE_H
