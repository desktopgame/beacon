#ifndef BEACON_VM_DEFER_CONTEXT_H
#define BEACON_VM_DEFER_CONTEXT_H
#include "label.h"
#include "../util/vector.h"
/**
 * deferステートメントが実行された時、
 * その時点でのpcと名前束縛を記録しておく構造体です.
 */
typedef struct DeferContext {
	Label* Offset;
	Vector* VariableTable;
} DeferContext;

/**
 * 新しい DeferContext を作成します.
 * @return
 */
DeferContext* NewDeferContext();

/**
 * DeferContext を解放します.
 * @param self
 */
void DeleteDeferContext(DeferContext* self);
#endif