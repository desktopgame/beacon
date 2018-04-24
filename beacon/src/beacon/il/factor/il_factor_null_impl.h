#pragma once
#ifndef BEACON_IL_IL_FACTOR_NULL_H
#define BEACON_IL_IL_FACTOR_NULL_H
#include "../il_factor_interface.h"

struct enviroment;
struct type;
void il_factor_null_dump(void* empty, int depth);

void il_factor_null_generate(void* empty, struct enviroment* env, il_context* ilctx);

void il_factor_null_load(void* empty, struct enviroment* env, il_context* ilctx);

generic_type* il_factor_null_eval(void* empty, struct enviroment* env, il_context* ilctx);

char* il_factor_null_tostr(void* empty, struct enviroment* env, il_context* ilctx);
#endif // !SIGNAL_IL_IL_FACTOR_NULL_H
