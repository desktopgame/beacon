#ifndef BEACON_ENV_TYPE_CLASS_VALIDATE_H
#define BEACON_ENV_TYPE_CLASS_VALIDATE_H
#include "../../util/string_pool.h"
#include <stdbool.h>
struct class_;
struct method;
struct property;
struct field;
struct constructor;
/**
 * クラスが全てのメソッドを正しく実装しているなら true.
 * インターフェイスを一つも持っていないなら 常にtrue です。
 * @param cls
 * @param out
 * @return
 */
bool class_interface_method_implement_valid(struct class_* cls, struct method** out);
/**
 * クラスが全てのプロパティを正しく実装しているなら true.
 * インターフェイスを一つも持っていないなら 常にtrue です。
 * @param cls
 * @param out
 * @return
 */
bool class_interface_property_implement_valid(struct class_* cls, struct property** out);

/**
 * クラスが親の抽象メソッドを正しく実装しているなら true.
 * 親が具象クラスであるか、このクラスも抽象クラスなら 常にtrue です。
 * @param cls
 * @param out
 * @return
 */
bool class_abstract_class_implement_valid(struct class_* cls, struct method** out);

/**
 * クラスのフィールド名のうち重複するものがないなら true.
 * 親クラスのフィールドとの重複は無視されます。
 * @param cls
 * @param out
 * @return
 */
bool class_field_valid(struct class_* cls, struct field** out);

/**
 * クラスのプロパティ名のうち重複するものがないなら true.
 * @param self
 * @param out
 * @return
 */
bool class_property_valid(struct class_* self, struct property** out);

/**
 * 全てのメソッドを巡回して、全てにおいてパラメータ名の重複がないなら true.
 * @param cls
 * @param out_method
 * @param out_name
 * @return
 */
bool class_method_parameter_valid(struct class_* cls, struct method** out_method, string_view* out_name);

/**
 * 全てのコンストラクタを巡回して、全てにおいてパラメータ名の重複がないなら true.
 * @param self
 * @param out_ctor
 * @param out_name
 * @return
 */
bool class_ctor_parameter_valid(struct class_* self, struct constructor** out_ctor, string_view* out_name);

/**
 * クラスの型変数に重複する名前がないなら true.
 * @param self
 * @param out_name
 * @return
 */
bool class_type_type_parameter_valid(struct class_* self, string_view* out_name);

/**
 * メソッドの型変数に重複するものがないなら true.
 * @param self
 * @param out_method
 * @param out_name
 * @return
 */
bool class_method_type_parameter_valid(struct class_* self, struct method** out_method, string_view* out_name);
#endif