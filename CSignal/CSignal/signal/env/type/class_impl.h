#pragma once
#ifndef SIGNAL_ENV_CLASS_H
#define SIGNAL_ENV_CLASS_H
#include "../namespace.h"
#include "../class_state.h"
#include "../native_method_ref.h"
#include "../vtable.h"
#include "../type_interface.h"
#include "../../vm/enviroment.h"
#include "../../util/vector.h"
#include "../access_domain.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
//struct field_list;
//struct method_list;
struct object;
struct field;
struct method;
struct constructor;
/**
 * クラスを表す構造体です.
 */
typedef struct class_ {
	type* parent;
	char* name;
	namespace_* location;
	struct class_* super_class;
	vector* impl_list;
	vector* field_list;
	vector* sfield_list;
	vector* method_list;
	vector* smethod_list;
	vector* constructor_list;
	//class_type type;
	class_state state;
	uint32_t ref_count;
	tree_map* native_method_ref_map;
	//vector* static_fieldval_vec;
	vtable* vt;
	int classIndex;
} class_;

/**
 * クラスをスーパーセットにラップします.
 * @param self
 * @return
 */
type* type_wrap_class(class_* self);

/**
 * 新しいクラスを作成します.
 * 呼び出し側で対応する名前空間を紐づけてください。
 * @param name これは呼び出し側で開放してください。
 * @return
 */
class_* class_new(const char* name);

/**
 * 事前に読みこまれる必要があるクラスを作成します.
 * @param name
 */
class_* class_new_preload(const char* name);

/**
 * 指定のオブジェクトにこのクラスのフィールドを表す
 * オブジェクトの一覧を追加します。
 * この関数は親クラスから順番に呼び出してください。
 * 以下の副作用をもたらします。
 * - o->classz は self で上書きされます。
 * - o->vptr は self->vt で上書きされます。
 * @param self
 * @param o
 */
void class_alloc_fields(class_* self, struct object* o);

/**
 * 指定のオブジェクトに追加されたフィールドの一覧を開放します.
 * このメソッドは子クラスから順番に呼び出してください。
 * @param self
 * @param o
 */
void class_free_fields(class_* self, struct object* o);

/**
 * このクラスにフィールドを追加します.
 * @param self
 * @param f
 */
void class_add_field(class_* self, struct field* f);

/**
 * このクラスにメソッドを追加します.
 * @param self
 * @param m
 */
void class_add_method(class_* self, struct method* m);

/**
 * このクラスにコンストラクタを追加します.
 * @param self
 * @param c
 */
void class_add_constructor(class_* self, struct constructor* c);

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
 * @param outIndex
 * @return 無ければ NULL
 */
struct field* class_find_field(class_* self, const char* name, int* outIndex);

/**
 * 指定の名前を持つフィールドを返します.
 * selfの中に見つけられなかった場合には親クラスも検索します。
 * @param self
 * @param name
 * @param domain
 * @param outIndex
 * @return
 */
struct field* class_find_field_tree(class_* self, const char* name, int* outIndex);

/**
 * 指定の名前を持つ静的フィールドを返します.
 * @param self
 * @param name
 * @param outIndex
 * @return 無ければ NULL
 */
struct field* class_find_sfield(class_* self, const char* name, int* outIndex);

/**
 * 指定の名前を持つ静的フィールドを返します.
 * selfの中に見つけられなかった場合には親クラスも検索します。
 * @param self
 * @param name
 * @param outIndex
 * @return 無ければ NULL
 */
struct field* class_find_sfield_tree(class_* self, const char* name, int* outIndex);

/**
 * 指定位置のフィールドを返します.
 * このクラスの上や下も含めて検索します。
 * つまりこの index は self の最上位クラスから self までに現れる全てのフィールドの通し番号です。
 * @param self
 * @param index
 * @return
 */
struct field* class_get_field(class_* self, int index);

/**
 * 指定位置の静的フィールドを返します.
 * このクラスの上や下も含めて検索します。
 * つまりこの index は self の最上位クラスから self までに現れる全てのフィールドの通し番号です。
 * @param self
 * @param index
 * @return
 */
struct field* class_get_sfield(class_* self, int index);

/**
 * もっとも一致するコンストラクタを返します.
 * @param self
 * @param args<il_argument*> 呼び出し側で開放してください.
 * @param env
 * @param outIndex
 * @return 無ければ空
 *         呼び出し側で開放してください。
 */
struct constructor* class_find_constructor(class_* self, vector* args, enviroment* env, int* outIndex);

/**
 * 引数が一つもないコンストラクタを検索して返します.
 * @param self
 * @param env
 * @param outIndex
 * @return
 */
struct constructor* class_find_empty_constructor(class_* self, enviroment* env, int* outIndex);

/**
 * もっとも一致するメソッドを返します.
 * @param self
 * @param name
 * @param env
 * @param args<il_argument*>
 * @param outIndex メソッドへのインデックス
 * @return
 */
struct method* class_find_method(class_* self, const char* name, vector* args, enviroment* env, int* outIndex);

/**
 * もっとも一致する静的メソッドを返します.
 * @param self
 * @param name
 * @param env
 * @param args<il_argument*>
 * @param outIndex メソッドへのインデックス
 * @return
 */
struct method* class_find_smethod(class_* self, const char* name, vector* args, enviroment* env, int* outIndex);

/**
 * 指定位置のメソッドを返します.
 * このクラスの上や下も含めて検索します。
 * つまりこの index は self の最上位クラスから self までに現れる全てのメソッドの通し番号です。
 * @param o
 * @param index
 * @return
 */
struct method* class_get_method(struct object* o, int index);

/**
 * 指定位置のメソッドを返します.
 * このクラスの上や下も含めて検索します。
 * つまりこの index は self の最上位クラスから self までに現れる全てのメソッドの通し番号です。
 * @param self
 * @param index
 * @return
 */
struct method* class_get_smethod(class_* self, int index);

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
 * このクラスの vtable を、現在のメソッド一覧に基づいて作成します.
 * このメソッドが呼び出されるまでメンバの vt は NULL です。
 * また、この関数は全てのメソッドが登録されてから呼び出してさい。
 * @param self
 */
void class_create_vtable(class_* self);

/**
 * このクラスとその親全てに定義されたフィールドの合計を返します.
 * @param self
 * @return
 */
int class_count_fieldall(class_* self);

/**
 * このクラスとその親全てに定義された静的フィールドの合計を返します.
 * @param self
 * @return
 */
int class_count_sfieldall(class_* self);

/**
 * このクラスとその親全てに定義されたメソッドの合計を返します.
 * @param self
 * @return
 */
int class_count_methodall(class_* self);

/**
 * このクラスとその親全てに定義されたメソッドの合計を返します.
 * @param self
 * @return
 */
int class_count_smethodall(class_* self);

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
