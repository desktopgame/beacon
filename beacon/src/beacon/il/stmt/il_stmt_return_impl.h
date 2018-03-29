#pragma once
#ifndef BEACON_IL_IL_STMT_RETURN_H
#define BEACON_IL_IL_STMT_RETURN_H
#include "../il_factor_interface.h"
#include "../il_stmt_interface.h"
struct enviroment;
/**
 * 値の返却を表す要素.
 */
typedef struct il_stmt_return {
	il_factor* fact;
} il_stmt_return;

/**
 * 式を返却する文をスーパーセットにラップします.
 * @param self
 * @return
 */
il_stmt* il_stmt_wrap_return(il_stmt_return* self);

/**
 * 式を返却する文を作成します.
 * @return
 */
il_stmt_return* il_stmt_return_new();

/**
 *  式を返却する文を出力します.
 * @param self
 * @param depth
 */
void il_stmt_return_dump(il_stmt_return* self, int depth);

/**
 * 式を返却する文を生成します.
 * @param self
 * @param env
 * @param cache
 */
void il_stmt_return_generate(il_stmt_return* self, struct enviroment* env, il_load_cache* cache);

/**
 * 式を返却する文を読み込みます.
 * @param self
 * @param env
 * @param cache
 * @param eh
 */
void il_stmt_return_load(il_stmt_return* self, struct enviroment* env, il_load_cache* cache, il_ehandler* eh);

/**
 * 式を返却する文を開放します.
 * @param self
 */
void il_stmt_return_delete(il_stmt_return* self);
#endif // !SIGNAL_IL_IL_STMT_RETURN_H
