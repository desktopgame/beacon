#include "il_interface_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../il_method.h"
#include "../il_type_parameter.h"
#include "../il_property.h"

//proto
static void ILInterface_fqcn_delete(bc_VectorItem item);
static void ILInterface_DeleteMethod(bc_VectorItem item);
static void ILInterface_DeleteTypeParameter(bc_VectorItem item);
static void ILInterface_DeleteProperty(bc_VectorItem item);

ILType * WrapILInterface(ILInterface * self) {
	ILType* ret = NewILType();
	ret->Tag = ILTYPE_INTERFACE_T;
	ret->Kind.Interface = self;
	return ret;
}

ILInterface * NewILInterface(bc_StringView namev) {
	ILInterface* ret = (ILInterface*)MEM_MALLOC(sizeof(ILInterface));
	ret->Extends = bc_NewVector();
	ret->Methods = bc_NewVector();
	ret->Name = namev;
	ret->TypeParameters = bc_NewVector();
	ret->Properties = bc_NewVector();
	return ret;
}

void AddPropertyILInterface(ILInterface* self, ILProperty* prop) {
	bc_PushVector(self->Properties, prop);
}

void AddMethodILInterface(ILInterface * self, ILMethod * method) {
	bc_PushVector(self->Methods, method);
}

void DeleteILInterface(ILInterface * self) {
	bc_DeleteVector(self->Extends, ILInterface_fqcn_delete);
	bc_DeleteVector(self->Methods, ILInterface_DeleteMethod);
	bc_DeleteVector(self->TypeParameters, ILInterface_DeleteTypeParameter);
	bc_DeleteVector(self->Properties, ILInterface_DeleteProperty);
	MEM_FREE(self);
}
//private 
static void ILInterface_fqcn_delete(bc_VectorItem item) {
	bc_GenericCache* e = (bc_GenericCache*)item;
	bc_DeleteGenericCache(e);
}

static void ILInterface_DeleteMethod(bc_VectorItem item) {
	ILMethod* e = (ILMethod*)item;
	DeleteILMethod(e);
}

static void ILInterface_DeleteTypeParameter(bc_VectorItem item) {
	ILTypeParameter* e = (ILTypeParameter*)item;
	DeleteILTypeParameter(e);
}

static void ILInterface_DeleteProperty(bc_VectorItem item) {
	ILProperty* e = (ILProperty*)item;
	DeleteILProperty(e);
}