#pragma once
#ifndef BEACON_IL_IL_FACTOR_NULL_H
#define BEACON_IL_IL_FACTOR_NULL_H
#include "../il_factor_interface.h"

struct enviroment;
struct type;

void GenerateILNull(void* empty, struct enviroment* env, call_context* cctx);

void LoadILNull(void* empty, struct enviroment* env, call_context* cctx);

generic_type* EvalILNull(void* empty, struct enviroment* env, call_context* cctx);

char* ILNullToString(void* empty, struct enviroment* env);
#endif // !SIGNAL_IL_IL_FACTOR_NULL_H
