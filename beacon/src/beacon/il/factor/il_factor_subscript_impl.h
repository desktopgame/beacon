#ifndef BEACON_IL_FACTOR_SUBSCRIPT_H
#define BEACON_IL_FACTOR_SUBSCRIPT_H
#include "../il_factor_interface.h"

struct operator_overload;

typedef struct il_factor_subscript {
	il_factor* receiver;
	il_factor* pos;
	int operator_index;
	struct operator_overload* opov;
} il_factor_subscript;

il_factor* il_factor_wrap_subscript(il_factor_subscript* self);

#define il_factor_subscript_new() (il_factor_subscript_malloc(__FILE__, __LINE__))
il_factor_subscript* il_factor_subscript_malloc(const char* filename, int lineno);

void il_factor_subscript_generate(il_factor_subscript* self, enviroment* env, call_context* cctx);

void il_factor_subscript_load(il_factor_subscript* self, enviroment* env, call_context* cctx);

generic_type* il_factor_subscript_eval(il_factor_subscript* self, enviroment* env, call_context* cctx);

char* il_factor_subscript_tostr(il_factor_subscript* self, enviroment* env);

void il_factor_subscript_delete(il_factor_subscript* self);
#endif