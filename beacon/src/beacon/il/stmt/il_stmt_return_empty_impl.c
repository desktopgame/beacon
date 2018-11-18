#include "il_stmt_return_empty_impl.h"
#include "../il_stmt_interface.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/method.h"
#include "../../env/generic_type.h"
#include "../../env/type_interface.h"
#include "../../env/namespace.h"

static void check_method_return(ILReturnEmpty self, Enviroment * env, CallContext* cctx);

void GenerateILReturnEmpty(ILReturnEmpty self, Enviroment* env, CallContext* cctx) {
	AddOpcodeBuf(env->Bytecode, OP_RETURN);
}

void LoadILReturnEmpty(ILReturnEmpty self, Enviroment* env, CallContext* cctx) {
	check_method_return(self, env, cctx);
}
//private
static void check_method_return(ILReturnEmpty self, Enviroment * env, CallContext* cctx) {
	if(cctx->Tag != CALL_METHOD_T) {
		return;
	}
	Method* m = GetMethodCContext(cctx);
	//戻り値が Void ではないのに値を返さない
	if(m->ReturnGType->CoreType != TYPE_VOID) {
		bc_Panic(BCERROR_NOT_RETURN_VALUE_NOT_VOID_METHOD_T,
			Ref2Str(GetTypeName(m->Parent)),
			Ref2Str(m->Name)
		);
		return;
	}
}