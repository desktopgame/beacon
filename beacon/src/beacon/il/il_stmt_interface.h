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
typedef enum ILStatementTag {
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
} ILStatementTag;

//詳細は il_stmt_impl.h を参照してください。
struct ILProc;
struct ILIf;
struct ILStatement_while;
struct ILVariableDecl;
struct ILVariableInit;
struct ILReturn;
typedef void* ILReturnEmpty;
struct ILInferencedTypeInit;
struct ILTry;
struct ILThrow;
struct ILAssert;
struct ILDefer;
struct ILStatement_yield_return;
typedef void* ILStatement_yield_break;
struct ILInjectJNI;

/**
 * 文を表す要素です.
 */
typedef struct ILStatement {
	ILStatementTag type;
	int lineno;
	union {
		struct ILProc* proc_;
		struct ILIf* if_;
		struct ILStatement_while* while_;
		struct ILVariableDecl* variable_decl;
		struct ILVariableInit* variable_init;
		struct ILReturn* return_;
		ILReturnEmpty return_empty;
		struct ILInferencedTypeInit* inferenced_type_init;
		struct ILTry* try_;
		struct ILThrow* throw_;
		struct ILAssert* bcassert_;
		struct ILDefer* defer_;
		struct ILStatement_yield_return* yield_return;
		ILStatement_yield_break yield_break;
		struct ILInjectJNI* inject_jni;
	} u;
} ILStatement;

#define ILStatement_new(type) (MallocILStmt(type, __FILE__, __LINE__))
ILStatement* MallocILStmt(ILStatementTag type, const char* filename, int lineno);

/**
 * 文を生成します.
 * @param self
 * @param env
 * @param cctx
 */
void GenerateILStmt(ILStatement* self, Enviroment* env, CallContext* cctx);

/**
 * ステートメントを読み込んでエラーがあれば記録します.
 * @param self
 * @param env
 * @param cctx
 */
void LoadILStmt(ILStatement * self, Enviroment* env, CallContext* cctx);

/**
 * 文を開放します.
 * @param self
 */
void DeleteILStmt(ILStatement* self);
#endif // !SIGNAL_IL_IL_STMT_INTERFACE_H
