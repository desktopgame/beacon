#pragma once
#ifndef BEACON_IL_IL_STMT_INTERFACE_H
#define BEACON_IL_IL_STMT_INTERFACE_H
#include "../vm/enviroment.h"
#include "il_ehandler.h"
#include "il_context.h"
#include <stdint.h>
/**
 * 文の種類を表す列挙型.
 */
typedef enum il_stmt_type {
	ilstmt_proc,
	ilstmt_if,
	ilstmt_while,
	ilstmt_variable_decl,
	ilstmt_variable_init,
	ilstmt_return,
	ilstmt_break,
	ilstmt_continue,
	ilstmt_inferenced_type_init,
	ilstmt_try,
	ilstmt_throw,
} il_stmt_type;

//詳細は il_stmt_impl.h を参照してください。
struct il_stmt_proc;
struct il_stmt_if;
struct il_stmt_while;
struct il_stmt_variable_decl;
struct il_stmt_variable_init;
struct il_stmt_return;
struct il_stmt_inferenced_type_init;
struct il_stmt_try;
struct il_stmt_throw;

/**
 * 文を表す要素です.
 */
typedef struct il_stmt {
	il_stmt_type type;
	uint32_t lineno;
	union {
		struct il_stmt_proc* proc_;
		struct il_stmt_if* if_;
		struct il_stmt_while* while_;
		struct il_stmt_variable_decl* variable_decl;
		struct il_stmt_variable_init* variable_init;
		struct il_stmt_return* return_;
		struct il_stmt_inferenced_type_init* inferenced_type_init;
		struct il_stmt_try* try_;
		struct il_stmt_throw* throw_;
	} u;
} il_stmt;

/**
 * 文を出力します.
 * @param self
 * @param depth
 */
void il_stmt_dump(il_stmt* self, int depth);

/**
 * 文を生成します.
 * @param self
 * @param env
 * @param cache
 */
void il_stmt_generate(il_stmt* self, enviroment* env, il_context* ilctx);

/**
 * ステートメントを読み込んでエラーがあれば記録します.
 * @param self
 * @param env
 * @param cache
 * @param eh
 */
void il_stmt_load(il_stmt * self, enviroment* env, il_context* ilctx, il_ehandler * eh);

/**
 * 文を開放します.
 * @param self
 */
void il_stmt_delete(il_stmt* self);
#endif // !SIGNAL_IL_IL_STMT_INTERFACE_H
