#include "lambda_scope.h"
#include "method.h"
#include "../util/mem.h"

lambda_scope* lambda_scope_new(method* body) {
	lambda_scope* ret = (lambda_scope*)MEM_MALLOC(sizeof(lambda_scope));
	ret->body = body;
	ret->offset = 0;
	return ret;
}

void lambda_scope_delete(lambda_scope* self) {
	MEM_FREE(self);
}