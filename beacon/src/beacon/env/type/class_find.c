#include "class_find.h"
#include "meta_impl.h"
#include "../object.h"
#include "interface_impl.h"
#include "../field.h"
#include "../property.h"
#include "../property_body.h"
#include "../parameter.h"
#include "../generic_type.h"
#include "../../il/il_argument.h"
#include "../../il/il_factor_impl.h"
#include "../../util/vector.h"

static bool IsContainsFieldClassImpl(Vector* fields, bc_Field* f);
static bool IsContainsPropertyClassImpl(Vector* props, bc_Property* p);

bc_Field* bc_FindFieldClass(bc_Class* self, StringView namev, int* outIndex) {
	(*outIndex) = -1;
	for (int i = 0; i < self->Fields->Length; i++) {
		VectorItem e = AtVector(self->Fields, i);
		bc_Field* f = (bc_Field*)e;
		if (namev == f->Name) {
			(*outIndex) = (bc_CountAllFieldClass(self) - self->Fields->Length) + i;
			return f;
		}
	}
	return NULL;
}

bc_Field* bc_FindTreeFieldClass(bc_Class* self, StringView namev, int * outIndex) {
	bc_Class* pointee = self;
	do {
		bc_Field* f = bc_FindFieldClass(pointee, namev, outIndex);
		if (f != NULL) {
			return f;
		}
		bc_GenericType* supergtype = pointee->SuperClass;
		if(supergtype == NULL) {
			break;
		}
		pointee = supergtype->CoreType->Kind.Class;
	} while (pointee != NULL);
	return NULL;
}

bc_Field* bc_FindSFieldClass(bc_Class* self, StringView namev, int * outIndex) {
	(*outIndex) = -1;
	for (int i = 0; i < self->StaticFields->Length; i++) {
		VectorItem e = AtVector(self->StaticFields, i);
		bc_Field* f = (bc_Field*)e;
		if (namev == f->Name) {
			(*outIndex) = (bc_CountAllSFieldClass(self) - self->StaticFields->Length) + i;
			return f;
		}
	}
	return NULL;
}

bc_Field* bc_FindTreeSFieldClass(bc_Class* self, StringView namev, int * outIndex) {
	bc_Class* pointee = self;
	do {
		bc_Field* f = bc_FindSFieldClass(pointee, namev, outIndex);
		if (f != NULL) {
			return f;
		}
		if(pointee->SuperClass == NULL) {
			break;
		}
		pointee = pointee->SuperClass->CoreType->Kind.Class;
	} while (pointee != NULL);
	return NULL;
}

bc_Field* bc_GetFieldClass(bc_Class* self, int index) {
	assert(index >= 0);
	int all = bc_CountAllFieldClass(self);
	if (index >= (all - self->Fields->Length) &&
		index < all) {
		return AtVector(self->Fields, self->Fields->Length - (all - index));
	}
	return bc_GetFieldClass(self->SuperClass->CoreType->Kind.Class, index);
}

bc_Field* bc_GetSFieldClass(bc_Class* self, int index) {
	assert(index >= 0);
	int all = bc_CountAllSFieldClass(self);
	if (index >= (all - self->StaticFields->Length) &&
		index < all) {
		return AtVector(self->StaticFields, self->StaticFields->Length - (all - index));
	}
	return bc_GetSFieldClass(self->SuperClass->CoreType->Kind.Class, index);
}

bool bc_IsContainsFieldClass(bc_Class* self, bc_Field* f) {
	return IsContainsFieldClassImpl(self->Fields, f);
}

bool bc_IsContainsSFieldClass(bc_Class* self, bc_Field* f) {
	return IsContainsFieldClassImpl(self->StaticFields, f);
}

