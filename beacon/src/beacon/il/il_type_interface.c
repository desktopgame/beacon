#include "il_type_interface.h"
#include "../util/mem.h"
#include "il_TYPE_IMPL.h"
#include "il_property.h"
#include "il_constructor.h"
#include "il_field.h"
#include "il_method.h"
#include <assert.h>

il_type * il_type_new() {
	il_type* ret = (il_type*)MEM_MALLOC(sizeof(il_type));
	ret->tag = ilTYPE_CLASS_T;
	return ret;
}

Vector * il_type_method_vec(il_type * self) {
	if (self->tag == ilTYPE_CLASS_T) {
		return self->u.class_->method_list;
	} else if (self->tag == ilTYPE_INTERFACE_T) {
		return self->u.interface_->method_list;
	}
	return NULL;
}

Vector * il_type_smethod_vec(il_type * self) {
	if (self->tag == ilTYPE_CLASS_T) {
		return self->u.class_->smethod_list;
	} else if (self->tag == ilTYPE_INTERFACE_T) {
		return NULL;
	}
	return NULL;
}

void il_type_add_constructor(il_type * self, il_constructor * ctor) {
	assert(self->tag == ilTYPE_CLASS_T);
	if (self->tag == ilTYPE_CLASS_T) {
	}
}

void il_type_add_field(il_type * self, il_field * field) {
	assert(self->tag == ilTYPE_CLASS_T);
	if (self->tag == ilTYPE_CLASS_T) {
		il_class_add_field(self->u.class_, field);
	}
}

void il_type_add_property(il_type* self, il_property* prop) {
	if (self->tag == ilTYPE_CLASS_T) {
		il_class_add_property(self->u.class_, prop);
	} else if(self->tag == ilTYPE_INTERFACE_T) {
		il_interface_add_property(self->u.interface_, prop);
	}
}

void il_type_add_method(il_type * self, il_method * method) {
	if (self->tag == ilTYPE_CLASS_T) {
		il_class_add_method(self->u.class_, method);
	} else if (self->tag == ilTYPE_INTERFACE_T) {
		il_interface_add_method(self->u.interface_, method);
	}
}

void il_type_delete(il_type * self) {
	if (self->tag == ilTYPE_CLASS_T) {
		il_class_delete(self->u.class_);
	} else if (self->tag == ilTYPE_INTERFACE_T) {
		il_interface_delete(self->u.interface_);
	} else if(self->tag == ilTYPE_ENUM_T) {
		il_enum_delete(self->u.enum_);
	}
	MEM_FREE(self);
}

Vector* il_type_type_parameter_list(il_type* self) {
	return self->tag == ilTYPE_INTERFACE_T ? self->u.interface_->type_parameter_list : self->u.class_->type_parameter_list;
}