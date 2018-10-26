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

Field* FindFieldClass(class_* self, StringView namev, int* outIndex) {
	(*outIndex) = -1;
	for (int i = 0; i < self->field_list->Length; i++) {
		VectorItem e = AtVector(self->field_list, i);
		Field* f = (Field*)e;
		if (namev == f->namev) {
			(*outIndex) = (CountAllFieldClass(self) - self->field_list->Length) + i;
			return f;
		}
	}
	return NULL;
}

Field* FindTreeFieldClass(class_ * self, StringView namev, int * outIndex) {
	class_* pointee = self;
	do {
		Field* f = FindFieldClass(pointee, namev, outIndex);
		if (f != NULL) {
			return f;
		}
		generic_type* supergtype = pointee->super_class;
		if(supergtype == NULL) {
			break;
		}
		pointee = supergtype->core_type->u.class_;
	} while (pointee != NULL);
	return NULL;
}

Field* FindSFieldClass(class_ * self, StringView namev, int * outIndex) {
	(*outIndex) = -1;
	for (int i = 0; i < self->sfield_list->Length; i++) {
		VectorItem e = AtVector(self->sfield_list, i);
		Field* f = (Field*)e;
		if (namev == f->namev) {
			(*outIndex) = (CountAllSFieldClass(self) - self->sfield_list->Length) + i;
			return f;
		}
	}
	return NULL;
}

Field* FindTreeSFieldClass(class_ * self, StringView namev, int * outIndex) {
	class_* pointee = self;
	do {
		Field* f = FindSFieldClass(pointee, namev, outIndex);
		if (f != NULL) {
			return f;
		}
		if(pointee->super_class == NULL) {
			break;
		}
		pointee = pointee->super_class->core_type->u.class_;
	} while (pointee != NULL);
	return NULL;
}

Field* GetFieldClass(class_ * self, int index) {
	assert(index >= 0);
	int all = CountAllFieldClass(self);
	if (index >= (all - self->field_list->Length) &&
		index < all) {
		return AtVector(self->field_list, self->field_list->Length - (all - index));
	}
	return GetFieldClass(self->super_class->core_type->u.class_, index);
}

Field* GetSFieldClass(class_ * self, int index) {
	assert(index >= 0);
	int all = CountAllSFieldClass(self);
	if (index >= (all - self->sfield_list->Length) &&
		index < all) {
		return AtVector(self->sfield_list, self->sfield_list->Length - (all - index));
	}
	return GetSFieldClass(self->super_class->core_type->u.class_, index);
}

bool IsContainsFieldClass(class_* self, Field* f) {
	return IsContainsFieldClassImpl(self->field_list, f);
}

bool IsContainsSFieldClass(class_* self, Field* f) {
	return IsContainsFieldClassImpl(self->sfield_list, f);
}

bool IsAccessibleFieldClass(class_* self, Field* f) {
	assert(f != NULL);
	if(f->access == ACCESS_PUBLIC_T) {
		return true;
	}
	if(f->access == ACCESS_PRIVATE_T) {
		return self == TYPE2CLASS(f->parent);
	}
	type* ty = self->parent;
	class_* fcl = TYPE2CLASS(f->parent);
	while(true) {
		class_* c = TYPE2CLASS(ty);
		if(c == fcl) {
			return true;
		}
		//次へ
		if(c->super_class == NULL) {
			break;
		}
		ty = c->super_class->core_type;
	}
	return false;
}



bool IsContainsPropertyClass(class_* self, Property* p) {
	return IsContainsPropertyClassImpl(self->prop_list, p);
}

bool IsContainsSPropertyClass(class_* self, Property* p) {
	return IsContainsPropertyClassImpl(self->sprop_list, p);
}