bool bc_IsAccessibleFieldClass(bc_Class* self, bc_Field* f) {
	assert(f != NULL);
	if(f->Access == ACCESS_PUBLIC_T) {
		return true;
	}
	if(f->Access == ACCESS_PRIVATE_T) {
		return self == BC_TYPE2CLASS(f->Parent);
	}
	bc_Type* ty = self->Parent;
	bc_Class* fcl = BC_TYPE2CLASS(f->Parent);
	while(true) {
		bc_Class* c = BC_TYPE2CLASS(ty);
		if(c == fcl) {
			return true;
		}
		//次へ
		if(c->SuperClass == NULL) {
			break;
		}
		ty = c->SuperClass->CoreType;
	}
	return false;
}



bool bc_IsContainsPropertyClass(bc_Class* self, bc_Property* p) {
	return IsContainsPropertyClassImpl(self->Properties, p);
}

bool bc_IsContainsSPropertyClass(bc_Class* self, bc_Property* p) {
	return IsContainsPropertyClassImpl(self->StaticProperties, p);
}

bool bc_IsAccessiblePropertyClass(bc_Class* self, bc_Property* p) {
	assert(p != NULL);
	if(p->Access == ACCESS_PUBLIC_T) {
		return true;
	}
	if(p->Access == ACCESS_PRIVATE_T) {
		return self == BC_TYPE2CLASS(p->Parent);
	}
	bc_Type* ty = self->Parent;
	bc_Class* fcl = BC_TYPE2CLASS(p->Parent);
	while(true) {
		bc_Class* c = BC_TYPE2CLASS(ty);
		if(c == fcl) {
			return true;
		}
		//次へ
		if(c->SuperClass == NULL) {
			break;
		}
		ty = c->SuperClass->CoreType;
	}
	return false;
}

bool bc_IsAccessiblePropertyAccessorClass(bc_Class* self, bc_PropertyBody* pb) {
	assert(pb != NULL);
	if(pb->Access == ACCESS_PUBLIC_T) {
		return true;
	}
	if(pb->Access == ACCESS_PRIVATE_T) {
		return self == BC_TYPE2CLASS(pb->Parent->Parent);
	}
	bc_Type* ty = self->Parent;
	bc_Class* fcl = BC_TYPE2CLASS(pb->Parent->Parent);
	while(true) {
		bc_Class* c = BC_TYPE2CLASS(ty);
		if(c == fcl) {
			return true;
		}
		//次へ
		if(c->SuperClass == NULL) {
			break;
		}
		ty = c->SuperClass->CoreType;
	}
	return false;
}

int bc_GetFieldByPropertyClass(bc_Class* self, bc_Property* p) {
	int temp = -1;
	assert(p->SourceRef != NULL);
	if(bc_IsStaticModifier(p->Modifier)) {
		bc_FindSFieldClass(self, p->SourceRef->Name, &temp);
	} else {
		bc_FindFieldClass(self, p->SourceRef->Name, &temp);
	}
	return temp;
}

bc_Property* bc_GetPropertyClass(bc_Class* self, int index) {
	assert(index >= 0);
	int all = bc_CountAllPropertyClass(self);
	if (index >= (all - self->Properties->Length) &&
		index < all) {
		return AtVector(self->Properties, self->Properties->Length - (all - index));
	}
	return bc_GetPropertyClass(self->SuperClass->CoreType->Kind.Class, index);
}

bc_Property* bc_GetSPropertyClass(bc_Class* self, int index) {
	assert(index >= 0);
	int all = bc_CountAllSPropertyClass(self);
	if (index >= (all - self->StaticProperties->Length) &&
		index < all) {
		return AtVector(self->StaticProperties, self->StaticProperties->Length - (all - index));
	}
	return bc_GetPropertyClass(self->SuperClass->CoreType->Kind.Class, index);
}

bc_Property* bc_FindPropertyClass(bc_Class* self, StringView namev, int* outIndex) {
	(*outIndex) = -1;
	for (int i = 0; i < self->Properties->Length; i++) {
		VectorItem e = AtVector(self->Properties, i);
		bc_Property* p = (bc_Property*)e;
		if (namev == p->Name) {
			(*outIndex) = (bc_CountAllPropertyClass(self) - self->Properties->Length) + i;
			return p;
		}
	}
	return NULL;
}

