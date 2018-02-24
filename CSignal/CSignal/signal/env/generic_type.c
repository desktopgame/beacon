#include "generic_type.h"
#include "type_interface.h"
#include "../util/mem.h"
#include "../util/text.h"

//proto
static void generic_type_tree_delete(vector_item item);

generic_type * generic_type_new(type * core_type) {
	generic_type* ret = (generic_type*)MEM_MALLOC(sizeof(generic_type));
	ret->core_type = core_type;
	ret->type_args_list = vector_new();
	ret->virtual_type_index = -1;
	return ret;
}

bool generic_type_assignable(generic_type * left, generic_type * right) {
	//完全に同じポインタなら比較は不要
	if (left == right) {
		return true;
	}
	//基本型か型引数の数が違うなら false
	if (left->core_type != right->core_type ||
		left->type_args_list->length != right->type_args_list) {
		return false;
	}
	//型引数が 0 個なら比較不要
	if (left->type_args_list->length == 0 &&
		right->type_args_list->length == 0) {
		return true;
	}
	//TODO: in/out の考慮
	//基本型と型引数が0個以上で一致するならそれらを比較
	bool ret = true;
	for (int i = 0; i < left->type_args_list->length; i++) {
		generic_type* le = (generic_type*)vector_at(left->type_args_list, i);
		generic_type* re = (generic_type*)vector_at(right->type_args_list, i);
		if (!generic_type_assignable(le, re)) {
			ret = false;
			break;
		}
	}
	return ret;
}

void generic_type_print(generic_type * self) {
	if (self->virtual_type_index != -1) {
		text_printf("[%d]", self->virtual_type_index);
	} else {
		text_printf("%s", type_name(self->core_type));
	}
	if (self->type_args_list->length == 0) {
		return;
	}
	text_printf("<");
	for (int i = 0; i < self->type_args_list->length; i++) {
		generic_type* e = (generic_type*)vector_at(self->type_args_list, i);
		generic_type_print(e);
		if (i != self->type_args_list->length - 1) {
			text_printf(",");
		}
	}
	text_printf(">");
}

void generic_type_delete(generic_type * self) {
	vector_delete(self->type_args_list, generic_type_tree_delete);
	MEM_FREE(self);
}

//private
static void generic_type_tree_delete(vector_item item) {
	generic_type* e = (generic_type*)item;
	generic_type_delete(e);
}