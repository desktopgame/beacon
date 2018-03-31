#include "il_factor_invoke_static_impl.h"
#include "../../../util/mem.h"
#include "../../../env/generic_type.h"
#include "../../../vm/enviroment.h"

il_factor_invoke_static* il_factor_invoke_static_new() {
	il_factor_invoke_static* ret = (il_factor_invoke_static*)MEM_MALLOC(sizeof(il_factor_invoke_static));
	ret->args = NULL;
	ret->fqcn = NULL;
	ret->type_args = NULL;
	return ret;
}

void il_factor_invoke_static_generate(il_factor_invoke_static* self, enviroment* env, il_load_cache* cache) {

}

void il_factor_invoke_static_load(il_factor_invoke_static * self, enviroment * env, il_load_cache* cache, il_ehandler* eh) {

}

generic_type* il_factor_invoke_static_eval(il_factor_invoke_static * self, enviroment * env, il_load_cache* cache) {
	return NULL;
}

void il_factor_invoke_static_delete(il_factor_invoke_static* self) {

}