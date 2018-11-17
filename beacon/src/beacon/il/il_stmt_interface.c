#include "il_stmt_interface.h"
#include "il_stmt_impl.h"
#include "../env/class_loader.h"
#include "../env/type_interface.h"
#include "../vm/enviroment.h"
#include "../util/mem.h"
#include "il_print_layout.h"

ILStatement* MallocILStmt(ILStatementTag type, const char* filename, int lineno) {
	ILStatement* ret = bc_MXMalloc(sizeof(ILStatement), filename, lineno);
	ret->Type = type;
	ret->Lineno = -1;
	return ret;
}

void GenerateILStmt(ILStatement * self, Enviroment* env, CallContext* cctx) {
	if(GetLastBCError()) {
		return;
	}
	SetBCErrorFile(env->ContextRef->FileName);
	SetBCErrorLine(self->Lineno);
	switch (self->Type) {
		case ILSTMT_IF_T:
			GenerateILIf(self->Kind.If, env, cctx);
			//DeleteILIf(self->Kind.If);
			break;
		case ILSTMT_PROC_T:
			GenerateILProc(self->Kind.Proc, env, cctx);
			//DeleteILProc(self->Kind.Proc);
			break;
		case ILSTMT_VARIABLE_DECL_T:
			GenerateILVariableDecl(self->Kind.VariableDecl, env, cctx);
			break;
		case ILSTMT_VARIABLE_INIT_T:
			GenerateILVariableInit(self->Kind.VariableInit, env, cctx);
			break;
		case ILSTMT_RETURN_T:
			GenerateILReturn(self->Kind.Return, env, cctx);
			break;
		case ILSTMT_RETURN_EMPTY_T:
			GenerateILReturnEmpty(NULL, env, cctx);
			break;
		case ILSTMT_WHILE_T:
			GenerateILWhile(self->Kind.While, env, cctx);
			break;
		case ILSTMT_BREAK_T:
			GenerateILBreak(NULL, env, cctx);
			break;
		case ILSTMT_CONTINUE_T:
			GenerateILContinue(NULL, env, cctx);
			break;
		case ILSTMT_INFERENCED_TYPE_INIT_T:
			GenerateILInferencedTypeInit(self->Kind.InferencedTypeInit, env, cctx);
			break;
		case ILSTMT_TRY_T:
			GenerateILTry(self->Kind.Try, env, cctx);
			break;
		case ILSTMT_THROW_T:
			GenerateILThrow(self->Kind.Throw, env, cctx);
			break;
		case ILSTMT_ASSERT_T:
			GenerateILAssert(self->Kind.Assert, env, cctx);
			break;
		case ILSTMT_DEFER_T:
			GenerateILDefer(self->Kind.Defer, env, cctx);
			break;
		case ILSTMT_YIELD_RETURN_T:
			GenerateILYieldReturn(self->Kind.YieldReturn, env, cctx);
			break;
		case ILSTMT_YIELD_BREAK_T:
			GenerateILYieldBreak(self->Kind.YieldBreak, env, cctx);
			break;
		case ILSTMT_INJECT_JNI_T:
			GenerateILInjectJNI(self->Kind.InjectJNI, env, cctx);
			break;
		default:
			//ERROR("ステートメントを開放出来ませんでした。");
			break;
	}
	AddRangeEnviroment(env, self->Lineno);
}