bool IsAccessiblePropertyClass(class_* self, Property* p) {
	assert(p != NULL);
	if(p->Access == ACCESS_PUBLIC_T) {
		return true;
	}
	if(p->Access == ACCESS_PRIVATE_T) {
		return self == TYPE2CLASS(p->Parent);
	}
	type* ty = self->parent;
	class_* fcl = TYPE2CLASS(p->Parent);
	while(true) {
		class_* c = TYPE2CLASS(ty);
		if(c == fcl) {
			return true;
		}
		//次へ
		if(c->super_class == NULL) {
			break;
		}
		ty = c->super_class->core_type;
	}
	return false;
}

bool IsAccessiblePropertyAccessorClass(class_* self, PropertyBody* pb) {
	assert(pb != NULL);
	if(pb->Access == ACCESS_PUBLIC_T) {
		return true;
	}
	if(pb->Access == ACCESS_PRIVATE_T) {
		return self == TYPE2CLASS(pb->Parent->Parent);
	}
	type* ty = self->parent;
	class_* fcl = TYPE2CLASS(pb->Parent->Parent);
	while(true) {
		class_* c = TYPE2CLASS(ty);
		if(c == fcl) {
			return true;
		}
		//次へ
		if(c->super_class == NULL) {
			break;
		}
		ty = c->super_class->core_type;
	}
	return false;
}

int GetFieldByPropertyClass(class_* self, Property* p) {
	int temp = -1;
	assert(p->SourceRef != NULL);
	if(IsStaticModifier(p->Modifier)) {
		FindSFieldClass(self, p->SourceRef->namev, &temp);
	} else {
		FindFieldClass(self, p->SourceRef->namev, &temp);
	}
	return temp;
}

Property* GetPropertyClass(class_* self, int index) {
	assert(index >= 0);
	int all = CountAllPropertyClass(self);
	if (index >= (all - self->prop_list->Length) &&
		index < all) {
		return AtVector(self->prop_list, self->prop_list->Length - (all - index));
	}
	return GetPropertyClass(self->super_class->core_type->u.class_, index);
}

Property* GetSPropertyClass(class_* self, int index) {
	assert(index >= 0);
	int all = CountAllSPropertyClass(self);
	if (index >= (all - self->sprop_list->Length) &&
		index < all) {
		return AtVector(self->sprop_list, self->sprop_list->Length - (all - index));
	}
	return GetPropertyClass(self->super_class->core_type->u.class_, index);
}

Property* FindPropertyClass(class_* self, StringView namev, int* outIndex) {
	(*outIndex) = -1;
	for (int i = 0; i < self->prop_list->Length; i++) {
		VectorItem e = AtVector(self->prop_list, i);
		Property* p = (Property*)e;
		if (namev == p->Name) {
			(*outIndex) = (CountAllPropertyClass(self) - self->prop_list->Length) + i;
			return p;
		}
	}
	return NULL;
}

Property* FindTreePropertyClass(class_* self, StringView namev, int* outIndex) {
	class_* pointee = self;
	do {
		Property* p = FindPropertyClass(pointee, namev, outIndex);
		if (p != NULL) {
			return p;
		}
		generic_type* supergtype = pointee->super_class;
		if(supergtype == NULL) {
			break;
		}
		pointee = supergtype->core_type->u.class_;
	} while (pointee != NULL);
	return NULL;
}

Property* FindSPropertyClass(class_* self, StringView namev, int* outIndex) {
	(*outIndex) = -1;
	for (int i = 0; i < self->sprop_list->Length; i++) {
		VectorItem e = AtVector(self->sprop_list, i);
		Property* p = (Property*)e;
		if (namev == p->Name) {
			(*outIndex) = (CountAllSPropertyClass(self) - self->sprop_list->Length) + i;
			return p;
		}
	}
	return NULL;
}

Property* FindTreeSPropertyClass(class_* self, StringView namev, int* outIndex) {
	class_* pointee = self;
	do {
		Property* p = FindSPropertyClass(pointee, namev, outIndex);
		if (p != NULL) {
			return p;
		}
		generic_type* supergtype = pointee->super_class;
		if(supergtype == NULL) {
			break;
		}
		pointee = supergtype->core_type->u.class_;
	} while (pointee != NULL);
	return NULL;
}



