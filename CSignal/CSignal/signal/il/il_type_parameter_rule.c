#include "il_type_parameter_rule.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../util/vector.h"

il_type_parameter_rule * il_type_parameter_rule_new() {
	il_type_parameter_rule* ret = (il_type_parameter_rule*)MEM_MALLOC(sizeof(il_type_parameter_rule));
	ret->tag = il_type_parameter_rule_polymorphic;
	return ret;
}

void il_type_parameter_rule_list_print(vector * v) {
	if (v->length == 0) {
		return;
	}
	text_printf("(");
	for (int i = 0; i < v->length; i++) {
		il_type_parameter_rule* e = (il_type_parameter_rule*)vector_at(v, i);
		if (e->tag == il_type_parameter_rule_polymorphic) {
			fqcn_cache_print(e->u.fqcn_);
		}
		if (i != v->length - 1) {
			text_printf(", ");
		}
	}
	text_printf(")");
}

void il_type_parameter_rule_delete(il_type_parameter_rule * self) {
	if (self->tag == il_type_parameter_rule_polymorphic) {
		fqcn_cache_delete(self->u.fqcn_);
	}
	MEM_FREE(self);
}
