#include "lazy_resolve.h"
#include "../util/mem.h"
#include "resolve/default_operator_resolve.h"

lazy_resolve* lazy_resolve_new(lazy_resolve_tag tag) {
	lazy_resolve* ret = (lazy_resolve*)MEM_MALLOC(sizeof(lazy_resolve));
	ret->tag = tag;
	ret->active = true;
	switch(ret->tag) {
		case resolve_default_operator:
			ret->u.def_operator = default_operator_resolve_new();
			break;
	}
	return ret;
}

void lazy_resolve_apply(lazy_resolve* self) {
	switch(self->tag) {
		case resolve_default_operator:
			default_operator_resolve_apply(self->u.def_operator);
			break;
	}
}

void lazy_resolve_delete(lazy_resolve* self) {
	switch(self->tag) {
		case resolve_default_operator:
			default_operator_resolve_delete(self->u.def_operator);
			break;
	}
	MEM_FREE(self);
}