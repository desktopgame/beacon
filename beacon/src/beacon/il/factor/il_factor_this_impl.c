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

static void check_context(il_factor_this * self, enviroment * env, call_context* cctx);

il_factor_this* NewILThis() {
	il_factor_this* ret = (il_factor_this*)MEM_MALLOC(sizeof(il_factor_this));
	ret->resolved = NULL;
	return ret;
}

void il_factor_this_generate(il_factor_this * self, enviroment * env, call_context* cctx) {
	AddOpcodeBuf(env->buf, OP_THIS);
}

void LoadILThis(il_factor_this * self, enviroment * env, call_context* cctx) {
	check_context(self, env, cctx);
}

generic_type* EvalILThis(il_factor_this * self, enviroment * env, call_context* cctx) {
	return GetTypeCContext(cctx)->generic_self;
}

char* ILThisToString(il_factor_this* self, enviroment* env) {
	return Strdup("this");
}

void DeleteILThis(il_factor_this * self) {
	MEM_FREE(self);
}
//private
static void check_context(il_factor_this * self, enviroment * env, call_context* cctx) {
	if(cctx->tag != CALL_METHOD_T) {
		return;
	}
	method* met = GetMethodCContext(cctx);
	if(IsStaticModifier(met->modifier)) {
		ThrowBCError(BCERROR_ACCESS_TO_THIS_AT_STATIC_METHOD_T,
			Ref2Str(type_name(met->parent)),
			Ref2Str(met->namev)
		);
	}
}