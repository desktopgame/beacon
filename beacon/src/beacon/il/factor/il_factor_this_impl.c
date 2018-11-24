#include "il_factor_this_impl.h"
#include <stdio.h>
#include "../../util/text.h"
#include "../../util/mem.h"
#include "../../vm/enviroment.h"
#include "../../env/type_interface.h"
#include "../../env/method.h"
#include "../call_context.h"
#include "../../error.h"
#include <assert.h>

static void check_context(bc_ILThis * self, bc_Enviroment * env, bc_CallContext* cctx);

bc_ILThis* bc_NewILThis() {
	bc_ILThis* ret = (bc_ILThis*)MEM_MALLOC(sizeof(bc_ILThis));
	ret->Resolved = NULL;
	return ret;
}

void bc_GenerateILThis(bc_ILThis * self, bc_Enviroment * env, bc_CallContext* cctx) {
	bc_AddOpcodeBuf(env->Bytecode, OP_THIS);
}

void bc_LoadILThis(bc_ILThis * self, bc_Enviroment * env, bc_CallContext* cctx) {
	check_context(self, env, cctx);
}

bc_GenericType* bc_EvalILThis(bc_ILThis * self, bc_Enviroment * env, bc_CallContext* cctx) {
	return bc_GetTypeCContext(cctx)->GenericSelf;
}

char* bc_ILThisToString(bc_ILThis* self, bc_Enviroment* env) {
	return bc_Strdup("this");
}

void bc_DeleteILThis(bc_ILThis * self) {
	MEM_FREE(self);
}
//private
static void check_context(bc_ILThis * self, bc_Enviroment * env, bc_CallContext* cctx) {
	if(cctx->Tag != CALL_METHOD_T) {
		return;
	}
	bc_Method* met = bc_GetMethodCContext(cctx);
	if(bc_IsStaticModifier(BC_MEMBER_MODIFIER(met))) {
		bc_Panic(BCERROR_ACCESS_TO_THIS_AT_STATIC_METHOD_T,
			bc_Ref2Str(bc_GetTypeName(BC_MEMBER_TYPE(met))),
			bc_Ref2Str(met->Name)
		);
	}
}