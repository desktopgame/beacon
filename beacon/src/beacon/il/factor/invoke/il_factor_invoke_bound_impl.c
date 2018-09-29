#include "il_factor_invoke_bound_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../env/field.h"
#include "../../../env/property.h"
#include "../../../env/operator_overload.h"
#include "../../../env/generic_type.h"
#include "../../../env/type_interface.h"
#include "../../../env/type/class_impl.h"
#include "../../../vm/symbol_entry.h"
#include "../../../vm/enviroment.h"
#include "../../il_argument.h"
#include "../../il_type_argument.h"

//proto
static void il_factor_invoke_bound_delete_typeargs(VectorItem item);
static void resolve_non_default(il_factor_invoke_bound * self, enviroment * env, call_context* cctx);
static void resolve_default(il_factor_invoke_bound * self, enviroment * env, call_context* cctx);
static void il_factor_invoke_bound_check(il_factor_invoke_bound * self, enviroment * env, call_context* cctx);
static void il_factor_invoke_bound_args_delete(VectorItem item);
static void il_factor_invoke_bound_generate_method(il_factor_invoke_bound* self, enviroment* env, call_context* cctx);
static void il_factor_invoke_bound_generate_subscript(il_factor_invoke_bound* self, enviroment* env, call_context* cctx);
static generic_type* il_factor_invoke_bound_return_gtype(il_factor_invoke_bound* self, call_context* cctx);
static generic_type* il_factor_invoke_bound_evalImpl(il_factor_invoke_bound * self, enviroment * env, call_context* cctx);

il_factor_invoke_bound* il_factor_invoke_bound_new(string_view namev) {
	il_factor_invoke_bound* ret = (il_factor_invoke_bound*)MEM_MALLOC(sizeof(il_factor_invoke_bound));
	ret->namev = namev;
	ret->args = NULL;
	ret->type_args = NULL;
	ret->index = -1;
	ret->resolved = NULL;
	ret->tag = BOUND_INVOKE_UNDEFINED_T;
	return ret;
}

void il_factor_invoke_bound_generate(il_factor_invoke_bound* self, enviroment* env, call_context* cctx) {
	il_factor_invoke_bound_generate_method(self, env, cctx);
	il_factor_invoke_bound_generate_subscript(self, env, cctx);
}

void il_factor_invoke_bound_load(il_factor_invoke_bound * self, enviroment * env, call_context* cctx) {
	il_factor_invoke_bound_check(self, env, cctx);
}

generic_type* il_factor_invoke_bound_eval(il_factor_invoke_bound * self, enviroment * env, call_context* cctx) {
	generic_type* ret = il_factor_invoke_bound_evalImpl(self, env, cctx);
	assert(ret != NULL);
	return ret;
}

char* il_factor_invoke_bound_tostr(il_factor_invoke_bound* self, enviroment* env) {
	string_buffer* sb = NewBuffer();
	AppendsBuffer(sb, Ref2Str(self->namev));
	il_factor_type_args_tostr(sb, self->type_args, env);
	il_factor_args_tostr(sb, self->type_args, env);
	return ReleaseBuffer(sb);
}

void il_factor_invoke_bound_delete(il_factor_invoke_bound* self) {
	DeleteVector(self->args, il_factor_invoke_bound_args_delete);
	DeleteVector(self->type_args, il_factor_invoke_bound_delete_typeargs);
	//generic_type_delete(self->resolved);
	MEM_FREE(self);
}

operator_overload* il_factor_invoke_bound_find_set(il_factor_invoke_bound* self, il_factor* value, struct enviroment* env, call_context* cctx, int* outIndex) {
	assert(self->tag == BOUND_INVOKE_SUBSCRIPT_T);
	Vector* args = NewVector();
	PushVector(args, ((il_argument*)AtVector(self->args, 0))->factor);
	PushVector(args, value);
	operator_overload* opov = class_ilfind_operator_overload(TYPE2CLASS(self->u.subscript.opov->parent), OPERATOR_SUB_SCRIPT_SET_T, args, env, cctx, outIndex);
	DeleteVector(args, VectorDeleterOfNull);
	return opov;
}

//private
//FIXME:il_factor_invokeからのコピペ
static void il_factor_invoke_bound_delete_typeargs(VectorItem item) {
	il_type_argument* e = (il_type_argument*)item;
	il_type_argument_delete(e);
}