Constructor* RFindConstructorClass(class_ * self, Vector * args, Vector* typeargs, Frame* fr, int* outIndex) {
	return MetaScopedRFindConstructor(self, self->constructor_list, args, typeargs, fr, outIndex);
}

Constructor* ILFindConstructorClass(class_ * self, Vector * args, Enviroment * env, CallContext* cctx, int* outIndex) {
	//	Vector* v = meta_find_constructors(self, args, env, ilctx);
	//	(*outIndex) = -1;
	//	return class_find_constructor_impl(v, args, env, ilctx, outIndex);
	Constructor* ctor = MetaScopedILFindConstructor(self, self->constructor_list, args, env, cctx, outIndex);
	return ctor;
}

Constructor * ILFindEmptyConstructorClass(class_ * self, Enviroment * env, CallContext* cctx, int * outIndex) {
	Vector* emptyArgs = NewVector();
	Constructor* ret = ILFindConstructorClass(self, emptyArgs, env, cctx, outIndex);
	DeleteVector(emptyArgs, VectorDeleterOfNull);
	return ret;
}



Method * ILFindMethodClass(class_ * self, StringView namev, Vector * args, Enviroment * env, CallContext* cctx, int * outIndex) {
	(*outIndex) = -1;
	CreateVTableClass(self);
	#if defined(DEBUG)
	const char* str = Ref2Str(self->namev);
	#endif
	//assert(self->vt->elements->Length > 0);
	Method* ret = NULL;
	if((ret = MetaScopedILFindMethod(self, self->vt->Elements, namev, args, env, cctx, outIndex))
	   != NULL) {
		   return ret;
	}
	if((ret = MetaScopedILFindMethod(self, self->method_list, namev, args, env, cctx, outIndex))
	   != NULL) {
		   return ret;
	}
	if((ret = MetaScopedILFindMethod(self, self->smethod_list, namev, args, env, cctx, outIndex))
	   != NULL) {
		   return ret;
	}
	return NULL;
}

Method* GFindMethodClass(class_* self, StringView namev, Vector* gargs, int* outIndex) {
	(*outIndex) = -1;
	CreateVTableClass(self);
	//assert(self->vt->elements->Length > 0);
	Method* ret = NULL;
	if((ret = MetaScopedGFindMethod(self, self->vt->Elements, namev, gargs, outIndex))
	   != NULL) {
		   return ret;
	}
	if((ret = MetaScopedGFindMethod(self, self->method_list, namev, gargs, outIndex))
	   != NULL) {
		   return ret;
	}
	if((ret = MetaScopedGFindMethod(self, self->smethod_list, namev, gargs, outIndex))
	   != NULL) {
		   return ret;
	}
	return NULL;
}

Method* GFindEqMethodClass(class_* self, int* outIndex) {
	Vector* gargs = NewVector();
	PushVector(gargs, TYPE_OBJECT->generic_self);
	Method* ret = GFindMethodClass(self, InternString("equals"), gargs, outIndex);
	DeleteVector(gargs, VectorDeleterOfNull);
	return ret;
}

Method * ILFindSMethodClass(class_ * self, StringView namev, Vector * args, Enviroment * env, CallContext* cctx, int * outIndex) {
	#if defined(DEBUG)
	const char* str = Ref2Str(namev);
	#endif
	(*outIndex) = -1;
	CreateVTableClass(self);
	int temp = 0;
	Method* ret = MetaILFindMethod(self->smethod_list, namev, args, env, cctx, &temp);
//	temp += (CountAllSMethodClass(self) - self->smethod_list->Length);
	(*outIndex) = temp;
	return ret;
}

Method* GFindSMethodClass(class_* self, StringView namev, Vector* gargs, int* outIndex) {
	(*outIndex) = -1;
	CreateVTableClass(self);
	int temp = 0;
	Method* ret = MetaGFindMethod(self->smethod_list, namev, gargs, &temp);
//	temp += (CountAllSMethodClass(self) - self->smethod_list->Length);
	(*outIndex) = temp;
	return ret;
}

