#pragma once
#ifndef SIGNAL_IL_IL_STMT_EXPR_H
#define SIGNAL_IL_IL_STMT_EXPR_H
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
il_stmt* il_stmt_wrap_proc(il_stmt_proc* self);

/**
 * 式のみで構成される文を表す要素を作成します.
 * @return
 */
il_stmt_proc* il_stmt_proc_new();

/**
 * 式のみで構成される文を表す要素を出力します.
 * @param self
 * @param depth
 */
void il_stmt_proc_dump(il_stmt_proc* self, int depth);

/**
 * 式のみで構成される文を生成します.
 * @param self
 * @param env
 */
void il_stmt_proc_generate(il_stmt_proc* self, struct enviroment* env);

/**
 * 式のみで構成される文を読み込みます.
 * @param self
 * @param env
 * @param eh
 */
void il_stmt_proc_load(il_stmt_proc* self, struct enviroment* env, il_ehandler* eh);

/**
 * 式のみで構成される文を表す要素を開放します.
 * @param self
 */
void il_stmt_proc_delete(il_stmt_proc* self);
#endif // !SIGNAL_IL_IL_STMT_EXPR_H
