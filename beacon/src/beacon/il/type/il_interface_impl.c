#include "il_interface_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../il_method.h"
#include "../il_type_parameter.h"
#include "../il_property.h"

//proto
static void ILInterface_fqcn_delete(VectorItem item);
static void ILInterface_DeleteMethod(VectorItem item);
static void ILInterface_DeleteTypeParameter(VectorItem item);
static void ILInterface_DeleteProperty(VectorItem item);

ILType * WrapILInterface(ILInterface * self) {
	ILType* ret = NewILType();
	ret->Tag = ILTYPE_INTERFACE_T;
	ret->Kind.Interface = self;
	return ret;
}

ILInterface * NewILInterface(StringView namev) {
	ILInterface* ret = (ILInterface*)MEM_MALLOC(sizeof(ILInterface));
	ret->Extends = NewVector();
	ret->Methods = NewVector();
	ret->Name = namev;
	ret->TypeParameters = NewVector();
	ret->Properties = NewVector();
	return ret;
}

void AddPropertyILInterface(ILInterface* self, ILProperty* prop) {
	PushVector(self->Properties, prop);
}

void AddMethodILInterface(ILInterface * self, ILMethod * method) {
	PushVector(self->Methods, method);
}

void DeleteILInterface(ILInterface * self) {
	DeleteVector(self->Extends, ILInterface_fqcn_delete);
	DeleteVector(self->Methods, ILInterface_DeleteMethod);
	DeleteVector(self->TypeParameters, ILInterface_DeleteTypeParameter);
	DeleteVector(self->Properties, ILInterface_DeleteProperty);
	MEM_FREE(self);
}
//private 
static void ILInterface_fqcn_delete(VectorItem item) {
	bc_GenericCache* e = (bc_GenericCache*)item;
	bc_DeleteGenericCache(e);
}

static void ILInterface_DeleteMethod(VectorItem item) {
	ILMethod* e = (ILMethod*)item;
	DeleteILMethod(e);
}

static void ILInterface_DeleteTypeParameter(VectorItem item) {
	ILTypeParameter* e = (ILTypeParameter*)item;
	DeleteILTypeParameter(e);
}

static void ILInterface_DeleteProperty(VectorItem item) {
	ILProperty* e = (ILProperty*)item;
	DeleteILProperty(e);
}