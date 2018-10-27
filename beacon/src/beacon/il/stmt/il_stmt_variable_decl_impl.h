#pragma once
#ifndef BEACON_IL_IL_STMT_VARIABLE_DECL_H
#define BEACON_IL_IL_STMT_VARIABLE_DECL_H
#include "../il_stmt_interface.h"
#include "../../util/string_pool.h"
#include "../../env/generic_cache.h"
struct Enviroment;
/**
 * 型宣言を表す要素.
 */
typedef struct ILStatement_variable_decl {
	GenericCache* fqcn;
	StringView namev;
} ILStatement_variable_decl;
/**
 * 型宣言を表す要素をスーパーセットにラップします.
 * @param self
 * @return
 */
ILStatement* WrapILVariableDecl(ILStatement_variable_decl* self);

/**
 * 型宣言を表す要素を作成します.
 * @param namev
 * @return
 */
ILStatement_variable_decl* NewILVariableDecl(StringView namev);

/**
 * 型宣言を表す要素を出力します.
 * @param self
 * @param env
 * @param cctx
 */
void GenerateILVariableDecl(ILStatement_variable_decl* self, Enviroment* env, CallContext* cctx);

/**
 * 型宣言を表す要素を出力します.
 * @param self
 * @param env
 * @param cctx
 */
void LoadILVariableDecl(ILStatement_variable_decl* self, Enviroment* env, CallContext* cctx);

/**
 * 型宣言を表す要素を開放します.
 * @param self
 */
void DeleteILVariableDecl(ILStatement_variable_decl* self);
#endif // !SIGNAL_IL_IL_STMT_VARIABLE_DECL_H
