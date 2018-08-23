#include "method.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../util/text.h"
#include "../util/string_buffer.h"
#include "type_interface.h"
#include "parameter.h"
#include "namespace.h"
#include "object.h"
#include "../env/class_loader.h"
#include "../util/mem.h"
#include "../thread/thread.h"
#include "../il/call_context.h"
#include "../il/il_stmt_impl.h"
#include "../vm/vm.h"
#include "type_impl.h"
#include "type_parameter.h"
#include "generic_type.h"
#include "constructor.h"
#include <assert.h>

#if defined(_MSC_VER)
#pragma warning(disable:4996)
#endif

//proto
static void method_parameter_delete(vector_item item);
static void method_type_parameter_delete(vector_item item);
static void method_count(il_stmt* s, int* yeild_ret, int* ret);
static constructor* create_delegate_ctor(method* self, type* ty, class_loader* cll,int op_len);
static method* create_has_next(method* self, type* ty,class_loader* cll, vector* stmt_list, int* out_op_len);
static method* create_next(method* self, type* ty,class_loader* cll, generic_type* a, vector* stmt_list, int* out_op_len);
static vector* method_vm_args(method* self, frame* fr, frame* a);
static vector* method_vm_typeargs(method* self, frame* fr, frame* a);

method* method_malloc(string_view namev, const char* filename, int lineno) {
	method* ret = (method*)mem_malloc(sizeof(method), filename, lineno);
	ret->namev = namev;
	ret->parameters = vector_malloc(filename, lineno);
	ret->type = method_type_script_T;
	ret->access = access_public_T;
	ret->modifier = modifier_none_T;
	ret->parent = NULL;
	ret->type_parameters = vector_malloc(filename, lineno);
	ret->return_gtype = NULL;
	return ret;
}

void method_execute(method* self, frame * fr, enviroment* env) {
	#if defined(DEBUG)
	const char* namestr = string_pool_ref2str(self->namev);
	if(self->namev == string_pool_intern("writeLine")) {
		int a = 0;
	}
	#endif
	if (self->type == method_type_script_T) {
		script_method_execute(self->u.script_method, self, fr, env);
	} else if (self->type == method_type_native_T) {
		frame* a = frame_sub(fr);
		call_frame* cfr = NULL;
		vector* aArgs = NULL;
		vector* aTArgs = NULL;
		//レシーバも
		if(!modifier_is_static(self->modifier)) {
			object* receiver_obj = vector_pop(fr->value_stack);
			vector_assign(a->ref_stack, 0, receiver_obj);
			cfr = call_context_push(sg_thread_context(), frame_instance_invoke_T);
			cfr->u.instance_invoke.receiver = receiver_obj->gtype;
			aArgs = cfr->u.instance_invoke.args = method_vm_args(self, fr, a);
			aTArgs = cfr->u.instance_invoke.typeargs = method_vm_typeargs(self, fr, a);
		} else {
			cfr = call_context_push(sg_thread_context(), frame_static_invoke_T);
			aArgs = cfr->u.static_invoke.args = method_vm_args(self, fr, a);
			aTArgs = cfr->u.static_invoke.typeargs = method_vm_typeargs(self, fr, a);
		}
		native_method_execute(self->u.native_method, self, a, env);
		//戻り値を残す
		if(self->return_gtype != TYPE_VOID->generic_self) {
			vector_push(fr->value_stack, vector_pop(a->value_stack));
		}
		vector_delete(aArgs, vector_deleter_null);
		vector_delete(aTArgs, vector_deleter_null);
		call_context_pop(sg_thread_context());
		frame_delete(a);
	}
}

