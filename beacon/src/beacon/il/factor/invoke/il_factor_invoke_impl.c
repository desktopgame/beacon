#include "il_factor_invoke_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../env/operator_overload.h"
#include "../../../env/generic_type.h"
#include "../../../env/type_interface.h"
#include "../../../env/type/class_impl.h"
#include "../../../env/method.h"
#include "../../../env/class_loader.h"
#include "../../../vm/enviroment.h"
#include "../../il_argument.h"
#include "../../il_type_argument.h"
#include "../../il_factor_impl.h"
#include <string.h>
#include <stdio.h>

//proto
static void resolve_non_default(il_factor_invoke * self, enviroment * env, call_context* cctx);
static void resolve_default(il_factor_invoke * self, enviroment * env, call_context* cctx);
static void il_factor_invoke_args_delete(VectorItem item);
static void il_factor_invoke_check(il_factor_invoke * self, enviroment * env, call_context* cctx);
static generic_type* il_factor_invoke_return_gtype(il_factor_invoke* self);
static void il_factor_invoke_generate_method(il_factor_invoke* self, enviroment* env, call_context* cctx);
static void il_factor_invoke_generate_subscript(il_factor_invoke* self, enviroment* env, call_context* cctx);

il_factor_invoke* NewILInvoke(string_view namev) {
	il_factor_invoke* ret = (il_factor_invoke*)MEM_MALLOC(sizeof(il_factor_invoke));
	ret->args = NULL;
	ret->receiver = NULL;
	ret->type_args = NULL;
	ret->index = -1;
	ret->tag = INSTANCE_INVOKE_UNDEFINED_T;
	ret->namev = namev;
	ret->resolved = NULL;
	return ret;
}

void il_factor_invoke_generate(il_factor_invoke* self, enviroment* env, call_context* cctx) {
	il_factor_invoke_generate_method(self, env, cctx);
	il_factor_invoke_generate_subscript(self, env, cctx);
}

void il_factor_invoke_load(il_factor_invoke * self, enviroment * env, call_context* cctx) {
	if(self->index != -1) {
		return;
	}
	call_frame* cfr = PushCallContext(cctx, FRAME_INSTANCE_INVOKE_T);
	cfr->u.instance_invoke.args = self->args;
	cfr->u.instance_invoke.typeargs = self->type_args;
	cfr->u.instance_invoke.receiver = EvalILFactor(self->receiver, env, cctx);
	LoadILFactor(self->receiver, env, cctx);
	il_factor_invoke_check(self, env, cctx);
	PopCallContext(cctx);
}

generic_type* il_factor_invoke_eval(il_factor_invoke * self, enviroment * env, call_context* cctx) {
	il_factor_invoke_check(self, env, cctx);
	if(GetLastBCError()) {
		return NULL;
	}
	generic_type* rgtp = il_factor_invoke_return_gtype(self);
	generic_type* ret = NULL;
	//型変数をそのまま返す場合
	if(rgtp->tag != GENERIC_TYPE_TAG_NONE_T) {
		resolve_non_default(self, env, cctx);
		ret = self->resolved;
	//型変数ではない型を返す
	} else {
		resolve_default(self, env, cctx);
		ret = self->resolved;
	}
	return ret;
}

char* il_factor_invoke_tostr(il_factor_invoke* self, enviroment* env) {
	string_buffer* sb = NewBuffer();
	char* invstr = ILFactorToString(self->receiver, env);
	AppendsBuffer(sb, invstr);
	AppendBuffer(sb, '.');
	AppendsBuffer(sb, Ref2Str(self->namev));
	il_factor_type_args_tostr(sb, self->type_args, env);
	ILArgsToString(sb, self->type_args, env);
	MEM_FREE(invstr);
	return ReleaseBuffer(sb);
}

void il_factor_invoke_delete(il_factor_invoke* self) {
	DeleteVector(self->args, il_factor_invoke_args_delete);
	DeleteVector(self->type_args, VectorDeleterOfNull);
	DeleteILFactor(self->receiver);
	//generic_type_delete(self->resolved);
	MEM_FREE(self);
}

