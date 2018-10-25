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
struct Property;
struct PropertyBody;
struct Method;
struct constructor;
struct generic_type;
struct operator_overload;
/**
 * クラスを表す構造体です.
 */
typedef struct class_ {
	type* parent;
	StringView namev;
	Namespace* location;
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
	NumericMap* NativeMethodRef_nmap;
	Vector* GetParameterListType;
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
type* WrapClass(class_* self);

/**
 * 新しいクラスを作成します.
 * 呼び出し側で対応する名前空間を紐づけてください。
 * @param namev
 * @return
 */
class_* NewClass(StringView namev);

/**
 * 指定のインターフェイスを実装するクラスを作成します.
 * @param gt
 * @param namev
 * @return
 */
class_* NewClassProxy(struct generic_type* gt, StringView namev);

/**
 * 事前に読みこまれる必要があるクラスを作成します.
 * @param namev
 */
type* NewPreloadClass(StringView namev);

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
void AllocFieldsClass(class_* self, struct object* o, Frame* fr);

/**
 * 指定のオブジェクトに追加されたフィールドの一覧を開放します.
 * このメソッドは子クラスから順番に呼び出してください。
 * @param self
 * @param o
 */
void FreeClassFields(class_* self, struct object* o);

/**
 * このクラスにフィールドを追加します.
 * @param self
 * @param f
 */
void AddFieldClass(class_* self, struct field* f);

/**
 * このクラスにプロパティを追加します.
 * @param self
 * @param p
 */
void AddPropertyClass(class_* self, struct Property* p);

/**
 * このクラスにメソッドを追加します.
 * @param self
 * @param m
 */
void AddMethodClass(class_* self, struct Method* m);

/**
 * このクラスにコンストラクタを追加します.
 * @param self
 * @param c
 */
void AddConstructorClass(class_* self, struct constructor* c);

/**
 * 指定の名前に対応するネイティブ関数を登録します.
 * @param self
 * @param name
 * @param impl
 */
void DefineNativeMethodClass(class_* self, const char* name, NativeImpl impl);

/**
 * 指定の名前に対応するネイティブ関数を登録します.
 * @param self
 * @param namev
 * @param impl
 */
void DefineNativeMethodByRefClass(class_* self, StringView namev, NativeImpl impl);

/**
 * super と sub の距離を返します.
 * @param super
 * @param sub
 * @return 同じクラスなら 0
 *         otherがselfのサブクラスなら正の数(階層の深さ)
 *         継承関係が異なるなら -1
 */
int DistanceClass(class_* super, class_* sub);

/**
 * このクラスの vtable を、現在のメソッド一覧に基づいて作成します.
 * このメソッドが呼び出されるまでメンバの vt は NULL です。
 * また、この関数は全てのメソッドが登録されてから呼び出してさい。
 * @param self
 */
void CreateVTableClass(class_* self);
/**
 * このクラスの operator_Vt を、現在のメソッド一覧に基づいて作成します.
 * @param self
 */
void CreateOperatorVTClass(class_* self);

/**
 * このクラスとその親全てに定義されたフィールドの合計を返します.
 * @param self
 * @return
 */
int CountAllFieldClass(class_* self);

/**
 * このクラスとその親全てに定義された静的フィールドの合計を返します.
 * @param self
 * @return
 */
int CountAllSFieldClass(class_* self);

/**
 * このクラスとその親全てに定義されたプロパティの合計を返します.
 * @return
 */
int CountAllPropertyClass(class_* self);

/**
 * このクラスとその親全てに定義された静的プロパティの合計を返します.
 * @param self
 * @return
 */
int CountAllSPropertyClass(class_* self);

/**
 * このクラスとその親全てに定義されたメソッドの合計を返します.
 * @param self
 * @return
 */
int CountAllMethodClass(class_* self);

/**
 * このクラスとその親全てに定義されたメソッドの合計を返します.
 * @param self
 * @return
 */
int CountAllSMethodClass(class_* self);

/**
 * @param self
 * @param ilctx
 * @param fr
 * @param count
 * @param args
 * @param type_args
 * @return
 */
struct object* NewInstanceClass(class_* self, Frame* fr, Vector* args, Vector* type_args);

/**
 * 全てのメンバーがこのクラスを参照できるようにします.
 * @param self
 */
void LinkAllClass(class_* self);

/**
 * 型情報を残してメソッドやフィールドなどのみを開放します.
 * @param self
 */
void UnlinkClass(class_* self);

/**
 * このクラスを開放します.
 * ただし先にこのクラスを参照するサブクラスを開放する必要があります。
 * @param self
 */
void DeleteClass(class_* self);
#endif // !SIGNAL_ENV_CLASS_H
