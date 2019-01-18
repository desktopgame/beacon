#include "class_loader_bc.h"
#include <glib.h>
#include "../env/script_context.h"
#include "../env/type_cache.h"
#include "../env/type_impl.h"
#include "../env/type_parameter.h"
#include "../error.h"
#include "../il/il_method.h"
#include "../il/il_namespace.h"
#include "../il/il_type_impl.h"
#include "class_loader.h"
#include "type_impl.h"

static void load_namespace_tree(bc_ClassLoader* self);
static void load_namespace_list(bc_ClassLoader* self,
                                bc_Vector* ilNamespacelist,
                                bc_Namespace* parent);
static void load_namespace(bc_ClassLoader* self, bc_ILNamespace* ilnamespace,
                           bc_Namespace* parent);
static void load_type_list(bc_ClassLoader* self, bc_Vector* iltype_list,
                           bc_Namespace* parent);
static void load_enum(bc_ClassLoader* self, bc_ILType* iltype,
                      bc_Namespace* parent);
static void load_class(bc_ClassLoader* self, bc_ILType* iltype,
                       bc_Namespace* parent);
static void load_interface(bc_ClassLoader* self, bc_ILType* iltype,
                           bc_Namespace* parent);
static void load_attach_native_method(bc_ClassLoader* self, bc_ILType* iltype,
                                      bc_Class* classz, bc_ILMethod* ilmethod,
                                      bc_Method* me);
static void load_debug_native_method(bc_Method* parent, bc_Frame* fr,
                                     bc_Enviroment* env);
static void load_check_superclass(bc_Class* cls);
static bc_Type* load_get_or_load_enum(bc_Namespace* parent, bc_ILType* iltype);
static bc_Type* load_get_or_load_class(bc_ClassLoader* self,
                                       bc_Namespace* parent, bc_ILType* iltype);
static void load_register_class(bc_ClassLoader* self, bc_Namespace* parent,
                                bc_ILType* iltype, bc_Type* tp, bc_Class* cls);
static bc_Type* load_get_or_load_interface(bc_ClassLoader* self,
                                           bc_Namespace* parent,
                                           bc_ILType* iltype);
static void load_register_interface(bc_ClassLoader* self, bc_Namespace* parent,
                                    bc_ILType* iltype, bc_Type* tp,
                                    bc_Interface* inter);

void bc_LoadIL(bc_ClassLoader* self) {
        bc_CL_ERROR(self);
        bc_ScriptContext* ctx = bc_GetScriptContext();
        bc_ILToplevel* iltop = self->ILCode;
        CLBC_import(self, self->ILCode->ImportList);
        load_namespace_tree(self);
}

void bc_SpecialLoadIL(bc_ClassLoader* self) {
        bc_CL_ERROR(self);
        bc_ScriptContext* ctx = bc_GetScriptContext();
        bc_ILToplevel* iltop = self->ILCode;
        //	CLBC_import(self, self->ILCode->import_list);
        load_namespace_tree(self);
}

// private
static void load_namespace_tree(bc_ClassLoader* self) {
        bc_CL_ERROR(self);
        load_namespace_list(self, self->ILCode->NamespaceList, NULL);
}

static void load_namespace_list(bc_ClassLoader* self,
                                bc_Vector* ilNamespacelist,
                                bc_Namespace* parent) {
        // self->link = classlink_resume;
        bc_CL_ERROR(self);
        for (int i = 0; i < ilNamespacelist->Length; i++) {
                bc_VectorItem e = bc_AtVector(ilNamespacelist, i);
                bc_ILNamespace* iln = (bc_ILNamespace*)e;
                load_namespace(self, iln, parent);
                bc_CL_ERROR(self);
        }
}

static void load_namespace(bc_ClassLoader* self, bc_ILNamespace* ilnamespace,
                           bc_Namespace* parent) {
        bc_CL_ERROR(self);
        bc_Namespace* current = NULL;
        if (parent == NULL) {
                current = bc_CreateNamespaceAtRoot(NULL, ilnamespace->Name);
        } else {
                current = bc_AddNamespaceNamespace(parent, ilnamespace->Name);
        }
        load_namespace_list(self, ilnamespace->NamespaceList, current);
        load_type_list(self, ilnamespace->TypeList, current);
}

static void load_type_list(bc_ClassLoader* self, bc_Vector* iltype_list,
                           bc_Namespace* parent) {
        bc_CL_ERROR(self);
        for (int i = 0; i < iltype_list->Length; i++) {
                bc_VectorItem e = bc_AtVector(iltype_list, i);
                bc_ILType* ilt = (bc_ILType*)e;
                if (ilt->Tag == ILTYPE_CLASS_T) {
                        load_class(self, ilt, parent);
                } else if (ilt->Tag == ILTYPE_INTERFACE_T) {
                        load_interface(self, ilt, parent);
                } else if (ilt->Tag == ILTYPE_ENUM_T) {
                        load_enum(self, ilt, parent);
                }
                bc_CL_ERROR(self);
        }
}

