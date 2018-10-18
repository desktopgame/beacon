#pragma once
#ifndef BEACON_IL_IL_STMT_IF_IMPL_H
#define BEACON_IL_IL_STMT_IF_IMPL_H
#include "../../util/vector.h"
#include "../il_factor_interface.h"
#include "../il_stmt_interface.h"
/**
 * elif (...) { ... } を表す要素.
 */
typedef struct il_stmt_elif {
	il_factor* condition;
	Vector* body;
} il_stmt_elif;

/**
 * } else { ... } を表す要素.
 */
typedef struct il_stmt_else {
	Vector* body;
} il_stmt_else;

/**
 * if (...) {
 *    ...
 * }
 * を表す要素.
 */
typedef struct il_stmt_if {
	il_factor* condition;
	Vector* body;
	Vector* elif_list;
	il_stmt_else* else_body;
} il_stmt_if;

/**
 * if をスーパーセットにラップします.
 * @param self
 * @return
 */
il_stmt* WrapILIf(il_stmt_if* self);

/**
 * if を表す要素を作成します.
 * @return
 */
il_stmt_if* NewILIf();

/**
 * elif を表す要素を作成します.
 * @return
 */
il_stmt_elif* NewILElif();

/**
 * elif の一覧を表す要素を作成します.
 * @return
 */
Vector* NewILElifList();

/**
 * else を表す要素を作成します.
 * @return
 */
il_stmt_else* NewILElse();

/**
 * elif を一覧に加えます.
 */
void PushILElifList(Vector* self, il_stmt_elif* child);

/**
 * if とその子要素を生成します.
 * @param self
 * @param env
 * @param cctx
 */
void GenerateILIf(il_stmt_if* self, Enviroment* env, call_context* cctx);

/**
 * if とその子要素を読み込みます.
 * @param self
 * @param env
 * @param cctx
 */
void LoadILIf(il_stmt_if* self, Enviroment* env, call_context* cctx);

/**
 * if を表す要素を開放します.
 * @param self
 */
void DeleteILIf(il_stmt_if* self);

/**
 * elif を表す要素を開放します.
 * @param self
 */
void DeleteILElif(il_stmt_elif* self);

/**
 * elifの一覧 を表す要素を開放します.
 * @param self
 */
void DeleteILElifList(Vector* self);

/**
 * else を表す要素を開放します.
 * @param self
 */
void DeleteILElse(il_stmt_else* self);
#endif // !SIGNAL_IL_IL_STMT_IF_IMPL_H
