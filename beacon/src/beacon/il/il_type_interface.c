#include "il_type_interface.h"
#include "../util/mem.h"
#include "il_type_impl.h"
#include "il_property.h"
#include "il_constructor.h"
#include "il_field.h"
#include "il_method.h"
#include <assert.h>

il_type * il_type_new() {
	il_type* ret = (il_type*)MEM_MALLOC(sizeof(il_type));
	ret->tag = iltype_class;
	return ret;
}

vector * il_type_method_vec(il_type * self) {
	if (self->tag == iltype_class) {
		return self->u.class_->method_list;
	} else if (self->tag == iltype_interface) {
		return self->u.interface_->method_list;
	}
	return NULL;
}

vector * il_type_smethod_vec(il_type * self) {
	if (self->tag == iltype_class) {
		return self->u.class_->smethod_list;
	} else if (self->tag == iltype_interface) {
		return NULL;
	}
	return NULL;
}

void il_type_add_constructor(il_type * self, il_constructor * ctor) {
	assert(self->tag == iltype_class);
	if (self->tag == iltype_class) {
	}
}

void il_type_add_field(il_type * self, il_field * field) {
	assert(self->tag == iltype_class);
	if (self->tag == iltype_class) {
		il_class_add_field(self->u.class_, field);
	}
}

void il_type_add_property(il_type* self, il_property* prop) {
	if (self->tag == iltype_class) {
		il_class_add_property(self->u.class_, prop);
	} else if(self->tag == iltype_interface) {
		il_interface_add_property(self->u.interface_, prop);
	}
}

void il_type_add_method(il_type * self, il_method * method) {
	if (self->tag == iltype_class) {
		il_class_add_method(self->u.class_, method);
	} else if (self->tag == iltype_interface) {
		il_interface_add_method(self->u.interface_, method);
	}
}

void il_type_dump(il_type * self, int depth) {
	if (self->tag == iltype_class) {
		il_class_dump(self->u.class_, depth);
	} else if (self->tag == iltype_interface) {
		il_interface_dump(self->u.interface_, depth);
	} else if (self->tag == iltype_enum) {
		il_enum_dump(self->u.enum_, depth);
	}
}

void il_type_delete(il_type * self) {
	if (self->tag == iltype_class) {
		il_class_delete(self->u.class_);
	} else if (self->tag == iltype_interface) {
		il_interface_delete(self->u.interface_);
	} else if(self->tag == iltype_enum) {
		il_enum_delete(self->u.enum_);
	}
	MEM_FREE(self);
}

vector* il_type_type_parameter_list(il_type* self) {
	return self->tag == iltype_interface ? self->u.interface_->type_parameter_list : self->u.class_->type_parameter_list;
}