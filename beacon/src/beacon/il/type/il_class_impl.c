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
static void ILClass_DeleteField(bc_VectorItem item);
static void ILClass_DeleteMethod(bc_VectorItem item);
static void ILClass_ctor_delete(bc_VectorItem item);
static void ILClass_extend_delete(bc_VectorItem item);
static void ILClass_DeleteTypeParameter(bc_VectorItem item);
static void DeleteILClass_operator_overload(bc_VectorItem item);
static void ILClass_prop_delete(bc_VectorItem item );

bc_ILType * WrapILClass(ILClass * self) {
	bc_ILType* ret = bc_NewILType();
	ret->Tag = ILTYPE_CLASS_T;
	ret->Kind.Class = self;
	return ret;
}

ILClass* NewILClass(bc_StringView namev) {
	ILClass* ret = (ILClass*)MEM_MALLOC(sizeof(ILClass));
	ret->Name = namev;
	ret->Extends = bc_NewVector();
	ret->Fields = bc_NewVector();
	ret->StaticFields = bc_NewVector();
	ret->Methods = bc_NewVector();
	ret->StaticMethods = bc_NewVector();
	ret->Constructors = bc_NewVector();
	ret->TypeParameters = bc_NewVector();
	ret->OperatorOverloads = bc_NewVector();
	ret->Properties = bc_NewVector();
	ret->StaticProperties = bc_NewVector();
	ret->IsAbstract = false;
	return ret;
}

void AddFieldILClass(ILClass * self, bc_ILField * f) {
	if (bc_IsStaticModifier(f->Modifier)) {
		bc_PushVector(self->StaticFields, f);
	} else {
		bc_PushVector(self->Fields, f);
	}
}

void AddPropertyILClass(ILClass* self, bc_ILProperty* prop) {
	if(bc_IsStaticModifier(prop->Modifier)) {
		bc_PushVector(self->StaticProperties, prop);
	} else {
		bc_PushVector(self->Properties, prop);
	}
}

void AddMethodILClass(ILClass * self, bc_ILMethod * m) {
	if (bc_IsStaticModifier(m->Modifier)) {
		bc_PushVector(self->StaticMethods, m);
	} else {
		bc_PushVector(self->Methods, m);
	}
}

void DeleteILClass(ILClass * self) {
	if (self == NULL) {
		return;
	}
	//printf("free class %s\n", self->name);
	//MEM_FREE(self->super);
	bc_DeleteVector(self->Fields, ILClass_DeleteField);
	bc_DeleteVector(self->StaticFields, ILClass_DeleteField);
	bc_DeleteVector(self->Methods, ILClass_DeleteMethod);
	bc_DeleteVector(self->StaticMethods, ILClass_DeleteMethod);
	bc_DeleteVector(self->Constructors, ILClass_ctor_delete);
	bc_DeleteVector(self->Extends, ILClass_extend_delete);
	bc_DeleteVector(self->TypeParameters, ILClass_DeleteTypeParameter);
	bc_DeleteVector(self->OperatorOverloads, DeleteILClass_operator_overload);
	bc_DeleteVector(self->Properties, ILClass_prop_delete);
	bc_DeleteVector(self->StaticProperties, ILClass_prop_delete);
	MEM_FREE(self);
}

//private
static void ILClass_DeleteField(bc_VectorItem item) {
	bc_ILField* e = (bc_ILField*)item;
	bc_DeleteILField(e);
}

static void ILClass_DeleteMethod(bc_VectorItem item) {
	bc_ILMethod* e = (bc_ILMethod*)item;
	bc_DeleteILMethod(e);
}

static void ILClass_ctor_delete(bc_VectorItem item) {
	bc_ILConstructor* e = (bc_ILConstructor*)item;
	bc_DeleteILConstructor(e);
}

static void ILClass_extend_delete(bc_VectorItem item) {
	//FQCNCache* e = (FQCNCache*)item;
	//DeleteFQCNCache(e);
	bc_GenericCache* e = (bc_GenericCache*)item;
	bc_DeleteGenericCache(e);
}

static void ILClass_DeleteTypeParameter(bc_VectorItem item) {
	bc_ILTypeParameter* e = (bc_ILTypeParameter*)item;
	bc_DeleteILTypeParameter(e);
}

static void DeleteILClass_operator_overload(bc_VectorItem item) {
	bc_ILOperatorOverload* e = (bc_ILOperatorOverload*)item;
	bc_DeleteILOperatorOverload(e);
}

static void ILClass_prop_delete(bc_VectorItem item ) {
	bc_ILProperty* e = (bc_ILProperty*)item;
	bc_DeleteILProperty(e);
}