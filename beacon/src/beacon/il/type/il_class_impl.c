#include "il_class_impl.h"
#include <stdlib.h>
#include "../../util/text.h"
//#include "../../env/field.h"
//#include "../../env/method.h"
#include "../il_field.h"
#include "../il_method.h"
#include "../il_constructor.h"
#include "../il_type_parameter.h"
#include "../il_operator_overload.h"
#include "../../util/mem.h"
#include "../il_property.h"

//proto
static void il_class_field_delete(vector_item item);
static void il_class_method_delete(vector_item item);
static void il_class_ctor_delete(vector_item item);
static void il_class_extend_delete(vector_item item);
static void il_class_type_parameter_delete(vector_item item);
static void il_class_delete_operator_overload(vector_item item);
static void il_class_prop_delete(vector_item item );

il_type * il_type_wrap_class(il_class * self) {
	il_type* ret = il_type_new();
	ret->tag = iltype_class_T;
	ret->u.class_ = self;
	return ret;
}

il_class* il_class_new(string_view namev) {
	il_class* ret = (il_class*)MEM_MALLOC(sizeof(il_class));
	ret->namev = namev;
	ret->extend_list = vector_new();
	ret->field_list = vector_new();
	ret->sfield_list = vector_new();
	ret->method_list = vector_new();
	ret->smethod_list = vector_new();
	ret->constructor_list = vector_new();
	ret->type_parameter_list = vector_new();
	ret->operator_overload_list = vector_new();
	ret->prop_list = vector_new();
	ret->sprop_list = vector_new();
	ret->is_abstract = false;
	return ret;
}

void il_class_add_field(il_class * self, il_field * f) {
	if (modifier_is_static(f->modifier)) {
		vector_push(self->sfield_list, f);
	} else {
		vector_push(self->field_list, f);
	}
}

void il_class_add_property(il_class* self, il_property* prop) {
	if(modifier_is_static(prop->modifier)) {
		vector_push(self->sprop_list, prop);
	} else {
		vector_push(self->prop_list, prop);
	}
}

void il_class_add_method(il_class * self, il_method * m) {
	if (modifier_is_static(m->modifier)) {
		vector_push(self->smethod_list, m);
	} else {
		vector_push(self->method_list, m);
	}
}

void il_class_delete(il_class * self) {
	if (self == NULL) {
		return;
	}
	//printf("free class %s\n", self->name);
	//MEM_FREE(self->super);
	vector_delete(self->field_list, il_class_field_delete);
	vector_delete(self->sfield_list, il_class_field_delete);
	vector_delete(self->method_list, il_class_method_delete);
	vector_delete(self->smethod_list, il_class_method_delete);
	vector_delete(self->constructor_list, il_class_ctor_delete);
	vector_delete(self->extend_list, il_class_extend_delete);
	vector_delete(self->type_parameter_list, il_class_type_parameter_delete);
	vector_delete(self->operator_overload_list, il_class_delete_operator_overload);
	vector_delete(self->prop_list, il_class_prop_delete);
	vector_delete(self->sprop_list, il_class_prop_delete);
	MEM_FREE(self);
}

//private
static void il_class_field_delete(vector_item item) {
	il_field* e = (il_field*)item;
	il_field_delete(e);
}

static void il_class_method_delete(vector_item item) {
	il_method* e = (il_method*)item;
	il_method_delete(e);
}

static void il_class_ctor_delete(vector_item item) {
	il_constructor* e = (il_constructor*)item;
	il_constructor_delete(e);
}

static void il_class_extend_delete(vector_item item) {
	//fqcn_cache* e = (fqcn_cache*)item;
	//fqcn_cache_delete(e);
	generic_cache* e = (generic_cache*)item;
	generic_cache_delete(e);
}

static void il_class_type_parameter_delete(vector_item item) {
	il_type_parameter* e = (il_type_parameter*)item;
	il_type_parameter_delete(e);
}

static void il_class_delete_operator_overload(vector_item item) {
	il_operator_overload* e = (il_operator_overload*)item;
	il_operator_overload_delete(e);
}

static void il_class_prop_delete(vector_item item ) {
	il_property* e = (il_property*)item;
	il_property_delete(e);
}