bc_Property* bc_FindTreePropertyClass(bc_Class* self, StringView namev, int* outIndex) {
	bc_Class* pointee = self;
	do {
		bc_Property* p = bc_FindPropertyClass(pointee, namev, outIndex);
		if (p != NULL) {
			return p;
		}
		bc_GenericType* supergtype = pointee->SuperClass;
		if(supergtype == NULL) {
			break;
		}
		pointee = supergtype->CoreType->Kind.Class;
	} while (pointee != NULL);
	return NULL;
}

bc_Property* bc_FindSPropertyClass(bc_Class* self, StringView namev, int* outIndex) {
	(*outIndex) = -1;
	for (int i = 0; i < self->StaticProperties->Length; i++) {
		VectorItem e = AtVector(self->StaticProperties, i);
		bc_Property* p = (bc_Property*)e;
		if (namev == p->Name) {
			(*outIndex) = (bc_CountAllSPropertyClass(self) - self->StaticProperties->Length) + i;
			return p;
		}
	}
	return NULL;
}

bc_Property* bc_FindTreeSPropertyClass(bc_Class* self, StringView namev, int* outIndex) {
	bc_Class* pointee = self;
	do {
		bc_Property* p = bc_FindSPropertyClass(pointee, namev, outIndex);
		if (p != NULL) {
			return p;
		}
		bc_GenericType* supergtype = pointee->SuperClass;
		if(supergtype == NULL) {
			break;
		}
		pointee = supergtype->CoreType->Kind.Class;
	} while (pointee != NULL);
	return NULL;
}



bc_Constructor* bc_RFindConstructorClass(bc_Class* self, Vector * args, Vector* typeargs, Frame* fr, int* outIndex) {
	return bc_MetaScopedRFindConstructor(self, self->Constructors, args, typeargs, fr, outIndex);
}

bc_Constructor* bc_ILFindConstructorClass(bc_Class* self, Vector * args, Enviroment * env, CallContext* cctx, int* outIndex) {
	//	Vector* v = meta_find_constructors(self, args, env, ilctx);
	//	(*outIndex) = -1;
	//	return class_find_constructor_impl(v, args, env, ilctx, outIndex);
	bc_Constructor* ctor = bc_MetaScopedILFindConstructor(self, self->Constructors, args, env, cctx, outIndex);
	return ctor;
}

bc_Constructor * bc_ILFindEmptyConstructorClass(bc_Class* self, Enviroment * env, CallContext* cctx, int * outIndex) {
	Vector* emptyArgs = NewVector();
	bc_Constructor* ret = bc_ILFindConstructorClass(self, emptyArgs, env, cctx, outIndex);
	DeleteVector(emptyArgs, VectorDeleterOfNull);
	return ret;
}



bc_Method * bc_ILFindMethodClass(bc_Class* self, StringView namev, Vector * args, Enviroment * env, CallContext* cctx, int * outIndex) {
	(*outIndex) = -1;
	bc_CreateVTableClass(self);
	#if defined(DEBUG)
	const char* str = Ref2Str(self->Name);
	#endif
	//assert(self->vt->elements->Length > 0);
	bc_Method* ret = NULL;
	if((ret = bc_MetaScopedILFindMethod(self, self->VT->Elements, namev, args, env, cctx, outIndex))
	   != NULL) {
		   return ret;
	}
	if((ret = bc_MetaScopedILFindMethod(self, self->Methods, namev, args, env, cctx, outIndex))
	   != NULL) {
		   return ret;
	}
	if((ret = bc_MetaScopedILFindMethod(self, self->StaticMethods, namev, args, env, cctx, outIndex))
	   != NULL) {
		   return ret;
	}
	return NULL;
}

