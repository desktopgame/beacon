#pragma once
#ifndef BEACON_IL_IL_STMT_EXPR_H
#define BEACON_IL_IL_STMT_EXPR_H
#include "../il_stmt_interface.h"
#include "../il_factor_interface.h"
/**
 * 式のみで構成される文を表す要素.
 */
typedef struct il_stmt_proc {
	il_factor* factor;
} il_stmt_proc;

/**
 * 式のみで構成される文を表す要素をスーパーセットにラップします.
 * @param self
 * @return
 */
il_stmt* WrapILProc(il_stmt_proc* self);

/**
 * 式のみで構成される文を表す要素を作成します.
 * @return
 */
il_stmt_proc* NewILProc();

/**
 * 式のみで構成される文を生成します.
 * @param self
 * @param env
 * @param cctx
 */
void il_stmt_proc_generate(il_stmt_proc* self, struct enviroment* env, call_context* cctx);

/**
 * 式のみで構成される文を読み込みます.
 * @param self
 * @param env
 * @param cctx
 */
void LoadILProc(il_stmt_proc* self, struct enviroment* env, call_context* cctx);

/**
 * 式のみで構成される文を表す要素を開放します.
 * @param self
 */
void DeleteILProc(il_stmt_proc* self);
#endif // !SIGNAL_IL_IL_STMT_EXPR_H
