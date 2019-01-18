#include "class_loader_link_impl.h"
#include <assert.h>
#include <glib.h>
#include "../../env/constructor.h"
#include "../../env/object.h"
#include "../../env/property.h"
#include "../../error.h"
#include "../../il/il_TYPE_IMPL.h"
#include "../../util/text.h"
#include "../TYPE_IMPL.h"
#include "../field.h"
#include "../type_cache.h"
#include "class_loader_bcload_import_module_impl.h"
#include "class_loader_bcload_member_module_impl.h"

static void CLBC_class_decl(bc_ClassLoader* self, bc_ILType* iltype,
                            bc_Type* tp, bc_Namespace* scope);
static void CLBC_class_impl(bc_ClassLoader* self, bc_ILType* iltype,
                            bc_Type* tp, bc_Namespace* scope);

static void CLBC_interface_decl(bc_ClassLoader* self, bc_ILType* iltype,
                                bc_Type* tp, bc_Namespace* scope);
static void CLBC_interface_impl(bc_ClassLoader* self, bc_ILType* iltype,
                                bc_Type* tp, bc_Namespace* scope);

static void CLBC_enum_decl(bc_ClassLoader* self, bc_ILType* iltype, bc_Type* tp,
                           bc_Namespace* scope);
static void CLBC_enum_impl(bc_ClassLoader* self, bc_ILType* iltype, bc_Type* tp,
                           bc_Namespace* scope);

static void CLBC_excec_class_decl(bc_ClassLoader* self);
static void CLBC_excec_class_impl(bc_ClassLoader* self);
static void CLBC_excec_interface_decl(bc_ClassLoader* self);
static void CLBC_excec_interface_impl(bc_ClassLoader* self);
static void CLBC_excec_enum_decl(bc_ClassLoader* self);
static void CLBC_excec_enum_impl(bc_ClassLoader* self);
static void CLBC_check_class(bc_ClassLoader* self, bc_ILType* iltype,
                             bc_Type* tp, bc_Namespace* scope);
static void CLBC_check_interface(bc_ClassLoader* self, bc_ILType* iltype,
                                 bc_Type* tp, bc_Namespace* scope);

void LinkClassLoader(bc_ClassLoader* self, bc_LinkType type) {
        bc_CL_ERROR(self);
        bc_SetPanicFile(self->FileName);
        if (type == LINK_DECL_T) {
                CLBC_excec_class_decl(self);
                bc_CL_ERROR(self);
                CLBC_excec_interface_decl(self);
                bc_CL_ERROR(self);
                CLBC_excec_enum_decl(self);
        } else if (type == LINK_IMPL_T) {
                CLBC_excec_class_impl(self);
                bc_CL_ERROR(self);
                CLBC_excec_interface_impl(self);
                bc_CL_ERROR(self);
                CLBC_excec_enum_impl(self);
        } else
                assert(false);
}

// private
static void CLBC_class_decl(bc_ClassLoader* self, bc_ILType* iltype,
                            bc_Type* tp, bc_Namespace* scope) {
        if ((tp->State & TYPE_DECL) > 0) {
                return;
        }
#if defined(DEBUG)
        const char* name = bc_Ref2Str(bc_GetTypeName(tp));
#endif
        bc_CL_ERROR(self);
        g_message("Class.Decl:%s", bc_Ref2Str(bc_GetTypeName(tp)));
        CLBC_fields_decl(self, iltype, tp, iltype->Kind.Class->Fields, scope);
        CLBC_fields_decl(self, iltype, tp, iltype->Kind.Class->StaticFields,
                         scope);
        bc_CL_ERROR(self);
        CLBC_properties_decl(self, iltype, tp, iltype->Kind.Class->Properties,
                             scope);
        CLBC_properties_decl(self, iltype, tp,
                             iltype->Kind.Class->StaticProperties, scope);
        bc_CL_ERROR(self);

        CLBC_methods_decl(self, iltype, tp, iltype->Kind.Class->Methods, scope);
        CLBC_methods_decl(self, iltype, tp, iltype->Kind.Class->StaticMethods,
                          scope);
        bc_CL_ERROR(self);

        CLBC_ctors_decl(self, iltype, tp, scope);
        bc_CL_ERROR(self);

        CLBC_operator_overloads_decl(self, iltype, tp, scope);
        bc_CL_ERROR(self);

        bc_CL_ERROR(self);
        tp->State = tp->State | TYPE_DECL;
}