bool method_override(method* superM, method* subM, call_context* cctx) {
	//名前が違うか引数の数が違う
	if (superM->namev != subM->namev ||
		superM->parameters->length != subM->parameters->length) {
		return false;
	}
	generic_type* bl = type_baseline(superM->parent, subM->parent);
	assert(bl != NULL);
	//全ての引数を比較
	for (int i = 0; i < superM->parameters->length; i++) {
		parameter* superP = ((parameter*)vector_at(superM->parameters, i));
		parameter* subP = ((parameter*)vector_at(subM->parameters, i));
		generic_type* superGT = superP->gtype;
		generic_type* subGT = subP->gtype;

		call_frame* cfr = call_context_push(cctx, frame_resolve_T);
		cfr->u.resolve.gtype = bl;
		generic_type* superGT2 = generic_type_apply(superGT, cctx);
		call_context_pop(cctx);
//		assert(!generic_type_equals(superGT, superGT2));

//		generic_type_diff(superGT, superGT2);
		if(generic_type_distance(superGT2, subGT, cctx) != 0) {
			return false;
		}
	}
	generic_type* superRet = superM->return_gtype;
	generic_type* subRet = subM->return_gtype;
	call_frame* cfr = call_context_push(cctx, frame_resolve_T);
	cfr->u.resolve.gtype = bl;
	generic_type* superRet2 = generic_type_apply(superRet, cctx);
//	generic_type_diff(superRet, superRet2);
//	assert(!generic_type_equals(superRet, superRet2));
	int ret =generic_type_distance(superRet2, subRet, cctx);
	call_context_pop(cctx);
	return ret != -1;
}

int method_for_generic_index(method * self, string_view namev) {
	int ret = -1;
	for (int i = 0; i < self->type_parameters->length; i++) {
		type_parameter* e = (type_parameter*)vector_at(self->type_parameters, i);
		if (e->namev == namev) {
			ret = i;
			break;
		}
	}
	return ret;
}

void method_delete(method * self) {
	vector_delete(self->type_parameters, method_type_parameter_delete);
	vector_delete(self->parameters, method_parameter_delete);
	if (self->type == method_type_script_T) {
		script_method_delete(self->u.script_method);
	} else if (self->type == method_type_native_T) {
		native_method_delete(self->u.native_method);
	}
	MEM_FREE(self);
}

string_view method_mangle(method* self) {
	string_buffer* ret = string_buffer_new();
	string_buffer_appends(ret, string_pool_ref2str(self->namev));
	//引数が一つもないので終了
	if(self->parameters->length == 0) {
		char* raw = string_buffer_release(ret);
		string_view sv = string_pool_intern(raw);
		MEM_FREE(raw);
		return sv;
	}
	for(int i=0; i<self->parameters->length; i++) {
		parameter* e = (parameter*)vector_at(self->parameters, i);
		generic_type* gt = e->gtype;
		string_buffer_append(ret, '_');
		if(gt->core_type == NULL) {
			//ジェネリックの場合は methodname_c0 のように
			//何番目の型変数であるかを入れる
			if(gt->tag == generic_type_tag_class_T) {
				string_buffer_append(ret, 'c');
			} else if(gt->tag == generic_type_tag_method_T) {
				string_buffer_append(ret, 'm');
			} else {
				assert(false);
			}
			//数値 -> 文字
			char buff[256];
			memset(buff, '\0', 256);
			sprintf(buff, "%d", gt->virtual_type_index);
			string_buffer_appends(ret, buff);
		} else {
			string_buffer_appends(ret, string_pool_ref2str(type_full_name(gt->core_type)));
		}
	}
	char* raw = string_buffer_release(ret);
	string_view sv = string_pool_intern(raw);
	MEM_FREE(raw);
	return sv;
}

string_view method_unique(method* self) {
	string_buffer* ret = string_buffer_new();
	string_buffer_appends(ret, string_pool_ref2str(type_full_name(self->parent)));
	string_buffer_appends(ret, string_pool_ref2str(method_mangle(self)));
	char* raw = string_buffer_release(ret);
	string_view sv = string_pool_intern(raw);
	MEM_FREE(raw);
	return sv;
}

bool method_coroutine(method* self) {
	type* iteratorT = namespace_get_type(namespace_lang(), string_pool_intern("Iterator"));
	return (iteratorT && self->return_gtype->core_type == iteratorT);
}

