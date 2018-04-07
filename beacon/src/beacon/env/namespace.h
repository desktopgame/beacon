#pragma once
#ifndef BEACON_ENV_NAMESPACE_H
#define BEACON_ENV_NAMESPACE_H
#include "../util/tree_map.h"
#include <stdint.h>
#define CL_OBJECT (namespace_object_class())
#define CL_INT (namespace_int_class())
#define CL_DOUBLE (namespace_double_class())
#define CL_CHAR (namespace_char_class())
#define CL_STRING (namespace_string_class())
#define CL_BOOL (namespace_bool_class())
#define CL_VOID (namespace_void_class())
#define CL_NULL (namespace_null_class())


#define GEN_OBJECT (generic_type_new(namespace_object_class()))
#define GEN_INT (generic_type_new(namespace_int_class()))
#define GEN_DOUBLE (generic_type_new(namespace_double_class()))
#define GEN_CHAR (generic_type_new(namespace_char_class()))
#define GEN_STRING (generic_type_new(namespace_string_class()))
#define GEN_BOOL (generic_type_new(namespace_bool_class()))
#define GEN_VOID (generic_type_new(namespace_void_class()))
#define GEN_NULL (generic_type_new(namespace_null_class()))

struct type;
struct class_;
struct interface_;
/**
 * 名前空間を表す構造体.
 */
typedef struct namespace_ {
	char* name;
	struct namespace_* parent;
	tree_map* namespace_map;
	tree_map* type_map;
	uint32_t ref_count;
} namespace_;

/**
 * 指定の名前でトップレベルに新しい名前空間を定義します.
 * @param name
 * @return 既に存在するならそれを返します.
 */
namespace_* namespace_create_at_root(char* name);

/**
 * 指定の名前でトップレベルから名前空間を検索します.
 * @param name
 * @return
 */
namespace_* namespace_get_at_root(char* name);

/**
 * 指定の名前空間に新しい名前空間を定義します.
 * @param self
 * @param name
 * @return 既に存在するならそれを返します.
 */
namespace_* namespace_add_namespace(namespace_* self, char* name);

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
 * @param name
 * @return 見つからないなら NULL
 */
namespace_* namespace_get_namespace(namespace_* self, const char* name);

/**
 * 指定の名前空間で指定の名前のタイプを検索します.
 * @param self
 * @param name
 * @return 見つからないなら NULL
 */
struct type* namespace_get_type(namespace_* self, const char* name);

/**
 * 指定の名前空間で指定の名前のクラスを検索します.
 * @param self
 * @param name
 * @return 見つからないなら NULL
 */
struct class_* namespace_get_class(namespace_* self, const char* name);

/**
 * 指定の名前空間で指定の名前のインターフェースを検索します.
 * @param self
 * @param name
 * @return 見つからないなら NULL
 */
struct interface_* namespace_get_interface(namespace_* self, const char* name);

/**
 * signal 名前空間を返します.
 * @return
 */
namespace_* namespace_signal();

/**
 * signal.lang 名前空間を返します.
 * @return
 */
namespace_* namespace_lang();

/**
 * 現在のスクリプトコンテキストで int クラスを返します.
 * @return
 */
struct type* namespace_object_class();

/**
 * 現在のスクリプトコンテキストで int クラスを返します.
 * @return
 */
struct type* namespace_int_class();

/**
 * 現在のスクリプトコンテキストで double クラスを返します.
 * @return
 */
struct type* namespace_double_class();

/**
 * 現在のスクリプトコンテキストで char クラスを返します.
 * @return
 */
struct type* namespace_char_class();

/**
 * 現在のスクリプトコンテキストで string クラスを返します.
 * @return
 */
struct type* namespace_string_class();

/**
 * 現在のスクリプトコンテキストで bool クラスを返します.
 * @return
 */
struct type* namespace_bool_class();

/**
 * 現在のスクリプトコンテキストで void クラスを返します.
 * @return
 */
struct type* namespace_void_class();

/**
 * 現在のスクリプトコンテキストで null クラスを返します.
 * @return
 */
struct type* namespace_null_class();

/**
 * 全ての名前空間を出力します.
 */
void namespace_dump();

/**
 * 指定の名前空間のすべての型で unlink を呼び出します.
 * @param self
 */
void namespace_unlink(namespace_* self);

/**
 * 名前空間を開放します.
 * @param self
 */
void namespace_delete(namespace_* self);
#endif // !SIGNAL_ENV_NAMESPACE_H
