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
	ret->Name = namev;
	ret->Extends = NewVector();
	ret->Fields = NewVector();
	ret->StaticFields = NewVector();
	ret->Methods = NewVector();
	ret->StaticMethods = NewVector();
	ret->Constructors = NewVector();
	ret->TypeParameters = NewVector();
	ret->OperatorOverloads = NewVector();
	ret->Properties = NewVector();
	ret->StaticProperties = NewVector();
	ret->IsAbstract = false;
	return ret;
}

void AddFieldILClass(ILClass * self, ILField * f) {
	if (bc_IsStaticModifier(f->Modifier)) {
		PushVector(self->StaticFields, f);
	} else {
		PushVector(self->Fields, f);
	}
}

void AddPropertyILClass(ILClass* self, ILProperty* prop) {
	if(bc_IsStaticModifier(prop->Modifier)) {
		PushVector(self->StaticProperties, prop);
	} else {
		PushVector(self->Properties, prop);
	}
}

void AddMethodILClass(ILClass * self, ILMethod * m) {
	if (bc_IsStaticModifier(m->Modifier)) {
		PushVector(self->StaticMethods, m);
	} else {
		PushVector(self->Methods, m);
	}
}

void DeleteILClass(ILClass * self) {
	if (self == NULL) {
		return;
	}
	//printf("free class %s\n", self->name);
	//MEM_FREE(self->super);
	DeleteVector(self->Fields, ILClass_DeleteField);
	DeleteVector(self->StaticFields, ILClass_DeleteField);
	DeleteVector(self->Methods, ILClass_DeleteMethod);
	DeleteVector(self->StaticMethods, ILClass_DeleteMethod);
	DeleteVector(self->Constructors, ILClass_ctor_delete);
	DeleteVector(self->Extends, ILClass_extend_delete);
	DeleteVector(self->TypeParameters, ILClass_DeleteTypeParameter);
	DeleteVector(self->OperatorOverloads, DeleteILClass_operator_overload);
	DeleteVector(self->Properties, ILClass_prop_delete);
	DeleteVector(self->StaticProperties, ILClass_prop_delete);
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
	bc_GenericCache* e = (bc_GenericCache*)item;
	bc_DeleteGenericCache(e);
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