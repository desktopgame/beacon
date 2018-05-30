#pragma once
#ifndef BEACON_LIB_SIGNAL_LANG_INT_H
#define BEACON_LIB_SIGNAL_LANG_INT_H
struct type;
/**
 * beacon::lang::Intクラスを初期化します.
 */
void bc_int_init();

/**
 * beacon::lang::Intを返します.
 * @return
 */
struct type* bc_int_type();
#endif // !SIGNAL_LIB_SIGNAL_LANG_INT_H
