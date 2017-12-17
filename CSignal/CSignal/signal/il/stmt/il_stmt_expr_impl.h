#pragma once
#ifndef SIGNAL_IL_IL_STMT_EXPR_H
#define SIGNAL_IL_IL_STMT_EXPR_H
#include "../il_factor_interface.h"
/**
 * 式のみで構成される文を表す要素.
 */
typedef struct il_stmt_expr {
	il_factor* factor;
} il_stmt_expr;

/**
 * 式のみで構成される文を表す要素を作成します.
 * @return
 */
il_stmt_expr* il_stmt_expr_new();

/**
 * 式のみで構成される文を表す要素を開放します.
 * @param self
 */
void il_stmt_expr_delete(il_stmt_expr* self);
#endif // !SIGNAL_IL_IL_STMT_EXPR_H
