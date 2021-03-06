#ifndef BEACON_ENV_TYPE_INTERFACE_VALID_H
#define BEACON_ENV_TYPE_INTERFACE_VALID_H
#include "../../util/string_pool.h"
#include <stdbool.h>
struct interface_;
struct method;
/**
 * 全てのメソッドを巡回して、全てにおいてパラメータ名の重複がないなら true.
 * @param inter
 * @param out
 * @return
 */
bool interface_method_parameter_valid(struct interface_* inter, struct method** out_method, string_view* out_name);

/**
 * インターフェイスの型変数に重複する名前がないなら true.
 * @param inter
 * @param out_name
 * @return
 */
bool interface_type_type_parameter_valid(struct interface_* inter, string_view* out_name);

/**
 * メソッドの型変数に重複するものがないなら true.
 * @param self
 * @param out_method
 * @param out_name
 * @return
 */
bool interface_method_type_parameter_valid(struct interface_* inter, struct method** out_method, string_view* out_name);

#endif