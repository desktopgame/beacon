#pragma once
#ifndef BEACON_IL_IL_STMT_BREAK_H
#define BEACON_IL_IL_STMT_BREAK_H
#include "../il_stmt_interface.h"

struct Enviroment;

ILStatement* WrapILBreak();

void GenerateILBreak(void* empty, Enviroment* env, CallContext* cctx);

void LoadILBreak(void* empty, Enviroment* env, CallContext* cctx);

void DeleteILBreak(void* empty);
#endif // !SIGNAL_IL_IL_STMT_BREAK_H
