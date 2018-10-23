#pragma once
#ifndef BEACON_IL_IL_FUNCTION_H
#define BEACON_IL_IL_FUNCTION_H
#include "../util/vector.h"
#include "../util/string_pool.h"

struct generic_cache;
/**
 * 関数宣言を表す要素.
 */
typedef struct ILFunction {
	StringView Name;
	Vector* TypeParameters;
	Vector* Parameters;
	Vector* Statements;
	struct generic_cache* ReturnGCache;
} ILFunction;

/**
 * 新しい関数宣言を作成します.
 * @param name
 * @return
 */
ILFunction* NewILFunction(StringView name);

/**
 * 関数を解放します.
 * @param self
 */
void DeleteILFunction(ILFunction* self);
#endif // !SIGNAL_IL_IL_FUNCTION_H
