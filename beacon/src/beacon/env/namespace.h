#pragma once
#ifndef BEACON_ENV_NAMESPACE_H
#define BEACON_ENV_NAMESPACE_H
#include "../util/tree_map.h"
#include "../util/string_pool.h"
#include "../util/vector.h"
#include "../util/numeric_map.h"
#include <stdint.h>
struct script_context;
#define TYPE_OBJECT (GetObjectTypeNamespace())
#define TYPE_INT (GetIntTypeNamespace())
#define TYPE_DOUBLE (GetDoubleTypeNamespace())
#define TYPE_CHAR (GetCharTypeNamespace())
#define TYPE_STRING (GetStringTypeNamespace())
#define TYPE_BOOL (GetBoolTypeNamespace())
#define TYPE_VOID (GetVoidTypeNamespace())
#define TYPE_NULL (GetNullTypeNamespace())
#define TYPE_EXCEPTION (GetExceptionTypeNamespace())


#define GENERIC_OBJECT ((GetObjectTypeNamespace()->generic_self))
#define GENERIC_INT ((GetIntTypeNamespace()->generic_self))
#define GENERIC_DOUBLE ((GetDoubleTypeNamespace()->generic_self))
#define GENERIC_CHAR ((GetCharTypeNamespace()->generic_self))
#define GENERIC_STRING ((GetStringTypeNamespace()->generic_self))
#define GENERIC_BOOL ((GetBoolTypeNamespace()->generic_self))
#define GENERIC_VOID ((GetVoidTypeNamespace()->generic_self))
#define GENERIC_NULL ((GetNullTypeNamespace()->generic_self))
#define GENERIC_EXCEPTION ((GetExceptionTypeNamespace()->generic_self))

struct type;
struct class_;
struct interface_;
/**
 * 名前空間を表す構造体.
 */
typedef struct namespace_ {
	StringView namev;
	struct namespace_* parent;
	NumericMap* namespace_map;
	NumericMap* type_map;
	uint32_t ref_count;
} namespace_;

/**
 * 指定の名前でトップレベルに新しい名前空間を定義します.
 * @param namev
 * @return 既に存在するならそれを返します.
 */
namespace_* CreateNamespaceAtRoot(StringView namev);

/**
 * 指定の名前でトップレベルから名前空間を検索します.
 * @param namev
 * @return
 */
namespace_* FindNamespaceFromRoot(StringView namev);

/**
 * コンテキストを指定してトップレベルの名前空間を返します.
 * @param sctx
 * @param namev
 * @return
 */
namespace_* CFindNamespaceFromRoot(struct script_context* sctx, StringView namev);

/**
 * 指定の名前空間に新しい名前空間を定義します.
 * @param self
 * @param namev
 * @return 既に存在するならそれを返します.
 */
namespace_* AddNamespaceNamespace(namespace_* self, StringView namev);

/**
 * この名前空間にクラスを含めます.
 * クラスのカウントは +1 されます。
 * @param self
 * @param type
 */
struct type* AddTypeNamespace(namespace_* self, struct type* type);

/**
 * 指定の名前空間から指定の名前の名前空間を検索します.
 * @param self
 * @param namev
 * @return 見つからないなら NULL
 */
namespace_* FindNamespaceFromNamespace(namespace_* self, StringView namev);

/**
 * 指定の名前空間で指定の名前のタイプを検索します.
 * @param self
 * @param namev
 * @return 見つからないなら NULL
 */
struct type* FindTypeFromNamespace(namespace_* self, StringView namev);

/**
 * 指定の名前空間で指定の名前のクラスを検索します.
 * @param self
 * @param namev
 * @return 見つからないなら NULL
 */
struct class_* FindClassFromNamespace(namespace_* self, StringView namev);

/**
 * 指定の名前空間で指定の名前のインターフェースを検索します.
 * @param self
 * @param namev
 * @return 見つからないなら NULL
 */
struct interface_* FindInterfaceFromNamespace(namespace_* self, StringView namev);

/**
 * beacon 名前空間を返します.
 * @return
 */
namespace_* GetBeaconNamespace();

/**
 * beacon.lang 名前空間を返します.
 * @return
 */
namespace_* GetLangNamespace();

/**
 * beacon.unsafe 名前空間を返します.
 * @return
 */
namespace_* GetUnsafeNamespace();

/**
 * $placeholder 名前空間を返します.
 * @return
 */
namespace_* GetPlaceholderNamespace();

/**
 * 現在のスクリプトコンテキストで object タイプを返します.
 * @return
 */
struct type* GetObjectTypeNamespace();

/**
 * 現在のスクリプトコンテキストで int タイプを返します.
 * @return
 */
struct type* GetIntTypeNamespace();

/**
 * 現在のスクリプトコンテキストで double タイプを返します.
 * @return
 */
struct type* GetDoubleTypeNamespace();

/**
 * 現在のスクリプトコンテキストで char タイプを返します.
 * @return
 */
struct type* GetCharTypeNamespace();

/**
 * 現在のスクリプトコンテキストで string タイプを返します.
 * @return
 */
struct type* GetStringTypeNamespace();

/**
 * 現在のスクリプトコンテキストで bool タイプを返します.
 * @return
 */
struct type* GetBoolTypeNamespace();

/**
 * 現在のスクリプトコンテキストで void タイプを返します.
 * @return
 */
struct type* GetVoidTypeNamespace();

/**
 * 現在のスクリプトコンテキストで null タイプを返します.
 * @return
 */
struct type* GetNullTypeNamespace();

/**
 * beacon::lang::Exception
 * @return
 */
struct type* GetExceptionTypeNamespace();

/**
 * 指定の名前空間のすべての型で unlink を呼び出します.
 * @param self
 */
void UnlinkNamespace(namespace_* self);

/**
 * 名前空間を完全な文字列として返します.
 * @param self
 * @return
 */
StringView NamespaceToString(namespace_* self);

/**
 * 名前空間を開放します.
 * @param self
 */
void DeleteNamespace(namespace_* self);
#endif // !SIGNAL_ENV_NAMESPACE_H
