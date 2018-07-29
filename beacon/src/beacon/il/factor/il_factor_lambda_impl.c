#include "il_factor_lambda_impl.h"
#include "../il_factor_impl.h"
#include "../il_stmt_impl.h"
#include "../../env/type_impl.h"
#include "../../env/import_manager.h"
#include "../../env/class_loader.h"
#include "../../env/parameter.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../util/string_buffer.h"

static void il_factor_lambda_param_delete(vector_item item);
static void il_factor_lambda_stmt_delete(vector_item item);

il_factor* il_factor_wrap_lambda(il_factor_lambda* self) {
	il_factor* ret = il_factor_new(ilfactor_lambda);
	ret->u.lambda_ = self;
	return ret;
}

il_factor_lambda* il_factor_lambda_new() {
	il_factor_lambda* ret = (il_factor_lambda*)MEM_MALLOC(sizeof(il_factor_lambda));
	ret->parameter_vec = vector_new();
	ret->statement_vec = vector_new();
	ret->return_gcache = generic_cache_new();
	ret->return_gtype = NULL;
	ret->offset = 0;
	ret->resolved = NULL;
	return ret;
}

void il_factor_lambda_dump(il_factor_lambda* self, int depth) {
	text_putindent(depth);
	text_printfln("`(");
	for(int i=0; i<self->parameter_vec->length; i++) {
		il_parameter* e = (il_parameter*)vector_at(self->parameter_vec, i);
		il_parameter_dump(e, depth + 1);
	}
	text_putindent(depth);
	text_printfln(" ) -> ");
	generic_cache_print(self->return_gcache);
	text_printf("{");
	for(int i=0; i<self->statement_vec->length; i++) {
		il_stmt* e = (il_stmt*)vector_at(self->statement_vec, i);
		il_stmt_dump(e, depth + 1);
	}
	text_printf("}");
	text_putline();
}

void il_factor_lambda_generate(il_factor_lambda* self, enviroment* env, call_context* cctx) {
}

void il_factor_lambda_load(il_factor_lambda* self, enviroment* env, call_context* cctx) {
	if(self->return_gtype == NULL) {
		self->return_gtype = import_manager_resolve(NULL, NULL, self->return_gcache);
	}
}

generic_type* il_factor_lambda_eval(il_factor_lambda* self, enviroment* env, call_context* cctx) {
	/*
	//lambda_scope* scope = cctop_lambda_scope();
	if(self->offset != scope->offset) {
		return NULL;
	}
	if(self->resolved != NULL) {
		return self->resolved;
	}
	parameter* param = vector_at(scope->body->parameter_list, scope->offset);
	generic_type* param_gtype = param->gtype;
	generic_type* ins = generic_type_apply(param_gtype);
	type* interT = ins->core_type;
	//ターゲット引数がインターフェイスではない
	if(interT == NULL || interT->tag != type_interface) {
		il_error_report(ilerror_can_t_resolve_lambda, string_pool_ref2str(scope->body->namev), string_pool_ref2str(param->namev));
		return NULL;
	}
	//関数型インターフェイスでない
	interface_* inter = TYPE2INTERFACE(interT);
	if(!interface_is_functional(inter)) {
		il_error_report(ilerror_not_functional_interface, string_pool_ref2str(type_name(interT)));
		return NULL;
	}
	//関数型インターフェイスだが、戻り値がマッチしない
	method* f = interface_get_function(inter);
	if(generic_type_distance(f->return_gtype, self->return_gtype) < 0) {
		il_error_report(ilerror_can_t_resolve_lambda, string_pool_ref2str(scope->body->namev), string_pool_ref2str(param->namev));
		return NULL;
	}
	//、引数の数が違う
	if(f->parameter_list->length != self->parameter_vec->length) {
		il_error_report(ilerror_can_t_resolve_lambda, string_pool_ref2str(scope->body->namev), string_pool_ref2str(param->namev));
		return NULL;
	}
	//、戻り値が違う
	for(int i=0; i<f->parameter_list->length; i++) {
		//メソッドの引数
		parameter* param = vector_at(f->parameter_list, i);
		generic_type* param_gtype = param->gtype;
		//ラムダの引数
		//`(Parameer a, Parameter b) -> Void { ... }
		il_parameter* lparam = vector_at(self->parameter_vec, i);
		generic_type* lparam_gtype = import_manager_resolve(env->context_ref->import_manager, cc_namespace(), lparam->fqcn);
		if(generic_type_distance(param_gtype, lparam_gtype) < 0) {
			return NULL;
		}
	}
	self->resolved = ins;
	return ins;
	*/
	return NULL;
}

char* il_factor_lambda_tostr(il_factor_lambda* self, enviroment* env) {
	string_buffer* sb = string_buffer_new();
	string_buffer_appends(sb, "lambda(");
	if(self->resolved == NULL) {
		string_buffer_appends(sb, "unresolved");
	} else {
		string_buffer_appends(sb, type_name(GENERIC2TYPE(self->resolved)));
	}
	string_buffer_append(sb, ')');
	return string_buffer_release(sb);
}

void il_factor_lambda_delete(il_factor_lambda* self) {
	vector_delete(self->parameter_vec, il_factor_lambda_param_delete);
	vector_delete(self->statement_vec, il_factor_lambda_stmt_delete);
	generic_cache_delete(self->return_gcache);
	MEM_FREE(self);
}
//private
static void il_factor_lambda_param_delete(vector_item item) {
	il_parameter* e = (il_parameter*)item;
	il_parameter_delete(e);
}

static void il_factor_lambda_stmt_delete(vector_item item) {
	il_stmt* e = (il_stmt*)item;
	il_stmt_delete(e);
}