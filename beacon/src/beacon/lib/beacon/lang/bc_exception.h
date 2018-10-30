#pragma once
#ifndef BEACON_LIB_SIGNAL_LANG_EXCEPTION_H
#define BEACON_LIB_SIGNAL_LANG_EXCEPTION_H
struct Type;
/**
 * beacon::lang::Exceptionクラスを初期化します.
 */
void InitBCException();

/**
 * beacon::lang::Exception型を返します.
 */
struct Type* GetBCExceptionType();
#endif // !SIGNAL_LIB_SIGNAL_LANG_EXCEPTION_H
