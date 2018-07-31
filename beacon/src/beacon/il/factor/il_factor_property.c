#include "il_factor_property.h"
#include "../../util/mem.h"

il_factor_property* il_factor_property_malloc(const char* filename, int lineno) {
	il_factor_property* ret = mem_malloc(sizeof(il_factor_property), filename, lineno);
	ret->fact = NULL;
	ret->index = -1;
	ret->namev = ZERO_VIEW;
	ret->p = NULL;
	return ret;
}

void il_factor_property_delete(il_factor_property* self) {
	MEM_FREE(self);
}