#ifndef BEACON_LIB_BEACON_LANG_CONDITION_VARIABLE_H
#define BEACON_LIB_BEACON_LANG_CONDITION_VARIABLE_H
#include <glib.h>
#include "../../bc_library_impl.h"

typedef struct bc_ConditionVariable {
        bc_Object Super;
        GCond Cond;
} bc_ConditionVariable;

/**
 * 新しい条件変数を生成します。
 * @return
 */
bc_Object* bc_NewConditionVariable();

/**
 * beacon::lang::ConditionVariableクラスを初期化します。
 */
void bc_InitConditionVariable();

/**
 * beacon::lang::ConditionVariableクラスを返します。
 * @return
 */
struct bc_Type* bc_GetConditionVariableType();
#endif