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

il_type * WrapILInterface(il_interface * self) {
	il_type* ret = NewILType();
	ret->tag = ilTYPE_INTERFACE_T;
	ret->u.interface_ = self;
	return ret;
}

il_interface * NewILInterface(string_view namev) {
	il_interface* ret = (il_interface*)MEM_MALLOC(sizeof(il_interface));
	ret->extends_list = NewVector();
	ret->method_list = NewVector();
	ret->namev = namev;
	ret->type_parameter_list = NewVector();
	ret->prop_list = NewVector();
	return ret;
}

void AddPropertyILInterface(il_interface* self, il_property* prop) {
	PushVector(self->prop_list, prop);
}

void AddMethodILInterface(il_interface * self, il_method * method) {
	PushVector(self->method_list, method);
}

void DeleteILInterface(il_interface * self) {
	DeleteVector(self->extends_list, il_interface_fqcn_delete);
	DeleteVector(self->method_list, il_interface_DeleteMethod);
	DeleteVector(self->type_parameter_list, il_interface_DeleteTypeParameter);
	DeleteVector(self->prop_list, il_interface_DeleteProperty);
	MEM_FREE(self);
}
//private 
static void il_interface_fqcn_delete(VectorItem item) {
	generic_cache* e = (generic_cache*)item;
	generic_cache_delete(e);
}

static void il_interface_DeleteMethod(VectorItem item) {
	il_method* e = (il_method*)item;
	DeleteILMethod(e);
}

static void il_interface_DeleteTypeParameter(VectorItem item) {
	il_type_parameter* e = (il_type_parameter*)item;
	DeleteILTypeParameter(e);
}

static void il_interface_DeleteProperty(VectorItem item) {
	il_property* e = (il_property*)item;
	DeleteILProperty(e);
}