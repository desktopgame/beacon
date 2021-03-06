#include "il_type_parameter.h"
#include "../util/mem.h"
#include "../util/text.h"

//proto
static void il_type_parameter_rule_list_delete(vector_item item);

il_type_parameter * il_type_parameter_new(string_view namev) {
	il_type_parameter* ret = (il_type_parameter*)MEM_MALLOC(sizeof(il_type_parameter));
	ret->kind = il_type_parameter_kind_default_T;
	ret->namev = namev;
	return ret;
}

void il_type_parameter_list_print(vector * v) {
	if (v->length <= 0) {
		return;
	}
	printf("<");
	for (int i = 0; i < v->length; i++) {
		il_type_parameter* e = (il_type_parameter*)vector_at(v, i);
		if (e->kind == il_type_parameter_kind_in_T) {
			printf("in ");
		} else if (e->kind == il_type_parameter_kind_out_T) {
			printf("out ");
		}
		printf("%s", string_pool_ref2str(e->namev));
		if (i != v->length - 1) {
			printf(", ");
		}
	}
	printf(">");
}

void il_type_parameter_delete(il_type_parameter * self) {
	MEM_FREE(self);
}
//private
static void il_type_parameter_rule_list_delete(vector_item item) {
}