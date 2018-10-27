#pragma once
#ifndef BEACON_IL_IL_INTERFACE_H
#define BEACON_IL_IL_INTERFACE_H
#include "../../util/vector.h"
#include "../../util/string_pool.h"
#include "../il_type_interface.h"
struct ILMethod;
/**
 * インターフェースを表す要素.
 */
typedef struct ILInterface {
	StringView Name;
	Vector* Methods;
	Vector* Extends;
	Vector* TypeParameters;
	Vector* Properties;
} ILInterface;

/**
 * 型をスーパーセットにラップします.
 * @param self
 * @return
 */
ILType* WrapILInterface(ILInterface* self);

/**
 * インターフェースを作成します.
 * @param namev
 * @return
 */
ILInterface* NewILInterface(StringView namev);

/**
 * プロパティを追加します.
 * @param self
 * @param prop
 */
void AddPropertyILInterface(ILInterface* self, struct ILProperty* prop);

/**
 * プロパティを追加します.
 * @param self
 * @param method
 */
void AddMethodILInterface(ILInterface* self, struct ILMethod* method);

/**
 * インターフェースを開放します.
 * @param self
 */
void DeleteILInterface(ILInterface* self);
#endif // !SIGNAL_IL_IL_INTERFACE_H
