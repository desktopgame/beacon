#include "default_eqoperator_resolve.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../vm/lazy_int.h"
#include "../type_impl.h"
#include <assert.h>

default_eqoperator_resolve* default_eqoperator_resolve_new() {
	default_eqoperator_resolve* ret = (default_eqoperator_resolve*)MEM_MALLOC(sizeof(default_eqoperator_resolve));
	ret->lazyi_ref = NULL;
	ret->type_ref = NULL;
	return ret;
}

void default_eqoperator_resolve_apply(default_eqoperator_resolve* self) {
	int pos = 0;
	class_gfind_eqmethod(TYPE2CLASS(self->type_ref), &pos);
	assert(pos != -1);
	self->lazyi_ref->value = pos;
}

void default_eqoperator_resolve_delete(default_eqoperator_resolve* self) {
	MEM_FREE(self);
}