operator_overload* il_factor_invoke_find_set(il_factor_invoke* self, il_factor* value, enviroment* env, call_context* cctx, int* outIndex) {
	assert(self->tag == INSTANCE_INVOKE_SUBSCRIPT_T);
	Vector* args = NewVector();
	PushVector(args, ((il_argument*)AtVector(self->args, 0))->factor);
	PushVector(args, value);
	operator_overload* opov = class_ilfind_operator_overload(TYPE2CLASS(self->u.opov->parent), OPERATOR_SUB_SCRIPT_SET_T, args, env, cctx, outIndex);
	DeleteVector(args, VectorDeleterOfNull);
	return opov;
}
//private
static void resolve_non_default(il_factor_invoke * self, enviroment * env, call_context* cctx) {
	if(self->resolved != NULL) {
		return;
	}
	generic_type* receivergType = EvalILFactor(self->receiver, env, cctx);
	generic_type* rgtp = il_factor_invoke_return_gtype(self);
	if(rgtp->tag == GENERIC_TYPE_TAG_CLASS_T) {
		//レシーバの実体化された型の中で、
		//メソッドの戻り値 'T' が表す位置に対応する実際の型を取り出す。
		generic_type* instanced_type = (generic_type*)AtVector(receivergType->type_args_list, rgtp->virtual_type_index);
		self->resolved = generic_type_clone(instanced_type);
		self->resolved->tag = GENERIC_TYPE_TAG_CLASS_T;
	} else if(rgtp->tag == GENERIC_TYPE_TAG_METHOD_T) {
		//メソッドに渡された型引数を参照する
		generic_type* instanced_type = (generic_type*)AtVector(self->type_args, rgtp->virtual_type_index);
		self->resolved = generic_type_clone(instanced_type);
		self->resolved->tag = GENERIC_TYPE_TAG_CLASS_T;
	}
}

static void resolve_default(il_factor_invoke * self, enviroment * env, call_context* cctx) {
	if(self->resolved != NULL) {
		return;
	}
	generic_type* receivergType = EvalILFactor(self->receiver, env, cctx);
	generic_type* rgtp = il_factor_invoke_return_gtype(self);
//	virtual_type returnvType = self->m->return_vtype;
	//内側に型変数が含まれているかもしれないので、
	//それをここで展開する。
	call_frame* cfr = PushCallContext(cctx, FRAME_INSTANCE_INVOKE_T);
	cfr->u.instance_invoke.receiver = receivergType;
	cfr->u.instance_invoke.args = self->args;
	cfr->u.instance_invoke.typeargs = self->type_args;
	self->resolved = generic_type_apply(rgtp, cctx);
	PopCallContext(cctx);
}

static void il_factor_invoke_check(il_factor_invoke * self, enviroment * env, call_context* cctx) {
	//レシーバの読み込み
	LoadILFactor(self->receiver, env, cctx);
	if(GetLastBCError()) {
		return;
	}
	if(self->receiver->type == ILFACTOR_VARIABLE_T) {
		il_factor_variable* ilvar = self->receiver->u.variable_;
		assert(ilvar->type != ILVARIABLE_TYPE_STATIC_T);
	}
	//レシーバの型を評価
	generic_type* gtype = EvalILFactor(self->receiver, env, cctx);
	if(GetLastBCError()) {
		return;
	}
	il_type_argument_resolve(self->type_args, cctx);
	type* ctype = gtype->core_type;
	#if defined(DEBUG)
	const char* cname = Ref2Str(type_name(ctype));
	#endif
	//ジェネリックな変数に対しても
	//Objectクラスのメソッドは呼び出せる
	if(ctype == NULL) {
		ctype = TYPE_OBJECT;
	}
	//メソッドを検索
	assert(ctype != NULL);
	int temp = -1;
	self->tag = INSTANCE_INVOKE_METHOD_T;
	self->u.m = type_ilfind_method(ctype, self->namev, self->args, env, cctx, &temp);
	self->index = temp;
	if(temp != -1) {
		return;
	}
	//メソッドが見つからなかったら
	//subscript(添字アクセス)として解決する
	if(self->args->length != 1) {
		//hoge(1) = 0;
		//の形式なら引数は一つのはず
		ThrowBCError(BCERROR_INVOKE_INSTANCE_UNDEFINED_METHOD_T,
			Ref2Str(type_name(ctype)),
			Ref2Str(self->namev)
		);
		return;
	}
	self->tag = INSTANCE_INVOKE_SUBSCRIPT_T;
	self->u.opov = class_argfind_operator_overload(TYPE2CLASS(ctype), OPERATOR_SUB_SCRIPT_GET_T, self->args, env, cctx, &temp);
	self->index = temp;
	if(temp == -1) {
		ThrowBCError(BCERROR_INVOKE_INSTANCE_UNDEFINED_METHOD_T,
			Ref2Str(type_name(ctype)),
			Ref2Str(self->namev)
		);
		return;
	}
}

