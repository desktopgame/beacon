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

il_factor_this* il_factor_this_new() {
	il_factor_this* ret = (il_factor_this*)MEM_MALLOC(sizeof(il_factor_this));
	ret->resolved = NULL;
	return ret;
}

void il_factor_this_dump(il_factor_this * self, int depth) {
	text_putindent(depth);
	text_printf("this");
	text_putline();
}

void il_factor_this_generate(il_factor_this * self, enviroment * env, call_context* cctx) {
	opcode_buf_add(env->buf, op_this);
}

void il_factor_this_load(il_factor_this * self, enviroment * env, call_context* cctx) {
	check_context(self, env, cctx);
}

generic_type* il_factor_this_eval(il_factor_this * self, enviroment * env, call_context* cctx) {
	return call_context_type(cctx)->generic_self;
}

char* il_factor_this_tostr(il_factor_this* self, enviroment* env) {
	return text_strdup("this");
}

void il_factor_this_delete(il_factor_this * self) {
	MEM_FREE(self);
}
//private
static void check_context(il_factor_this * self, enviroment * env, call_context* cctx) {
	if(cctx->tag != call_method_T) {
		return;
	}
	method* met = call_context_method(cctx);
	if(modifier_is_static(met->modifier)) {
		bc_error_throw(bcerror_access_to_this_at_static_method,
			string_pool_ref2str(type_name(met->parent)),
			string_pool_ref2str(met->namev)
		);
	}
}