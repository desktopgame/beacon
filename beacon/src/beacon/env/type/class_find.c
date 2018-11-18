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

static bool IsContainsFieldClassImpl(Vector* fields, Field* f);
static bool IsContainsPropertyClassImpl(Vector* props, Property* p);

Field* FindFieldClass(Class* self, StringView namev, int* outIndex) {
	(*outIndex) = -1;
	for (int i = 0; i < self->Fields->Length; i++) {
		VectorItem e = AtVector(self->Fields, i);
		Field* f = (Field*)e;
		if (namev == f->Name) {
			(*outIndex) = (CountAllFieldClass(self) - self->Fields->Length) + i;
			return f;
		}
	}
	return NULL;
}

Field* FindTreeFieldClass(Class* self, StringView namev, int * outIndex) {
	Class* pointee = self;
	do {
		Field* f = FindFieldClass(pointee, namev, outIndex);
		if (f != NULL) {
			return f;
		}
		GenericType* supergtype = pointee->SuperClass;
		if(supergtype == NULL) {
			break;
		}
		pointee = supergtype->CoreType->Kind.Class;
	} while (pointee != NULL);
	return NULL;
}

Field* FindSFieldClass(Class* self, StringView namev, int * outIndex) {
	(*outIndex) = -1;
	for (int i = 0; i < self->StaticFields->Length; i++) {
		VectorItem e = AtVector(self->StaticFields, i);
		Field* f = (Field*)e;
		if (namev == f->Name) {
			(*outIndex) = (CountAllSFieldClass(self) - self->StaticFields->Length) + i;
			return f;
		}
	}
	return NULL;
}

