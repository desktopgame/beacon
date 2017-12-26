#pragma once
#ifndef SIGNAL_IL_IL_FACTOR_STRING_H
#define SIGNAL_IL_IL_FACTOR_STRING_H
#include "../il_factor_interface.h"
//struct opcode_buf;
/**
 * 文字列を表す要素.
 */
typedef struct il_factor_string {
	char* value;
} il_factor_string;

/**
 * 文字列を表す要素をスーパーセットにラップします.
 * @param self
 * @return
 */
il_factor* il_factor_wrap_string(il_factor_string* self);

/**
 * 文字列を表す用をを作成します.
 * @param name
 * @return
 */
il_factor_string* il_factor_string_new(const char* name);

/**
 * 文字列を表す要素を出力します.
 * @param self
 * @param depth
 */
void il_factor_string_dump(il_factor_string* self, int depth);

/**
 * 文字列を生成します.
 * @param self
 * @param buf
 */
void il_factor_string_generate(il_factor_string* self, struct opcode_buf* buf);

/**
 * 文字列を表す要素を開放します.
 * @param self
 */
void il_factor_string_delete(il_factor_string* self);
#endif // !SIGNAL_IL_IL_FACTOR_STRING_H
