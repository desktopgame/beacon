#pragma once
#ifndef BEACON_IL_IL_STMT_WHILE_H
#define BEACON_IL_IL_STMT_WHILE_H
#include "../il_factor_interface.h"
#include "../il_stmt_interface.h"
#include "../../util/vector.h"

struct Enviroment;

typedef struct ILStatement_while {
	ILFactor* condition;
	Vector* statement_list;
} ILStatement_while;

ILStatement* WrapILWhile(ILStatement_while* self);

ILStatement_while* NewILWhile();

void GenerateILWhile(ILStatement_while* self, Enviroment* env, CallContext* cctx);

void LoadILWhile(ILStatement_while* self, Enviroment* env, CallContext* cctx);

void DeleteILWhile(ILStatement_while* self);
#endif // !SIGNAL_IL_IL_STMT_WHILE_H
