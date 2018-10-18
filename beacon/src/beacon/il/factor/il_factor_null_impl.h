#pragma once
#ifndef BEACON_IL_IL_FACTOR_NULL_H
#define BEACON_IL_IL_FACTOR_NULL_H
#include "../il_factor_interface.h"

struct Enviroment;
struct type;

void GenerateILNull(void* empty, Enviroment* env, call_context* cctx);

void LoadILNull(void* empty, Enviroment* env, call_context* cctx);

generic_type* EvalILNull(void* empty, Enviroment* env, call_context* cctx);

char* ILNullToString(void* empty, Enviroment* env);
#endif // !SIGNAL_IL_IL_FACTOR_NULL_H
