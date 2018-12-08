#ifndef BEACON_ENV_TYPE_RESOLVE_H
#define BEACON_ENV_TYPE_RESOLVE_H
#include "../../il/call_context.h"
#include "../../util/string_pool.h"
#include "../../util/vector.h"
#include "../../vm/enviroment.h"
#include "../constructor.h"
#include "../field.h"
#include "../generic_type.h"
#include "../method.h"
#include "../operator_overload.h"
#include "../property.h"
#include "../type_interface.h"

typedef enum bc_SearchOption {
        MATCH_ALL,
        MATCH_PUBLIC_ONLY,
        MATCH_PUBLIC_OR_PROTECTED
} bc_SearchOption;

/**
 * argsの中の bc_ILArgument->Factor を全て計算して result へ格納します。
 * @param args[bc_ILArgument]
 * @param result
 * @param env
 * @param cctx
 */
void bc_CevaluateArguments(bc_Vector* args, bc_GenericType* result[],
                           bc_Enviroment* env, bc_CallContext* cctx);
/**
 * argsの中の bc_Object->GTypeを result へ格納します。
 * @param args[bc_Object]
 * @param result
 * @param env
 * @param cctx
 */
void bc_RevaluateArguments(bc_Vector* args, bc_GenericType* result[]);

//
// Find
//

/**
 * 一覧からマッチする要素を返します。
 * @param operator_overlods[bc_OperatorOverload]
 * @param type
 * @param args_count
 * @param args
 * @param option
 * @param cctx
 * @param outIndex
 * @return
 */
bc_OperatorOverload* bc_FindOperatorOverload(
    bc_Vector* operator_overloads, bc_OperatorType type, int args_count,
    bc_GenericType* args[], bc_SearchOption option, bc_CallContext* cctx,
    int* outIndex);

/**
 * 一覧からマッチする要素を返します。
 * @param methods[bc_Method]
 * @param name
 * @param args_count
 * @param args
 * @param type_args
 * @param option
 * @param cctx
 * @param outIndex
 * @return
 */
bc_Method* bc_FindMethod(bc_Vector* methods, bc_StringView name, int args_count,
                         bc_GenericType* args[], bc_Vector* type_args,
                         bc_SearchOption option, bc_CallContext* cctx,
                         int* outIndex);

/**
 * 一覧からマッチする要素を返します。
 * @param constructors[bc_Constructor]
 * @param name
 * @param args_count
 * @param args
 * @param type_args
 * @param option
 * @param cctx
 * @param outIndex
 * @return
 */
bc_Constructor* bc_FindConstructor(bc_Vector* constructors, int args_count,
                                   bc_GenericType* args[], bc_Vector* type_args,
                                   bc_SearchOption option, bc_CallContext* cctx,
                                   int* outIndex);
/**
 * 一致するフィールドを返します。
 * @param fields
 * @param name
 * @param option
 * @param outIndex
 * @return
 */
bc_Field* bc_FindField(bc_Vector* fields, bc_StringView name,
                       bc_SearchOption option, int* outIndex);

/**
 * 一致するプロパティを返します。
 * @param properties
 * @param name
 * @param option
 * @param outIndex
 * @return
 */
bc_Property* bc_FindProperty(bc_Vector* properties, bc_StringView name,
                             bc_SearchOption option, int* outIndex);

//
// Resolve
//
bc_Field* bc_ResolveField(struct bc_Class* classz, bc_StringView name,
                          int* outIndex);

bc_Property* bc_ResolveProperty(struct bc_Class* classz, bc_StringView name,
                                int* outIndex);

//
// Other
//
bc_Vector* bc_GetOverideMethods(struct bc_Class* classz, bc_Method* method);

bool bc_IsOverrideAny(bc_Vector* methods, bc_Method* super,
                      bc_Method** outOverride);

/**
 * @param self
 * @param index
 * @return
 */
bc_Property* bc_GetPropertyClass(struct bc_Class* self, int index);
/**
 * @param self
 * @param index
 * @return
 */
bc_Property* bc_GetSPropertyClass(struct bc_Class* self, int index);

/**
 * 指定位置のメソッドを返します.
 * このクラスの上や下も含めて検索します。
 * つまりこの index は self の最上位クラスから self
 * までに現れる全てのメソッドの通し番号です。
 * @param o
 * @param index
 * @return
 */
bc_Method* bc_GetMethodClass(struct bc_Object* o, int index);

/**
 * 指定位置のメソッドを返します.
 * このクラスの上や下も含めて検索します。
 * つまりこの index は self の最上位クラスから self
 * までに現れる全てのメソッドの通し番号です。
 * @param self
 * @param index
 * @return
 */
bc_Method* bc_GetSMethodClass(struct bc_Class* self, int index);
#endif