#include "type_interface.h"
#include "../util/mem.h"
#include "object.h"
#include "TYPE_IMPL.h"
#include "field.h"
#include "method.h"
#include "property.h"
#include "type_parameter.h"
#include "generic_type.h"
#include "../util/text.h"
#include <assert.h>
#include <string.h>

Type* NewType() {
	Type* ret = (Type*)MEM_MALLOC(sizeof(Type));
	ret->AllocSize = sizeof(Object);
	ret->Tag = TYPE_CLASS_T;
	ret->Location = NULL;
	ret->AbsoluteIndex = -1;
	ret->GenericSelf = NULL;
	ret->State = TYPE_NONE;
	return ret;
}

GenericType* InitGenericSelf(Type* self, int counts) {
	if (self == NULL) {
		return NULL;
	}
	if (self->GenericSelf == NULL) {
		self->GenericSelf = NewGenericType(self);
		for (int i = 0; i < counts; i++) {
			GenericType* arg = NewGenericType(NULL);
			arg->Tag = GENERIC_TYPE_TAG_CLASS_T;
			arg->VirtualTypeIndex = i;
			arg->Kind.Type = self;
			AddArgsGenericType(self->GenericSelf, arg);
		}
	}
	return self->GenericSelf;
}

StringView GetTypeName(Type* self) {
	if(self == NULL) {
		return InternString("NULL");
	}
	if (self->Tag == TYPE_CLASS_T) {
		return self->Kind.Class->Name;
	} else if (self->Tag == TYPE_INTERFACE_T) {
		return self->Kind.Interface->Name;
	}
	return 0;
}

StringView GetTypeFullName(Type* self) {
	if(self == NULL) {
		return InternString("NULL");
	}
	StringView Namespacestr = NamespaceToString(self->Location);
	StringView self_str = GetTypeName(self);
	return ConcatIntern(
		Ref2Str(Namespacestr),
		ConcatIntern(".", self_str)
	);
}

void AddFieldType(Type* self, Field* f) {
	assert(self->Tag == TYPE_CLASS_T);
	AddFieldClass(self->Kind.Class, f);
}

void AddPropertyType(Type* self, Property* p) {
	if(self->Tag == TYPE_CLASS_T) {
		AddPropertyClass(self->Kind.Class, p);
	} else if(self->Tag == TYPE_INTERFACE_T) {
		AddPropertyInterface(self->Kind.Interface, p);
	}
}

void AddMethodType(Type* self, Method * m) {
	if (self->Tag == TYPE_CLASS_T) {
		AddMethodClass(self->Kind.Class, m);
	} else if (self->Tag == TYPE_INTERFACE_T) {
		AddMethodInterface(self->Kind.Interface, m);
	}
}

Method * ILFindMethodType(Type* self, StringView namev, Vector * args, Enviroment * env, CallContext* cctx, int * outIndex) {
	assert(self != NULL);
	if (self->Tag == TYPE_CLASS_T) {
		return ILFindMethodClass(self->Kind.Class, namev, args, env, cctx, outIndex);
	} else if (self->Tag == TYPE_INTERFACE_T) {
		return ILFindMethodInterface(self->Kind.Interface, namev, args, env, cctx, outIndex);
	}
	return NULL;
}

Method* ILFindSMethodType(Type* self, StringView namev, Vector* args, Enviroment* env, CallContext* cctx, int* outIndex) {
	assert(self->Tag == TYPE_CLASS_T);
	return ILFindSMethodClass(self->Kind.Class, namev, args, env, cctx, outIndex);
}

VTable * GetVTableType(Type* self) {
	if (self->Tag == TYPE_CLASS_T) {
		CreateVTableClass(self->Kind.Class);
		return self->Kind.Class->VT;
	} else if (self->Tag == TYPE_INTERFACE_T) {
		return self->Kind.Interface->VT;
	}
	return NULL;
}

int DistanceType(Type* super, Type* sub) {
	if (super == sub) {
		return 0;
	}
	//nullはあらゆる型のサブクラス
	if(sub == TYPE_NULL) {
		return 1;
	}
	if (super->Tag == TYPE_INTERFACE_T &&
		sub->Tag == TYPE_CLASS_T) {
		bool found = false;
		Vector* gimpl_list = GetGenericInterfaceListClass(TYPE2CLASS(sub));
		for (int i = 0; i < gimpl_list->Length; i++) {
			GenericType* e = (GenericType*)AtVector(gimpl_list, i);
			if (e->CoreType == super) {
				found = true;
				break;
			}
		}
		DeleteVector(gimpl_list, VectorDeleterOfNull);
		return found ? 0 : -1;
	}
	if (super->Tag == TYPE_CLASS_T &&
		sub->Tag == TYPE_CLASS_T) {
		int dist = DistanceClass(super->Kind.Class, sub->Kind.Class);
		return dist;
	}
	return -1;
}

void UnlinkType(Type* self) {
	if (self->Tag == TYPE_CLASS_T) {
		UnlinkClass(self->Kind.Class);
	} else if (self->Tag == TYPE_INTERFACE_T) {
		UnlinkInterface(self->Kind.Interface);
	}
}

int GetGenericIndexType(Type* self, StringView namev) {
	assert(self->Tag != TYPE_ENUM_T);
	Vector* v = NULL;
	if (self->Tag == TYPE_CLASS_T) v = self->Kind.Class->TypeParameters;
	if (self->Tag == TYPE_INTERFACE_T) v = self->Kind.Interface->TypeParameters;
	//全ての型変数と比べる
	int ret = -1;
	for (int i = 0; i < v->Length; i++) {
		TypeParameter* e = (TypeParameter*)AtVector(v, i);
		if (e->Name == namev) {
			ret = i;
			break;
		}
	}
	if (ret == -1) {
		int a = 0;
	}
	return ret;
}

