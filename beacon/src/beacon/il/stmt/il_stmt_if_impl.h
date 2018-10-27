#pragma once
#ifndef BEACON_IL_IL_STMT_IF_IMPL_H
#define BEACON_IL_IL_STMT_IF_IMPL_H
#include "../../util/vector.h"
#include "../il_factor_interface.h"
#include "../il_stmt_interface.h"
/**
 * elif (...) { ... } を表す要素.
 */
typedef struct ILStatement_elif {
	ILFactor* condition;
	Vector* body;
} ILStatement_elif;

/**
 * } else { ... } を表す要素.
 */
typedef struct ILStatement_else {
	Vector* body;
} ILStatement_else;

/**
 * if (...) {
 *    ...
 * }
 * を表す要素.
 */
typedef struct ILStatement_if {
	ILFactor* condition;
	Vector* body;
	Vector* elif_list;
	ILStatement_else* else_body;
} ILStatement_if;

/**
 * if をスーパーセットにラップします.
 * @param self
 * @return
 */
ILStatement* WrapILIf(ILStatement_if* self);

/**
 * if を表す要素を作成します.
 * @return
 */
ILStatement_if* NewILIf();

/**
 * elif を表す要素を作成します.
 * @return
 */
ILStatement_elif* NewILElif();

/**
 * elif の一覧を表す要素を作成します.
 * @return
 */
Vector* NewILElifList();

/**
 * else を表す要素を作成します.
 * @return
 */
ILStatement_else* NewILElse();

/**
 * elif を一覧に加えます.
 */
void PushILElifList(Vector* self, ILStatement_elif* child);

/**
 * if とその子要素を生成します.
 * @param self
 * @param env
 * @param cctx
 */
void GenerateILIf(ILStatement_if* self, Enviroment* env, CallContext* cctx);

/**
 * if とその子要素を読み込みます.
 * @param self
 * @param env
 * @param cctx
 */
void LoadILIf(ILStatement_if* self, Enviroment* env, CallContext* cctx);

/**
 * if を表す要素を開放します.
 * @param self
 */
void DeleteILIf(ILStatement_if* self);

/**
 * elif を表す要素を開放します.
 * @param self
 */
void DeleteILElif(ILStatement_elif* self);

/**
 * elifの一覧 を表す要素を開放します.
 * @param self
 */
void DeleteILElifList(Vector* self);

/**
 * else を表す要素を開放します.
 * @param self
 */
void DeleteILElse(ILStatement_else* self);
#endif // !SIGNAL_IL_IL_STMT_IF_IMPL_H
