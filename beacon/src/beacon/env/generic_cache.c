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

/*
generic_type * generic_cache_gtype(generic_cache * self, namespace_ * scope, il_context* ilctx) {
	type* core_type = generic_cache_type(self, scope);
	//もし名前空間でラッピングされていなくて、
	//なおかつ型が見つからないなら、
	//仮想型(List<T>のT)として扱う。
	if (self->fqcn->scope_vec->length == 0 &&
		core_type == NULL) {
		//読み込み中の型
		generic_type* ret = generic_type_new(core_type);
		type* container = (type*)vector_top(ilctx->type_vec);
		ret->u.type_ = container;
		ret->tag = generic_type_tag_class;
		ret->virtual_type_index = type_for_generic_index(container, self->fqcn->name);
		//見つからなかったのでメソッドから調べる
		if (ret->virtual_type_index == -1) {
			method* m = (method*)vector_top(ilctx->method_vec);
			ret->u.type_ = m->parent;
			ret->tag = generic_type_tag_method;
			ret->virtual_type_index = method_for_generic_index(m, self->fqcn->name);
		}
		//しかし、Tに対して追加の型変数を与えることはできません。
		assert(self->type_args->length == 0);
		assert(ret != NULL);
		return ret;
	}
	//型変数がない
	if (self->type_args->length == 0) {
		if(core_type->tag == type_class) {
			type_init_generic(core_type, core_type->u.class_->type_parameter_list->length);
		} else if(core_type->tag == type_interface) {
			type_init_generic(core_type, core_type->u.interface_->type_parameter_list->length);
		}
		assert(core_type->generic_self != NULL);
		return core_type->generic_self;
	}
	generic_type* ret2 = generic_type_new(core_type);
	assert(core_type->tag != type_enum);
	for (int i = 0; i < self->type_args->length; i++) {
		generic_cache* e = (generic_cache*)vector_at(self->type_args, i);
		generic_type* child = generic_cache_gtype(e, scope, ilctx);
		generic_type_addargs(ret2, child);
	}
	assert(ret2 != NULL);
	return ret2;
}
*/

generic_type * generic_cache_gtypeloc(generic_cache * self, namespace_ * scope, il_context* ilctx, const char* filename, int lineno) {
	type* core_type = generic_cache_type(self, scope);
	//もし名前空間でラッピングされていなくて、
	//なおかつ型が見つからないなら、
	//仮想型(List<T>のT)として扱う。
	if (self->fqcn->scope_vec->length == 0 &&
		core_type == NULL) {
		//読み込み中の型
		generic_type* ret = generic_type_malloc(core_type, filename, lineno);
		type* container = (type*)vector_top(ilctx->type_vec);
		ret->u.type_ = container;
		ret->tag = generic_type_tag_class;
		ret->virtual_type_index = type_for_generic_index(container, self->fqcn->name);
		//見つからなかったのでメソッドから調べる
		if (ret->virtual_type_index == -1) {
			method* m = (method*)vector_top(ilctx->method_vec);
			ret->u.type_ = m->parent;
			ret->tag = generic_type_tag_method;
			ret->virtual_type_index = method_for_generic_index(m, self->fqcn->name);
		}
		//しかし、Tに対して追加の型変数を与えることはできません。
		assert(self->type_args->length == 0);
		assert(ret != NULL);
		return ret;
	}
	//型変数がない
	if (self->type_args->length == 0) {
		//assert(core_type->generic_self != NULL);
		//core_type->generic_self->ref_count++;
		//return core_type->generic_self;
		return generic_type_malloc(core_type, filename, lineno);
	}
	generic_type* ret2 = generic_type_malloc(core_type, filename, lineno);
	assert(core_type->tag != type_enum);
	for (int i = 0; i < self->type_args->length; i++) {
		generic_cache* e = (generic_cache*)vector_at(self->type_args, i);
		generic_type* child = generic_cache_gtype(e, scope, ilctx);
		generic_type_addargs(ret2, child);
	}
	assert(ret2 != NULL);
	return ret2;
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