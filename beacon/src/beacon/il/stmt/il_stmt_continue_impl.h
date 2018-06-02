#pragma once
#ifndef BEACON_IL_IL_STMT_CONTINUE_H
#define BEACON_IL_IL_STMT_CONTINUE_H
#include "../il_stmt_interface.h"

il_stmt* il_stmt_wrap_continue();

void il_stmt_continue_generate(void* empty, struct enviroment* env);

void il_stmt_continue_load(void* empty, struct enviroment* env);

void il_stmt_continue_dump(void* empty, int depth);

void il_stmt_continue_delete(void* empty);
#endif // !SIGNAL_IL_IL_STMT_CONTINUE_H
