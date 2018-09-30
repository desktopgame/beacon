#pragma once
#ifndef BEACON_IL_IL_STMT_CONTINUE_H
#define BEACON_IL_IL_STMT_CONTINUE_H
#include "../il_stmt_interface.h"

il_stmt* WrapILContinue();

void il_stmt_continue_generate(void* empty, struct enviroment* env, call_context* cctx);

void LoadILContinue(void* empty, struct enviroment* env, call_context* cctx);

void il_stmt_continue_delete(void* empty);
#endif // !SIGNAL_IL_IL_STMT_CONTINUE_H
