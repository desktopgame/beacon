#include "il_factor_super_impl.h"
#include <stdio.h>
#include <assert.h>
#include "../../vm/enviroment.h"
#include "../../util/text.h"
#include "../../util/mem.h"
#include "../../env/type_interface.h"
#include "../../env/TYPE_IMPL.h"
#include "../call_context.h"
#include "../../error.h"

static void check_context(ILSuper * self, bc_Enviroment * env, bc_CallContext* cctx);

ILSuper* NewILSuper() {
	ILSuper* ret = (ILSuper*)MEM_MALLOC(sizeof(ILSuper));
	ret->Resolved = NULL;
	return ret;
}

void GenerateILSuper(ILSuper * self, bc_Enviroment * env, bc_CallContext* cctx) {
	bc_AddOpcodeBuf(env->Bytecode, OP_SUPER);
}

void LoadILSuper(ILSuper * self, bc_Enviroment * env, bc_CallContext* cctx) {
	check_context(self, env, cctx);
}

bc_GenericType* EvalILSuper(ILSuper * self, bc_Enviroment * env, bc_CallContext* cctx) {
	bc_Type* t = bc_GetTypeCContext(cctx);
	return t->Kind.Class->SuperClass;
}

char* ILSuperToString(ILSuper* self, bc_Enviroment* env) {
	return bc_Strdup("super");
}

void DeleteILSuper(ILSuper * self) {
	MEM_FREE(self);
}

//private
static void check_context(ILSuper * self, bc_Enviroment * env, bc_CallContext* cctx) {
	if(cctx->Tag != CALL_METHOD_T) {
		return;
	}
	bc_Method* met = bc_GetMethodCContext(cctx);
	if(bc_IsStaticModifier(met->Modifier)) {
		bc_Panic(BCERROR_ACCESS_TO_SUPER_AT_STATIC_METHOD_T,
			bc_Ref2Str(bc_GetTypeName(met->Parent)),
			bc_Ref2Str(met->Name)
		);
	}
}