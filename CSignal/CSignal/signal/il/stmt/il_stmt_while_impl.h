#pragma once
#ifndef SIGNAL_IL_IL_STMT_WHILE_H
#define SIGNAL_IL_IL_STMT_WHILE_H
#include "../il_factor_interface.h"
#include "../il_stmt_interface.h"
#include "../../util/vector.h"

struct enviroment;

typedef struct il_stmt_while {
	il_factor* condition;
	vector* statement_list;
} il_stmt_while;

il_stmt* il_stmt_wrap_while(il_stmt_while* self);

il_stmt_while* il_stmt_while_new();

void il_stmt_while_dump(il_stmt_while* self, int depth);

void il_stmt_while_generate(il_stmt_while* self, struct enviroment* env, il_load_cache* cache);

void il_stmt_while_delete(il_stmt_while* self);
#endif // !SIGNAL_IL_IL_STMT_WHILE_H
