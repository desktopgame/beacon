#pragma once
#ifndef BEACON_IL_IL_STMT_BREAK_H
#define BEACON_IL_IL_STMT_BREAK_H
#include "../il_stmt_interface.h"

struct Enviroment;

il_stmt* WrapILBreak();

void GenerateILBreak(void* empty, Enviroment* env, call_context* cctx);

void LoadILBreak(void* empty, Enviroment* env, call_context* cctx);

void DeleteILBreak(void* empty);
#endif // !SIGNAL_IL_IL_STMT_BREAK_H
