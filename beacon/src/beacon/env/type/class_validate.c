#include "class_validate.h"
#include "../TYPE_IMPL.h"
#include "../generic_type.h"
#include "../property.h"
#include "../constructor.h"
#include "../parameter.h"
#include "../type_parameter.h"
#include "../field.h"
#include "class_impl.h"
static bool IsValidFieldClassImpl(Vector* field_vec, Field** out);
static bool IsValidPropertyClassImpl(Vector* prop_vec, Property** out);
static bool methods_is_all_abstract(Vector* v);

bool IsImplementInterfaceMethodValidClass(class_* cls, Method** out) {
	(*out) = NULL;
	bool contains = true;
	#if defined(DEBUG)
	const char* csupername = Ref2Str(cls->namev);
	if(cls->namev == InternString("AdditiveOperator")) {
		int a = 0;
	}
	#endif
	//全ての実装インターフェイスを取得する
	Vector* inter_list = GetInterfaceTreeClass(cls);
	Vector* methods = FlattenMethodInterfaceList(inter_list);
	if(inter_list->Length == 0 || cls->is_abstract) {
		DeleteVector(inter_list, VectorDeleterOfNull);
		DeleteVector(methods, VectorDeleterOfNull);
		return true;
	}
	for(int i=0; i<methods->Length; i++) {
		Method* m = AtVector(methods, i);
		Vector* methods = FindTreeMethodClass(cls, m);
		if(methods->Length == 0 || methods_is_all_abstract(methods)) {
			(*out) = m;
			contains = false;
			DeleteVector(methods, VectorDeleterOfNull);
			break;
		}
		DeleteVector(methods, VectorDeleterOfNull);
	}
	DeleteVector(inter_list, VectorDeleterOfNull);
	DeleteVector(methods, VectorDeleterOfNull);
	return contains;
}

bool IsImplementInterfacePropertyValidClass(class_* cls, Property** out) {
	(*out) = NULL;
	//全ての実装インターフェイスを取得する
	Vector* gimpl_list = GetGenericInterfaceListClass(cls);
	if(gimpl_list->Length == 0 || cls->is_abstract) {
		DeleteVector(gimpl_list, VectorDeleterOfNull);
		return true;
	}
	//全てのインターフェイスに
	for(int i=0;i<gimpl_list->Length; i++) {
		GenericType* e = AtVector(gimpl_list, i);
		interface_* inter = TYPE2INTERFACE(GENERIC2TYPE(e));
		bool valid = true;
		for(int j=0; j<inter->prop_list->Length; j++) {
			int temp = 0;
			Property* decl = AtVector(inter->prop_list, j);
			Property* impl = FindPropertyClass(cls, decl->Name, &temp);
			if(temp == -1) {
				(*out) = decl;
				DeleteVector(gimpl_list, VectorDeleterOfNull);
				return false;
			} else {
				if(DistanceGenericType(decl->GType, impl->GType, NULL) != 0) {
					(*out) = decl;
					DeleteVector(gimpl_list, VectorDeleterOfNull);
					return false;
				}
				if(decl->Set->Access != impl->Set->Access ||
				   decl->Get->Access != impl->Get->Access) {
					(*out) = decl;
					DeleteVector(gimpl_list, VectorDeleterOfNull);
					return false;
				}
			}
		}
	}
	DeleteVector(gimpl_list, VectorDeleterOfNull);
	return true;
}

bool IsImplementAbstractClassValidClass(class_* cls, Method** out) {
	(*out) = NULL;
	//これ自体が抽象クラス
	if(cls->is_abstract) {
		return true;
	}
	//Objectクラス
	GenericType* gsuper = cls->super_class;
	if(gsuper == NULL) {
		return true;
	}
	class_* csuper = TYPE2CLASS(GENERIC2TYPE(gsuper));
	//親が具象クラスならtrue
	if(!csuper->is_abstract) {
		return true;
	}
	#if defined(DEBUG)
	const char* csupername = Ref2Str(csuper->namev);
	if(cls->namev == InternString("Concrete")) {
		int a = 0;
	}
	#endif
	bool ret = true;
	for(int i=0; i<csuper->method_list->Length; i++) {
		Method* me = AtVector(csuper->method_list, i);
		#if defined(DEBUG)
		const char* mename = Ref2Str(me->Name);
		#endif
		if(!IsAbstractModifier(me->Modifier)) { continue; }
		Vector* methods = FindTreeMethodClass(cls, me);
		if(methods->Length == 0 || methods_is_all_abstract(methods)) {
		   (*out) = me;
		   ret = false;
		   DeleteVector(methods, VectorDeleterOfNull);
		   break;
		}
		DeleteVector(methods, VectorDeleterOfNull);
	}
	return ret;
}

