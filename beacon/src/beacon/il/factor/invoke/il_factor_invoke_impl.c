#include "il_factor_invoke_impl.h"
#include "../../../util/mem.h"
#include "../../../env/generic_type.h"
#include "../../../vm/enviroment.h"

il_factor_invoke* il_factor_invoke_new() {
	il_factor_invoke* ret = (il_factor_invoke*)MEM_MALLOC(sizeof(il_factor_invoke));
	ret->args = NULL;
	ret->receiver = NULL;
	ret->type_args = NULL;
	return ret;
}

void il_factor_invoke_generate(il_factor_invoke* self, enviroment* env, il_load_cache* cache) {

}

void il_factor_invoke_load(il_factor_invoke * self, enviroment * env, il_load_cache* cache, il_ehandler* eh) {

}

generic_type* il_factor_invoke_eval(il_factor_invoke * self, enviroment * env, il_load_cache* cache) {
	return NULL;
}

void il_factor_invoke_delete(il_factor_invoke* self) {

}