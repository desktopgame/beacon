#pragma once
#ifndef BEACON_LIB_SIGNAL_LANG_STRING_H
#define BEACON_LIB_SIGNAL_LANG_STRING_H
#include "../../../util/string_buffer.h"
struct object;
struct type;
/**
 * beacon::lang::Stringクラスを初期化します.
 */
void bc_string_init();

/**
 * beacon::lang::Stringが内部的に保持するバッファーを返します.
 * @param self
 * @return
 */
string_buffer* bc_string_raw(struct object* self);

/**
 * beacon::lang::String型を返します.
 * @return
 */
struct type* bc_string_type();
#endif // !SIGNAL_LIB_SIGNAL_LANG_STRING_H
