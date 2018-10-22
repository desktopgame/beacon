#pragma once
#ifndef BEACON_THREAD_THREAD_H
#define BEACON_THREAD_THREAD_H
//#include "../util/stack.h"
#include <stdbool.h>
#include "../util/vector.h"
struct script_context;
struct Frame;
struct CallContext;
/**
 * 並列実行のための構造体です.
 * 現在の呼び出し位置を表すトレースのスタックを含みます。
 */
typedef struct ScriptThread {
	Vector* TraceStack;
	bool IsVMCrushByException;
	bool IsVMDump;
	struct Frame* FrameRef;
	struct CallContext* CCtx;
} ScriptThread;

/**
 * メインスレッドを作成します.
 */
void LaunchSGThread();

/**
 * 新しいスレッドを作成します.
 * @return
 */
ScriptThread* NewSGThread();

/**
 * 現在のスレッドを返します.
 * @param sctx
 * @return
 */
ScriptThread* GetCurrentSGThread(struct script_context* sctx);

/**
 * スレッドに記録された全てのトレースを解放します.
 * @param self
 */
void ClearSGThread(ScriptThread* self);

/**
 * スレッドを解放します.
 * @param self
 */
void DeleteSGThread(ScriptThread* self);

/**
 * このスレッドが "実行中のVMのルート" を渡します.
 * このメソッドは通常スクリプトの開始時に一度だけ呼び出されます。
 * スレッドからVMを参照できる必要があるので用意されています。
 * ここから参照されるVMはガベージコレクションの対象になります。
 * @param self
 * @param frame_ref 呼び出し側で開放してください.
 */
void SetSGThreadFrameRef(ScriptThread* self, struct Frame* frame_ref);

/**
 * このスレッドが "実行中のVMのルート" を返します.
 * @param self
 * @return
 */
struct Frame* GetSGThreadFrameRef(ScriptThread* self);

/**
 * このスレッドからVMを参照出来ないようにします.
 * 通常、このスレッドに設定されたVMを開放したあとに呼び出します。
 * @param self
 */
void ReleaseSGThreadFrameRef(ScriptThread* self);

/**
 * メインスレッドを返します.
 * @return
 */
ScriptThread* GetMainSGThread();


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
