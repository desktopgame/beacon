#ifndef BEACON_IL_IL_CLASS_H
#define BEACON_IL_IL_CLASS_H
#include "../../util/vector.h"
#include "../../util/string_pool.h"
#include "../../env/fqcn_cache.h"
#include "../il_type_interface.h"
#include <stdbool.h>
struct il_field;
struct il_method;
/**
 * クラスを表す要素.
 */
typedef struct il_class {
	string_view namev;
//	fqcn_cache* super;
//	vector* implement_list;
	vector* extend_list;
	vector* field_list;
	vector* sfield_list;
	vector* method_list;
	vector* smethod_list;
	vector* constructor_list;
	vector* type_parameter_list;
	vector* operator_overload_list;
	vector* prop_list;
	vector* sprop_list;
	bool is_abstract;
} il_class;

/**
 * この型をスーパーセットにラップします.
 * @param self
 * @return
 */
il_type* il_type_wrap_class(il_class* self);

/**
 * クラスを表す要素を作成します.
 * @param namev
 * @return
 */
il_class* il_class_new(string_view namev);

/**
 * フィールドを追加します.
 * @param self
 * @param f
 */
void il_class_add_field(il_class* self, struct il_field* f);

/**
 * プロパティを追加します.
 * @param self
 * @param prop
 */
void il_class_add_property(il_class* self, struct il_property* prop);

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
