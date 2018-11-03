#include "interface_impl.h"
//#include "../type_interface.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/method.h"
#include "../../env/generic_type.h"
#include "../../env/property.h"
#include "../../env/parameter.h"
#include "meta_impl.h"
#include "../generic_type.h"
#include "../type_parameter.h"
#include <stdio.h>
//proto
Vector* get_generic_interface_tree_impl(Interface* self);
static void delete_method(VectorItem item);
static void delete_type_parameter(VectorItem item);
static void delete_generic_type(VectorItem item);
static void flatten_method_impl(Interface* self, Vector* dest, int depth);
static void delete_property(VectorItem item);

Type* WrapInterface(Interface* self) {
	Type* ret = NewType();
	ret->Tag = TYPE_INTERFACE_T;
	ret->Kind.Interface = self;
	self->Parent = ret;
	return ret;
}

Interface* NewInterface(StringView namev) {
	Interface* ret = (Interface*)MEM_MALLOC(sizeof(Interface));
	ret->Name = namev;
	ret->Implements = NewVector();
	ret->Location = NULL;
	ret->Methods = NewVector();
	ret->Properties = NewVector();
	ret->VT = NULL;
	ret->TypeParameters = NewVector();
	ret->Parent = NULL;
	return ret;
}

void AddMethodInterface(Interface* self, Method * m) {
	PushVector(self->Methods, m);
}

void AddPropertyInterface(Interface* self, Property* p) {
	PushVector(self->Properties, p);
}

Method * ILFindMethodInterface(Interface* self, StringView namev, Vector * args, Enviroment * env, CallContext* cctx, int * outIndex) {
	return MetaILFindMethod(self->Methods, namev, args, env,cctx, outIndex);
}

Method* GFindMethodInterface(Interface* self, StringView namev, Vector* gargs, int* outIndex) {
	return MetaGFindMethod(self->Methods, namev, gargs, outIndex);
}

Vector* FlattenMethodInterfaceList(Vector* inter_list) {
	Vector* ret = NewVector();
	for(int i=0; i<inter_list->Length; i++) {
		Interface* inter = AtVector(inter_list, i);
		//インターフェイスのメソッド一覧を挿入
		Vector* list = FlattenMethodInterface(inter);
		for(int j=0; j<list->Length; j++) {
			PushVector(ret, AtVector(list, j));
		}
		DeleteVector(list, VectorDeleterOfNull);
	}
	return ret;
}

Vector* FlattenMethodInterface(Interface* self) {
	Vector* ret = NewVector();
	flatten_method_impl(self, ret, 0);
	return ret;
}

void CreateVTableInterface(Interface* self) {
	//初期化済み
	if (self->VT != NULL) {
		return;
	}
	self->VT = NewVTable();
	//他のインターフェイスを継承していないならフラットに並べる
	if (self->Implements->Length == 0) {
		for (int i = 0; i < self->Methods->Length; i++) {
			AddVTable(self->VT, AtVector(self->Methods, i));
		}
	} else {
		for (int i = 0; i < self->Implements->Length; i++) {
			GenericType* ginter = (GenericType*)AtVector(self->Implements, i);
			Type* cinter = GENERIC2TYPE(ginter);
			Interface* inter = TYPE2INTERFACE(cinter);
//			Interface* inter = (Interface*)AtVector(self->Implements, i);
			CreateVTableInterface(inter);
			CopyVTable(inter->VT, self->VT);
		}
		for (int i = 0; i < self->Methods->Length; i++) {
			AddVTable(self->VT, AtVector(self->Methods, i));
		}
	}
}

void UnlinkInterface(Interface* self) {
	DeleteVector(self->Methods, delete_method);
	DeleteVector(self->Properties, delete_property);
	DeleteVector(self->Implements, VectorDeleterOfNull);
	DeleteVTable(self->VT);
}

void DeleteInterface(Interface* self) {
	DeleteVector(self->TypeParameters, delete_type_parameter);
	MEM_FREE(self);
}

GenericType* IsContainsTypeInterface(GenericType* source, Interface* find) {
	Interface* self = source->CoreType->Kind.Interface;
	if(self == find) {
		return source;
	}
	for(int i=0; i<self->Implements->Length; i++) {
		GenericType* gE = AtVector(self->Implements, i);
		if(gE->CoreType->Kind.Interface == find) {
			return gE;
		}
	}
	return NULL;
}

bool IsFunctionalInterface(Interface* self) {
	return GetFunctionInterface(self) != NULL;
}

Method* GetFunctionInterface(Interface* self) {
	Vector* v = FlattenMethodInterface(self);
	Method* ret = NULL;
	if(v->Length == 1) {
		ret = AtVector(v, 0);
	}
	DeleteVector(v, VectorDeleterOfNull);
	return ret;
}


Vector* GetGenericInterfaceTreeInterface(Interface* self) {
	return get_generic_interface_tree_impl(self);
}

GenericType* FindInterfaceInterface(Interface* self, Type* tinter) {
	assert(tinter->Tag == TYPE_INTERFACE_T);
	if (self == TYPE2INTERFACE(tinter)) {
		return NULL;
	}
	for (int i = 0; i < self->Implements->Length; i++) {
		GenericType* e = AtVector(self->Implements, i);
		if (e->CoreType == tinter) {
			return e;
		}
	}
	return NULL;
}

//private
Vector* get_generic_interface_tree_impl(Interface* self) {
	Vector* ret = NewVector();
	for(int i=0; i<self->Implements->Length; i++) {
		GenericType* ginter = AtVector(self->Implements, i);
		PushVector(ret, ginter);
		Vector* inner = get_generic_interface_tree_impl(TYPE2INTERFACE(GENERIC2TYPE(ginter)));
		MergeVector(ret, inner);
		DeleteVector(inner, VectorDeleterOfNull);
	}
	return ret;
}
static void delete_method(VectorItem item) {
	Method* e = (Method*)item;
	DeleteMethod(e);
}

static void delete_type_parameter(VectorItem item) {
	TypeParameter* e = (TypeParameter*)item;
	DeleteTypeParameter(e);
}

static void delete_generic_type(VectorItem item) {
	//GenericType* e = (GenericType*)item;
	//generic_DeleteType(e);
}

static void flatten_method_impl(Interface* self, Vector* dest, int depth) {
	//tekitou
	#if defined(DEBUG)
	const char* intername = Ref2Str(self->Name);
	#endif
	assert(depth < 42);
	for(int i=0; i<self->Methods->Length; i++) {
		Method* m = AtVector(self->Methods, i);
		PushVector(dest, m);
	}
	for(int i=0; i<self->Implements->Length; i++) {
		GenericType* e = AtVector(self->Implements, i);
		Interface* inter = TYPE2INTERFACE(e->CoreType);
		flatten_method_impl(inter, dest, depth + 1);
	}
}

static void delete_property(VectorItem item) {
	Property* e = (Property*)item;
	DeleteProperty(e);
}