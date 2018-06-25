#include "il_operator_overload.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "il_parameter.h"
#include "il_stmt_interface.h"

static void il_operator_overload_delete_parameter(vector_item item);
static void il_operator_overload_delete_stmt(vector_item item);

il_operator_overload* il_operator_overload_new(operator_type type) {
	il_operator_overload* ret = (il_operator_overload*)MEM_MALLOC(sizeof(il_operator_overload));
	ret->op = type;
	ret->parameter_list = vector_new();
	ret->statement_list = vector_new();
	ret->return_fqcn = generic_cache_new();
	return ret;
}

void il_operator_overload_dump(il_operator_overload* self, int depth) {
	text_putindent(depth);
	text_printf("operator-overload ");
	operator_fprintf(stdout, self->op);
	text_printf(" -> ");
	generic_cache_print(self->return_fqcn);
	text_printfln("");
	for(int i=0; i<self->parameter_list->length; i++) {
		il_parameter* e = (il_parameter*)vector_at(self->parameter_list, i);
		il_parameter_dump(e, depth + 1);
	}
	for(int i=0; i<self->statement_list->length; i++) {
		il_stmt* e = (il_stmt*)vector_at(self->statement_list, i);
		il_stmt_dump(e, depth + 1);
	}
}

void il_operator_overload_delete(il_operator_overload* self) {
	vector_delete(self->parameter_list, il_operator_overload_delete_parameter);
	vector_delete(self->statement_list, il_operator_overload_delete_stmt);
	generic_cache_delete(self->return_fqcn);
	MEM_FREE(self);
}
//private
static void il_operator_overload_delete_parameter(vector_item item) {
	il_parameter* e = (il_parameter*)item;
	il_parameter_delete(e);
}

static void il_operator_overload_delete_stmt(vector_item item) {
	il_stmt* e = (il_stmt*)item;
	il_stmt_delete(e);
}