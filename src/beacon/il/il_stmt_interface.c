#include "il_stmt_interface.h"
#include "../env/class_loader.h"
#include "../env/type_interface.h"
#include "../util/mem.h"
#include "../vm/enviroment.h"
#include "il_print_layout.h"
#include "il_stmt_impl.h"

bc_ILStatement* bc_MallocILStmt(bc_ILStatementTag type, const char* filename,
                                int lineno) {
        bc_ILStatement* ret =
            bc_MXMalloc(sizeof(bc_ILStatement), filename, lineno);
        ret->Type = type;
        ret->Lineno = -1;
        return ret;
}

void bc_GenerateILStmt(bc_ILStatement* self, bc_Enviroment* env,
                       bc_CallContext* cctx) {
        if (bc_GetLastPanic()) {
                return;
        }
        bc_SetPanicFile(env->ContextRef->FileName);
        bc_SetPanicLine(self->Lineno);
        switch (self->Type) {
                case ILSTMT_IF_T:
                        bc_GenerateILIf(self->Kind.If, env, cctx);
                        // DeleteILIf(self->Kind.If);
                        break;
                case ILSTMT_PROC_T:
                        bc_GenerateILProc(self->Kind.Proc, env, cctx);
                        // DeleteILProc(self->Kind.Proc);
                        break;
                case ILSTMT_VARIABLE_DECL_T:
                        bc_GenerateILVariableDecl(self->Kind.VariableDecl, env,
                                                  cctx);
                        break;
                case ILSTMT_VARIABLE_INIT_T:
                        bc_GenerateILVariableInit(self->Kind.VariableInit, env,
                                                  cctx);
                        break;
                case ILSTMT_RETURN_T:
                        bc_GenerateILReturn(self->Kind.Return, env, cctx);
                        break;
                case ILSTMT_RETURN_EMPTY_T:
                        bc_GenerateILReturnEmpty(NULL, env, cctx);
                        break;
                case ILSTMT_WHILE_T:
                        bc_GenerateILWhile(self->Kind.While, env, cctx);
                        break;
                case ILSTMT_BREAK_T:
                        bc_GenerateILBreak(NULL, env, cctx);
                        break;
                case ILSTMT_CONTINUE_T:
                        bc_GenerateILContinue(NULL, env, cctx);
                        break;
                case ILSTMT_INFERENCED_TYPE_INIT_T:
                        bc_GenerateILInferencedTypeInit(
                            self->Kind.InferencedTypeInit, env, cctx);
                        break;
                case ILSTMT_TRY_T:
                        bc_GenerateILTry(self->Kind.Try, env, cctx);
                        break;
                case ILSTMT_THROW_T:
                        bc_GenerateILThrow(self->Kind.Throw, env, cctx);
                        break;
                case ILSTMT_ASSERT_T:
                        bc_GenerateILAssert(self->Kind.Assert, env, cctx);
                        break;
                case ILSTMT_DEFER_T:
                        bc_GenerateILDefer(self->Kind.Defer, env, cctx);
                        break;
                case ILSTMT_YIELD_RETURN_T:
                        bc_GenerateILYieldReturn(self->Kind.YieldReturn, env,
                                                 cctx);
                        break;
                case ILSTMT_YIELD_BREAK_T:
                        bc_GenerateILYieldBreak(self->Kind.YieldBreak, env,
                                                cctx);
                        break;
                case ILSTMT_INJECT_JNI_T:
                        bc_GenerateILInjectJNI(self->Kind.InjectJNI, env, cctx);
                        break;
                default:
                        // ERROR("ステートメントを開放出来ませんでした。");
                        break;
        }
        bc_AddRangeEnviroment(env, self->Lineno);
}

