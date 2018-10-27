#include "il_factor_variable_static_impl.h"
#include "../../../util/mem.h"
#include "../../../env/generic_type.h"
#include "../../../vm/enviroment.h"
#include "../../il_type_argument.h"

static void ILFactor_static_delete_typeargs(VectorItem item);

ILFactor_variable_static* NewILVariableStatic() {
	ILFactor_variable_static* ret = (ILFactor_variable_static*)MEM_MALLOC(sizeof(ILFactor_variable_static));
	ret->fqcn = NULL;
	ret->type_args = NULL;
	return ret;
}

void GenerateILVariableStatic(ILFactor_variable_static* self, Enviroment* env, CallContext* cctx) {
	//FATAL("not implemented, because must be wrapped by call operator");
}

void LoadILVariableStatic(ILFactor_variable_static * self, Enviroment * env, CallContext* cctx) {
//	FATAL("not implemented, because must be wrapped by call operator");
}

GenericType* EvalILVariableStatic(ILFactor_variable_static * self, Enviroment * env, CallContext* cctx) {
	return NULL;
}

char* ILVariableStaticToString(ILFactor_variable_static * self, Enviroment * env) {
	return NULL;
}

void DeleteILVariableStatic(ILFactor_variable_static* self) {
	DeleteFQCNCache(self->fqcn);
	DeleteVector(self->type_args, ILFactor_static_delete_typeargs);
	MEM_FREE(self);
}
//private
static void ILFactor_static_delete_typeargs(VectorItem item) {
	ILTypeArgument* e = (ILTypeArgument*)item;
	DeleteILTypeArgument(e);
}