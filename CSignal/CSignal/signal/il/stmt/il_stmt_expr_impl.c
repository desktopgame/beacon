#include "il_stmt_expr_impl.h"
#include <stdlib.h>

il_stmt_expr * il_stmt_expr_new() {
	il_stmt_expr* ret = (il_stmt_expr*)malloc(sizeof(il_stmt_expr));
	ret->factor = NULL;
	return ret;
}

void il_stmt_expr_delete(il_stmt_expr * self) {
	il_factor_delete(self->factor);
	free(self);
}
