#include "default_operator_resolve.h"
#include "../../util/mem.h"
#include "../../vm/lazy_int.h"
#include "../type_impl.h"
#include <assert.h>

default_operator_resolve* default_operator_resolve_new() {
	default_operator_resolve* ret = (default_operator_resolve*)MEM_MALLOC(sizeof(default_operator_resolve));
	ret->lazyi_ref = NULL;
	ret->type_ref = NULL;
	return ret;
}

void default_operator_resolve_apply(default_operator_resolve* self) {
	int pos = 0;
	class_gfind_eqmethod(TYPE2CLASS(self->type_ref), &pos);
	assert(pos != -1);
	self->lazyi_ref->value = pos;
}

void default_operator_resolve_delete(default_operator_resolve* self) {
	MEM_FREE(self);
}