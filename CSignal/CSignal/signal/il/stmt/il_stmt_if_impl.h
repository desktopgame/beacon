#pragma once
#ifndef SIGNAL_IL_IL_STMT_IF_IMPL_H
#define SIGNAL_IL_IL_STMT_IF_IMPL_H
#include "../../util/vector.h"
#include "../il_factor_interface.h"
#include "../il_stmt_interface.h"
/**
 * elif (...) { ... } を表す要素.
 */
typedef struct il_stmt_elif {
	il_factor* condition;
	vector* body;
} il_stmt_elif;

/**
 * } else { ... } を表す要素.
 */
typedef struct il_stmt_else {
	vector* body;
} il_stmt_else;

/**
 * if (...) {
 *    ...
 * }
 * を表す要素.
 */
typedef struct il_stmt_if {
	il_factor* condition;
	vector* body;
	vector* elif_list;
	il_stmt_else* else_body;
} il_stmt_if;

/**
 * if をスーパーセットにラップします.
 * @param self
 * @return
 */
il_stmt* il_stmt_wrap_if(il_stmt_if* self);

/**
 * if を表す要素を作成します.
 * @return
 */
il_stmt_if* il_stmt_if_new();

/**
 * elif を表す要素を作成します.
 * @return
 */
il_stmt_elif* il_stmt_elif_new();

/**
 * elif の一覧を表す要素を作成します.
 * @return
 */
vector* il_stmt_elif_list_new();

/**
 * else を表す要素を作成します.
 * @return
 */
il_stmt_else* il_stmt_else_new();

/**
 * elif を一覧に加えます.
 */
void il_stmt_elif_list_push(vector* self, il_stmt_elif* child);

/**
 * if とその子要素を出力します.
 * @param self
 * @param depth
 */
void il_stmt_if_dump(il_stmt_if* self, int depth);

/**
 * if とその子要素を生成します.
 * @param self
 * @param env
 * @param cache
 */
void il_stmt_if_generate(il_stmt_if* self, struct enviroment* env, il_load_cache* cache);

/**
 * if とその子要素を読み込みます.
 * @param self
 * @param env
 * @param cache
 * @param eh
 */
void il_stmt_if_load(il_stmt_if* self, struct enviroment* env, il_load_cache* cache, il_ehandler* eh);

/**
 * if を表す要素を開放します.
 * @param self
 */
void il_stmt_if_delete(il_stmt_if* self);

/**
 * elif を表す要素を開放します.
 * @param self
 */
void il_stmt_elif_delete(il_stmt_elif* self);

/**
 * elifの一覧 を表す要素を開放します.
 * @param self
 */
void il_stmt_elif_list_delete(vector* self);

/**
 * else を表す要素を開放します.
 * @param self
 */
void il_stmt_else_delete(il_stmt_else* self);
#endif // !SIGNAL_IL_IL_STMT_IF_IMPL_H
