#pragma once
#ifndef BEACON_LIB_SIGNAL_LANG_INT_H
#define BEACON_LIB_SIGNAL_LANG_INT_H
struct Type;
/**
 * beacon::lang::Intクラスを初期化します.
 */
void InitBCInt();

/**
 * beacon::lang::Intを返します.
 * @return
 */
struct Type* GetBCIntType();
#endif // !SIGNAL_LIB_SIGNAL_LANG_INT_H
