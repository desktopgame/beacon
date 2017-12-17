#pragma once
#ifndef SIGNAL_IL_IL_FACTOR_CALL_H
#define SIGNAL_IL_IL_FACTOR_CALL_H
#include "../il_argument_list.h"
/**
 * 関数呼び出しを表す要素.
 */
typedef struct il_factor_call {
	char* name;
	il_argument_list* argument_list;
} il_factor_call;

/**
 * 関数呼び出しをスーパーセットにラップします.
 * @param self
 * @return
 */
il_factor* il_factor_wrap_call(il_factor_call* self);

/**
 * 関数呼び出しを表す要素を作成します.
 * @param name
 * @return
 */
il_factor_call* il_factor_call_new(const char* name);

/**
 * 関数呼び出しを出力します.
 * @param self
 * @param depth
 */
void il_factor_call_dump(il_factor_call* self, int depth);

/**
 * 関数呼び出しを開放します.
 * @param self
 */
void il_factor_call_delete(il_factor_call* self);
#endif // !SIGNAL_IL_IL_FACTOR_CALL_H