void LoadILStmt(ILStatement * self, Enviroment* env, CallContext* cctx) {
	if(GetLastBCError()) {
		return;
	}
	SetBCErrorFile(env->ContextRef->FileName);
	SetBCErrorLine(self->Lineno);
	switch (self->Type) {
		case ILSTMT_IF_T:
			LoadILIf(self->Kind.If, env, cctx);
			break;
		case ILSTMT_PROC_T:
			LoadILProc(self->Kind.Proc, env, cctx);
			break;
		case ILSTMT_VARIABLE_DECL_T:
			LoadILVariableDecl(self->Kind.VariableDecl, env, cctx);
			break;
		case ILSTMT_VARIABLE_INIT_T:
			LoadILVariableInit(self->Kind.VariableInit, env, cctx);
			break;
		case ILSTMT_RETURN_T:
			LoadILReturn(self->Kind.Return, env, cctx);
			break;
		case ILSTMT_RETURN_EMPTY_T:
			LoadILReturnEmpty(NULL, env, cctx);
			break;
		case ILSTMT_WHILE_T:
			LoadILWhile(self->Kind.While, env, cctx);
			break;
		case ILSTMT_BREAK_T:
			LoadILBreak(NULL, env, cctx);
			break;
		case ILSTMT_CONTINUE_T:
			LoadILContinue(NULL, env, cctx);
			break;
		case ILSTMT_INFERENCED_TYPE_INIT_T:
			LoadILInferencedTypeInit(self->Kind.InferencedTypeInit, env, cctx);
			break;
		case ILSTMT_TRY_T:
			LoadILTry(self->Kind.Try, env, cctx);
			break;
		case ILSTMT_THROW_T:
			LoadILThrow(self->Kind.Throw, env, cctx);
			break;
		case ILSTMT_ASSERT_T:
			LoadILAssert(self->Kind.Assert, env, cctx);
			break;
		case ILSTMT_DEFER_T:
			LoadILDefer(self->Kind.Defer, env, cctx);
			break;
		case ILSTMT_YIELD_RETURN_T:
			LoadILYieldReturn(self->Kind.YieldReturn, env, cctx);
			break;
		case ILSTMT_YIELD_BREAK_T:
			LoadILYieldBreak(self->Kind.YieldBreak, env, cctx);
			break;
		case ILSTMT_INJECT_JNI_T:
			LoadILInjectJNI(self->Kind.InjectJNI, env, cctx);
			break;
		default:
			//ERROR("ステートメントを開放出来ませんでした。");
			break;
	}
}

void DeleteILStmt(ILStatement * self) {
	switch (self->Type) {
		case ILSTMT_IF_T:
			DeleteILIf(self->Kind.If);
			break;
		case ILSTMT_PROC_T:
			DeleteILProc(self->Kind.Proc);
			break;
		case ILSTMT_VARIABLE_DECL_T:
			DeleteILVariableDecl(self->Kind.VariableDecl);
			break;
		case ILSTMT_VARIABLE_INIT_T:
			DeleteILVariableInit(self->Kind.VariableInit);
			break;
		case ILSTMT_RETURN_T:
			DeleteILReturn(self->Kind.Return);
			break;
		case ILSTMT_WHILE_T:
			DeleteILWhile(self->Kind.While);
			break;
		case ILSTMT_BREAK_T:
			DeleteILBreak(NULL);
			break;
		case ILSTMT_CONTINUE_T:
			DeleteILContinue(NULL);
			break;
		case ILSTMT_INFERENCED_TYPE_INIT_T:
			DeleteILInferencedTypeInit(self->Kind.InferencedTypeInit);
			break;
		case ILSTMT_TRY_T:
			DeleteILTry(self->Kind.Try);
			break;
		case ILSTMT_THROW_T:
			DeleteILThrow(self->Kind.Throw);
			break;
		case ILSTMT_ASSERT_T:
			DeleteILAssert(self->Kind.Assert);
			break;
		case ILSTMT_DEFER_T:
			DeleteILDefer(self->Kind.Defer);
			break;
		case ILSTMT_YIELD_RETURN_T:
			DeleteILYieldReturn(self->Kind.YieldReturn);
			break;
		case ILSTMT_YIELD_BREAK_T:
			//ILStatementYieldBreak_delete(self->Kind.YieldBreak);
			break;
		case ILSTMT_INJECT_JNI_T:
			DeleteILInjectJni(self->Kind.InjectJNI);
			break;
		default:
			//ERROR("ステートメントを開放出来ませんでした。");
			{ int x = 0; }
			break;
	}
	MEM_FREE(self);
}
