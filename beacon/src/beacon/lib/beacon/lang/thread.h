#ifndef BEACON_LIB_SIGNAL_LANG_THREAD_H
#define BEACON_LIB_SIGNAL_LANG_THREAD_H
#include "../../../vm/script_thread.h"
#include "../../bc_library_impl.h"

typedef struct bc_Thread {
        bc_ScriptThread* ScriptThread;
} bc_Thread;

/**
 * 新しいスレッドオブジェクトを生成します。
 * @return
 */
struct bc_Object* bc_NewThread(bc_ScriptThread* thread);

/**
 * beacon::lang::Threadクラスを初期化します.
 */
void bc_InitThread();

/**
 * beacon::lang::Threadクラスを返します.
 * @return
 */
struct bc_Type* bc_GetThreadType();
#endif