#include "il_stmt_return_empty_impl.h"
#include "../il_stmt_interface.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/method.h"
#include "../../env/generic_type.h"
#include "../../env/type_interface.h"
#include "../../env/namespace.h"

static void check_method_return(il_stmt_return_empty self, Enviroment * env, CallContext* cctx);

void GenerateILReturnEmpty(il_stmt_return_empty self, Enviroment* env, CallContext* cctx) {
	AddOpcodeBuf(env->Bytecode, OP_RETURN);
}

void LoadILReturnEmpty(il_stmt_return_empty self, Enviroment* env, CallContext* cctx) {
	check_method_return(self, env, cctx);
}
//private
static void check_method_return(il_stmt_return_empty self, Enviroment * env, CallContext* cctx) {
	if(cctx->Tag != CALL_METHOD_T) {
		return;
	}
	method* m = GetMethodCContext(cctx);
	//戻り値が Void ではないのに値を返さない
	if(m->return_gtype->core_type != TYPE_VOID) {
		ThrowBCError(BCERROR_NOT_RETURN_VALUE_NOT_VOID_METHOD_T,
			Ref2Str(GetTypeName(m->parent)),
			Ref2Str(m->namev)
		);
		return;
	}
}