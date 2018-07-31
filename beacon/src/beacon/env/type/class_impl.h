#pragma once
#ifndef BEACON_ENV_CLASS_H
#define BEACON_ENV_CLASS_H
#include "../namespace.h"
#include "../native_method_ref.h"
#include "../vtable.h"
#include "../type_interface.h"
#include "../../ast/operator_type.h"
#include "../../vm/enviroment.h"
#include "../../util/vector.h"
#include "../../il/call_context.h"
#include "../../util/numeric_map.h"
#include "../../util/string_pool.h"
//#include "../access_domain.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
//struct field_list;
//struct method_list;
struct object;
struct field;
struct method;
struct constructor;
struct generic_type;
struct operator_overload;
/**
 * クラスを表す構造体です.
 */
typedef struct class_ {
	type* parent;
	string_view namev;
	namespace_* location;
	struct generic_type* super_class;
	vector* impl_list;
	vector* field_list;
	vector* sfield_list;
	vector* method_list;
	vector* smethod_list;
	vector* constructor_list;
	vector* operator_overload_list;
	//class_type type;
	uint32_t ref_count;
	numeric_map* native_method_ref_nmap;
	vector* type_parameter_list;
	//インターフェースに対応した
	//実装メソッドのテーブルのベクター
	//http://d.hatena.ne.jp/tetz42/20120205/1328449750
	vector* vt_vec;
	//vector* static_fieldval_vec;
	vtable* vt;
	int classIndex;
	bool is_abstract;
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
 * @param namev
 * @return
 */
class_* class_new(string_view namev);

/**
 * 事前に読みこまれる必要があるクラスを作成します.
 * @param namev
 */
type* class_new_preload(string_view namev);

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
 * 指定の名前に対応するネイティブ関数を登録します.
 * @param self
 * @param name
 * @param impl
 */
void class_define_native_method(class_* self, const char* name, native_impl impl);

/**
 * 指定の名前に対応するネイティブ関数を登録します.
 * @param self
 * @param namev
 * @param impl
 */
void class_define_native_method_by_ref(class_* self, string_view namev, native_impl impl);

/**
 * 指定の名前を持つフィールドを返します.
 * @param self
 * @param namev
 * @param outIndex
 * @return 無ければ NULL
 */
struct field* class_find_field(class_* self, string_view namev, int* outIndex);

/**
 * 指定の名前を持つフィールドを返します.
 * selfの中に見つけられなかった場合には親クラスも検索します。
 * @param self
 * @param namev
 * @param domain
 * @param outIndex
 * @return
 */
struct field* class_find_field_tree(class_* self, string_view namev, int* outIndex);

/**
 * 指定の名前を持つ静的フィールドを返します.
 * @param self
 * @param namev
 * @param outIndex
 * @return 無ければ NULL
 */
struct field* class_find_sfield(class_* self, string_view namev, int* outIndex);

/**
 * 指定の名前を持つ静的フィールドを返します.
 * selfの中に見つけられなかった場合には親クラスも検索します。
 * @param self
 * @param namev
 * @param outIndex
 * @return 無ければ NULL
 */
struct field* class_find_sfield_tree(class_* self, string_view namev, int* outIndex);

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
 * @param args<object*> 呼び出し側で開放してください.
 * @param typeargs
 * @param outIndex
 * @return 無ければ空
 */
struct constructor* class_rfind_constructor(class_* self, vector* args, vector* typeargs, frame* fr, int* outIndex);

/**
 * もっとも一致するコンストラクタを返します.
 * @param self
 * @param args<il_argument*> 呼び出し側で開放してください.
 * @param env
 * @param cctx
 * @param outIndex
 * @return 無ければ空
 */
struct constructor* class_ilfind_constructor(class_* self, vector* args, enviroment* env, call_context* cctx, int* outIndex);

/**
 * 引数が一つもないコンストラクタを検索して返します.
 * @param self
 * @param env
 * @param cctx
 * @param outIndex
 * @return
 */
struct constructor* class_ilfind_empty_constructor(class_* self, enviroment* env, call_context* cctx, int* outIndex);

/**
 * もっとも一致するメソッドを返します.
 * @param self
 * @param namev
 * @param env
 * @param cctx
 * @param args<il_argument*>
 * @param outIndex メソッドへのインデックス
 * @return
 */
struct method* class_ilfind_method(class_* self, string_view namev, vector* args, enviroment* env, call_context* cctx, int* outIndex);

/**
 * もっとも一致するメソッドを返します.
 * @param self
 * @param namev
 * @param gargs
 * @param outIndex
 * @return
 */
struct method* class_gfind_method(class_* self, string_view namev, vector* gargs, int* outIndex);

/**
 * equalsメソッドを検索します.
 * @param self
 * @param outIndex
 * @return
 */
struct method* class_gfind_eqmethod(class_* self, int* outIndex);

/**
 * もっとも一致する静的メソッドを返します.
 * @param self
 * @param namev
 * @param env
 * @param cctx
 * @param args<il_argument*>
 * @param outIndex メソッドへのインデックス
 * @return
 */
struct method* class_ilfind_smethod(class_* self, string_view namev, vector* args, enviroment* env, call_context* cctx, int* outIndex);

/**
 * もっとも一致する静的メソッドを返します.
 * @param self
 * @param namev
 * @param gargs
 * @param outIndex
 * @return
 */
struct method* class_gfind_smethod(class_* self, string_view namev, vector* gargs, int* outIndex);

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
 * selfから、 interTypeの仮想関数テーブルの interIndex番目に属するメソッド
 * を実装するために定義されたメソッドを検索して返します。
 * @param self
 * @param interType
 * @param interIndex
 * @return
 */
struct method* class_get_impl_method(class_* self, type* interType, int interMIndex);

/**
 * @param self
 * @param type
 * @param args
 * @param env
 * @param outIndex
 * @return
 */
struct operator_overload* class_find_operator_overload(class_* self, operator_type type, vector* args, enviroment* env, int* outIndex);

/**
 * @param self
 * @param index
 * @return
 */
struct operator_overload* class_get_operator_overload(class_* self, int index);

/**
 * 指定のクラスから Object クラスまでのいずれかの階層に m が含まれるなら true.
 * @param self
 * @param m
 * @return
 */
bool class_contains_method_tree(class_* self, method* m);

/**
 * 指定のメソッド一覧に指定のメソッドが含まれるなら true.
 * 静的メソッドの場合はエラーを発生させます。
 * @param method_list
 * @param m
 */
bool class_contains_method(vector* method_list, method* m);

/**
 * super と sub の距離を返します.
 * @param super
 * @param sub
 * @return 同じクラスなら 0
 *         otherがselfのサブクラスなら正の数(階層の深さ)
 *         継承関係が異なるなら -1
 */
int class_distance(class_* super, class_* sub);

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
 * @param self
 * @param ilctx
 * @param fr
 * @param count
 * @param args
 * @param type_args
 * @return
 */
struct object* class_new_instance(class_* self, frame* fr, vector* args, vector* type_args);

/**
 * 全てのメンバーがこのクラスを参照できるようにします.
 * @param self
 */
void class_linkall(class_* self);

/**
 * 型情報を残してメソッドやフィールドなどのみを開放します.
 * @param self
 */
void class_unlink(class_* self);

/**
 * このクラスを開放します.
 * ただし先にこのクラスを参照するサブクラスを開放する必要があります。
 * @param self
 */
void class_delete(class_* self);

/**
 * ジェネリックタイプの一覧をクラスの一覧に変換します.
 * @param list
 * @return
 */
vector* class_generic_type_list_to_class_list(vector* list);

/**
 * ジェネリックタイプの一覧をインターフェイスの一覧に変換します.
 * @param list
 * @return
 */
vector* class_generic_type_list_to_interface_list(vector* list);

/**
 * クラスが全てのメソッドを正しく実装しているなら true.
 * インターフェイスを一つも持っていないなら 常にtrue です。
 * @param cls
 * @param out
 * @return
 */
bool class_interface_implement_valid(class_* cls, method** out);

/**
 * クラスが親の抽象メソッドを正しく実装しているなら true.
 * 親が具象クラスであるか、このクラスも抽象クラスなら 常にtrue です。
 * @param cls
 * @param out
 * @return
 */
bool class_abstract_class_implement_valid(class_* cls, method** out);

/**
 * クラスのフィールド名のうち重複するものがないなら true.
 * 親クラスのフィールドとの重複は無視されます。
 * @param cls
 * @param out
 * @return
 */
bool class_field_valid(class_* cls, struct field** out);
#endif // !SIGNAL_ENV_CLASS_H
