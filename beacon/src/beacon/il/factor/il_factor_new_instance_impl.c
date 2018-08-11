#include "il_factor_new_instance_impl.h"
#include "../../util/mem.h"
#include "../il_argument.h"
#include "../il_type_argument.h"
#include "../../vm/enviroment.h"
#include "../../env/type_interface.h"
#include "../../util/text.h"
#include "../../env/constructor.h"
#include "../../env/type_interface.h"
#include "../../env/type_impl.h"
#include "../../env/class_loader.h"
#include "../../env/import_manager.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

//proto
static void il_factor_new_instance_delete_typearg(vector_item item);
static void il_factor_new_instance_find(il_factor_new_instance * self, enviroment * env, call_context* cctx);
static void il_Factor_new_instace_delete_arg(vector_item item);

il_factor * il_factor_wrap_new_instance(il_factor_new_instance * self) {
	il_factor* ret = il_factor_new(ilfactor_new_instance);
	ret->u.new_instance_ = self;
	return ret;
}

il_factor_new_instance * il_factor_new_instance_new() {
	il_factor_new_instance* ret = (il_factor_new_instance*)MEM_MALLOC(sizeof(il_factor_new_instance));
	ret->fqcnc = fqcn_cache_new();
	ret->type_args = vector_new();
	ret->argument_list = vector_new();
	ret->c = NULL;
	ret->constructor_index = -1;
	ret->instance_type = NULL;
	return ret;
}

void il_factor_new_instance_dump(il_factor_new_instance * self, int depth) {
	io_printi(depth);
	printf("new instance");
	io_println();
	fqcn_cache_dump(self->fqcnc, depth + 1);
	for (int i = 0; i < self->argument_list->length; i++) {
		il_argument* ilarg = (il_argument*)vector_at(self->argument_list, i);
		il_argument_dump(ilarg, depth + 1);
	}
}

void il_factor_new_instance_generate(il_factor_new_instance * self, enviroment * env, call_context* cctx) {
	il_factor_new_instance_find(self, env, cctx);
	for(int i=0; i<self->type_args->length; i++) {
		il_type_argument* e = (il_type_argument*)vector_at(self->type_args, i);
		assert(e->gtype != NULL);
		opcode_buf_add(env->buf, op_generic_add);
		generic_type_generate(e->gtype, env);
	}
	//実引数を全てスタックへ
	for (int i = 0; i < self->argument_list->length; i++) {
		il_argument* ilarg = (il_argument*)vector_at(self->argument_list, i);
		il_factor_generate(ilarg->factor, env, cctx);
		if(bc_error_last()) {
			return;
		}
	}
	//クラスとコンストラクタのインデックスをプッシュ
	opcode_buf_add(env->buf, op_new_instance);
	opcode_buf_add(env->buf, self->c->parent->absolute_index);
	opcode_buf_add(env->buf, self->constructor_index);
}

void il_factor_new_instance_load(il_factor_new_instance * self, enviroment * env, call_context* cctx) {
	il_factor_new_instance_find(self, env, cctx);
	if(bc_error_last()) {
		return;
	}
	//抽象クラスはインスタンス化できない
	if(type_is_abstract(self->c->parent)) {
		bc_error_throw(bcerror_construct_abstract_type, string_pool_ref2str(type_name(self->c->parent)));
	}
}

generic_type* il_factor_new_instance_eval(il_factor_new_instance * self, enviroment * env, call_context* cctx) {
	il_factor_new_instance_find(self, env, cctx);
	if(bc_error_last()) {
		return NULL;
	}
	//型引数がないのでそのまま
	if (self->type_args->length == 0) {
		generic_type* ret = generic_type_ref(self->c->parent);
		return ret;
	}
	//fqcn_cache typename_group
	if (self->instance_type == NULL) {
		namespace_* scope = NULL;
		generic_type* a = generic_type_new(self->c->parent);
		for (int i = 0; i < self->type_args->length; i++) {
			il_type_argument* e = (il_type_argument*)vector_at(self->type_args, i);
			generic_type* arg = import_manager_resolve(NULL, NULL, e->gcache, cctx);
			generic_type_addargs(a, arg);
		}
		self->instance_type = a;
	}
	return self->instance_type;
}

char* il_factor_new_instance_tostr(il_factor_new_instance* self, enviroment* env) {
	string_buffer* sb = string_buffer_new();
	string_buffer_appends(sb, "new ");
	char* type = fqcn_cache_tostr(self->fqcnc);
	string_buffer_appends(sb, type);
	il_factor_type_args_tostr(sb, self->type_args, env);
	il_factor_args_tostr(sb, self->argument_list, env);
	MEM_FREE(type);
	return string_buffer_release(sb);
}

void il_factor_new_instance_delete(il_factor_new_instance * self) {
	vector_delete(self->argument_list, il_Factor_new_instace_delete_arg);
	vector_delete(self->type_args, il_factor_new_instance_delete_typearg);
	fqcn_cache_delete(self->fqcnc);
	MEM_FREE(self);
}

il_factor_new_instance* il_factor_cast_new_instance(il_factor* fact) {
	assert(fact->type == ilfactor_new_instance);
	return fact->u.new_instance_;
}

//private
static void il_factor_new_instance_delete_typearg(vector_item item) {
	il_type_argument* e = (il_type_argument*)item;
	il_type_argument_delete(e);
}

static void il_factor_new_instance_find(il_factor_new_instance * self, enviroment * env, call_context* cctx) {
	if(self->constructor_index != -1) {
		return;
	}
	#if defined(DEBUG)
	const char* namea = string_pool_ref2str(self->fqcnc->namev);
	if(self->fqcnc->namev == string_pool_intern("Vector")) {
		int a = 0;
	}
	#endif
	//コンストラクタで生成するオブジェクトの肩を取得
	type* ty = call_context_eval_type(cctx, self->fqcnc);
	if(ty == NULL) {
		bc_error_throw(bcerror_undefined_class, string_pool_ref2str(self->fqcnc->namev));
		return;
	}
	//使用するコンストラクタを取得
	class_* cls = TYPE2CLASS(ty);
	int temp = -1;
	call_frame* cfr = call_context_push(cctx, frame_resolve_T);
	cfr->u.resolve.gtype = cls->parent->generic_self;
	cfr->u.resolve.typeargs = self->type_args;
	il_type_argument_resolve(self->type_args, cctx);
	self->c = class_ilfind_constructor(cls, self->argument_list, env, cctx, &temp);
	self->constructor_index = temp;
	call_context_pop(cctx);
	if(temp == -1) {
		bc_error_throw(bcerror_undefined_ctor, string_pool_ref2str(cls->namev));
	}
}

static void il_Factor_new_instace_delete_arg(vector_item item) {
	il_argument* e = (il_argument*)item;
	il_argument_delete(e);
}