bool method_yield(method* self, vector* stmt_list, bool* error) {
	(*error) = false;
	if(self->type != method_type_script_T || !method_coroutine(self)) {
		return false;
	}
	int yield_ret = 0;
	int ret = 0;
	for(int i=0; i<stmt_list->length; i++) {
		int yrtemp = 0;
		int rtemp = 0;
		il_stmt* e = (il_stmt*)vector_at(stmt_list, i);
		method_count(e, &yrtemp, &rtemp);
		yield_ret += yrtemp;
		ret += rtemp;
	}
	//yield return, return の混在
	if(yield_ret > 0 && ret > 0) {
		(*error) = true;
		return true;
	}
	return yield_ret > 0 ? true : false;
}

type* method_create_iterator_type(method* self,  class_loader* cll, vector* stmt_list) {
	call_context* lCctx = call_context_new(call_ctor_T);
	call_frame* lCfr = call_context_push(lCctx, frame_resolve_T);
	lCfr->u.resolve.gtype = self->return_gtype;
	string_view iterName = method_unique(self);
	type* iterT = namespace_get_type(namespace_lang(), string_pool_intern("Iterator"));
	//イテレータの実装クラスを登録
	generic_type* iterImplGT = generic_type_apply(self->return_gtype, lCctx);
	class_* iterImplC = class_new_proxy(iterImplGT, iterName);
	type* iterImplT = type_wrap_class(iterImplC);
	namespace_add_type(namespace_placeholder(), iterImplT);
	type_init_generic(iterImplT, 0);
	//イテレータのコンストラクタ追加
	int op_len = 0;
	class_add_method(iterImplC, create_has_next(self,  iterImplT, cll, stmt_list, &op_len));
	class_add_method(iterImplC, create_next(self, iterImplT, cll, vector_at(self->return_gtype->type_args_list, 0), stmt_list, &op_len));
	class_add_constructor(iterImplC, create_delegate_ctor(self, iterImplT, cll, op_len));
	call_context_pop(lCctx);
	call_context_delete(lCctx);
	return iterImplT;
}

generic_type* method_diff(method* abstract, method* concrete) {
	type* abstractT = abstract->parent;
	type* implT = concrete->parent;
	generic_type* bounds = type_baseline(abstractT, implT);
	return bounds;
}

method* method_clone(method* self) {
	method* ret = method_new(self->namev);
	ret->type = self->type;
	ret->modifier = self->modifier;
	ret->access = self->access;
	ret->return_gtype = generic_type_clone(self->return_gtype);
	for(int i=0; i<self->type_parameters->length; i++) {
		type_parameter* e = vector_at(self->type_parameters, i);
		type_parameter* ecpy = type_parameter_new(e->namev);
		ecpy->kind = e->kind;
		vector_push(ret->type_parameters, ecpy);
	}
	for(int i=0; i<self->parameters->length; i++) {
		parameter* e = vector_at(self->parameters, i);
		parameter* ecpy = parameter_new(e->namev);
		ecpy->gtype = e->gtype;
		vector_push(ret->parameters, ecpy);
	}
	return ret;
}

//private
static void method_parameter_delete(vector_item item) {
	parameter* e = (parameter*)item;
	parameter_delete(e);
}

static void method_type_parameter_delete(vector_item item) {
	type_parameter* e = (type_parameter*)item;
	type_parameter_delete(e);
}

