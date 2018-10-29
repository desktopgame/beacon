#pragma once
#ifndef BEACON_IL_IL_STMT_INFERENCED_TYPE_INIT
#define BEACON_IL_IL_STMT_INFERENCED_TYPE_INIT
#include "../il_factor_interface.h"
#include "../il_stmt_interface.h"
#include "../../util/string_pool.h"
struct Enviroment;
struct SymbolEntry;
/**
 * 推論された型の初期化を表す要素.
 * var y = new X::Y();
 */
typedef struct ILInferencedTypeInit {
	StringView Name;
	ILFactor* Value;
	struct SymbolEntry* Symbol;
} ILInferencedTypeInit;

/**
 * 推論された型の初期化を表す要素をスーパーセットにラップします.
 * @param self
 * @return
 */
ILStatement* WrapILInferencedTypeInit(ILInferencedTypeInit* self);

/**
 * 推論された型の初期化を表す要素を作成します.
 * @param namev
 * @return
 */
ILInferencedTypeInit* NewILInferencedTypeInit(StringView namev);

/**
 * 推論された型の初期化を表す要素を生成します.
 * @param self
 * @param env
 * @param cctx
 */
void GenerateILInferencedTypeInit(ILInferencedTypeInit* self, Enviroment* env, CallContext* cctx);

/**
 * 推論された型の初期化を表す要素を読み込みます.
 * @param self
 * @param env
 * @param cctx
 */
void LoadILInferencedTypeInit(ILInferencedTypeInit* self, Enviroment* env, CallContext* cctx);

/**
 * 推論された型の初期化を表す要素を開放します.
 * @param self
 */
void DeleteILInferencedTypeInit(ILInferencedTypeInit* self);
#endif // !SIGNAL_IL_IL_STMT_INFERENCED_TYPE_INIT
