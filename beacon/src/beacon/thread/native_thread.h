#ifndef BEACON_THREAD_NATIVE_THREAD_H
#define BEACON_THREAD_NATIVE_THREAD_H


#if __APPLE__
	#include <pthread.h>
	#include <unistd.h>
	typedef void* ThreadStartArgument;
	#define NativeMutex pthread_mutex_t
	typedef void* (*Runnable)(ThreadStartArgument a);
	#define USE_PTHREAD
#elif defined(_WIN32) || defined(_WIN64)
	#include <Windows.h>
	typedef void* ThreadStartArgument;
	typedef int NativeMutex;
	typedef void(*Runnable)(ThreadStartArgument a);
	#define USE_WINTHREAD
#else
	"unsupported your operating system."
#endif

/**
 * OSに組み込まれたスレッド機能を使用するためのラッパーです。
 * この構造体は Mac/pthread, Windows/Thread の両方で動作するように定義されています。
 */
typedef struct NativeThread {
	#if defined(USE_PTHREAD)
	pthread_t t;
	#elif defined(USE_WINTHREAD)

	#endif
	Runnable Runnable;
	ThreadStartArgument Arg;
	int Index;
} NativeThread;

/**
 * NativeThreadシステムを初期化します。
 */
void InitNativeThread();

/**
 * 新しいスレッドのための領域を確保します。
 * @param runnable
 * @param arg
 * @return
 */
NativeThread* AllocNativeThread(Runnable runnable, ThreadStartArgument arg);

/**
 * 新しいスレッドを作成して開始します。
 * 必ず DetachNativeThread によって終了する必要があります。
 * @param runnable
 * @param arg
 * @param outNativeThread
 * @return エラーコード
 */
int StartNativeThread(Runnable runnable, ThreadStartArgument arg, NativeThread** outNativeThread);

/**
 * 指定のミューテックスを初期化します。
 * @param mtx
 */
void InitNativeMutex(NativeMutex * mtx);

/**
 * 現在のコンテキストでモニターをロックします。
 * 他のスレッドは実行中のコンテキストの直前で待機します。
 * @param mtx
 */
void NativeMutexEnter(NativeMutex * mtx);

/**
 * ロックを解放します。
 * 他のスレッドは実行中のコンテキストを開始できます。
 * @param mtx
 */
void NativeMutexExit(NativeMutex * mtx);

/**
 * ミューテックスを解放します。
 * @param mtx
 */
void DestroyNativeMutex(NativeMutex * mtx);

/**
 * 実行中のスレッドで指定の秒数だけ待機します。
 * @param seconds
 * @return 正常に完了したなら 0 を返す
 */
unsigned int NativeSleep(unsigned int seconds);

/**
 * スレッドが終了するまで現在のコンテキストで待機します。
 * @param self
 */
void JoinNativeThread(NativeThread* self);

/**
 * スレッドと関連するリソースを全て解放します。
 * @param self
 */
void DetachNativeThread(NativeThread** self);

/**
 * 実行中のスレッドのうち、指定位置のスレッドを返します。
 * デタッチされたスレッドは取得できません。
 * @param index
 * @return
 */
NativeThread* GetNativeThreadAt(int index);

/**
 * 実行中のスレッドの数を返します。
 * @return
 */
int GetNativeThreadCount();

/**
 * NativeThreadシステムを終了します。
 */
void DestroyNativeThread();
#endif