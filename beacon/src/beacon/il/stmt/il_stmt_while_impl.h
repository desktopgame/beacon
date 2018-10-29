#pragma once
#ifndef BEACON_IL_IL_STMT_WHILE_H
#define BEACON_IL_IL_STMT_WHILE_H
#include "../il_factor_interface.h"
#include "../il_stmt_interface.h"
#include "../../util/vector.h"

struct Enviroment;

typedef struct ILWhile {
	ILFactor* condition;
	Vector* statement_list;
} ILWhile;

ILStatement* WrapILWhile(ILWhile* self);

ILWhile* NewILWhile();

void GenerateILWhile(ILWhile* self, Enviroment* env, CallContext* cctx);

void LoadILWhile(ILWhile* self, Enviroment* env, CallContext* cctx);

void DeleteILWhile(ILWhile* self);
#endif // !SIGNAL_IL_IL_STMT_WHILE_H
