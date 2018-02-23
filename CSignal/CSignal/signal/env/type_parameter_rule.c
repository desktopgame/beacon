#include "type_parameter_rule.h"
#include "../util/mem.h"
#include "../il/il_type_parameter_rule.h"
#include "../il/il_load_cache.h"
#include "../vm/enviroment.h"
#include "../env/namespace.h"
#include "../util/vector.h"

type_parameter_rule * type_parameter_rule_new() {
	type_parameter_rule* ret = (type_parameter_rule*)MEM_MALLOC(sizeof(type_parameter_rule));
	ret->tag = type_parameter_rule_tag_polymorphic;
	return ret;
}

type_parameter_rule * type_parameter_rule_dup(il_type_parameter_rule * src, il_load_cache* cache) {
	type_parameter_rule* ret = type_parameter_rule_new();
	if (src->tag == il_type_parameter_rule_polymorphic) {
		ret->tag = il_type_parameter_rule_polymorphic;
		ret->u.type_ = fqcn_type(src->u.fqcn_, (namespace_*)vector_top(cache->namespace_vec));
	}
	return ret;
}

void type_parameter_rule_list_dup(vector * ilSource, vector * sgDest, il_load_cache* cache) {
	for (int i = 0; i < ilSource->length; i++) {
		il_type_parameter_rule* e = (il_type_parameter_rule*)vector_at(ilSource, i);
		vector_push(sgDest, type_parameter_rule_dup(e, cache));
	}
}

void type_parameter_rule_delete(type_parameter_rule * self) {
	MEM_FREE(self);
}