bc_Method* bc_GFindMethodClass(bc_Class* self, StringView namev, Vector* gargs, int* outIndex) {
	(*outIndex) = -1;
	bc_CreateVTableClass(self);
	//assert(self->vt->elements->Length > 0);
	bc_Method* ret = NULL;
	if((ret = bc_MetaScopedGFindMethod(self, self->VT->Elements, namev, gargs, outIndex))
	   != NULL) {
		   return ret;
	}
	if((ret = bc_MetaScopedGFindMethod(self, self->Methods, namev, gargs, outIndex))
	   != NULL) {
		   return ret;
	}
	if((ret = bc_MetaScopedGFindMethod(self, self->StaticMethods, namev, gargs, outIndex))
	   != NULL) {
		   return ret;
	}
	return NULL;
}

bc_Method* bc_GFindEqMethodClass(bc_Class* self, int* outIndex) {
	Vector* gargs = NewVector();
	PushVector(gargs, BC_TYPE_OBJECT->GenericSelf);
	bc_Method* ret = bc_GFindMethodClass(self, InternString("equals"), gargs, outIndex);
	DeleteVector(gargs, VectorDeleterOfNull);
	return ret;
}

bc_Method * bc_ILFindSMethodClass(bc_Class* self, StringView namev, Vector * args, Enviroment * env, CallContext* cctx, int * outIndex) {
	#if defined(DEBUG)
	const char* str = Ref2Str(namev);
	#endif
	(*outIndex) = -1;
	bc_CreateVTableClass(self);
	int temp = 0;
	bc_Method* ret = bc_MetaILFindMethod(self->StaticMethods, namev, args, env, cctx, &temp);
//	temp += (CountAllSMethodClass(self) - self->StaticMethods->Length);
	(*outIndex) = temp;
	return ret;
}

bc_Method* bc_GFindSMethodClass(bc_Class* self, StringView namev, Vector* gargs, int* outIndex) {
	(*outIndex) = -1;
	bc_CreateVTableClass(self);
	int temp = 0;
	bc_Method* ret = bc_MetaGFindMethod(self->StaticMethods, namev, gargs, &temp);
//	temp += (CountAllSMethodClass(self) - self->StaticMethods->Length);
	(*outIndex) = temp;
	return ret;
}

bc_Method * bc_GetMethodClass(bc_Object * o, int index) {
	assert(index >= 0);
	#if defined(DEBUG)
	const char* name = bc_GetObjectName(o);
	#endif
	if(bc_IsNullValue(o)) {
		o->VPtr = BC_TYPE2CLASS(BC_TYPE_OBJECT)->VT;
	}
	bc_VTable* vx = (o->VPtr);
	return (bc_Method*)AtVector(vx->Elements, index);
}

bc_Method * bc_GetSMethodClass(bc_Class* self, int index) {
	assert(index >= 0);
	/*
	//Class* self = o->classz;
	int all = CountAllSMethodClass(self);
	if (index >= (all - self->StaticMethods->Length) &&
		index < all) {
		return AtVector(self->StaticMethods, self->StaticMethods->Length - (all - index));
	}
	return GetSMethodClass(self->SuperClass->CoreType->Kind.Class, index);
	//*/
	return AtVector(self->StaticMethods, index);
}

bc_Method * bc_GetImplMethodClass(bc_Class* self, bc_Type* interType, int interMIndex) {
	#if defined(DEBUG)
	const char* str = Ref2Str(self->Name);
	#endif
	assert(self->VTTable->Length > 0);
	Vector* tbl = bc_GetGenericInterfaceTreeClass(self);
	//指定のインターフェイスが
	//このクラスにおいて何番目かを調べる
	int declIndex = -1;
	for (int i = 0; i < tbl->Length; i++) {
		bc_GenericType* e = AtVector(tbl, i);
		bc_Interface* inter = e->CoreType->Kind.Interface;
		if (inter == interType->Kind.Interface) {
			declIndex = i;
			break;
		}
	}
	//仮想関数テーブルの一覧から引く
	assert(declIndex != -1);
	DeleteVector(tbl, VectorDeleterOfNull);
	bc_VTable* vtAt = AtVector(self->VTTable, declIndex);
	return AtVector(vtAt->Elements, interMIndex);
}




