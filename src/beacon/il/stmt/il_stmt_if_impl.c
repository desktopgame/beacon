#include "il_stmt_if_impl.h"
#include <stdio.h>
#include <stdlib.h>
#include "../../env/namespace.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../vm/opcode_buf.h"

// proto
static void DeleteILElifList_impl(bc_VectorItem item);
static void DeleteILIf_stmt(bc_VectorItem item);
static void check_condition_type(bc_ILFactor* fact, bc_Enviroment* env,
                                 bc_CallContext* cctx);

bc_ILStatement* bc_WrapILIf(bc_ILIf* self) {
        bc_ILStatement* ret = bc_NewILStatement(ILSTMT_IF_T);
        ret->Kind.If = self;
        return ret;
}

bc_ILIf* bc_NewILIf() {
        bc_ILIf* ret = (bc_ILIf*)MEM_MALLOC(sizeof(bc_ILIf));
        ret->Condition = NULL;
        ret->ElifList = bc_NewVector();
        ret->Else = bc_NewILElse();
        ret->Body = bc_NewVector();
        return ret;
}

bc_ILElif* bc_NewILElif() {
        bc_ILElif* ret = (bc_ILElif*)MEM_MALLOC(sizeof(bc_ILElif));
        ret->Condition = NULL;
        ret->Body = bc_NewVector();
        return ret;
}

bc_Vector* bc_NewILElifList() { return bc_NewVector(); }

bc_ILElse* bc_NewILElse() {
        bc_ILElse* ret = (bc_ILElse*)MEM_MALLOC(sizeof(bc_ILElse));
        ret->Body = bc_NewVector();
        return ret;
}

void bc_PushILElifList(bc_Vector* self, bc_ILElif* child) {
        bc_PushVector(self, child);
}

void bc_GenerateILIf(bc_ILIf* self, bc_Enviroment* env, bc_CallContext* cctx) {
        // if(...)
        env->Symboles->ScopeDepth++;
        bc_GenerateILFactor(self->Condition, env, cctx);
        bc_Label* l1 = bc_AddLabelOpcodeBuf(env->Bytecode, -1);
        bc_Label* tail = bc_AddLabelOpcodeBuf(env->Bytecode, -1);
        // { ... }
        bc_AddOpcodeBuf(env->Bytecode, OP_GOTO_IF_FALSE);
        bc_AddOpcodeBuf(env->Bytecode, l1);
        for (int i = 0; i < self->Body->Length; i++) {
                bc_ILStatement* stmt =
                    (bc_ILStatement*)bc_AtVector(self->Body, i);
                bc_GenerateILStmt(stmt, env, cctx);
        }
        //条件が満たされて実行されたら最後までジャンプ
        bc_AddOpcodeBuf(env->Bytecode, OP_GOTO);
        bc_AddOpcodeBuf(env->Bytecode, tail);
        l1->Cursor = bc_AddNOPOpcodeBuf(env->Bytecode);
        // elif(...)
        for (int i = 0; i < self->ElifList->Length; i++) {
                bc_ILElif* elif = (bc_ILElif*)bc_AtVector(self->ElifList, i);
                bc_GenerateILFactor(elif->Condition, env, cctx);
                bc_Label* l2 = bc_AddLabelOpcodeBuf(env->Bytecode, -1);
                // { ... }
                bc_AddOpcodeBuf(env->Bytecode, OP_GOTO_IF_FALSE);
                bc_AddOpcodeBuf(env->Bytecode, l2);
                for (int j = 0; j < elif->Body->Length; j++) {
                        bc_ILStatement* stmt =
                            (bc_ILStatement*)bc_AtVector(elif->Body, j);
                        bc_GenerateILStmt(stmt, env, cctx);
                }
                //条件が満たされて実行されたら最後までジャンプ
                bc_AddOpcodeBuf(env->Bytecode, OP_GOTO);
                bc_AddOpcodeBuf(env->Bytecode, tail);
                l2->Cursor = bc_AddNOPOpcodeBuf(env->Bytecode);
        }
        // else { ... }
        if (self->Else == NULL || self->Else->Body->Length == 0) {
                tail->Cursor = bc_AddNOPOpcodeBuf(env->Bytecode);
        } else {
                for (int i = 0; i < self->Else->Body->Length; i++) {
                        bc_ILStatement* stmt =
                            (bc_ILStatement*)bc_AtVector(self->Else->Body, i);
                        bc_GenerateILStmt(stmt, env, cctx);
                }
                tail->Cursor = bc_AddNOPOpcodeBuf(env->Bytecode);
        }
        env->Symboles->ScopeDepth--;
}

void bc_LoadILIf(bc_ILIf* self, bc_Enviroment* env, bc_CallContext* cctx) {
        env->Symboles->ScopeDepth++;
        bc_LoadILFactor(self->Condition, env, cctx);
        for (int i = 0; i < self->Body->Length; i++) {
                bc_ILStatement* e = (bc_ILStatement*)bc_AtVector(self->Body, i);
                bc_LoadILStmt(e, env, cctx);
                BC_ERROR();
        }
        for (int i = 0; i < self->ElifList->Length; i++) {
                bc_ILElif* e = (bc_ILElif*)bc_AtVector(self->ElifList, i);
                bc_LoadILFactor(e->Condition, env, cctx);
                for (int j = 0; j < e->Body->Length; j++) {
                        bc_ILStatement* st =
                            (bc_ILStatement*)bc_AtVector(e->Body, j);
                        bc_LoadILStmt(st, env, cctx);
                        BC_ERROR();
                }
                BC_ERROR();
        }
        for (int i = 0; i < self->Else->Body->Length; i++) {
                bc_ILStatement* e =
                    (bc_ILStatement*)bc_AtVector(self->Else->Body, i);
                bc_LoadILStmt(e, env, cctx);
                BC_ERROR();
        }
        //条件が bool を返さない
        BC_ERROR();
        check_condition_type(self->Condition, env, cctx);
        for (int i = 0; i < self->ElifList->Length; i++) {
                bc_ILElif* elif = bc_AtVector(self->ElifList, i);
                check_condition_type(elif->Condition, env, cctx);
                BC_ERROR();
        }
        env->Symboles->ScopeDepth--;
}

void bc_DeleteILIf(bc_ILIf* self) {
        bc_DeleteVector(self->ElifList, DeleteILElifList_impl);
        bc_DeleteILElse(self->Else);
        bc_DeleteVector(self->Body, DeleteILIf_stmt);
        bc_DeleteILFactor(self->Condition);
        MEM_FREE(self);
}

void bc_DeleteILElif(bc_ILElif* self) {
        bc_DeleteILFactor(self->Condition);
        bc_DeleteVector(self->Body, DeleteILIf_stmt);
        MEM_FREE(self);
}

void bc_DeleteILElifList(bc_Vector* self) {
        bc_DeleteVector(self, DeleteILElifList_impl);
}

void bc_DeleteILElse(bc_ILElse* self) {
        bc_DeleteVector(self->Body, DeleteILIf_stmt);
        MEM_FREE(self);
}

// private
static void DeleteILElifList_impl(bc_VectorItem item) {
        bc_ILElif* el = (bc_ILElif*)item;
        bc_DeleteILElif(el);
}

static void DeleteILIf_stmt(bc_VectorItem item) {
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