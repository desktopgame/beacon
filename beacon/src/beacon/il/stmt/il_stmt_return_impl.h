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
il_stmt* WrapILReturn(il_stmt_return* self);

/**
 * 式を返却する文を作成します.
 * @return
 */
il_stmt_return* NewILReturn();

/**
 * 式を返却する文を生成します.
 * @param self
 * @param env
 * @param cctx
 */
void GenerateILReturn(il_stmt_return* self, struct enviroment* env, call_context* cctx);

/**
 * 式を返却する文を読み込みます.
 * @param self
 * @param env
 * @param cctx
 */
void LoadILReturn(il_stmt_return* self, struct enviroment* env, call_context* cctx);

/**
 * 式を返却する文を開放します.
 * @param self
 */
void DeleteILReturn(il_stmt_return* self);
#endif // !SIGNAL_IL_IL_STMT_RETURN_H
