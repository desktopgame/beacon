#include "il_type_interface.h"
#include "../util/mem.h"
#include "il_TYPE_IMPL.h"
#include "il_property.h"
#include "il_constructor.h"
#include "il_field.h"
#include "il_method.h"
#include <assert.h>

bc_ILType * bc_NewILType() {
	bc_ILType* ret = (bc_ILType*)MEM_MALLOC(sizeof(bc_ILType));
	ret->Tag = ILTYPE_CLASS_T;
	return ret;
}

bc_Vector * bc_GetMethodsILType(bc_ILType * self) {
	if (self->Tag == ILTYPE_CLASS_T) {
		return self->Kind.Class->Methods;
	} else if (self->Tag == ILTYPE_INTERFACE_T) {
		return self->Kind.Interface->Methods;
	}
	return NULL;
}

bc_Vector * bc_GetSMethodsILType(bc_ILType * self) {
	if (self->Tag == ILTYPE_CLASS_T) {
		return self->Kind.Class->StaticMethods;
	} else if (self->Tag == ILTYPE_INTERFACE_T) {
		return NULL;
	}
	return NULL;
}

void bc_AddConstructorILType(bc_ILType * self, bc_ILConstructor * ctor) {
	assert(self->Tag == ILTYPE_CLASS_T);
	if (self->Tag == ILTYPE_CLASS_T) {
	}
}

void bc_AddFieldILType(bc_ILType * self, bc_ILField * field) {
	assert(self->Tag == ILTYPE_CLASS_T);
	if (self->Tag == ILTYPE_CLASS_T) {
		bc_AddFieldILClass(self->Kind.Class, field);
	}
}

void bc_AddPropertyILType(bc_ILType* self, bc_ILProperty* prop) {
	if (self->Tag == ILTYPE_CLASS_T) {
		bc_AddPropertyILClass(self->Kind.Class, prop);
	} else if(self->Tag == ILTYPE_INTERFACE_T) {
		bc_AddPropertyILInterface(self->Kind.Interface, prop);
	}
}

void bc_AddMethodILType(bc_ILType * self, bc_ILMethod * method) {
	if (self->Tag == ILTYPE_CLASS_T) {
		bc_AddMethodILClass(self->Kind.Class, method);
	} else if (self->Tag == ILTYPE_INTERFACE_T) {
		bc_AddMethodILInterface(self->Kind.Interface, method);
	}
}

void bc_DeleteILType(bc_ILType * self) {
	if (self->Tag == ILTYPE_CLASS_T) {
		bc_DeleteILClass(self->Kind.Class);
	} else if (self->Tag == ILTYPE_INTERFACE_T) {
		bc_DeleteILInterface(self->Kind.Interface);
	} else if(self->Tag == ILTYPE_ENUM_T) {
		bc_DeleteILEnum(self->Kind.Enum);
	}
	MEM_FREE(self);
}

bc_Vector* bc_GetTypeParametersILType(bc_ILType* self) {
	return self->Tag == ILTYPE_INTERFACE_T ? self->Kind.Interface->TypeParameters : self->Kind.Class->TypeParameters;
}