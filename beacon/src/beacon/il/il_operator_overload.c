#include "il_operator_overload.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "il_parameter.h"
#include "il_stmt_interface.h"

static void il_operator_overload_delete_parameter(VectorItem item);
static void il_operator_overload_delete_stmt(VectorItem item);

il_operator_overload* il_operator_overload_new(operator_type type) {
	il_operator_overload* ret = (il_operator_overload*)MEM_MALLOC(sizeof(il_operator_overload));
	ret->op = type;
	ret->parameter_list = NewVector();
	ret->statement_list = NewVector();
	ret->return_fqcn = generic_cache_new();
	return ret;
}

void il_operator_overload_delete(il_operator_overload* self) {
	DeleteVector(self->parameter_list, il_operator_overload_delete_parameter);
	DeleteVector(self->statement_list, il_operator_overload_delete_stmt);
	generic_cache_delete(self->return_fqcn);
	MEM_FREE(self);
}
//private
static void il_operator_overload_delete_parameter(VectorItem item) {
	il_parameter* e = (il_parameter*)item;
	DeleteILParameter(e);
}

static void il_operator_overload_delete_stmt(VectorItem item) {
	il_stmt* e = (il_stmt*)item;
	DeleteILStmt(e);
}