static void CLBC_class_impl(bc_ClassLoader* self, bc_ILType* iltype,
                            bc_Type* tp, bc_Namespace* scope) {
        if ((tp->State & TYPE_IMPL) > 0) {
                return;
        }
#if defined(DEBUG)
        const char* tyname = bc_Ref2Str(bc_GetTypeName(tp));
#endif
        g_message("Class.Impl:%s", bc_Ref2Str(bc_GetTypeName(tp)));
        bc_CreateVTableClass(tp->Kind.Class);
        bc_CreateOperatorVTClass(tp->Kind.Class);
        bc_CL_ERROR(self);
        CLBC_fields_impl(self, scope, tp, iltype->Kind.Class->Fields,
                         (BC_TYPE2CLASS(tp))->Fields);
        CLBC_fields_impl(self, scope, tp, iltype->Kind.Class->StaticFields,
                         (BC_TYPE2CLASS(tp))->StaticFields);
        bc_CL_ERROR(self);
        CLBC_properties_impl(self, iltype, tp, iltype->Kind.Class->Properties,
                             tp->Kind.Class->Properties, scope);
        CLBC_properties_impl(self, iltype, tp,
                             iltype->Kind.Class->StaticProperties,
                             tp->Kind.Class->StaticProperties, scope);
        bc_CL_ERROR(self);

        CLBC_methods_impl(self, scope, iltype, tp, iltype->Kind.Class->Methods,
                          ((BC_TYPE2CLASS(tp))->Methods));
        CLBC_methods_impl(self, scope, iltype, tp,
                          iltype->Kind.Class->StaticMethods,
                          ((BC_TYPE2CLASS(tp))->StaticMethods));
        bc_CL_ERROR(self);

        CLBC_ctors_impl(self, iltype, tp);
        bc_CL_ERROR(self);

        CLBC_operator_overloads_impl(self, iltype, tp, scope);
        bc_CL_ERROR(self);
        tp->State = tp->State | TYPE_IMPL;
        CLBC_check_class(self, iltype, tp, scope);
}

static void CLBC_interface_decl(bc_ClassLoader* self, bc_ILType* iltype,
                                bc_Type* tp, bc_Namespace* scope) {
        if ((tp->State & TYPE_DECL) > 0) {
                return;
        }
        g_message("Interface.Decl:%s", bc_Ref2Str(bc_GetTypeName(tp)));
        assert(tp->Kind.Interface->Methods->Length == 0);
        bc_CL_ERROR(self);
        CLBC_methods_decl(self, iltype, tp, iltype->Kind.Interface->Methods,
                          scope);
        CLBC_properties_decl(self, iltype, tp,
                             iltype->Kind.Interface->Properties, scope);
        // privateなメンバーは定義できない
        for (int i = 0; i < tp->Kind.Interface->Methods->Length; i++) {
                bc_Method* e = bc_AtVector(tp->Kind.Interface->Methods, i);
                if (BC_MEMBER_ACCESS(e) == ACCESS_PRIVATE_T) {
                        bc_Panic(BCERROR_INTERFACE_HAS_PRIVATE_MEMBER_T,
                                 bc_Ref2Str(bc_GetTypeName(tp)),
                                 bc_Ref2Str(e->Name));
                }
        }
        for (int i = 0; i < tp->Kind.Interface->Properties->Length; i++) {
                bc_Property* e = bc_AtVector(tp->Kind.Interface->Properties, i);
                if (BC_MEMBER_ACCESS(e) == ACCESS_PRIVATE_T) {
                        bc_Panic(BCERROR_INTERFACE_HAS_PRIVATE_MEMBER_T,
                                 bc_Ref2Str(bc_GetTypeName(tp)),
                                 bc_Ref2Str(e->Name));
                }
        }
        bc_CL_ERROR(self);
        bc_CreateVTableInterface(tp->Kind.Interface);
        tp->State = tp->State | TYPE_DECL;
        CLBC_check_interface(self, iltype, tp, scope);
}

