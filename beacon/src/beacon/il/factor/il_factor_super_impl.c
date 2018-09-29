#include "il_factor_super_impl.h"
#include <stdio.h>
#include <assert.h>
#include "../../vm/enviroment.h"
#include "../../util/text.h"
#include "../../util/mem.h"
#include "../../env/type_interface.h"
#include "../../env/type_impl.h"
#include "../call_context.h"
#include "../../error.h"

static void check_context(il_factor_super * self, enviroment * env, call_context* cctx);

il_factor_super* il_factor_super_new() {
	il_factor_super* ret = (il_factor_super*)MEM_MALLOC(sizeof(il_factor_super));
	ret->resolved = NULL;
	return ret;
}

void il_factor_super_generate(il_factor_super * self, enviroment * env, call_context* cctx) {
	opcode_buf_add(env->buf, op_super);
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
	if(cctx->tag != call_method_T) {
		return;
	}
	method* met = call_context_method(cctx);
	if(modifier_is_static(met->modifier)) {
		bc_error_throw(bcerror_access_to_super_at_static_method_T,
			Ref2Str(type_name(met->parent)),
			Ref2Str(met->namev)
		);
	}
}