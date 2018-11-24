#include "class_loader_bcload_impl.h"
#include <assert.h>
#include "../../env/object.h"
#include "../../il/il_TYPE_IMPL.h"
#include "../../il/il_argument.h"
#include "../../il/il_constructor.h"
#include "../../il/il_constructor_chain.h"
#include "../../il/il_field.h"
#include "../../il/il_import.h"
#include "../../il/il_method.h"
#include "../../il/il_namespace.h"
#include "../../il/il_parameter.h"
#include "../../il/il_stmt_interface.h"
#include "../../il/il_type_interface.h"
#include "../../il/il_type_parameter.h"
#include "../../parse/parser.h"
#include "../../util/io.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../TYPE_IMPL.h"
#include "../constructor.h"
#include "../field.h"
#include "../method.h"
#include "../parameter.h"
#include "../script_context.h"
#include "../type_interface.h"
#include "../type_parameter.h"
#include "class_loader_bcload_import_module_impl.h"
//
// sgload
//
#include <string.h>
#include "../../env/heap.h"
#include "../import_info.h"
#include "../type_cache.h"
// proto
static void CLBC_namespace_tree(bc_ClassLoader* self);
/**
 * 名前空間の一覧を読み込みます.
 * @param self
 * @param ilNamespacelist
 * @param parent
 */
static void CLBC_namespace_list(bc_ClassLoader* self,
                                bc_Vector* ilNamespacelist,
                                bc_Namespace* parent);

/**
 * 名前空間と含まれるエントリの一覧を読み込みます.
 * @param self
 * @param ilnamespace
 * @param parent
 */
static void CLBC_namespace(bc_ClassLoader* self, bc_ILNamespace* ilnamespace,
                           bc_Namespace* parent);

/**
 * 型宣言の一覧を読み込みます.
 * @param self
 * @param iltype_list
 * @param parent
 */
static void CLBC_type_list(bc_ClassLoader* self, bc_Vector* iltype_list,
                           bc_Namespace* parent);

/**
 * 列挙宣言を読み込んで名前空間に登録します.
 * @param self
 * @param iltype
 * @param parent
 */
static void CLBC_enum(bc_ClassLoader* self, bc_ILType* iltype,
                      bc_Namespace* parent);

/**
 * クラス宣言を読み込んで名前空間に登録します.
 * @param self
 * @param iltype
 * @param parent
 */
static void CLBC_class(bc_ClassLoader* self, bc_ILType* iltype,
                       bc_Namespace* parent);

/**
 * インターフェース宣言を読み込んで名前空間に登録します.
 * @param self
 * @param iltype
 * @param parent
 */
static void CLBC_interface(bc_ClassLoader* self, bc_ILType* iltype,
                           bc_Namespace* parent);

static void CLBC_attach_native_method(bc_ClassLoader* self, bc_ILType* iltype,
                                      bc_Class* classz, bc_ILMethod* ilmethod,
                                      bc_Method* me);
static void CLBC_debug_native_method(bc_Method* parent, bc_Frame* fr,
                                     bc_Enviroment* env);

static void CLBC_check_superclass(bc_Class* cls);
static bc_Type* CLBC_get_or_load_enum(bc_Namespace* parent, bc_ILType* iltype);
static bc_Type* CLBC_get_or_load_class(bc_ClassLoader* self,
                                       bc_Namespace* parent, bc_ILType* iltype);
static void CLBC_register_class(bc_ClassLoader* self, bc_Namespace* parent,
                                bc_ILType* iltype, bc_Type* tp, bc_Class* cls);
static bc_Type* CLBC_get_or_load_interface(bc_ClassLoader* self,
                                           bc_Namespace* parent,
                                           bc_ILType* iltype);
static void CLBC_register_interface(bc_ClassLoader* self, bc_Namespace* parent,
                                    bc_ILType* iltype, bc_Type* tp,
                                    bc_Interface* inter);

void BCLoadClassLoader(bc_ClassLoader* self) {
        bc_CL_ERROR(self);
        bc_ScriptContext* ctx = bc_GetCurrentScriptContext();
        bc_ILToplevel* iltop = self->ILCode;
        CLBC_import(self, self->ILCode->ImportList);
        CLBC_namespace_tree(self);
}

void SpecialBCLoadClassLoader(bc_ClassLoader* self) {
        bc_CL_ERROR(self);
        bc_ScriptContext* ctx = bc_GetCurrentScriptContext();
        bc_ILToplevel* iltop = self->ILCode;
        //	CLBC_import(self, self->ILCode->import_list);
        CLBC_namespace_tree(self);
}

// private
static void CLBC_namespace_tree(bc_ClassLoader* self) {
        bc_CL_ERROR(self);
        CLBC_namespace_list(self, self->ILCode->NamespaceList, NULL);
}

