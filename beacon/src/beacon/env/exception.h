#pragma once
#ifndef BEACON_ENV_EXCEPTION_H
#define BEACON_ENV_EXCEPTION_H
#include <stdarg.h>

struct object;
struct frame;

/**
 * signal::lang::Exception 型の例外を作成します.
 * @param fr
 * @param message
 * @return
 */
struct object* exception_new_simple(struct frame* fr, const char* message);
/**
 * signal::lang::Exception 型の例外を作成します.
 * フォーマット付きです.
 * @param fr
 * @param message
 * @param ...
 * @return
 */
struct object* exception_new_simplef(struct frame* fr, const char* message, ...);
#endif // !SIGNAL_ENV_EXCEPTION_H
