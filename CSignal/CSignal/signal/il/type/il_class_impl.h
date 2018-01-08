#ifndef SIGNAL_IL_IL_CLASS_H
#define SIGNAL_IL_IL_CLASS_H
#include "../../util/vector.h"
#include "../../env/fqcn_cache.h"
#include "../il_type_interface.h"
struct il_field;
struct il_method;
/**
 * クラスを表す要素.
 */
typedef struct il_class {
	char* name;
	fqcn_cache* super;
	vector* field_list;
	vector* sfield_list;
	vector* method_list;
	vector* smethod_list;
	vector* constructor_list;
} il_class;

/**
 * この型をスーパーセットにラップします.
 * @param self
 * @return
 */
il_type* il_type_wrap_class(il_class* self);

/**
 * クラスを表す要素を作成します.
 * @param name
 * @return
 */
il_class* il_class_new(const char* name);

/**
 * フィールドを追加します.
 * @param self
 * @param f
 */
void il_class_add_field(il_class* self, struct il_field* f);

/**
 * メソッドを追加します.
 * @param self
 * @param m
 */
void il_class_add_method(il_class* self, struct il_method* m);

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