#ifndef BEACON_IL_STMT_RETURN_EMPTY_H
#define BEACON_IL_STMT_RETURN_EMPTY_H
#include "../il_stmt_interface.h"
/**
 *  式を返却する文を出力します.
 * @param self
 * @param depth
 */
void il_stmt_return_empty_dump(il_stmt_return_empty self, int depth);

/**
 * 式を返却する文を生成します.
 * @param self
 * @param env
 * @param cctx
 */
void il_stmt_return_empty_generate(il_stmt_return_empty self, struct enviroment* env, call_context* cctx);

/**
 * 式を返却する文を読み込みます.
 * @param self
 * @param env
 * @param cctx
 */
void il_stmt_return_empty_load(il_stmt_return_empty self, struct enviroment* env, call_context* cctx);
#endif