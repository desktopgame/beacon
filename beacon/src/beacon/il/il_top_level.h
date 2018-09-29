#ifndef BEACON_IL_IL_TOP_LEVEL_H
#define BEACON_IL_IL_TOP_LEVEL_H
#include "../util/vector.h"

/**
 * 中間言語ILのトップレベル要素です.
 */
typedef struct il_top_level {
	Vector* import_list;
	Vector* namespace_list;
	Vector* statement_list;
	Vector* function_list;
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
