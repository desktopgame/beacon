#include "virtual_type.h"
#include "generic_type.h"
#include "../util/text.h"
#include "namespace.h"
#include "type_impl.h"

//proto
static bool virtual_type_comp(virtual_type* self, type* tp);

void virtual_type_nongeneric_init(virtual_type* self, generic_type* gtype) {
	self->tag = virtualtype_default;
	self->u.gtype = gtype;
}

void virtual_type_class_init(virtual_type* self, int index) {
	self->tag = virtualtype_class_tv;
	self->u.index = index;
}

void virtual_type_method_init(virtual_type* self, int index) {
	self->tag = virtualtype_method_tv;
	self->u.index = index;
}

void virtual_type_print(const virtual_type* self) {
	if(self->tag == virtualtype_default) {
		generic_type_print(self->u.gtype);
	} else if(self->tag == virtualtype_class_tv) {
		text_printf("class generic<%d>", self->u.index);
	} else if(self->tag == virtualtype_method_tv) {
		text_printf("method generic<%d>", self->u.index);
	}
}

bool virtual_type_eq(const virtual_type* a, const virtual_type* b) {
	if(a->tag != b->tag) {
		return false;
	}
	if(a->tag == virtualtype_default) {
		generic_type* ga = a->u.gtype;
		generic_type* gb = b->u.gtype;
		return ga == gb;
	}
	return false;
}

bool virtual_type_void(virtual_type* self) {
	return virtual_type_comp(self, CL_VOID);
}

bool virtual_type_int(virtual_type* self) {
	return virtual_type_comp(self, CL_INT);
}

bool virtual_type_double(virtual_type* self) {
	return virtual_type_comp(self, CL_DOUBLE);
}

bool virtual_type_bool(virtual_type* self) {
	return virtual_type_comp(self, CL_BOOL);
}

bool virtual_type_char(virtual_type* self) {
	return virtual_type_comp(self, CL_CHAR);
}

bool virtual_type_null(virtual_type* self){
	return virtual_type_comp(self, CL_NULL);
}

int virtual_type_distance(virtual_type* self, generic_type* a, il_context* ilctx) {
	if(self->tag == virtualtype_default) {
		return generic_type_distance(self->u.gtype, a, ilctx);
	} else if(self->tag == virtualtype_class_tv) {
		generic_type* r = (generic_type*)vector_top(ilctx->receiver_vec);
		generic_type* m = vector_at(r->type_args_list, self->u.index);
		return generic_type_distance(m, a, ilctx);
	} else if(self->tag == virtualtype_method_tv) {
		vector* type_args = ilctx->type_args_vec;
		generic_type* r = vector_at(type_args, self->u.index);
		return generic_type_distance(r, a, ilctx);
	}
	return 0;
}

//private
static bool virtual_type_comp(virtual_type* self, type* tp) {
	if(self->tag == virtualtype_default) {
		return self->u.gtype->core_type == tp;
	}
	return false;
}