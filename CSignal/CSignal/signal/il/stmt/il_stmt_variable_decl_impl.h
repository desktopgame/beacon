#pragma once
#ifndef SIGNAL_IL_IL_STMT_VARIABLE_DECL_H
#define SIGNAL_IL_IL_STMT_VARIABLE_DECL_H
#include "../il_type.h"
#include "../il_stmt_interface.h"
#include "../../env/fqcn_cache.h"
struct enviroment;
/**
 * 型宣言を表す要素.
 */
typedef struct il_stmt_variable_decl {
	fqcn_cache* fqcn;
	char* name;
} il_stmt_variable_decl;
/**
 * 型宣言を表す要素をスーパーセットにラップします.
 * @param self
 * @return
 */
il_stmt* il_stmt_wrap_variable_decl(il_stmt_variable_decl* self);

/**
 * 型宣言を表す要素を作成します.
 * @param name
 * @return
 */
il_stmt_variable_decl* il_stmt_variable_decl_new(const char* name);

/**
 * 型宣言を表す要素を出力します.
 * @param self
 * @param depth
 */
void il_stmt_variable_decl_dump(il_stmt_variable_decl* self, int depth);

/**
 * 型宣言を表す要素を出力します.
 * @param self
 * @param env
 */
void il_stmt_variable_decl_generate(il_stmt_variable_decl* self, struct enviroment* env);

/**
 * 型宣言を表す要素を開放します.
 * @param self
 */
void il_stmt_variable_decl_delete(il_stmt_variable_decl* self);
#endif // !SIGNAL_IL_IL_STMT_VARIABLE_DECL_H
