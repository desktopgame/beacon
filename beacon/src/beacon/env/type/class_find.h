#ifndef BEACON_TYPE_FIND_H
#define BEACON_TYPE_FIND_H
#include "../../util/string_pool.h"
#include "../../util/vector.h"
#include "class_impl.h"
/**
 * 指定の名前を持つフィールドを返します.
 * @param self
 * @param namev
 * @param outIndex
 * @return 無ければ NULL
 */
struct field* FindFieldClass(class_* self, StringView namev, int* outIndex);

/**
 * 指定の名前を持つフィールドを返します.
 * selfの中に見つけられなかった場合には親クラスも検索します。
 * @param self
 * @param namev
 * @param outIndex
 * @return
 */
struct field* FindTreeFieldClass(class_* self, StringView namev, int* outIndex);

/**
 * 指定の名前を持つ静的フィールドを返します.
 * @param self
 * @param namev
 * @param outIndex
 * @return 無ければ NULL
 */
struct field* FindSFieldClass(class_* self, StringView namev, int* outIndex);

/**
 * 指定の名前を持つ静的フィールドを返します.
 * selfの中に見つけられなかった場合には親クラスも検索します。
 * @param self
 * @param namev
 * @param outIndex
 * @return 無ければ NULL
 */
struct field* FindTreeSFieldClass(class_* self, StringView namev, int* outIndex);

/**
 * 指定位置のフィールドを返します.
 * このクラスの上や下も含めて検索します。
 * つまりこの index は self の最上位クラスから self までに現れる全てのフィールドの通し番号です。
 * @param self
 * @param index
 * @return
 */
struct field* GetFieldClass(class_* self, int index);

/**
 * 指定位置の静的フィールドを返します.
 * このクラスの上や下も含めて検索します。
 * つまりこの index は self の最上位クラスから self までに現れる全てのフィールドの通し番号です。
 * @param self
 * @param index
 * @return
 */
struct field* GetSFieldClass(class_* self, int index);

/**
 * クラスに指定のフィールドが含まれるなら true.
 * @param self
 * @param f
 * @return
 */
bool IsContainsFieldClass(class_* self, struct field* f);

/**
 * クラスに指定の静的フィールドが含まれるなら true.
 * @param self
 * @param f
 * @return
 */
bool IsContainsSFieldClass(class_* self, struct field* f);

/**
 * 指定のクラスからフィールドにアクセスできるなら true.
 * @param self
 * @param f
 * @return
 */
bool IsAccessibleFieldClass(class_* self, struct field* f);




/**
 * クラスに指定のプロパティが含まれるなら true.
 * @param self
 * @param p
 * @return
 */
bool IsContainsPropertyClass(class_* self, struct property* p);

/**
 * クラスに指定のプロパティが含まれるなら true.
 * @param self
 * @param p
 * @return
 */
bool IsContainsSPropertyClass(class_* self, struct property* p);

/**
 * 指定のクラスからプロパティにアクセスできるなら true.
 * @param self
 * @param p
 */
bool IsAccessiblePropertyClass(class_* self, struct property* p);

/**
 * 指定のクラスからアクセサにアクセスできるなら true.
 * @param self
 * @param pb
 * @return
 */
bool IsAccessiblePropertyAccessorClass(class_* self, struct property_body* pb);

/**
 * 指定のプロパティが内部的に使用しているフィールドを返します.
 * @param self
 * @param p
 * @return
 */
int GetFieldByPropertyClass(class_* self, struct property* p);

/**
 * @param self
 * @param index
 * @return
 */
struct property* GetPropertyClass(class_* self, int index);
/**
 * @param self
 * @param index
 * @return
 */
struct property* GetSPropertyClass(class_* self, int index);

/**
 * 指定の名前のプロパティを検索します.
 * @param self
 * @param namev
 * @param outIndex
 * @return
 */
struct property* FindPropertyClass(class_* self, StringView namev, int* outIndex);

/**
 * 指定の名前を持つプロパティを返します.
 * selfの中に見つけられなかった場合には親クラスも検索します。
 * @param self
 * @param namev
 * @param outIndex
 * @return
 */
struct property* FindTreePropertyClass(class_* self, StringView namev, int* outIndex);

/**
 * 指定の名前の静的プロパティを検索します.
 * @param self
 * @param namev
 * @param outIndex
 * @return
 */
struct property* FindSPropertyClass(class_* self, StringView namev, int* outIndex);

/**
 * 指定の名前を持つ静的プロパティを返します.
 * selfの中に見つけられなかった場合には親クラスも検索します。
 * @param self
 * @param namev
 * @param outIndex
 * @return
 */
struct property* FindTreeSPropertyClass(class_* self, StringView namev, int* outIndex);



