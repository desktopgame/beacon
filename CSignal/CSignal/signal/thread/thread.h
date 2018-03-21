#pragma once
#ifndef SIGNAL_THREAD_THREAD_H
#define SIGNAL_THREAD_THREAD_H
//#include "../util/stack.h"
#include "../util/vector.h"

struct vm;
/**
 * 並列実行のための構造体です.
 * 現在の呼び出し位置を表すトレースのスタックを含みます。
 */
typedef struct sg_thread {
	vector* trace_stack;
	struct vm* vmRef;
} sg_thread;

void sg_thread_launch();

sg_thread* sg_thread_new();

sg_thread* sg_thread_current();

void sg_thread_clear(sg_thread* self);

void sg_thread_delete(sg_thread* self);

/**
 * このスレッドが "実行中のVMのルート" を渡します.
 * このメソッドは通常スクリプトの開始時に一度だけ呼び出されます。
 * スレッドからVMを参照できる必要があるので用意されています。
 * ここから参照されるVMはガベージコレクションの対象になります。
 * @param self
 * @param vmRef 呼び出し側で開放してください.
 */
void sg_thread_set_vm_ref(sg_thread* self, struct vm* vmRef);

/**
 * このスレッドが "実行中のVMのルート" を返します.
 * @param self
 * @return
 */
struct vm* sg_thread_get_vm_ref(sg_thread* self);

/**
 * このスレッドからVMを参照出来ないようにします.
 * 通常、このスレッドに設定されたVMを開放したあとに呼び出します。
 * @param self
 */
void sg_thread_release_vm_ref(sg_thread* self);

sg_thread* sg_thread_main();

void sg_thread_destroy();
#endif // SIGNAL_THREAD_THREAD_H
