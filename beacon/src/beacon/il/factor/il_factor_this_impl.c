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

static void check_context(ILFactor_this * self, Enviroment * env, CallContext* cctx);

ILFactor_this* NewILThis() {
	ILFactor_this* ret = (ILFactor_this*)MEM_MALLOC(sizeof(ILFactor_this));
	ret->resolved = NULL;
	return ret;
}

void GenerateILThis(ILFactor_this * self, Enviroment * env, CallContext* cctx) {
	AddOpcodeBuf(env->Bytecode, OP_THIS);
}

void LoadILThis(ILFactor_this * self, Enviroment * env, CallContext* cctx) {
	check_context(self, env, cctx);
}

GenericType* EvalILThis(ILFactor_this * self, Enviroment * env, CallContext* cctx) {
	return GetTypeCContext(cctx)->generic_self;
}

char* ILThisToString(ILFactor_this* self, Enviroment* env) {
	return Strdup("this");
}

void DeleteILThis(ILFactor_this * self) {
	MEM_FREE(self);
}
//private
static void check_context(ILFactor_this * self, Enviroment * env, CallContext* cctx) {
	if(cctx->Tag != CALL_METHOD_T) {
		return;
	}
	Method* met = GetMethodCContext(cctx);
	if(IsStaticModifier(met->Modifier)) {
		ThrowBCError(BCERROR_ACCESS_TO_THIS_AT_STATIC_METHOD_T,
			Ref2Str(GetTypeName(met->Parent)),
			Ref2Str(met->Name)
		);
	}
}