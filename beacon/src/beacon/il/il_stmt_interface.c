#include "il_stmt_interface.h"
#include "il_stmt_impl.h"
#include "../env/class_loader.h"
#include "../env/type_interface.h"
#include "../vm/enviroment.h"
#include "../util/mem.h"
#include "il_print_layout.h"

il_stmt* MallocILStmt(il_stmt_type type, const char* filename, int lineno) {
	il_stmt* ret = mem_malloc(sizeof(il_stmt), filename, lineno);
	ret->type = type;
	ret->lineno = -1;
	return ret;
}

void GenerateILStmt(il_stmt * self, struct enviroment* env, call_context* cctx) {
	if(GetLastBCError()) {
		return;
	}
	SetBCErrorFile(env->context_ref->filename);
	SetBCErrorLine(self->lineno);
	switch (self->type) {
		case ILSTMT_IF_T:
			GenerateILIf(self->u.if_, env, cctx);
			//DeleteILIf(self->u.if_);
			break;
		case ILSTMT_PROC_T:
			GenerateILProc(self->u.proc_, env, cctx);
			//DeleteILProc(self->u.proc_);
			break;
		case ILSTMT_VARIABLE_DECL_T:
			il_stmt_variable_decl_generate(self->u.variable_decl, env, cctx);
			break;
		case ILSTMT_VARIABLE_INIT_T:
			il_stmt_variable_init_generate(self->u.variable_init, env, cctx);
			break;
		case ILSTMT_RETURN_T:
			GenerateILReturn(self->u.return_, env, cctx);
			break;
		case ILSTMT_RETURN_EMPTY_T:
			il_stmt_return_empty_generate(NULL, env, cctx);
			break;
		case ILSTMT_WHILE_T:
			GenerateILWhile(self->u.while_, env, cctx);
			break;
		case ILSTMT_BREAK_T:
			GenerateILBreak(NULL, env, cctx);
			break;
		case ILSTMT_CONTINUE_T:
			GenerateILContinue(NULL, env, cctx);
			break;
		case ILSTMT_INFERENCED_TYPE_INIT_T:
			il_stmt_inferenced_type_init_generate(self->u.inferenced_type_init, env, cctx);
			break;
		case ILSTMT_TRY_T:
			GenerateILTry(self->u.try_, env, cctx);
			break;
		case ILSTMT_THROW_T:
			GenerateILThrow(self->u.throw_, env, cctx);
			break;
		case ILSTMT_ASSERT_T:
			GenerateILAssert(self->u.bcassert_, env, cctx);
			break;
		case ILSTMT_DEFER_T:
			GenerateILDefer(self->u.defer_, env, cctx);
			break;
		case ILSTMT_YIELD_RETURN_T:
			il_stmt_yield_return_generate(self->u.yield_return, env, cctx);
			break;
		case ILSTMT_YIELD_BREAK_T:
			il_stmt_yield_break_generate(self->u.yield_break, env, cctx);
			break;
		case ILSTMT_INJECT_JNI_T:
			GenerateILInjectJNI(self->u.inject_jni, env, cctx);
			break;
		default:
			//ERROR("ステートメントを開放出来ませんでした。");
			break;
	}
	AddRangeEnviroment(env, self->lineno);
}

void LoadILStmt(il_stmt * self, enviroment* env, call_context* cctx) {
	if(GetLastBCError()) {
		return;
	}
	SetBCErrorFile(env->context_ref->filename);
	SetBCErrorLine(self->lineno);
	switch (self->type) {
		case ILSTMT_IF_T:
			LoadILIf(self->u.if_, env, cctx);
			break;
		case ILSTMT_PROC_T:
			LoadILProc(self->u.proc_, env, cctx);
			break;
		case ILSTMT_VARIABLE_DECL_T:
			LoadILVariableDecl(self->u.variable_decl, env, cctx);
			break;
		case ILSTMT_VARIABLE_INIT_T:
			LoadILVariableInit(self->u.variable_init, env, cctx);
			break;
		case ILSTMT_RETURN_T:
			LoadILReturn(self->u.return_, env, cctx);
			break;
		case ILSTMT_RETURN_EMPTY_T:
			LoadILReturnEmpty(NULL, env, cctx);
			break;
		case ILSTMT_WHILE_T:
			LoadILWhile(self->u.while_, env, cctx);
			break;
		case ILSTMT_BREAK_T:
			LoadILBreak(NULL, env, cctx);
			break;
		case ILSTMT_CONTINUE_T:
			LoadILContinue(NULL, env, cctx);
			break;
		case ILSTMT_INFERENCED_TYPE_INIT_T:
			il_stmt_inferenced_type_init_load(self->u.inferenced_type_init, env, cctx);
			break;
		case ILSTMT_TRY_T:
			LoadILTry(self->u.try_, env, cctx);
			break;
		case ILSTMT_THROW_T:
			LoadILThrow(self->u.throw_, env, cctx);
			break;
		case ILSTMT_ASSERT_T:
			LoadILAssert(self->u.bcassert_, env, cctx);
			break;
		case ILSTMT_DEFER_T:
			LoadILDefer(self->u.defer_, env, cctx);
			break;
		case ILSTMT_YIELD_RETURN_T:
			LoadILYieldReturn(self->u.yield_return, env, cctx);
			break;
		case ILSTMT_YIELD_BREAK_T:
			LoadILYieldBreak(self->u.yield_break, env, cctx);
			break;
		case ILSTMT_INJECT_JNI_T:
			LoadILInjectJNI(self->u.inject_jni, env, cctx);
			break;
		default:
			//ERROR("ステートメントを開放出来ませんでした。");
			break;
	}
}

void DeleteILStmt(il_stmt * self) {
	switch (self->type) {
		case ILSTMT_IF_T:
			DeleteILIf(self->u.if_);
			break;
		case ILSTMT_PROC_T:
			DeleteILProc(self->u.proc_);
			break;
		case ILSTMT_VARIABLE_DECL_T:
			DeleteILVariableDecl(self->u.variable_decl);
			break;
		case ILSTMT_VARIABLE_INIT_T:
			il_stmt_variable_init_delete(self->u.variable_init);
			break;
		case ILSTMT_RETURN_T:
			DeleteILReturn(self->u.return_);
			break;
		case ILSTMT_WHILE_T:
			DeleteILWhile(self->u.while_);
			break;
		case ILSTMT_BREAK_T:
			DeleteILBreak(NULL);
			break;
		case ILSTMT_CONTINUE_T:
			DeleteILContinue(NULL);
			break;
		case ILSTMT_INFERENCED_TYPE_INIT_T:
			il_stmt_inferenced_type_init_delete(self->u.inferenced_type_init);
			break;
		case ILSTMT_TRY_T:
			DeleteILTry(self->u.try_);
			break;
		case ILSTMT_THROW_T:
			DeleteILThrow(self->u.throw_);
			break;
		case ILSTMT_ASSERT_T:
			DeleteILAssert(self->u.bcassert_);
			break;
		case ILSTMT_DEFER_T:
			DeleteILDefer(self->u.defer_);
			break;
		case ILSTMT_YIELD_RETURN_T:
			DeleteILYieldReturn(self->u.yield_return);
			break;
		case ILSTMT_YIELD_BREAK_T:
			//il_stmt_yield_break_delete(self->u.yield_break);
			break;
		case ILSTMT_INJECT_JNI_T:
			DeleteILInjectJni(self->u.inject_jni);
			break;
		default:
			//ERROR("ステートメントを開放出来ませんでした。");
			{ int x = 0; }
			break;
	}
	MEM_FREE(self);
}
