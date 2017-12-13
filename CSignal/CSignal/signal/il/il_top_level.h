#ifndef SIGNAL_IL_IL_TOP_LEVEL_H
#define SIGNAL_IL_IL_TOP_LEVEL_H
#include "il_import_list.h"
#include "il_namespace_list.h"

/**
 * 中間言語ILのトップレベル要素です.
 */
typedef struct il_top_level {
	il_import_list* import_list;
} il_top_level;
/**
 * トップレベルの要素を作成します.
 * @return
 */
il_top_level* il_top_level_new();

/**
 * この要素と付随する全てを解放します.
 * @param self
 */
void il_top_level_delete(il_top_level* self);
#endif // !SIGNAL_IL_IL_TOP_LEVEL_H