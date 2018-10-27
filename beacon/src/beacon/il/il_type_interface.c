#include "il_type_interface.h"
#include "../util/mem.h"
#include "il_TYPE_IMPL.h"
#include "il_property.h"
#include "il_constructor.h"
#include "il_field.h"
#include "il_method.h"
#include <assert.h>

ILType * NewILType() {
	ILType* ret = (ILType*)MEM_MALLOC(sizeof(ILType));
	ret->Tag = ILTYPE_CLASS_T;
	return ret;
}

Vector * GetMethodsILType(ILType * self) {
	if (self->Tag == ILTYPE_CLASS_T) {
		return self->Kind.Class->method_list;
	} else if (self->Tag == ILTYPE_INTERFACE_T) {
		return self->Kind.Interface->method_list;
	}
	return NULL;
}

Vector * GetSMethodsILType(ILType * self) {
	if (self->Tag == ILTYPE_CLASS_T) {
		return self->Kind.Class->smethod_list;
	} else if (self->Tag == ILTYPE_INTERFACE_T) {
		return NULL;
	}
	return NULL;
}

void AddConstructorILType(ILType * self, ILConstructor * ctor) {
	assert(self->Tag == ILTYPE_CLASS_T);
	if (self->Tag == ILTYPE_CLASS_T) {
	}
}

void AddFieldILType(ILType * self, ILField * field) {
	assert(self->Tag == ILTYPE_CLASS_T);
	if (self->Tag == ILTYPE_CLASS_T) {
		AddFieldILClass(self->Kind.Class, field);
	}
}

void AddPropertyILType(ILType* self, ILProperty* prop) {
	if (self->Tag == ILTYPE_CLASS_T) {
		AddPropertyILClass(self->Kind.Class, prop);
	} else if(self->Tag == ILTYPE_INTERFACE_T) {
		AddPropertyILInterface(self->Kind.Interface, prop);
	}
}

void AddMethodILType(ILType * self, ILMethod * method) {
	if (self->Tag == ILTYPE_CLASS_T) {
		AddMethodILClass(self->Kind.Class, method);
	} else if (self->Tag == ILTYPE_INTERFACE_T) {
		AddMethodILInterface(self->Kind.Interface, method);
	}
}

void DeleteILType(ILType * self) {
	if (self->Tag == ILTYPE_CLASS_T) {
		DeleteILClass(self->Kind.Class);
	} else if (self->Tag == ILTYPE_INTERFACE_T) {
		DeleteILInterface(self->Kind.Interface);
	} else if(self->Tag == ILTYPE_ENUM_T) {
		DeleteILEnum(self->Kind.Enum);
	}
	MEM_FREE(self);
}

Vector* GetTypeParametersILType(ILType* self) {
	return self->Tag == ILTYPE_INTERFACE_T ? self->Kind.Interface->GetParameterListType : self->Kind.Class->GetParameterListType;
}