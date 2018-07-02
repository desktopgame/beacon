#ifndef BEACON_IL_IL_FACTOR_LAMBDA_IMPL_H
#define BEACON_IL_IL_FACTOR_LAMBDA_IMPL_H
#include "../il_parameter.h"
#include "../../util/vector.h"
#include "../../env/generic_cache.h"
struct il_factor;
struct enviroment;
typedef struct il_factor_lambda {
	vector* statement_vec;
	vector* parameter_vec;
	generic_cache* return_gtype;
} il_factor_lambda;

struct il_factor* il_factor_wrap_lambda(il_factor_lambda* self);

il_factor_lambda* il_factor_lambda_new();

void il_factor_lambda_dump(il_factor_lambda* self, int depth);

void il_factor_lambda_generate(il_factor_lambda* self, struct enviroment* env);

void il_factor_lambda_load(il_factor_lambda* self, struct enviroment* env);

struct generic_type* il_factor_lambda_eval(il_factor_lambda* self, struct enviroment* env);

char* il_factor_lambda_tostr(il_factor_lambda* self, struct enviroment* env);

void il_factor_lambda_delete(il_factor_lambda* self);
#endif