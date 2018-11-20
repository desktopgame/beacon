//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_stmt_if_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

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
	ILFactor* Condition;
	Vector* Body;
} ILElif;

/**
 * } else { ... } を表す要素.
 */
typedef struct ILElse {
	Vector* Body;
} ILElse;

/**
 * if (...) {
 *    ...
 * }
 * を表す要素.
 */
typedef struct ILIf {
	ILFactor* Condition;
	Vector* Body;
	Vector* ElifList;
	ILElse* Else;
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
void GenerateILIf(ILIf* self, bc_Enviroment* env, CallContext* cctx);

/**
 * if とその子要素を読み込みます.
 * @param self
 * @param env
 * @param cctx
 */
void LoadILIf(ILIf* self, bc_Enviroment* env, CallContext* cctx);

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
