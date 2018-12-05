// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file generic_type.h
 * @brief ジェネリック型を定義します。
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_ENV_GENERIC_TYPE_H
#define BEACON_ENV_GENERIC_TYPE_H
#include "../util/vector.h"
//#include "type_parameter_rule.h"
#include <assert.h>
#include <stdbool.h>

#define bc_GENERIC2TYPE(gtype) (bc_GenericTypeToType(gtype))
#define bc_TYPE2GENERIC(type) (type->GenericSelf)

struct bc_Type;
struct bc_Method;
struct bc_Enviroment;
struct virtual_type;
struct bc_Frame;
struct bc_CallContext;
/**
 * 型変数つきの型宣言の型引数では GenericType 自身が使われますが、
 * それ自体が型変数の場合、何の型変数を指しているかを示す列挙型です.
 */
typedef enum bc_GenericTypeTag {
        /* bc_GenericType が型引数を持たない場合はこれを使用します。 */
        GENERIC_TYPE_TAG_NONE_T,
        /* 型変数がクラスに紐づいているならこれ。 */
        GENERIC_TYPE_TAG_CLASS_T,
        /* 型変数がメソッドに紐づいているならこれ。 */
        GENERIC_TYPE_TAG_METHOD_T,
} bc_GenericTypeTag;

/**
 * 型変数つきの型宣言.
 */
typedef struct bc_GenericType {
        /* 型変数を持っている型。 */
        struct bc_Type* CoreType;
        /* 型変数の一覧。 */
        bc_Vector* TypeArgs;
        /* 型変数を持っているメンバー。 */
        union {
                struct bc_Type* Type;
                struct bc_Method* Method;
        } Kind;
        /* 何番目の型変数であるかを示す。 */
        int VirtualTypeIndex;
        /* 型変数の種類を示す。 */
        bc_GenericTypeTag Tag;

        bool IsMark;
        /* コンストラクタの引数であるクラスにひもづく型変数ならtrueです。 */
        bool IsCtorParameter;
} bc_GenericType;

/**
 * beaocnが現在実行中のどの段階であるかを示す列挙。
 */
typedef enum bc_ExecutePhase {
        PHASE_COMPILE_TIME,
        PHASE_RUN_TIME,
} bc_ExecutePhase;

/**
 * 引数の種類です。
 */
typedef enum bc_ParameterKind {
        PARAMETER_INSTANCE,
        PARAMETER_TYPE,
} bc_ParameterKind;

//#define GenericType_validate(self) assert((self)->CoreType != NULL ||
// self->VirtualTypeIndex != -1)

/**
 * 新しい型変数つきの型宣言を作成します.
 * @param ctype
 * @return
 */
#define bc_NewGenericType(ctype) \
        (bc_MallocGenericType(ctype, __FILE__, __LINE__))

/**
 * CoreTypeがNULL以外なら GenericSelfを参照し、
 * NULLなら新規作成します。
 * @param CoreType
 * @return
 */
bc_GenericType* bc_RefGenericType(struct bc_Type* CoreType);

/**
 * 新しい型変数つきの型宣言を作成します.
 * 通常はマクロ版の NewGenericType を使用します。
 * @param ctype
 * @return
 */
bc_GenericType* bc_MallocGenericType(struct bc_Type* CoreType,
                                     const char* filename, int lineno);

/**
 * ジェネリックタイプを複製します.
 * @param self
 * @param recursive
 * @return
 */
bc_GenericType* bc_CloneGenericType(bc_GenericType* self, bool recursive);

/**
 * 現在のスクリプトコンテキストでどこからも参照されていない
 * GenericType の一覧を解放します。
 */
void bc_CollectGenericType();

/**
 * type#GenericSelf を解放する時に使います.
 * CollectGenericType より後に呼び出してください。
 * @param a
 */
void bc_LostownershipGenericType(bc_GenericType* a);

/**
 * self の子要素として a を追加します.
 * @param self
 * @param a
 */
void bc_AddArgsGenericType(bc_GenericType* self, bc_GenericType* a);

/**
 * a と b の距離を返します.
 * メソッドを解決する時、もっともマッチするオーバーロードを見つけるために使用されます。
 * @param self
 * @param other
 * @return 同じなら 0
 *         異なる継承階層なら -1
 *         サブタイプなら階層の数
 */
int bc_CdistanceGenericType(bc_GenericType* self, bc_GenericType* other);
/**
 * a と b の距離を返します.
 * メソッドを解決する時、もっともマッチするオーバーロードを見つけるために使用されます。
 * @param self
 * @param other
 * @return 同じなら 0
 *         異なる継承階層なら -1
 *         サブタイプなら階層の数
 */
int bc_RdistanceGenericType(bc_GenericType* self, bc_GenericType* other);

/**
 * 型変数と型を出力します.
 * @param self
 */
void bc_PrintGenericType(bc_GenericType* self);

/**
 * ジェネリックタイプをオペコードとして出力します.
 * @param self
 * @param env
 * @param ilctx
 */
void bc_GenerateGenericType(bc_GenericType* self, struct bc_Enviroment* env);

/**
 * コンパイル時にジェネリック型を解決します。
 * @param self
 * @param cctx
 * @return
 */
bc_GenericType* bc_CapplyGenericType(bc_GenericType* self,
                                     struct bc_CallContext* cctx);
/**
 * 実行時にジェネリック型を解決します。
 * @param self
 * @param fr
 * @return
 */
bc_GenericType* bc_RapplyGenericType(bc_GenericType* self, struct bc_Frame* fr);

/**
 * 再帰的に型変数を展開して返します。
 * @param self
 * @param cctx
 * @param receiver
 * @param type_args
 * @param phase
 * @return
 */
bc_GenericType* bc_ExpandGenericType(bc_GenericType* self,
                                     struct bc_GenericType* receiver,
                                     bc_Vector* type_args,
                                     bc_ExecutePhase phase);

/**
 * GenericType を type へ変換します.
 * @param self
 * @return
 */
struct bc_Type* bc_GenericTypeToType(bc_GenericType* self);
#endif  // !SIGNAL_ENV_GENERIC_TYPE_H
