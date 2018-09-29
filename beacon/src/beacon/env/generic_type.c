#include "generic_type.h"
#include "type_interface.h"
#include "TYPE_IMPL.h"
#include "script_context.h"
#include "type_parameter.h"
#include "constructor.h"
#include "../env/object.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../il/il_type_argument.h"
#include "../vm/frame.h"
#include "fqcn_cache.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

//proto
static generic_type* generic_type_applyImpl(generic_type* self, call_context* cctx, frame* fr);
static int generic_type_distanceImpl(generic_type* self, generic_type* other, frame* fr, call_context* cctx);
static int generic_type_distance_nogeneric(generic_type* self, generic_type* other, frame* fr, call_context* cctx);
static int generic_type_distance_class(int dist, generic_type* self, generic_type* other, frame* fr, call_context* cctx);
static int generic_type_distance_interface(int dist, generic_type* self, generic_type* other, frame* fr, call_context* cctx);
static Vector* generic_type_apply_by_hierarchy(generic_type* impl_baseline, generic_type* impl);
static generic_type* generic_type_typeargs_at(call_context* cctx, frame* fr, int index);
static generic_type* generic_type_receiver_at(call_context* cctx, frame* fr, int index);
static void generic_type_delete_self(VectorItem item);
static void generic_type_deletercr_self(VectorItem item);
static void generic_type_recursive_mark(generic_type* a);
static generic_type* generic_type_get(generic_type* a);
/*
generic_type * generic_type_new(type * core_type) {

}
*/

generic_type* generic_type_ref(type* core_type) {
	if(core_type == NULL) {
		return generic_type_new(core_type);
	}
	return core_type->generic_self;
}

generic_type* generic_type_malloc(struct type* core_type, const char* filename, int lineno) {
	generic_type* ret = (generic_type*)mem_malloc(sizeof(generic_type), filename, lineno);
	ret->core_type = core_type;
	ret->type_args_list = NewVector();
	ret->virtual_type_index = -1;
	ret->tag = GENERIC_TYPE_TAG_NONE_T;
	ret->is_ctor = false;
	//現在のスクリプトコンテキストに登録
	script_context* ctx = script_context_get_current();
	PushVector(ctx->all_generic_vec, ret);
	return ret;
}

generic_type* generic_type_clone(generic_type* self) {
	generic_type* a = generic_type_new(self->core_type);
	for(int i=0; i<self->type_args_list->length; i++) {
		generic_type* e = AtVector(self->type_args_list, i);
		generic_type_addargs(a, generic_type_clone(e));
	}
	a->tag = self->tag;
	a->virtual_type_index = self->virtual_type_index;
	if(a->tag == GENERIC_TYPE_TAG_CLASS_T) {
		a->u.type_ = self->u.type_;
	} else if(a->tag == GENERIC_TYPE_TAG_METHOD_T) {
		a->u.method_ = self->u.method_;
	}
	return a;
}

void generic_type_collect() {
	script_context* ctx = script_context_get_current();
	//マークを外す
	for(int i=0; i<ctx->all_generic_vec->length; i++) {
		generic_type* e= (generic_type*)AtVector(ctx->all_generic_vec, i);
		e->mark = false;
	}
	//全ての型に定義された自身を参照するための generic をマーク
	for(int i=0; i<ctx->type_vec->length; i++) {
		type* e= (type*)AtVector(ctx->type_vec, i);
		generic_type_recursive_mark(e->generic_self);
	}
	Vector* alive = NewVector();
	Vector* dead = NewVector();
	for(int i=0; i<ctx->all_generic_vec->length; i++) {
		generic_type* e= (generic_type*)AtVector(ctx->all_generic_vec, i);
		PushVector((!e->mark ? dead : alive), e);
	}
	DeleteVector(ctx->all_generic_vec, VectorDeleterOfNull);
	DeleteVector(dead, generic_type_delete_self);
	ctx->all_generic_vec = alive;
}

