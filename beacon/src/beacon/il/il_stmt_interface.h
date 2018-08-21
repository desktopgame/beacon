#pragma once
#ifndef BEACON_IL_IL_STMT_INTERFACE_H
#define BEACON_IL_IL_STMT_INTERFACE_H
#include "../vm/enviroment.h"
#include "../error.h"
#include "call_context.h"
#include <stdint.h>
/**
 * 文の種類を表す列挙型.
 */
typedef enum il_stmt_type {
	ilstmt_proc_T,
	ilstmt_if_T,
	ilstmt_while_T,
	ilstmt_variable_decl_T,
	ilstmt_variable_init_T,
	ilstmt_return_T,
	ilstmt_return_empty_T,
	ilstmt_break_T,
	ilstmt_continue_T,
	ilstmt_inferenced_type_init_T,
	ilstmt_try_T,
	ilstmt_throw_T,
	ilstmt_assert_T,
	ilstmt_defer_T,
	ilstmt_yield_return_T,
	ilstmt_yield_break_T,
} il_stmt_type;

//詳細は il_stmt_impl.h を参照してください。
struct il_stmt_proc;
struct il_stmt_if;
struct il_stmt_while;
struct il_stmt_variable_decl;
struct il_stmt_variable_init;
struct il_stmt_return;
typedef void* il_stmt_return_empty;
struct il_stmt_inferenced_type_init;
struct il_stmt_try;
struct il_stmt_throw;
struct il_stmt_assert;
struct il_stmt_defer;
struct il_stmt_yield_return;
typedef void* il_stmt_yield_break;

/**
 * 文を表す要素です.
 */
typedef struct il_stmt {
	il_stmt_type type;
	int lineno;
	union {
		struct il_stmt_proc* proc_;
		struct il_stmt_if* if_;
		struct il_stmt_while* while_;
		struct il_stmt_variable_decl* variable_decl;
		struct il_stmt_variable_init* variable_init;
		struct il_stmt_return* return_;
		il_stmt_return_empty return_empty;
		struct il_stmt_inferenced_type_init* inferenced_type_init;
		struct il_stmt_try* try_;
		struct il_stmt_throw* throw_;
		struct il_stmt_assert* bcassert_;
		struct il_stmt_defer* defer_;
		struct il_stmt_yield_return* yield_return;
		il_stmt_yield_break yield_break;
	} u;
} il_stmt;

#define il_stmt_new(type) (il_stmt_malloc(type, __FILE__, __LINE__))
il_stmt* il_stmt_malloc(il_stmt_type type, const char* filename, int lineno);

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
 * @param cctx
 */
void il_stmt_generate(il_stmt* self, enviroment* env, call_context* cctx);

/**
 * ステートメントを読み込んでエラーがあれば記録します.
 * @param self
 * @param env
 * @param cctx
 */
void il_stmt_load(il_stmt * self, enviroment* env, call_context* cctx);

/**
 * 文を開放します.
 * @param self
 */
void il_stmt_delete(il_stmt* self);
#endif // !SIGNAL_IL_IL_STMT_INTERFACE_H
