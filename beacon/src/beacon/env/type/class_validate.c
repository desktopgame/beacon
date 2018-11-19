#include "class_validate.h"
#include "../TYPE_IMPL.h"
#include "../generic_type.h"
#include "../property.h"
#include "../constructor.h"
#include "../parameter.h"
#include "../type_parameter.h"
#include "../field.h"
#include "class_impl.h"
static bool IsValidFieldClassImpl(Vector* field_vec, bc_Field** out);
static bool IsValidPropertyClassImpl(Vector* prop_vec, bc_Property** out);
static bool methods_is_all_abstract(Vector* v);

bool bc_IsImplementInterfaceMethodValidClass(bc_Class* cls, bc_Method** out) {
	(*out) = NULL;
	bool contains = true;
	#if defined(DEBUG)
	const char* csupername = Ref2Str(cls->Name);
	if(cls->Name == InternString("AdditiveOperator")) {
		int a = 0;
	}
	#endif
	//全ての実装インターフェイスを取得する
	Vector* inter_list = bc_GetInterfaceTreeClass(cls);
	Vector* methods = bc_FlattenMethodInterfaceList(inter_list);
	if(inter_list->Length == 0 || cls->IsAbstract) {
		DeleteVector(inter_list, VectorDeleterOfNull);
		DeleteVector(methods, VectorDeleterOfNull);
		return true;
	}
	for(int i=0; i<methods->Length; i++) {
		bc_Method* m = AtVector(methods, i);
		Vector* methods = bc_FindTreeMethodClass(cls, m);
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

bool bc_IsImplementInterfacePropertyValidClass(bc_Class* cls, bc_Property** out) {
	(*out) = NULL;
	//全ての実装インターフェイスを取得する
	Vector* gimpl_list = bc_GetGenericInterfaceListClass(cls);
	if(gimpl_list->Length == 0 || cls->IsAbstract) {
		DeleteVector(gimpl_list, VectorDeleterOfNull);
		return true;
	}
	//全てのインターフェイスに
	for(int i=0;i<gimpl_list->Length; i++) {
		bc_GenericType* e = AtVector(gimpl_list, i);
		bc_Interface* inter = BC_TYPE2INTERFACE(bc_GENERIC2TYPE(e));
		bool valid = true;
		for(int j=0; j<inter->Properties->Length; j++) {
			int temp = 0;
			bc_Property* decl = AtVector(inter->Properties, j);
			bc_Property* impl = bc_FindPropertyClass(cls, decl->Name, &temp);
			if(temp == -1) {
				(*out) = decl;
				DeleteVector(gimpl_list, VectorDeleterOfNull);
				return false;
			} else {
				if(bc_DistanceGenericType(decl->GType, impl->GType, NULL) != 0) {
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

bool bc_IsImplementAbstractClassValidClass(bc_Class* cls, bc_Method** out) {
	(*out) = NULL;
	//これ自体が抽象クラス
	if(cls->IsAbstract) {
		return true;
	}
	//Objectクラス
	bc_GenericType* gsuper = cls->SuperClass;
	if(gsuper == NULL) {
		return true;
	}
	bc_Class* csuper = BC_TYPE2CLASS(bc_GENERIC2TYPE(gsuper));
	//親が具象クラスならtrue
	if(!csuper->IsAbstract) {
		return true;
	}
	#if defined(DEBUG)
	const char* csupername = Ref2Str(csuper->Name);
	#endif
	bool ret = true;
	for(int i=0; i<csuper->Methods->Length; i++) {
		bc_Method* me = AtVector(csuper->Methods, i);
		#if defined(DEBUG)
		const char* mename = Ref2Str(me->Name);
		#endif
		if(!bc_IsAbstractModifier(me->Modifier)) { continue; }
		Vector* methods = bc_FindTreeMethodClass(cls, me);
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

bool bc_IsValidFieldClass(bc_Class* cls, bc_Field** out) {
	return IsValidFieldClassImpl(cls->Fields, out) &&
		   IsValidFieldClassImpl(cls->StaticFields, out);
}

bool bc_IsValidPropertyClass(bc_Class* self, bc_Property** out) {
	return IsValidPropertyClassImpl(self->Properties, out) &&
	       IsValidPropertyClassImpl(self->StaticProperties, out);
}

bool bc_IsMethodParameterValidClass(bc_Class* cls, bc_Method** out_method, StringView* out_name) {
	(*out_name) = ZERO_VIEW;
	for(int i=0; i<cls->Methods->Length; i++) {
		bc_Method* m = (bc_Method*)AtVector(cls->Methods, i);
		if(bc_IsOverwrappedParameterName(m->Parameters, out_name)) {
			(*out_method) = m;
			return false;
		}
	}
	for(int i=0; i<cls->StaticMethods->Length; i++) {
		bc_Method* m = (bc_Method*)AtVector(cls->StaticMethods, i);
		if(bc_IsOverwrappedParameterName(m->Parameters, out_name)) {
			(*out_method) = m;
			return false;
		}
	}
	return true;
}

bool bc_IsConstructorParameterValidClass(bc_Class* self, bc_Constructor** out_ctor, StringView* out_name) {
	for(int i=0; i<self->Constructors->Length; i++) {
		bc_Constructor* ctor = (bc_Constructor*)AtVector(self->Constructors, i);
		if(bc_IsOverwrappedParameterName(ctor->Parameters, out_name)) {
			(*out_ctor) = ctor;
			return false;
		}
	}
	return true;
}

bool bc_IsTypeParameterValidClass(bc_Class* self, StringView* out_name) {
	return !bc_IsOverwrappedTypeParameterName(self->TypeParameters, out_name);
}

bool bc_IsMethodTypeParameterValidClass(bc_Class* self, bc_Method** out_method, StringView* out_name) {
	(*out_name) = ZERO_VIEW;
	for(int i=0; i<self->Methods->Length; i++) {
		bc_Method* m = (bc_Method*)AtVector(self->Methods, i);
		if(bc_IsOverwrappedTypeParameterName(m->TypeParameters, out_name)) {
			(*out_method) = m;
			return false;
		}
	}
	for(int i=0; i<self->StaticMethods->Length; i++) {
		bc_Method* m = (bc_Method*)AtVector(self->StaticMethods, i);
		if(bc_IsOverwrappedTypeParameterName(m->TypeParameters, out_name)) {
			(*out_method) = m;
			return false;
		}
	}
	return true;
}
//private
static bool IsValidFieldClassImpl(Vector* field_vec, bc_Field** out) {
	(*out) = NULL;
	bool ret = true;
	for(int i=0; i<field_vec->Length; i++) {
		bc_Field* f = (bc_Field*)AtVector(field_vec, i);
		for(int j=0; j<field_vec->Length; j++) {
			bc_Field* fE = (bc_Field*)AtVector(field_vec, j);
			if(f == fE) { continue; }
			if(f->Name 	== fE->Name) {
				ret = false;
				(*out) = fE;
				break;
			}
		}
	}
	return ret;
}

static bool IsValidPropertyClassImpl(Vector* prop_vec, bc_Property** out) {
	(*out) = NULL;
	bool ret = true;
	for(int i=0; i<prop_vec->Length; i++) {
		bc_Property* p = (bc_Property*)AtVector(prop_vec, i);
		for(int j=0; j<prop_vec->Length; j++) {
			bc_Property* pE = (bc_Property*)AtVector(prop_vec, j);
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
		bc_Method* e = AtVector(v, i);
		#if defined(DEBUG)
		const char* tyname = Ref2Str(bc_GetTypeName(e->Parent));
		#endif
		if(!bc_IsAbstractModifier(e->Modifier)) {
			return false;
		}
	}
	return true;
}