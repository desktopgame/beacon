#pragma once
#ifndef BEACON_IL_IL_FUNCTION_H
#define BEACON_IL_IL_FUNCTION_H
#include "../util/vector.h"
#include "../util/string_pool.h"

struct generic_cache;
/**
 * 関数宣言を表す要素.
 */
typedef struct il_function {
	StringView namev;
	Vector* type_parameter_vec;
	Vector* parameter_list;
	Vector* statement_list;
	//il_type* return_type;
	struct generic_cache* return_fqcn;
} il_function;

/**
 * 新しい関数宣言を作成します.
 * @param namev
 * @return
 */
il_function* NewILFunction(StringView namev);

/**
 * 関数を解放します.
 * @param self
 */
void DeleteILFunction(il_function* self);
#endif // !SIGNAL_IL_IL_FUNCTION_H
