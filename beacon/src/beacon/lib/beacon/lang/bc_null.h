#pragma once
#ifndef BEACON_LIB_SIGNAL_LANG_NULL_H
#define BEACON_LIB_SIGNAL_LANG_NULL_H
struct type;
/**
 * beacon::lang::Nullクラスを初期化します.
 */
void bc_null_init();

/**
 * beacon::lang::Null型を返します.
 * @return
 */
struct type* bc_null_type();
#endif // !SIGNAL_LIB_SIGNAL_LANG_NULL_H
