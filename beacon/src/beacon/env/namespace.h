#pragma once
#ifndef BEACON_ENV_NAMESPACE_H
#define BEACON_ENV_NAMESPACE_H
#include "../util/tree_map.h"
#include "../util/string_pool.h"
#include "../util/vector.h"
#include "../util/numeric_map.h"
#include <stdint.h>
#define TYPE_OBJECT (namespace_object_type())
#define TYPE_INT (namespace_int_type())
#define TYPE_DOUBLE (namespace_double_type())
#define TYPE_CHAR (namespace_char_type())
#define TYPE_STRING (namespace_string_type())
#define TYPE_BOOL (namespace_bool_type())
#define TYPE_VOID (namespace_void_type())
#define TYPE_NULL (namespace_null_type())
#define TYPE_EXCEPTION (namespace_exception_type())


#define GENERIC_OBJECT ((namespace_object_type()->generic_self))
#define GENERIC_INT ((namespace_int_type()->generic_self))
#define GENERIC_DOUBLE ((namespace_double_type()->generic_self))
#define GENERIC_CHAR ((namespace_char_type()->generic_self))
#define GENERIC_STRING ((namespace_string_type()->generic_self))
#define GENERIC_BOOL ((namespace_bool_type()->generic_self))
#define GENERIC_VOID ((namespace_void_type()->generic_self))
#define GENERIC_NULL ((namespace_null_type()->generic_self))
#define GENERIC_EXCEPTION ((namespace_exception_type()->generic_self))

struct type;
struct class_;
struct interface_;
/**
 * 名前空間を表す構造体.
 */
typedef struct namespace_ {
	string_view namev;
	struct namespace_* parent;
	numeric_map* namespace_map;
	numeric_map* type_map;
	uint32_t ref_count;
} namespace_;

/**
 * 指定の名前でトップレベルに新しい名前空間を定義します.
 * @param namev
 * @return 既に存在するならそれを返します.
 */
namespace_* namespace_create_at_root(string_view namev);

/**
 * 指定の名前でトップレベルから名前空間を検索します.
 * @param namev
 * @return
 */
namespace_* namespace_get_at_root(string_view namev);

/**
 * 指定の名前空間に新しい名前空間を定義します.
 * @param self
 * @param namev
 * @return 既に存在するならそれを返します.
 */
namespace_* namespace_add_namespace(namespace_* self, string_view namev);

/**
 * この名前空間にクラスを含めます.
 * クラスのカウントは +1 されます。
 * @param self
 * @param type
 */
struct type* namespace_add_type(namespace_* self, struct type* type);

/**
 * 指定の名前空間から指定の名前の名前空間を検索します.
 * @param self
 * @param namev
 * @return 見つからないなら NULL
 */
namespace_* namespace_get_namespace(namespace_* self, string_view namev);

/**
 * 指定の名前空間で指定の名前のタイプを検索します.
 * @param self
 * @param namev
 * @return 見つからないなら NULL
 */
struct type* namespace_get_type(namespace_* self, string_view namev);

/**
 * 指定の名前空間で指定の名前のクラスを検索します.
 * @param self
 * @param namev
 * @return 見つからないなら NULL
 */
struct class_* namespace_get_class(namespace_* self, string_view namev);

/**
 * 指定の名前空間で指定の名前のインターフェースを検索します.
 * @param self
 * @param namev
 * @return 見つからないなら NULL
 */
struct interface_* namespace_get_interface(namespace_* self, string_view namev);

/**
 * beacon 名前空間を返します.
 * @return
 */
namespace_* namespace_beacon();

/**
 * beacon.lang 名前空間を返します.
 * @return
 */
namespace_* namespace_lang();

/**
 * beacon.unsafe 名前空間を返します.
 * @return
 */
namespace_* namespace_unsafe();

/**
 * $placeholder 名前空間を返します.
 * @return
 */
namespace_* namespace_placeholder();

/**
 * 現在のスクリプトコンテキストで object タイプを返します.
 * @return
 */
struct type* namespace_object_type();

/**
 * 現在のスクリプトコンテキストで int タイプを返します.
 * @return
 */
struct type* namespace_int_type();

/**
 * 現在のスクリプトコンテキストで double タイプを返します.
 * @return
 */
struct type* namespace_double_type();

/**
 * 現在のスクリプトコンテキストで char タイプを返します.
 * @return
 */
struct type* namespace_char_type();

/**
 * 現在のスクリプトコンテキストで string タイプを返します.
 * @return
 */
struct type* namespace_string_type();

/**
 * 現在のスクリプトコンテキストで bool タイプを返します.
 * @return
 */
struct type* namespace_bool_type();

/**
 * 現在のスクリプトコンテキストで void タイプを返します.
 * @return
 */
struct type* namespace_void_type();

/**
 * 現在のスクリプトコンテキストで null タイプを返します.
 * @return
 */
struct type* namespace_null_type();

/**
 * beacon::lang::Exception
 * @return
 */
struct type* namespace_exception_type();

/**
 * 指定の名前空間のすべての型で unlink を呼び出します.
 * @param self
 */
void namespace_unlink(namespace_* self);

/**
 * 名前空間を完全な文字列として返します.
 * @param self
 * @return
 */
string_view namespace_tostr(namespace_* self);

/**
 * 名前空間を開放します.
 * @param self
 */
void namespace_delete(namespace_* self);
#endif // !SIGNAL_ENV_NAMESPACE_H
