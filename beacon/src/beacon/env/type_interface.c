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

type * NewType() {
	type* ret = (type*)MEM_MALLOC(sizeof(type));
	ret->tag = TYPE_CLASS_T;
	ret->location = NULL;
	ret->absolute_index = -1;
	ret->generic_self = NULL;
	ret->state = TYPE_NONE;
	return ret;
}

generic_type* InitGenericSelf(type* self, int counts) {
	if (self == NULL) {
		return NULL;
	}
	if (self->generic_self == NULL) {
		self->generic_self = generic_NewType(self);
		for (int i = 0; i < counts; i++) {
			generic_type* arg = generic_NewType(NULL);
			arg->tag = GENERIC_TYPE_TAG_CLASS_T;
			arg->virtual_type_index = i;
			arg->u.type_ = self;
			AddArgsGenericType(self->generic_self, arg);
		}
	}
	return self->generic_self;
}

string_view GetTypeName(type * self) {
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

string_view GetTypeFullName(type* self) {
	if(self == NULL) {
		return InternString("NULL");
	}
	string_view namespace_str = NamespaceToString(self->location);
	string_view self_str = GetTypeName(self);
	return ConcatIntern(
		Ref2Str(namespace_str),
		ConcatIntern(".", self_str)
	);
}

void AddFieldType(type* self, field * f) {
	assert(self->tag == TYPE_CLASS_T);
	AddFieldClass(self->u.class_, f);
}

void AddPropertyType(type* self, property* p) {
	if(self->tag == TYPE_CLASS_T) {
		AddPropertyClass(self->u.class_, p);
	} else if(self->tag == TYPE_INTERFACE_T) {
		AddPropertyInterface(self->u.interface_, p);
	}
}

void AddMethodType(type* self, method * m) {
	if (self->tag == TYPE_CLASS_T) {
		AddMethodClass(self->u.class_, m);
	} else if (self->tag == TYPE_INTERFACE_T) {
		AddMethodInterface(self->u.interface_, m);
	}
}

method * ILFindMethodType(type * self, string_view namev, Vector * args, enviroment * env, call_context* cctx, int * outIndex) {
	assert(self != NULL);
	if (self->tag == TYPE_CLASS_T) {
		return ILFindMethodClass(self->u.class_, namev, args, env, cctx, outIndex);
	} else if (self->tag == TYPE_INTERFACE_T) {
		return ILFindMethodInterface(self->u.interface_, namev, args, env, cctx, outIndex);
	}
	return NULL;
}

method* ILFindSMethodType(type* self, string_view namev, Vector* args, struct enviroment* env, call_context* cctx, int* outIndex) {
	assert(self->tag == TYPE_CLASS_T);
	return ILFindSMethodClass(self->u.class_, namev, args, env, cctx, outIndex);
}

vtable * GetVTableType(type * self) {
	if (self->tag == TYPE_CLASS_T) {
		CreateVTableClass(self->u.class_);
		return self->u.class_->vt;
	} else if (self->tag == TYPE_INTERFACE_T) {
		return self->u.interface_->vt;
	}
	return NULL;
}

int DistanceType(type * super, type * sub) {
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
		Vector* gimpl_list = GetGenericInterfaceListClass(TYPE2CLASS(sub));
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
		int dist = DistanceClass(super->u.class_, sub->u.class_);
		return dist;
	}
	return -1;
}

void UnlinkType(type * self) {
	if (self->tag == TYPE_CLASS_T) {
		UnlinkClass(self->u.class_);
	} else if (self->tag == TYPE_INTERFACE_T) {
		UnlinkInterface(self->u.interface_);
	}
}

int GetGenericIndexType(type * self, string_view namev) {
	assert(self->tag != TYPE_ENUM_T);
	Vector* v = NULL;
	if (self->tag == TYPE_CLASS_T) v = self->u.class_->GetParameterListType;
	if (self->tag == TYPE_INTERFACE_T) v = self->u.interface_->GetParameterListType;
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

generic_type * FindImplementType(type * self, type * a) {
	//selfがクラスなら
	if (self->tag == TYPE_CLASS_T) {

		class_* ptr = self->u.class_;
		while (ptr != NULL) {
			if (a->tag == TYPE_CLASS_T &&
				ptr == a->u.class_) {
				return RefGenericType(ptr->parent);
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

Vector* GetParameterListType(type* self) {
	assert(self != NULL);
	if(self->tag == TYPE_CLASS_T) {
		return self->u.class_->GetParameterListType;
	} else if(self->tag == TYPE_INTERFACE_T) {
		return self->u.interface_->GetParameterListType;
	}
}

Vector* GetImplementList(type* self) {
	assert(self != NULL);
	if(self->tag == TYPE_CLASS_T) {
		return self->u.class_->impl_list;
	} else if(self->tag == TYPE_INTERFACE_T) {
		return self->u.interface_->impl_list;
	}
}

generic_type * TypeParameterAtType(type * self, int index) {
	assert(self->tag != TYPE_ENUM_T);
	if (self->tag == TYPE_CLASS_T) {
		return (generic_type*)AtVector(self->u.class_->GetParameterListType, index);
	} else if (self->tag == TYPE_INTERFACE_T) {
		return (generic_type*)AtVector(self->u.interface_->GetParameterListType, index);
	}
	return NULL;
}

void DeleteType(type * self) {
	if (self->tag == TYPE_CLASS_T) {
		DeleteClass(self->u.class_);
	} else if (self->tag == TYPE_INTERFACE_T) {
		DeleteInterface(self->u.interface_);
	}
	LostownershipGenericType(self->generic_self);
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

generic_type* BaselineType(type* abstract, type* concrete) {
	if(abstract == concrete) {
		return abstract->generic_self;
	}
	#if defined(DEBUG)
	const char* abstractname = Ref2Str(GetTypeName(abstract));
	const char* concretename = Ref2Str(GetTypeName(concrete));
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
				generic_type* impl = IsContainsTypeInterface(gE, abstract->u.interface_);
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

interface_* IsValidInterface(type* self) {
#if defined(_MSC_VER)
	//コンパイラが初期化されていないローカル変数として認識してしまうのでその対策
	Vector* impl_list = NULL;
	impl_list = GetImplementList(self);
#else
	Vector* impl_list = GetImplementList(self);
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

bool IsAbstractType(type* self) {
	if(self->tag == TYPE_CLASS_T) {
		return TYPE2CLASS(self)->is_abstract;
	}
	return self->tag == TYPE_INTERFACE_T;
}

class_* TypeToClass(type* self) {
	if(self == NULL || self->tag != TYPE_CLASS_T) {
		return NULL;
	}
	return self->u.class_;
}

interface_* TypeToInterface(type* self) {
	if(self == NULL || self->tag != TYPE_INTERFACE_T) {
		return NULL;
	}
	return self->u.interface_;
}