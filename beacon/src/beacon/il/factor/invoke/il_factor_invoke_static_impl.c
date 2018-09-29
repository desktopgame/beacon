#include "il_factor_invoke_static_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../env/generic_type.h"
#include "../../../env/type/class_impl.h"
#include "../../../vm/enviroment.h"
#include "../../il_argument.h"
#include "../../il_type_argument.h"
#include "../../../util/vector.h"

//proto
static void resolve_non_default(il_factor_invoke_static * self, enviroment * env, call_context* cctx);
static void resolve_default(il_factor_invoke_static * self, enviroment * env, call_context* cctx);
static void il_factor_invoke_static_check(il_factor_invoke_static * self, enviroment * env, call_context* cctx);
static void il_factor_invoke_static_args_delete(VectorItem item);
static void il_factor_invoke_static_typeargs_delete(VectorItem item);

il_factor_invoke_static* il_factor_invoke_static_new(string_view namev) {
	il_factor_invoke_static* ret = (il_factor_invoke_static*)MEM_MALLOC(sizeof(il_factor_invoke_static));
	ret->args = NULL;
	ret->fqcn = NULL;
	ret->type_args = NULL;
	ret->namev = namev;
	ret->m = NULL;
	ret->index = -1;
	ret->resolved = NULL;
	return ret;
}

void il_factor_invoke_static_generate(il_factor_invoke_static* self, enviroment* env, call_context* cctx) {
	for(int i=0; i<self->type_args->length; i++) {
		il_type_argument* e = (il_type_argument*)AtVector(self->type_args, i);
		assert(e->gtype != NULL);
		AddOpcodeBuf(env->buf, OP_GENERIC_ADD);
		generic_type_generate(e->gtype, env);
	}
	for(int i=0; i<self->args->length; i++) {
		il_argument* e = (il_argument*)AtVector(self->args, i);
		il_factor_generate(e->factor, env, cctx);
		if(GetLastBCError()) {
			return;
		}
	}
	AddOpcodeBuf(env->buf, (VectorItem)OP_INVOKESTATIC);
	AddOpcodeBuf(env->buf, (VectorItem)self->m->parent->absolute_index);
	AddOpcodeBuf(env->buf, (VectorItem)self->index);
}

void il_factor_invoke_static_load(il_factor_invoke_static * self, enviroment * env, call_context* cctx) {
	il_factor_invoke_static_check(self, env, cctx);
}

generic_type* il_factor_invoke_static_eval(il_factor_invoke_static * self, enviroment * env, call_context* cctx) {
	il_factor_invoke_static_check(self, env, cctx);
	//メソッドを解決できなかった場合
	if(GetLastBCError()) {
		return NULL;
	}
	generic_type* rgtp = self->m->return_gtype;
	if(rgtp->tag != GENERIC_TYPE_TAG_NONE_T) {
		resolve_non_default(self, env, cctx);
		return self->resolved;
	} else {
		resolve_default(self, env, cctx);
		return self->resolved;
	}
	return NULL;
}

char* il_factor_invoke_static_tostr(il_factor_invoke_static* self, enviroment* env) {
	string_buffer* sb = NewBuffer();
	char* name = fqcn_cache_tostr(self->fqcn);
	AppendsBuffer(sb, name);
	AppendBuffer(sb, '.');
	AppendsBuffer(sb, Ref2Str(self->namev));
	il_factor_type_args_tostr(sb, self->type_args, env);
	il_factor_args_tostr(sb, self->args, env);
	MEM_FREE(name);
	return ReleaseBuffer(sb);
}

void il_factor_invoke_static_delete(il_factor_invoke_static* self) {
	DeleteVector(self->args, il_factor_invoke_static_args_delete);
	DeleteVector(self->type_args, il_factor_invoke_static_typeargs_delete);
	fqcn_cache_delete(self->fqcn);
	MEM_FREE(self);
}
//private
//FIXME:il_factor_invokeからのコピペ
static void resolve_non_default(il_factor_invoke_static * self, enviroment * env, call_context* cctx) {
	if(self->resolved != NULL) {
		return;
	}
	generic_type* rgtp = self->m->return_gtype;
	generic_type* instanced_type = (generic_type*)AtVector(self->type_args, rgtp->virtual_type_index);
	self->resolved = generic_type_new(instanced_type->core_type);
	self->resolved->tag = GENERIC_TYPE_TAG_METHOD_T;
	self->resolved->virtual_type_index = rgtp->virtual_type_index;
}

static void resolve_default(il_factor_invoke_static * self, enviroment * env, call_context* cctx) {
	if(self->resolved != NULL) {
		return;
	}
	call_frame* cfr = call_context_push(cctx, FRAME_STATIC_INVOKE_T);
	cfr->u.static_invoke.args = self->args;
	cfr->u.static_invoke.typeargs = self->type_args;
	generic_type* rgtp = self->m->return_gtype;
	self->resolved = generic_type_apply(rgtp, cctx);
	call_context_pop(cctx);
}

static void il_factor_invoke_static_check(il_factor_invoke_static * self, enviroment * env, call_context* cctx) {
	type* ty =call_context_eval_type(cctx, self->fqcn);
	if(ty == NULL) {
		ThrowBCError(BCERROR_UNDEFINED_TYPE_STATIC_INVOKE_T,
			Ref2Str(self->fqcn->namev),
			Ref2Str(self->namev)
		);
		return;
	}
	class_* cls = TYPE2CLASS(ty);
	#if defined(DEBUG)
	const char* classname = Ref2Str(cls->namev);
	const char* methodname = Ref2Str(self->namev);
	#endif
	int temp = -1;
	il_type_argument_resolve(self->type_args, cctx);
	//環境を設定
	//メソッドを検索
	for(int i=0; i<self->args->length; i++) {
		il_argument* ilarg = AtVector(self->args, i);
		il_factor_load(ilarg->factor, env, cctx);
	}
	call_frame* cfr = call_context_push(cctx, FRAME_STATIC_INVOKE_T);
	cfr->u.static_invoke.args = self->args;
	cfr->u.static_invoke.typeargs = self->type_args;
	self->m = class_ilfind_smethod(cls, self->namev, self->args, env, cctx, &temp);
	self->index = temp;
	//メソッドが見つからない
	if(temp == -1 || self->m == NULL) {
		ThrowBCError(BCERROR_INVOKE_STATIC_UNDEFINED_METHOD_T,
			Ref2Str(cls->namev),
			Ref2Str(self->namev)
		);
	}
	call_context_pop(cctx);
}

static void il_factor_invoke_static_args_delete(VectorItem item) {
	il_argument* e = (il_argument*)item;
	il_argument_delete(e);
}

static void il_factor_invoke_static_typeargs_delete(VectorItem item) {
	il_type_argument* e = (il_type_argument*)item;
	il_type_argument_delete(e);
}