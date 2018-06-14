#include "default_noteqoperator_resolve.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/type_impl.h"
#include <assert.h>

default_noteqoperator_resolve* default_noteqoperator_resolve_new() {
	default_noteqoperator_resolve* ret = (default_noteqoperator_resolve*)MEM_MALLOC(sizeof(default_noteqoperator_resolve));
	ret->lazyi_ref = NULL;
	ret->type_ref = NULL;
	return ret;
}

void default_noteqoperator_resolve_apply(default_noteqoperator_resolve* self) {
	int pos = 0;
	class_gfind_eqmethod(TYPE2CLASS(self->type_ref), &pos);
	assert(pos != -1);
	self->lazyi_ref->value = pos;
}

void default_noteqoperator_resolve_delete(default_noteqoperator_resolve* self) {
	MEM_FREE(self);
}