Field* FindTreeSFieldClass(Class* self, StringView namev, int * outIndex) {
	Class* pointee = self;
	do {
		Field* f = FindSFieldClass(pointee, namev, outIndex);
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

Field* GetFieldClass(Class* self, int index) {
	assert(index >= 0);
	int all = CountAllFieldClass(self);
	if (index >= (all - self->Fields->Length) &&
		index < all) {
		return AtVector(self->Fields, self->Fields->Length - (all - index));
	}
	return GetFieldClass(self->SuperClass->CoreType->Kind.Class, index);
}

Field* GetSFieldClass(Class* self, int index) {
	assert(index >= 0);
	int all = CountAllSFieldClass(self);
	if (index >= (all - self->StaticFields->Length) &&
		index < all) {
		return AtVector(self->StaticFields, self->StaticFields->Length - (all - index));
	}
	return GetSFieldClass(self->SuperClass->CoreType->Kind.Class, index);
}

bool IsContainsFieldClass(Class* self, Field* f) {
	return IsContainsFieldClassImpl(self->Fields, f);
}

bool IsContainsSFieldClass(Class* self, Field* f) {
	return IsContainsFieldClassImpl(self->StaticFields, f);
}

bool IsAccessibleFieldClass(Class* self, Field* f) {
	assert(f != NULL);
	if(f->Access == ACCESS_PUBLIC_T) {
		return true;
	}
	if(f->Access == ACCESS_PRIVATE_T) {
		return self == TYPE2CLASS(f->Parent);
	}
	Type* ty = self->Parent;
	Class* fcl = TYPE2CLASS(f->Parent);
	while(true) {
		Class* c = TYPE2CLASS(ty);
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



bool IsContainsPropertyClass(Class* self, Property* p) {
	return IsContainsPropertyClassImpl(self->Properties, p);
}

bool IsContainsSPropertyClass(Class* self, Property* p) {
	return IsContainsPropertyClassImpl(self->StaticProperties, p);
}

bool IsAccessiblePropertyClass(Class* self, Property* p) {
	assert(p != NULL);
	if(p->Access == ACCESS_PUBLIC_T) {
		return true;
	}
	if(p->Access == ACCESS_PRIVATE_T) {
		return self == TYPE2CLASS(p->Parent);
	}
	Type* ty = self->Parent;
	Class* fcl = TYPE2CLASS(p->Parent);
	while(true) {
		Class* c = TYPE2CLASS(ty);
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

bool IsAccessiblePropertyAccessorClass(Class* self, PropertyBody* pb) {
	assert(pb != NULL);
	if(pb->Access == ACCESS_PUBLIC_T) {
		return true;
	}
	if(pb->Access == ACCESS_PRIVATE_T) {
		return self == TYPE2CLASS(pb->Parent->Parent);
	}
	Type* ty = self->Parent;
	Class* fcl = TYPE2CLASS(pb->Parent->Parent);
	while(true) {
		Class* c = TYPE2CLASS(ty);
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

int GetFieldByPropertyClass(Class* self, Property* p) {
	int temp = -1;
	assert(p->SourceRef != NULL);
	if(bc_IsStaticModifier(p->Modifier)) {
		FindSFieldClass(self, p->SourceRef->Name, &temp);
	} else {
		FindFieldClass(self, p->SourceRef->Name, &temp);
	}
	return temp;
}

Property* GetPropertyClass(Class* self, int index) {
	assert(index >= 0);
	int all = CountAllPropertyClass(self);
	if (index >= (all - self->Properties->Length) &&
		index < all) {
		return AtVector(self->Properties, self->Properties->Length - (all - index));
	}
	return GetPropertyClass(self->SuperClass->CoreType->Kind.Class, index);
}

Property* GetSPropertyClass(Class* self, int index) {
	assert(index >= 0);
	int all = CountAllSPropertyClass(self);
	if (index >= (all - self->StaticProperties->Length) &&
		index < all) {
		return AtVector(self->StaticProperties, self->StaticProperties->Length - (all - index));
	}
	return GetPropertyClass(self->SuperClass->CoreType->Kind.Class, index);
}

Property* FindPropertyClass(Class* self, StringView namev, int* outIndex) {
	(*outIndex) = -1;
	for (int i = 0; i < self->Properties->Length; i++) {
		VectorItem e = AtVector(self->Properties, i);
		Property* p = (Property*)e;
		if (namev == p->Name) {
			(*outIndex) = (CountAllPropertyClass(self) - self->Properties->Length) + i;
			return p;
		}
	}
	return NULL;
}

Property* FindTreePropertyClass(Class* self, StringView namev, int* outIndex) {
	Class* pointee = self;
	do {
		Property* p = FindPropertyClass(pointee, namev, outIndex);
		if (p != NULL) {
			return p;
		}
		GenericType* supergtype = pointee->SuperClass;
		if(supergtype == NULL) {
			break;
		}
		pointee = supergtype->CoreType->Kind.Class;
	} while (pointee != NULL);
	return NULL;
}

Property* FindSPropertyClass(Class* self, StringView namev, int* outIndex) {
	(*outIndex) = -1;
	for (int i = 0; i < self->StaticProperties->Length; i++) {
		VectorItem e = AtVector(self->StaticProperties, i);
		Property* p = (Property*)e;
		if (namev == p->Name) {
			(*outIndex) = (CountAllSPropertyClass(self) - self->StaticProperties->Length) + i;
			return p;
		}
	}
	return NULL;
}

Property* FindTreeSPropertyClass(Class* self, StringView namev, int* outIndex) {
	Class* pointee = self;
	do {
		Property* p = FindSPropertyClass(pointee, namev, outIndex);
		if (p != NULL) {
			return p;
		}
		GenericType* supergtype = pointee->SuperClass;
		if(supergtype == NULL) {
			break;
		}
		pointee = supergtype->CoreType->Kind.Class;
	} while (pointee != NULL);
	return NULL;
}



Constructor* RFindConstructorClass(Class* self, Vector * args, Vector* typeargs, Frame* fr, int* outIndex) {
	return MetaScopedRFindConstructor(self, self->Constructors, args, typeargs, fr, outIndex);
}

Constructor* ILFindConstructorClass(Class* self, Vector * args, Enviroment * env, CallContext* cctx, int* outIndex) {
	//	Vector* v = meta_find_constructors(self, args, env, ilctx);
	//	(*outIndex) = -1;
	//	return class_find_constructor_impl(v, args, env, ilctx, outIndex);
	Constructor* ctor = MetaScopedILFindConstructor(self, self->Constructors, args, env, cctx, outIndex);
	return ctor;
}

Constructor * ILFindEmptyConstructorClass(Class* self, Enviroment * env, CallContext* cctx, int * outIndex) {
	Vector* emptyArgs = NewVector();
	Constructor* ret = ILFindConstructorClass(self, emptyArgs, env, cctx, outIndex);
	DeleteVector(emptyArgs, VectorDeleterOfNull);
	return ret;
}



Method * ILFindMethodClass(Class* self, StringView namev, Vector * args, Enviroment * env, CallContext* cctx, int * outIndex) {
	(*outIndex) = -1;
	CreateVTableClass(self);
	#if defined(DEBUG)
	const char* str = Ref2Str(self->Name);
	#endif
	//assert(self->vt->elements->Length > 0);
	Method* ret = NULL;
	if((ret = MetaScopedILFindMethod(self, self->VT->Elements, namev, args, env, cctx, outIndex))
	   != NULL) {
		   return ret;
	}
	if((ret = MetaScopedILFindMethod(self, self->Methods, namev, args, env, cctx, outIndex))
	   != NULL) {
		   return ret;
	}
	if((ret = MetaScopedILFindMethod(self, self->StaticMethods, namev, args, env, cctx, outIndex))
	   != NULL) {
		   return ret;
	}
	return NULL;
}

Method* GFindMethodClass(Class* self, StringView namev, Vector* gargs, int* outIndex) {
	(*outIndex) = -1;
	CreateVTableClass(self);
	//assert(self->vt->elements->Length > 0);
	Method* ret = NULL;
	if((ret = MetaScopedGFindMethod(self, self->VT->Elements, namev, gargs, outIndex))
	   != NULL) {
		   return ret;
	}
	if((ret = MetaScopedGFindMethod(self, self->Methods, namev, gargs, outIndex))
	   != NULL) {
		   return ret;
	}
	if((ret = MetaScopedGFindMethod(self, self->StaticMethods, namev, gargs, outIndex))
	   != NULL) {
		   return ret;
	}
	return NULL;
}

Method* GFindEqMethodClass(Class* self, int* outIndex) {
	Vector* gargs = NewVector();
	PushVector(gargs, TYPE_OBJECT->GenericSelf);
	Method* ret = GFindMethodClass(self, InternString("equals"), gargs, outIndex);
	DeleteVector(gargs, VectorDeleterOfNull);
	return ret;
}

Method * ILFindSMethodClass(Class* self, StringView namev, Vector * args, Enviroment * env, CallContext* cctx, int * outIndex) {
	#if defined(DEBUG)
	const char* str = Ref2Str(namev);
	#endif
	(*outIndex) = -1;
	CreateVTableClass(self);
	int temp = 0;
	Method* ret = MetaILFindMethod(self->StaticMethods, namev, args, env, cctx, &temp);
//	temp += (CountAllSMethodClass(self) - self->StaticMethods->Length);
	(*outIndex) = temp;
	return ret;
}

Method* GFindSMethodClass(Class* self, StringView namev, Vector* gargs, int* outIndex) {
	(*outIndex) = -1;
	CreateVTableClass(self);
	int temp = 0;
	Method* ret = MetaGFindMethod(self->StaticMethods, namev, gargs, &temp);
//	temp += (CountAllSMethodClass(self) - self->StaticMethods->Length);
	(*outIndex) = temp;
	return ret;
}

Method * GetMethodClass(Object * o, int index) {
	assert(index >= 0);
	#if defined(DEBUG)
	const char* name = GetObjectName(o);
	#endif
	if(IsNullValue(o)) {
		o->VPtr = TYPE2CLASS(TYPE_OBJECT)->VT;
	}
	VTable* vx = (o->VPtr);
	return (Method*)AtVector(vx->Elements, index);
}

Method * GetSMethodClass(Class* self, int index) {
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

Method * GetImplMethodClass(Class* self, Type* interType, int interMIndex) {
	#if defined(DEBUG)
	const char* str = Ref2Str(self->Name);
	#endif
	assert(self->VTTable->Length > 0);
	Vector* tbl = GetGenericInterfaceTreeClass(self);
	//指定のインターフェイスが
	//このクラスにおいて何番目かを調べる
	int declIndex = -1;
	for (int i = 0; i < tbl->Length; i++) {
		GenericType* e = AtVector(tbl, i);
		Interface* inter = e->CoreType->Kind.Interface;
		if (inter == interType->Kind.Interface) {
			declIndex = i;
			break;
		}
	}
	//仮想関数テーブルの一覧から引く
	assert(declIndex != -1);
	DeleteVector(tbl, VectorDeleterOfNull);
	VTable* vtAt = AtVector(self->VTTable, declIndex);
	return AtVector(vtAt->Elements, interMIndex);
}




OperatorOverload* GFindOperatorOverloadClass(Class* self, bc_OperatorType type, Vector* args, Enviroment* env, CallContext* cctx, int* outIndex) {
	(*outIndex) = -1;
	OperatorOverload* ret = NULL;
	CreateOperatorVTClass(self);
	for(int i=0; i<self->OVT->Operators->Length; i++) {
		OperatorOverload* operator_ov = AtVector(self->OVT->Operators, i);
		if(operator_ov->Type != type) {
			continue;
		}
		bool nomatch = false;
		int score = 1024;
		int sum = 0;
		Vector* params = operator_ov->Parameters;
		for(int j=0; j<params->Length; j++) {
			Parameter* param = AtVector(params, j);
			GenericType* arg = AtVector(args, j);
			int dist = DistanceGenericType(param->GType, arg, cctx);
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

OperatorOverload* ILFindOperatorOverloadClass(Class* self, bc_OperatorType type, Vector* args, Enviroment* env, CallContext* cctx, int* outIndex) {
	Vector* gargs =NewVector();
	for(int i=0; i<args->Length; i++) {
		ILFactor* ilfact = (ILFactor*)AtVector(args,i);
		GenericType* g = EvalILFactor(ilfact, env, cctx);
		PushVector(gargs, g);
	}
	OperatorOverload* ret = GFindOperatorOverloadClass(self, type, gargs, env, cctx, outIndex);
	DeleteVector(gargs, VectorDeleterOfNull);
	return ret;
}

OperatorOverload* ArgFindOperatorOverloadClass(Class* self, bc_OperatorType type, Vector* args, Enviroment* env, CallContext* cctx, int* outIndex) {
	Vector* gargs =NewVector();
	for(int i=0; i<args->Length; i++) {
		//ILFactor* ilfact = (ILFactor*)AtVector(args,i);
		ILArgument* ilarg = (ILArgument*)AtVector(args, i);
		ILFactor* ilfact = ilarg->Factor;
		GenericType* g = EvalILFactor(ilfact, env, cctx);
		PushVector(gargs, g);
	}
	OperatorOverload* ret = GFindOperatorOverloadClass(self, type, gargs, env, cctx, outIndex);
	DeleteVector(gargs, VectorDeleterOfNull);
	return ret;
}

OperatorOverload* GetOperatorOverloadClass(Class* self, int index) {
	return AtVector(self->OVT->Operators, index);
}

Vector* FindTreeMethodClass(Class* self, Method* m) {
	assert(self != NULL);
	assert(m != NULL);
	Class* ptr = self;
	Vector* ret = NewVector();
	#if defined(DEBUG)
	const char* ptrname = Ref2Str(ptr->Name);
	#endif
	do {
		Method* tmp = NULL;
		if(IsContainsMethod(ptr->Methods, m, &tmp)) {
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

bool IsContainsMethod(Vector* method_list, Method* m, Method** outM) {
	assert(!bc_IsStaticModifier(m->Modifier));
	(*outM) = NULL;
	bool ret = false;
	CallContext* cctx = NewCallContext(CALL_DECL_T);
	cctx->Scope = m->Parent->Location;
	cctx->Ty = m->Parent;
	for(int i=0; i<method_list->Length; i++) {
		Method* mE = AtVector(method_list, i);
		if(IsOverridedMethod(m, mE, cctx)) {
			(*outM) = mE;
			ret = true;
			break;
		}
	}
	DeleteCallContext(cctx);
	return ret;
}

Vector* GetGenericInterfaceListClass(Class* self) {
	Vector* ret = NewVector();
	for(int i=0; i<self->Implements->Length; i++) {
		GenericType* ginter = AtVector(self->Implements, i);
		Vector* inner = GetGenericInterfaceTreeInterface(TYPE2INTERFACE(GENERIC2TYPE(ginter)));
		MergeVector(ret, inner);
		PushVector(ret, ginter);
		DeleteVector(inner, VectorDeleterOfNull);
	}
	return ret;
}

Vector* GetGenericInterfaceTreeClass(Class* self) {
	Class* ptr = self;
	Vector* ret = NewVector();
	do {
		Vector* v = GetGenericInterfaceListClass(ptr);
		MergeVector(v, ret);
		DeleteVector(v, VectorDeleterOfNull);
		if(ptr->SuperClass == NULL) {
			break;
		}
		ptr = TYPE2CLASS(GENERIC2TYPE(ptr->SuperClass));
	} while(ptr != NULL);
	return ret;
}

Vector* GetInterfaceListClass(Class* self) {
	Vector* ret = NewVector();
	Vector* c = GetGenericInterfaceListClass(self);
	for(int i=0; i<c->Length; i++) {
		GenericType* gt = AtVector(c, i);
		PushVector(ret, TYPE2INTERFACE(GENERIC2TYPE(gt)));
	}
	DeleteVector(c, VectorDeleterOfNull);
	return ret;
}

Vector* GetInterfaceTreeClass(Class* self) {
	Vector* ret = NewVector();
	Vector* c = GetGenericInterfaceTreeClass(self);
	for(int i=0; i<c->Length; i++) {
		GenericType* gt = AtVector(c, i);
		PushVector(ret, TYPE2INTERFACE(GENERIC2TYPE(gt)));
	}
	DeleteVector(c, VectorDeleterOfNull);
	return ret;
}

GenericType* FindInterfaceTypeClass(Class* self, Type* tinter, GenericType** out_baseline) {
	assert(tinter->Tag == TYPE_INTERFACE_T);
	(*out_baseline) = NULL;
	//実装インターフェイス一覧から同じのを探す
	GenericType* ret = NULL;
	GenericType* out = NULL;
	Class* ptr = self;
	do {
		if (ptr->SuperClass == NULL) {
			break;
		}
		bool found = false;
		//Vector* gimpl_list = GetGenericInterfaceListClass(ptr);
		Vector* gimpl_list = ptr->Implements;
		for (int i = 0; i < gimpl_list->Length; i++) {
			GenericType* gimpl = AtVector(gimpl_list, i);
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
		ptr = TYPE2CLASS(GENERIC2TYPE(ptr->SuperClass));
	} while (ptr != NULL);
	return ret;
}

//private
static bool IsContainsFieldClassImpl(Vector* fields, Field* f) {
	for(int i=0; i<fields->Length; i++) {
		Field* e = (Field*)AtVector(fields, i);
		if(e == f) {
			return true;
		}
	}
	return false;
}

static bool IsContainsPropertyClassImpl(Vector* props, Property* p) {
	for(int i=0; i<props->Length; i++) {
		Property* e = (Property*)AtVector(props, i);
		if(e == p) {
			return true;
		}
	}
	return false;
}