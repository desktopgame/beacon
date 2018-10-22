#pragma once
#ifndef BEACON_ENV_EXCEPTION_H
#define BEACON_ENV_EXCEPTION_H
#include <stdarg.h>

struct object;
struct Frame;

/**
 * signal::lang::Exception 型の例外を作成します.
 * @param fr
 * @param message
 * @return
 */
struct object* NewSimpleException(struct Frame* fr, const char* message);
/**
 * signal::lang::Exception 型の例外を作成します.
 * フォーマット付きです.
 * @param fr
 * @param message
 * @param ...
 * @return
 */
struct object* NewSimplefException(struct Frame* fr, const char* message, ...);
#endif // !SIGNAL_ENV_EXCEPTION_H
