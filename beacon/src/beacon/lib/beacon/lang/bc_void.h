#pragma once
#ifndef BEACON_LIB_SIGNAL_LANG_VOID_H
#define BEACON_LIB_SIGNAL_LANG_VOID_H
struct type;
/**
 * beacon::lang::Voidクラスを初期化します.
 */
void bc_void_init();

/**
 * beacon::lang::Void型を返します.
 * @return
 */
struct type* bc_void_type();
#endif // !SIGNAL_LIB_SIGNAL_LANG_VOID_H
