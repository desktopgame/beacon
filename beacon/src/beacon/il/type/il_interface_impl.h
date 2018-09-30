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
	Vector* method_list;
	Vector* extends_list;
	Vector* type_parameter_list;
	Vector* prop_list;
} il_interface;

/**
 * 型をスーパーセットにラップします.
 * @param self
 * @return
 */
il_type* WrapILInterface(il_interface* self);

/**
 * インターフェースを作成します.
 * @param namev
 * @return
 */
il_interface* NewILInterface(string_view namev);

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
void AddMethodILInterface(il_interface* self, struct il_method* method);

/**
 * インターフェースを開放します.
 * @param self
 */
void DeleteILInterface(il_interface* self);
#endif // !SIGNAL_IL_IL_INTERFACE_H
