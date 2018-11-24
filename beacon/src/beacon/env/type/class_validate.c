#include "class_validate.h"
#include "../TYPE_IMPL.h"
#include "../generic_type.h"
#include "../property.h"
#include "../constructor.h"
#include "../parameter.h"
#include "../type_parameter.h"
#include "../field.h"
#include "class_impl.h"
static bool IsValidFieldClassImpl(bc_Vector* field_vec, bc_Field** out);
static bool IsValidPropertyClassImpl(bc_Vector* prop_vec, bc_Property** out);
static bool methods_is_all_abstract(bc_Vector* v);

bool bc_IsImplementInterfaceMethodValidClass(bc_Class* cls, bc_Method** out) {
	(*out) = NULL;
	bool contains = true;
	#if defined(DEBUG)
	const char* csupername = bc_Ref2Str(cls->Name);
	if(cls->Name == bc_InternString("AdditiveOperator")) {
		int a = 0;
	}
	#endif
	//全ての実装インターフェイスを取得する
	bc_Vector* inter_list = bc_GetInterfaceTreeClass(cls);
	bc_Vector* methods = bc_FlattenMethodInterfaceList(inter_list);
	if(inter_list->Length == 0 || cls->IsAbstract) {
		bc_DeleteVector(inter_list, bc_VectorDeleterOfNull);
		bc_DeleteVector(methods, bc_VectorDeleterOfNull);
		return true;
	}
	for(int i=0; i<methods->Length; i++) {
		bc_Method* m = bc_AtVector(methods, i);
		bc_Vector* methods = bc_FindTreeMethodClass(cls, m);
		if(methods->Length == 0 || methods_is_all_abstract(methods)) {
			(*out) = m;
			contains = false;
			bc_DeleteVector(methods, bc_VectorDeleterOfNull);
			break;
		}
		bc_DeleteVector(methods, bc_VectorDeleterOfNull);
	}
	bc_DeleteVector(inter_list, bc_VectorDeleterOfNull);
	bc_DeleteVector(methods, bc_VectorDeleterOfNull);
	return contains;
}