Method * GetMethodClass(Object * o, int index) {
	assert(index >= 0);
	#if defined(DEBUG)
	const char* name = GetObjectName(o);
	#endif
	if(o->Tag == OBJECT_NULL_T) {
		o->VPtr = TYPE2CLASS(TYPE_OBJECT)->vt;
	}
	VTable* vx = (o->VPtr);
	return (Method*)AtVector(vx->Elements, index);
}

Method * GetSMethodClass(class_* self, int index) {
	assert(index >= 0);
	/*
	//class_* self = o->classz;
	int all = CountAllSMethodClass(self);
	if (index >= (all - self->smethod_list->Length) &&
		index < all) {
		return AtVector(self->smethod_list, self->smethod_list->Length - (all - index));
	}
	return GetSMethodClass(self->super_class->core_type->u.class_, index);
	//*/
	return AtVector(self->smethod_list, index);
}

Method * GetImplMethodClass(class_ * self, type * interType, int interMIndex) {
	#if defined(DEBUG)
	const char* str = Ref2Str(self->namev);
	#endif
	assert(self->vt_vec->Length > 0);
	Vector* tbl = GetGenericInterfaceTreeClass(self);
	//指定のインターフェイスが
	//このクラスにおいて何番目かを調べる
	int declIndex = -1;
	for (int i = 0; i < tbl->Length; i++) {
		generic_type* e = AtVector(tbl, i);
		interface_* inter = e->core_type->u.interface_;
		if (inter == interType->u.interface_) {
			declIndex = i;
			break;
		}
	}
	//仮想関数テーブルの一覧から引く
	assert(declIndex != -1);
	DeleteVector(tbl, VectorDeleterOfNull);
	VTable* vtAt = AtVector(self->vt_vec, declIndex);
	return AtVector(vtAt->Elements, interMIndex);
}




