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
	ILSTMT_PROC_T,
	ILSTMT_IF_T,
	ILSTMT_WHILE_T,
	ILSTMT_VARIABLE_DECL_T,
	ILSTMT_VARIABLE_INIT_T,
	ILSTMT_RETURN_T,
	ILSTMT_RETURN_EMPTY_T,
	ILSTMT_BREAK_T,
	ILSTMT_CONTINUE_T,
	ILSTMT_INFERENCED_TYPE_INIT_T,
	ILSTMT_TRY_T,
	ILSTMT_THROW_T,
	ILSTMT_ASSERT_T,
	ILSTMT_DEFER_T,
	ILSTMT_YIELD_RETURN_T,
	ILSTMT_YIELD_BREAK_T,
	ILSTMT_INJECT_JNI_T,
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
struct il_stmt_inject_jni;

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
		struct il_stmt_inject_jni* inject_jni;
	} u;
} il_stmt;

#define il_stmt_new(type) (MallocILStmt(type, __FILE__, __LINE__))
il_stmt* MallocILStmt(il_stmt_type type, const char* filename, int lineno);

/**
 * 文を生成します.
 * @param self
 * @param env
 * @param cctx
 */
void GenerateILStmt(il_stmt* self, Enviroment* env, CallContext* cctx);

/**
 * ステートメントを読み込んでエラーがあれば記録します.
 * @param self
 * @param env
 * @param cctx
 */
void LoadILStmt(il_stmt * self, Enviroment* env, CallContext* cctx);

/**
 * 文を開放します.
 * @param self
 */
void DeleteILStmt(il_stmt* self);
#endif // !SIGNAL_IL_IL_STMT_INTERFACE_H
