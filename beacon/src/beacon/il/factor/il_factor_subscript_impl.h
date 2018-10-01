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

il_factor* WrapILSubscript(il_factor_subscript* self);

#define il_factor_subscript_new() (MallocILSubscript(__FILE__, __LINE__))
il_factor_subscript* MallocILSubscript(const char* filename, int lineno);

void GenerateILSubscript(il_factor_subscript* self, enviroment* env, call_context* cctx);

void LoadILSubscript(il_factor_subscript* self, enviroment* env, call_context* cctx);

generic_type* EvalILSubscript(il_factor_subscript* self, enviroment* env, call_context* cctx);

char* ILSubscriptToString(il_factor_subscript* self, enviroment* env);

void DeleteILSubscript(il_factor_subscript* self);
#endif