static void CLBC_namespace_list(bc_ClassLoader* self,
                                bc_Vector* ilNamespacelist,
                                bc_Namespace* parent) {
        // self->link = classlink_resume;
        bc_CL_ERROR(self);
        for (int i = 0; i < ilNamespacelist->Length; i++) {
                bc_VectorItem e = bc_AtVector(ilNamespacelist, i);
                bc_ILNamespace* iln = (bc_ILNamespace*)e;
                CLBC_namespace(self, iln, parent);
                bc_CL_ERROR(self);
        }
}

static void CLBC_namespace(bc_ClassLoader* self, bc_ILNamespace* ilnamespace,
                           bc_Namespace* parent) {
        bc_CL_ERROR(self);
        bc_Namespace* current = NULL;
        if (parent == NULL) {
                current = bc_CreateNamespaceAtRoot(ilnamespace->Name);
        } else {
                current = bc_AddNamespaceNamespace(parent, ilnamespace->Name);
        }
        CLBC_namespace_list(self, ilnamespace->NamespaceList, current);
        CLBC_type_list(self, ilnamespace->TypeList, current);
}

static void CLBC_type_list(bc_ClassLoader* self, bc_Vector* iltype_list,
                           bc_Namespace* parent) {
        bc_CL_ERROR(self);
        for (int i = 0; i < iltype_list->Length; i++) {
                bc_VectorItem e = bc_AtVector(iltype_list, i);
                bc_ILType* ilt = (bc_ILType*)e;
                if (ilt->Tag == ILTYPE_CLASS_T) {
                        CLBC_class(self, ilt, parent);
                } else if (ilt->Tag == ILTYPE_INTERFACE_T) {
                        CLBC_interface(self, ilt, parent);
                } else if (ilt->Tag == ILTYPE_ENUM_T) {
                        CLBC_enum(self, ilt, parent);
                }
                bc_CL_ERROR(self);
        }
}

static void CLBC_enum(bc_ClassLoader* self, bc_ILType* iltype,
                      bc_Namespace* parent) {
        bc_CL_ERROR(self);
        assert(iltype->Tag == ILTYPE_ENUM_T);
        bc_ILEnum* ilenum = iltype->Kind.Enum;
        bc_Type* tp = CLBC_get_or_load_enum(parent, iltype);
        bc_CL_ERROR(self);
        bc_Class* cls = BC_TYPE2CLASS(tp);
        if ((tp->State & TYPE_REGISTER) > 0) {
                return;
        }
        bc_InitGenericSelf(tp, 0);
        //全ての列挙子を public static final フィールドとして追加
        for (int i = 0; i < ilenum->Items->Length; i++) {
                bc_StringView str =
                    (bc_StringView)bc_AtVector(ilenum->Items, i);
                bc_Field* f = bc_NewField(str);
                BC_MEMBER_MODIFIER(f) = MODIFIER_STATIC_T;
                BC_MEMBER_ACCESS(f) = ACCESS_PUBLIC_T;
                f->StaticValue = NULL;
                f->GType = BC_TYPE_INT->GenericSelf;
                // virtual_type_nongeneric_init(&f->vtype, GENERIC_INT);
                BC_MEMBER_TYPE(f) = tp;
                // f->static_value->paint = PAINT_MARKED_T;
                bc_AddFieldClass(cls, f);
        }
        //宣言のロードを予約
        bc_TypeCache* tc = bc_InitTypeCache(bc_NewTypeCache(), self, iltype, tp,
                                            parent, CACHEKIND_ENUM_DECL_T);
        bc_PushVector(self->TypeCaches, tc);
        //実装のロードを予約
        bc_TypeCache* mtc = bc_InitTypeCache(bc_NewTypeCache(), self, iltype,
                                             tp, parent, CACHEKIND_ENUM_IMPL_T);
        bc_PushVector(self->TypeCaches, mtc);
        tp->State = tp->State | TYPE_REGISTER;
}

static void CLBC_class(bc_ClassLoader* self, bc_ILType* iltype,
                       bc_Namespace* parent) {
        bc_CL_ERROR(self);
        //既に登録されていたら二重に登録しないように
        //例えば、ネイティブメソッドを登録するために一時的にクラスが登録されている場合がある
        assert(iltype->Tag == ILTYPE_CLASS_T);
        bc_Type* tp = CLBC_get_or_load_class(self, parent, iltype);
        bc_CL_ERROR(self);
        bc_Class* cls = BC_TYPE2CLASS(tp);
        if ((tp->State & TYPE_REGISTER) > 0) {
                return;
        }
        cls->IsAbstract = iltype->Kind.Class->IsAbstract;
        bc_InitGenericSelf(tp, iltype->Kind.Class->TypeParameters->Length);
        //デフォルトで親に Object を持つように
        CLBC_check_superclass(cls);
        //宣言のロードを予約
        bc_TypeCache* tc = bc_InitTypeCache(bc_NewTypeCache(), self, iltype, tp,
                                            parent, CACHEKIND_CLASS_DECL_T);
        bc_PushVector(self->TypeCaches, tc);
        //実装のロードを予約
        bc_TypeCache* mtc =
            bc_InitTypeCache(bc_NewTypeCache(), self, iltype, tp, parent,
                             CACHEKIND_CLASS_IMPL_T);
        bc_PushVector(self->TypeCaches, mtc);
        tp->State = tp->State | TYPE_REGISTER;
}

