#include "type_interface.h"
#include "../util/mem.h"
#include "TYPE_IMPL.h"
#include "field.h"
#include "method.h"
#include "property.h"
#include "type_parameter.h"
#include "generic_type.h"
#include "../util/text.h"
#include <assert.h>
#include <string.h>

type * type_new() {
	type* ret = (type*)MEM_MALLOC(sizeof(type));
	ret->tag = TYPE_CLASS_T;
	ret->location = NULL;
	ret->absolute_index = -1;
	ret->generic_self = NULL;
	ret->state = TYPE_NONE;
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
			arg->tag = GENERIC_TYPE_TAG_CLASS_T;
			arg->virtual_type_index = i;
			arg->u.type_ = self;
			generic_type_addargs(self->generic_self, arg);
		}
	}
	return self->generic_self;
}

string_view type_name(type * self) {
	if(self == NULL) {
		return InternString("NULL");
	}
	if (self->tag == TYPE_CLASS_T) {
		return self->u.class_->namev;
	} else if (self->tag == TYPE_INTERFACE_T) {
		return self->u.interface_->namev;
	}
	return 0;
}

string_view type_full_name(type* self) {
	if(self == NULL) {
		return InternString("NULL");
	}
	string_view namespace_str = NamespaceToString(self->location);
	string_view self_str = type_name(self);
	return ConcatIntern(
		Ref2Str(namespace_str),
		ConcatIntern(".", self_str)
	);
}

void type_add_field(type* self, field * f) {
	assert(self->tag == TYPE_CLASS_T);
	class_add_field(self->u.class_, f);
}

void type_add_property(type* self, property* p) {
	if(self->tag == TYPE_CLASS_T) {
		class_add_property(self->u.class_, p);
	} else if(self->tag == TYPE_INTERFACE_T) {
		interface_add_property(self->u.interface_, p);
	}
}

void type_add_method(type* self, method * m) {
	if (self->tag == TYPE_CLASS_T) {
		class_add_method(self->u.class_, m);
	} else if (self->tag == TYPE_INTERFACE_T) {
		interface_add_method(self->u.interface_, m);
	}
}

method * type_ilfind_method(type * self, string_view namev, Vector * args, enviroment * env, call_context* cctx, int * outIndex) {
	assert(self != NULL);
	if (self->tag == TYPE_CLASS_T) {
		return class_ilfind_method(self->u.class_, namev, args, env, cctx, outIndex);
	} else if (self->tag == TYPE_INTERFACE_T) {
		return interface_ilfind_method(self->u.interface_, namev, args, env, cctx, outIndex);
	}
	return NULL;
}

method* type_ilfind_smethod(type* self, string_view namev, Vector* args, struct enviroment* env, call_context* cctx, int* outIndex) {
	assert(self->tag == TYPE_CLASS_T);
	return class_ilfind_smethod(self->u.class_, namev, args, env, cctx, outIndex);
}

vtable * type_vtable(type * self) {
	if (self->tag == TYPE_CLASS_T) {
		class_create_vtable(self->u.class_);
		return self->u.class_->vt;
	} else if (self->tag == TYPE_INTERFACE_T) {
		return self->u.interface_->vt;
	}
	return NULL;
}

int type_distance(type * super, type * sub) {
	if (super == sub) {
		return 0;
	}
	//nullはあらゆる型のサブクラス
	if(sub == TYPE_NULL) {
		return 1;
	}
	if (super->tag == TYPE_INTERFACE_T &&
		sub->tag == TYPE_CLASS_T) {
		bool found = false;
		Vector* gimpl_list = class_get_generic_interface_list(TYPE2CLASS(sub));
		for (int i = 0; i < gimpl_list->length; i++) {
			generic_type* e = (generic_type*)AtVector(gimpl_list, i);
			if (e->core_type == super) {
				found = true;
				break;
			}
		}
		DeleteVector(gimpl_list, VectorDeleterOfNull);
		return found ? 0 : -1;
	}
	if (super->tag == TYPE_CLASS_T &&
		sub->tag == TYPE_CLASS_T) {
		int dist = class_distance(super->u.class_, sub->u.class_);
		return dist;
	}
	return -1;
}

void type_unlink(type * self) {
	if (self->tag == TYPE_CLASS_T) {
		class_unlink(self->u.class_);
	} else if (self->tag == TYPE_INTERFACE_T) {
		interface_unlink(self->u.interface_);
	}
}

