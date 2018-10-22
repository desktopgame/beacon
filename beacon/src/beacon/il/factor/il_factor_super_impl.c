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

static void check_context(il_factor_super * self, Enviroment * env, CallContext* cctx);

il_factor_super* NewILSuper() {
	il_factor_super* ret = (il_factor_super*)MEM_MALLOC(sizeof(il_factor_super));
	ret->resolved = NULL;
	return ret;
}

void GenerateILSuper(il_factor_super * self, Enviroment * env, CallContext* cctx) {
	AddOpcodeBuf(env->Bytecode, OP_SUPER);
}

void LoadILSuper(il_factor_super * self, Enviroment * env, CallContext* cctx) {
	check_context(self, env, cctx);
}

generic_type* EvalILSuper(il_factor_super * self, Enviroment * env, CallContext* cctx) {
	type* t = GetTypeCContext(cctx);
	return t->u.class_->super_class;
}

char* ILSuperToString(il_factor_super* self, Enviroment* env) {
	return Strdup("super");
}

void DeleteILSuper(il_factor_super * self) {
	MEM_FREE(self);
}

//private
static void check_context(il_factor_super * self, Enviroment * env, CallContext* cctx) {
	if(cctx->tag != CALL_METHOD_T) {
		return;
	}
	method* met = GetMethodCContext(cctx);
	if(IsStaticModifier(met->modifier)) {
		ThrowBCError(BCERROR_ACCESS_TO_SUPER_AT_STATIC_METHOD_T,
			Ref2Str(GetTypeName(met->parent)),
			Ref2Str(met->namev)
		);
	}
}