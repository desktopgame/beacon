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
	ret->tag = iltype_interface;
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

void il_interface_dump(il_interface * self, int depth) {
	text_putindent(depth);
	text_printf("interface %s", string_pool_ref2str(self->namev));
	il_type_parameter_list_print(self->type_parameter_list);
	text_putline();
	//継承するインターフェイスの一覧を出力
	for (int i = 0; i < self->extends_list->length; i++) {
		generic_cache* e = (generic_cache*)vector_at(self->extends_list, i);
		generic_cache_dump(e, depth + 1);
	}

	for (int i = 0; i < self->method_list->length; i++) {
		vector_item e = vector_at(self->method_list, i);
		il_method* ilm = (il_method*)e;
		il_method_dump(ilm, depth + 1);
	}
	for(int i=0; i<self->prop_list->length; i++) {
		il_property* e = vector_at(self->prop_list, i);
		il_property_dump(e, depth + 1);
	}
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