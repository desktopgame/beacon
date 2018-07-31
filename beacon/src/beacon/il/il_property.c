#include "il_property.h"
#include "../util/mem.h"
#include "../env/generic_cache.h"
#include "../util/text.h"

il_property* il_property_malloc(string_view namev, const char* filename, int lineno) {
	il_property* ret = mem_malloc(sizeof(il_property), filename, lineno);
	ret->namev = namev;
	ret->fqcn = generic_cache_new();
	ret->set = NULL;
	ret->get = NULL;
	return ret;
}

void il_property_dump(il_property* self, int depth) {
	text_putindent(depth);
	access_print(self->access);
	text_printf(" ");
	modifier_print(self->modifier);
	text_printf(" property ");
	generic_cache_print(self->fqcn);
	text_printf(" %s", string_pool_ref2str(self->namev));
	text_putline();
	if(self->set != NULL) {
		il_property_body_dump(self->set, depth + 1);
	}
	if(self->get != NULL) {
		il_property_body_dump(self->get, depth + 1);
	}
}

void il_property_delete(il_property* self) {
	generic_cache_delete(self->fqcn);
	il_property_body_delete(self->set);
	il_property_body_delete(self->get);
	MEM_FREE(self);
}