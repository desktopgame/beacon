#pragma once
#ifndef SIGNAL_ENV_CLASS_H
#define SIGNAL_ENV_CLASS_H
#include "namespace.h"
#include "class_type.h"
#include "class_state.h"
#include "native_method_ref.h"
#include "../vm/enviroment.h"
#include "../util/vector.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
//struct field_list;
//struct method_list;

/**
 * クラスを表す構造体です.
 */
typedef struct class_ {
	char* name;
	namespace_* location;
	struct class_* super_class;
	vector* field_list;
	vector* method_list;
	vector* constructor_list;
	class_type type;
	class_state state;
	uint32_t ref_count;
	tree_map* native_method_ref_map;
	//名前空間を無視してフラットにアクセスするための添え字
	int absoluteIndex;
} class_;

/**
 * 新しいクラスを作成します.
 * 呼び出し側で対応する名前空間を紐づけてください。
 * @param name これは呼び出し側で開放してください。
 * @param type
 * @return
 */
class_* class_new(const char* name, class_type type);

/**
 * クラスを出力します.
 * @param self
 * @param depth
 */
void class_dump(class_* self, int depth);

/**
 * 指定の名前に対応するネイティブ関数を登録します.s
 * @param self
 * @param name
 * @param impl
 */
void class_define_native_method(class_* self, const char* name, native_impl impl);

/**
 * 指定の名前を持つフィールドを返します.
 * @param self
 * @param name
 * @return 無ければ NULL
 */
struct field* class_find_field(class_* self, const char* name);

/**
 * 指定の名前/仮引数を持つメソッドの一覧を返します.
 * @param self
 * @param name
 * @param count
 * @param ...
 * @return 無ければ空
 *         呼び出し側で開放してください。
 */
vector* class_find_method(class_* self, const char* name, int count, ...);

/**
 * 引数が0個のメソッドを検索します.
 * @param self
 * @param name
 * @return
 */
vector* class_find_method0(class_* self, const char* name);

/**
 * 引数が1個のメソッドを検索します.
 * @param self
 * @param name
 * @param type1
 * @return
 */
vector* class_find_method1(class_* self, const char* name, class_* type1);

/**
 * vectorで可変長引数を表現する版の実装.
 * こちらでは全ての要素に il_argument* が入っている必要があります。
 * @param self
 * @param name
 * @param args 呼び出し側で開放してください.
 * @param env
 * @return 無ければ空
 *         呼び出し側で開放してください。
 */
vector* class_find_methodv(class_* self, const char* name, vector* args, enviroment* env);

/**
 * もっとも一致するメソッドを返します.
 * @param self
 * @param name
 * @param env
 * @param args
 * @param outIndex メソッドへのインデックス
 * @return
 */
struct method* class_find_methodvf(class_* self, const char* name, vector* args, enviroment* env, int* outIndex);

/**
 * このクラスの中で有効なメソッドへのインデックスを、
 * スーパークラスも加味したインデックスへ変換します.
 * @param self
 * @param index selfのメソッド一覧の中で有効なインデックス
 * @return
 */
int class_method_index_resolve(class_* self, int index);

/**
 * スーパークラスも加味したメソッドのインデックスから、
 * 適切なクラスのメソッドを返します.
 * @param self
 * @param index
 * @return
 */
struct method* class_method_by_index(class_* self, int index);

/**
 * このクラスからルートまでを辿って、
 * 全てのメソッドの数を返します.
 * @param self
 * @return
 */
int class_method_countall(class_* self);

/**
 * このクラスの中で有効なフィールドへのインデックスを
 * スーパークラスも加味したインデックスへ変換します.
 * @param self
 * @param index
 * @return
 */
int class_field_index_resolve(class_* self, int index);

/**
 * スーパークラスも加味したフィールドのインデックスから、
 * 適切なクラスのメソッドを返します.
 * @param self
 * @param index
 * @return
 */
struct field* class_field_by_index(class_* self, int index);

/**
 * このクラスからルートまでを辿って、
 * 全てのフィールドの数を返します.
 * @param self
 * @return
 */
int class_field_countall(class_* self);

/**
 * self を other の型に変換出来るなら true.
 * 例えば、クラスAとそれを継承したクラスBがあるとき、
 * class_castable(B.class, A.class) は true です。
 * @param self
 * @param other
 * @return
 */
bool class_castable(class_* self, class_* other);

/**
 * self と other の距離を返します.
 * どれだけ近しい継承関係かを測れます。
 * @param self
 * @param other
 * @return 同じクラスなら 0 
 *         継承関係が異なるなら -1
 */
int class_distance(class_* self, class_* other);

/**
 * 全てのメンバーがこのクラスを参照できるようにします.
 * @param self
 */
void class_linkall(class_* self);

/**
 * このクラスを開放します.
 * ただし先にこのクラスを参照するサブクラスを開放する必要があります。
 * @param self
 */
void class_delete(class_* self);
#endif // !SIGNAL_ENV_CLASS_H
