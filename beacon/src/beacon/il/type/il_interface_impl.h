#pragma once
#ifndef BEACON_IL_IL_INTERFACE_H
#define BEACON_IL_IL_INTERFACE_H
#include "../../util/vector.h"
#include "../../util/string_pool.h"
#include "../il_type_interface.h"
struct il_method;
/**
 * インターフェースを表す要素.
 */
typedef struct il_interface {
	string_view namev;
	vector* method_list;
	vector* extends_list;
	vector* type_parameter_list;
	vector* prop_list;
} il_interface;

/**
 * 型をスーパーセットにラップします.
 * @param self
 * @return
 */
il_type* il_type_wrap_interface(il_interface* self);

/**
 * インターフェースを作成します.
 * @param namev
 * @return
 */
il_interface* il_interface_new(string_view namev);

/**
 * プロパティを追加します.
 * @param self
 * @param prop
 */
void il_interface_add_property(il_interface* self, struct il_property* prop);

/**
 * プロパティを追加します.
 * @param self
 * @param method
 */
void il_interface_add_method(il_interface* self, struct il_method* method);

/**
 * インターフェースを出力します.
 * @param self
 * @param depth
 */
void il_interface_dump(il_interface* self, int depth);

/**
 * インターフェースを開放します.
 * @param self
 */
void il_interface_delete(il_interface* self);
#endif // !SIGNAL_IL_IL_INTERFACE_H
