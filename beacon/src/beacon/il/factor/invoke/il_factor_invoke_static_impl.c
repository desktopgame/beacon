#include "il_factor_invoke_static_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../env/generic_type.h"
#include "../../../env/type/class_impl.h"
#include "../../../vm/enviroment.h"
#include "../../il_argument.h"
#include "../../il_type_argument.h"
#include "../../../util/xassert.h"
#include "../../../util/vector.h"

//proto
static void resolve_non_default(il_factor_invoke_static * self, enviroment * env);
static void resolve_default(il_factor_invoke_static * self, enviroment * env);
static void il_factor_invoke_static_check(il_factor_invoke_static * self, enviroment * env);
static void il_factor_invoke_static_args_delete(vector_item item);
static void il_factor_invoke_static_typeargs_delete(vector_item item);

il_factor_invoke_static* il_factor_invoke_static_new(const char* name) {
	il_factor_invoke_static* ret = (il_factor_invoke_static*)MEM_MALLOC(sizeof(il_factor_invoke_static));
	ret->args = NULL;
	ret->fqcn = NULL;
	ret->type_args = NULL;
	ret->name = text_strdup(name);
	ret->m = NULL;
	ret->index = -1;
	ret->resolved = NULL;
	return ret;
}

void il_factor_invoke_static_dump(il_factor_invoke_static* self, int depth) {
	text_putindent(depth);
	text_printfln("invoke static");

	text_putindent(depth + 1);
	text_printfln("%s", self->m->name);

	for(int i=0; i<self->args->length; i++) {
		il_argument* e = (il_argument*)vector_at(self->args, i);
		il_factor_dump(e->factor, depth + 2);
	}
}

void il_factor_invoke_static_generate(il_factor_invoke_static* self, enviroment* env) {
	for(int i=0; i<self->type_args->length; i++) {
		il_type_argument* e = (il_type_argument*)vector_at(self->type_args, i);
		assert(e->gtype != NULL);
		opcode_buf_add(env->buf, op_generic_add);
		generic_type_generate(e->gtype, env);
	}
	for(int i=0; i<self->args->length; i++) {
		il_argument* e = (il_argument*)vector_at(self->args, i);
		il_factor_generate(e->factor, env);
		if(il_error_panic()) {
			return;
		}
	}
	opcode_buf_add(env->buf, (vector_item)op_invokestatic);
	opcode_buf_add(env->buf, (vector_item)self->m->parent->absolute_index);
	opcode_buf_add(env->buf, (vector_item)self->index);
}

void il_factor_invoke_static_load(il_factor_invoke_static * self, enviroment * env) {
	ccpush_type_args(self->type_args);
	il_factor_invoke_static_check(self, env);
	ccpop_type_args();
}

generic_type* il_factor_invoke_static_eval(il_factor_invoke_static * self, enviroment * env) {
	il_factor_invoke_static_check(self, env);
	//メソッドを解決できなかった場合
	if(il_error_panic()) {
		return NULL;
	}
	generic_type* rgtp = self->m->return_gtype;
//	virtual_type returnvType = self->m->return_vtype;
	if(rgtp->tag != generic_type_tag_none) {
		resolve_non_default(self, env);
		return self->resolved;
	} else {
		resolve_default(self, env);
		return self->resolved;
	}
	return NULL;
}

char* il_factor_invoke_static_tostr(il_factor_invoke_static* self, enviroment* env) {
	string_buffer* sb = string_buffer_new();
	char* name = fqcn_cache_tostr(self->fqcn);
	string_buffer_appends(sb, name);
	string_buffer_append(sb, '.');
	string_buffer_appends(sb, self->name);
	il_factor_type_args_tostr(sb, self->type_args, env);
	il_factor_args_tostr(sb, self->args, env);
	MEM_FREE(name);
	return string_buffer_release(sb);
}

void il_factor_invoke_static_delete(il_factor_invoke_static* self) {
	vector_delete(self->args, il_factor_invoke_static_args_delete);
	vector_delete(self->type_args, il_factor_invoke_static_typeargs_delete);
	fqcn_cache_delete(self->fqcn);
//	generic_type_delete(self->resolved);
	MEM_FREE(self->name);
	MEM_FREE(self);
}
//private
//FIXME:il_factor_invokeからのコピペ
static void resolve_non_default(il_factor_invoke_static * self, enviroment * env) {
	if(self->resolved != NULL) {
		return;
	}
	generic_type* rgtp = self->m->return_gtype;
//	virtual_type returnvType = self->m->return_vtype;
	generic_type* instanced_type = (generic_type*)vector_at(self->type_args, rgtp->virtual_type_index);
	self->resolved = generic_type_new(instanced_type->core_type);
	self->resolved->tag = generic_type_tag_method;
	self->resolved->virtual_type_index = rgtp->virtual_type_index;
}

static void resolve_default(il_factor_invoke_static * self, enviroment * env) {
	if(self->resolved != NULL) {
		return;
	}
	generic_type* rgtp = self->m->return_gtype;
//	virtual_type returnvType = self->m->return_vtype;
	ccpush_type_args(self->type_args);
	self->resolved = generic_type_apply(rgtp);
	ccpop_type_args();
}

static void il_factor_invoke_static_check(il_factor_invoke_static * self, enviroment * env) {
	class_* cls = cc_class(self->fqcn);
	int temp = -1;
//	XSTREQ(self->name, "write");
	il_type_argument_resolve(self->type_args);
	//環境を設定
	ccpush_type_args(self->type_args);
	//メソッドを検索
	self->m = class_ilfind_smethod(cls, self->name, self->args, env, &temp);
	self->index = temp;
	//メソッドが見つからない
	if(temp == -1) {
		il_error_report(ilerror_undefined_method, self->name);
	}
	//元に戻す
	ccpop_type_args();
}

static void il_factor_invoke_static_args_delete(vector_item item) {
	il_argument* e = (il_argument*)item;
	il_argument_delete(e);
}

static void il_factor_invoke_static_typeargs_delete(vector_item item) {
	il_type_argument* e = (il_type_argument*)item;
	il_type_argument_delete(e);
}