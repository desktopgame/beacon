#include "lazy_resolve.h"
#include "../util/mem.h"
#include "resolve/default_eqoperator_resolve.h"
#include "resolve/default_noteqoperator_resolve.h"

lazy_resolve* lazy_resolve_new(lazy_resolve_tag tag) {
	lazy_resolve* ret = (lazy_resolve*)MEM_MALLOC(sizeof(lazy_resolve));
	ret->tag = tag;
	ret->active = true;
	switch(ret->tag) {
		case resolve_default_eqoperator:
			ret->u.def_eqoperator = default_eqoperator_resolve_new();
			break;
		case resolve_default_noteqoperator:
			ret->u.def_noteqoperator = default_noteqoperator_resolve_new();
			break;
	}
	return ret;
}

void lazy_resolve_apply(lazy_resolve* self) {
	switch(self->tag) {
		case resolve_default_eqoperator:
			default_eqoperator_resolve_apply(self->u.def_eqoperator);
			break;
		case resolve_default_noteqoperator:
			default_noteqoperator_resolve_apply(self->u.def_noteqoperator);
			break;
	}
}

void lazy_resolve_delete(lazy_resolve* self) {
	switch(self->tag) {
		case resolve_default_eqoperator:
			default_eqoperator_resolve_delete(self->u.def_eqoperator);
			break;
		case resolve_default_noteqoperator:
			default_noteqoperator_resolve_delete(self->u.def_noteqoperator);
			break;
	}
	MEM_FREE(self);
}