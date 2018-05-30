#pragma once
#ifndef BEACON_LIB_SIGNAL_LANG_H
#define BEACON_LIB_SIGNAL_LANG_H
struct type;
/**
 * beacon::lang::Objectクラスを初期化します.
 */
void bc_object_init();

/**
 * beacon::lang::Object型を返します.
 */
struct type* bc_object_type();
#endif // !SIGNAL_LIB_SIGNAL_LANG_H
