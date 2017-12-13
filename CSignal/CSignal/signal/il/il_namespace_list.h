#ifndef SIGNAL_IL_IL_NAMESPACE_LIST_H
#define SIGNAL_IL_IL_NAMESPACE_LIST_H
#include "il_namespace.h"
/**
 * 名前空間の一覧を表す要素.
 */
typedef struct il_namespace_list {
	il_namespace* namespacez;
	struct il_namespace_list* next;
} il_namespace_list;
/**
 * 名前空間の一覧を表す要素を作成します.
 * @return
 */
il_namespace_list* il_namespace_list_new();
/**
 * 名前空間を一覧に追加.
 * @param self
 * @param namespacez
 */
void il_namespace_list_push(il_namespace_list* self, il_namespace* namespacez);

/**
 * 名前空間の一覧を解放します.
 * @param self
 */
void il_namespace_list_delete(il_namespace_list* self);
#endif // !SIGNAL_IL_IL_NAMESPACE_LIST_H