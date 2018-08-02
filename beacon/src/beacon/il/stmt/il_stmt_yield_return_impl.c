#include "il_stmt_yield_return_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"

il_stmt* il_stmt_wrap_yield_return(il_stmt_yield_return* self) {
	il_stmt* ret = il_stmt_new(ilstmt_yield_return);
	ret->type = ilstmt_yield_return;
	ret->u.yield_return = self;
	return ret;
}

il_stmt_yield_return* il_stmt_yield_return_malloc(const char* filename, int lineno) {
	il_stmt_yield_return* ret = (il_stmt_yield_return*)mem_malloc(sizeof(il_stmt_yield_return), filename, lineno);
	ret->fact = NULL;
	return ret;
}

void il_stmt_yield_return_dump(il_stmt_yield_return* self, int depth) {
	text_putindent(depth);
	text_printf("yield return");
	text_putline();
	il_factor_dump(self->fact, depth + 1);
}

void il_stmt_yield_return_generate(il_stmt_yield_return* self, enviroment* env, call_context* cctx) {
}

void il_stmt_yield_return_load(il_stmt_yield_return * self, enviroment* env, call_context* cctx) {
}

void il_stmt_yield_return_delete(il_stmt_yield_return* self) {
	il_factor_delete(self->fact);
	MEM_FREE(self);
}