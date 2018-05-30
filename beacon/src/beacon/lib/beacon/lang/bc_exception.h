#pragma once
#ifndef BEACON_LIB_SIGNAL_LANG_EXCEPTION_H
#define BEACON_LIB_SIGNAL_LANG_EXCEPTION_H
struct type*
/**
 * beacon::lang::Exceptionクラスを初期化します.
 */
void bc_exception_init();

/**
 * beacon::lang::Exception型を返します.
 */
struct type* bc_exception_type();
#endif // !SIGNAL_LIB_SIGNAL_LANG_EXCEPTION_H
