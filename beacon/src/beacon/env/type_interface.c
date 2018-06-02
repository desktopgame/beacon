#include "type_interface.h"
#include "../util/mem.h"
#include "type_impl.h"
#include "field.h"
#include "method.h"
#include "type_parameter.h"
#include "generic_type.h"
#include "../util/text.h"
#include "../util/xassert.h"
#include <assert.h>
#include <string.h>

type * type_new() {
	type* ret = (type*)MEM_MALLOC(sizeof(type));
	ret->tag = type_class;
	ret->location = NULL;
	ret->absolute_index = -1;
	ret->generic_self = NULL;
	return ret;
}

generic_type* type_init_generic(type* self, int counts) {
	if (self == NULL) {
		return NULL;
	}
	if (self->generic_self == NULL) {
		self->generic_self = generic_type_new(self);
		for (int i = 0; i < counts; i++) {
			generic_type* arg = generic_type_new(NULL);
			arg->tag = generic_type_tag_self;
			arg->virtual_type_index = i;
			generic_type_addargs(self->generic_self, arg);
		}
	}
	return self->generic_self;
}

char * type_name(type * self) {
	//assert(self->tag == type_class);
	if(self == NULL) {
		return "NULL";
	}
	if (self->tag == type_class) {
		return self->u.class_->name;
	} else if (self->tag == type_interface) {
		return self->u.interface_->name;
	}
	return NULL;
}

void type_add_field(type* self, field * f) {
	assert(self->tag == type_class);
	class_add_field(self->u.class_, f);
}

void type_add_method(type* self, method * m) {
	if (self->tag == type_class) {
		class_add_method(self->u.class_, m);
	} else if (self->tag == type_interface) {
		interface_add_method(self->u.interface_, m);
	}
}

method * type_find_method(type * self, const char * name, vector * args, enviroment * env, int * outIndex) {
	assert(self != NULL);
	if (self->tag == type_class) {
		return class_find_method(self->u.class_, name, args, env, outIndex);
	} else if (self->tag == type_interface) {
		return interface_find_method(self->u.interface_, name, args, env, outIndex);
	}
	return NULL;
}

method* type_find_smethod(type* self, const char* name, vector* args, struct enviroment* env, int* outIndex) {
	assert(self->tag == type_class);
	return class_find_smethod(self->u.class_, name, args, env, outIndex);
}

vtable * type_vtable(type * self) {
	if (self->tag == type_class) {
		class_create_vtable(self->u.class_);
		return self->u.class_->vt;
	} else if (self->tag == type_interface) {
		return self->u.interface_->vt;
	}
	return NULL;
}

void type_dump(type * self, int depth) {
	if (self->tag == type_class) {
		class_dump(self->u.class_, depth);
	} else if (self->tag == type_interface) {
		interface_dump(self->u.interface_, depth);
	}
}

int type_distance(type * super, type * sub) {
	if (super == sub) {
		return 0;
	}
	if (super->tag == type_class &&
		sub->tag == type_class) {
		int dist = class_distance(super->u.class_, sub->u.class_);
		return dist;
	}
	return -1;
}

void type_unlink(type * self) {
	if (self->tag == type_class) {
		class_unlink(self->u.class_);
	} else if (self->tag == type_interface) {
		interface_unlink(self->u.interface_);
	}
}

int type_for_generic_index(type * self, char * name) {
	assert(self->tag != type_enum);
	vector* v = NULL;
	XSTREQ(name, "A");
	if (self->tag == type_class) v = self->u.class_->type_parameter_list;
	if (self->tag == type_interface) v = self->u.interface_->type_parameter_list;
	//全ての型変数と比べる
	int ret = -1;
	for (int i = 0; i < v->length; i++) {
		type_parameter* e = (type_parameter*)vector_at(v, i);
		if (!strcmp(e->name, name)) {
			ret = i;
			break;
		}
	}
	if (ret == -1) {
		int a = 0;
	}
	return ret;
}

generic_type * type_find_impl(type * self, type * a) {
	//selfがクラスなら
	if (self->tag == type_class) {

		class_* ptr = self->u.class_;
		while (ptr != NULL) {
			if (a->tag == type_class &&
				ptr == a->u.class_) {
				return generic_type_ref(ptr->parent);
			}
			if (a->tag == type_interface) {
				for (int i = 0; i < ptr->impl_list->length; i++) {
					generic_type* inter = (generic_type*)vector_at(ptr->impl_list, i);
					if (inter->core_type == a) {
						return inter;
					}
				}
			}
			ptr = ptr->super_class->core_type->u.class_;
		}
	} else if (self->tag == type_interface) {
		interface_* inter = self->u.interface_;
		for (int i = 0; i < inter->impl_list->length; i++) {
			generic_type* e = (generic_type*)vector_at(inter->impl_list, i);
			if (e->core_type == a) {
				return e;
			}
		}
	}
	return NULL;
}

vector* type_parameter_list(type* self) {
	assert(self != NULL);
	if(self->tag == type_class) {
		return self->u.class_->type_parameter_list;
	} else if(self->tag == type_interface) {
		return self->u.interface_->type_parameter_list;
	}
}

generic_type * type_type_parameter_at(type * self, int index) {
	assert(self->tag != type_enum);
	if (self->tag == type_class) {
		return (generic_type*)vector_at(self->u.class_, index);
	} else if (self->tag == type_interface) {
		return (generic_type*)vector_at(self->u.interface_, index);
	}
	return NULL;
}

int type_type_parameter_len(type* self) {
	int res = -1;
	if(self->tag == type_class) {
		res = self->u.class_->type_parameter_list->length;
	} else if(self->tag == type_interface) {
		res = self->u.interface_->type_parameter_list->length;
	}
	assert(res < 2);
	return res;
}

void type_delete(type * self) {
	if (self->tag == type_class) {
		class_delete(self->u.class_);
	} else if (self->tag == type_interface) {
		interface_delete(self->u.interface_);
	}
//	generic_type_delete(self->generic_self);
	generic_type_lostownership(self->generic_self);
	MEM_FREE(self);
}

class_* type_cast_class(type* self) {
	assert(self->tag == type_class);
	return self->u.class_;
}

interface_* type_cast_interface(type* self) {
	assert(self->tag == type_interface);
	return self->u.interface_;
}

generic_type* type_baseline(type* abstract, type* concrete) {
	type* ptr = concrete;
	do {
		class_* cls = TYPE2CLASS(ptr);
		if(cls->super_class != NULL &&
		   cls->super_class->core_type == abstract) {
			return cls->super_class;
		}
		if(abstract->tag == type_interface) {
			for(int i=0; i<cls->impl_list->length; i++) {
				generic_type* gE = (generic_type*)vector_at(cls->impl_list, i);
				generic_type* impl = interface_contains(gE, abstract->u.interface_);
				if(impl) {
					return impl;
				}
			}
		}
		//次へ
		if(cls->super_class == NULL) {
			ptr = NULL;
		} else {
			ptr = cls->super_class->core_type;
		}
	} while(ptr != NULL);
	return NULL;
}