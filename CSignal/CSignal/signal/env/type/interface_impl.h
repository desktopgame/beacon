#pragma once
#ifndef SIGNAL_ENV_TYPE_IINTERFACE_H
#define SIGNAL_ENV_TYPE_IINTERFACE_H
#include "../type_interface.h"
#include "../namespace.h"
#include "../vtable.h"
#include "../../util/vector.h"
#include "../../il/il_load_cache.h"
struct method;
struct enviroment;
//struct type;
/**
 * インターフェースを表す構造体.
 */
typedef struct interface_ {
	char* name;
	vector* impl_list;
	vector* method_list;
	namespace_* location;
	vtable* vt;
} interface_;

/**
 * インターフェイスをスーパーセットにラップします.
 * @param self
 * @return
 */
type* type_wrap_interface(interface_* self);

/** 
 * インターフェイスを作成します.
 * @param name
 * @return
 */
interface_* interface_new(const char* name);

/**
 * インターフェイスにメソッドを追加します.
 * @param self
 * @param m
 */
void interface_add_method(interface_* self, struct method* m);

/**
 * インターフェイスからメソッドを検索します.
 * @param self
 * @param name
 * @param args
 * @param env
 * @param cache
 * @param outIndex
 * @return
 */
struct method* interface_find_method(interface_* self, const char * name, vector * args, struct enviroment * env, il_load_cache* cache, int * outIndex);

/**
 * インターフェイスをダンプします.
 * @param self
 * @param depth
 */
void interface_dump(interface_* self, int depth);

/**
 * メソッドの一覧から vtable を作成します.
 * @param self
 */
void interface_create_vtable(interface_* self);

/**
 * 型情報を残してメソッドやフィールドなどのみを開放します.
 * @param self
 */
void interface_unlink(interface_* self);

/**
 * インターフェイスを開放します.
 * @param self
 */
void interface_delete(interface_* self);
#endif // !SIGNAL_ENV_TYPE_IINTERFACE_H
