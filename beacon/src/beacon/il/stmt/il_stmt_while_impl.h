#pragma once
#ifndef BEACON_IL_IL_STMT_WHILE_H
#define BEACON_IL_IL_STMT_WHILE_H
#include "../il_factor_interface.h"
#include "../il_stmt_interface.h"
#include "../../util/vector.h"

struct Enviroment;

typedef struct il_stmt_while {
	il_factor* condition;
	Vector* statement_list;
} il_stmt_while;

il_stmt* WrapILWhile(il_stmt_while* self);

il_stmt_while* NewILWhile();

void GenerateILWhile(il_stmt_while* self, Enviroment* env, CallContext* cctx);

void LoadILWhile(il_stmt_while* self, Enviroment* env, CallContext* cctx);

void DeleteILWhile(il_stmt_while* self);
#endif // !SIGNAL_IL_IL_STMT_WHILE_H
