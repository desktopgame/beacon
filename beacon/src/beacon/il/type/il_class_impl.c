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
static void il_class_DeleteField(VectorItem item);
static void il_class_DeleteMethod(VectorItem item);
static void il_class_ctor_delete(VectorItem item);
static void il_class_extend_delete(VectorItem item);
static void il_class_DeleteTypeParameter(VectorItem item);
static void DeleteILClass_operator_overload(VectorItem item);
static void il_class_prop_delete(VectorItem item );

il_type * WrapILClass(il_class * self) {
	il_type* ret = NewILType();
	ret->tag = ilTYPE_CLASS_T;
	ret->u.class_ = self;
	return ret;
}

il_class* NewILClass(StringView namev) {
	il_class* ret = (il_class*)MEM_MALLOC(sizeof(il_class));
	ret->namev = namev;
	ret->extend_list = NewVector();
	ret->field_list = NewVector();
	ret->sfield_list = NewVector();
	ret->method_list = NewVector();
	ret->smethod_list = NewVector();
	ret->constructor_list = NewVector();
	ret->GetParameterListType = NewVector();
	ret->operator_overload_list = NewVector();
	ret->prop_list = NewVector();
	ret->sprop_list = NewVector();
	ret->is_abstract = false;
	return ret;
}

void AddFieldILClass(il_class * self, ILField * f) {
	if (IsStaticModifier(f->Modifier)) {
		PushVector(self->sfield_list, f);
	} else {
		PushVector(self->field_list, f);
	}
}

void AddPropertyILClass(il_class* self, ILProperty* prop) {
	if(IsStaticModifier(prop->Modifier)) {
		PushVector(self->sprop_list, prop);
	} else {
		PushVector(self->prop_list, prop);
	}
}

void AddMethodILClass(il_class * self, ILMethod * m) {
	if (IsStaticModifier(m->Modifier)) {
		PushVector(self->smethod_list, m);
	} else {
		PushVector(self->method_list, m);
	}
}

void DeleteILClass(il_class * self) {
	if (self == NULL) {
		return;
	}
	//printf("free class %s\n", self->name);
	//MEM_FREE(self->super);
	DeleteVector(self->field_list, il_class_DeleteField);
	DeleteVector(self->sfield_list, il_class_DeleteField);
	DeleteVector(self->method_list, il_class_DeleteMethod);
	DeleteVector(self->smethod_list, il_class_DeleteMethod);
	DeleteVector(self->constructor_list, il_class_ctor_delete);
	DeleteVector(self->extend_list, il_class_extend_delete);
	DeleteVector(self->GetParameterListType, il_class_DeleteTypeParameter);
	DeleteVector(self->operator_overload_list, DeleteILClass_operator_overload);
	DeleteVector(self->prop_list, il_class_prop_delete);
	DeleteVector(self->sprop_list, il_class_prop_delete);
	MEM_FREE(self);
}

//private
static void il_class_DeleteField(VectorItem item) {
	ILField* e = (ILField*)item;
	DeleteILField(e);
}

static void il_class_DeleteMethod(VectorItem item) {
	ILMethod* e = (ILMethod*)item;
	DeleteILMethod(e);
}

static void il_class_ctor_delete(VectorItem item) {
	ILConstructor* e = (ILConstructor*)item;
	DeleteILConstructor(e);
}

static void il_class_extend_delete(VectorItem item) {
	//FQCNCache* e = (FQCNCache*)item;
	//DeleteFQCNCache(e);
	generic_cache* e = (generic_cache*)item;
	DeleteGenericCache(e);
}

static void il_class_DeleteTypeParameter(VectorItem item) {
	ILTypeParameter* e = (ILTypeParameter*)item;
	DeleteILTypeParameter(e);
}

static void DeleteILClass_operator_overload(VectorItem item) {
	ILOperatorOverload* e = (ILOperatorOverload*)item;
	DeleteILOperatorOverload(e);
}

static void il_class_prop_delete(VectorItem item ) {
	ILProperty* e = (ILProperty*)item;
	DeleteILProperty(e);
}