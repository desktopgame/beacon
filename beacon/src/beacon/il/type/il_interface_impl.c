#include "il_interface_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../il_method.h"
#include "../il_type_parameter.h"
#include "../il_property.h"

//proto
static void il_interface_fqcn_delete(VectorItem item);
static void il_interface_DeleteMethod(VectorItem item);
static void il_interface_DeleteTypeParameter(VectorItem item);
static void il_interface_DeleteProperty(VectorItem item);

ILType * WrapILInterface(il_interface * self) {
	ILType* ret = NewILType();
	ret->tag = ilTYPE_INTERFACE_T;
	ret->u.interface_ = self;
	return ret;
}

il_interface * NewILInterface(StringView namev) {
	il_interface* ret = (il_interface*)MEM_MALLOC(sizeof(il_interface));
	ret->extends_list = NewVector();
	ret->method_list = NewVector();
	ret->namev = namev;
	ret->GetParameterListType = NewVector();
	ret->prop_list = NewVector();
	return ret;
}

void AddPropertyILInterface(il_interface* self, ILProperty* prop) {
	PushVector(self->prop_list, prop);
}

void AddMethodILInterface(il_interface * self, ILMethod * method) {
	PushVector(self->method_list, method);
}

void DeleteILInterface(il_interface * self) {
	DeleteVector(self->extends_list, il_interface_fqcn_delete);
	DeleteVector(self->method_list, il_interface_DeleteMethod);
	DeleteVector(self->GetParameterListType, il_interface_DeleteTypeParameter);
	DeleteVector(self->prop_list, il_interface_DeleteProperty);
	MEM_FREE(self);
}
//private 
static void il_interface_fqcn_delete(VectorItem item) {
	GenericCache* e = (GenericCache*)item;
	DeleteGenericCache(e);
}

static void il_interface_DeleteMethod(VectorItem item) {
	ILMethod* e = (ILMethod*)item;
	DeleteILMethod(e);
}

static void il_interface_DeleteTypeParameter(VectorItem item) {
	ILTypeParameter* e = (ILTypeParameter*)item;
	DeleteILTypeParameter(e);
}

static void il_interface_DeleteProperty(VectorItem item) {
	ILProperty* e = (ILProperty*)item;
	DeleteILProperty(e);
}