static void load_enum(bc_ClassLoader* self, bc_ILType* iltype,
                      bc_Namespace* parent) {
        bc_CL_ERROR(self);
        assert(iltype->Tag == ILTYPE_ENUM_T);
        bc_ILEnum* ilenum = iltype->Kind.Enum;
        bc_Type* tp = load_get_or_load_enum(parent, iltype);
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

static void load_class(bc_ClassLoader* self, bc_ILType* iltype,
                       bc_Namespace* parent) {
        bc_CL_ERROR(self);
        //既に登録されていたら二重に登録しないように
        //例えば、ネイティブメソッドを登録するために一時的にクラスが登録されている場合がある
        assert(iltype->Tag == ILTYPE_CLASS_T);
        bc_Type* tp = load_get_or_load_class(self, parent, iltype);
        bc_CL_ERROR(self);
        bc_Class* cls = BC_TYPE2CLASS(tp);
        if ((tp->State & TYPE_REGISTER) > 0) {
                return;
        }
        cls->IsAbstract = iltype->Kind.Class->IsAbstract;
        bc_InitGenericSelf(tp, iltype->Kind.Class->TypeParameters->Length);
        //デフォルトで親に Object を持つように
        load_check_superclass(cls);
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

static void load_interface(bc_ClassLoader* self, bc_ILType* iltype,
                           bc_Namespace* parent) {
        bc_CL_ERROR(self);
        assert(iltype->Tag == ILTYPE_INTERFACE_T);
        // NOTE:後で親関数から渡すようにする
        bc_Type* tp = load_get_or_load_interface(self, parent, iltype);
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

static void load_attach_native_method(bc_ClassLoader* self, bc_ILType* ilclass,
                                      bc_Class* classz, bc_ILMethod* ilmethod,
                                      bc_Method* me) {
        //	native_method.h で、実行時にリンクするようにしたので不要
        //	me->u.NativeMethod->ref =
        // NewNativeMethodRef(class_loader_sgload_debug_NativeMethod);
}

static void load_debug_native_method(bc_Method* parent, bc_Frame* fr,
                                     bc_Enviroment* env) {}

static void load_check_superclass(bc_Class* cls) {
        bc_Class* objClass = BC_TYPE_OBJECT->Kind.Class;
        if (cls != objClass) {
                if (cls->SuperClass == NULL) {
                        cls->SuperClass = BC_GENERIC_OBJECT;
                }
        }
}

static bc_Type* load_get_or_load_enum(bc_Namespace* parent, bc_ILType* iltype) {
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

static bc_Type* load_get_or_load_class(bc_ClassLoader* self,
                                       bc_Namespace* parent,
                                       bc_ILType* iltype) {
        bc_Type* tp =
            bc_FindTypeFromNamespace(parent, iltype->Kind.Class->Name);
        bc_Class* outClass = NULL;
        //取得できなかった
        if (tp == NULL) {
                outClass = bc_NewClass(iltype->Kind.Class->Name);
                tp = bc_WrapClass(outClass);
                load_register_class(self, parent, iltype, tp, outClass);
                bc_CL_ERROR_RET(self, tp);
        } else if (tp->State == TYPE_PENDING) {
                outClass = tp->Kind.Class;
                load_register_class(self, parent, iltype, tp, outClass);
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

static void load_register_class(bc_ClassLoader* self, bc_Namespace* parent,
                                bc_ILType* iltype, bc_Type* tp, bc_Class* cls) {
        g_message("Class.Register:%s", bc_Ref2Str(cls->Name));
        bc_InitGenericSelf(tp, iltype->Kind.Class->TypeParameters->Length);
        bc_DupTypeParameterList(iltype->Kind.Class->TypeParameters,
                                cls->TypeParameters);
        bc_CallContext* cctx = bc_NewNameContext(parent, tp);
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
        if (tp->State != TYPE_PENDING) {
                bc_AddTypeNamespace(parent, tp);
        }
        //重複するインターフェイスを検出
        bc_Interface* inter = NULL;
        if ((inter = bc_IsValidInterface(tp))) {
                bc_Panic(BCERROR_MULTI_EQINTERFACE_T, bc_Ref2Str(inter->Name));
        }
}

static bc_Type* load_get_or_load_interface(bc_ClassLoader* self,
                                           bc_Namespace* parent,
                                           bc_ILType* iltype) {
        bc_Type* tp =
            bc_FindTypeFromNamespace(parent, iltype->Kind.Interface->Name);
        bc_Interface* inter = NULL;
        if (tp == NULL) {
                inter = bc_NewInterface(iltype->Kind.Interface->Name);
                tp = bc_WrapInterface(inter);
                load_register_interface(self, parent, iltype, tp, inter);
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

static void load_register_interface(bc_ClassLoader* self, bc_Namespace* parent,
                                    bc_ILType* iltype, bc_Type* tp,
                                    bc_Interface* inter) {
        g_message("Interface.Register:%s", bc_Ref2Str(inter->Name));
        bc_InitGenericSelf(tp, iltype->Kind.Interface->TypeParameters->Length);
        bc_DupTypeParameterList(iltype->Kind.Interface->TypeParameters,
                                inter->TypeParameters);
        bc_CallContext* cctx = bc_NewNameContext(parent, tp);
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