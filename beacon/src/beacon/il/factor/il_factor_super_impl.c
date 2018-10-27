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

static void check_context(ILFactor_super * self, Enviroment * env, CallContext* cctx);

ILFactor_super* NewILSuper() {
	ILFactor_super* ret = (ILFactor_super*)MEM_MALLOC(sizeof(ILFactor_super));
	ret->resolved = NULL;
	return ret;
}

void GenerateILSuper(ILFactor_super * self, Enviroment * env, CallContext* cctx) {
	AddOpcodeBuf(env->Bytecode, OP_SUPER);
}

void LoadILSuper(ILFactor_super * self, Enviroment * env, CallContext* cctx) {
	check_context(self, env, cctx);
}

GenericType* EvalILSuper(ILFactor_super * self, Enviroment * env, CallContext* cctx) {
	type* t = GetTypeCContext(cctx);
	return t->u.class_->super_class;
}

char* ILSuperToString(ILFactor_super* self, Enviroment* env) {
	return Strdup("super");
}

void DeleteILSuper(ILFactor_super * self) {
	MEM_FREE(self);
}

//private
static void check_context(ILFactor_super * self, Enviroment * env, CallContext* cctx) {
	if(cctx->Tag != CALL_METHOD_T) {
		return;
	}
	Method* met = GetMethodCContext(cctx);
	if(IsStaticModifier(met->Modifier)) {
		ThrowBCError(BCERROR_ACCESS_TO_SUPER_AT_STATIC_METHOD_T,
			Ref2Str(GetTypeName(met->Parent)),
			Ref2Str(met->Name)
		);
	}
}