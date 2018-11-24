#include "il_stmt_while_impl.h"
#include <stdio.h>
#include "../../env/namespace.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../call_context.h"

// proto
static void ILWhile_stmt_delete(bc_VectorItem item);
static void check_condition_type(bc_ILFactor* fact, bc_Enviroment* env,
                                 bc_CallContext* cctx);

bc_ILStatement* bc_WrapILWhile(bc_ILWhile* self) {
        bc_ILStatement* ret = bc_NewILStatement(ILSTMT_WHILE_T);
        ret->Kind.While = self;
        return ret;
}

bc_ILWhile* bc_NewILWhile() {
        bc_ILWhile* ret = (bc_ILWhile*)MEM_MALLOC(sizeof(bc_ILWhile));
        ret->Statements = bc_NewVector();
        ret->Condition = NULL;
        return ret;
}

void bc_GenerateILWhile(bc_ILWhile* self, bc_Enviroment* env,
                        bc_CallContext* cctx) {
        env->Symboles->ScopeDepth++;
        int prev = bc_AddNOPOpcodeBuf(env->Bytecode);
        bc_Label* prevLab = bc_AddLabelOpcodeBuf(env->Bytecode, prev);
        bc_Label* nextLab = bc_AddLabelOpcodeBuf(env->Bytecode, -1);
        bc_PushVector(cctx->Control.WhileStartTable, prevLab);
        bc_PushVector(cctx->Control.WhileEndTable, nextLab);
        //条件を満たさないなら nextLab へ
        bc_GenerateILFactor(self->Condition, env, cctx);
        bc_AddOpcodeBuf(env->Bytecode, OP_GOTO_IF_FALSE);
        bc_AddOpcodeBuf(env->Bytecode, nextLab);
        //全てのステートメントを実行
        for (int i = 0; i < self->Statements->Length; i++) {
                bc_ILStatement* e =
                    (bc_ILStatement*)bc_AtVector(self->Statements, i);
                bc_GenerateILStmt(e, env, cctx);
        }
        // prevLab へ行って再判定
        bc_AddOpcodeBuf(env->Bytecode, OP_GOTO);
        bc_AddOpcodeBuf(env->Bytecode, prevLab);
        bc_PopVector(cctx->Control.WhileStartTable);
        bc_PopVector(cctx->Control.WhileEndTable);
        int next = bc_AddNOPOpcodeBuf(env->Bytecode);
        nextLab->Cursor = next;
        env->Symboles->ScopeDepth--;
}

void bc_DeleteILWhile(bc_ILWhile* self) {
        bc_DeleteVector(self->Statements, ILWhile_stmt_delete);
        bc_DeleteILFactor(self->Condition);
        MEM_FREE(self);
}

void bc_LoadILWhile(bc_ILWhile* self, bc_Enviroment* env,
                    bc_CallContext* cctx) {
        env->Symboles->ScopeDepth++;
        bc_LoadILFactor(self->Condition, env, cctx);
        for (int i = 0; i < self->Statements->Length; i++) {
                bc_ILStatement* e =
                    (bc_ILStatement*)bc_AtVector(self->Statements, i);
                bc_LoadILStmt(e, env, cctx);
        }
        check_condition_type(self->Condition, env, cctx);
        env->Symboles->ScopeDepth--;
}

// private
static void ILWhile_stmt_delete(bc_VectorItem item) {
        bc_ILStatement* e = (bc_ILStatement*)item;
        bc_DeleteILStmt(e);
}

static void check_condition_type(bc_ILFactor* fact, bc_Enviroment* env,
                                 bc_CallContext* cctx) {
        bc_GenericType* cond_T = bc_EvalILFactor(fact, env, cctx);
        if (cond_T->CoreType != BC_TYPE_BOOL) {
                char* condstr = bc_ILFactorToString(fact, env);
                bc_Panic(BCERROR_IF_EXPR_TYPE_OF_NOT_BOOL_T, condstr);
                MEM_FREE(condstr);
        }
}
