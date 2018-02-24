#include "generic_cache.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "type_impl.h"
#include "generic_type.h"
#include <assert.h>

//proto
static void generic_cache_tree_delete(vector_item item);

generic_cache * generic_cache_new() {
	generic_cache* ret = (generic_cache*)MEM_MALLOC(sizeof(generic_cache));
	ret->fqcn = fqcn_cache_new();
	ret->type_args = vector_new();
	return ret;
}

generic_type * generic_cache_gtype(generic_cache * self, namespace_ * scope, il_load_cache* cache) {
	type* core_type = generic_cache_type(self, scope);
	generic_type* ret = generic_type_new(core_type);
	//もし名前空間でラッピングされていなくて、
	//なおかつ型が見つからないなら、
	//仮想型(List<T>のT)として扱う。
	if (self->fqcn->scope_vec->length == 0 &&
		core_type == NULL) {
		//読み込み中の型
		type* container = (type*)vector_top(cache->type_vec);
		ret->virtual_type_index = type_for_generic_index(container, self->fqcn->name);
		//しかし、Tに対して追加の型変数を与えることはできません。
		assert(self->type_args->length == 0 && ret->virtual_type_index != -1);
		return ret;
	}
	assert(core_type->tag != type_enum);
	for (int i = 0; i < self->type_args->length; i++) {
		generic_cache* e = (generic_cache*)vector_at(self->type_args, i);
		generic_type* child = generic_cache_gtype(e, scope, cache);
		vector_push(ret->type_args_list, child);
	}
	if (core_type->tag == type_class) {
		vector_push(core_type->u.class_->generic_instance_list, ret);
	} else if (core_type->tag == type_interface) {
		vector_push(core_type->u.interface_->generic_instance_list, ret);
	}
	return ret;
}

type * generic_cache_type(generic_cache * self, namespace_ * scope) {
	type* ret = fqcn_type(self->fqcn, scope);
	return ret;
}

class_ * generic_cache_class(generic_cache * self, namespace_ * scope) {
	type* tp = generic_cache_type(self, scope);
	if (tp == NULL || tp->tag == type_interface) {
		return NULL;
	}
	return tp->u.class_;
}

interface_ * generic_cache_interface(generic_cache * self, namespace_ * scope) {
	type* tp = generic_cache_type(self, scope);
	if (tp == NULL || tp->tag == type_class) {
		return NULL;
	}
	return tp->u.interface_;
}

void generic_cache_print(generic_cache * self) {
	fqcn_cache_print(self->fqcn);
	if (self->type_args->length <= 0) {
		return;
	}
	text_printf("<");
	for (int i = 0; i < self->type_args->length; i++) {
		generic_cache* e = (generic_cache*)vector_at(self->type_args, i);
		generic_cache_print(e);
		//il_type_parameter_rule_list_print(e->rule_vec);
		if (i != self->type_args->length - 1) {
			text_printf(", ");
		}
	}
	text_printf(">");
}

void generic_cache_dump(generic_cache * self, int depth) {
	text_putindent(depth);
	generic_cache_print(self);
	text_putline();
}

void generic_cache_delete(generic_cache * self) {
	fqcn_cache_delete(self->fqcn);
	vector_delete(self->type_args, generic_cache_tree_delete);
	MEM_FREE(self);
}
//private
static void generic_cache_tree_delete(vector_item item) {
	generic_cache* e = (generic_cache*)item;
	generic_cache_delete(e);
}