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
	ret->tag = ilTYPE_CLASS_T;
	return ret;
}

Vector * GetMethodsILType(ILType * self) {
	if (self->tag == ilTYPE_CLASS_T) {
		return self->u.class_->method_list;
	} else if (self->tag == ilTYPE_INTERFACE_T) {
		return self->u.interface_->method_list;
	}
	return NULL;
}

Vector * GetSMethodsILType(ILType * self) {
	if (self->tag == ilTYPE_CLASS_T) {
		return self->u.class_->smethod_list;
	} else if (self->tag == ilTYPE_INTERFACE_T) {
		return NULL;
	}
	return NULL;
}

void AddConstructorILType(ILType * self, ILConstructor * ctor) {
	assert(self->tag == ilTYPE_CLASS_T);
	if (self->tag == ilTYPE_CLASS_T) {
	}
}

void AddFieldILType(ILType * self, ILField * field) {
	assert(self->tag == ilTYPE_CLASS_T);
	if (self->tag == ilTYPE_CLASS_T) {
		AddFieldILClass(self->u.class_, field);
	}
}

void AddPropertyILType(ILType* self, ILProperty* prop) {
	if (self->tag == ilTYPE_CLASS_T) {
		AddPropertyILClass(self->u.class_, prop);
	} else if(self->tag == ilTYPE_INTERFACE_T) {
		AddPropertyILInterface(self->u.interface_, prop);
	}
}

void AddMethodILType(ILType * self, ILMethod * method) {
	if (self->tag == ilTYPE_CLASS_T) {
		AddMethodILClass(self->u.class_, method);
	} else if (self->tag == ilTYPE_INTERFACE_T) {
		AddMethodILInterface(self->u.interface_, method);
	}
}

void DeleteILType(ILType * self) {
	if (self->tag == ilTYPE_CLASS_T) {
		DeleteILClass(self->u.class_);
	} else if (self->tag == ilTYPE_INTERFACE_T) {
		DeleteILInterface(self->u.interface_);
	} else if(self->tag == ilTYPE_ENUM_T) {
		DeleteILEnum(self->u.enum_);
	}
	MEM_FREE(self);
}

Vector* GetTypeParametersILType(ILType* self) {
	return self->tag == ilTYPE_INTERFACE_T ? self->u.interface_->GetParameterListType : self->u.class_->GetParameterListType;
}