/**
 * もっとも一致するコンストラクタを返します.
 * @param self
 * @param args<object*> 呼び出し側で開放してください.
 * @param typeargs
 * @param outIndex
 * @return 無ければ空
 */
struct constructor* RFindConstructorClass(class_* self, Vector* args, Vector* typeargs, frame* fr, int* outIndex);

/**
 * もっとも一致するコンストラクタを返します.
 * @param self
 * @param args<il_argument*> 呼び出し側で開放してください.
 * @param env
 * @param cctx
 * @param outIndex
 * @return 無ければ空
 */
struct constructor* ILFindConstructorClass(class_* self, Vector* args, enviroment* env, call_context* cctx, int* outIndex);

/**
 * 引数が一つもないコンストラクタを検索して返します.
 * @param self
 * @param env
 * @param cctx
 * @param outIndex
 * @return
 */
struct constructor* ILFindEmptyConstructorClass(class_* self, enviroment* env, call_context* cctx, int* outIndex);

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
struct method* ILFindMethodClass(class_* self, StringView namev, Vector* args, enviroment* env, call_context* cctx, int* outIndex);

/**
 * もっとも一致するメソッドを返します.
 * @param self
 * @param namev
 * @param gargs
 * @param outIndex
 * @return
 */
struct method* GFindMethodClass(class_* self, StringView namev, Vector* gargs, int* outIndex);

/**
 * equalsメソッドを検索します.
 * @param self
 * @param outIndex
 * @return
 */
struct method* GFindEqMethodClass(class_* self, int* outIndex);

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
struct method* ILFindSMethodClass(class_* self, StringView namev, Vector* args, enviroment* env, call_context* cctx, int* outIndex);

/**
 * もっとも一致する静的メソッドを返します.
 * @param self
 * @param namev
 * @param gargs
 * @param outIndex
 * @return
 */
struct method* GFindSMethodClass(class_* self, StringView namev, Vector* gargs, int* outIndex);

/**
 * 指定位置のメソッドを返します.
 * このクラスの上や下も含めて検索します。
 * つまりこの index は self の最上位クラスから self までに現れる全てのメソッドの通し番号です。
 * @param o
 * @param index
 * @return
 */
struct method* GetMethodClass(struct object* o, int index);

/**
 * 指定位置のメソッドを返します.
 * このクラスの上や下も含めて検索します。
 * つまりこの index は self の最上位クラスから self までに現れる全てのメソッドの通し番号です。
 * @param self
 * @param index
 * @return
 */
struct method* GetSMethodClass(class_* self, int index);

/**
 * selfから、 interTypeの仮想関数テーブルの interIndex番目に属するメソッド
 * を実装するために定義されたメソッドを検索して返します。
 * @param self
 * @param interType
 * @param interIndex
 * @return
 */
struct method* GetImplMethodClass(class_* self, type* interType, int interMIndex);




/**
 * @param self
 * @param type
 * @param args
 * @param env
 * @param cctx
 * @param outIndex
 * @return
 */
struct operator_overload* GFindOperatorOverloadClass(class_* self, operator_type type, Vector* args, enviroment* env, call_context* cctx, int* outIndex);

struct operator_overload* ILFindOperatorOverloadClass(class_* self, operator_type type, Vector* args, enviroment* env, call_context* cctx, int* outIndex);

struct operator_overload* ArgFindOperatorOverloadClass(class_* self, operator_type type, Vector* args, enviroment* env, call_context* cctx, int* outIndex);

/**
 * @param self
 * @param index
 * @return
 */
struct operator_overload* GetOperatorOverloadClass(class_* self, int index);

/**
 * 指定のクラスから Object クラスまで階層で m と互換性のあるメソッドを検索して返します.
 * @param self
 * @param m
 * @param outM
 * @return
 */
Vector* FindTreeMethodClass(class_* self, method* m);

/**
 * 指定のメソッド一覧に指定のメソッドが含まれるなら true.
 * 静的メソッドの場合はエラーを発生させます。
 * @param method_list
 * @param m
 */
bool IsContainsMethod(Vector* method_list, method* m, method** outM);

/**
 * 実装された全てのジェネリックインターフェイスを返します.
 * @param self
 * @return
 */
Vector* GetGenericInterfaceListClass(class_* self);

/**
 * 実装/継承された全てのジェネリックインターフェイスを返します.
 * @param self
 * @return
 */
Vector* GetGenericInterfaceTreeClass(class_* self);

/**
 * 実装された全てのインターフェイスを返します.
 * @param self
 * @return
 */
Vector* GetInterfaceListClass(class_* self);

/**
 * 実装/継承された全てのインターフェイスを返します.
 * @param self
 * @return
 */
Vector* GetInterfaceTreeClass(class_* self);

/**
 * @param self
 * @parma tinter
 * @return
 */
struct generic_type* FindInterfaceTypeClass(class_* self, type* tinter, struct generic_type** out_baseline);
#endif