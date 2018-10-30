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
struct Field* FindFieldClass(class_* self, StringView namev, int* outIndex);

/**
 * 指定の名前を持つフィールドを返します.
 * selfの中に見つけられなかった場合には親クラスも検索します。
 * @param self
 * @param namev
 * @param outIndex
 * @return
 */
struct Field* FindTreeFieldClass(class_* self, StringView namev, int* outIndex);

/**
 * 指定の名前を持つ静的フィールドを返します.
 * @param self
 * @param namev
 * @param outIndex
 * @return 無ければ NULL
 */
struct Field* FindSFieldClass(class_* self, StringView namev, int* outIndex);

/**
 * 指定の名前を持つ静的フィールドを返します.
 * selfの中に見つけられなかった場合には親クラスも検索します。
 * @param self
 * @param namev
 * @param outIndex
 * @return 無ければ NULL
 */
struct Field* FindTreeSFieldClass(class_* self, StringView namev, int* outIndex);

/**
 * 指定位置のフィールドを返します.
 * このクラスの上や下も含めて検索します。
 * つまりこの index は self の最上位クラスから self までに現れる全てのフィールドの通し番号です。
 * @param self
 * @param index
 * @return
 */
struct Field* GetFieldClass(class_* self, int index);

/**
 * 指定位置の静的フィールドを返します.
 * このクラスの上や下も含めて検索します。
 * つまりこの index は self の最上位クラスから self までに現れる全てのフィールドの通し番号です。
 * @param self
 * @param index
 * @return
 */
struct Field* GetSFieldClass(class_* self, int index);

/**
 * クラスに指定のフィールドが含まれるなら true.
 * @param self
 * @param f
 * @return
 */
bool IsContainsFieldClass(class_* self, struct Field* f);

/**
 * クラスに指定の静的フィールドが含まれるなら true.
 * @param self
 * @param f
 * @return
 */
bool IsContainsSFieldClass(class_* self, struct Field* f);

/**
 * 指定のクラスからフィールドにアクセスできるなら true.
 * @param self
 * @param f
 * @return
 */
bool IsAccessibleFieldClass(class_* self, struct Field* f);




/**
 * クラスに指定のプロパティが含まれるなら true.
 * @param self
 * @param p
 * @return
 */
bool IsContainsPropertyClass(class_* self, struct Property* p);

/**
 * クラスに指定のプロパティが含まれるなら true.
 * @param self
 * @param p
 * @return
 */
bool IsContainsSPropertyClass(class_* self, struct Property* p);

/**
 * 指定のクラスからプロパティにアクセスできるなら true.
 * @param self
 * @param p
 */
bool IsAccessiblePropertyClass(class_* self, struct Property* p);

/**
 * 指定のクラスからアクセサにアクセスできるなら true.
 * @param self
 * @param pb
 * @return
 */
bool IsAccessiblePropertyAccessorClass(class_* self, struct PropertyBody* pb);

/**
 * 指定のプロパティが内部的に使用しているフィールドを返します.
 * @param self
 * @param p
 * @return
 */
int GetFieldByPropertyClass(class_* self, struct Property* p);

/**
 * @param self
 * @param index
 * @return
 */
struct Property* GetPropertyClass(class_* self, int index);
/**
 * @param self
 * @param index
 * @return
 */
struct Property* GetSPropertyClass(class_* self, int index);

/**
 * 指定の名前のプロパティを検索します.
 * @param self
 * @param namev
 * @param outIndex
 * @return
 */
struct Property* FindPropertyClass(class_* self, StringView namev, int* outIndex);

/**
 * 指定の名前を持つプロパティを返します.
 * selfの中に見つけられなかった場合には親クラスも検索します。
 * @param self
 * @param namev
 * @param outIndex
 * @return
 */
struct Property* FindTreePropertyClass(class_* self, StringView namev, int* outIndex);

/**
 * 指定の名前の静的プロパティを検索します.
 * @param self
 * @param namev
 * @param outIndex
 * @return
 */
struct Property* FindSPropertyClass(class_* self, StringView namev, int* outIndex);

/**
 * 指定の名前を持つ静的プロパティを返します.
 * selfの中に見つけられなかった場合には親クラスも検索します。
 * @param self
 * @param namev
 * @param outIndex
 * @return
 */
struct Property* FindTreeSPropertyClass(class_* self, StringView namev, int* outIndex);



