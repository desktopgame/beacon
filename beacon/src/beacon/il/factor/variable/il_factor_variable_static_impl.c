#include "il_factor_variable_static_impl.h"
#include "../../../util/mem.h"
#include "../../../env/generic_type.h"
#include "../../../vm/enviroment.h"
#include "../../il_type_argument.h"

static void ILFactor_static_delete_typeargs(VectorItem item);

ILVariable_static* NewILVariableStatic() {
	ILVariable_static* ret = (ILVariable_static*)MEM_MALLOC(sizeof(ILVariable_static));
	ret->fqcn = NULL;
	ret->type_args = NULL;
	return ret;
}

void GenerateILVariableStatic(ILVariable_static* self, Enviroment* env, CallContext* cctx) {
	//FATAL("not implemented, because must be wrapped by call operator");
}

void LoadILVariableStatic(ILVariable_static * self, Enviroment * env, CallContext* cctx) {
//	FATAL("not implemented, because must be wrapped by call operator");
}

GenericType* EvalILVariableStatic(ILVariable_static * self, Enviroment * env, CallContext* cctx) {
	return NULL;
}

char* ILVariableStaticToString(ILVariable_static * self, Enviroment * env) {
	return NULL;
}

void DeleteILVariableStatic(ILVariable_static* self) {
	DeleteFQCNCache(self->fqcn);
	DeleteVector(self->type_args, ILFactor_static_delete_typeargs);
	MEM_FREE(self);
}
//private
static void ILFactor_static_delete_typeargs(VectorItem item) {
	ILTypeArgument* e = (ILTypeArgument*)item;
	DeleteILTypeArgument(e);
}