void generic_type_lostownership(generic_type* a) {
	//enumはクラスの一種だが、
	//generic_Selfを持たない
	if(a == NULL) {
		return;
	}
	assert(a->core_type != NULL);
	assert(a->core_type->generic_self == a);
	generic_type_deletercr_self(a);
}

void generic_type_addargs(generic_type* self, generic_type* a) {
	assert(a != NULL);
	PushVector(self->type_args_list, a);
}

int generic_type_distance(generic_type * self, generic_type * other, call_context* cctx) {
	return generic_type_distanceImpl(self, other, NULL, cctx);
}

int generic_type_rdistance(generic_type* self, generic_type* other, frame* fr) {
	return generic_type_distanceImpl(self, other, fr, NULL);
}

void generic_type_print(generic_type * self) {
	assert(self != NULL);
	//タグを出力
	switch(self->tag) {
		case GENERIC_TYPE_TAG_NONE_T:
			printf("::");
			break;
		case GENERIC_TYPE_TAG_CLASS_T:
			printf("@@");
			break;
		case GENERIC_TYPE_TAG_METHOD_T:
			printf("##");
			break;
	}
	//T, Uなど
	if (self->virtual_type_index != -1) {
		//(Array)[0]
		if(self->tag == GENERIC_TYPE_TAG_CLASS_T) {
			printf("(%s)", Ref2Str(type_name(self->u.type_)));
		//copy[0]
		} else if(self->tag == GENERIC_TYPE_TAG_METHOD_T) {
			printf("(%s)", Ref2Str(self->u.method_->namev));
		}
		printf("[%d]", self->virtual_type_index);
	//Intなど
	} else {
		printf("%s", Ref2Str(type_name(self->core_type)));
	}
	if(self->is_ctor) {
		printf("!!");
	}
	if (self->type_args_list->length == 0) {
		return;
	}
	//[...]
	printf("[");
	for (int i = 0; i < self->type_args_list->length; i++) {
		generic_type* e = (generic_type*)AtVector(self->type_args_list, i);
		generic_type_print(e);
		if (i != self->type_args_list->length - 1) {
			printf(",");
		}
	}
	printf("]");
}

void generic_type_generate(generic_type* self, enviroment* env) {
	AddOpcodeBuf(env->buf, OP_GENERIC_ENTER);
	AddOpcodeBuf(env->buf, self->type_args_list->length);
	if(self->core_type == NULL) {
		if(self->tag == GENERIC_TYPE_TAG_CLASS_T) {
			AddOpcodeBuf(env->buf, OP_GENERIC_INSTANCE_TYPE);
			AddOpcodeBuf(env->buf, self->virtual_type_index);
			//assert(self->virtual_type_index != -1);
		} else {
			AddOpcodeBuf(env->buf, OP_GENERIC_STATIC_TYPE);
			AddOpcodeBuf(env->buf, self->virtual_type_index);
		}
	} else {
		AddOpcodeBuf(env->buf, OP_GENERIC_UNIQUE_TYPE);
		AddOpcodeBuf(env->buf, self->core_type->absolute_index);
	}
	for(int i=0; i<self->type_args_list->length; i++) {
		generic_type* e = (generic_type*)AtVector(self->type_args_list, i);
		generic_type_generate(e, env);
	}
	AddOpcodeBuf(env->buf, OP_GENERIC_EXIT);
}

//Hash<String,List<Int>>
generic_type* generic_type_apply(generic_type* self, call_context* cctx) {
	return generic_type_applyImpl(self, cctx, NULL);
}

generic_type* generic_type_rapply(generic_type* self, call_context* cctx, frame* fr) {
	return generic_type_applyImpl(self, cctx, fr);
}

struct type* generic_type_to_type(generic_type* self) {
	return self->core_type;
}