bc_OperatorOverload* bc_GFindOperatorOverloadClass(bc_Class* self, bc_OperatorType type, Vector* args, Enviroment* env, CallContext* cctx, int* outIndex) {
	(*outIndex) = -1;
	bc_OperatorOverload* ret = NULL;
	bc_CreateOperatorVTClass(self);
	for(int i=0; i<self->OVT->Operators->Length; i++) {
		bc_OperatorOverload* operator_ov = AtVector(self->OVT->Operators, i);
		if(operator_ov->Type != type) {
			continue;
		}
		bool nomatch = false;
		int score = 1024;
		int sum = 0;
		Vector* params = operator_ov->Parameters;
		for(int j=0; j<params->Length; j++) {
			bc_Parameter* param = AtVector(params, j);
			bc_GenericType* arg = AtVector(args, j);
			int dist = bc_DistanceGenericType(param->GType, arg, cctx);
			if(dist == -1) {
				nomatch = true;
				break;
			}
			sum += dist;
		}
		if(nomatch) {
			continue;
		}
		if(sum < score) {
			score = sum;
			(*outIndex) = i;
			ret = operator_ov;
		}
	}
	return ret;
}

bc_OperatorOverload* bc_ILFindOperatorOverloadClass(bc_Class* self, bc_OperatorType type, Vector* args, Enviroment* env, CallContext* cctx, int* outIndex) {
	Vector* gargs =NewVector();
	for(int i=0; i<args->Length; i++) {
		ILFactor* ilfact = (ILFactor*)AtVector(args,i);
		bc_GenericType* g = EvalILFactor(ilfact, env, cctx);
		PushVector(gargs, g);
	}
	bc_OperatorOverload* ret = bc_GFindOperatorOverloadClass(self, type, gargs, env, cctx, outIndex);
	DeleteVector(gargs, VectorDeleterOfNull);
	return ret;
}

bc_OperatorOverload* bc_ArgFindOperatorOverloadClass(bc_Class* self, bc_OperatorType type, Vector* args, Enviroment* env, CallContext* cctx, int* outIndex) {
	Vector* gargs =NewVector();
	for(int i=0; i<args->Length; i++) {
		//ILFactor* ilfact = (ILFactor*)AtVector(args,i);
		ILArgument* ilarg = (ILArgument*)AtVector(args, i);
		ILFactor* ilfact = ilarg->Factor;
		bc_GenericType* g = EvalILFactor(ilfact, env, cctx);
		PushVector(gargs, g);
	}
	bc_OperatorOverload* ret = bc_GFindOperatorOverloadClass(self, type, gargs, env, cctx, outIndex);
	DeleteVector(gargs, VectorDeleterOfNull);
	return ret;
}

bc_OperatorOverload* bc_GetOperatorOverloadClass(bc_Class* self, int index) {
	return AtVector(self->OVT->Operators, index);
}

Vector* bc_FindTreeMethodClass(bc_Class* self, bc_Method* m) {
	assert(self != NULL);
	assert(m != NULL);
	bc_Class* ptr = self;
	Vector* ret = NewVector();
	#if defined(DEBUG)
	const char* ptrname = Ref2Str(ptr->Name);
	#endif
	do {
		bc_Method* tmp = NULL;
		if(bc_IsContainsMethod(ptr->Methods, m, &tmp)) {
			PushVector(ret, tmp);
		}
		//親クラスへ
		if(ptr->SuperClass != NULL) {
			ptr = ptr->SuperClass->CoreType->Kind.Class;
		} else {
			ptr = NULL;
		}
	} while(ptr != NULL);
	return ret;
}

bool bc_IsContainsMethod(Vector* method_list, bc_Method* m, bc_Method** outM) {
	assert(!bc_IsStaticModifier(m->Modifier));
	(*outM) = NULL;
	bool ret = false;
	CallContext* cctx = NewCallContext(CALL_DECL_T);
	cctx->Scope = m->Parent->Location;
	cctx->Ty = m->Parent;
	for(int i=0; i<method_list->Length; i++) {
		bc_Method* mE = AtVector(method_list, i);
		if(bc_IsOverridedMethod(m, mE, cctx)) {
			(*outM) = mE;
			ret = true;
			break;
		}
	}
	DeleteCallContext(cctx);
	return ret;
}