static void resolve_non_default(il_factor_invoke_bound * self, enviroment * env, call_context* cctx) {
	if(self->resolved != NULL) {
		return;
	}
	type* tp = NULL;
	generic_type* rgtp  = il_factor_invoke_bound_return_gtype(self, cctx);
	if(rgtp->tag == GENERIC_TYPE_TAG_CLASS_T) {
		self->resolved = generic_type_new(NULL);
		self->resolved->tag = GENERIC_TYPE_TAG_CLASS_T;
		self->resolved->virtual_type_index = rgtp->virtual_type_index;
	} else if(rgtp->tag == GENERIC_TYPE_TAG_METHOD_T) {
		//メソッドに渡された型引数を参照する
		generic_type* instanced_type = (generic_type*)AtVector(self->type_args, rgtp->virtual_type_index);
		self->resolved = generic_type_new(instanced_type->core_type);
		self->resolved->tag = GENERIC_TYPE_TAG_CLASS_T;
	}
}

static void resolve_default(il_factor_invoke_bound * self, enviroment * env, call_context* cctx) {
	if(self->resolved != NULL) {
		return;
	}
	generic_type* rgtp = il_factor_invoke_bound_return_gtype(self, cctx);
	self->resolved = generic_type_apply(rgtp, cctx);
}

static void il_factor_invoke_bound_check(il_factor_invoke_bound * self, enviroment * env, call_context* cctx) {
	if(self->index != -1) {
		return;
	}
	//対応するメソッドを検索
	type* ctype = call_context_type(cctx);
	int temp = -1;
	il_type_argument_resolve(self->type_args, cctx);
	for(int i=0; i<self->args->length; i++) {
		il_argument* ilarg = AtVector(self->args, i);
		il_factor_load(ilarg->factor, env, cctx);
	}
	BC_ERROR();
	#if defined(DEBUG)
	const char* nstr = Ref2Str(self->namev);
	const char* str = Ref2Str(type_name(ctype));
	#endif
	call_frame* cfr = call_context_push(cctx, FRAME_SELF_INVOKE_T);
	cfr->u.self_invoke.args = self->args;
	cfr->u.self_invoke.typeargs = self->type_args;
	self->tag = BOUND_INVOKE_METHOD_T;
	self->u.m = class_ilfind_method(TYPE2CLASS(ctype), self->namev, self->args, env, cctx, &temp);
	self->index = temp;
	BC_ERROR();
	if(self->index != -1) {
		call_context_pop(cctx);
		return;
	}
	//添字アクセスとして解決する
	generic_type* receiver_gtype = NULL;
	symbol_entry* local = EntrySymbolTable(env->sym_table, NULL, self->namev);
	if(receiver_gtype == NULL && local != NULL) {
		receiver_gtype = local->gtype;
		self->u.subscript.tag = SUBSCRIPT_LOCAL_T;
		self->u.subscript.u.local = local;
		self->u.subscript.index = local->index;
	}
	//フィールドとして解決する
	field* fi = class_find_field(call_context_class(cctx), self->namev, &temp);
	if(receiver_gtype == NULL && fi != NULL) {
		receiver_gtype = fi->gtype;
		self->u.subscript.tag = SUBSCRIPT_FIELD_T;
		self->u.subscript.u.fi = fi;
		self->u.subscript.index = temp;
	}
	//プロパティとして解決する
	property* prop = class_find_property(call_context_class(cctx), self->namev, &temp);
	if(receiver_gtype == NULL && prop != NULL) {
		receiver_gtype = prop->gtype;
		self->u.subscript.tag = SUBSCRIPT_PROPERTY_T;
		self->u.subscript.u.prop = prop;
		self->u.subscript.index = temp;
	}
	if(receiver_gtype != NULL) {
		self->tag = BOUND_INVOKE_SUBSCRIPT_T;
		self->u.subscript.opov = class_argfind_operator_overload(TYPE2CLASS(GENERIC2TYPE(receiver_gtype)), OPERATOR_SUB_SCRIPT_GET_T, self->args, env, cctx, &temp);
		self->index = temp;
		if(temp == -1) {
			ThrowBCError(BCERROR_INVOKE_BOUND_UNDEFINED_METHOD_T,
				Ref2Str(self->namev)
			);
		}
	}
	if(self->index == -1) {
		ThrowBCError(BCERROR_INVOKE_BOUND_UNDEFINED_METHOD_T,
			Ref2Str(type_name(ctype)),
			Ref2Str(self->namev)
		);
	}
	call_context_pop(cctx);
}

static void il_factor_invoke_bound_args_delete(VectorItem item) {
	il_argument* e = (il_argument*)item;
	il_argument_delete(e);
}

