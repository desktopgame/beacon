#pragma once
#ifndef SIGNAL_IL_IL_STMT_WHILE_H
#define SIGNAL_IL_IL_STMT_WHILE_H
#include "../il_factor_interface.h"
#include "../il_stmt_list.h"

typedef struct il_stmt_while {
	il_factor* condition;
	il_stmt_list* body;
} il_stmt_while;
#endif // !SIGNAL_IL_IL_STMT_WHILE_H
