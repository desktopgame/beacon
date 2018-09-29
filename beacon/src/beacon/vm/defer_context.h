#ifndef BEACON_VM_DEFER_CONTEXT_H
#define BEACON_VM_DEFER_CONTEXT_H
#include "label.h"
#include "../util/vector.h"
/**
 * deferステートメントが実行された時、
 * その時点でのpcと名前束縛を記録しておく構造体です.
 */
typedef struct defer_context {
	label* offset;
	Vector* variable_vec;
} defer_context;

/**
 * 新しい defer_context を作成します.
 * @return
 */
defer_context* defer_context_new();

/**
 * defer_context を解放します.
 * @param self
 */
void defer_context_delete(defer_context* self);
#endif