static void CLBC_interface_impl(bc_ClassLoader* self, bc_ILType* iltype,
                                bc_Type* tp, bc_Namespace* scope) {
        if ((tp->State & TYPE_IMPL) > 0) {
                return;
        }
        g_message("Interface.Impl:%s", bc_Ref2Str(bc_GetTypeName(tp)));
        bc_CL_ERROR(self);
        CLBC_methods_impl(self, scope, iltype, tp,
                          iltype->Kind.Interface->Methods,
                          tp->Kind.Interface->Methods);
        tp->State = tp->State | TYPE_IMPL;
}

static void CLBC_enum_decl(bc_ClassLoader* self, bc_ILType* iltype, bc_Type* tp,
                           bc_Namespace* scope) {
        if ((tp->State & TYPE_DECL) > 0) {
                return;
        }
        //重複するフィールドを確認する
        bc_Field* outField = NULL;
        if ((tp->Tag == TYPE_ENUM_T || tp->Tag == TYPE_CLASS_T) &&
            !bc_IsValidFieldClass(tp->Kind.Class, &outField)) {
                bc_Panic(BCERROR_OVERWRAP_FIELD_NAME_T,
                         bc_Ref2Str(tp->Kind.Class->Name),
                         bc_Ref2Str(outField->Name));
        }
        tp->State = tp->State | TYPE_DECL;
}

static void CLBC_enum_impl(bc_ClassLoader* self, bc_ILType* iltype, bc_Type* tp,
                           bc_Namespace* scope) {
        if ((tp->State & TYPE_IMPL) > 0) {
                return;
        }
        for (int i = 0; i < tp->Kind.Class->StaticFields->Length; i++) {
                bc_Field* f = bc_AtVector(tp->Kind.Class->StaticFields, i);
                f->StaticValue = bc_GetIntObject(i);
        }
        tp->State = tp->State | TYPE_IMPL;
}

static void CLBC_excec_class_decl(bc_ClassLoader* self) {
        bc_CL_ERROR(self);
        int count = 0;
        for (int i = 0; i < self->TypeCaches->Length; i++) {
                bc_TypeCache* e =
                    (bc_TypeCache*)bc_AtVector(self->TypeCaches, i);
                if (e->Kind != CACHEKIND_CLASS_DECL_T || e->IsConsume) {
                        continue;
                }
                count++;
                e->IsConsume = true;
                CLBC_class_decl(e->Context, e->ILType, e->Type, e->Scope);
        }
}

static void CLBC_excec_class_impl(bc_ClassLoader* self) {
        int count = 0;
        for (int i = 0; i < self->TypeCaches->Length; i++) {
                bc_TypeCache* e =
                    (bc_TypeCache*)bc_AtVector(self->TypeCaches, i);
                if (e->Kind != CACHEKIND_CLASS_IMPL_T || e->IsConsume) {
                        continue;
                }
                count++;
                e->IsConsume = true;
                CLBC_class_impl(e->Context, e->ILType, e->Type, e->Scope);
        }
}

static void CLBC_excec_interface_decl(bc_ClassLoader* self) {
        bc_CL_ERROR(self);
        int count = 0;
        for (int i = 0; i < self->TypeCaches->Length; i++) {
                bc_TypeCache* e =
                    (bc_TypeCache*)bc_AtVector(self->TypeCaches, i);
                if (e->Kind != CACHEKIND_INTERFACE_DECL_T || e->IsConsume) {
                        continue;
                }
                count++;
                e->IsConsume = true;
                CLBC_interface_decl(e->Context, e->ILType, e->Type, e->Scope);
        }
}

static void CLBC_excec_interface_impl(bc_ClassLoader* self) {
        bc_CL_ERROR(self);
        int count = 0;
        for (int i = 0; i < self->TypeCaches->Length; i++) {
                bc_TypeCache* e =
                    (bc_TypeCache*)bc_AtVector(self->TypeCaches, i);
                if (e->Kind != CACHEKIND_INTERFACE_IMPL_T || e->IsConsume) {
                        continue;
                }
                count++;
                e->IsConsume = true;
                CLBC_interface_impl(e->Context, e->ILType, e->Type, e->Scope);
        }
}

