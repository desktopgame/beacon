#pragma once
#ifndef BEACON_THREAD_THREAD_H
#define BEACON_THREAD_THREAD_H
//#include "../util/stack.h"
#include <stdbool.h>
#include "../util/vector.h"
struct script_context;
struct frame;
struct call_context;
/**
 * 並列実行のための構造体です.
 * 現在の呼び出し位置を表すトレースのスタックを含みます。
 */
typedef struct sg_thread {
	Vector* trace_stack;
	bool vm_crush_by_exception;
	bool vm_dump;
	struct frame* frame_ref;
	struct call_context* cctx;
} sg_thread;

/**
 * メインスレッドを作成します.
 */
void sg_thread_launch();

/**
 * 新しいスレッドを作成します.
 * @return
 */
sg_thread* sg_thread_new();

/**
 * 現在のスレッドを返します.
 * @param sctx
 * @return
 */
sg_thread* sg_thread_current(struct script_context* sctx);

/**
 * スレッドに記録された全てのトレースを解放します.
 * @param self
 */
void sg_thread_clear(sg_thread* self);

/**
 * スレッドを解放します.
 * @param self
 */
void sg_thread_delete(sg_thread* self);

/**
 * このスレッドが "実行中のVMのルート" を渡します.
 * このメソッドは通常スクリプトの開始時に一度だけ呼び出されます。
 * スレッドからVMを参照できる必要があるので用意されています。
 * ここから参照されるVMはガベージコレクションの対象になります。
 * @param self
 * @param frame_ref 呼び出し側で開放してください.
 */
void sg_thread_set_frame_ref(sg_thread* self, struct frame* frame_ref);

/**
 * このスレッドが "実行中のVMのルート" を返します.
 * @param self
 * @return
 */
struct frame* sg_thread_get_frame_ref(sg_thread* self);

/**
 * このスレッドからVMを参照出来ないようにします.
 * 通常、このスレッドに設定されたVMを開放したあとに呼び出します。
 * @param self
 */
void sg_thread_release_frame_ref(sg_thread* self);

/**
 * メインスレッドを返します.
 * @return
 */
sg_thread* sg_thread_main();


/**
 * メインスレッドの呼び出しコンテキストを返します.
 * @return
 */
struct call_context* sg_thread_context();

/**
 * メインスレッドを終了します.
 */
void sg_thread_destroy();
#endif // SIGNAL_THREAD_THREAD_H