//private
static generic_type* generic_type_applyImpl(generic_type* self, call_context* cctx, frame* fr) {
	int count = 0;
	//型変数なら変換
	generic_type* ret = NULL;
	if(self->virtual_type_index != -1) {
		count++;
		if(self->tag == GENERIC_TYPE_TAG_CLASS_T) {
			if(self->is_ctor) {
				ret = generic_type_clone(generic_type_typeargs_at(cctx, fr, self->virtual_type_index));
			} else {
				ret = generic_type_clone(generic_type_receiver_at(cctx, fr, self->virtual_type_index));
			}
		} else if(self->tag == GENERIC_TYPE_TAG_METHOD_T) {
			ret = generic_type_clone(generic_type_typeargs_at(cctx, fr, self->virtual_type_index));
		}
	} else {
		ret = generic_type_new(self->core_type);
		ret->tag = self->tag;
		ret->virtual_type_index = self->virtual_type_index;
	}
	assert(ret != NULL);
	for(int i=0; i<self->type_args_list->length; i++) {
		generic_type_addargs(ret, generic_type_apply(AtVector(self->type_args_list, i), cctx));
	}
	return ret;
}

static int generic_type_distanceImpl(generic_type* self, generic_type* other, frame* fr, call_context* cctx) {
	if(fr != NULL) {
		return generic_type_distance_nogeneric(self, other, fr, cctx);
	}
	//要求されている型は T
	if(self->core_type == NULL) {
		//提供されているのは T
		if(other->core_type == NULL) {
			return 0;
		//提供されているのは具体的な型
		} else {
			//具体的な型が T のルールを満たしているか？
			return 0;
		}
	//提供している型は T
	} else if(other->core_type == NULL) {
		//要求されているのは具体的な型
		if(self->core_type != NULL) {
			//Object型にのみ変換可能
			if(self->core_type == TYPE_OBJECT) {
				return 0;
			}
			//T が 具体的な型の要件を満たしているか？
			return -1;
		//要求されているのは T
		} else {
			return 0;
		}
	//どちらも具体的な型
	} else {
		return generic_type_distance_nogeneric(self, other, fr, cctx);
	}
}

static int generic_type_distance_nogeneric(generic_type* self, generic_type* other, frame* fr, call_context* cctx) {
	assert(self->core_type != NULL);
	assert(other->core_type != NULL);
	int dist = type_distance(self->core_type, other->core_type);
	assert(self->core_type != NULL);
	assert(other->core_type != NULL);
	#if defined(DEBUG)
	const char* sname = Ref2Str(type_name(self->core_type));
	const char* oname = Ref2Str(type_name(other->core_type));
	#endif
	//List : Dict みたいな型ならもうこの時点で次へ
	if(dist == -1) {
		return dist;
	}
	if(other->core_type == TYPE_NULL) {
		return 1;
	}
	if (self->core_type->tag == TYPE_CLASS_T) {
		return generic_type_distance_class(dist, self, other, fr, cctx);
	} else if (self->core_type->tag == TYPE_INTERFACE_T) {
		return generic_type_distance_interface(dist, self, other, fr, cctx);
	}
	return dist;
}

static int generic_type_distance_class(int dist, generic_type* self, generic_type* other, frame* fr, call_context* cctx) {
	//otherからselfまで辿る
	class_* baseline = self->core_type->u.class_;
	class_* ptr = other->core_type->u.class_;
	generic_type* target = other;
	while (baseline != ptr) {
		target = ptr->super_class;
		ptr = ptr->super_class->core_type->u.class_;
	}
	assert(target != NULL);
	assert(self->type_args_list->length == target->type_args_list->length);
	for (int i = 0; i<self->type_args_list->length; i++) {
		generic_type* a = AtVector(self->type_args_list, i);
		generic_type* b = AtVector(target->type_args_list, i);
		int calc = generic_type_distanceImpl(a, b, fr, cctx);
		if (calc == -1 || calc > 0) {
			dist = -1;
			break;
		}
	}
	return dist;
}

