#pragma once
#ifndef SIGNAL_THREAD_THREAD_H
#define SIGNAL_THREAD_THREAD_H
#include "../util/stack.h"


/**
 * 並列実行のための構造体です.
 * 現在の呼び出し位置を表すトレースのスタックを含みます。
 */
typedef struct sg_thread {
	stack* trace_stack;
} sg_thread;

void sg_thread_launch();

sg_thread* sg_thread_new();

sg_thread* sg_thread_current();

void sg_thread_clear(sg_thread* self);

void sg_thread_delete(sg_thread* self);

sg_thread* sg_thread_main();

void sg_thread_destroy();
#endif // SIGNAL_THREAD_THREAD_H
