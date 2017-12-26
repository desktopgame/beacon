#pragma once
#ifndef SIGNAL_IL_IL_METHOD_H
#define SIGNAL_IL_IL_METHOD_H
#include "il_type.h"
#include "il_stmt_list.h"
#include "../util/vector.h"
/**
 * メソッドの定義を表す要素.
 */
typedef struct il_method {
	char* name;
	vector* parameter_list;
	il_stmt_list* statement_list;
	il_type* return_type;
} il_method;
/**
 * メソッドを作成します.
 * @param name
 * @return
 */
il_method* il_method_new(const char* name);

/**
 * メソッドを出力します.
 * @param self
 * @param depth
 */
void il_method_dump(il_method* self, int depth);

/**
 * メソッドを開放します.
 * @param self
 */
void il_method_delete(il_method* self);
#endif // !SIGNAL_IL_IL_METHOD_H
