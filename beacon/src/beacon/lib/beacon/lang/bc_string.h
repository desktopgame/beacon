#pragma once
#ifndef BEACON_LIB_SIGNAL_LANG_STRING_H
#define BEACON_LIB_SIGNAL_LANG_STRING_H
#include "../../../util/string_buffer.h"
struct Object;
struct Type;
/**
 * beacon::lang::Stringクラスを初期化します.
 */
void InitBCString();

/**
 * beacon::lang::Stringが内部的に保持するバッファーを返します.
 * @param self
 * @return
 */
Buffer* GetRawBCString(struct Object* self);

/**
 * beacon::lang::String型を返します.
 * @return
 */
struct Type* GetBCStringType();
#endif // !SIGNAL_LIB_SIGNAL_LANG_STRING_H
