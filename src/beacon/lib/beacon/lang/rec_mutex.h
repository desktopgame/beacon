#ifndef BEACON_LIB_BEACON_LANG_REC_MUTEX_H
#define BEACON_LIB_BEACON_LANG_REC_MUTEX_H
#include <glib.h>
#include "../../bc_library_impl.h"

/**
 * glibの`GRecMutex`のラッパーです。
 */
typedef struct bc_RecMutex {
        bc_Object Super;
        GRecMutex Mutex;
        int Stack;
} bc_RecMutex;

/**
 * 新しいミューテックスを生成します。
 * @return
 */
bc_Object* bc_NewRecMutex();

/**
 * beacon::lang::RecMutexクラスを初期化します。
 */
void bc_InitRecMutex();

/**
 * beacon::lang::RecMutexクラスを返します。
 * @return
 */
struct bc_Type* bc_GetRecMutexType();
#endif