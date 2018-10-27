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
static void ILClass_DeleteField(VectorItem item);
static void ILClass_DeleteMethod(VectorItem item);
static void ILClass_ctor_delete(VectorItem item);
static void ILClass_extend_delete(VectorItem item);
static void ILClass_DeleteTypeParameter(VectorItem item);
static void DeleteILClass_operator_overload(VectorItem item);
static void ILClass_prop_delete(VectorItem item );

ILType * WrapILClass(ILClass * self) {
	ILType* ret = NewILType();
	ret->Tag = ILTYPE_CLASS_T;
	ret->Kind.Class = self;
	return ret;
}

ILClass* NewILClass(StringView namev) {
	ILClass* ret = (ILClass*)MEM_MALLOC(sizeof(ILClass));
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

void AddFieldILClass(ILClass * self, ILField * f) {
	if (IsStaticModifier(f->Modifier)) {
		PushVector(self->sfield_list, f);
	} else {
		PushVector(self->field_list, f);
	}
}

void AddPropertyILClass(ILClass* self, ILProperty* prop) {
	if(IsStaticModifier(prop->Modifier)) {
		PushVector(self->sprop_list, prop);
	} else {
		PushVector(self->prop_list, prop);
	}
}

void AddMethodILClass(ILClass * self, ILMethod * m) {
	if (IsStaticModifier(m->Modifier)) {
		PushVector(self->smethod_list, m);
	} else {
		PushVector(self->method_list, m);
	}
}

void DeleteILClass(ILClass * self) {
	if (self == NULL) {
		return;
	}
	//printf("free class %s\n", self->name);
	//MEM_FREE(self->super);
	DeleteVector(self->field_list, ILClass_DeleteField);
	DeleteVector(self->sfield_list, ILClass_DeleteField);
	DeleteVector(self->method_list, ILClass_DeleteMethod);
	DeleteVector(self->smethod_list, ILClass_DeleteMethod);
	DeleteVector(self->constructor_list, ILClass_ctor_delete);
	DeleteVector(self->extend_list, ILClass_extend_delete);
	DeleteVector(self->GetParameterListType, ILClass_DeleteTypeParameter);
	DeleteVector(self->operator_overload_list, DeleteILClass_operator_overload);
	DeleteVector(self->prop_list, ILClass_prop_delete);
	DeleteVector(self->sprop_list, ILClass_prop_delete);
	MEM_FREE(self);
}

//private
static void ILClass_DeleteField(VectorItem item) {
	ILField* e = (ILField*)item;
	DeleteILField(e);
}

static void ILClass_DeleteMethod(VectorItem item) {
	ILMethod* e = (ILMethod*)item;
	DeleteILMethod(e);
}

static void ILClass_ctor_delete(VectorItem item) {
	ILConstructor* e = (ILConstructor*)item;
	DeleteILConstructor(e);
}

static void ILClass_extend_delete(VectorItem item) {
	//FQCNCache* e = (FQCNCache*)item;
	//DeleteFQCNCache(e);
	GenericCache* e = (GenericCache*)item;
	DeleteGenericCache(e);
}

static void ILClass_DeleteTypeParameter(VectorItem item) {
	ILTypeParameter* e = (ILTypeParameter*)item;
	DeleteILTypeParameter(e);
}

static void DeleteILClass_operator_overload(VectorItem item) {
	ILOperatorOverload* e = (ILOperatorOverload*)item;
	DeleteILOperatorOverload(e);
}

static void ILClass_prop_delete(VectorItem item ) {
	ILProperty* e = (ILProperty*)item;
	DeleteILProperty(e);
}