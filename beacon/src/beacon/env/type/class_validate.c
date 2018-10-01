#include "class_validate.h"
#include "../TYPE_IMPL.h"
#include "../generic_type.h"
#include "../property.h"
#include "../constructor.h"
#include "../parameter.h"
#include "../type_parameter.h"
#include "../field.h"
#include "class_impl.h"
static bool class_field_validImpl(Vector* field_vec, field** out);
static bool class_property_validImpl(Vector* prop_vec, property** out);
static bool methods_is_all_abstract(Vector* v);

bool class_interface_method_implement_valid(class_* cls, method** out) {
	(*out) = NULL;
	bool contains = true;
	#if defined(DEBUG)
	const char* csupername = Ref2Str(cls->namev);
	if(cls->namev == InternString("AdditiveOperator")) {
		int a = 0;
	}
	#endif
	//全ての実装インターフェイスを取得する
	Vector* inter_list = class_get_interface_tree(cls);
	Vector* methods = interface_method_flatten_list(inter_list);
	if(inter_list->length == 0 || cls->is_abstract) {
		DeleteVector(inter_list, VectorDeleterOfNull);
		DeleteVector(methods, VectorDeleterOfNull);
		return true;
	}
	for(int i=0; i<methods->length; i++) {
		method* m = AtVector(methods, i);
		Vector* methods = class_find_methods_tree(cls, m);
		if(methods->length == 0 || methods_is_all_abstract(methods)) {
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

bool class_interface_property_implement_valid(class_* cls, property** out) {
	(*out) = NULL;
	//全ての実装インターフェイスを取得する
	Vector* gimpl_list = class_get_generic_interface_list(cls);
	if(gimpl_list->length == 0 || cls->is_abstract) {
		DeleteVector(gimpl_list, VectorDeleterOfNull);
		return true;
	}
	//全てのインターフェイスに
	for(int i=0;i<gimpl_list->length; i++) {
		generic_type* e = AtVector(gimpl_list, i);
		interface_* inter = TYPE2INTERFACE(GENERIC2TYPE(e));
		bool valid = true;
		for(int j=0; j<inter->prop_list->length; j++) {
			int temp = 0;
			property* decl = AtVector(inter->prop_list, j);
			property* impl = class_find_property(cls, decl->namev, &temp);
			if(temp == -1) {
				(*out) = decl;
				DeleteVector(gimpl_list, VectorDeleterOfNull);
				return false;
			} else {
				if(DistanceGenericType(decl->gtype, impl->gtype, NULL) != 0) {
					(*out) = decl;
					DeleteVector(gimpl_list, VectorDeleterOfNull);
					return false;
				}
				if(decl->set->access != impl->set->access ||
				   decl->get->access != impl->get->access) {
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

bool class_abstract_class_implement_valid(class_* cls, method** out) {
	(*out) = NULL;
	//これ自体が抽象クラス
	if(cls->is_abstract) {
		return true;
	}
	//Objectクラス
	generic_type* gsuper = cls->super_class;
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
	for(int i=0; i<csuper->method_list->length; i++) {
		method* me = AtVector(csuper->method_list, i);
		#if defined(DEBUG)
		const char* mename = Ref2Str(me->namev);
		#endif
		if(!IsAbstractModifier(me->modifier)) { continue; }
		Vector* methods = class_find_methods_tree(cls, me);
		if(methods->length == 0 || methods_is_all_abstract(methods)) {
		   (*out) = me;
		   ret = false;
		   DeleteVector(methods, VectorDeleterOfNull);
		   break;
		}
		DeleteVector(methods, VectorDeleterOfNull);
	}
	return ret;
}

bool class_field_valid(class_* cls, field** out) {
	return class_field_validImpl(cls->field_list, out) &&
		   class_field_validImpl(cls->sfield_list, out);
}

bool class_property_valid(class_* self, property** out) {
	return class_property_validImpl(self->prop_list, out) &&
	       class_property_validImpl(self->sprop_list, out);
}

bool class_method_parameter_valid(class_* cls, method** out_method, string_view* out_name) {
	(*out_name) = ZERO_VIEW;
	for(int i=0; i<cls->method_list->length; i++) {
		method* m = (method*)AtVector(cls->method_list, i);
		if(IsOverwrappedParameterName(m->parameters, out_name)) {
			(*out_method) = m;
			return false;
		}
	}
	for(int i=0; i<cls->smethod_list->length; i++) {
		method* m = (method*)AtVector(cls->smethod_list, i);
		if(IsOverwrappedParameterName(m->parameters, out_name)) {
			(*out_method) = m;
			return false;
		}
	}
	return true;
}

bool class_ctor_parameter_valid(class_* self, constructor** out_ctor, string_view* out_name) {
	for(int i=0; i<self->constructor_list->length; i++) {
		constructor* ctor = (constructor*)AtVector(self->constructor_list, i);
		if(IsOverwrappedParameterName(ctor->parameter_list, out_name)) {
			(*out_ctor) = ctor;
			return false;
		}
	}
	return true;
}

bool class_type_type_parameter_valid(class_* self, string_view* out_name) {
	return !IsOverwrappedTypeParameterName(self->type_parameter_list, out_name);
}

bool class_method_type_parameter_valid(class_* self, method** out_method, string_view* out_name) {
	(*out_name) = ZERO_VIEW;
	for(int i=0; i<self->method_list->length; i++) {
		method* m = (method*)AtVector(self->method_list, i);
		if(IsOverwrappedTypeParameterName(m->type_parameters, out_name)) {
			(*out_method) = m;
			return false;
		}
	}
	for(int i=0; i<self->smethod_list->length; i++) {
		method* m = (method*)AtVector(self->smethod_list, i);
		if(IsOverwrappedTypeParameterName(m->type_parameters, out_name)) {
			(*out_method) = m;
			return false;
		}
	}
	return true;
}
//private
static bool class_field_validImpl(Vector* field_vec, field** out) {
	(*out) = NULL;
	bool ret = true;
	for(int i=0; i<field_vec->length; i++) {
		field* f = (field*)AtVector(field_vec, i);
		for(int j=0; j<field_vec->length; j++) {
			field* fE = (field*)AtVector(field_vec, j);
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

static bool class_property_validImpl(Vector* prop_vec, property** out) {
	(*out) = NULL;
	bool ret = true;
	for(int i=0; i<prop_vec->length; i++) {
		property* p = (property*)AtVector(prop_vec, i);
		for(int j=0; j<prop_vec->length; j++) {
			property* pE = (property*)AtVector(prop_vec, j);
			if(i == j) { continue; }
			if(p->namev == pE->namev) {
				ret = false;
				(*out) = p;
				break;
			}
		}
	}
	return ret;
}

static bool methods_is_all_abstract(Vector* v) {
	for(int i=0; i<v->length; i++) {
		method* e = AtVector(v, i);
		#if defined(DEBUG)
		const char* tyname = Ref2Str(type_name(e->parent));
		#endif
		if(!IsAbstractModifier(e->modifier)) {
			return false;
		}
	}
	return true;
}