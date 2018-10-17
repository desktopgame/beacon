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
	StringView namev;
//	fqcn_cache* super;
//	Vector* implement_list;
	Vector* extend_list;
	Vector* field_list;
	Vector* sfield_list;
	Vector* method_list;
	Vector* smethod_list;
	Vector* constructor_list;
	Vector* GetParameterListType;
	Vector* operator_overload_list;
	Vector* prop_list;
	Vector* sprop_list;
	bool is_abstract;
} il_class;

/**
 * この型をスーパーセットにラップします.
 * @param self
 * @return
 */
il_type* WrapILClass(il_class* self);

/**
 * クラスを表す要素を作成します.
 * @param namev
 * @return
 */
il_class* NewILClass(StringView namev);

/**
 * フィールドを追加します.
 * @param self
 * @param f
 */
void AddFieldILClass(il_class* self, struct il_field* f);

/**
 * プロパティを追加します.
 * @param self
 * @param prop
 */
void AddPropertyILClass(il_class* self, struct il_property* prop);

/**
 * メソッドを追加します.
 * @param self
 * @param m
 */
void AddMethodILClass(il_class* self, struct il_method* m);

/**
 * クラスと含まれるメンバー宣言の一覧を解放します.
 * @param self
 */
void DeleteILClass(il_class* self);
#endif // !SIGNAL_IL_IL_CLASS_H
