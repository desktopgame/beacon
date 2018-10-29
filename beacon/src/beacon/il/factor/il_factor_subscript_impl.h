#ifndef BEACON_IL_FACTOR_SUBSCRIPT_H
#define BEACON_IL_FACTOR_SUBSCRIPT_H
#include "../il_factor_interface.h"

struct OperatorOverload;

typedef struct ILSubscript {
	ILFactor* Receiver;
	ILFactor* Position;
	int OperatorIndex;
	struct OperatorOverload* Operator;
} ILSubscript;

ILFactor* WrapILSubscript(ILSubscript* self);

#define ILSubscript_new() (MallocILSubscript(__FILE__, __LINE__))
ILSubscript* MallocILSubscript(const char* filename, int lineno);

void GenerateILSubscript(ILSubscript* self, Enviroment* env, CallContext* cctx);

void LoadILSubscript(ILSubscript* self, Enviroment* env, CallContext* cctx);

GenericType* EvalILSubscript(ILSubscript* self, Enviroment* env, CallContext* cctx);

char* ILSubscriptToString(ILSubscript* self, Enviroment* env);

void DeleteILSubscript(ILSubscript* self);
#endif