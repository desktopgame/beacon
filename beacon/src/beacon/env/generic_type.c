#include "generic_type.h"
#include "type_interface.h"
#include "type_impl.h"
#include "script_context.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../util/xassert.h"
#include "fqcn_cache.h"
#include <assert.h>
#include <string.h>

//proto
static void generic_type_delete_self(vector_item item);
static void generic_type_deletercr_self(vector_item item);
static void generic_type_recursive_mark(generic_type* a);

/*
generic_type * generic_type_new(type * core_type) {

}
*/

generic_type* generic_type_make(type* core_type) {
	if(core_type == NULL) {
		return generic_type_new(core_type);
	}
	generic_type* ret = generic_type_new(core_type);
	int len = type_type_parameter_len(core_type);
	for(int i=0; i<len; i++) {
		generic_type* a = generic_type_new(NULL);
		a->tag = generic_type_tag_class;
		a->virtual_type_index = i;
		a->u.type_ = core_type;
		generic_type_addargs(ret, a);
	}
	if(core_type->tag == type_class &&
	   !strcmp(core_type->u.class_->name, "Array")) {
		assert((len == 1));
	}
	return ret;
}

generic_type* generic_type_malloc(struct type* core_type, const char* filename, int lineno) {
	generic_type* ret = (generic_type*)mem_malloc(sizeof(generic_type), filename, lineno);
	ret->core_type = core_type;
	ret->type_args_list = vector_new();
	ret->virtual_type_index = -1;
	ret->ref_count = 0;
	//現在のスクリプトコンテキストに登録
	script_context* ctx = script_context_get_current();
	vector_push(ctx->all_generic_vec, ret);
	return ret;
}

void generic_type_collect() {
	script_context* ctx = script_context_get_current();
	//マークを外す
	for(int i=0; i<ctx->all_generic_vec->length; i++) {
		generic_type* e= (generic_type*)vector_at(ctx->all_generic_vec, i);
		e->mark = false;
	}
	//全ての型に定義された自身を参照するための generic をマーク
	for(int i=0; i<ctx->type_vec->length; i++) {
		type* e= (type*)vector_at(ctx->type_vec, i);
		generic_type_recursive_mark(e->generic_self);
	}
	vector* alive = vector_new();
	vector* dead = vector_new();
	for(int i=0; i<ctx->all_generic_vec->length; i++) {
		generic_type* e= (generic_type*)vector_at(ctx->all_generic_vec, i);
		vector_push((!e->mark ? dead : alive), e);
	}
	vector_delete(ctx->all_generic_vec, vector_deleter_null);
	vector_delete(dead, generic_type_delete_self);
	ctx->all_generic_vec = alive;
}

void generic_type_lostownership(generic_type* a) {
	assert(a->core_type != NULL);
	assert(a->core_type->generic_self == a);
	generic_type_deletercr_self(a);
}

void generic_type_fixtype(generic_type* self) {
	if(self->tag != generic_type_tag_class &&
	   self->tag != generic_type_tag_method) {
		   self->tag =generic_type_tag_none;
	   }
}

void generic_type_addargs(generic_type* self, generic_type* a) {
	assert(a != NULL);
//	assert(a->tag == generic_type_tag_class || 
//	       a->tag == generic_type_tag_method ||
//		   a->tag == generic_type_tag_none);
	a->ref_count++;
	vector_push(self->type_args_list, a);
	assert(self->type_args_list->length < 2);
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
		assert(a->core_type != NULL && b->core_type != NULL);
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

bool generic_type_int(generic_type* self) {
	return self->core_type == CL_INT;
}

bool generic_type_double(generic_type* self) {
	return self->core_type == CL_DOUBLE;
}

bool generic_type_bool(generic_type* self) {
	return self->core_type == CL_BOOL;
}

//Hash<String,List<Int>>
generic_type* generic_type_apply(generic_type* self, il_context* ilctx) {
	generic_type* copy = generic_type_new(self->core_type);
	generic_type* e = NULL;
	int count = 0;
	//全ての実型引数
	for(int i=0; i<self->type_args_list->length; i++) {
		e = (generic_type*)vector_at(self->type_args_list, i);
		//この型がクラスやメソッドに定義された仮装型なら
		if(e->virtual_type_index != -1) {
			count++;
			if(e->tag == generic_type_tag_class) {
				generic_type* tp = vector_top(ilctx->receiver_vec);
				generic_type* instanced = vector_at(tp->type_args_list, e->virtual_type_index);
				generic_type_addargs(copy, generic_type_apply(instanced, ilctx));
			} else if(e->tag == generic_type_tag_method) {
				vector* type_args = vector_top(ilctx->type_args_vec);
				generic_type* a = vector_at(type_args, e->virtual_type_index);
				generic_type_addargs(copy, generic_type_apply(a, ilctx));
				//メソッド呼び出しが必要！！
				//メソッドは仮想型しかもってない！！！
			} else XBREAK(e->tag != generic_type_tag_none);
		//
		} else {
			generic_type_addargs(copy, generic_type_apply(e, ilctx));
		}
	}
	assert(copy->core_type != NULL || count == 0);
	copy->tag = generic_type_tag_none;
	return copy;
}

method * generic_type_find_method(generic_type* self, const char * name, vector * args, enviroment * env, il_context * ilctx, int * outIndex) {	
	return type_find_method(self->core_type, name, args, env, ilctx, outIndex);
}

//private
static void generic_type_delete_self(vector_item item) {
	generic_type* e = (generic_type*)item;
	vector_delete(e->type_args_list, vector_deleter_null);
	MEM_FREE(e);
}

static void generic_type_deletercr_self(vector_item item) {
	generic_type* e = (generic_type*)item;
	vector_delete(e->type_args_list, generic_type_deletercr_self);
	MEM_FREE(e);
}

static void generic_type_recursive_mark(generic_type* a) {
	if(a == NULL || a->mark) {
		return;
	}
	a->mark = true;
	for(int i=0; i<a->type_args_list->length; i++) {
		generic_type_recursive_mark((generic_type*)vector_at(a->type_args_list, i));
	}
}