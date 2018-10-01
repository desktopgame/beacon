#ifndef BEACON_IL_STMT_RETURN_EMPTY_H
#define BEACON_IL_STMT_RETURN_EMPTY_H
#include "../il_stmt_interface.h"

/**
 * 式を返却する文を生成します.
 * @param self
 * @param env
 * @param cctx
 */
void GenerateILReturnEmpty(il_stmt_return_empty self, struct enviroment* env, call_context* cctx);

/**
 * 式を返却する文を読み込みます.
 * @param self
 * @param env
 * @param cctx
 */
void LoadILReturnEmpty(il_stmt_return_empty self, struct enviroment* env, call_context* cctx);
#endif