#include "il_factor_new_instance_impl.h"
#include "../../util/mem.h"
#include "../../util/xassert.h"
#include "../il_argument.h"
#include "../../vm/enviroment.h"
#include "../../env/type_interface.h"
#include "../../util/text.h"
#include "../../env/constructor.h"
#include "../../env/type_interface.h"
#include "../../env/type_impl.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../../util/logger.h"

//proto
static void il_factor_new_instance_find(il_factor_new_instance * self, enviroment * env, il_load_cache* cache);
static void il_Factor_new_instace_delete_arg(vector_item item);

il_factor * il_factor_wrap_new_instance(il_factor_new_instance * self) {
	il_factor* ret = (il_factor*)MEM_MALLOC(sizeof(il_factor));
	ret->type = ilfactor_new_instance;
	ret->u.new_instance_ = self;
	return ret;
}

il_factor_new_instance * il_factor_new_instance_new() {
	il_factor_new_instance* ret = (il_factor_new_instance*)MEM_MALLOC(sizeof(il_factor_new_instance));
	ret->fqcn = generic_cache_new();
	ret->argument_list = vector_new();
	ret->c = NULL;
	ret->constructor_index = -1;
	ret->instance_type = NULL;
	return ret;
}

void il_factor_new_instance_dump(il_factor_new_instance * self, int depth) {
	text_putindent(depth);
	text_printf("new instance");
	text_putline();
	generic_cache_dump(self->fqcn, depth + 1);
	for (int i = 0; i < self->argument_list->length; i++) {
		il_argument* ilarg = (il_argument*)vector_at(self->argument_list, i);
		il_argument_dump(ilarg, depth + 1);
	}
}

void il_factor_new_instance_generate(il_factor_new_instance * self, enviroment * env, il_load_cache* cache) {
	il_factor_new_instance_find(self, env, cache);
	//実引数を全てスタックへ
	for (int i = 0; i < self->argument_list->length; i++) {
		il_argument* ilarg = (il_argument*)vector_at(self->argument_list, i);
		il_factor_generate(ilarg->factor, env, cache);
	}
	//クラスとコンストラクタのインデックスをプッシュ
	opcode_buf_add(env->buf, op_new_instance);
	opcode_buf_add(env->buf, self->c->gparent->core_type->absolute_index);
	opcode_buf_add(env->buf, self->constructor_index);
}

void il_factor_new_instance_load(il_factor_new_instance * self, enviroment * env, il_load_cache* cache, il_ehandler * eh) {
//	fqcn_cache_delete(self->fqcn);
//	vector_delete(self->argument_list, il_Factor_new_instace_delete_arg);
//	MEM_FREE(self);
}

generic_type* il_factor_new_instance_eval(il_factor_new_instance * self, enviroment * env, il_load_cache* cache) {
	il_factor_new_instance_find(self, env, cache);
	//型引数がないのでそのまま
	if (self->fqcn->type_args->length == 0) {
		return self->c->gparent;
	}
	if (self->instance_type == NULL) {
		namespace_* scope = (namespace_*)vector_top(cache->namespace_vec);
		generic_type* a = generic_type_new(self->c->gparent->core_type);
		for (int i = 0; i < self->fqcn->type_args->length; i++) {
			generic_cache* e = vector_at(self->fqcn->type_args, i);
			generic_type* arg = generic_cache_gtype(e, scope, cache);
			generic_type_addargs(a, arg);
		}
		self->instance_type = a;
	}
	return self->instance_type;
}

void il_factor_new_instance_delete(il_factor_new_instance * self) {
	vector_delete(self->argument_list, il_Factor_new_instace_delete_arg);
	generic_cache_delete(self->fqcn);
	MEM_FREE(self);
}

//private
static void il_factor_new_instance_find(il_factor_new_instance * self, enviroment * env, il_load_cache* cache) {
	//*
	class_* cls = il_load_cache_class(cache, self->fqcn->fqcn);
	int temp = 0;
	//TEST(!strcmp(cls->name, "Point3D"));
	self->c = class_find_constructor(cls, self->argument_list, env, cache, &temp);
	assert(self->c != NULL);
	self->constructor_index = temp;
	//*/
}

static void il_Factor_new_instace_delete_arg(vector_item item) {
	il_argument* e = (il_argument*)item;
	il_argument_delete(e);
}