void bc_LoadILStmt(bc_ILStatement* self, bc_Enviroment* env,
                   bc_CallContext* cctx) {
        if (bc_GetLastPanic()) {
                return;
        }
        bc_SetPanicFile(env->ContextRef->FileName);
        bc_SetPanicLine(self->Lineno);
        switch (self->Type) {
                case ILSTMT_IF_T:
                        bc_LoadILIf(self->Kind.If, env, cctx);
                        break;
                case ILSTMT_PROC_T:
                        bc_LoadILProc(self->Kind.Proc, env, cctx);
                        break;
                case ILSTMT_VARIABLE_DECL_T:
                        bc_LoadILVariableDecl(self->Kind.VariableDecl, env,
                                              cctx);
                        break;
                case ILSTMT_VARIABLE_INIT_T:
                        bc_LoadILVariableInit(self->Kind.VariableInit, env,
                                              cctx);
                        break;
                case ILSTMT_RETURN_T:
                        bc_LoadILReturn(self->Kind.Return, env, cctx);
                        break;
                case ILSTMT_RETURN_EMPTY_T:
                        bc_LoadILReturnEmpty(NULL, env, cctx);
                        break;
                case ILSTMT_WHILE_T:
                        bc_LoadILWhile(self->Kind.While, env, cctx);
                        break;
                case ILSTMT_BREAK_T:
                        bc_LoadILBreak(NULL, env, cctx);
                        break;
                case ILSTMT_CONTINUE_T:
                        bc_LoadILContinue(NULL, env, cctx);
                        break;
                case ILSTMT_INFERENCED_TYPE_INIT_T:
                        bc_LoadILInferencedTypeInit(
                            self->Kind.InferencedTypeInit, env, cctx);
                        break;
                case ILSTMT_TRY_T:
                        bc_LoadILTry(self->Kind.Try, env, cctx);
                        break;
                case ILSTMT_THROW_T:
                        bc_LoadILThrow(self->Kind.Throw, env, cctx);
                        break;
                case ILSTMT_ASSERT_T:
                        bc_LoadILAssert(self->Kind.Assert, env, cctx);
                        break;
                case ILSTMT_DEFER_T:
                        bc_LoadILDefer(self->Kind.Defer, env, cctx);
                        break;
                case ILSTMT_YIELD_RETURN_T:
                        bc_LoadILYieldReturn(self->Kind.YieldReturn, env, cctx);
                        break;
                case ILSTMT_YIELD_BREAK_T:
                        bc_LoadILYieldBreak(self->Kind.YieldBreak, env, cctx);
                        break;
                case ILSTMT_INJECT_JNI_T:
                        bc_LoadILInjectJNI(self->Kind.InjectJNI, env, cctx);
                        break;
                default:
                        // ERROR("ステートメントを開放出来ませんでした。");
                        break;
        }
}

void bc_DeleteILStmt(bc_ILStatement* self) {
        switch (self->Type) {
                case ILSTMT_IF_T:
                        bc_DeleteILIf(self->Kind.If);
                        break;
                case ILSTMT_PROC_T:
                        bc_DeleteILProc(self->Kind.Proc);
                        break;
                case ILSTMT_VARIABLE_DECL_T:
                        bc_DeleteILVariableDecl(self->Kind.VariableDecl);
                        break;
                case ILSTMT_VARIABLE_INIT_T:
                        bc_DeleteILVariableInit(self->Kind.VariableInit);
                        break;
                case ILSTMT_RETURN_T:
                        bc_DeleteILReturn(self->Kind.Return);
                        break;
                case ILSTMT_WHILE_T:
                        bc_DeleteILWhile(self->Kind.While);
                        break;
                case ILSTMT_BREAK_T:
                        bc_DeleteILBreak(NULL);
                        break;
                case ILSTMT_CONTINUE_T:
                        bc_DeleteILContinue(NULL);
                        break;
                case ILSTMT_INFERENCED_TYPE_INIT_T:
                        bc_DeleteILInferencedTypeInit(
                            self->Kind.InferencedTypeInit);
                        break;
                case ILSTMT_TRY_T:
                        bc_DeleteILTry(self->Kind.Try);
                        break;
                case ILSTMT_THROW_T:
                        bc_DeleteILThrow(self->Kind.Throw);
                        break;
                case ILSTMT_ASSERT_T:
                        bc_DeleteILAssert(self->Kind.Assert);
                        break;
                case ILSTMT_DEFER_T:
                        bc_DeleteILDefer(self->Kind.Defer);
                        break;
                case ILSTMT_YIELD_RETURN_T:
                        bc_DeleteILYieldReturn(self->Kind.YieldReturn);
                        break;
                case ILSTMT_YIELD_BREAK_T:
                        // ILStatementYieldBreak_delete(self->Kind.YieldBreak);
                        break;
                case ILSTMT_INJECT_JNI_T:
                        bc_DeleteILInjectJni(self->Kind.InjectJNI);
                        break;
                default:
                        // ERROR("ステートメントを開放出来ませんでした。");
                        { int x = 0; }
                        break;
        }
        MEM_FREE(self);
}
