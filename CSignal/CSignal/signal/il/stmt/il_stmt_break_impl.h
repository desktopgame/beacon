#pragma once
#ifndef SIGNAL_IL_IL_STMT_BREAK_H
#define SIGNAL_IL_IL_STMT_BREAK_H
#include "../il_stmt_interface.h"

struct enviroment;

il_stmt* il_stmt_wrap_break();

void il_stmt_break_generate(void* empty, struct enviroment* env, il_load_cache* cache);

void il_stmt_break_load(void* empty, struct enviroment* env, il_load_cache* cache, il_ehandler* eh);

void il_stmt_break_dump(void* empty, int depth);

void il_stmt_break_delete(void* empty);
#endif // !SIGNAL_IL_IL_STMT_BREAK_H
