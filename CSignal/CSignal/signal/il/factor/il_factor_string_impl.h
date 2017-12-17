#pragma once
#ifndef SIGNAL_IL_IL_FACTOR_STRING_H
#define SIGNAL_IL_IL_FACTOR_STRING_H
/**
 * 文字列を表す要素.
 */
typedef struct il_factor_string {
	char* value;
} il_factor_string;

/**
 * 文字列を表す用をを作成します.
 * @param name
 * @return
 */
il_factor_string* il_factor_string_new(const char* name);

/**
 * 文字列を表す要素
 * @param self
 */
void il_factor_string_delete(il_factor_string* self);
#endif // !SIGNAL_IL_IL_FACTOR_STRING_H
