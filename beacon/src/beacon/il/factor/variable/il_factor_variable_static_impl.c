#include "il_factor_variable_static_impl.h"
#include "../../../util/mem.h"
#include "../../../env/generic_type.h"
#include "../../../vm/enviroment.h"
#include "../../il_type_argument.h"

static void ILFactor_static_delete_typeargs(bc_VectorItem item);

bc_ILVariableStatic* bc_NewILVariableStatic() {
	bc_ILVariableStatic* ret = (bc_ILVariableStatic*)MEM_MALLOC(sizeof(bc_ILVariableStatic));
	ret->FQCN = NULL;
	ret->TypeArgs = NULL;
	return ret;
}

void bc_GenerateILVariableStatic(bc_ILVariableStatic* self, bc_Enviroment* env, bc_CallContext* cctx) {
	//FATAL("not implemented, because must be wrapped by call operator");
}

void bc_LoadILVariableStatic(bc_ILVariableStatic * self, bc_Enviroment * env, bc_CallContext* cctx) {
//	FATAL("not implemented, because must be wrapped by call operator");
}

bc_GenericType* bc_EvalILVariableStatic(bc_ILVariableStatic * self, bc_Enviroment * env, bc_CallContext* cctx) {
	return NULL;
}

char* bc_ILVariableStaticToString(bc_ILVariableStatic * self, bc_Enviroment * env) {
	return NULL;
}

void bc_DeleteILVariableStatic(bc_ILVariableStatic* self) {
	bc_DeleteFQCNCache(self->FQCN);
	bc_DeleteVector(self->TypeArgs, ILFactor_static_delete_typeargs);
	MEM_FREE(self);
}
//private
static void ILFactor_static_delete_typeargs(bc_VectorItem item) {
	bc_ILTypeArgument* e = (bc_ILTypeArgument*)item;
	bc_DeleteILTypeArgument(e);
}