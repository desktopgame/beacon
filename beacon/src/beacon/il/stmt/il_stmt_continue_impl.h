#pragma once
#ifndef BEACON_IL_IL_STMT_CONTINUE_H
#define BEACON_IL_IL_STMT_CONTINUE_H
#include "../il_stmt_interface.h"

ILStatement* WrapILContinue();

void GenerateILContinue(void* empty, Enviroment* env, CallContext* cctx);

void LoadILContinue(void* empty, Enviroment* env, CallContext* cctx);

void DeleteILContinue(void* empty);
#endif // !SIGNAL_IL_IL_STMT_CONTINUE_H
