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

static bool class_contains_fieldImpl(Vector* fields, field* f);
static bool class_contains_propertyImpl(Vector* props, property* p);

field * class_find_field(class_* self, string_view namev, int* outIndex) {
	(*outIndex) = -1;
	for (int i = 0; i < self->field_list->length; i++) {
		VectorItem e = AtVector(self->field_list, i);
		field* f = (field*)e;
		if (namev == f->namev) {
			(*outIndex) = (class_count_fieldall(self) - self->field_list->length) + i;
			return f;
		}
	}
	return NULL;
}

field * class_find_field_tree(class_ * self, string_view namev, int * outIndex) {
	class_* pointee = self;
	do {
		field* f = class_find_field(pointee, namev, outIndex);
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

field * class_find_sfield(class_ * self, string_view namev, int * outIndex) {
	(*outIndex) = -1;
	for (int i = 0; i < self->sfield_list->length; i++) {
		VectorItem e = AtVector(self->sfield_list, i);
		field* f = (field*)e;
		if (namev == f->namev) {
			(*outIndex) = (class_count_sfieldall(self) - self->sfield_list->length) + i;
			return f;
		}
	}
	return NULL;
}

field * class_find_sfield_tree(class_ * self, string_view namev, int * outIndex) {
	class_* pointee = self;
	do {
		field* f = class_find_sfield(pointee, namev, outIndex);
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

field * class_get_field(class_ * self, int index) {
	assert(index >= 0);
	int all = class_count_fieldall(self);
	if (index >= (all - self->field_list->length) &&
		index < all) {
		return AtVector(self->field_list, self->field_list->length - (all - index));
	}
	return class_get_field(self->super_class->core_type->u.class_, index);
}

field * class_get_sfield(class_ * self, int index) {
	assert(index >= 0);
	int all = class_count_sfieldall(self);
	if (index >= (all - self->sfield_list->length) &&
		index < all) {
		return AtVector(self->sfield_list, self->sfield_list->length - (all - index));
	}
	return class_get_sfield(self->super_class->core_type->u.class_, index);
}

bool class_contains_field(class_* self, field* f) {
	return class_contains_fieldImpl(self->field_list, f);
}

bool class_contains_sfield(class_* self, field* f) {
	return class_contains_fieldImpl(self->sfield_list, f);
}

bool class_accessible_field(class_* self, field* f) {
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



bool class_contains_property(class_* self, property* p) {
	return class_contains_propertyImpl(self->prop_list, p);
}

bool class_contains_sproperty(class_* self, property* p) {
	return class_contains_propertyImpl(self->sprop_list, p);
}

bool class_accessible_property(class_* self, property* p) {
	assert(p != NULL);
	if(p->access == ACCESS_PUBLIC_T) {
		return true;
	}
	if(p->access == ACCESS_PRIVATE_T) {
		return self == TYPE2CLASS(p->parent);
	}
	type* ty = self->parent;
	class_* fcl = TYPE2CLASS(p->parent);
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

bool class_accessible_property_accessor(class_* self, property_body* pb) {
	assert(pb != NULL);
	if(pb->access == ACCESS_PUBLIC_T) {
		return true;
	}
	if(pb->access == ACCESS_PRIVATE_T) {
		return self == TYPE2CLASS(pb->parent->parent);
	}
	type* ty = self->parent;
	class_* fcl = TYPE2CLASS(pb->parent->parent);
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

int class_get_field_by_property(class_* self, property* p) {
	int temp = -1;
	assert(p->source_ref != NULL);
	if(IsStaticModifier(p->modifier)) {
		class_find_sfield(self, p->source_ref->namev, &temp);
	} else {
		class_find_field(self, p->source_ref->namev, &temp);
	}
	return temp;
}

property* class_get_property(class_* self, int index) {
	assert(index >= 0);
	int all = class_count_propertyall(self);
	if (index >= (all - self->prop_list->length) &&
		index < all) {
		return AtVector(self->prop_list, self->prop_list->length - (all - index));
	}
	return class_get_property(self->super_class->core_type->u.class_, index);
}

property* class_get_sproperty(class_* self, int index) {
	assert(index >= 0);
	int all = class_count_spropertyall(self);
	if (index >= (all - self->sprop_list->length) &&
		index < all) {
		return AtVector(self->sprop_list, self->sprop_list->length - (all - index));
	}
	return class_get_property(self->super_class->core_type->u.class_, index);
}

property* class_find_property(class_* self, string_view namev, int* outIndex) {
	(*outIndex) = -1;
	for (int i = 0; i < self->prop_list->length; i++) {
		VectorItem e = AtVector(self->prop_list, i);
		property* p = (property*)e;
		if (namev == p->namev) {
			(*outIndex) = (class_count_propertyall(self) - self->prop_list->length) + i;
			return p;
		}
	}
	return NULL;
}

property* class_find_property_tree(class_* self, string_view namev, int* outIndex) {
	class_* pointee = self;
	do {
		property* p = class_find_property(pointee, namev, outIndex);
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

property* class_find_sproperty(class_* self, string_view namev, int* outIndex) {
	(*outIndex) = -1;
	for (int i = 0; i < self->sprop_list->length; i++) {
		VectorItem e = AtVector(self->sprop_list, i);
		property* p = (property*)e;
		if (namev == p->namev) {
			(*outIndex) = (class_count_spropertyall(self) - self->sprop_list->length) + i;
			return p;
		}
	}
	return NULL;
}

property* class_find_sproperty_tree(class_* self, string_view namev, int* outIndex) {
	class_* pointee = self;
	do {
		property* p = class_find_sproperty(pointee, namev, outIndex);
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



constructor * class_rfind_constructor(class_ * self, Vector * args, Vector* typeargs, frame* fr, int* outIndex) {
	return meta_scoped_rfind_ctor(self, self->constructor_list, args, typeargs, fr, outIndex);
}

constructor * class_ilfind_constructor(class_ * self, Vector * args, enviroment * env, call_context* cctx, int* outIndex) {
	//	Vector* v = meta_find_constructors(self, args, env, ilctx);
	//	(*outIndex) = -1;
	//	return class_find_constructor_impl(v, args, env, ilctx, outIndex);
	constructor* ctor = meta_scoped_ilfind_ctor(self, self->constructor_list, args, env, cctx, outIndex);
	return ctor;
}

constructor * class_ilfind_empty_constructor(class_ * self, enviroment * env, call_context* cctx, int * outIndex) {
	Vector* emptyArgs = NewVector();
	constructor* ret = class_ilfind_constructor(self, emptyArgs, env, cctx, outIndex);
	DeleteVector(emptyArgs, VectorDeleterOfNull);
	return ret;
}



method * class_ilfind_method(class_ * self, string_view namev, Vector * args, enviroment * env, call_context* cctx, int * outIndex) {
	(*outIndex) = -1;
	class_create_vtable(self);
	#if defined(DEBUG)
	const char* str = Ref2Str(self->namev);
	#endif
	//assert(self->vt->elements->length > 0);
	method* ret = NULL;
	if((ret = meta_scoped_ilfind_method(self, self->vt->elements, namev, args, env, cctx, outIndex))
	   != NULL) {
		   return ret;
	}
	if((ret = meta_scoped_ilfind_method(self, self->method_list, namev, args, env, cctx, outIndex))
	   != NULL) {
		   return ret;
	}
	if((ret = meta_scoped_ilfind_method(self, self->smethod_list, namev, args, env, cctx, outIndex))
	   != NULL) {
		   return ret;
	}
	return NULL;
}

method* class_gfind_method(class_* self, string_view namev, Vector* gargs, int* outIndex) {
	(*outIndex) = -1;
	class_create_vtable(self);
	//assert(self->vt->elements->length > 0);
	method* ret = NULL;
	if((ret = meta_scoped_gfind_method(self, self->vt->elements, namev, gargs, outIndex))
	   != NULL) {
		   return ret;
	}
	if((ret = meta_scoped_gfind_method(self, self->method_list, namev, gargs, outIndex))
	   != NULL) {
		   return ret;
	}
	if((ret = meta_scoped_gfind_method(self, self->smethod_list, namev, gargs, outIndex))
	   != NULL) {
		   return ret;
	}
	return NULL;
}

method* class_gfind_eqmethod(class_* self, int* outIndex) {
	Vector* gargs = NewVector();
	PushVector(gargs, TYPE_OBJECT->generic_self);
	method* ret = class_gfind_method(self, InternString("equals"), gargs, outIndex);
	DeleteVector(gargs, VectorDeleterOfNull);
	return ret;
}

method * class_ilfind_smethod(class_ * self, string_view namev, Vector * args, enviroment * env, call_context* cctx, int * outIndex) {
	#if defined(DEBUG)
	const char* str = Ref2Str(namev);
	#endif
	(*outIndex) = -1;
	class_create_vtable(self);
	int temp = 0;
	method* ret = meta_ilfind_method(self->smethod_list, namev, args, env, cctx, &temp);
//	temp += (class_count_smethodall(self) - self->smethod_list->length);
	(*outIndex) = temp;
	return ret;
}

method* class_gfind_smethod(class_* self, string_view namev, Vector* gargs, int* outIndex) {
	(*outIndex) = -1;
	class_create_vtable(self);
	int temp = 0;
	method* ret = meta_gfind_method(self->smethod_list, namev, gargs, &temp);
//	temp += (class_count_smethodall(self) - self->smethod_list->length);
	(*outIndex) = temp;
	return ret;
}

method * class_get_method(object * o, int index) {
	assert(index >= 0);
	#if defined(DEBUG)
	const char* name = object_name(o);
	#endif
	if(o->tag == OBJECT_NULL_T) {
		o->vptr = TYPE2CLASS(TYPE_OBJECT)->vt;
	}
	vtable* vx = (o->vptr);
	return (method*)AtVector(vx->elements, index);
}

method * class_get_smethod(class_* self, int index) {
	assert(index >= 0);
	/*
	//class_* self = o->classz;
	int all = class_count_smethodall(self);
	if (index >= (all - self->smethod_list->length) &&
		index < all) {
		return AtVector(self->smethod_list, self->smethod_list->length - (all - index));
	}
	return class_get_smethod(self->super_class->core_type->u.class_, index);
	//*/
	return AtVector(self->smethod_list, index);
}

method * class_get_impl_method(class_ * self, type * interType, int interMIndex) {
	#if defined(DEBUG)
	const char* str = Ref2Str(self->namev);
	#endif
	assert(self->vt_vec->length > 0);
	Vector* tbl = class_get_generic_interface_tree(self);
	//指定のインターフェイスが
	//このクラスにおいて何番目かを調べる
	int declIndex = -1;
	for (int i = 0; i < tbl->length; i++) {
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
	vtable* vtAt = AtVector(self->vt_vec, declIndex);
	return AtVector(vtAt->elements, interMIndex);
}




operator_overload* class_gfind_operator_overload(class_* self, operator_type type, Vector* args, enviroment* env, call_context* cctx, int* outIndex) {
	(*outIndex) = -1;
	operator_overload* ret = NULL;
	class_create_operator_vt(self);
	for(int i=0; i<self->ovt->vec->length; i++) {
		operator_overload* operator_ov = AtVector(self->ovt->vec, i);
		if(operator_ov->type != type) {
			continue;
		}
		bool nomatch = false;
		int score = 1024;
		int sum = 0;
		Vector* params = operator_ov->parameter_list;
		for(int j=0; j<params->length; j++) {
			parameter* param = AtVector(params, j);
			generic_type* arg = AtVector(args, j);
			int dist = generic_type_distance(param->gtype, arg, cctx);
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

operator_overload* class_ilfind_operator_overload(class_* self, operator_type type, Vector* args, enviroment* env, call_context* cctx, int* outIndex) {
	Vector* gargs =NewVector();
	for(int i=0; i<args->length; i++) {
		il_factor* ilfact = (il_factor*)AtVector(args,i);
		generic_type* g = il_factor_eval(ilfact, env, cctx);
		PushVector(gargs, g);
	}
	operator_overload* ret = class_gfind_operator_overload(self, type, gargs, env, cctx, outIndex);
	DeleteVector(gargs, VectorDeleterOfNull);
	return ret;
}

operator_overload* class_argfind_operator_overload(class_* self, operator_type type, Vector* args, enviroment* env, call_context* cctx, int* outIndex) {
	Vector* gargs =NewVector();
	for(int i=0; i<args->length; i++) {
		//il_factor* ilfact = (il_factor*)AtVector(args,i);
		il_argument* ilarg = (il_argument*)AtVector(args, i);
		il_factor* ilfact = ilarg->factor;
		generic_type* g = il_factor_eval(ilfact, env, cctx);
		PushVector(gargs, g);
	}
	operator_overload* ret = class_gfind_operator_overload(self, type, gargs, env, cctx, outIndex);
	DeleteVector(gargs, VectorDeleterOfNull);
	return ret;
}

operator_overload* class_get_operator_overload(class_* self, int index) {
	return AtVector(self->ovt->vec, index);
}

Vector* class_find_methods_tree(class_* self, method* m) {
	assert(self != NULL);
	assert(m != NULL);
	class_* ptr = self;
	Vector* ret = NewVector();
	#if defined(DEBUG)
	const char* ptrname = Ref2Str(ptr->namev);
	#endif
	do {
		method* tmp = NULL;
		if(class_contains_method(ptr->method_list, m, &tmp)) {
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

bool class_contains_method(Vector* method_list, method* m, method** outM) {
	assert(!IsStaticModifier(m->modifier));
	(*outM) = NULL;
	bool ret = false;
	call_context* cctx = call_context_new(CALL_DECL_T);
	cctx->scope = m->parent->location;
	cctx->ty = m->parent;
	for(int i=0; i<method_list->length; i++) {
		method* mE = AtVector(method_list, i);
		if(method_override(m, mE, cctx)) {
			(*outM) = mE;
			ret = true;
			break;
		}
	}
	call_context_delete(cctx);
	return ret;
}

Vector* class_get_generic_interface_list(class_* self) {
	Vector* ret = NewVector();
	for(int i=0; i<self->impl_list->length; i++) {
		generic_type* ginter = AtVector(self->impl_list, i);
		Vector* inner = interface_get_generic_interface_tree(TYPE2INTERFACE(GENERIC2TYPE(ginter)));
		MergeVector(ret, inner);
		PushVector(ret, ginter);
		DeleteVector(inner, VectorDeleterOfNull);
	}
	return ret;
}

Vector* class_get_generic_interface_tree(class_* self) {
	class_* ptr = self;
	Vector* ret = NewVector();
	do {
		Vector* v = class_get_generic_interface_list(ptr);
		MergeVector(v, ret);
		DeleteVector(v, VectorDeleterOfNull);
		if(ptr->super_class == NULL) {
			break;
		}
		ptr = TYPE2CLASS(GENERIC2TYPE(ptr->super_class));
	} while(ptr != NULL);
	return ret;
}

Vector* class_get_interface_list(class_* self) {
	Vector* ret = NewVector();
	Vector* c = class_get_generic_interface_list(self);
	for(int i=0; i<c->length; i++) {
		generic_type* gt = AtVector(c, i);
		PushVector(ret, TYPE2INTERFACE(GENERIC2TYPE(gt)));
	}
	DeleteVector(c, VectorDeleterOfNull);
	return ret;
}

Vector* class_get_interface_tree(class_* self) {
	Vector* ret = NewVector();
	Vector* c = class_get_generic_interface_tree(self);
	for(int i=0; i<c->length; i++) {
		generic_type* gt = AtVector(c, i);
		PushVector(ret, TYPE2INTERFACE(GENERIC2TYPE(gt)));
	}
	DeleteVector(c, VectorDeleterOfNull);
	return ret;
}

generic_type* class_find_interface_type(class_* self, type* tinter, generic_type** out_baseline) {
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
		//Vector* gimpl_list = class_get_generic_interface_list(ptr);
		Vector* gimpl_list = ptr->impl_list;
		for (int i = 0; i < gimpl_list->length; i++) {
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
static bool class_contains_fieldImpl(Vector* fields, field* f) {
	for(int i=0; i<fields->length; i++) {
		field* e = (field*)AtVector(fields, i);
		if(e == f) {
			return true;
		}
	}
	return false;
}

static bool class_contains_propertyImpl(Vector* props, property* p) {
	for(int i=0; i<props->length; i++) {
		property* e = (property*)AtVector(props, i);
		if(e == p) {
			return true;
		}
	}
	return false;
}