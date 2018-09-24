#include "il_stmt_return_empty_impl.h"
#include "../il_stmt_interface.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/method.h"
#include "../../env/generic_type.h"
#include "../../env/type_interface.h"
#include "../../env/namespace.h"

static void check_method_return(il_stmt_return_empty self, enviroment * env, call_context* cctx);

void il_stmt_return_empty_generate(il_stmt_return_empty self, enviroment* env, call_context* cctx) {
	opcode_buf_add(env->buf, op_return);
}

void il_stmt_return_empty_load(il_stmt_return_empty self, enviroment* env, call_context* cctx) {
	check_method_return(self, env, cctx);
}
//private
static void check_method_return(il_stmt_return_empty self, enviroment * env, call_context* cctx) {
	if(cctx->tag != call_method_T) {
		return;
	}
	method* m = call_context_method(cctx);
	//戻り値が Void ではないのに値を返さない
	if(m->return_gtype->core_type != TYPE_VOID) {
		bc_error_throw(bcerror_not_return_value_not_void_method_T,
			string_pool_ref2str(type_name(m->parent)),
			string_pool_ref2str(m->namev)
		);
		return;
	}
}