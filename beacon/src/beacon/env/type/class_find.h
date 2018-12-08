// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file class_find.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

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
struct bc_Field* bc_FindFieldClass(bc_Class* self, bc_StringView namev,
                                   int* outIndex);

/**
 * 指定の名前を持つフィールドを返します.
 * selfの中に見つけられなかった場合には親クラスも検索します。
 * @param self
 * @param namev
 * @param outIndex
 * @return
 */
struct bc_Field* bc_FindTreeFieldClass(bc_Class* self, bc_StringView namev,
                                       int* outIndex);

/**
 * 指定の名前を持つ静的フィールドを返します.
 * @param self
 * @param namev
 * @param outIndex
 * @return 無ければ NULL
 */
struct bc_Field* bc_FindSFieldClass(bc_Class* self, bc_StringView namev,
                                    int* outIndex);

/**
 * 指定の名前を持つ静的フィールドを返します.
 * selfの中に見つけられなかった場合には親クラスも検索します。
 * @param self
 * @param namev
 * @param outIndex
 * @return 無ければ NULL
 */
struct bc_Field* bc_FindTreeSFieldClass(bc_Class* self, bc_StringView namev,
                                        int* outIndex);

/**
 * 指定位置のフィールドを返します.
 * このクラスの上や下も含めて検索します。
 * つまりこの index は self の最上位クラスから self
 * までに現れる全てのフィールドの通し番号です。
 * @param self
 * @param index
 * @return
 */
struct bc_Field* bc_GetFieldClass(bc_Class* self, int index);

/**
 * 指定位置の静的フィールドを返します.
 * このクラスの上や下も含めて検索します。
 * つまりこの index は self の最上位クラスから self
 * までに現れる全てのフィールドの通し番号です。
 * @param self
 * @param index
 * @return
 */
struct bc_Field* bc_GetSFieldClass(bc_Class* self, int index);

/**
 * クラスに指定のフィールドが含まれるなら true.
 * @param self
 * @param f
 * @return
 */
bool bc_IsContainsFieldClass(bc_Class* self, struct bc_Field* f);

/**
 * クラスに指定の静的フィールドが含まれるなら true.
 * @param self
 * @param f
 * @return
 */
bool bc_IsContainsSFieldClass(bc_Class* self, struct bc_Field* f);

/**
 * 指定のクラスからフィールドにアクセスできるなら true.
 * @param self
 * @param f
 * @return
 */
bool bc_IsAccessibleFieldClass(bc_Class* self, struct bc_Field* f);

/**
 * クラスに指定のプロパティが含まれるなら true.
 * @param self
 * @param p
 * @return
 */
bool bc_IsContainsPropertyClass(bc_Class* self, struct bc_Property* p);

/**
 * クラスに指定のプロパティが含まれるなら true.
 * @param self
 * @param p
 * @return
 */
bool bc_IsContainsSPropertyClass(bc_Class* self, struct bc_Property* p);

/**
 * 指定のクラスからプロパティにアクセスできるなら true.
 * @param self
 * @param p
 */
bool bc_IsAccessiblePropertyClass(bc_Class* self, struct bc_Property* p);

/**
 * 指定のクラスからアクセサにアクセスできるなら true.
 * @param self
 * @param pb
 * @return
 */
bool bc_IsAccessiblePropertyAccessorClass(bc_Class* self,
                                          struct bc_PropertyBody* pb);

/**
 * 指定のプロパティが内部的に使用しているフィールドを返します.
 * @param self
 * @param p
 * @return
 */
int bc_GetFieldByPropertyClass(bc_Class* self, struct bc_Property* p);

/**
 * @param self
 * @param index
 * @return
 */
struct bc_Property* bc_GetPropertyClass(bc_Class* self, int index);
/**
 * @param self
 * @param index
 * @return
 */
struct bc_Property* bc_GetSPropertyClass(bc_Class* self, int index);

/**
 * 指定位置のメソッドを返します.
 * このクラスの上や下も含めて検索します。
 * つまりこの index は self の最上位クラスから self
 * までに現れる全てのメソッドの通し番号です。
 * @param o
 * @param index
 * @return
 */
struct bc_Method* bc_GetMethodClass(struct bc_Object* o, int index);

/**
 * 指定位置のメソッドを返します.
 * このクラスの上や下も含めて検索します。
 * つまりこの index は self の最上位クラスから self
 * までに現れる全てのメソッドの通し番号です。
 * @param self
 * @param index
 * @return
 */
struct bc_Method* bc_GetSMethodClass(bc_Class* self, int index);

/**
 * selfから、 interTypeの仮想関数テーブルの interIndex番目に属するメソッド
 * を実装するために定義されたメソッドを検索して返します。
 * @param self
 * @param interType
 * @param interIndex
 * @return
 */
struct bc_Method* bc_GetImplMethodClass(bc_Class* self, bc_Type* interType,
                                        int interMIndex);

/**
 * @param self
 * @param index
 * @return
 */
struct bc_OperatorOverload* bc_GetOperatorOverloadClass(bc_Class* self,
                                                        int index);

/**
 * 指定のメソッド一覧に指定のメソッドが含まれるなら true.
 * 静的メソッドの場合はエラーを発生させます。
 * @param method_list
 * @param m
 */
bool bc_IsContainsMethod(bc_Vector* method_list, bc_Method* m,
                         bc_Method** outM);

/**
 * 実装された全てのジェネリックインターフェイスを返します.
 * @param self
 * @return
 */
bc_Vector* bc_GetGenericInterfaceListClass(bc_Class* self);

/**
 * 実装/継承された全てのジェネリックインターフェイスを返します.
 * @param self
 * @return
 */
bc_Vector* bc_GetGenericInterfaceTreeClass(bc_Class* self);

/**
 * 実装された全てのインターフェイスを返します.
 * @param self
 * @return
 */
bc_Vector* bc_GetInterfaceListClass(bc_Class* self);

/**
 * 実装/継承された全てのインターフェイスを返します.
 * @param self
 * @return
 */
bc_Vector* bc_GetInterfaceTreeClass(bc_Class* self);

/**
 * @param self
 * @parma tinter
 * @return
 */
struct bc_GenericType* bc_FindInterfaceTypeClass(
    bc_Class* self, bc_Type* tinter, struct bc_GenericType** out_baseline);
#endif