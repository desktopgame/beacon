#include "il_factor_lambda_impl.h"
#include "../il_factor_impl.h"
#include "../il_stmt_impl.h"
#include "../../env/type_impl.h"
#include "../../env/import_manager.h"
#include "../../env/class_loader.h"
#include "../../env/parameter.h"
#include "../../util/mem.h"
#include "../../util/text.h"

static void il_factor_lambda_param_delete(vector_item item);
static void il_factor_lambda_stmt_delete(vector_item item);

il_factor* il_factor_wrap_lambda(il_factor_lambda* self) {
	il_factor* ret = (il_factor*)MEM_MALLOC(sizeof(il_factor));
	ret->type = ilfactor_lambda;
	ret->u.lambda_ = self;
	return ret;
}

il_factor_lambda* il_factor_lambda_new() {
	il_factor_lambda* ret = (il_factor_lambda*)MEM_MALLOC(sizeof(il_factor_lambda));
	ret->parameter_vec = vector_new();
	ret->statement_vec = vector_new();
	ret->return_gtype = generic_cache_new();
	ret->offset = 0;
	return ret;
}

void il_factor_lambda_dump(il_factor_lambda* self, int depth) {
	/*
	`(
		Int a
	 ) -> Void {
		 ...
}
	*/
	text_putindent(depth);
	text_printfln("`(");
	for(int i=0; i<self->parameter_vec->length; i++) {
		il_parameter* e = (il_parameter*)vector_at(self->parameter_vec, i);
		il_parameter_dump(e, depth + 1);
	}
	text_putindent(depth);
	text_printfln(" ) -> ");
	generic_cache_print(self->return_gtype);
	text_printf("{");
	for(int i=0; i<self->statement_vec->length; i++) {
		il_stmt* e = (il_stmt*)vector_at(self->statement_vec, i);
		il_stmt_dump(e, depth + 1);
	}
	text_printf("}");
	text_putline();
}

void il_factor_lambda_generate(il_factor_lambda* self, enviroment* env) {
}

void il_factor_lambda_load(il_factor_lambda* self, enviroment* env) {
}

generic_type* il_factor_lambda_eval(il_factor_lambda* self, enviroment* env) {
	return NULL;
}

char* il_factor_lambda_tostr(il_factor_lambda* self, enviroment* env) {
	return NULL;
}

void il_factor_lambda_delete(il_factor_lambda* self) {
	vector_delete(self->parameter_vec, il_factor_lambda_param_delete);
	vector_delete(self->statement_vec, il_factor_lambda_stmt_delete);
	generic_cache_delete(self->return_gtype);
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