Vector* bc_GetGenericInterfaceListClass(bc_Class* self) {
	Vector* ret = NewVector();
	for(int i=0; i<self->Implements->Length; i++) {
		bc_GenericType* ginter = AtVector(self->Implements, i);
		Vector* inner = bc_GetGenericInterfaceTreeInterface(BC_TYPE2INTERFACE(bc_GENERIC2TYPE(ginter)));
		MergeVector(ret, inner);
		PushVector(ret, ginter);
		DeleteVector(inner, VectorDeleterOfNull);
	}
	return ret;
}

Vector* bc_GetGenericInterfaceTreeClass(bc_Class* self) {
	bc_Class* ptr = self;
	Vector* ret = NewVector();
	do {
		Vector* v = bc_GetGenericInterfaceListClass(ptr);
		MergeVector(v, ret);
		DeleteVector(v, VectorDeleterOfNull);
		if(ptr->SuperClass == NULL) {
			break;
		}
		ptr = BC_TYPE2CLASS(bc_GENERIC2TYPE(ptr->SuperClass));
	} while(ptr != NULL);
	return ret;
}

Vector* bc_GetInterfaceListClass(bc_Class* self) {
	Vector* ret = NewVector();
	Vector* c = bc_GetGenericInterfaceListClass(self);
	for(int i=0; i<c->Length; i++) {
		bc_GenericType* gt = AtVector(c, i);
		PushVector(ret, BC_TYPE2INTERFACE(bc_GENERIC2TYPE(gt)));
	}
	DeleteVector(c, VectorDeleterOfNull);
	return ret;
}

Vector* bc_GetInterfaceTreeClass(bc_Class* self) {
	Vector* ret = NewVector();
	Vector* c = bc_GetGenericInterfaceTreeClass(self);
	for(int i=0; i<c->Length; i++) {
		bc_GenericType* gt = AtVector(c, i);
		PushVector(ret, BC_TYPE2INTERFACE(bc_GENERIC2TYPE(gt)));
	}
	DeleteVector(c, VectorDeleterOfNull);
	return ret;
}

bc_GenericType* bc_FindInterfaceTypeClass(bc_Class* self, bc_Type* tinter, bc_GenericType** out_baseline) {
	assert(tinter->Tag == TYPE_INTERFACE_T);
	(*out_baseline) = NULL;
	//実装インターフェイス一覧から同じのを探す
	bc_GenericType* ret = NULL;
	bc_GenericType* out = NULL;
	bc_Class* ptr = self;
	do {
		if (ptr->SuperClass == NULL) {
			break;
		}
		bool found = false;
		//Vector* gimpl_list = GetGenericInterfaceListClass(ptr);
		Vector* gimpl_list = ptr->Implements;
		for (int i = 0; i < gimpl_list->Length; i++) {
			bc_GenericType* gimpl = AtVector(gimpl_list, i);
			if (gimpl->CoreType == tinter) {
				found = true;
				ret = gimpl;
				break;
			}
		}
		//DeleteVector(gimpl_list, VectorDeleterOfNull);
		if (found) {
			(*out_baseline) = out;
			break;
		}
		out = ptr->SuperClass;
		ptr = BC_TYPE2CLASS(bc_GENERIC2TYPE(ptr->SuperClass));
	} while (ptr != NULL);
	return ret;
}

//private
static bool IsContainsFieldClassImpl(Vector* fields, bc_Field* f) {
	for(int i=0; i<fields->Length; i++) {
		bc_Field* e = (bc_Field*)AtVector(fields, i);
		if(e == f) {
			return true;
		}
	}
	return false;
}

static bool IsContainsPropertyClassImpl(Vector* props, bc_Property* p) {
	for(int i=0; i<props->Length; i++) {
		bc_Property* e = (bc_Property*)AtVector(props, i);
		if(e == p) {
			return true;
		}
	}
	return false;
}