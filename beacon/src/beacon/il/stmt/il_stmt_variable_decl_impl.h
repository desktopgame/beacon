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
typedef struct ILVariableDecl {
	GenericCache* GCache;
	StringView Name;
} ILVariableDecl;
/**
 * 型宣言を表す要素をスーパーセットにラップします.
 * @param self
 * @return
 */
ILStatement* WrapILVariableDecl(ILVariableDecl* self);

/**
 * 型宣言を表す要素を作成します.
 * @param namev
 * @return
 */
ILVariableDecl* NewILVariableDecl(StringView namev);

/**
 * 型宣言を表す要素を出力します.
 * @param self
 * @param env
 * @param cctx
 */
void GenerateILVariableDecl(ILVariableDecl* self, Enviroment* env, CallContext* cctx);

/**
 * 型宣言を表す要素を出力します.
 * @param self
 * @param env
 * @param cctx
 */
void LoadILVariableDecl(ILVariableDecl* self, Enviroment* env, CallContext* cctx);

/**
 * 型宣言を表す要素を開放します.
 * @param self
 */
void DeleteILVariableDecl(ILVariableDecl* self);
#endif // !SIGNAL_IL_IL_STMT_VARIABLE_DECL_H