/**
 * もっとも一致するコンストラクタを返します.
 * @param self
 * @param args<Object*> 呼び出し側で開放してください.
 * @param typeargs
 * @param outIndex
 * @return 無ければ空
 */
struct Constructor* RFindConstructorClass(class_* self, Vector* args, Vector* typeargs, Frame* fr, int* outIndex);

/**
 * もっとも一致するコンストラクタを返します.
 * @param self
 * @param args<il_argument*> 呼び出し側で開放してください.
 * @param env
 * @param cctx
 * @param outIndex
 * @return 無ければ空
 */
struct Constructor* ILFindConstructorClass(class_* self, Vector* args, Enviroment* env, CallContext* cctx, int* outIndex);

/**
 * 引数が一つもないコンストラクタを検索して返します.
 * @param self
 * @param env
 * @param cctx
 * @param outIndex
 * @return
 */
struct Constructor* ILFindEmptyConstructorClass(class_* self, Enviroment* env, CallContext* cctx, int* outIndex);

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
struct Method* ILFindMethodClass(class_* self, StringView namev, Vector* args, Enviroment* env, CallContext* cctx, int* outIndex);

/**
 * もっとも一致するメソッドを返します.
 * @param self
 * @param namev
 * @param gargs
 * @param outIndex
 * @return
 */
struct Method* GFindMethodClass(class_* self, StringView namev, Vector* gargs, int* outIndex);

/**
 * equalsメソッドを検索します.
 * @param self
 * @param outIndex
 * @return
 */
struct Method* GFindEqMethodClass(class_* self, int* outIndex);

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
struct Method* ILFindSMethodClass(class_* self, StringView namev, Vector* args, Enviroment* env, CallContext* cctx, int* outIndex);

/**
 * もっとも一致する静的メソッドを返します.
 * @param self
 * @param namev
 * @param gargs
 * @param outIndex
 * @return
 */
struct Method* GFindSMethodClass(class_* self, StringView namev, Vector* gargs, int* outIndex);

/**
 * 指定位置のメソッドを返します.
 * このクラスの上や下も含めて検索します。
 * つまりこの index は self の最上位クラスから self までに現れる全てのメソッドの通し番号です。
 * @param o
 * @param index
 * @return
 */
struct Method* GetMethodClass(struct Object* o, int index);

/**
 * 指定位置のメソッドを返します.
 * このクラスの上や下も含めて検索します。
 * つまりこの index は self の最上位クラスから self までに現れる全てのメソッドの通し番号です。
 * @param self
 * @param index
 * @return
 */
struct Method* GetSMethodClass(class_* self, int index);

/**
 * selfから、 interTypeの仮想関数テーブルの interIndex番目に属するメソッド
 * を実装するために定義されたメソッドを検索して返します。
 * @param self
 * @param interType
 * @param interIndex
 * @return
 */
struct Method* GetImplMethodClass(class_* self, Type* interType, int interMIndex);




/**
 * @param self
 * @param type
 * @param args
 * @param env
 * @param cctx
 * @param outIndex
 * @return
 */
struct OperatorOverload* GFindOperatorOverloadClass(class_* self, OperatorType type, Vector* args, Enviroment* env, CallContext* cctx, int* outIndex);

struct OperatorOverload* ILFindOperatorOverloadClass(class_* self, OperatorType type, Vector* args, Enviroment* env, CallContext* cctx, int* outIndex);

struct OperatorOverload* ArgFindOperatorOverloadClass(class_* self, OperatorType type, Vector* args, Enviroment* env, CallContext* cctx, int* outIndex);

/**
 * @param self
 * @param index
 * @return
 */
struct OperatorOverload* GetOperatorOverloadClass(class_* self, int index);

/**
 * 指定のクラスから Object クラスまで階層で m と互換性のあるメソッドを検索して返します.
 * @param self
 * @param m
 * @param outM
 * @return
 */
Vector* FindTreeMethodClass(class_* self, Method* m);

/**
 * 指定のメソッド一覧に指定のメソッドが含まれるなら true.
 * 静的メソッドの場合はエラーを発生させます。
 * @param method_list
 * @param m
 */
bool IsContainsMethod(Vector* method_list, Method* m, Method** outM);

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
struct GenericType* FindInterfaceTypeClass(class_* self, Type* tinter, struct GenericType** out_baseline);
#endif