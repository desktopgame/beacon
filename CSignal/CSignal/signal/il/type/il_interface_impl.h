#pragma once
#ifndef SIGNAL_IL_IL_INTERFACE_H
#define SIGNAL_IL_IL_INTERFACE_H
#include "../../util/vector.h"
#include "../il_type_interface.h"
/**
 * インターフェースを表す要素.
 */
typedef struct il_interface {
	char* name;
	vector* method_list;
} il_interface;

/**
 * 型をスーパーセットにラップします.
 * @param self
 * @return
 */
il_type* il_type_wrap_interface(il_interface* self);

/**
 * インターフェースを作成します.
 * @param name
 * @return
 */
il_interface* il_interface_new(const char* name);

/**
 * インターフェースを出力します.
 * @param self
 */
void il_interface_dump(il_interface* self);

/**
 * インターフェースを開放します.
 * @param self
 */
void il_interface_delete(il_interface* self);
#endif // !SIGNAL_IL_IL_INTERFACE_H
