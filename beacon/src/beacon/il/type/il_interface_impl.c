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
	ret->extends_list = NewVector();
	ret->method_list = NewVector();
	ret->namev = namev;
	ret->GetParameterListType = NewVector();
	ret->prop_list = NewVector();
	return ret;
}

void AddPropertyILInterface(ILInterface* self, ILProperty* prop) {
	PushVector(self->prop_list, prop);
}

void AddMethodILInterface(ILInterface * self, ILMethod * method) {
	PushVector(self->method_list, method);
}

void DeleteILInterface(ILInterface * self) {
	DeleteVector(self->extends_list, ILInterface_fqcn_delete);
	DeleteVector(self->method_list, ILInterface_DeleteMethod);
	DeleteVector(self->GetParameterListType, ILInterface_DeleteTypeParameter);
	DeleteVector(self->prop_list, ILInterface_DeleteProperty);
	MEM_FREE(self);
}
//private 
static void ILInterface_fqcn_delete(VectorItem item) {
	GenericCache* e = (GenericCache*)item;
	DeleteGenericCache(e);
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