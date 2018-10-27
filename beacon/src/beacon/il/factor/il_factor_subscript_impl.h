#ifndef BEACON_IL_FACTOR_SUBSCRIPT_H
#define BEACON_IL_FACTOR_SUBSCRIPT_H
#include "../il_factor_interface.h"

struct OperatorOverload;

typedef struct ILFactor_subscript {
	ILFactor* receiver;
	ILFactor* pos;
	int operator_index;
	struct OperatorOverload* opov;
} ILFactor_subscript;

ILFactor* WrapILSubscript(ILFactor_subscript* self);

#define ILFactor_subscript_new() (MallocILSubscript(__FILE__, __LINE__))
ILFactor_subscript* MallocILSubscript(const char* filename, int lineno);

void GenerateILSubscript(ILFactor_subscript* self, Enviroment* env, CallContext* cctx);

void LoadILSubscript(ILFactor_subscript* self, Enviroment* env, CallContext* cctx);

GenericType* EvalILSubscript(ILFactor_subscript* self, Enviroment* env, CallContext* cctx);

char* ILSubscriptToString(ILFactor_subscript* self, Enviroment* env);

void DeleteILSubscript(ILFactor_subscript* self);
#endif