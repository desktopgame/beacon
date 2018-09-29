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
#include "../operator_vt.h"
#include "class_validate.h"
//#include "../access_domain.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
//struct field_list;
//struct method_list;
struct object;
struct field;
struct property;
struct property_body;
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
	Vector* impl_list;
	Vector* field_list;
	Vector* sfield_list;
	Vector* prop_list;
	Vector* sprop_list;
	Vector* method_list;
	Vector* smethod_list;
	Vector* constructor_list;
	Vector* operator_overload_list;
	//class_type type;
	uint32_t ref_count;
	NumericMap* native_method_ref_nmap;
	Vector* type_parameter_list;
	//インターフェースに対応した
	//実装メソッドのテーブルのベクター
	//http://d.hatena.ne.jp/tetz42/20120205/1328449750
	Vector* vt_vec;
	//Vector* static_fieldval_vec;
	vtable* vt;
	operator_vt* ovt;
	bool is_abstract;
} class_;
#include "class_find.h"

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
 * 指定のインターフェイスを実装するクラスを作成します.
 * @param gt
 * @param namev
 * @return
 */
class_* class_new_proxy(struct generic_type* gt, string_view namev);

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
 * @param fr
 */
void class_alloc_fields(class_* self, struct object* o, frame* fr);

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
 * このクラスにプロパティを追加します.
 * @param self
 * @param p
 */
void class_add_property(class_* self, struct property* p);

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
 * このクラスの operator_Vt を、現在のメソッド一覧に基づいて作成します.
 * @param self
 */
void class_create_operator_vt(class_* self);

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
 * このクラスとその親全てに定義されたプロパティの合計を返します.
 * @return
 */
int class_count_propertyall(class_* self);

/**
 * このクラスとその親全てに定義された静的プロパティの合計を返します.
 * @param self
 * @return
 */
int class_count_spropertyall(class_* self);

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
struct object* class_new_instance(class_* self, frame* fr, Vector* args, Vector* type_args);

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
#endif // !SIGNAL_ENV_CLASS_H