bool bc_IsImplementInterfacePropertyValidClass(bc_Class* cls, bc_Property** out) {
	(*out) = NULL;
	//全ての実装インターフェイスを取得する
	bc_Vector* gimpl_list = bc_GetGenericInterfaceListClass(cls);
	if(gimpl_list->Length == 0 || cls->IsAbstract) {
		bc_DeleteVector(gimpl_list, bc_VectorDeleterOfNull);
		return true;
	}
	//全てのインターフェイスに
	for(int i=0;i<gimpl_list->Length; i++) {
		bc_GenericType* e = bc_AtVector(gimpl_list, i);
		bc_Interface* inter = BC_TYPE2INTERFACE(bc_GENERIC2TYPE(e));
		bool valid = true;
		for(int j=0; j<inter->Properties->Length; j++) {
			int temp = 0;
			bc_Property* decl = bc_AtVector(inter->Properties, j);
			bc_Property* impl = bc_FindPropertyClass(cls, decl->Name, &temp);
			if(temp == -1) {
				(*out) = decl;
				bc_DeleteVector(gimpl_list, bc_VectorDeleterOfNull);
				return false;
			} else {
				if(bc_DistanceGenericType(decl->GType, impl->GType, NULL) != 0) {
					(*out) = decl;
					bc_DeleteVector(gimpl_list, bc_VectorDeleterOfNull);
					return false;
				}
				if(decl->Set->Access != impl->Set->Access ||
				   decl->Get->Access != impl->Get->Access) {
					(*out) = decl;
					bc_DeleteVector(gimpl_list, bc_VectorDeleterOfNull);
					return false;
				}
			}
		}
	}
	bc_DeleteVector(gimpl_list, bc_VectorDeleterOfNull);
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
	const char* csupername = bc_Ref2Str(csuper->Name);
	#endif
	bool ret = true;
	for(int i=0; i<csuper->Methods->Length; i++) {
		bc_Method* me = bc_AtVector(csuper->Methods, i);
		#if defined(DEBUG)
		const char* mename = bc_Ref2Str(me->Name);
		#endif
		if(!bc_IsAbstractModifier(BC_MEMBER_MODIFIER(me))) { continue; }
		bc_Vector* methods = bc_FindTreeMethodClass(cls, me);
		if(methods->Length == 0 || methods_is_all_abstract(methods)) {
		   (*out) = me;
		   ret = false;
		   bc_DeleteVector(methods, bc_VectorDeleterOfNull);
		   break;
		}
		bc_DeleteVector(methods, bc_VectorDeleterOfNull);
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

bool bc_IsMethodParameterValidClass(bc_Class* cls, bc_Method** out_method, bc_StringView* out_name) {
	(*out_name) = BC_ZERO_VIEW;
	for(int i=0; i<cls->Methods->Length; i++) {
		bc_Method* m = (bc_Method*)bc_AtVector(cls->Methods, i);
		if(bc_IsOverwrappedParameterName(m->Parameters, out_name)) {
			(*out_method) = m;
			return false;
		}
	}
	for(int i=0; i<cls->StaticMethods->Length; i++) {
		bc_Method* m = (bc_Method*)bc_AtVector(cls->StaticMethods, i);
		if(bc_IsOverwrappedParameterName(m->Parameters, out_name)) {
			(*out_method) = m;
			return false;
		}
	}
	return true;
}

bool bc_IsConstructorParameterValidClass(bc_Class* self, bc_Constructor** out_ctor, bc_StringView* out_name) {
	for(int i=0; i<self->Constructors->Length; i++) {
		bc_Constructor* ctor = (bc_Constructor*)bc_AtVector(self->Constructors, i);
		if(bc_IsOverwrappedParameterName(ctor->Parameters, out_name)) {
			(*out_ctor) = ctor;
			return false;
		}
	}
	return true;
}

bool bc_IsTypeParameterValidClass(bc_Class* self, bc_StringView* out_name) {
	return !bc_IsOverwrappedTypeParameterName(self->TypeParameters, out_name);
}

bool bc_IsMethodTypeParameterValidClass(bc_Class* self, bc_Method** out_method, bc_StringView* out_name) {
	(*out_name) = BC_ZERO_VIEW;
	for(int i=0; i<self->Methods->Length; i++) {
		bc_Method* m = (bc_Method*)bc_AtVector(self->Methods, i);
		if(bc_IsOverwrappedTypeParameterName(m->TypeParameters, out_name)) {
			(*out_method) = m;
			return false;
		}
	}
	for(int i=0; i<self->StaticMethods->Length; i++) {
		bc_Method* m = (bc_Method*)bc_AtVector(self->StaticMethods, i);
		if(bc_IsOverwrappedTypeParameterName(m->TypeParameters, out_name)) {
			(*out_method) = m;
			return false;
		}
	}
	return true;
}
//private
static bool IsValidFieldClassImpl(bc_Vector* field_vec, bc_Field** out) {
	(*out) = NULL;
	bool ret = true;
	for(int i=0; i<field_vec->Length; i++) {
		bc_Field* f = (bc_Field*)bc_AtVector(field_vec, i);
		for(int j=0; j<field_vec->Length; j++) {
			bc_Field* fE = (bc_Field*)bc_AtVector(field_vec, j);
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

static bool IsValidPropertyClassImpl(bc_Vector* prop_vec, bc_Property** out) {
	(*out) = NULL;
	bool ret = true;
	for(int i=0; i<prop_vec->Length; i++) {
		bc_Property* p = (bc_Property*)bc_AtVector(prop_vec, i);
		for(int j=0; j<prop_vec->Length; j++) {
			bc_Property* pE = (bc_Property*)bc_AtVector(prop_vec, j);
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

static bool methods_is_all_abstract(bc_Vector* v) {
	for(int i=0; i<v->Length; i++) {
		bc_Method* e = bc_AtVector(v, i);
		#if defined(DEBUG)
		const char* tyname = bc_Ref2Str(bc_GetTypeName(BC_MEMBER_TYPE(e)));
		#endif
		if(!bc_IsAbstractModifier(BC_MEMBER_MODIFIER(e))) {
			return false;
		}
	}
	return true;
}