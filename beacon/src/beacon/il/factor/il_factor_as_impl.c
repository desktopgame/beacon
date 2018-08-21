#include "il_factor_as_impl.h"
#include "../../util/mem.h"
#include "../../env/type_interface.h"
#include "../../util/text.h"
#include "../../env/namespace.h"
#include "../../env/class_loader.h"
#include "../../env/import_manager.h"
#include <stdio.h>
#include <assert.h>

il_factor * il_factor_wrap_as(il_factor_as * self) {
	il_factor* ret = il_factor_new(ilfactor_as);
	ret->u.as_ = self;
	return ret;
}

il_factor_as * il_factor_as_new() {
	il_factor_as* ret = (il_factor_as*)MEM_MALLOC(sizeof(il_factor_as));
	ret->fact = NULL;
	ret->fqcn = generic_cache_new();
	ret->gtype = NULL;
	ret->mode = cast_unknown_T;
	return ret;
}

void il_factor_as_dump(il_factor_as * self, int depth) {
	io_printi(depth);
	printf("as ");
	generic_cache_print(self->fqcn);
	io_println();
	il_factor_dump(self->fact, depth + 1);
}

void il_factor_as_generate(il_factor_as * self, enviroment * env, call_context* cctx) {
	il_factor_generate(self->fact, env, cctx);
	opcode_buf_add(env->buf, op_generic_add);
	generic_type_generate(self->gtype, env);
	if(self->mode == cast_down_T) {
		opcode_buf_add(env->buf, op_down_as);
	} else {
		opcode_buf_add(env->buf, op_up_as);
	}
}

void il_factor_as_load(il_factor_as * self, enviroment * env, call_context* cctx) {
	if(self->gtype != NULL) {
		return;
	}
	il_factor_load(self->fact, env, cctx);
	self->gtype = import_manager_resolve(NULL, call_context_namespace(cctx), self->fqcn, cctx);
	generic_type* a = il_factor_eval(self->fact, env, cctx);
	//キャスト元がインターフェイスなら常にアップキャスト
	if(self->gtype->core_type != NULL && GENERIC2TYPE(self->gtype)->tag == type_interface_T) {
		self->mode = cast_up_T;
		return;
	}
	//キャスト先がインターフェイスなら常にアップキャスト
	if(a->core_type != NULL && GENERIC2TYPE(a)->tag == type_interface_T) {
		self->mode = cast_down_T;
		return;
	}
	//キャスト先がオブジェクトなら常にアップキャスト
	if(self->gtype->core_type != NULL && self->gtype->core_type == TYPE_OBJECT) {
		self->mode = cast_up_T;
		return;
	}
	int downTo = generic_type_distance(self->gtype, a, cctx);
	int upTo = generic_type_distance(a, self->gtype, cctx);
	//ダウンキャスト
	if(downTo >= 0) {
		self->mode = cast_up_T;
	//アップキャスト
	} else if(upTo >= 0) {
		self->mode = cast_down_T;
	//それ以外
	} else {
		bc_error_throw(bcerror_cast_not_compatible,
			string_pool_ref2str(type_name(a->core_type)),
			string_pool_ref2str(type_name(self->gtype->core_type))
		);
	}
}

generic_type* il_factor_as_eval(il_factor_as * self, enviroment * env, call_context* cctx) {
	il_factor_as_load(self, env, cctx);
	return self->gtype;
}

void il_factor_as_delete(il_factor_as * self) {
	generic_cache_delete(self->fqcn);
	il_factor_delete(self->fact);
	MEM_FREE(self);
}

char* il_factor_as_tostr(il_factor_as* self, enviroment* env) {
	string_buffer* sb = string_buffer_new();
	char* factstr = il_factor_tostr(self->fact, env);
	char* to = generic_cache_tostr(self->fqcn);
	string_buffer_appendf(sb, "%s as %s", factstr, to);
	MEM_FREE(factstr);
	MEM_FREE(to);
	return string_buffer_release(sb);
}

il_factor_as* il_factor_cast_as(il_factor* fact) {
	assert(fact->type == ilfactor_as);
	return fact->u.as_;
}