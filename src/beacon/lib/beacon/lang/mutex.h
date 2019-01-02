#ifndef BEACON_LIB_BEACON_LANG_MUTEX_H
#define BEACON_LIB_BEACON_LANG_MUTEX_H
#include <glib.h>
#include "../../bc_library_impl.h"

/**
 * glibの`GMutex`のラッパーです。
 */
typedef struct bc_Mutex {
        bc_Object Super;
        GMutex Mutex;
        int Stack;
} bc_Mutex;

/**
 * 新しいミューテックスを生成します。
 * @return
 */
bc_Object* bc_NewMutex();

/**
 * beacon::lang::Mutexクラスを初期化します。
 */
void bc_InitMutex();

/**
 * beacon::lang::Mutexクラスを返します。
 * @return
 */
struct bc_Type* bc_GetMutexType();
#endif
