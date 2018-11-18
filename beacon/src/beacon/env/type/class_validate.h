//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file class_validate.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#ifndef BEACON_ENV_TYPE_CLASS_VALIDATE_H
#define BEACON_ENV_TYPE_CLASS_VALIDATE_H
#include "../../util/string_pool.h"
#include <stdbool.h>
struct Class;
struct Method;
struct Property;
struct Field;
struct bc_Constructor;
/**
 * クラスが全てのメソッドを正しく実装しているなら true.
 * インターフェイスを一つも持っていないなら 常にtrue です。
 * @param cls
 * @param out
 * @return
 */
bool IsImplementInterfaceMethodValidClass(struct Class* cls, struct Method** out);
/**
 * クラスが全てのプロパティを正しく実装しているなら true.
 * インターフェイスを一つも持っていないなら 常にtrue です。
 * @param cls
 * @param out
 * @return
 */
bool IsImplementInterfacePropertyValidClass(struct Class* cls, struct Property** out);

/**
 * クラスが親の抽象メソッドを正しく実装しているなら true.
 * 親が具象クラスであるか、このクラスも抽象クラスなら 常にtrue です。
 * @param cls
 * @param out
 * @return
 */
bool IsImplementAbstractClassValidClass(struct Class* cls, struct Method** out);

/**
 * クラスのフィールド名のうち重複するものがないなら true.
 * 親クラスのフィールドとの重複は無視されます。
 * @param cls
 * @param out
 * @return
 */
bool IsValidFieldClass(struct Class* cls, struct Field** out);

/**
 * クラスのプロパティ名のうち重複するものがないなら true.
 * @param self
 * @param out
 * @return
 */
bool IsValidPropertyClass(struct Class* self, struct Property** out);

/**
 * 全てのメソッドを巡回して、全てにおいてパラメータ名の重複がないなら true.
 * @param cls
 * @param out_method
 * @param out_name
 * @return
 */
bool IsMethodParameterValidClass(struct Class* cls, struct Method** out_method, StringView* out_name);

/**
 * 全てのコンストラクタを巡回して、全てにおいてパラメータ名の重複がないなら true.
 * @param self
 * @param out_ctor
 * @param out_name
 * @return
 */
bool IsConstructorParameterValidClass(struct Class* self, struct bc_Constructor** out_ctor, StringView* out_name);

/**
 * クラスの型変数に重複する名前がないなら true.
 * @param self
 * @param out_name
 * @return
 */
bool IsTypeParameterValidClass(struct Class* self, StringView* out_name);

/**
 * メソッドの型変数に重複するものがないなら true.
 * @param self
 * @param out_method
 * @param out_name
 * @return
 */
bool IsMethodTypeParameterValidClass(struct Class* self, struct Method** out_method, StringView* out_name);
#endif