bool IsValidFieldClass(class_* cls, Field** out) {
	return IsValidFieldClassImpl(cls->field_list, out) &&
		   IsValidFieldClassImpl(cls->sfield_list, out);
}

bool IsValidPropertyClass(class_* self, Property** out) {
	return IsValidPropertyClassImpl(self->prop_list, out) &&
	       IsValidPropertyClassImpl(self->sprop_list, out);
}

bool IsMethodParameterValidClass(class_* cls, Method** out_method, StringView* out_name) {
	(*out_name) = ZERO_VIEW;
	for(int i=0; i<cls->method_list->Length; i++) {
		Method* m = (Method*)AtVector(cls->method_list, i);
		if(IsOverwrappedParameterName(m->Parameters, out_name)) {
			(*out_method) = m;
			return false;
		}
	}
	for(int i=0; i<cls->smethod_list->Length; i++) {
		Method* m = (Method*)AtVector(cls->smethod_list, i);
		if(IsOverwrappedParameterName(m->Parameters, out_name)) {
			(*out_method) = m;
			return false;
		}
	}
	return true;
}

bool IsConstructorParameterValidClass(class_* self, Constructor** out_ctor, StringView* out_name) {
	for(int i=0; i<self->constructor_list->Length; i++) {
		Constructor* ctor = (Constructor*)AtVector(self->constructor_list, i);
		if(IsOverwrappedParameterName(ctor->Parameters, out_name)) {
			(*out_ctor) = ctor;
			return false;
		}
	}
	return true;
}

bool IsTypeParameterValidClass(class_* self, StringView* out_name) {
	return !IsOverwrappedTypeParameterName(self->GetParameterListType, out_name);
}

bool IsMethodTypeParameterValidClass(class_* self, Method** out_method, StringView* out_name) {
	(*out_name) = ZERO_VIEW;
	for(int i=0; i<self->method_list->Length; i++) {
		Method* m = (Method*)AtVector(self->method_list, i);
		if(IsOverwrappedTypeParameterName(m->TypeParameters, out_name)) {
			(*out_method) = m;
			return false;
		}
	}
	for(int i=0; i<self->smethod_list->Length; i++) {
		Method* m = (Method*)AtVector(self->smethod_list, i);
		if(IsOverwrappedTypeParameterName(m->TypeParameters, out_name)) {
			(*out_method) = m;
			return false;
		}
	}
	return true;
}
//private
static bool IsValidFieldClassImpl(Vector* field_vec, Field** out) {
	(*out) = NULL;
	bool ret = true;
	for(int i=0; i<field_vec->Length; i++) {
		Field* f = (Field*)AtVector(field_vec, i);
		for(int j=0; j<field_vec->Length; j++) {
			Field* fE = (Field*)AtVector(field_vec, j);
			if(f == fE) { continue; }
			if(f->namev == fE->namev) {
				ret = false;
				(*out) = fE;
				break;
			}
		}
	}
	return ret;
}

static bool IsValidPropertyClassImpl(Vector* prop_vec, Property** out) {
	(*out) = NULL;
	bool ret = true;
	for(int i=0; i<prop_vec->Length; i++) {
		Property* p = (Property*)AtVector(prop_vec, i);
		for(int j=0; j<prop_vec->Length; j++) {
			Property* pE = (Property*)AtVector(prop_vec, j);
			if(i == j) { continue; }
			if(p->Name == pE->Name) {
				ret = false;
				(*out) = p;
				break;
			}
		}
	}
	return ret;
}

static bool methods_is_all_abstract(Vector* v) {
	for(int i=0; i<v->Length; i++) {
		Method* e = AtVector(v, i);
		#if defined(DEBUG)
		const char* tyname = Ref2Str(GetTypeName(e->Parent));
		#endif
		if(!IsAbstractModifier(e->Modifier)) {
			return false;
		}
	}
	return true;
}