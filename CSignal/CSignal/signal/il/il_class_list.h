#ifndef SIGNAL_IL_IL_CLASS_LIST_H
#define SIGNAL_IL_IL_CLASS_LIST_H
#include "il_class.h"
/**
 * クラスの一覧を表す要素.
 */
typedef struct il_class_list {
	il_class* classz;
	struct il_class_list* next;
} il_class_list;
/**
 * クラスの一覧を表す要素を作成します.
 * @return
 */
il_class_list* il_class_list_new();

/**
 * クラスを一覧に追加します.
 * @param self
 * @param classz
 */
void il_class_list_push(il_class_list* self, il_class* classz);

/**
 * クラスの一覧を解放します.
 * @param self
 */
void il_class_list_delete(il_class_list* self);
#endif // !SIGNAL_IL_IL_CLASS_LIST_H