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
static void il_class_field_delete(VectorItem item);
static void il_class_method_delete(VectorItem item);
static void il_class_ctor_delete(VectorItem item);
static void il_class_extend_delete(VectorItem item);
static void il_class_type_parameter_delete(VectorItem item);
static void il_class_delete_operator_overload(VectorItem item);
static void il_class_prop_delete(VectorItem item );

il_type * il_type_wrap_class(il_class * self) {
	il_type* ret = il_type_new();
	ret->tag = iltype_class_T;
	ret->u.class_ = self;
	return ret;
}

il_class* il_class_new(string_view namev) {
	il_class* ret = (il_class*)MEM_MALLOC(sizeof(il_class));
	ret->namev = namev;
	ret->extend_list = NewVector();
	ret->field_list = NewVector();
	ret->sfield_list = NewVector();
	ret->method_list = NewVector();
	ret->smethod_list = NewVector();
	ret->constructor_list = NewVector();
	ret->type_parameter_list = NewVector();
	ret->operator_overload_list = NewVector();
	ret->prop_list = NewVector();
	ret->sprop_list = NewVector();
	ret->is_abstract = false;
	return ret;
}

void il_class_add_field(il_class * self, il_field * f) {
	if (IsStaticModifier(f->modifier)) {
		PushVector(self->sfield_list, f);
	} else {
		PushVector(self->field_list, f);
	}
}

void il_class_add_property(il_class* self, il_property* prop) {
	if(IsStaticModifier(prop->modifier)) {
		PushVector(self->sprop_list, prop);
	} else {
		PushVector(self->prop_list, prop);
	}
}

void il_class_add_method(il_class * self, il_method * m) {
	if (IsStaticModifier(m->modifier)) {
		PushVector(self->smethod_list, m);
	} else {
		PushVector(self->method_list, m);
	}
}

void il_class_delete(il_class * self) {
	if (self == NULL) {
		return;
	}
	//printf("free class %s\n", self->name);
	//MEM_FREE(self->super);
	DeleteVector(self->field_list, il_class_field_delete);
	DeleteVector(self->sfield_list, il_class_field_delete);
	DeleteVector(self->method_list, il_class_method_delete);
	DeleteVector(self->smethod_list, il_class_method_delete);
	DeleteVector(self->constructor_list, il_class_ctor_delete);
	DeleteVector(self->extend_list, il_class_extend_delete);
	DeleteVector(self->type_parameter_list, il_class_type_parameter_delete);
	DeleteVector(self->operator_overload_list, il_class_delete_operator_overload);
	DeleteVector(self->prop_list, il_class_prop_delete);
	DeleteVector(self->sprop_list, il_class_prop_delete);
	MEM_FREE(self);
}

//private
static void il_class_field_delete(VectorItem item) {
	il_field* e = (il_field*)item;
	il_field_delete(e);
}

static void il_class_method_delete(VectorItem item) {
	il_method* e = (il_method*)item;
	il_method_delete(e);
}

static void il_class_ctor_delete(VectorItem item) {
	il_constructor* e = (il_constructor*)item;
	il_constructor_delete(e);
}

static void il_class_extend_delete(VectorItem item) {
	//fqcn_cache* e = (fqcn_cache*)item;
	//fqcn_cache_delete(e);
	generic_cache* e = (generic_cache*)item;
	generic_cache_delete(e);
}

static void il_class_type_parameter_delete(VectorItem item) {
	il_type_parameter* e = (il_type_parameter*)item;
	il_type_parameter_delete(e);
}

static void il_class_delete_operator_overload(VectorItem item) {
	il_operator_overload* e = (il_operator_overload*)item;
	il_operator_overload_delete(e);
}

static void il_class_prop_delete(VectorItem item ) {
	il_property* e = (il_property*)item;
	il_property_delete(e);
}