int type_for_generic_index(type * self, string_view namev) {
	assert(self->tag != TYPE_ENUM_T);
	Vector* v = NULL;
	if (self->tag == TYPE_CLASS_T) v = self->u.class_->type_parameter_list;
	if (self->tag == TYPE_INTERFACE_T) v = self->u.interface_->type_parameter_list;
	//全ての型変数と比べる
	int ret = -1;
	for (int i = 0; i < v->length; i++) {
		type_parameter* e = (type_parameter*)AtVector(v, i);
		if (e->namev == namev) {
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
	if (self->tag == TYPE_CLASS_T) {

		class_* ptr = self->u.class_;
		while (ptr != NULL) {
			if (a->tag == TYPE_CLASS_T &&
				ptr == a->u.class_) {
				return generic_type_ref(ptr->parent);
			}
			if (a->tag == TYPE_INTERFACE_T) {
				for (int i = 0; i < ptr->impl_list->length; i++) {
					generic_type* inter = (generic_type*)AtVector(ptr->impl_list, i);
					if (inter->core_type == a) {
						return inter;
					}
				}
			}
			ptr = ptr->super_class->core_type->u.class_;
		}
	} else if (self->tag == TYPE_INTERFACE_T) {
		interface_* inter = self->u.interface_;
		for (int i = 0; i < inter->impl_list->length; i++) {
			generic_type* e = (generic_type*)AtVector(inter->impl_list, i);
			if (e->core_type == a) {
				return e;
			}
		}
	}
	return NULL;
}

Vector* type_parameter_list(type* self) {
	assert(self != NULL);
	if(self->tag == TYPE_CLASS_T) {
		return self->u.class_->type_parameter_list;
	} else if(self->tag == TYPE_INTERFACE_T) {
		return self->u.interface_->type_parameter_list;
	}
}

Vector* TYPE_IMPLement_list(type* self) {
	assert(self != NULL);
	if(self->tag == TYPE_CLASS_T) {
		return self->u.class_->impl_list;
	} else if(self->tag == TYPE_INTERFACE_T) {
		return self->u.interface_->impl_list;
	}
}

generic_type * type_type_parameter_at(type * self, int index) {
	assert(self->tag != TYPE_ENUM_T);
	if (self->tag == TYPE_CLASS_T) {
		return (generic_type*)AtVector(self->u.class_->type_parameter_list, index);
	} else if (self->tag == TYPE_INTERFACE_T) {
		return (generic_type*)AtVector(self->u.interface_->type_parameter_list, index);
	}
	return NULL;
}

void type_delete(type * self) {
	if (self->tag == TYPE_CLASS_T) {
		class_delete(self->u.class_);
	} else if (self->tag == TYPE_INTERFACE_T) {
		interface_delete(self->u.interface_);
	}
	generic_type_lostownership(self->generic_self);
	MEM_FREE(self);
}

class_* CastClassType(type* self) {
	assert(self->tag == TYPE_CLASS_T);
	return self->u.class_;
}

interface_* CastInterfaceType(type* self) {
	assert(self->tag == TYPE_INTERFACE_T);
	return self->u.interface_;
}

generic_type* type_baseline(type* abstract, type* concrete) {
	if(abstract == concrete) {
		return abstract->generic_self;
	}
	#if defined(DEBUG)
	const char* abstractname = Ref2Str(type_name(abstract));
	const char* concretename = Ref2Str(type_name(concrete));
	#endif
	type* ptr = concrete;
	do {
		class_* cls = TYPE2CLASS(ptr);
		if(cls->super_class != NULL &&
		   cls->super_class->core_type == abstract) {
			return cls->super_class;
		}
		if(abstract->tag == TYPE_INTERFACE_T) {
			for(int i=0; i<cls->impl_list->length; i++) {
				generic_type* gE = (generic_type*)AtVector(cls->impl_list, i);
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

interface_* type_interface_valid(type* self) {
#if defined(_MSC_VER)
	//コンパイラが初期化されていないローカル変数として認識してしまうのでその対策
	Vector* impl_list = NULL;
	impl_list = TYPE_IMPLement_list(self);
#else
	Vector* impl_list = TYPE_IMPLement_list(self);
#endif
	for(int i=0; i<impl_list->length; i++) {
		generic_type* gE = AtVector(impl_list, i);
		interface_* iE = TYPE2INTERFACE(GENERIC2TYPE(gE));
		for(int j=0; j<impl_list->length; j++) {
			if(i == j) { continue; }
			generic_type* gE2 = AtVector(impl_list, j);
			interface_* iE2 = TYPE2INTERFACE(GENERIC2TYPE(gE2));
			if(iE == iE2) {
				return iE2;
			}
		}
	}
	return NULL;
}

bool type_is_abstract(type* self) {
	if(self->tag == TYPE_CLASS_T) {
		return TYPE2CLASS(self)->is_abstract;
	}
	return self->tag == TYPE_INTERFACE_T;
}

class_* type_as_class(type* self) {
	if(self == NULL || self->tag != TYPE_CLASS_T) {
		return NULL;
	}
	return self->u.class_;
}

interface_* type_as_interface(type* self) {
	if(self == NULL || self->tag != TYPE_INTERFACE_T) {
		return NULL;
	}
	return self->u.interface_;
}