static void CLBC_excec_enum_decl(bc_ClassLoader* self) {
        bc_CL_ERROR(self);
        int count = 0;
        for (int i = 0; i < self->TypeCaches->Length; i++) {
                bc_TypeCache* e =
                    (bc_TypeCache*)bc_AtVector(self->TypeCaches, i);
                if (e->Kind != CACHEKIND_ENUM_DECL_T || e->IsConsume) {
                        continue;
                }
                count++;
                e->IsConsume = true;
                CLBC_enum_decl(e->Context, e->ILType, e->Type, e->Scope);
        }
}

static void CLBC_excec_enum_impl(bc_ClassLoader* self) {
        bc_CL_ERROR(self);
        int count = 0;
        for (int i = 0; i < self->TypeCaches->Length; i++) {
                bc_TypeCache* e =
                    (bc_TypeCache*)bc_AtVector(self->TypeCaches, i);
                if (e->Kind != CACHEKIND_ENUM_IMPL_T || e->IsConsume) {
                        continue;
                }
                count++;
                e->IsConsume = true;
                CLBC_enum_impl(e->Context, e->ILType, e->Type, e->Scope);
        }
}

static void CLBC_check_class(bc_ClassLoader* self, bc_ILType* iltype,
                             bc_Type* tp, bc_Namespace* scope) {
        //実装されていないインターフェイスを確認する
        bc_Method* outiMethod = NULL;
        if (tp->Tag == TYPE_CLASS_T && !bc_IsImplementInterfaceMethodValidClass(
                                           BC_TYPE2CLASS(tp), &outiMethod)) {
                bc_Panic(BCERROR_NOT_IMPLEMENT_INTERFACE_T,
                         bc_Ref2Str(tp->Kind.Class->Name),
                         bc_Ref2Str(outiMethod->Name));
                return;
        }
        //実装されていないプロパティを確認する
        bc_Property* outiProperty = NULL;
        if (tp->Tag == TYPE_CLASS_T &&
            !bc_IsImplementInterfacePropertyValidClass(BC_TYPE2CLASS(tp),
                                                       &outiProperty)) {
                bc_Panic(BCERROR_NOT_IMPLEMENT_ABSTRACT_METHOD_T,
                         bc_Ref2Str(tp->Kind.Class->Name),
                         bc_Ref2Str(outiProperty->Name));
                return;
        }
        //実装されていない抽象メソッドを確認する
        bc_Method* outaMethod = NULL;
        if (tp->Tag == TYPE_CLASS_T && !bc_IsImplementAbstractClassValidClass(
                                           BC_TYPE2CLASS(tp), &outaMethod)) {
                bc_Panic(BCERROR_NOT_IMPLEMENT_ABSTRACT_METHOD_T,
                         bc_Ref2Str(tp->Kind.Class->Name),
                         bc_Ref2Str(outaMethod->Name));
                return;
        }
        //重複するプロパティを確認する
        bc_Property* outProp = NULL;
        if (!bc_IsValidPropertyClass(tp->Kind.Class, &outProp)) {
                bc_Panic(BCERROR_OVERWRAP_PROPERTY_NAME_T,
                         bc_Ref2Str(tp->Kind.Class->Name),
                         bc_Ref2Str(outProp->Name));
                return;
        }
        //重複するフィールドを確認する
        bc_Field* outField = NULL;
        if (!bc_IsValidFieldClass(tp->Kind.Class, &outField)) {
                bc_Panic(BCERROR_OVERWRAP_FIELD_NAME_T,
                         bc_Ref2Str(tp->Kind.Class->Name),
                         bc_Ref2Str(outField->Name));
                return;
        }
        //メソッドの重複するパラメータ名を検出する
        bc_Method* out_overwrap_m = NULL;
        bc_StringView out_overwrap_mname;
        if (!bc_IsMethodParameterValidClass(tp->Kind.Class, &out_overwrap_m,
                                            &out_overwrap_mname)) {
                bc_Panic(BCERROR_OVERWRAP_PARAMETER_NAME_T,
                         bc_Ref2Str(bc_GetTypeName(tp)),
                         bc_Ref2Str(out_overwrap_m->Name),
                         bc_Ref2Str(out_overwrap_mname));
                return;
        }
        //コンストラクタの重複するパラメータ名を検出する
        bc_Constructor* out_overwrap_c = NULL;
        bc_StringView out_overwrap_cname;
        if (!bc_IsConstructorParameterValidClass(
                tp->Kind.Class, &out_overwrap_c, &out_overwrap_cname)) {
                bc_Panic(BCERROR_OVERWRAP_PARAMETER_NAME_T,
                         bc_Ref2Str(bc_GetTypeName(tp)), "new",
                         bc_Ref2Str(out_overwrap_cname));
                return;
        }
        //クラスの重複する型パラメータ名を検出する
        bc_StringView out_overwrap_tpname;
        if (!bc_IsTypeParameterValidClass(tp->Kind.Class,
                                          &out_overwrap_tpname)) {
                bc_Panic(BCERROR_OVERWRAP_TYPE_TYPE_PARAMETER_NAME_T,
                         bc_Ref2Str(bc_GetTypeName(tp)),
                         bc_Ref2Str(out_overwrap_tpname));
                return;
        }
        //メソッドの重複する型パラメータ名を検出する
        bc_Method* out_overwrap_tpm = NULL;
        bc_StringView out_overwrap_tpmname;
        if (!bc_IsMethodTypeParameterValidClass(
                tp->Kind.Class, &out_overwrap_tpm, &out_overwrap_tpmname)) {
                bc_Panic(BCERROR_OVERWRAP_METHOD_TYPE_PARAMETER_NAME_T,
                         bc_Ref2Str(bc_GetTypeName(tp)),
                         bc_Ref2Str(out_overwrap_tpm->Name),
                         bc_Ref2Str(out_overwrap_tpmname));
                return;
        }
        //コンストラクタで初期化されていない final フィールドの確認
        //これはコンストラクタが生成されてからでないといけない
        bc_Class* cls = BC_TYPE2CLASS(tp);
        for (int i = 0; i < cls->Fields->Length; i++) {
                bc_Field* fi = bc_AtVector(cls->Fields, i);
                //インスタンス定数が
                //フィールドでもコンストラクタでも初期化されない
                if (!bc_IsStaticModifier(BC_MEMBER_MODIFIER(fi)) &&
                    bc_IsFinalModifier(BC_MEMBER_MODIFIER(fi)) &&
                    !fi->IsNotInitializedAtCtor) {
                        bc_Panic(
                            BCERROR_NOT_INITIAL_FIELD_NOT_INITIALIZED_AT_CTOR_T,
                            bc_Ref2Str(bc_GetTypeName(tp)),
                            bc_Ref2Str(fi->Name));
                        return;
                }
        }
}

