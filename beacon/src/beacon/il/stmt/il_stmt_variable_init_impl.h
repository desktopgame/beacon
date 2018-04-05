#pragma once
#ifndef BEACON_IL_IL_STMT_VARIABLE_INIT_H
#define BEACON_IL_IL_STMT_VARIABLE_INIT_H
#include "../../env/generic_cache.h"
#include "../il_stmt_interface.h"
#include "../il_factor_interface.h"
struct enviroment;
struct symbol_entry;
/**
 * 変数の初期化を表す要素.
 */
typedef struct il_stmt_variable_init {
	generic_cache* fqcn;
	char* name;
	il_factor* fact;
	struct symbol_entry* sym;
} il_stmt_variable_init;

/**
 * 変数の初期化を表す要素をスーパーセットにラップします.
 * @param self
 * @return
 */
il_stmt* il_stmt_wrap_variable_init(il_stmt_variable_init* self);

/**
 * 変数の初期化を表す要素を作成します.
 * @param name
 * @return
 */
il_stmt_variable_init* il_stmt_variable_init_new(const char* name);

/**
 * 変数の初期化を表す要素を出力します.
 * @param self
 * @param depth
 * @return
 */
void il_stmt_variable_init_dump(il_stmt_variable_init* self, int depth);

/**
 * 変数の初期化を表す要素を出力します.
 * @param depth
 * @param env
 * @param cache
 */
void il_stmt_variable_init_generate(il_stmt_variable_init* self, struct enviroment* env, il_context* ilctx);

/**
 * 変数の初期化を表す要素を読み込みます.
 * @param self
 * @param env
 * @param cache
 * @param eh
 */
void il_stmt_variable_init_load(il_stmt_variable_init* self, struct enviroment* env, il_context* ilctx, il_ehandler* eh);

/**
 * 変数の初期化を表す要素を開放します.
 * @param self
 */
void il_stmt_variable_init_delete(il_stmt_variable_init* self);
#endif // !SIGNAL_IL_IL_STMT_VARIABLE_INIT_H