static int generic_type_distance_interface(int dist, generic_type* self, generic_type* other, frame* fr, call_context* cctx) {
	if (other->core_type->tag == TYPE_CLASS_T) {
		//クラスからインターフェイスを探す
		generic_type* impl_baseline = NULL;
		generic_type* impl = class_find_interface_type(TYPE2CLASS(GENERIC2TYPE(other)), (GENERIC2TYPE(self)), &impl_baseline);
		if (impl_baseline == NULL) {
			impl_baseline = other;
		}
		Vector* gargs = generic_type_apply_by_hierarchy(impl_baseline, impl);
		for (int i = 0; i<self->type_args_list->length; i++) {
			generic_type* a = AtVector(self->type_args_list, i);
			generic_type* b = AtVector(gargs, i);
			int calc = generic_type_distanceImpl(a, b, fr, cctx);
			if (calc == -1 || calc > 0) {
				dist = -1;
				break;
			}
		}
		DeleteVector(gargs, VectorDeleterOfNull);
		return dist;
	} else if (other->core_type->tag == TYPE_INTERFACE_T) {
		generic_type* impl = interface_find_interface(TYPE2INTERFACE(GENERIC2TYPE(other)), (GENERIC2TYPE(self)));
		if (impl == NULL) {
			impl = other;
		}
		for (int i = 0; i<self->type_args_list->length; i++) {
			generic_type* a = AtVector(self->type_args_list, i);
			generic_type* b = AtVector(impl->type_args_list, i);
			int calc = generic_type_distanceImpl(a, b, fr, cctx);
			if (calc == -1 || calc > 0) {
				dist = -1;
				break;
			}
		}
		//generic_type_print(self); Println();
		//generic_type_print(other); Println();
		//Printfln("---");
		return dist;
	}
	return dist;
}

static Vector* generic_type_apply_by_hierarchy(generic_type* impl_baseline, generic_type* impl) {
	assert(impl_baseline->core_type != NULL);
	Vector* gargs = NewVector();
	for (int i = 0; i < impl->type_args_list->length; i++) {
		generic_type* e = AtVector(impl->type_args_list, i);
		if (e->core_type == NULL) {
			e = AtVector(impl_baseline->type_args_list, e->virtual_type_index);
		}
		PushVector(gargs, e);
	}
	return gargs;
}

static generic_type* generic_type_typeargs_at(call_context* cctx, frame* fr, int index) {
	if(fr == NULL) {
		Vector* type_args = call_context_typeargs(cctx);
		il_type_argument* a = AtVector(type_args, index);
		return a->gtype;
	} else {
		generic_type* a = AtVector(fr->type_args_vec, index);
		return a;
	}
	return NULL;
}

static generic_type* generic_type_receiver_at(call_context* cctx, frame* fr, int index) {
	if(fr == NULL) {
		generic_type* tp = call_context_receiver(cctx);
		generic_type* instanced = AtVector(tp->type_args_list, index);
		return instanced;
	} else {
		object* a = AtVector(fr->ref_stack, 0);
		printf("receiver at: "); generic_type_print(a->gtype); Println();
		return AtVector(a->gtype->type_args_list, index);
	}
	return NULL;
}

static generic_type* generic_type_get(generic_type* a) {
	/*
	if(a->virtual_type_index == -1) {
		return a;
	}
	if(a->tag == GENERIC_TYPE_TAG_CLASS_T) {
		generic_type* receiver = ccat_receiver(a->virtual_type_index);
		a = receiver;
	} else if(a->tag == GENERIC_TYPE_TAG_METHOD_T) {
		generic_type* at = AtVector(cctop_type_args(), a->virtual_type_index);
		a = at;
	}
	return a;
	*/
	return NULL;
}

static void generic_type_delete_self(VectorItem item) {
	generic_type* e = (generic_type*)item;
	DeleteVector(e->type_args_list, VectorDeleterOfNull);
	MEM_FREE(e);
}

static void generic_type_deletercr_self(VectorItem item) {
	generic_type* e = (generic_type*)item;
	DeleteVector(e->type_args_list, generic_type_deletercr_self);
	MEM_FREE(e);
}

static void generic_type_recursive_mark(generic_type* a) {
	if(a == NULL || a->mark) {
		return;
	}
	a->mark = true;
	for(int i=0; i<a->type_args_list->length; i++) {
		generic_type_recursive_mark((generic_type*)AtVector(a->type_args_list, i));
	}
}