static void il_factor_invoke_bound_generate_method(il_factor_invoke_bound* self, enviroment* env, call_context* cctx) {
	assert(self->tag != BOUND_INVOKE_UNDEFINED_T);
	if(self->tag != BOUND_INVOKE_METHOD_T) {
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
		il_factor_generate(e->factor, env, cctx);
		if(GetLastBCError()) {
			return;
		}
	}
	if(IsStaticModifier(self->u.m->modifier)) {
		AddOpcodeBuf(env->buf, (VectorItem)OP_INVOKESTATIC);
		AddOpcodeBuf(env->buf, (VectorItem)self->u.m->parent->absolute_index);
		AddOpcodeBuf(env->buf,(VectorItem) self->index);
	} else {
		AddOpcodeBuf(env->buf,(VectorItem) OP_THIS);
		if(self->u.m->access == ACCESS_PRIVATE_T) {
			AddOpcodeBuf(env->buf, (VectorItem)OP_INVOKESPECIAL);
			AddOpcodeBuf(env->buf, (VectorItem)self->index);
		} else {
			AddOpcodeBuf(env->buf, (VectorItem)OP_INVOKEVIRTUAL);
			AddOpcodeBuf(env->buf, (VectorItem)self->index);
		}
	}
}

static void il_factor_invoke_bound_generate_subscript(il_factor_invoke_bound* self, enviroment* env, call_context* cctx) {
	assert(self->tag != BOUND_INVOKE_UNDEFINED_T);
	if(self->tag != BOUND_INVOKE_SUBSCRIPT_T) {
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
		il_factor_generate(e->factor, env, cctx);
		if(GetLastBCError()) {
			return;
		}
	}
	subscript_descriptor subs = self->u.subscript;
	if(subs.tag == SUBSCRIPT_LOCAL_T) {
		AddOpcodeBuf(env->buf, OP_LOAD);
		AddOpcodeBuf(env->buf, subs.index);
	} else if(subs.tag == SUBSCRIPT_FIELD_T) {
		AddOpcodeBuf(env->buf, OP_THIS);
		GenerateGetField(env->buf, subs.u.fi, subs.index);
	} else if(subs.tag == SUBSCRIPT_PROPERTY_T) {
		AddOpcodeBuf(env->buf, OP_THIS);
		GenerateGetProperty(env->buf, subs.u.prop, subs.index);
	} else {
		assert(false);
	}
	AddOpcodeBuf(env->buf, OP_INVOKEOPERATOR);
	AddOpcodeBuf(env->buf, self->index);
}

static generic_type* il_factor_invoke_bound_return_gtype(il_factor_invoke_bound* self, call_context* cctx) {
	assert(self->tag != BOUND_INVOKE_UNDEFINED_T);
	return generic_type_apply(self->tag == BOUND_INVOKE_METHOD_T ?
			self->u.m->return_gtype :
			self->u.subscript.opov->return_gtype, cctx);
}

static generic_type* il_factor_invoke_bound_evalImpl(il_factor_invoke_bound * self, enviroment * env, call_context* cctx) {
	type* tp = NULL;
	//メソッドが見つからない
	il_factor_invoke_bound_check(self, env, cctx);
	if(GetLastBCError()) {
		return NULL;
	}
	call_frame* cfr = NULL;
	if(self->tag == BOUND_INVOKE_METHOD_T) {
		cfr = call_context_push(cctx, FRAME_SELF_INVOKE_T);
		cfr->u.self_invoke.args = self->args;
		cfr->u.self_invoke.typeargs = self->type_args;
	} else {
		cfr = call_context_push(cctx, FRAME_INSTANCE_INVOKE_T);
		cfr->u.instance_invoke.receiver = generic_type_apply(subscript_descriptor_receiver(&self->u.subscript), cctx);
		cfr->u.instance_invoke.args = self->args;
		cfr->u.instance_invoke.typeargs = self->type_args;
	}

	if(il_factor_invoke_bound_return_gtype(self, cctx)->tag != GENERIC_TYPE_TAG_NONE_T) {
		resolve_non_default(self, env, cctx);
		assert(self->resolved != NULL);
		call_context_pop(cctx);
		return self->resolved;
	} else {
		resolve_default(self, env, cctx);
		assert(self->resolved != NULL);
		call_context_pop(cctx);
		return self->resolved;
	}
	call_context_pop(cctx);
	assert(self->resolved != NULL);
	return self->resolved;
}