#pragma once
#ifndef BEACON_IL_IL_STMT_VARIABLE_DECL_H
#define BEACON_IL_IL_STMT_VARIABLE_DECL_H
#include "../il_stmt_interface.h"
#include "../../util/string_pool.h"
#include "../../env/generic_cache.h"
struct enviroment;
/**
 * 型宣言を表す要素.
 */
typedef struct il_stmt_variable_decl {
	generic_cache* fqcn;
	string_view namev;
} il_stmt_variable_decl;
/**
 * 型宣言を表す要素をスーパーセットにラップします.
 * @param self
 * @return
 */
il_stmt* WrapILVariableDecl(il_stmt_variable_decl* self);

/**
 * 型宣言を表す要素を作成します.
 * @param namev
 * @return
 */
il_stmt_variable_decl* NewILVariableDecl(string_view namev);

/**
 * 型宣言を表す要素を出力します.
 * @param self
 * @param env
 * @param cctx
 */
void il_stmt_variable_decl_generate(il_stmt_variable_decl* self, struct enviroment* env, call_context* cctx);

/**
 * 型宣言を表す要素を出力します.
 * @param self
 * @param env
 * @param cctx
 */
void LoadILVariableDecl(il_stmt_variable_decl* self, struct enviroment* env, call_context* cctx);

/**
 * 型宣言を表す要素を開放します.
 * @param self
 */
void il_stmt_variable_decl_delete(il_stmt_variable_decl* self);
#endif // !SIGNAL_IL_IL_STMT_VARIABLE_DECL_H
