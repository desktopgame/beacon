#pragma once
#ifndef BEACON_IL_IL_METHOD_H
#define BEACON_IL_IL_METHOD_H
#include "../env/generic_cache.h"
#include "../util/vector.h"
#include "../util/string_pool.h"
#include "../ast/access_level.h"
#include "../ast/modifier_type.h"
#include <stdbool.h>
/**
 * メソッドの定義を表す要素.
 */
typedef struct il_method {
	string_view namev;
	vector* parameter_list;
	vector* statement_list;
	//il_type* return_type;
	generic_cache* return_fqcn;
	access_level access;
	modifier_type modifier;
	vector* type_parameter_list;
	bool no_stmt;
} il_method;
/**
 * メソッドを作成します.
 * @param name
 * @return
 */
il_method* il_method_new(string_view namev);

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
