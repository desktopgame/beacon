#include "generic_type.h"
#include "type_impl.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../util/xassert.h"
#include "fqcn_cache.h"
#include <assert.h>

//proto
static void generic_type_tree_delete(vector_item item);

generic_type * generic_type_new(type * core_type) {
	generic_type* ret = (generic_type*)MEM_MALLOC(sizeof(generic_type));
	ret->core_type = core_type;
	ret->type_args_list = vector_new();
	ret->virtual_type_index = -1;
	ret->ref_count = 0;
	return ret;
}

void generic_type_addargs(generic_type* self, generic_type* a) {
	a->ref_count++;
	vector_push(self->type_args_list, a);
}

bool generic_type_castable(generic_type* a, generic_type* b) {
	//完全に同じポインタなら比較は不要
	if (a == b) {
		return true;
	}
	if (a->core_type != NULL &&
		b->core_type != NULL) {
		//基本型か型引数の数が違うなら false
		if (!type_castable(a->core_type, b->core_type) ||
			a->type_args_list->length != b->type_args_list->length) {
			return false;
		}
	}
	//型引数が 0 個なら比較不要
	if (a->type_args_list->length == 0 &&
		b->type_args_list->length == 0) {
		return true;
	}
	//TODO: in/out の考慮
	//基本型と型引数が0個以上で一致するならそれらを比較
	bool ret = true;
	for (int i = 0; i < a->type_args_list->length; i++) {
		generic_type* le = (generic_type*)vector_at(a->type_args_list, i);
		generic_type* re = (generic_type*)vector_at(b->type_args_list, i);
		if (!generic_type_castable(le, re)) {
			ret = false;
			break;
		}
	}
	return ret;
}

int generic_type_distance(generic_type * a, generic_type * b) {
	if (a->virtual_type_index == -1 &&
		b->virtual_type_index == -1) {
		return type_distance(a->core_type, b->core_type);
	}
	return 0;
}

void generic_type_print(generic_type * self) {
	assert(self != NULL);
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
	if((--self->ref_count) > 0) {
		return;
	}
	vector_delete(self->type_args_list, generic_type_tree_delete);
	MEM_FREE(self);
}

generic_type* generic_type_apply(generic_type* self, il_load_cache* cache) {
	generic_type* copy = generic_type_new(self->core_type);
	generic_type* e = NULL;

	for(int i=0; i<self->type_args_list->length; i++) {
		generic_type* e = vector_at(self->type_args_list, i);
		if(e->virtual_type_index != -1) {
			if(e->tag == generic_type_tag_class) {
				generic_type* tp = vector_top(cache->receiver_vec);
				generic_type* instanced = vector_at(tp->type_args_list, e->virtual_type_index);
				generic_type_addargs(copy, generic_type_apply(instanced, cache));
			} else if(e->tag == generic_type_tag_method) {
				vector* type_args = vector_top(cache->type_args_vec);
				generic_type* a = vector_at(type_args, e->virtual_type_index);
				generic_type_addargs(copy, generic_type_apply(a, cache));
				//メソッド呼び出しが必要！！
				//メソッドは仮想型しかもってない！！！
			} else XALWAYS();
		} else {
			generic_type_addargs(copy, generic_type_apply(e, cache));
		}
	}
	return copy;
}

type * generic_type_eval(generic_type * self, il_load_cache * cache) {
	if (self->core_type == NULL) {
		int index = self->virtual_type_index;
		generic_type* inner = NULL;
		if (self->tag == generic_type_tag_class) {
			type* tp = (type*)vector_top(cache->type_vec);
			inner = type_type_parameter_at(tp, index);
			if (inner->core_type == NULL) {
				return generic_type_eval(inner, cache);
			}
			return inner->core_type;
		} else if (self->tag == generic_type_tag_method) {
			method* m = (method*)vector_top(cache->method_vec);
			inner = type_type_parameter_at(m->type_parameter_list, index);
			if (inner->core_type == NULL) {
				return generic_type_eval(inner, cache);
			}
			return inner->core_type;
		} else assert(false);
	}
	if (self->type_args_list->length == 0) {
		return self->core_type;
	}
	return self->core_type;
}

method * generic_type_find_method(generic_type* self, const char * name, vector * args, enviroment * env, il_load_cache * cache, int * outIndex) {	
	return type_find_method(self->core_type, name, args, env, cache, outIndex);
}

//private
static void generic_type_tree_delete(vector_item item) {
	generic_type* e = (generic_type*)item;
	generic_type_delete(e);
}