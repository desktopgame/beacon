#ifndef BEACON_ENV_LAMBDASCOPE_H
#define BEACON_ENV_LAMBDASCOPE_H
struct method;

typedef struct lambda_scope {
	struct method* body;
	int offset;
} lambda_scope;

lambda_scope* lambda_scope_new(struct method* body);

void lambda_scope_delete(lambda_scope* self);
#endif