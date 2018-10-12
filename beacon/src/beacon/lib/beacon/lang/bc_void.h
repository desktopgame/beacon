#pragma once
#ifndef BEACON_LIB_SIGNAL_LANG_VOID_H
#define BEACON_LIB_SIGNAL_LANG_VOID_H
struct type;
/**
 * beacon::lang::Voidクラスを初期化します.
 */
void InitBCVoid();

/**
 * beacon::lang::Void型を返します.
 * @return
 */
struct type* GetBCVoidType();
#endif // !SIGNAL_LIB_SIGNAL_LANG_VOID_H
