#include "il_factor_variable_static_impl.h"
#include "../../../util/mem.h"
#include "../../../env/generic_type.h"
#include "../../../vm/enviroment.h"
#include "../../il_type_argument.h"

static void ILFactor_static_delete_typeargs(VectorItem item);

ILVariableStatic* NewILVariableStatic() {
	ILVariableStatic* ret = (ILVariableStatic*)MEM_MALLOC(sizeof(ILVariableStatic));
	ret->FQCN = NULL;
	ret->TypeArgs = NULL;
	return ret;
}

void GenerateILVariableStatic(ILVariableStatic* self, Enviroment* env, CallContext* cctx) {
	//FATAL("not implemented, because must be wrapped by call operator");
}

void LoadILVariableStatic(ILVariableStatic * self, Enviroment * env, CallContext* cctx) {
//	FATAL("not implemented, because must be wrapped by call operator");
}

bc_GenericType* EvalILVariableStatic(ILVariableStatic * self, Enviroment * env, CallContext* cctx) {
	return NULL;
}

char* ILVariableStaticToString(ILVariableStatic * self, Enviroment * env) {
	return NULL;
}

void DeleteILVariableStatic(ILVariableStatic* self) {
	bc_DeleteFQCNCache(self->FQCN);
	DeleteVector(self->TypeArgs, ILFactor_static_delete_typeargs);
	MEM_FREE(self);
}
//private
static void ILFactor_static_delete_typeargs(VectorItem item) {
	ILTypeArgument* e = (ILTypeArgument*)item;
	DeleteILTypeArgument(e);
}