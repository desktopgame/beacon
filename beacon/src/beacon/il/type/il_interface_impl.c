#include "il_interface_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../il_method.h"
#include "../il_type_parameter.h"
#include "../il_property.h"

//proto
static void il_interface_fqcn_delete(vector_item item);
static void il_interface_method_delete(vector_item item);
static void il_interface_type_parameter_delete(vector_item item);
static void il_interface_property_delete(vector_item item);

il_type * il_type_wrap_interface(il_interface * self) {
	il_type* ret = il_type_new();
	ret->tag = iltype_interface_T;
	ret->u.interface_ = self;
	return ret;
}

il_interface * il_interface_new(string_view namev) {
	il_interface* ret = (il_interface*)MEM_MALLOC(sizeof(il_interface));
	ret->extends_list = vector_new();
	ret->method_list = vector_new();
	ret->namev = namev;
	ret->type_parameter_list = vector_new();
	ret->prop_list = vector_new();
	return ret;
}

void il_interface_add_property(il_interface* self, il_property* prop) {
	vector_push(self->prop_list, prop);
}

void il_interface_add_method(il_interface * self, il_method * method) {
	vector_push(self->method_list, method);
}

void il_interface_delete(il_interface * self) {
	vector_delete(self->extends_list, il_interface_fqcn_delete);
	vector_delete(self->method_list, il_interface_method_delete);
	vector_delete(self->type_parameter_list, il_interface_type_parameter_delete);
	vector_delete(self->prop_list, il_interface_property_delete);
	MEM_FREE(self);
}
//private 
static void il_interface_fqcn_delete(vector_item item) {
	generic_cache* e = (generic_cache*)item;
	generic_cache_delete(e);
}

static void il_interface_method_delete(vector_item item) {
	il_method* e = (il_method*)item;
	il_method_delete(e);
}

static void il_interface_type_parameter_delete(vector_item item) {
	il_type_parameter* e = (il_type_parameter*)item;
	il_type_parameter_delete(e);
}

static void il_interface_property_delete(vector_item item) {
	il_property* e = (il_property*)item;
	il_property_delete(e);
}