#ifndef SIGNAL_IL_IL_IMPORT_LIST_H
#define SIGNAL_IL_IL_IMPORT_LIST_H
#include "il_import.h"

/**
 * インポートの一覧を表す要素.
 */
typedef struct il_import_list {
	il_import* import;
	struct il_import_list* next;
} il_import_list;

/**
 * 新しいインポート一覧を作成します.
 * @return 
 */
il_import_list* il_import_list_new();

/**
 * インポートの一覧に引数のインポート宣言を加えます.
 * @param self
 * @param child
 */
void il_import_list_push(il_import_list* self, il_import* child);

/**
 * インポートの一覧を解放します.
 * @param self
 */
void il_import_list_delete(il_import_list* self);
#endif // !SIGNAL_IL_IL_IMPORT_LIST_H