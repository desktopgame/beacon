#include "il_stmt_assert_impl.h"
#include <assert.h>
#include "../../env/namespace.h"
#include "../../env/type_interface.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../il_factor_impl.h"

bc_ILStatement* bc_WrapILAssert(bc_ILAssert* self) {
        bc_ILStatement* ret = bc_NewILStatement(ILSTMT_ASSERT_T);
        ret->Kind.Assert = self;
        self->Parent = ret;
        return ret;
}

bc_ILAssert* bc_NewILAssert() {
        bc_ILAssert* ret = (bc_ILAssert*)MEM_MALLOC(sizeof(bc_ILAssert));
        ret->Condition = NULL;
        ret->Message = NULL;
        ret->Parent = NULL;
        return ret;
}

void bc_GenerateILAssert(bc_ILAssert* self, bc_Enviroment* env,
                         bc_CallContext* cctx) {
        // https://code.i-harness.com/ja/q/2a1650
        bc_Label* gt = bc_AddLabelOpcodeBuf(env->Bytecode, 0);
        bc_GenerateILFactor(self->Condition, env, cctx);
        bc_AddOpcodeBuf(env->Bytecode, OP_GOTO_IF_TRUE);
        bc_AddOpcodeBuf(env->Bytecode, gt);

        bc_GenerateILFactor(self->Message, env, cctx);
        bc_AddOpcodeBuf(env->Bytecode, OP_NEW_INSTANCE);
        bc_AddOpcodeBuf(env->Bytecode,
                        bc_FindTypeFromNamespace(bc_GetLangNamespace(NULL),
                                                 bc_InternString("Exception"))
                            ->AbsoluteIndex);
        bc_AddOpcodeBuf(env->Bytecode, 0);
        bc_AddOpcodeBuf(env->Bytecode, OP_THROW);
        gt->Cursor = bc_AddNOPOpcodeBuf(env->Bytecode);
}

void bc_LoadILAssert(bc_ILAssert* self, bc_Enviroment* env,
                     bc_CallContext* cctx) {
        bc_LoadILFactor(self->Condition, env, cctx);
        if (self->Message == NULL) {
                char* str = bc_ILFactorToString(self->Condition, env);
                bc_ILString* ilstr = bc_NewILString(bc_InternString(str));
                self->Message = bc_WrapILString(ilstr);
                assert(ilstr->Value != 0);
                MEM_FREE(str);
                self->Message->Lineno = self->Parent->Lineno;
        }
        bc_LoadILFactor(self->Message, env, cctx);
}

void bc_DeleteILAssert(bc_ILAssert* self) {
        bc_DeleteILFactor(self->Condition);
        bc_DeleteILFactor(self->Message);
        MEM_FREE(self);
}