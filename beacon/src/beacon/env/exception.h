#pragma once
#ifndef BEACON_ENV_EXCEPTION_H
#define BEACON_ENV_EXCEPTION_H
#include <stdarg.h>

struct object;
struct vm;

/**
 * signal::lang::Exception 型の例外を作成します.
 * @param vmc
 * @param message
 * @return
 */
struct object* exception_new_simple(struct vm* vmc, const char* message);
/**
 * signal::lang::Exception 型の例外を作成します.
 * フォーマット付きです.
 * @param vmc
 * @param message
 * @param ...
 * @return
 */
struct object* exception_new_simplef(struct vm* vmc, const char* message, ...);
#endif // !SIGNAL_ENV_EXCEPTION_H
