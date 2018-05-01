#pragma once
#ifndef BEACON_LIB_SIGNAL_LANG_STRING_H
#define BEACON_LIB_SIGNAL_LANG_STRING_H
#include "../../../util/string_buffer.h"
struct object;

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
#endif // !SIGNAL_LIB_SIGNAL_LANG_STRING_H