static void il_factor_invoke_args_delete(VectorItem item) {
	il_argument* e = (il_argument*)item;
	DeleteILArgument(e);
}

static generic_type* il_factor_invoke_return_gtype(il_factor_invoke* self) {
	assert(self->tag != INSTANCE_INVOKE_UNDEFINED_T);
	return self->tag == INSTANCE_INVOKE_METHOD_T ? self->u.m->return_gtype : self->u.opov->return_gtype;
}

static void il_factor_invoke_generate_method(il_factor_invoke* self, enviroment* env, call_context* cctx) {
	assert(self->tag != INSTANCE_INVOKE_UNDEFINED_T);
	if(self->tag != INSTANCE_INVOKE_METHOD_T) {
		return;
	}
	for(int i=0; i<self->type_args->length; i++) {
		il_type_argument* e = (il_type_argument*)AtVector(self->type_args, i);
		assert(e->gtype != NULL);
		AddOpcodeBuf(env->buf, OP_GENERIC_ADD);
		generic_type_generate(e->gtype, env);
	}
	for(int i=0; i<self->args->length; i++) {
		il_argument* e = (il_argument*)AtVector(self->args, i);
		GenerateILFactor(e->factor, env, cctx);
	}
	GenerateILFactor(self->receiver, env, cctx);
	if(self->u.m->parent->tag == TYPE_INTERFACE_T) {
		AddOpcodeBuf(env->buf, (VectorItem)OP_INVOKEINTERFACE);
		AddOpcodeBuf(env->buf, (VectorItem)self->u.m->parent->absolute_index);
		AddOpcodeBuf(env->buf, (VectorItem)self->index);
	} else {
		assert(!IsStaticModifier(self->u.m->modifier));
		if(self->u.m->access == ACCESS_PRIVATE_T) {
			AddOpcodeBuf(env->buf, (VectorItem)OP_INVOKESPECIAL);
			AddOpcodeBuf(env->buf, (VectorItem)self->index);
		} else {
			AddOpcodeBuf(env->buf, (VectorItem)OP_INVOKEVIRTUAL);
			AddOpcodeBuf(env->buf, (VectorItem)self->index);
		}
	}
}

static void il_factor_invoke_generate_subscript(il_factor_invoke* self, enviroment* env, call_context* cctx) {
	assert(self->tag != INSTANCE_INVOKE_UNDEFINED_T);
	if(self->tag != INSTANCE_INVOKE_SUBSCRIPT_T) {
		return;
	}
	for(int i=0; i<self->type_args->length; i++) {
		il_type_argument* e = (il_type_argument*)AtVector(self->type_args, i);
		assert(e->gtype != NULL);
		AddOpcodeBuf(env->buf, OP_GENERIC_ADD);
		generic_type_generate(e->gtype, env);
	}
	for(int i=0; i<self->args->length; i++) {
		il_argument* e = (il_argument*)AtVector(self->args, i);
		GenerateILFactor(e->factor, env, cctx);
	}
	GenerateILFactor(self->receiver, env, cctx);
	AddOpcodeBuf(env->buf, OP_INVOKEOPERATOR);
	AddOpcodeBuf(env->buf, self->index);
}