OperatorOverload* GFindOperatorOverloadClass(class_* self, OperatorType type, Vector* args, Enviroment* env, CallContext* cctx, int* outIndex) {
	(*outIndex) = -1;
	OperatorOverload* ret = NULL;
	CreateOperatorVTClass(self);
	for(int i=0; i<self->ovt->Operators->Length; i++) {
		OperatorOverload* operator_ov = AtVector(self->ovt->Operators, i);
		if(operator_ov->Type != type) {
			continue;
		}
		bool nomatch = false;
		int score = 1024;
		int sum = 0;
		Vector* params = operator_ov->Parameters;
		for(int j=0; j<params->Length; j++) {
			Parameter* param = AtVector(params, j);
			generic_type* arg = AtVector(args, j);
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

OperatorOverload* ILFindOperatorOverloadClass(class_* self, OperatorType type, Vector* args, Enviroment* env, CallContext* cctx, int* outIndex) {
	Vector* gargs =NewVector();
	for(int i=0; i<args->Length; i++) {
		il_factor* ilfact = (il_factor*)AtVector(args,i);
		generic_type* g = EvalILFactor(ilfact, env, cctx);
		PushVector(gargs, g);
	}
	OperatorOverload* ret = GFindOperatorOverloadClass(self, type, gargs, env, cctx, outIndex);
	DeleteVector(gargs, VectorDeleterOfNull);
	return ret;
}

OperatorOverload* ArgFindOperatorOverloadClass(class_* self, OperatorType type, Vector* args, Enviroment* env, CallContext* cctx, int* outIndex) {
	Vector* gargs =NewVector();
	for(int i=0; i<args->Length; i++) {
		//il_factor* ilfact = (il_factor*)AtVector(args,i);
		ILArgument* ilarg = (ILArgument*)AtVector(args, i);
		il_factor* ilfact = ilarg->Factor;
		generic_type* g = EvalILFactor(ilfact, env, cctx);
		PushVector(gargs, g);
	}
	OperatorOverload* ret = GFindOperatorOverloadClass(self, type, gargs, env, cctx, outIndex);
	DeleteVector(gargs, VectorDeleterOfNull);
	return ret;
}

OperatorOverload* GetOperatorOverloadClass(class_* self, int index) {
	return AtVector(self->ovt->Operators, index);
}

Vector* FindTreeMethodClass(class_* self, Method* m) {
	assert(self != NULL);
	assert(m != NULL);
	class_* ptr = self;
	Vector* ret = NewVector();
	#if defined(DEBUG)
	const char* ptrname = Ref2Str(ptr->namev);
	#endif
	do {
		Method* tmp = NULL;
		if(IsContainsMethod(ptr->method_list, m, &tmp)) {
			PushVector(ret, tmp);
		}
		//親クラスへ
		if(ptr->super_class != NULL) {
			ptr = ptr->super_class->core_type->u.class_;
		} else {
			ptr = NULL;
		}
	} while(ptr != NULL);
	return ret;
}

bool IsContainsMethod(Vector* method_list, Method* m, Method** outM) {
	assert(!IsStaticModifier(m->Modifier));
	(*outM) = NULL;
	bool ret = false;
	CallContext* cctx = NewCallContext(CALL_DECL_T);
	cctx->Scope = m->Parent->location;
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

Vector* GetGenericInterfaceListClass(class_* self) {
	Vector* ret = NewVector();
	for(int i=0; i<self->impl_list->Length; i++) {
		generic_type* ginter = AtVector(self->impl_list, i);
		Vector* inner = GetGenericInterfaceTreeInterface(TYPE2INTERFACE(GENERIC2TYPE(ginter)));
		MergeVector(ret, inner);
		PushVector(ret, ginter);
		DeleteVector(inner, VectorDeleterOfNull);
	}
	return ret;
}

Vector* GetGenericInterfaceTreeClass(class_* self) {
	class_* ptr = self;
	Vector* ret = NewVector();
	do {
		Vector* v = GetGenericInterfaceListClass(ptr);
		MergeVector(v, ret);
		DeleteVector(v, VectorDeleterOfNull);
		if(ptr->super_class == NULL) {
			break;
		}
		ptr = TYPE2CLASS(GENERIC2TYPE(ptr->super_class));
	} while(ptr != NULL);
	return ret;
}

Vector* GetInterfaceListClass(class_* self) {
	Vector* ret = NewVector();
	Vector* c = GetGenericInterfaceListClass(self);
	for(int i=0; i<c->Length; i++) {
		generic_type* gt = AtVector(c, i);
		PushVector(ret, TYPE2INTERFACE(GENERIC2TYPE(gt)));
	}
	DeleteVector(c, VectorDeleterOfNull);
	return ret;
}

Vector* GetInterfaceTreeClass(class_* self) {
	Vector* ret = NewVector();
	Vector* c = GetGenericInterfaceTreeClass(self);
	for(int i=0; i<c->Length; i++) {
		generic_type* gt = AtVector(c, i);
		PushVector(ret, TYPE2INTERFACE(GENERIC2TYPE(gt)));
	}
	DeleteVector(c, VectorDeleterOfNull);
	return ret;
}

generic_type* FindInterfaceTypeClass(class_* self, type* tinter, generic_type** out_baseline) {
	assert(tinter->tag == TYPE_INTERFACE_T);
	(*out_baseline) = NULL;
	//実装インターフェイス一覧から同じのを探す
	generic_type* ret = NULL;
	generic_type* out = NULL;
	class_* ptr = self;
	do {
		if (ptr->super_class == NULL) {
			break;
		}
		bool found = false;
		//Vector* gimpl_list = GetGenericInterfaceListClass(ptr);
		Vector* gimpl_list = ptr->impl_list;
		for (int i = 0; i < gimpl_list->Length; i++) {
			generic_type* gimpl = AtVector(gimpl_list, i);
			if (gimpl->core_type == tinter) {
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
		out = ptr->super_class;
		ptr = TYPE2CLASS(GENERIC2TYPE(ptr->super_class));
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