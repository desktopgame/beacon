#pragma once
#ifndef BEACON_IL_IL_STMT_INFERENCED_TYPE_INIT
#define BEACON_IL_IL_STMT_INFERENCED_TYPE_INIT
#include "../il_factor_interface.h"
#include "../il_stmt_interface.h"
#include "../../util/string_pool.h"
struct enviroment;
struct symbol_entry;
/**
 * 推論された型の初期化を表す要素.
 * var y = new X::Y();
 */
typedef struct il_stmt_inferenced_type_init {
	string_view namev;
	il_factor* fact;
	struct symbol_entry* sym;
} il_stmt_inferenced_type_init;

/**
 * 推論された型の初期化を表す要素をスーパーセットにラップします.
 * @param self
 * @return
 */
il_stmt* il_stmt_wrap_inferenced_type_init(il_stmt_inferenced_type_init* self);

/**
 * 推論された型の初期化を表す要素を作成します.
 * @param namev
 * @return
 */
il_stmt_inferenced_type_init* il_stmt_inferenced_type_init_new(string_view namev);

/**
 * 推論された型の初期化を表す要素を出力します.
 * @param self
 * @param depth
 */
void il_stmt_inferenced_type_init_dump(il_stmt_inferenced_type_init* self, int depth);

/**
 * 推論された型の初期化を表す要素を生成します.
 * @param self
 * @param env
 * @param cctx
 */
void il_stmt_inferenced_type_init_generate(il_stmt_inferenced_type_init* self, struct enviroment* env, call_context* cctx);

/**
 * 推論された型の初期化を表す要素を読み込みます.
 * @param self
 * @param env
 * @param cctx
 */
void il_stmt_inferenced_type_init_load(il_stmt_inferenced_type_init* self, struct enviroment* env, call_context* cctx);

/**
 * 推論された型の初期化を表す要素を開放します.
 * @param self
 */
void il_stmt_inferenced_type_init_delete(il_stmt_inferenced_type_init* self);
#endif // !SIGNAL_IL_IL_STMT_INFERENCED_TYPE_INIT
