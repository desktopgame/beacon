#include "il_factor_super_impl.h"
#include <assert.h>
#include <stdio.h>
#include "../../env/TYPE_IMPL.h"
#include "../../env/type_interface.h"
#include "../../error.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../call_context.h"

static void check_context(bc_ILSuper* self, bc_Enviroment* env,
                          bc_CallContext* cctx);

bc_ILSuper* bc_NewILSuper() {
        bc_ILSuper* ret = (bc_ILSuper*)MEM_MALLOC(sizeof(bc_ILSuper));
        ret->Resolved = NULL;
        return ret;
}

void bc_GenerateILSuper(bc_ILSuper* self, bc_Enviroment* env,
                        bc_CallContext* cctx) {
        bc_AddOpcodeBuf(env->Bytecode, OP_SUPER);
}

void bc_LoadILSuper(bc_ILSuper* self, bc_Enviroment* env,
                    bc_CallContext* cctx) {
        check_context(self, env, cctx);
}

bc_GenericType* bc_EvalILSuper(bc_ILSuper* self, bc_Enviroment* env,
                               bc_CallContext* cctx) {
        bc_Type* t = bc_GetTypeCContext(cctx);
        return t->Kind.Class->SuperClass;
}

char* bc_ILSuperToString(bc_ILSuper* self, bc_Enviroment* env) {
        return bc_Strdup("super");
}

void bc_DeleteILSuper(bc_ILSuper* self) { MEM_FREE(self); }

// private
static void check_context(bc_ILSuper* self, bc_Enviroment* env,
                          bc_CallContext* cctx) {
        if (cctx->Tag != CALL_METHOD_T) {
                return;
        }
        bc_Method* met = bc_GetMethodCContext(cctx);
        if (bc_IsStaticModifier(BC_MEMBER_MODIFIER(met))) {
                bc_Panic(BCERROR_ACCESS_TO_SUPER_AT_STATIC_METHOD_T,
                         bc_Ref2Str(bc_GetTypeName(BC_MEMBER_TYPE(met))),
                         bc_Ref2Str(met->Name));
        }
}