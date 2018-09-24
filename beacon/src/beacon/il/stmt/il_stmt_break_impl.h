#pragma once
#ifndef BEACON_IL_IL_STMT_BREAK_H
#define BEACON_IL_IL_STMT_BREAK_H
#include "../il_stmt_interface.h"

struct enviroment;

il_stmt* il_stmt_wrap_break();

void il_stmt_break_generate(void* empty, struct enviroment* env, call_context* cctx);

void il_stmt_break_load(void* empty, struct enviroment* env, call_context* cctx);

void il_stmt_break_delete(void* empty);
#endif // !SIGNAL_IL_IL_STMT_BREAK_H
