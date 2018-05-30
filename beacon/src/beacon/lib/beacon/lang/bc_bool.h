#pragma once
#ifndef BEACON_LIB_SIGNAL_LANG_BOOL_H
#define BEACON_LIB_SIGNAL_LANG_BOOL_H
struct type;

/**
 * beacon::lang::Boolクラスを初期化します.
 */
void bc_bool_init();

/**
 * beacon::lang::Bool型を返します.
 * @return
 */
struct type* bc_bool_type();
#endif // !SIGNAL_LIB_SIGNAL_LANG_BOOL_H