static void CLBC_check_interface(bc_ClassLoader* self, bc_ILType* iltype,
                                 bc_Type* tp, bc_Namespace* scope) {
        //重複するパラメータ名を検出する
        bc_Method* out_overwrap_m = NULL;
        bc_StringView out_overwrap_name;
        if (!bc_IsMethodParameterValidInterface(
                tp->Kind.Interface, &out_overwrap_m, &out_overwrap_name)) {
                bc_Panic(BCERROR_OVERWRAP_PARAMETER_NAME_T,
                         bc_Ref2Str(bc_GetTypeName(tp)),
                         bc_Ref2Str(out_overwrap_m->Name),
                         bc_Ref2Str(out_overwrap_name));
        }
        //インターフェイスの重複する型パラメータ名を検出する
        bc_StringView out_overwrap_tpname;
        if (!bc_IsTypeParameterValidInterface(tp->Kind.Interface,
                                              &out_overwrap_tpname)) {
                bc_Panic(BCERROR_OVERWRAP_TYPE_TYPE_PARAMETER_NAME_T,
                         bc_Ref2Str(bc_GetTypeName(tp)),
                         bc_Ref2Str(out_overwrap_tpname));
        }
        //メソッドの重複する型パラメータ名を検出する
        bc_Method* out_overwrap_tpm = NULL;
        bc_StringView out_overwrap_tpmname;
        if (!bc_IsMethodTypeParameterValidInterface(
                tp->Kind.Interface, &out_overwrap_tpm, &out_overwrap_tpmname)) {
                bc_Panic(BCERROR_OVERWRAP_METHOD_TYPE_PARAMETER_NAME_T,
                         bc_Ref2Str(bc_GetTypeName(tp)),
                         bc_Ref2Str(out_overwrap_tpm->Name),
                         bc_Ref2Str(out_overwrap_tpmname));
        }
}