#include "il_factor_property.h"
#include "../../util/mem.h"
#include "../../vm/enviroment.h"
#include "../../env/generic_type.h"

il_factor_property* il_factor_property_malloc(const char* filename, int lineno) {
	il_factor_property* ret = mem_malloc(sizeof(il_factor_property), filename, lineno);
	ret->fact = NULL;
	ret->index = -1;
	ret->namev = ZERO_VIEW;
	ret->p = NULL;
	return ret;
}

void il_factor_property_generate(il_factor_property* self, enviroment* env, call_context* cctx) {
}

void il_factor_property_load(il_factor_property* self, enviroment* env, call_context* cctx) {
}

generic_type* il_factor_property_eval(il_factor_property* self, enviroment* env, call_context* cctx) {
	return NULL;
}

char* il_factor_property_tostr(il_factor_property* self, enviroment* env) {
	return NULL;
}

void il_factor_property_dump(il_factor_property* self, int depth) {

}

void il_factor_property_delete(il_factor_property* self) {
	MEM_FREE(self);
}