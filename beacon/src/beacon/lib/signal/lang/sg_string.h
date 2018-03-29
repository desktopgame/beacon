#pragma once
#ifndef BEACON_LIB_SIGNAL_LANG_STRING_H
#define BEACON_LIB_SIGNAL_LANG_STRING_H
#include "../../../util/string_buffer.h"
struct object;

/**
 * signal::lang::Stringクラスを初期化します.
 */
void sg_string_init();

/**
 * signal::lang::Stringが内部的に保持するバッファーを返します.
 * @param self
 * @return
 */
string_buffer* sg_string_raw(struct object* self);
#endif // !SIGNAL_LIB_SIGNAL_LANG_STRING_H
