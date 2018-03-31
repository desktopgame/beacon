#include "il_factor_invoke_bound_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../env/generic_type.h"
#include "../../../vm/enviroment.h"

il_factor_invoke_bound* il_factor_invoke_bound_new(const char* name) {
	il_factor_invoke_bound* ret = (il_factor_invoke_bound*)MEM_MALLOC(sizeof(il_factor_invoke_bound));
	ret->name = text_strdup(name);
	ret->args = NULL;
	ret->type_args = NULL;
	return ret;
}

void il_factor_invoke_bound_generate(il_factor_invoke_bound* self, enviroment* env, il_load_cache* cache) {

}

void il_factor_invoke_bound_load(il_factor_invoke_bound * self, enviroment * env, il_load_cache* cache, il_ehandler* eh) {

}

generic_type* il_factor_invoke_bound_eval(il_factor_invoke_bound * self, enviroment * env, il_load_cache* cache) {
	return NULL;
}

void il_factor_invoke_bound_delete(il_factor_invoke_bound* self) {

}