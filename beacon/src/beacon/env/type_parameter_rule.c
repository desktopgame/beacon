#include "type_parameter_rule.h"
#include "../util/mem.h"
#include "../il/il_type_parameter_rule.h"
#include "../il/il_context.h"
#include "../vm/enviroment.h"
#include "../env/namespace.h"
#include "../util/vector.h"
#include "../env/generic_type.h"
#include <assert.h>

type_parameter_rule * type_parameter_rule_new() {
	type_parameter_rule* ret = (type_parameter_rule*)MEM_MALLOC(sizeof(type_parameter_rule));
	ret->tag = type_parameter_rule_tag_polymorphic;
	return ret;
}

type_parameter_rule * type_parameter_rule_dup(il_type_parameter_rule * src, il_context* cache) {
	type_parameter_rule* ret = type_parameter_rule_new();
	if (src->tag == il_type_parameter_rule_polymorphic) {
		ret->tag = type_parameter_rule_tag_polymorphic;
		ret->u.gtype_ = generic_cache_gtype(src->u.fqcn_, (namespace_*)vector_top(cache->namespace_vec), cache);
		assert(ret->u.gtype_ != NULL);
	}
	return ret;
}

void type_parameter_rule_list_dup(vector * ilSource, vector * sgDest, il_context* cache) {
	for (int i = 0; i < ilSource->length; i++) {
		il_type_parameter_rule* e = (il_type_parameter_rule*)vector_at(ilSource, i);
		vector_push(sgDest, type_parameter_rule_dup(e, cache));
	}
}

void type_parameter_rule_list_print(vector * v) {
	//FIXME:il_type_parameter_ruleのコピペ
	if (v->length == 0) {
		return;
	}
	text_printf("(");
	for (int i = 0; i < v->length; i++) {
		type_parameter_rule* e = (type_parameter_rule*)vector_at(v, i);
		if (e->tag == type_parameter_rule_tag_polymorphic) {
			generic_type_print(e->u.gtype_);
		}
		if (i != v->length - 1) {
			text_printf(", ");
		}
	}
	text_printf(")");
}

void type_parameter_rule_delete(type_parameter_rule * self) {
	MEM_FREE(self);
}