static void CLBC_interface(bc_ClassLoader* self, bc_ILType* iltype,
                           bc_Namespace* parent) {
        bc_CL_ERROR(self);
        assert(iltype->Tag == ILTYPE_INTERFACE_T);
        // NOTE:後で親関数から渡すようにする
        bc_Type* tp = CLBC_get_or_load_interface(self, parent, iltype);
        bc_CL_ERROR(self);
        bc_Interface* inter = BC_TYPE2INTERFACE(tp);
        if ((tp->State & TYPE_REGISTER) > 0) {
                return;
        }
        bc_InitGenericSelf(tp, iltype->Kind.Interface->TypeParameters->Length);
        //宣言のロードを予約
        bc_TypeCache* tc = bc_InitTypeCache(bc_NewTypeCache(), self, iltype, tp,
                                            parent, CACHEKIND_INTERFACE_DECL_T);
        bc_PushVector(self->TypeCaches, tc);
        //実装のロードを予約
        bc_TypeCache* mtc =
            bc_InitTypeCache(bc_NewTypeCache(), self, iltype, tp, parent,
                             CACHEKIND_INTERFACE_IMPL_T);
        bc_PushVector(self->TypeCaches, mtc);
        tp->State = tp->State | TYPE_REGISTER;
}

static void CLBC_attach_native_method(bc_ClassLoader* self, bc_ILType* ilclass,
                                      bc_Class* classz, bc_ILMethod* ilmethod,
                                      bc_Method* me) {
        //	native_method.h で、実行時にリンクするようにしたので不要
        //	me->u.NativeMethod->ref =
        //NewNativeMethodRef(class_loader_sgload_debug_NativeMethod);
}

static void CLBC_debug_native_method(bc_Method* parent, bc_Frame* fr,
                                     bc_Enviroment* env) {}

static void CLBC_check_superclass(bc_Class* cls) {
        bc_Class* objClass = BC_TYPE_OBJECT->Kind.Class;
        if (cls != objClass) {
                if (cls->SuperClass == NULL) {
                        cls->SuperClass = BC_GENERIC_OBJECT;
                }
        }
}

static bc_Type* CLBC_get_or_load_enum(bc_Namespace* parent, bc_ILType* iltype) {
        bc_Class* outClass = NULL;
        bc_Type* tp = bc_FindTypeFromNamespace(parent, iltype->Kind.Enum->Name);
        if (tp == NULL) {
                outClass = bc_NewClass(iltype->Kind.Enum->Name);
                outClass->Location = parent;
                tp = bc_WrapClass(outClass);
                bc_AddTypeNamespace(parent, tp);
        } else {
                outClass = tp->Kind.Class;
        }
        return tp;
}

static bc_Type* CLBC_get_or_load_class(bc_ClassLoader* self,
                                       bc_Namespace* parent,
                                       bc_ILType* iltype) {
        bc_Type* tp =
            bc_FindTypeFromNamespace(parent, iltype->Kind.Class->Name);
        bc_Class* outClass = NULL;
        //取得できなかった
        if (tp == NULL) {
                outClass = bc_NewClass(iltype->Kind.Class->Name);
                tp = bc_WrapClass(outClass);
                CLBC_register_class(self, parent, iltype, tp, outClass);
                bc_CL_ERROR_RET(self, tp);
        } else {
                outClass = tp->Kind.Class;
                if ((tp->State & TYPE_REGISTER) == 0) {
                        //もしネイティブメソッドのために
                        //既に登録されていたならここが型変数がNULLになってしまう
                        bc_DupTypeParameterList(
                            iltype->Kind.Class->TypeParameters,
                            outClass->TypeParameters);
                }
        }
        return tp;
}

