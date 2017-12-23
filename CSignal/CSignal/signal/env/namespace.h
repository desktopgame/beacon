#pragma once
#ifndef SIGNAL_ENV_NAMESPACE_H
#define SIGNAL_ENV_NAMESPACE_H
#include "../util/tree_map.h"
#include <stdint.h>
struct class_;
/**
 * 名前空間を表す構造体.
 */
typedef struct namespace_ {
	char* name;
	struct namespace_* parent;
	tree_map* namespace_map;
	tree_map* class_map;
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
 * @param classz
 */
struct class_* namespace_add_class(namespace_* self, struct class_* classz);

/**
 * 指定の名前空間から指定の名前の名前空間を検索します.
 * @param self
 * @param name
 * @return 見つからないなら NULL
 */
namespace_* namespace_get_namespace(namespace_* self, char* name);

/**
 * 全ての名前空間を出力します.
 */
void namespace_dump();
#endif // !SIGNAL_ENV_NAMESPACE_H