GenericType * FindImplementType(Type* self, Type* a) {
	//selfがクラスなら
	if (self->Tag == TYPE_CLASS_T) {

		Class* ptr = self->Kind.Class;
		while (ptr != NULL) {
			if (a->Tag == TYPE_CLASS_T &&
				ptr == a->Kind.Class) {
				return RefGenericType(ptr->Parent);
			}
			if (a->Tag == TYPE_INTERFACE_T) {
				for (int i = 0; i < ptr->Implements->Length; i++) {
					GenericType* inter = (GenericType*)AtVector(ptr->Implements, i);
					if (inter->CoreType == a) {
						return inter;
					}
				}
			}
			ptr = ptr->SuperClass->CoreType->Kind.Class;
		}
	} else if (self->Tag == TYPE_INTERFACE_T) {
		Interface* inter = self->Kind.Interface;
		for (int i = 0; i < inter->Implements->Length; i++) {
			GenericType* e = (GenericType*)AtVector(inter->Implements, i);
			if (e->CoreType == a) {
				return e;
			}
		}
	}
	return NULL;
}

Vector* GetParameterListType(Type* self) {
	assert(self != NULL);
	if(self->Tag == TYPE_CLASS_T) {
		return self->Kind.Class->TypeParameters;
	} else if(self->Tag == TYPE_INTERFACE_T) {
		return self->Kind.Interface->TypeParameters;
	}
}

Vector* GetImplementList(Type* self) {
	assert(self != NULL);
	if(self->Tag == TYPE_CLASS_T) {
		return self->Kind.Class->Implements;
	} else if(self->Tag == TYPE_INTERFACE_T) {
		return self->Kind.Interface->Implements;
	}
}

GenericType * TypeParameterAtType(Type* self, int index) {
	assert(self->Tag != TYPE_ENUM_T);
	if (self->Tag == TYPE_CLASS_T) {
		return (GenericType*)AtVector(self->Kind.Class->TypeParameters, index);
	} else if (self->Tag == TYPE_INTERFACE_T) {
		return (GenericType*)AtVector(self->Kind.Interface->TypeParameters, index);
	}
	return NULL;
}

void DeleteType(Type* self) {
	if (self->Tag == TYPE_CLASS_T) {
		DeleteClass(self->Kind.Class);
	} else if (self->Tag == TYPE_INTERFACE_T) {
		DeleteInterface(self->Kind.Interface);
	}
	LostownershipGenericType(self->GenericSelf);
	MEM_FREE(self);
}

Class* CastClassType(Type* self) {
	assert(self->Tag == TYPE_CLASS_T);
	return self->Kind.Class;
}

Interface* CastInterfaceType(Type* self) {
	assert(self->Tag == TYPE_INTERFACE_T);
	return self->Kind.Interface;
}

GenericType* BaselineType(Type* abstract, Type* concrete) {
	if(abstract == concrete) {
		return abstract->GenericSelf;
	}
	#if defined(DEBUG)
	const char* abstractname = Ref2Str(GetTypeName(abstract));
	const char* concretename = Ref2Str(GetTypeName(concrete));
	#endif
	Type* ptr = concrete;
	do {
		Class* cls = TYPE2CLASS(ptr);
		if(cls->SuperClass != NULL &&
		   cls->SuperClass->CoreType == abstract) {
			return cls->SuperClass;
		}
		if(abstract->Tag == TYPE_INTERFACE_T) {
			for(int i=0; i<cls->Implements->Length; i++) {
				GenericType* gE = (GenericType*)AtVector(cls->Implements, i);
				GenericType* impl = IsContainsTypeInterface(gE, abstract->Kind.Interface);
				if(impl) {
					return impl;
				}
			}
		}
		//次へ
		if(cls->SuperClass == NULL) {
			ptr = NULL;
		} else {
			ptr = cls->SuperClass->CoreType;
		}
	} while(ptr != NULL);
	return NULL;
}

Interface* IsValidInterface(Type* self) {
#if defined(_MSC_VER)
	//コンパイラが初期化されていないローカル変数として認識してしまうのでその対策
	Vector* impl_list = NULL;
	impl_list = GetImplementList(self);
#else
	Vector* impl_list = GetImplementList(self);
#endif
	for(int i=0; i<impl_list->Length; i++) {
		GenericType* gE = AtVector(impl_list, i);
		Interface* iE = TYPE2INTERFACE(GENERIC2TYPE(gE));
		for(int j=0; j<impl_list->Length; j++) {
			if(i == j) { continue; }
			GenericType* gE2 = AtVector(impl_list, j);
			Interface* iE2 = TYPE2INTERFACE(GENERIC2TYPE(gE2));
			if(iE == iE2) {
				return iE2;
			}
		}
	}
	return NULL;
}

bool IsAbstractType(Type* self) {
	if(self->Tag == TYPE_CLASS_T) {
		return TYPE2CLASS(self)->IsAbstract;
	}
	return self->Tag == TYPE_INTERFACE_T;
}

Class* TypeToClass(Type* self) {
	if(self == NULL || self->Tag != TYPE_CLASS_T) {
		return NULL;
	}
	return self->Kind.Class;
}

Interface* TypeToInterface(Type* self) {
	if(self == NULL || self->Tag != TYPE_INTERFACE_T) {
		return NULL;
	}
	return self->Kind.Interface;
}