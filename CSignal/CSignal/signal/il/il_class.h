#ifndef SIGNAL_IL_IL_CLASS_H
#define SIGNAL_IL_IL_CLASS_H
#include "il_type.h"
#include "../util/vector.h"
#include "../env/fqcn_cache.h"
/**
 * クラスを表す要素.
 */
typedef struct il_class {
	char* name;
	fqcn_cache* super;
	vector* field_list;
	vector* method_list;
	vector* constructor_list;
} il_class;
/**
 * クラスを表す要素を作成します.
 * @param name
 * @return
 */
il_class* il_class_new(const char* name);

/**
 * クラスとそのメンバーの一覧を出力します.
 * @param self
 * @param depth
 */
void il_class_dump(il_class* self, int depth);

/**
 * クラスと含まれるメンバー宣言の一覧を解放します.
 * @param self
 */
void il_class_delete(il_class* self);
#endif // !SIGNAL_IL_IL_CLASS_H