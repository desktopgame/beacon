#include "il_factor_new_instance_impl.h"
#include "../../util/mem.h"
#include "../il_argument.h"
#include "../../vm/enviroment.h"
#include "../../env/type_interface.h"
#include "../../util/text.h"
#include "../../env/constructor.h"
#include "../../env/type_interface.h"
#include "../../env/type_impl.h"
#include <stdio.h>
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
	ret->fqcn = fqcn_cache_new();
	ret->argument_list = vector_new();
	ret->c = NULL;
	ret->constructorIndex = -1;
	return ret;
}

void il_factor_new_instance_dump(il_factor_new_instance * self, int depth) {
	text_putindent(depth);
	text_printf("new instance");
	text_putline();

	fqcn_cache_dump(self->fqcn, depth + 1);
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
	opcode_buf_add(env->buf, self->c->parent->absolute_index);
	opcode_buf_add(env->buf, self->constructorIndex);
}

void il_factor_new_instance_load(il_factor_new_instance * self, enviroment * env, il_load_cache* cache, il_ehandler * eh) {
//	fqcn_cache_delete(self->fqcn);
//	vector_delete(self->argument_list, il_Factor_new_instace_delete_arg);
//	MEM_FREE(self);
}

type * il_factor_new_instance_eval(il_factor_new_instance * self, enviroment * env, il_load_cache* cache) {
	il_factor_new_instance_find(self, env, cache);
	return self->c->parent;
}

void il_factor_new_instance_delete(il_factor_new_instance * self) {
	vector_delete(self->argument_list, il_Factor_new_instace_delete_arg);
	fqcn_cache_delete(self->fqcn);
	MEM_FREE(self);
}

//private
static void il_factor_new_instance_find(il_factor_new_instance * self, enviroment * env, il_load_cache* cache) {
	//*
	class_* cls = il_load_cache_class(cache, self->fqcn);
	int temp = 0;
	//TEST(!strcmp(cls->name, "Point3D"));
	self->c = class_find_constructor(cls, self->argument_list, env, cache, &temp);
	assert(self->c != NULL);
	self->constructorIndex = temp;
	//*/
}

static void il_Factor_new_instace_delete_arg(vector_item item) {
	il_argument* e = (il_argument*)item;
	il_argument_delete(e);
}