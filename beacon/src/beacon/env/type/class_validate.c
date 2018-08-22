#include "class_validate.h"
#include "../type_impl.h"
#include "../generic_type.h"
#include "../property.h"
#include "../constructor.h"
#include "../field.h"
#include "class_impl.h"
static bool class_field_validImpl(vector* field_vec, field** out);
static bool class_property_validImpl(vector* prop_vec, property** out);
static bool methods_is_all_abstract(vector* v);

bool class_interface_method_implement_valid(class_* cls, method** out) {
	(*out) = NULL;
	bool contains = true;
	#if defined(DEBUG)
	const char* csupername = string_pool_ref2str(cls->namev);
	if(cls->namev == string_pool_intern("AdditiveOperator")) {
		int a = 0;
	}
	#endif
	//全ての実装インターフェイスを取得する
	vector* inter_list = class_get_interface_tree(cls);
	vector* methods = interface_method_flatten_list(inter_list);
	if(inter_list->length == 0 || cls->is_abstract) {
		vector_delete(inter_list, vector_deleter_null);
		vector_delete(methods, vector_deleter_null);
		return true;
	}
	for(int i=0; i<methods->length; i++) {
		method* m = vector_at(methods, i);
		vector* methods = class_find_methods_tree(cls, m);
		if(methods->length == 0 || methods_is_all_abstract(methods)) {
			(*out) = m;
			contains = false;
			vector_delete(methods, vector_deleter_null);
			break;
		}
		vector_delete(methods, vector_deleter_null);
	}
	vector_delete(inter_list, vector_deleter_null);
	vector_delete(methods, vector_deleter_null);
	return contains;
}

bool class_interface_property_implement_valid(class_* cls, property** out) {
	(*out) = NULL;
	//全ての実装インターフェイスを取得する
	vector* gimpl_list = class_get_generic_interface_list(cls);
	if(gimpl_list->length == 0 || cls->is_abstract) {
		vector_delete(gimpl_list, vector_deleter_null);
		return true;
	}
	//全てのインターフェイスに
	for(int i=0;i<gimpl_list->length; i++) {
		generic_type* e = vector_at(gimpl_list, i);
		interface_* inter = TYPE2INTERFACE(GENERIC2TYPE(e));
		bool valid = true;
		for(int j=0; j<inter->prop_list->length; j++) {
			int temp = 0;
			property* decl = vector_at(inter->prop_list, j);
			property* impl = class_find_property(cls, decl->namev, &temp);
			if(temp == -1) {
				(*out) = decl;
				vector_delete(gimpl_list, vector_deleter_null);
				return false;
			} else {
				if(generic_type_distance(decl->gtype, impl->gtype, NULL) != 0) {
					(*out) = decl;
					vector_delete(gimpl_list, vector_deleter_null);
					return false;
				}
				if(decl->set->access != impl->set->access ||
				   decl->get->access != impl->get->access) {
					(*out) = decl;
					vector_delete(gimpl_list, vector_deleter_null);
					return false;
				}
			}
		}
	}
	vector_delete(gimpl_list, vector_deleter_null);
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
	const char* csupername = string_pool_ref2str(csuper->namev);
	if(cls->namev == string_pool_intern("Concrete")) {
		int a = 0;
	}
	#endif
	bool ret = true;
	for(int i=0; i<csuper->method_list->length; i++) {
		method* me = vector_at(csuper->method_list, i);
		#if defined(DEBUG)
		const char* mename = string_pool_ref2str(me->namev);
		#endif
		if(!modifier_is_abstract(me->modifier)) { continue; }
		vector* methods = class_find_methods_tree(cls, me);
		if(methods->length == 0 || methods_is_all_abstract(methods)) {
		   (*out) = me;
		   ret = false;
		   vector_delete(methods, vector_deleter_null);
		   break;
		}
		vector_delete(methods, vector_deleter_null);
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
	for(int i=0; i<cls->method_list->length; i++) {
		method* m = (method*)vector_at(cls->method_list, i);
		if(parameter_is_overwrapped_name(m->parameter_list, out_name)) {
			(*out_method) = m;
			return false;
		}
	}
	for(int i=0; i<cls->smethod_list->length; i++) {
		method* m = (method*)vector_at(cls->smethod_list, i);
		if(parameter_is_overwrapped_name(m->parameter_list, out_name)) {
			(*out_method) = m;
			return false;
		}
	}
	return true;
}

bool class_ctor_parameter_valid(class_* self, constructor** out_ctor, string_view* out_name) {
	for(int i=0; i<self->constructor_list->length; i++) {
		constructor* ctor = (constructor*)vector_at(self->constructor_list, i);
		if(parameter_is_overwrapped_name(ctor->parameter_list, out_name)) {
			(*out_ctor) = ctor;
			return false;
		}
	}
	return true;
}

bool class_type_type_parameter_valid(class_* self, string_view* out_name) {
	return !type_parameter_is_overwrapped_name(self->type_parameter_list, out_name);
}

bool class_method_type_parameter_valid(class_* self, method** out_method, string_view* out_name) {
	for(int i=0; i<self->method_list->length; i++) {
		method* m = (method*)vector_at(self->method_list, i);
		if(type_parameter_is_overwrapped_name(m->type_parameter_list, out_name)) {
			(*out_method) = m;
			return false;
		}
	}
	for(int i=0; i<self->smethod_list->length; i++) {
		method* m = (method*)vector_at(self->smethod_list, i);
		if(type_parameter_is_overwrapped_name(m->type_parameter_list, out_name)) {
			(*out_method) = m;
			return false;
		}
	}
	return true;
}
//private
static bool class_field_validImpl(vector* field_vec, field** out) {
	(*out) = NULL;
	bool ret = true;
	for(int i=0; i<field_vec->length; i++) {
		field* f = (field*)vector_at(field_vec, i);
		for(int j=0; j<field_vec->length; j++) {
			field* fE = (field*)vector_at(field_vec, j);
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

static bool class_property_validImpl(vector* prop_vec, property** out) {
	(*out) = NULL;
	bool ret = true;
	for(int i=0; i<prop_vec->length; i++) {
		property* p = (property*)vector_at(prop_vec, i);
		for(int j=0; j<prop_vec->length; j++) {
			property* pE = (property*)vector_at(prop_vec, j);
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

static bool methods_is_all_abstract(vector* v) {
	for(int i=0; i<v->length; i++) {
		method* e = vector_at(v, i);
		#if defined(DEBUG)
		const char* tyname = string_pool_ref2str(type_name(e->parent));
		#endif
		if(!modifier_is_abstract(e->modifier)) {
			return false;
		}
	}
	return true;
}