static void method_count(il_stmt* s, int* yield_ret, int* ret) {
	switch (s->type) {
		case ilstmt_if_T:
		{
			//if() { ... }
			il_stmt_if* sif = s->u.if_;
			for(int i=0; i<sif->body->length; i++) {
				method_count((il_stmt*)vector_at(sif->body, i), yield_ret, ret);
			}
			for(int i=0; i<sif->elif_list->length; i++) {
				il_stmt_elif* seif = (il_stmt_elif*)vector_at(sif->elif_list, i);
				vector* body = seif->body;
				for(int j=0; j<body->length; j++) {
					method_count((il_stmt*)vector_at(body, j), yield_ret, ret);
				}
			}
			for(int i=0; i<sif->else_body->body->length; i++) {
				il_stmt* e = vector_at(sif->else_body->body, i);
				method_count(e, yield_ret, ret);
			}
			break;
		}
		case ilstmt_proc_T:
		case ilstmt_variable_decl_T:
		case ilstmt_variable_init_T:
			break;
		case ilstmt_return_T:
			(*ret)++;
			break;
		case ilstmt_while_T:
		{
			il_stmt_while* whi = s->u.while_;
			for(int i=0; i<whi->statement_list->length; i++) {
				il_stmt* e = vector_at(whi->statement_list, i);
				method_count(e, yield_ret, ret);
			}
			break;
		}
		case ilstmt_break_T:
		case ilstmt_continue_T:
		case ilstmt_inferenced_type_init_T:
			break;
		case ilstmt_try_T:
		{
			il_stmt_try* tr = s->u.try_;
			for(int i=0; i<tr->statement_list->length; i++) {
				il_stmt* e = (il_stmt*)vector_at(tr->statement_list, i);
				method_count(e, yield_ret, ret);
			}
			vector* catches = tr->catch_list;
			for(int i=0; i<catches->length; i++) {
				il_stmt_catch* ce = (il_stmt_catch*)vector_at(catches, i);
				for(int j=0; j<ce->statement_list->length; j++) {
					il_stmt* e = (il_stmt*)vector_at(ce->statement_list, j);
					method_count(e, yield_ret, ret);
				}
			}
			break;
		}
		case ilstmt_throw_T:
		case ilstmt_assert_T:
		case ilstmt_defer_T:
			break;
		case ilstmt_yield_return_T:
			(*yield_ret)++;
			break;
		case ilstmt_yield_break_T:
		default:
			//ERROR("ステートメントをダンプ出来ませんでした。");
			break;
	}
}

static constructor* create_delegate_ctor(method* self, type* ty, class_loader* cll,int op_len) {
	//イテレータのコンストラクタを作成
	constructor* iterCons = constructor_new();
	enviroment* envIterCons = enviroment_new();
	//コルーチンを生成したオブジェクトを受け取るパラメータ追加
	parameter* coroOwnerParam = parameter_new(string_pool_intern("owner"));
	vector_push(iterCons->parameter_list, coroOwnerParam);
	envIterCons->context_ref = cll;
	//コルーチンに渡された引数を引き継ぐパラメータ追加
	for(int i=0; i<self->parameters->length; i++) {
		parameter* methP = (parameter*)vector_at(self->parameters, i);
		parameter* consP = parameter_new(methP->namev);
		consP->gtype = methP->gtype;
		vector_push(iterCons->parameter_list, consP);
	}
	for (int i = 0; i < iterCons->parameter_list->length; i++) {
		parameter* e = (parameter*)vector_at(iterCons->parameter_list, i);
		symbol_table_entry(
			envIterCons->sym_table,
			e->gtype,
			e->namev
		);
		//実引数を保存
		//0番目は this のために開けておく
		opcode_buf_add(envIterCons->buf, (vector_item)op_store);
		opcode_buf_add(envIterCons->buf, (vector_item)(i + 1));
	}
	//親クラスへ連鎖
	opcode_buf_add(envIterCons->buf, (vector_item)op_chain_super);
	opcode_buf_add(envIterCons->buf, (vector_item)0);
	opcode_buf_add(envIterCons->buf, (vector_item)0);
	//このクラスのフィールドを確保
	opcode_buf_add(envIterCons->buf, (vector_item)op_alloc_field);
	opcode_buf_add(envIterCons->buf, (vector_item)ty->absolute_index);
	opcode_buf_add(envIterCons->buf, op_coro_init);
	opcode_buf_add(envIterCons->buf, iterCons->parameter_list->length);
	opcode_buf_add(envIterCons->buf, op_len);
	iterCons->env = envIterCons;
	return iterCons;
}

