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
Vector* get_generic_interface_tree_impl(bc_Interface* self);
static void delete_method(VectorItem item);
static void delete_type_parameter(VectorItem item);
static void delete_generic_type(VectorItem item);
static void flatten_method_impl(bc_Interface* self, Vector* dest, int depth);
static void delete_property(VectorItem item);

bc_Type* bc_WrapInterface(bc_Interface* self) {
	bc_Type* ret = bc_NewType();
	ret->Tag = TYPE_INTERFACE_T;
	ret->Kind.Interface = self;
	self->Parent = ret;
	return ret;
}

bc_Interface* bc_NewInterface(StringView namev) {
	bc_Interface* ret = (bc_Interface*)MEM_MALLOC(sizeof(bc_Interface));
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

void bc_AddMethodInterface(bc_Interface* self, bc_Method * m) {
	PushVector(self->Methods, m);
}

void bc_AddPropertyInterface(bc_Interface* self, bc_Property* p) {
	PushVector(self->Properties, p);
}

bc_Method * bc_ILFindMethodInterface(bc_Interface* self, StringView namev, Vector * args, Enviroment * env, CallContext* cctx, int * outIndex) {
	return bc_MetaILFindMethod(self->Methods, namev, args, env,cctx, outIndex);
}

bc_Method* bc_GFindMethodInterface(bc_Interface* self, StringView namev, Vector* gargs, int* outIndex) {
	return bc_MetaGFindMethod(self->Methods, namev, gargs, outIndex);
}

Vector* bc_FlattenMethodInterfaceList(Vector* inter_list) {
	Vector* ret = NewVector();
	for(int i=0; i<inter_list->Length; i++) {
		bc_Interface* inter = AtVector(inter_list, i);
		//インターフェイスのメソッド一覧を挿入
		Vector* list = bc_FlattenMethodInterface(inter);
		for(int j=0; j<list->Length; j++) {
			PushVector(ret, AtVector(list, j));
		}
		DeleteVector(list, VectorDeleterOfNull);
	}
	return ret;
}

Vector* bc_FlattenMethodInterface(bc_Interface* self) {
	Vector* ret = NewVector();
	flatten_method_impl(self, ret, 0);
	return ret;
}

void bc_CreateVTableInterface(bc_Interface* self) {
	//初期化済み
	if (self->VT != NULL) {
		return;
	}
	self->VT = bc_NewVTable();
	//他のインターフェイスを継承していないならフラットに並べる
	if (self->Implements->Length == 0) {
		for (int i = 0; i < self->Methods->Length; i++) {
			bc_AddVTable(self->VT, AtVector(self->Methods, i));
		}
	} else {
		for (int i = 0; i < self->Implements->Length; i++) {
			bc_GenericType* ginter = (bc_GenericType*)AtVector(self->Implements, i);
			bc_Type* cinter = bc_GENERIC2TYPE(ginter);
			bc_Interface* inter = BC_TYPE2INTERFACE(cinter);
//			Interface* inter = (Interface*)AtVector(self->Implements, i);
			bc_CreateVTableInterface(inter);
			bc_CopyVTable(inter->VT, self->VT);
		}
		for (int i = 0; i < self->Methods->Length; i++) {
			bc_AddVTable(self->VT, AtVector(self->Methods, i));
		}
	}
}

void bc_UnlinkInterface(bc_Interface* self) {
	DeleteVector(self->Methods, delete_method);
	DeleteVector(self->Properties, delete_property);
	DeleteVector(self->Implements, VectorDeleterOfNull);
	bc_DeleteVTable(self->VT);
}

void bc_DeleteInterface(bc_Interface* self) {
	DeleteVector(self->TypeParameters, delete_type_parameter);
	MEM_FREE(self);
}

bc_GenericType* bc_IsContainsTypeInterface(bc_GenericType* source, bc_Interface* find) {
	bc_Interface* self = source->CoreType->Kind.Interface;
	if(self == find) {
		return source;
	}
	for(int i=0; i<self->Implements->Length; i++) {
		bc_GenericType* gE = AtVector(self->Implements, i);
		if(gE->CoreType->Kind.Interface == find) {
			return gE;
		}
	}
	return NULL;
}

bool bc_IsFunctionalInterface(bc_Interface* self) {
	return bc_GetFunctionInterface(self) != NULL;
}

bc_Method* bc_GetFunctionInterface(bc_Interface* self) {
	Vector* v = bc_FlattenMethodInterface(self);
	bc_Method* ret = NULL;
	if(v->Length == 1) {
		ret = AtVector(v, 0);
	}
	DeleteVector(v, VectorDeleterOfNull);
	return ret;
}


Vector* bc_GetGenericInterfaceTreeInterface(bc_Interface* self) {
	return get_generic_interface_tree_impl(self);
}

bc_GenericType* bc_FindInterfaceInterface(bc_Interface* self, bc_Type* tinter) {
	assert(tinter->Tag == TYPE_INTERFACE_T);
	if (self == BC_TYPE2INTERFACE(tinter)) {
		return NULL;
	}
	for (int i = 0; i < self->Implements->Length; i++) {
		bc_GenericType* e = AtVector(self->Implements, i);
		if (e->CoreType == tinter) {
			return e;
		}
	}
	return NULL;
}

//private
Vector* get_generic_interface_tree_impl(bc_Interface* self) {
	Vector* ret = NewVector();
	for(int i=0; i<self->Implements->Length; i++) {
		bc_GenericType* ginter = AtVector(self->Implements, i);
		PushVector(ret, ginter);
		Vector* inner = get_generic_interface_tree_impl(BC_TYPE2INTERFACE(bc_GENERIC2TYPE(ginter)));
		MergeVector(ret, inner);
		DeleteVector(inner, VectorDeleterOfNull);
	}
	return ret;
}
static void delete_method(VectorItem item) {
	bc_Method* e = (bc_Method*)item;
	bc_DeleteMethod(e);
}

static void delete_type_parameter(VectorItem item) {
	bc_TypeParameter* e = (bc_TypeParameter*)item;
	bc_DeleteTypeParameter(e);
}

static void delete_generic_type(VectorItem item) {
	//GenericType* e = (GenericType*)item;
	//generic_DeleteType(e);
}

static void flatten_method_impl(bc_Interface* self, Vector* dest, int depth) {
	//tekitou
	#if defined(DEBUG)
	const char* intername = Ref2Str(self->Name);
	#endif
	assert(depth < 42);
	for(int i=0; i<self->Methods->Length; i++) {
		bc_Method* m = AtVector(self->Methods, i);
		PushVector(dest, m);
	}
	for(int i=0; i<self->Implements->Length; i++) {
		bc_GenericType* e = AtVector(self->Implements, i);
		bc_Interface* inter = BC_TYPE2INTERFACE(e->CoreType);
		flatten_method_impl(inter, dest, depth + 1);
	}
}

static void delete_property(VectorItem item) {
	bc_Property* e = (bc_Property*)item;
	bc_DeleteProperty(e);
}