#include "il_factor_variable_static_impl.h"
#include "../../../util/mem.h"
#include "../../../env/generic_type.h"
#include "../../../vm/enviroment.h"
#include "../../il_type_argument.h"

static void il_factor_static_delete_typeargs(VectorItem item);

il_factor_variable_static* NewILVariableStatic() {
	il_factor_variable_static* ret = (il_factor_variable_static*)MEM_MALLOC(sizeof(il_factor_variable_static));
	ret->fqcn = NULL;
	ret->type_args = NULL;
	return ret;
}

void il_factor_variable_static_generate(il_factor_variable_static* self, enviroment* env, call_context* cctx) {
	//FATAL("not implemented, because must be wrapped by call operator");
}

void LoadILVariableStatic(il_factor_variable_static * self, enviroment * env, call_context* cctx) {
//	FATAL("not implemented, because must be wrapped by call operator");
}

generic_type* EvalILVariableStatic(il_factor_variable_static * self, enviroment * env, call_context* cctx) {
	return NULL;
}

char* ILVariableStaticToString(il_factor_variable_static * self, enviroment * env) {
	return NULL;
}

void DeleteILVariableStatic(il_factor_variable_static* self) {
	fqcn_cache_delete(self->fqcn);
	DeleteVector(self->type_args, il_factor_static_delete_typeargs);
	MEM_FREE(self);
}
//private
static void il_factor_static_delete_typeargs(VectorItem item) {
	il_type_argument* e = (il_type_argument*)item;
	DeleteILTypeArgument(e);
}