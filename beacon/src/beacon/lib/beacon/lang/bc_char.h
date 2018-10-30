#pragma once
#ifndef BEACON_LIB_SIGNAL_LANG_CHAR_H
#define BEACON_LIB_SIGNAL_LANG_CHAR_H
struct Type;
/**
 * beacon::lang::Charクラスを初期化します.
 */
void InitBCChar();

/**
 * beacon::lang::Char型を返します.
 * @return
 */
struct Type* GetBCCharType();
#endif // !SIGNAL_LIB_SIGNAL_LANG_CHAR_H
