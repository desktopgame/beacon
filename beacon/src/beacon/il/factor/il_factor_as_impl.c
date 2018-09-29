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
	il_factor* ret = il_factor_new(ILFACTOR_AS_T);
	ret->u.as_ = self;
	return ret;
}

il_factor_as * il_factor_as_new() {
	il_factor_as* ret = (il_factor_as*)MEM_MALLOC(sizeof(il_factor_as));
	ret->fact = NULL;
	ret->fqcn = generic_cache_new();
	ret->gtype = NULL;
	ret->mode = CAST_UNKNOWN_T;
	return ret;
}

void il_factor_as_generate(il_factor_as * self, enviroment * env, call_context* cctx) {
	il_factor_generate(self->fact, env, cctx);
	opcode_buf_add(env->buf, OP_GENERIC_ADD);
	generic_type_generate(self->gtype, env);
	if(self->mode == CAST_DOWN_T) {
		opcode_buf_add(env->buf, OP_DOWN_AS);
	} else {
		opcode_buf_add(env->buf, OP_UP_AS);
	}
}

void il_factor_as_load(il_factor_as * self, enviroment * env, call_context* cctx) {
	if(self->gtype != NULL) {
		return;
	}
	il_factor_load(self->fact, env, cctx);
	self->gtype = import_manager_resolve(call_context_namespace(cctx), self->fqcn, cctx);
	generic_type* a = il_factor_eval(self->fact, env, cctx);
	//キャスト元がインターフェイスなら常にアップキャスト
	if(self->gtype->core_type != NULL && GENERIC2TYPE(self->gtype)->tag == TYPE_INTERFACE_T) {
		self->mode = CAST_UP_T;
		return;
	}
	//キャスト先がインターフェイスなら常にアップキャスト
	if(a->core_type != NULL && GENERIC2TYPE(a)->tag == TYPE_INTERFACE_T) {
		self->mode = CAST_DOWN_T;
		return;
	}
	//キャスト先がオブジェクトなら常にアップキャスト
	if(self->gtype->core_type != NULL && self->gtype->core_type == TYPE_OBJECT) {
		self->mode = CAST_UP_T;
		return;
	}
	int downTo = generic_type_distance(self->gtype, a, cctx);
	int upTo = generic_type_distance(a, self->gtype, cctx);
	//ダウンキャスト
	if(downTo >= 0) {
		self->mode = CAST_UP_T;
	//アップキャスト
	} else if(upTo >= 0) {
		self->mode = CAST_DOWN_T;
	//それ以外
	} else {
		bc_error_throw(BCERROR_CAST_NOT_COMPATIBLE_T,
			Ref2Str(type_name(a->core_type)),
			Ref2Str(type_name(self->gtype->core_type))
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
	string_buffer* sb = NewBuffer();
	char* factstr = il_factor_tostr(self->fact, env);
	char* to = generic_cache_tostr(self->fqcn);
	AppendfBuffer(sb, "%s as %s", factstr, to);
	MEM_FREE(factstr);
	MEM_FREE(to);
	return ReleaseBuffer(sb);
}