#pragma once
#ifndef SIGNAL_IL_IL_FUNCTION_H
#define SIGNAL_IL_IL_FUNCTION_H
#include "../util/vector.h"

struct fqcn_cache;
/**
 * 関数宣言を表す要素.
 */
typedef struct il_function {
	char* name;
	vector* parameter_list;
	vector* statement_list;
	//il_type* return_type;
	struct fqcn_cache* return_fqcn;
} il_function;

il_function* il_function_new(const char* name);

void il_function_dump(il_function* self, int depth);

void il_function_delete(il_function* self);
#endif // !SIGNAL_IL_IL_FUNCTION_H
