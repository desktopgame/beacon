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

static void check_context(il_factor_super * self, enviroment * env, call_context* cctx);

il_factor_super* il_factor_super_new() {
	il_factor_super* ret = (il_factor_super*)MEM_MALLOC(sizeof(il_factor_super));
	ret->resolved = NULL;
	return ret;
}

void il_factor_super_generate(il_factor_super * self, enviroment * env, call_context* cctx) {
	AddOpcodeBuf(env->buf, OP_SUPER);
}

void il_factor_super_load(il_factor_super * self, enviroment * env, call_context* cctx) {
	check_context(self, env, cctx);
}

generic_type* il_factor_super_eval(il_factor_super * self, enviroment * env, call_context* cctx) {
	type* t = call_context_type(cctx);
	return t->u.class_->super_class;
}

char* il_factor_super_tostr(il_factor_super* self, enviroment* env) {
	return Strdup("super");
}

void il_factor_super_delete(il_factor_super * self) {
	MEM_FREE(self);
}

//private
static void check_context(il_factor_super * self, enviroment * env, call_context* cctx) {
	if(cctx->tag != CALL_METHOD_T) {
		return;
	}
	method* met = call_context_method(cctx);
	if(IsStaticModifier(met->modifier)) {
		ThrowBCError(BCERROR_ACCESS_TO_SUPER_AT_STATIC_METHOD_T,
			Ref2Str(type_name(met->parent)),
			Ref2Str(met->namev)
		);
	}
}