static method* create_has_next(method* self, type* ty, class_loader* cll, vector* stmt_list, int* out_op_len) {
	method* mt = method_new(string_pool_intern("moveNext"));
	mt->return_gtype = GENERIC_BOOL;
	mt->modifier = modifier_none_T;
	mt->access = access_public_T;
	mt->type = method_type_script_T;
	script_method* smt = script_method_new();
	enviroment* envSmt = enviroment_new();
	call_context* cctx = call_context_new(call_method_T);
	cctx->scope = self->parent->location;
	cctx->ty = self->parent;
	cctx->u.mt = self;
	envSmt->context_ref = cll;

	//iterate(int,int)のint,intを受け取る
	for(int i=0; i<self->parameters->length; i++) {
		parameter* e = vector_at(self->parameters, i);
		symbol_table_entry(
			envSmt->sym_table,
			e->gtype,
			e->namev
		);
		//実引数を保存
		//0番目は this のために開けておく
		//opcode_buf_add(envSmt->buf, (vector_item)op_store);
		//opcode_buf_add(envSmt->buf, (vector_item)(i + 1));
	}
	opcode_buf_add(envSmt->buf, (vector_item)op_store);
	opcode_buf_add(envSmt->buf, (vector_item)0);
	opcode_buf_add(envSmt->buf, (vector_item)op_coro_swap_self);
	opcode_buf_add(envSmt->buf, (vector_item)op_coro_resume);
	for(int i=0; i<stmt_list->length; i++) {
		il_stmt* e = (il_stmt*)vector_at(stmt_list, i);
		il_stmt_load(e, envSmt, cctx);
	}
	for(int i=0; i<stmt_list->length; i++) {
		il_stmt* e = (il_stmt*)vector_at(stmt_list, i);
		il_stmt_generate(e, envSmt, cctx);
	}
	opcode_buf_add(envSmt->buf, op_coro_exit);
	if(type_name(self->parent) == string_pool_intern("Base")) {
	//	enviroment_op_dump(envSmt, 0);
	}
	(*out_op_len) = envSmt->buf->source_vec->length;
	call_context_delete(cctx);
	smt->env = envSmt;
	mt->u.script_method = smt;
	mt->parent = ty;
	return mt;
}

static method* create_next(method* self, type* ty, class_loader* cll,generic_type* a, vector* stmt_list, int* out_op_len) {
	method* mt = method_new(string_pool_intern("current"));
	mt->return_gtype = a;
	mt->modifier = modifier_none_T;
	mt->access = access_public_T;
	mt->type = method_type_script_T;
	script_method* smt = script_method_new();
	enviroment* envSmt = enviroment_new();
	call_context* cctx = call_context_new(call_method_T);
	cctx->scope = self->parent->location;
	cctx->ty = self->parent;
	cctx->u.mt = mt;

	opcode_buf_add(envSmt->buf, (vector_item)op_store);
	opcode_buf_add(envSmt->buf, (vector_item)0);
	opcode_buf_add(envSmt->buf, (vector_item)op_coro_swap_self);
	opcode_buf_add(envSmt->buf, (vector_item)op_coro_current);

	envSmt->context_ref = cll;
	cctx->scope = self->parent->location;
	cctx->ty = self->parent;
	cctx->u.mt = self;
	
	smt->env = envSmt;
	mt->u.script_method = smt;
	mt->parent = ty;
	call_context_delete(cctx);
	//enviroment_op_dump(envSmt, 0);
	return mt;
}

static vector* method_vm_args(method* self, frame* fr, frame* a) {
	vector* args = vector_new();
	//引数を引き継ぐ
	int len = self->parameters->length;
	for(int i=0; i<len; i++) {
		object* ARG = vector_pop(fr->value_stack);
		assert(ARG != NULL);
		vector_assign(a->ref_stack, (len - i), ARG);
		vector_assign(args, (len - i), ARG->gtype);
	}
	return args;
}

static vector* method_vm_typeargs(method* self, frame* fr, frame* a) {
	//メソッドに渡された型引数を引き継ぐ
	vector* typeargs = vector_new();
	int typeparams = self->type_parameters->length;
	for(int i=0; i<typeparams; i++) {
		vector_item e = vector_pop(fr->type_args_vec);
		vector_assign(a->type_args_vec, (typeparams - i) - 1, e);
		vector_assign(typeargs, (typeparams - i) - 1, e);
	}
	return typeargs;
}