static void CLBC_register_class(bc_ClassLoader* self, bc_Namespace* parent,
                                bc_ILType* iltype, bc_Type* tp, bc_Class* cls) {
        bc_InitGenericSelf(tp, iltype->Kind.Class->TypeParameters->Length);
        bc_DupTypeParameterList(iltype->Kind.Class->TypeParameters,
                                cls->TypeParameters);
        bc_CallContext* cctx = bc_NewCallContext(CALL_DECL_T);
        cctx->Scope = parent;
        cctx->Ty = tp;
        for (int i = 0; i < iltype->Kind.Class->Extends->Length; i++) {
                bc_GenericCache* e = (bc_GenericCache*)bc_AtVector(
                    iltype->Kind.Class->Extends, i);
                //最初の一つはクラスでもインターフェースでもよい
                if (i == 0) {
                        bc_GenericType* gtp =
                            bc_ResolveImportManager(parent, e, cctx);
                        assert(gtp != NULL);
                        if (gtp->CoreType->Tag == TYPE_CLASS_T) {
                                cls->SuperClass = gtp;
                        } else if (gtp->CoreType->Tag == TYPE_INTERFACE_T) {
                                bc_PushVector(cls->Implements, gtp);
                        } else
                                assert(false);
                        //二つ目以降はインターフェースのみ
                } else {
                        bc_GenericType* gtp =
                            bc_ResolveImportManager(parent, e, cctx);
                        bc_Type* E = bc_GENERIC2TYPE(gtp);
#if defined(DEBUG)
                        const char* Estr = bc_Ref2Str(bc_GetTypeName(E));
#endif
                        bc_PushVector(cls->Implements, gtp);
                        if (E->Tag != TYPE_INTERFACE_T) {
                                bc_Panic(BCERROR_CLASS_FIRST_T,
                                         bc_Ref2Str(bc_GetTypeName(tp)));
                                bc_AddTypeNamespace(parent, tp);
                                bc_DeleteCallContext(cctx);
                                return;
                        }
                }
        }
        bc_DeleteCallContext(cctx);
        cls->Location = parent;
        bc_AddTypeNamespace(parent, tp);
        //重複するインターフェイスを検出
        bc_Interface* inter = NULL;
        if ((inter = bc_IsValidInterface(tp))) {
                bc_Panic(BCERROR_MULTI_EQINTERFACE_T, bc_Ref2Str(inter->Name));
        }
}

static bc_Type* CLBC_get_or_load_interface(bc_ClassLoader* self,
                                           bc_Namespace* parent,
                                           bc_ILType* iltype) {
        bc_Type* tp =
            bc_FindTypeFromNamespace(parent, iltype->Kind.Interface->Name);
        bc_Interface* inter = NULL;
        if (tp == NULL) {
                inter = bc_NewInterface(iltype->Kind.Interface->Name);
                tp = bc_WrapInterface(inter);
                CLBC_register_interface(self, parent, iltype, tp, inter);
                bc_CL_ERROR_RET(self, tp);
        } else {
                inter = tp->Kind.Interface;
                if ((tp->State & TYPE_REGISTER) == 0) {
                        //もしネイティブメソッドのために
                        //既に登録されていたならここが型変数がNULLになってしまう
                        bc_DupTypeParameterList(
                            bc_GetTypeParametersILType(iltype),
                            inter->TypeParameters);
                }
        }
        return tp;
}

static void CLBC_register_interface(bc_ClassLoader* self, bc_Namespace* parent,
                                    bc_ILType* iltype, bc_Type* tp,
                                    bc_Interface* inter) {
        bc_InitGenericSelf(tp, iltype->Kind.Interface->TypeParameters->Length);
        bc_DupTypeParameterList(iltype->Kind.Interface->TypeParameters,
                                inter->TypeParameters);
        bc_CallContext* cctx = bc_NewCallContext(CALL_DECL_T);
        cctx->Scope = parent;
        cctx->Ty = tp;
        for (int i = 0; i < iltype->Kind.Interface->Extends->Length; i++) {
                bc_GenericCache* e = (bc_GenericCache*)bc_AtVector(
                    iltype->Kind.Interface->Extends, i);
                //インターフェースはインターフェースのみ継承
                bc_GenericType* gtp = bc_ResolveImportManager(parent, e, cctx);
                bc_Type* E = bc_GENERIC2TYPE(gtp);
                if (E->Tag != TYPE_INTERFACE_T) {
                        bc_Panic(BCERROR_INTERFACE_ONLY_T,
                                 bc_Ref2Str(bc_GetTypeName(tp)));
                        bc_AddTypeNamespace(parent, tp);
                        bc_DeleteCallContext(cctx);
                        return;
                        //インターフェイスの時のみ追加
                } else {
                        bc_PushVector(inter->Implements, gtp);
                }
        }
        //場所を設定
        inter->Location = parent;
        bc_DeleteCallContext(cctx);
        bc_AddTypeNamespace(parent, tp);
        //重複するインターフェイスを検出
        bc_Interface* ovinter = NULL;
        if ((ovinter = bc_IsValidInterface(tp))) {
                bc_Panic(BCERROR_MULTI_EQINTERFACE_T,
                         bc_Ref2Str(ovinter->Name));
        }
}