#pragma once
#ifndef BEACON_IL_IL_STMT_IF_IMPL_H
#define BEACON_IL_IL_STMT_IF_IMPL_H
#include "../../util/vector.h"
#include "../il_factor_interface.h"
#include "../il_stmt_interface.h"
/**
 * elif (...) { ... } を表す要素.
 */
typedef struct ILElif {
	ILFactor* condition;
	Vector* body;
} ILElif;

/**
 * } else { ... } を表す要素.
 */
typedef struct ILElse {
	Vector* body;
} ILElse;

/**
 * if (...) {
 *    ...
 * }
 * を表す要素.
 */
typedef struct ILIf {
	ILFactor* condition;
	Vector* body;
	Vector* elif_list;
	ILElse* else_body;
} ILIf;

/**
 * if をスーパーセットにラップします.
 * @param self
 * @return
 */
ILStatement* WrapILIf(ILIf* self);

/**
 * if を表す要素を作成します.
 * @return
 */
ILIf* NewILIf();

/**
 * elif を表す要素を作成します.
 * @return
 */
ILElif* NewILElif();

/**
 * elif の一覧を表す要素を作成します.
 * @return
 */
Vector* NewILElifList();

/**
 * else を表す要素を作成します.
 * @return
 */
ILElse* NewILElse();

/**
 * elif を一覧に加えます.
 */
void PushILElifList(Vector* self, ILElif* child);

/**
 * if とその子要素を生成します.
 * @param self
 * @param env
 * @param cctx
 */
void GenerateILIf(ILIf* self, Enviroment* env, CallContext* cctx);

/**
 * if とその子要素を読み込みます.
 * @param self
 * @param env
 * @param cctx
 */
void LoadILIf(ILIf* self, Enviroment* env, CallContext* cctx);

/**
 * if を表す要素を開放します.
 * @param self
 */
void DeleteILIf(ILIf* self);

/**
 * elif を表す要素を開放します.
 * @param self
 */
void DeleteILElif(ILElif* self);

/**
 * elifの一覧 を表す要素を開放します.
 * @param self
 */
void DeleteILElifList(Vector* self);

/**
 * else を表す要素を開放します.
 * @param self
 */
void DeleteILElse(ILElse* self);
#endif // !SIGNAL_IL_IL_STMT_IF_IMPL_H
