#pragma once
#ifndef BEACON_IL_IL_STMT_VARIABLE_INIT_H
#define BEACON_IL_IL_STMT_VARIABLE_INIT_H
#include "../../env/generic_cache.h"
#include "../../util/string_pool.h"
#include "../il_stmt_interface.h"
#include "../il_factor_interface.h"
struct Enviroment;
struct SymbolEntry;
/**
 * 変数の初期化を表す要素.
 */
typedef struct il_stmt_variable_init {
	generic_cache* fqcn;
	StringView namev;
	il_factor* fact;
	struct SymbolEntry* sym;
} il_stmt_variable_init;

/**
 * 変数の初期化を表す要素をスーパーセットにラップします.
 * @param self
 * @return
 */
il_stmt* WrapILVariableInit(il_stmt_variable_init* self);

/**
 * 変数の初期化を表す要素を作成します.
 * @param namev
 * @return
 */
il_stmt_variable_init* NewILVariableInit(StringView namev);

/**
 * 変数の初期化を表す要素を出力します.
 * @param depth
 * @param env
 * @param ccctx
 */
void GenerateILVariableInit(il_stmt_variable_init* self, Enviroment* env, CallContext* cctx);

/**
 * 変数の初期化を表す要素を読み込みます.
 * @param self
 * @param env
 * @param cctx
 */
void LoadILVariableInit(il_stmt_variable_init* self, Enviroment* env, CallContext* cctx);

/**
 * 変数の初期化を表す要素を開放します.
 * @param self
 */
void DeleteILVariableInit(il_stmt_variable_init* self);
#endif // !SIGNAL_IL_IL_STMT_VARIABLE_INIT_H
