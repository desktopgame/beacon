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

bc_ILType * bc_WrapILInterface(bc_ILInterface * self) {
	bc_ILType* ret = bc_NewILType();
	ret->Tag = ILTYPE_INTERFACE_T;
	ret->Kind.Interface = self;
	return ret;
}

bc_ILInterface * bc_NewILInterface(bc_StringView namev) {
	bc_ILInterface* ret = (bc_ILInterface*)MEM_MALLOC(sizeof(bc_ILInterface));
	ret->Extends = bc_NewVector();
	ret->Methods = bc_NewVector();
	ret->Name = namev;
	ret->TypeParameters = bc_NewVector();
	ret->Properties = bc_NewVector();
	return ret;
}

void bc_AddPropertyILInterface(bc_ILInterface* self, bc_ILProperty* prop) {
	bc_PushVector(self->Properties, prop);
}

void bc_AddMethodILInterface(bc_ILInterface * self, bc_ILMethod * method) {
	bc_PushVector(self->Methods, method);
}

void bc_DeleteILInterface(bc_ILInterface * self) {
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
	bc_ILMethod* e = (bc_ILMethod*)item;
	bc_DeleteILMethod(e);
}

static void ILInterface_DeleteTypeParameter(bc_VectorItem item) {
	bc_ILTypeParameter* e = (bc_ILTypeParameter*)item;
	bc_DeleteILTypeParameter(e);
}

static void ILInterface_DeleteProperty(bc_VectorItem item) {
	bc_ILProperty* e = (bc_ILProperty*)item;
	bc_DeleteILProperty(e);
}