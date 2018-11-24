// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_interface_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_IL_IL_INTERFACE_H
#define BEACON_IL_IL_INTERFACE_H
#include "../../util/string_pool.h"
#include "../../util/vector.h"
#include "../il_type_interface.h"
struct bc_ILMethod;
/**
 * インターフェースを表す要素.
 */
typedef struct bc_ILInterface {
        bc_StringView Name;
        bc_Vector* Methods;
        bc_Vector* Extends;
        bc_Vector* TypeParameters;
        bc_Vector* Properties;
} bc_ILInterface;

/**
 * 型をスーパーセットにラップします.
 * @param self
 * @return
 */
bc_ILType* bc_WrapILInterface(bc_ILInterface* self);

/**
 * インターフェースを作成します.
 * @param namev
 * @return
 */
bc_ILInterface* bc_NewILInterface(bc_StringView namev);

/**
 * プロパティを追加します.
 * @param self
 * @param prop
 */
void bc_AddPropertyILInterface(bc_ILInterface* self,
                               struct bc_ILProperty* prop);

/**
 * プロパティを追加します.
 * @param self
 * @param method
 */
void bc_AddMethodILInterface(bc_ILInterface* self, struct bc_ILMethod* method);

/**
 * インターフェースを開放します.
 * @param self
 */
void bc_DeleteILInterface(bc_ILInterface* self);
#endif  // !SIGNAL_IL_IL_INTERFACE_H
