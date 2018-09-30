#include "il_factor_new_instance_impl.h"
#include "../../util/mem.h"
#include "../il_argument.h"
#include "../il_type_argument.h"
#include "../../vm/enviroment.h"
#include "../../env/type_interface.h"
#include "../../util/text.h"
#include "../../env/constructor.h"
#include "../../env/type_interface.h"
#include "../../env/TYPE_IMPL.h"
#include "../../env/class_loader.h"
#include "../../env/import_manager.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

//proto
static void il_factor_new_instance_delete_typearg(VectorItem item);
static void il_factor_new_instance_find(il_factor_new_instance * self, enviroment * env, call_context* cctx);
static void il_Factor_new_instace_delete_arg(VectorItem item);

il_factor * il_factor_wrap_new_instance(il_factor_new_instance * self) {
	il_factor* ret = il_factor_new(ILFACTOR_NEW_INSTANCE_T);
	ret->u.new_instance_ = self;
	return ret;
}

il_factor_new_instance * il_factor_new_instance_new() {
	il_factor_new_instance* ret = (il_factor_new_instance*)MEM_MALLOC(sizeof(il_factor_new_instance));
	ret->fqcnc = fqcn_cache_new();
	ret->type_args = NewVector();
	ret->argument_list = NewVector();
	ret->c = NULL;
	ret->constructor_index = -1;
	ret->instance_type = NULL;
	return ret;
}

void il_factor_new_instance_generate(il_factor_new_instance * self, enviroment * env, call_context* cctx) {
	il_factor_new_instance_find(self, env, cctx);
	for(int i=0; i<self->type_args->length; i++) {
		il_type_argument* e = (il_type_argument*)AtVector(self->type_args, i);
		assert(e->gtype != NULL);
		AddOpcodeBuf(env->buf, OP_GENERIC_ADD);
		generic_type_generate(e->gtype, env);
	}
	//実引数を全てスタックへ
	for (int i = 0; i < self->argument_list->length; i++) {
		il_argument* ilarg = (il_argument*)AtVector(self->argument_list, i);
		GenerateILFactor(ilarg->factor, env, cctx);
		if(GetLastBCError()) {
			return;
		}
	}
	//クラスとコンストラクタのインデックスをプッシュ
	AddOpcodeBuf(env->buf, OP_NEW_INSTANCE);
	AddOpcodeBuf(env->buf, self->c->parent->absolute_index);
	AddOpcodeBuf(env->buf, self->constructor_index);
}

void il_factor_new_instance_load(il_factor_new_instance * self, enviroment * env, call_context* cctx) {
	il_factor_new_instance_find(self, env, cctx);
	if(GetLastBCError()) {
		return;
	}
	//抽象クラスはインスタンス化できない
	if(type_is_abstract(self->c->parent)) {
		ThrowBCError(BCERROR_CONSTRUCT_ABSTRACT_TYPE_T, Ref2Str(type_name(self->c->parent)));
	}
}

generic_type* il_factor_new_instance_eval(il_factor_new_instance * self, enviroment * env, call_context* cctx) {
	il_factor_new_instance_find(self, env, cctx);
	if(GetLastBCError()) {
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
			il_type_argument* e = (il_type_argument*)AtVector(self->type_args, i);
			generic_type* arg = import_manager_resolve(GetNamespaceCContext(cctx), e->gcache, cctx);
			generic_type_addargs(a, arg);
		}
		self->instance_type = a;
	}
	return self->instance_type;
}

char* il_factor_new_instance_tostr(il_factor_new_instance* self, enviroment* env) {
	string_buffer* sb = NewBuffer();
	AppendsBuffer(sb, "new ");
	char* type = fqcn_cache_tostr(self->fqcnc);
	AppendsBuffer(sb, type);
	il_factor_type_args_tostr(sb, self->type_args, env);
	ILArgsToString(sb, self->argument_list, env);
	MEM_FREE(type);
	return ReleaseBuffer(sb);
}

void il_factor_new_instance_delete(il_factor_new_instance * self) {
	DeleteVector(self->argument_list, il_Factor_new_instace_delete_arg);
	DeleteVector(self->type_args, il_factor_new_instance_delete_typearg);
	fqcn_cache_delete(self->fqcnc);
	MEM_FREE(self);
}

//private
static void il_factor_new_instance_delete_typearg(VectorItem item) {
	il_type_argument* e = (il_type_argument*)item;
	DeleteILTypeArgument(e);
}

static void il_factor_new_instance_find(il_factor_new_instance * self, enviroment * env, call_context* cctx) {
	if(self->constructor_index != -1) {
		return;
	}
	#if defined(DEBUG)
	const char* namea = Ref2Str(self->fqcnc->namev);
	if(self->fqcnc->namev == InternString("Vector")) {
		int a = 0;
	}
	#endif
	//コンストラクタで生成するオブジェクトの肩を取得
	type* ty = GetEvalTypeCContext(cctx, self->fqcnc);
	if(ty == NULL) {
		ThrowBCError(BCERROR_NEW_INSTANCE_UNDEFINED_CLASS_T,
			Ref2Str(self->fqcnc->namev)
		);
		return;
	}
	//使用するコンストラクタを取得
	class_* cls = TYPE2CLASS(ty);
	int temp = -1;
	call_frame* cfr = PushCallContext(cctx, FRAME_RESOLVE_T);
	cfr->u.resolve.gtype = cls->parent->generic_self;
	cfr->u.resolve.typeargs = self->type_args;
	ResolveILTypeArgument(self->type_args, cctx);
	self->c = class_ilfind_constructor(cls, self->argument_list, env, cctx, &temp);
	self->constructor_index = temp;
	PopCallContext(cctx);
	if(temp == -1) {
		ThrowBCError(BCERROR_NEW_INSTANCE_UNDEFINED_CTOR_T,
			Ref2Str(cls->namev)
		);
	}
}

static void il_Factor_new_instace_delete_arg(VectorItem item) {
	il_argument* e = (il_argument*)item;
	DeleteILArgument(e);
}