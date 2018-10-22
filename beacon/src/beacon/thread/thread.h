#pragma once
#ifndef BEACON_THREAD_THREAD_H
#define BEACON_THREAD_THREAD_H
//#include "../util/stack.h"
#include <stdbool.h>
#include "../util/vector.h"
struct script_context;
struct frame;
struct CallContext;
/**
 * 並列実行のための構造体です.
 * 現在の呼び出し位置を表すトレースのスタックを含みます。
 */
typedef struct sg_thread {
	Vector* trace_stack;
	bool vm_crush_by_exception;
	bool vm_dump;
	struct frame* frame_ref;
	struct CallContext* cctx;
} sg_thread;

/**
 * メインスレッドを作成します.
 */
void LaunchSGThread();

/**
 * 新しいスレッドを作成します.
 * @return
 */
sg_thread* NewSGThread();

/**
 * 現在のスレッドを返します.
 * @param sctx
 * @return
 */
sg_thread* GetCurrentSGThread(struct script_context* sctx);

/**
 * スレッドに記録された全てのトレースを解放します.
 * @param self
 */
void ClearSGThread(sg_thread* self);

/**
 * スレッドを解放します.
 * @param self
 */
void DeleteSGThread(sg_thread* self);

/**
 * このスレッドが "実行中のVMのルート" を渡します.
 * このメソッドは通常スクリプトの開始時に一度だけ呼び出されます。
 * スレッドからVMを参照できる必要があるので用意されています。
 * ここから参照されるVMはガベージコレクションの対象になります。
 * @param self
 * @param frame_ref 呼び出し側で開放してください.
 */
void SetSGThreadFrameRef(sg_thread* self, struct frame* frame_ref);

/**
 * このスレッドが "実行中のVMのルート" を返します.
 * @param self
 * @return
 */
struct frame* GetSGThreadFrameRef(sg_thread* self);

/**
 * このスレッドからVMを参照出来ないようにします.
 * 通常、このスレッドに設定されたVMを開放したあとに呼び出します。
 * @param self
 */
void ReleaseSGThreadFrameRef(sg_thread* self);

/**
 * メインスレッドを返します.
 * @return
 */
sg_thread* GetMainSGThread();


/**
 * メインスレッドの呼び出しコンテキストを返します.
 * @return
 */
struct CallContext* GetSGThreadCContext();

/**
 * メインスレッドを終了します.
 */
void DestroySGThread();
#endif // SIGNAL_THREAD_THREAD_H
