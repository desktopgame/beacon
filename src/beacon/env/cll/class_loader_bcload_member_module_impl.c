#include "class_loader_bcload_member_module_impl.h"
#include <assert.h>
#include <string.h>
#include "../../env/TYPE_IMPL.h"
#include "../../env/cll/class_loader_link_impl.h"
#include "../../env/constructor.h"
#include "../../env/field.h"
#include "../../env/heap.h"
#include "../../env/method.h"
#include "../../env/object.h"
#include "../../env/operator_overload.h"
#include "../../env/parameter.h"
#include "../../env/property.h"
#include "../../env/type/resolve.h"
#include "../../env/type_parameter.h"
#include "../../il/il_TYPE_IMPL.h"
#include "../../il/il_argument.h"
#include "../../il/il_constructor.h"
#include "../../il/il_constructor_chain.h"
#include "../../il/il_field.h"
#include "../../il/il_method.h"
#include "../../il/il_operator_overload.h"
#include "../../il/il_parameter.h"
#include "../../il/il_property.h"
#include "../../il/il_stmt_interface.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../vm/script_thread.h"
#include "../../vm/symbol_entry.h"
#include "class_loader_ilload_stmt_module_impl.h"

// proto
static void CLBC_parameter_list(bc_ClassLoader* self, bc_Namespace* scope,
                                bc_Vector* param_list,
                                bc_Vector* sg_param_liste,
                                bc_CallContext* cctx);
static void CLBC_parameter_list_ctor(bc_Vector* param_list);

static void CLBC_chain(bc_ClassLoader* self, bc_ILType* iltype, bc_Type* tp,
                       bc_ILConstructor* ilcons, bc_ILConstructorChain* ilchain,
                       bc_Enviroment* env);
static void CLBC_chain_root(bc_ClassLoader* self, bc_ILType* iltype,
                            bc_Type* tp, bc_ILConstructor* ilcons,
                            bc_ILConstructorChain* ilchain, bc_Enviroment* env);
static void CLBC_chain_auto(bc_ClassLoader* self, bc_ILType* iltype,
                            bc_Type* tp, bc_ILConstructor* ilcons,
                            bc_ILConstructorChain* ilchain, bc_Enviroment* env);
static void CLBC_chain_super(bc_ClassLoader* self, bc_ILType* iltype,
                             bc_Type* tp, bc_ILConstructor* ilcons,
                             bc_ILConstructorChain* ilchain,
                             bc_Enviroment* env);
static bool CLBC_test_operator_overlaod(bc_ClassLoader* self, bc_ILType* iltype,
                                        bc_Type* tp, bc_OperatorOverload* opov);

//
// field
//
//
bool CLBC_field_decl(bc_ClassLoader* self, bc_ILType* iltype, bc_Type* tp,
                     bc_ILField* ilfi, bc_Namespace* scope,
                     bc_CallContext* cctx) {
        bc_Field* fi = bc_NewField(ilfi->Name);
        g_message("    Field.Decl:%s", bc_Ref2Str(ilfi->Name));
        BC_MEMBER_ACCESS(fi) = ilfi->Access;
        BC_MEMBER_MODIFIER(fi) = ilfi->Modifier;
        BC_MEMBER_TYPE(fi) = tp;
        fi->GType = bc_ResolveImportManager(scope, ilfi->GCache, cctx);
        bc_AddFieldType(tp, fi);
        //フィールドの初期値
        fi->InitialValue = ilfi->InitialValue;
        ilfi->InitialValue = NULL;
        //フィールドの修飾子を検証
        const int errorLength = 3;
        bc_ModifierType errors[3] = {
            MODIFIER_NATIVE_T,
            MODIFIER_ABSTRACT_T,
            MODIFIER_OVERRIDE_T,
        };
        int errorIndex = -1;
        if (bc_IsIncludeModifier(BC_MEMBER_MODIFIER(fi), errorLength, errors,
                                 &errorIndex)) {
                bc_Panic(
                    BCERROR_INVALID_MODIFIER_FIELD_T,
                    bc_Ref2Str(bc_ModifierTypeToString(errors[errorIndex])),
                    bc_Ref2Str(bc_GetTypeName(tp)), bc_Ref2Str(fi->Name));
                return false;
        }
        // static finalなのに、
        //初期値が存在しない
        if (bc_IsStaticModifier(BC_MEMBER_MODIFIER(fi)) &&
            bc_IsFinalModifier(BC_MEMBER_MODIFIER(fi)) &&
            fi->InitialValue == NULL) {
                bc_Panic(BCERROR_NOT_DEFAULT_VALUE_STATIC_FINAL_FIELD_T,
                         bc_Ref2Str(bc_GetTypeName(tp)), bc_Ref2Str(fi->Name));
                return false;
        }
        return true;
}

bool CLBC_field_impl(bc_ClassLoader* self, bc_Type* tp, bc_Field* fi,
                     bc_Namespace* scope, bc_CallContext* cctx) {
        g_message("    Field.Impl:%s", bc_Ref2Str(fi->Name));
        fi->StaticValue = bc_GetDefaultObject(fi->GType);
        if (fi->InitialValue == NULL) {
                return true;
        }
        //フィールドの初期値を設定する
        bc_Enviroment* env = bc_NewEnviroment();
        env->ContextRef = self;
        fi->InitialValueEnv = env;
        bc_LoadILFactor(fi->InitialValue, env, cctx);
        bc_GenerateILFactor(fi->InitialValue, env, cctx);
        //フィールドの型と互換性がない
        bc_GenericType* gf = bc_EvalILFactor(fi->InitialValue, env, cctx);
        if (bc_CdistanceGenericType(fi->GType, gf) < 0) {
                bc_PrintGenericType(fi->GType);
                bc_Println();
                bc_PrintGenericType(gf);
                bc_Println();
                bc_Panic(
                    BCERROR_FIELD_DEFAULT_VALUE_NOT_COMPATIBLE_TO_FIELD_TYPE_T,
                    bc_Ref2Str(bc_GetTypeName(BC_MEMBER_TYPE(fi))),
                    bc_Ref2Str(fi->Name));
                return false;
        }
        //静的フィールドならついでに初期化
        //静的フィールドでものすごいでかいオブジェクトを確保すると重くなるかも
        int abtemp = bc_BeginNewRuntime();
        bc_BeginGCPending();
        if (bc_IsStaticModifier(BC_MEMBER_MODIFIER(fi))) {
                bc_Frame* f = bc_NewFrame();
                bc_SetScriptThreadFrameRef(bc_GetMainScriptThread(), f);
                bc_ExecuteVM(f, env);
                fi->StaticValue = bc_PopVector(f->ValueStack);
                bc_ReleaseScriptThreadFrameRef(bc_GetMainScriptThread());
                bc_DeleteFrame(f);
        }
        bc_EndNewRuntime(abtemp);
        bc_EndGCPending();
        return true;
}

void CLBC_fields_decl(bc_ClassLoader* self, bc_ILType* iltype, bc_Type* tp,
                      bc_Vector* ilfields, bc_Namespace* scope) {
        bc_CL_ERROR(self);
        bc_CallContext* cctx = bc_NewNameContext(scope, tp);
        for (int i = 0; i < ilfields->Length; i++) {
                if (!CLBC_field_decl(self, iltype, tp, bc_AtVector(ilfields, i),
                                     scope, cctx)) {
                        break;
                }
        }
        bc_DeleteCallContext(cctx);
}

void CLBC_fields_impl(bc_ClassLoader* self, bc_Namespace* scope, bc_Type* tp,
                      bc_Vector* ilfields, bc_Vector* sgfields) {
        bc_CL_ERROR(self);
        bc_CallContext* cctx = bc_NewCallContext(CALL_CTOR_T);
        cctx->Scope = scope;
        cctx->Ty = tp;
        for (int i = 0; i < sgfields->Length; i++) {
                if (!CLBC_field_impl(self, tp, bc_AtVector(sgfields, i), scope,
                                     cctx)) {
                        break;
                }
        }
        bc_DeleteCallContext(cctx);
}

//
// Property
//
//
bool CLBC_Property_decl(bc_ClassLoader* self, bc_ILType* iltype, bc_Type* tp,
                        bc_ILProperty* ilprop, bc_Namespace* scope,
                        bc_CallContext* cctx) {
        // VectorItem e = AtVector(ilprops, i);
        // ILProperty* ilprop = e;
        g_message("    Property.Decl:%s", bc_Ref2Str(ilprop->Name));
        bc_Property* prop = bc_NewProperty(ilprop->Name);
        BC_MEMBER_ACCESS(prop) = ilprop->Access;
        BC_MEMBER_MODIFIER(prop) = ilprop->Modifier;
        prop->Set->Access = ilprop->Set->Access;
        prop->Get->Access = ilprop->Get->Access;
        BC_MEMBER_TYPE(prop) = tp;
        prop->GType = bc_ResolveImportManager(scope, ilprop->GCache, cctx);
        prop->IsShort = ilprop->Set->IsShort && ilprop->Get->IsShort;
        bc_AddPropertyType(tp, prop);
        //プロパティの修飾子を検証
        const int errorLength = 3;
        bc_ModifierType errors[3] = {
            MODIFIER_NATIVE_T,
            MODIFIER_ABSTRACT_T,
            MODIFIER_OVERRIDE_T,
        };
        int errorIndex = -1;
        if (bc_IsIncludeModifier(BC_MEMBER_MODIFIER(prop), errorLength, errors,
                                 &errorIndex)) {
                bc_Panic(
                    BCERROR_INVALID_MODIFIER_FIELD_T,
                    bc_Ref2Str(bc_ModifierTypeToString(errors[errorIndex])),
                    bc_Ref2Str(bc_GetTypeName(tp)), bc_Ref2Str(prop->Name));
                bc_DeleteCallContext(cctx);
                return false;
        }
        //プロパティアクセサの方がプロパティよりも緩いアクセスになっている
        if (bc_IsWeakAccess(ilprop->Access, ilprop->Set->Access) ||
            bc_IsWeakAccess(ilprop->Access, ilprop->Get->Access)) {
                bc_Panic(BCERROR_INVALID_ACCESS_LEVEL_OF_PROPERTY_T,
                         bc_Ref2Str(bc_GetTypeName(tp)),
                         bc_Ref2Str(ilprop->Name));
                return false;
        }
        //二つのアクセサがどちらもプロパティと異なるアクセスレベル
        if ((ilprop->Access != ilprop->Set->Access) &&
            ilprop->Access != ilprop->Get->Access) {
                bc_Panic(BCERROR_SPECIFIED_BOTH_PROPERTY_ACCESSOR_T,
                         bc_Ref2Str(bc_GetTypeName(tp)),
                         bc_Ref2Str(ilprop->Name));
                return false;
        }
        return true;
}

bool CLBC_Property_impl(bc_ClassLoader* self, bc_ILType* iltype, bc_Type* tp,
                        bc_ILProperty* ilprop, bc_Property* prop,
                        bc_Namespace* scope, bc_CallContext* cctx) {
        // VectorItem e = AtVector(sgprops, i);
        g_message("    Property.Impl:%s", bc_Ref2Str(prop->Name));
        bc_Property* pr = prop;
        bc_ILProperty* ilpr = ilprop;
        if (pr->IsShort) {
                return true;
        }
        bc_PropertyBody* set = pr->Set;
        bc_PropertyBody* get = pr->Get;
        bc_Vector* set_stmt_list = ilpr->Set->Statements;
        bc_Vector* get_stmt_list = ilpr->Get->Statements;
        set->Env->ContextRef = self;
        get->Env->ContextRef = self;
        // setterのオペコードを生成
        bc_SymbolEntry* valueE = bc_EntrySymbolTable(
            set->Env->Symboles, pr->GType, bc_InternString("value"));
        if (!bc_IsStaticModifier(BC_MEMBER_MODIFIER(pr))) {
                bc_AddOpcodeBuf(set->Env->Bytecode, OP_STORE);
                bc_AddOpcodeBuf(set->Env->Bytecode, 0);
        }
        bc_AddOpcodeBuf(set->Env->Bytecode, OP_STORE);
        bc_AddOpcodeBuf(set->Env->Bytecode, valueE->Index);
        CLBC_body(self, set_stmt_list, set->Env, cctx, scope);
        // getterのオペコードを生成
        if (!bc_IsStaticModifier(BC_MEMBER_MODIFIER(pr))) {
                bc_AddOpcodeBuf(get->Env->Bytecode, OP_STORE);
                bc_AddOpcodeBuf(get->Env->Bytecode, 0);
        }
        CLBC_body(self, get_stmt_list, get->Env, cctx, scope);
        return true;
}

void CLBC_properties_decl(bc_ClassLoader* self, bc_ILType* iltype, bc_Type* tp,
                          bc_Vector* ilprops, bc_Namespace* scope) {
        bc_CL_ERROR(self);
        bc_CallContext* cctx = bc_NewNameContext(scope, tp);
        for (int i = 0; i < ilprops->Length; i++) {
                if (!CLBC_Property_decl(self, iltype, tp,
                                        bc_AtVector(ilprops, i), scope, cctx)) {
                        break;
                }
        }
        bc_DeleteCallContext(cctx);
}

void CLBC_properties_impl(bc_ClassLoader* self, bc_ILType* iltype, bc_Type* tp,
                          bc_Vector* ilprops, bc_Vector* sgprops,
                          bc_Namespace* scope) {
        bc_CL_ERROR(self);
        bc_CallContext* cctx = bc_NewNameContext(scope, tp);
        for (int i = 0; i < sgprops->Length; i++) {
                if (!CLBC_Property_impl(self, iltype, tp,
                                        bc_AtVector(ilprops, i),
                                        bc_AtVector(sgprops, i), scope, cctx)) {
                        break;
                }
        }
        bc_DeleteCallContext(cctx);
}

//
// method
//
//
bool CLBC_method_decl(bc_ClassLoader* self, bc_ILType* iltype, bc_Type* tp,
                      bc_ILMethod* ilmt, bc_Namespace* scope) {
        g_message("    Method.Decl:%s", bc_Ref2Str(ilmt->Name));
        //メソッド一覧から取り出す
        bc_ILMethod* ilmethod = ilmt;
        //メソッドから仮引数一覧を取りだす
        bc_Vector* ilparams = ilmethod->Parameters;
        //実行時のメソッド情報を作成する
        bc_Method* method = bc_NewMethod(ilmethod->Name);
        bc_Vector* parameter_list = method->Parameters;
        method->Type = bc_IsNativeModifier(ilmethod->Modifier)
                           ? METHOD_TYPE_NATIVE_T
                           : METHOD_TYPE_SCRIPT_T;
        BC_MEMBER_TYPE(method) = tp;
        BC_MEMBER_ACCESS(method) = ilmethod->Access;
        BC_MEMBER_MODIFIER(method) = ilmethod->Modifier;
        bc_DupTypeParameterList(ilmethod->TypeParameters,
                                method->TypeParameters);
        bc_CallContext* cctx = bc_NewMethodContext(method);
        //インターフェースなら空
        if (tp->Tag == TYPE_INTERFACE_T ||
            bc_IsAbstractModifier(BC_MEMBER_MODIFIER(method))) {
                method->Type = METHOD_TYPE_ABSTRACT_T;
                method->Kind.Script = NULL;
        } else {
                if (bc_IsNativeModifier(BC_MEMBER_MODIFIER(method))) {
                        method->Kind.Native = bc_NewNativeMethod();
                } else {
                        method->Kind.Script = bc_NewScriptMethod();
                }
        }
        //メソッドが抽象メソッドだが、
        //インターフェイスでも抽象クラスでもない
        if (bc_IsAbstractModifier(BC_MEMBER_MODIFIER(method)) &&
            (tp->Tag == TYPE_CLASS_T && !BC_TYPE2CLASS(tp)->IsAbstract)) {
                bc_Panic(BCERROR_ABSTRACT_METHOD_BY_T,
                         bc_Ref2Str(method->Name));
                bc_DeleteMethod(method);
                bc_DeleteCallContext(cctx);
                return false;
        }
        //メソッドの本文が省略されているが、
        //ネイティブメソッドでも抽象メソッドでもない
        if (tp->Tag == TYPE_CLASS_T && ilmethod->IsNoStmt &&
            (!bc_IsAbstractModifier(BC_MEMBER_MODIFIER(method)) &&
             !bc_IsNativeModifier(BC_MEMBER_MODIFIER(method)))) {
                bc_Panic(BCERROR_EMPTY_STMT_METHOD_T, bc_Ref2Str(method->Name));
                bc_DeleteMethod(method);
                bc_DeleteCallContext(cctx);
                return false;
        }
        //ネイティブメソッドもしくは抽象メソッドなのに本文が書かれている
        if (tp->Tag == TYPE_CLASS_T && !ilmethod->IsNoStmt &&
            (bc_IsAbstractModifier(BC_MEMBER_MODIFIER(method)) ||
             bc_IsNativeModifier(BC_MEMBER_MODIFIER(method)))) {
                bc_Panic(BCERROR_NOT_EMPTY_STMT_METHOD_T,
                         bc_Ref2Str(method->Name));
                bc_DeleteMethod(method);
                bc_DeleteCallContext(cctx);
                return false;
        }
        //メソッドの修飾子が static override
        if (bc_IsPairIncludeModifier(BC_MEMBER_MODIFIER(method),
                                     MODIFIER_STATIC_T, MODIFIER_OVERRIDE_T)) {
                bc_Panic(
                    BCERROR_INVALID_MODIFIER_PAIR_METHOD_T,
                    bc_Ref2Str(bc_ModifierTypeToString(MODIFIER_STATIC_T)),
                    bc_Ref2Str(bc_ModifierTypeToString(MODIFIER_OVERRIDE_T)),
                    bc_Ref2Str(bc_GetTypeName(tp)), bc_Ref2Str(method->Name));
                bc_DeleteMethod(method);
                bc_DeleteCallContext(cctx);
                return false;
        }
        //.. abstract override
        if (bc_IsPairIncludeModifier(BC_MEMBER_MODIFIER(method),
                                     MODIFIER_ABSTRACT_T,
                                     MODIFIER_OVERRIDE_T)) {
                bc_Panic(
                    BCERROR_INVALID_MODIFIER_PAIR_METHOD_T,
                    bc_Ref2Str(bc_ModifierTypeToString(MODIFIER_ABSTRACT_T)),
                    bc_Ref2Str(bc_ModifierTypeToString(MODIFIER_OVERRIDE_T)),
                    bc_Ref2Str(bc_GetTypeName(tp)), bc_Ref2Str(method->Name));
                bc_DeleteMethod(method);
                bc_DeleteCallContext(cctx);
                return false;
        }
        //.. abstract static
        if (bc_IsPairIncludeModifier(BC_MEMBER_MODIFIER(method),
                                     MODIFIER_ABSTRACT_T, MODIFIER_STATIC_T)) {
                bc_Panic(
                    BCERROR_INVALID_MODIFIER_PAIR_METHOD_T,
                    bc_Ref2Str(bc_ModifierTypeToString(MODIFIER_ABSTRACT_T)),
                    bc_Ref2Str(bc_ModifierTypeToString(MODIFIER_STATIC_T)),
                    bc_Ref2Str(bc_GetTypeName(tp)), bc_Ref2Str(method->Name));
                bc_DeleteMethod(method);
                bc_DeleteCallContext(cctx);
                return false;
        }
        method->ReturnGType =
            bc_ResolveImportManager(scope, ilmethod->ReturnGCache, cctx);
        // ILパラメータを実行時パラメータへ変換
        // NOTE:ここでは戻り値の型,引数の型を設定しません
        //     class_loader_sgload_complete参照
        for (int i = 0; i < ilparams->Length; i++) {
                bc_VectorItem e = bc_AtVector(ilparams, i);
                bc_ILParameter* ilp = (bc_ILParameter*)e;
                bc_Parameter* param = bc_NewParameter(ilp->Name);
                bc_PushVector(parameter_list, param);
        }
        CLBC_parameter_list(self, scope, ilmethod->Parameters,
                            method->Parameters, cctx);
        bc_AddMethodType(tp, method);
        bc_DeleteCallContext(cctx);
        return true;
}

bool CLBC_method_impl(bc_ClassLoader* self, bc_Namespace* scope,
                      bc_ILType* iltype, bc_Type* tp, bc_ILMethod* ilmt,
                      bc_Method* mt) {
        //	VectorItem e = AtVector(sgmethods, i);
        g_message("    Method.Decl:%s", bc_Ref2Str(mt->Name));
        bc_Method* me = mt;
        bc_ILMethod* ilmethod = ilmt;
        //ネイティブメソッドならオペコードは不要
        if (me->Type == METHOD_TYPE_NATIVE_T ||
            me->Type == METHOD_TYPE_ABSTRACT_T) {
                return true;
        }
        //オペコードを作成
        // FIXME:ILメソッドと実行時メソッドのインデックスが同じなのでとりあえず動く
        //まずは仮引数の一覧にインデックスを割り振る
        bc_Enviroment* env = bc_NewEnviroment();
        env->ContextRef = self;
        bc_CallContext* cctx = bc_NewMethodContext(mt);
        //引数を保存
        for (int i = 0; i < ilmethod->Parameters->Length; i++) {
                bc_ILParameter* ilparam =
                    (bc_ILParameter*)bc_AtVector(ilmethod->Parameters, i);
                bc_EntrySymbolTable(
                    env->Symboles,
                    bc_ResolveImportManager(scope, ilparam->GCache, cctx),
                    ilparam->Name);
                //実引数を保存
                // 0番目は this のために開けておく
                bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)OP_STORE);
                bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)(i + 1));
        }
        //インスタンスメソッドなら
        // 0番目を this で埋める
        if (!bc_IsStaticModifier(BC_MEMBER_MODIFIER(me))) {
                bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)OP_STORE);
                bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)0);
        }
        CLBC_corutine(self, me, env, ilmethod->Parameters, ilmethod->Statements,
                      cctx, scope);
        bc_DeleteCallContext(cctx);
        return true;
}

void CLBC_methods_decl(bc_ClassLoader* self, bc_ILType* iltype, bc_Type* tp,
                       bc_Vector* ilmethods, bc_Namespace* scope) {
        bc_CL_ERROR(self);
        for (int i = 0; i < ilmethods->Length; i++) {
                if (!CLBC_method_decl(self, iltype, tp,
                                      bc_AtVector(ilmethods, i), scope)) {
                        break;
                }
        }
}

void CLBC_methods_impl(bc_ClassLoader* self, bc_Namespace* scope,
                       bc_ILType* iltype, bc_Type* tp, bc_Vector* ilmethods,
                       bc_Vector* sgmethods) {
        bc_CL_ERROR(self);
        for (int i = 0; i < ilmethods->Length; i++) {
                if (!CLBC_method_impl(self, scope, iltype, tp,
                                      bc_AtVector(ilmethods, i),
                                      bc_AtVector(sgmethods, i))) {
                        break;
                }
                BC_ERROR();
        }
}

//
// ctor
//
//
bool CLBC_ctor_decl(bc_ClassLoader* self, bc_ILType* iltype, bc_Type* tp,
                    bc_ILConstructor* ilcons, bc_Namespace* scope) {
        g_message("    Constructor.Decl:%d", ilcons->Parameters->Length);
        //メソッドから仮引数一覧を取りだす
        bc_Vector* ilparams = ilcons->Parameters;
        bc_Class* classz = tp->Kind.Class;
        //実行時のメソッド情報を作成する
        bc_Constructor* cons = bc_NewConstructor();
        bc_Vector* parameter_list = cons->Parameters;
        BC_MEMBER_ACCESS(cons) = ilcons->Access;
        BC_MEMBER_TYPE(cons) = tp;
        bc_CallContext* cctx = bc_NewConstructorContext(cons);
        // NOTE:ここでは戻り値の型,引数の型を設定しません
        //     class_loader_sgload_complete参照
        for (int i = 0; i < ilparams->Length; i++) {
                bc_VectorItem e = bc_AtVector(ilparams, i);
                bc_ILParameter* ilp = (bc_ILParameter*)e;
                bc_Parameter* param = bc_NewParameter(ilp->Name);
                bc_PushVector(parameter_list, param);
        }
        CLBC_parameter_list(self, scope, ilcons->Parameters, cons->Parameters,
                            cctx);
        CLBC_parameter_list_ctor(cons->Parameters);
        bc_AddConstructorClass(classz, cons);
        bc_DeleteCallContext(cctx);
        return true;
}

bool CLBC_ctor_impl(bc_ClassLoader* self, bc_ILType* iltype, bc_Type* tp,
                    bc_ILConstructor* ilcons, bc_Constructor* cons,
                    bc_Namespace* scope) {
        g_message("    Constructor.Impl:%d", ilcons->Parameters->Length);
        //仮引数に型を設定する
        // class_loader_sgload_params(self, scope, ilcons->parameter_list,
        // cons->parameter_list); まずは仮引数の一覧にインデックスを割り振る
        bc_Enviroment* env = bc_NewEnviroment();
        env->ContextRef = self;
        bc_CallContext* cctx = bc_NewConstructorContext(cons);
        for (int i = 0; i < cons->Parameters->Length; i++) {
                bc_ILParameter* ilparam =
                    (bc_ILParameter*)bc_AtVector(ilcons->Parameters, i);
                bc_EntrySymbolTable(
                    env->Symboles,
                    bc_ResolveImportManager(scope, ilparam->GCache, cctx),
                    ilparam->Name);
                //実引数を保存
                // 0番目は this のために開けておく
                bc_AddOpcodeBuf(env->Bytecode, OP_STORE);
                bc_AddOpcodeBuf(env->Bytecode, (i + 1));
        }
        CLBC_chain(self, iltype, tp, ilcons, ilcons->Chain, env);
        // NOTE:ここなら名前空間を設定出来る
        CLBC_body(self, ilcons->Statements, env, cctx, scope);
        cons->Env = env;
        bc_DeleteCallContext(cctx);
        return true;
}

void CLBC_ctors_decl(bc_ClassLoader* self, bc_ILType* iltype, bc_Type* tp,
                     bc_Namespace* scope) {
        bc_CL_ERROR(self);
        bc_Class* classz = tp->Kind.Class;
        bc_Vector* ilcons_list = iltype->Kind.Class->Constructors;
        for (int i = 0; i < ilcons_list->Length; i++) {
                if (!CLBC_ctor_decl(self, iltype, tp,
                                    bc_AtVector(ilcons_list, i), scope)) {
                        break;
                }
        }
}

void CLBC_ctors_impl(bc_ClassLoader* self, bc_ILType* iltype, bc_Type* tp) {
        bc_CL_ERROR(self);
        assert(tp->Tag == TYPE_CLASS_T);
        bc_Class* classz = tp->Kind.Class;
        bc_Namespace* scope = classz->Location;
        bc_Vector* constructors = classz->Constructors;
        if (iltype->Tag != ILTYPE_CLASS_T) {
                return;
        }
        //既に登録されたが、
        //オペコードが空っぽになっているコンストラクタの一覧
        for (int i = 0; i < constructors->Length; i++) {
                if (!CLBC_ctor_impl(
                        self, iltype, tp,
                        bc_AtVector(iltype->Kind.Class->Constructors, i),
                        bc_AtVector(constructors, i), scope)) {
                        break;
                }
        }
}

//
// operator overload
//
//
bool CLBC_operator_overload_decl(bc_ClassLoader* self, bc_ILType* iltype,
                                 bc_Type* tp, bc_ILOperatorOverload* ilopov,
                                 bc_Namespace* scope) {
        //演算子オーバーロード一覧から取り出す
        bc_OperatorOverload* opov = bc_NewOperatorOverload(ilopov->Type);
        BC_MEMBER_ACCESS(opov) = ilopov->Access;
        BC_MEMBER_TYPE(opov) = tp;
        // CallContextの設定
        bc_CallContext* cctx = bc_NewOperatorOverloadContext(opov);
        //戻り値読み込み
        opov->ReturnGType =
            bc_ResolveImportManager(scope, ilopov->ReturnGCache, cctx);
        //パラメータ読み込み
        for (int j = 0; j < ilopov->Parameters->Length; j++) {
                bc_ILParameter* ilparam = bc_AtVector(ilopov->Parameters, j);
                bc_Parameter* param = bc_NewParameter(ilparam->Name);
                bc_PushVector(opov->Parameters, param);
        }
        CLBC_parameter_list(self, scope, ilopov->Parameters, opov->Parameters,
                            cctx);
        bc_PushVector(tp->Kind.Class->OperatorOverloads, opov);
        //オペレータオーバロードの妥当性をテストする
        if (CLBC_test_operator_overlaod(self, iltype, tp, opov)) {
                bc_DeleteCallContext(cctx);
                return false;
        }
        bc_DeleteCallContext(cctx);
        return true;
}

bool CLBC_operator_overload_impl(bc_ClassLoader* self, bc_ILType* iltype,
                                 bc_Type* tp, bc_ILOperatorOverload* ilopov,
                                 bc_OperatorOverload* opov,
                                 bc_Namespace* scope) {
        //オペコードを作成
        // FIXME:ILメソッドと実行時メソッドのインデックスが同じなのでとりあえず動く
        //まずは仮引数の一覧にインデックスを割り振る
        bc_Enviroment* env = bc_NewEnviroment();
        bc_CallContext* cctx = bc_NewOperatorOverloadContext(opov);
        // ccpush_method(me);
        env->ContextRef = self;
        for (int i = 0; i < ilopov->Parameters->Length; i++) {
                bc_ILParameter* ilparam =
                    (bc_ILParameter*)bc_AtVector(ilopov->Parameters, i);
                bc_EntrySymbolTable(
                    env->Symboles,
                    bc_ResolveImportManager(scope, ilparam->GCache, cctx),
                    ilparam->Name);
                //実引数を保存
                // 0番目は this のために開けておく
                bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)OP_STORE);
                bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)(i + 1));
        }
        // 0番目をthisで埋める
        bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)OP_STORE);
        bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)0);
        // NOTE:ここなら名前空間を設定出来る
        CLBC_body(self, ilopov->Statements, env, cctx, scope);
        bc_DeleteCallContext(cctx);
        // ccpop_method();
        opov->Env = env;
        return true;
}

void CLBC_operator_overloads_decl(bc_ClassLoader* self, bc_ILType* iltype,
                                  bc_Type* tp, bc_Namespace* scope) {
        bc_CL_ERROR(self);
        bc_Vector* opov_list = iltype->Kind.Class->OperatorOverloads;
        for (int i = 0; i < opov_list->Length; i++) {
                if (!CLBC_operator_overload_decl(
                        self, iltype, tp, bc_AtVector(opov_list, i), scope)) {
                        break;
                }
        }
        // CLBC_default_operator_overload(self, tp);
}

void CLBC_operator_overloads_impl(bc_ClassLoader* self, bc_ILType* iltype,
                                  bc_Type* tp, bc_Namespace* scope) {
        bc_CL_ERROR(self);
        bc_Vector* opov_list = tp->Kind.Class->OperatorOverloads;
        //ここで暗黙的に作成される == != によって長さが合わなくなる
        for (int i = 0; i < iltype->Kind.Class->OperatorOverloads->Length;
             i++) {
                if (!CLBC_operator_overload_impl(
                        self, iltype, tp,
                        bc_AtVector(iltype->Kind.Class->OperatorOverloads, i),
                        bc_AtVector(opov_list, i), scope)) {
                        break;
                }
        }
}

bool CLBC_corutine(bc_ClassLoader* self, bc_Method* mt, bc_Enviroment* env,
                   bc_Vector* ilparams, bc_Vector* ilstmts,
                   bc_CallContext* cctx, bc_Namespace* range) {
        //戻り値が iterator なら、
        //コルーチンとして使えるようにする
        bool yield_err = false;
        if (bc_IsYieldMethod(mt, ilstmts, &yield_err)) {
                if (yield_err) {
                        bc_FatalError();
                        return false;
                }
                //メソッド名からクラス名を作成して、
                // beacon::$placeholderへ肩を格納する
                bc_Type* iterT =
                    bc_CreateIteratorTypeFromMethod(mt, self, ilstmts);
                bc_AddOpcodeBuf(env->Bytecode, OP_THIS);
                for (int i = 0; i < ilparams->Length; i++) {
                        bc_AddOpcodeBuf(env->Bytecode, OP_LOAD);
                        bc_AddOpcodeBuf(env->Bytecode, i + 1);
                }
                mt->Kind.Script->Env = env;
                bc_AddOpcodeBuf(env->Bytecode, OP_NEW_INSTANCE);
                bc_AddOpcodeBuf(env->Bytecode, iterT->AbsoluteIndex);
                bc_AddOpcodeBuf(env->Bytecode, 0);
                bc_AddOpcodeBuf(env->Bytecode, OP_RETURN);
                return true;
        }
        // NOTE:ここなら名前空間を設定出来る
        CLBC_body(self, ilstmts, env, cctx, range);
        mt->Kind.Script->Env = env;
        return true;
}

void CLBC_body(bc_ClassLoader* self, bc_Vector* stmt_list, bc_Enviroment* dest,
               bc_CallContext* cctx, bc_Namespace* range) {
        bc_CL_ERROR(self);
        //まずは全てのステートメントを読み込む
        for (int i = 0; i < stmt_list->Length; i++) {
                if (bc_GetLastPanic()) {
                        break;
                }
                bc_VectorItem e = bc_AtVector(stmt_list, i);
                bc_ILStatement* s = (bc_ILStatement*)e;
                bc_LoadILStmt(s, dest, cctx);
        }
        //オペコードを生成
        for (int i = 0; i < stmt_list->Length; i++) {
                if (bc_GetLastPanic()) {
                        break;
                }
                bc_VectorItem e = bc_AtVector(stmt_list, i);
                bc_ILStatement* s = (bc_ILStatement*)e;
                bc_GenerateILStmt(s, dest, cctx);
        }
}

// private
static void CLBC_parameter_list(bc_ClassLoader* self, bc_Namespace* scope,
                                bc_Vector* param_list, bc_Vector* sg_param_list,
                                bc_CallContext* cctx) {
        for (int j = 0; j < param_list->Length; j++) {
                bc_VectorItem e = bc_AtVector(param_list, j);
                bc_ILParameter* ilparam = (bc_ILParameter*)e;
                // FIXME:ILパラメータと実行時パラメータのインデックスが同じなのでとりあえず動く
                bc_Parameter* mep =
                    (bc_Parameter*)bc_AtVector(sg_param_list, j);
                mep->GType =
                    bc_ResolveImportManager(scope, ilparam->GCache, cctx);
        }
}

static void CLBC_parameter_list_ctor(bc_Vector* param_list) {
        for (int i = 0; i < param_list->Length; i++) {
                bc_Parameter* param = bc_AtVector(param_list, i);
                param->GType->IsCtorParameter = true;
        }
}

static void CLBC_chain(bc_ClassLoader* self, bc_ILType* iltype, bc_Type* tp,
                       bc_ILConstructor* ilcons, bc_ILConstructorChain* ilchain,
                       bc_Enviroment* env) {
        //親クラスがないなら作成
        bc_Class* classz = tp->Kind.Class;
        if (classz->SuperClass == NULL && ilcons->Chain == NULL) {
                CLBC_chain_root(self, iltype, tp, ilcons, ilchain, env);
                return;
        }
        //親クラスがあるのに連鎖がない
        if (classz->SuperClass != NULL && ilcons->Chain == NULL) {
                CLBC_chain_auto(self, iltype, tp, ilcons, ilchain, env);
                return;
        }
        CLBC_chain_super(self, iltype, tp, ilcons, ilchain, env);
}

static void CLBC_chain_root(bc_ClassLoader* self, bc_ILType* iltype,
                            bc_Type* tp, bc_ILConstructor* ilcons,
                            bc_ILConstructorChain* ilchain,
                            bc_Enviroment* env) {
        bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)OP_NEW_OBJECT);
        bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)OP_ALLOC_FIELD);
        bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)tp->AbsoluteIndex);
}

static void CLBC_chain_auto(bc_ClassLoader* self, bc_ILType* iltype,
                            bc_Type* tp, bc_ILConstructor* ilcons,
                            bc_ILConstructorChain* ilchain,
                            bc_Enviroment* env) {
        bc_Class* classz = tp->Kind.Class;
        int emptyTemp = 0;
        bc_CallContext* cctx = bc_NewCallContext(CALL_CTOR_ARGS_T);
        cctx->Ty = tp;
        bc_Constructor* emptyTarget = bc_ResolveConstructor(
            classz->SuperClass->CoreType->Kind.Class->Constructors, 0, NULL,
            NULL, cctx, &emptyTemp);

        bc_DeleteCallContext(cctx);
        //連鎖を明示的に書いていないのに、
        //親クラスにも空のコンストラクタが存在しない=エラー
        //(この場合自動的にチェインコンストラクタを補うことが出来ないため。)
        if (emptyTarget == NULL) {
                bc_Panic(BCERROR_AUTO_CHAIN_CTOR_NOT_FOUND_T,
                         bc_Ref2Str(bc_GetTypeName(tp)));
                return;
        }
        assert((emptyTarget != NULL));
        //空のコンストラクタを見つけることが出来たので、
        //自動的にそれへ連鎖するチェインをおぎなう
        bc_ILConstructorChain* ch_empty = bc_NewILConstructorChain();
        ch_empty->Constructor = emptyTarget;
        ch_empty->ConstructorIndex = emptyTemp;
        ch_empty->Type = AST_CONSTRUCTOR_CHAIN_SUPER_T;
        ilcons->Chain = ch_empty;
        //親クラスへ連鎖
        bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)OP_CHAIN_SUPER);
        bc_AddOpcodeBuf(
            env->Bytecode,
            (bc_VectorItem)classz->SuperClass->CoreType->AbsoluteIndex);
        bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)emptyTemp);
        bc_AddOpcodeBuf(env->Bytecode,
                        (bc_VectorItem)classz->Parent->AllocSize);
        //このクラスのフィールドを確保
        bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)OP_ALLOC_FIELD);
        bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)tp->AbsoluteIndex);
}

static void CLBC_chain_super(bc_ClassLoader* self, bc_ILType* iltype,
                             bc_Type* tp, bc_ILConstructor* ilcons,
                             bc_ILConstructorChain* ilchain,
                             bc_Enviroment* env) {
        bc_Class* classz = tp->Kind.Class;
        //チェインコンストラクタの実引数をプッシュ
        bc_CallContext* cctx = bc_NewCallContext(CALL_CTOR_ARGS_T);
        cctx->Ty = tp;
        bc_ILConstructorChain* chain = ilcons->Chain;
        for (int i = 0; i < chain->Arguments->Length; i++) {
                bc_ILArgument* ilarg =
                    (bc_ILArgument*)bc_AtVector(chain->Arguments, i);
                bc_GenerateILFactor(ilarg->Factor, env, cctx);
        }
        //連鎖先のコンストラクタを検索する
        bc_Constructor* chainTarget = NULL;
        int temp = -1;
#if defined(_MSC_VER)
        bc_GenericType* gargs =
            MEM_MALLOC(sizeof(bc_GenericType*) * chain->Arguments->Length);
#else
        bc_GenericType* gargs[chain->Arguments->Length];
#endif
        bc_CevaluateArguments(chain->Arguments, gargs, env, cctx);
        if (bc_GetLastPanic()) {
#if defined(_MSC_VER)
                MEM_FREE(gargs);
#endif
                return;
        }
        if (chain->Type == CHAIN_TYPE_THIS_T) {
                chainTarget = bc_ResolveConstructor(classz->Constructors,
                                                    chain->Arguments->Length,
                                                    gargs, NULL, cctx, &temp);
                bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)OP_CHAIN_THIS);
                bc_AddOpcodeBuf(env->Bytecode,
                                (bc_VectorItem)(tp->AbsoluteIndex));
                bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)temp);
                bc_AddOpcodeBuf(env->Bytecode,
                                (bc_VectorItem)classz->Parent->AllocSize);
        } else if (chain->Type == CHAIN_TYPE_SUPER_T) {
                chainTarget = bc_ResolveConstructor(
                    BC_TYPE2CLASS(bc_GENERIC2TYPE(classz->SuperClass))
                        ->Constructors,
                    chain->Arguments->Length, gargs, NULL, cctx, &temp);
                bc_AddOpcodeBuf(env->Bytecode, OP_CHAIN_SUPER);
                bc_AddOpcodeBuf(env->Bytecode,
                                classz->SuperClass->CoreType->AbsoluteIndex);
                bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)temp);
                bc_AddOpcodeBuf(env->Bytecode,
                                (bc_VectorItem)classz->Parent->AllocSize);
        }
        if (chainTarget == NULL) {
                bc_Panic(BCERROR_EXPLICIT_CHAIN_CTOR_NOT_FOUND_T,
                         bc_Ref2Str(bc_GetTypeName(tp)));
#if defined(_MSC_VER)
                MEM_FREE(gargs);
#endif
                return;
        }
        bc_DeleteCallContext(cctx);
        chain->Constructor = chainTarget;
        chain->ConstructorIndex = temp;
        //親クラスへのチェインなら即座にフィールドを確保
        bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)OP_ALLOC_FIELD);
        bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)tp->AbsoluteIndex);
#if defined(_MSC_VER)
        MEM_FREE(gargs);
#endif
}

static bool CLBC_test_operator_overlaod(bc_ClassLoader* self, bc_ILType* iltype,
                                        bc_Type* tp,
                                        bc_OperatorOverload* opov) {
        //アクセスレベルを確認する
        if (BC_MEMBER_ACCESS(opov) != ACCESS_PUBLIC_T) {
                bc_Panic(BCERROR_PRIVATE_OPERATOR_T, bc_GetTypeName(tp));
                return true;
        }
        //二項演算子であるなら引数は1
        if (bc_Is2ArgOperator(opov->Type) && opov->Parameters->Length != 1) {
                bc_Panic(BCERROR_ARG_COUNT_NOT2_BIOPERATOR_T,
                         bc_GetTypeName(tp), bc_OperatorToString(opov->Type));
                return true;
        }
        //単項演算子であるなら引数は0
        if (bc_Is1ArgOperator(opov->Type) && opov->Parameters->Length != 0) {
                bc_Panic(BCERROR_ARG_COUNT_NOT1_UOPERATOR_T, bc_GetTypeName(tp),
                         bc_OperatorToString(opov->Type));
                return true;
        }
        //配列参照演算子であるあんら引数は1
        if (opov->Type == OPERATOR_SUB_SCRIPT_GET_T &&
            opov->Parameters->Length != 1) {
                bc_Panic(BCERROR_ARG_COUNT_NOT1_SUBSCRIPT_GET_OP_T,
                         bc_GetTypeName(tp), bc_OperatorToString(opov->Type));
                return true;
        }
        //配列書き込み演算子であるあんら引数は2
        if (opov->Type == OPERATOR_SUB_SCRIPT_SET_T &&
            opov->Parameters->Length != 2) {
                bc_Panic(BCERROR_ARG_COUNT_NOT2_SUBSCRIPT_SET_OP_T,
                         bc_GetTypeName(tp), bc_OperatorToString(opov->Type));
                return true;
        }
        //== などの比較演算子の戻り値が bool ではない
        if (bc_IsCompareOperator(opov->Type) &&
            opov->ReturnGType->CoreType != BC_TYPE_BOOL) {
                bc_Panic(BCERROR_RETURN_TYPE_NOT_BOOL_COMPARE_OPERATOR_T,
                         bc_Ref2Str(bc_GetTypeName(tp)),
                         bc_OperatorToString(opov->Type));
                return true;
        }
        //! の戻り値が bool ではない
        if (opov->Type == OPERATOR_NOT_T &&
            opov->ReturnGType->CoreType != BC_TYPE_BOOL) {
                bc_Panic(BCERROR_RETURN_TYPE_NOT_BOOL_NOT_OPERATOR_T,
                         bc_Ref2Str(bc_GetTypeName(tp)),
                         bc_OperatorToString(opov->Type));
                return true;
        }
        //- の戻り値がクラスと異なる
        //(IntならInt, Vector2ならVector2)
        if (opov->Type == OPERATOR_NEGATIVE_T &&
            opov->ReturnGType->CoreType != BC_MEMBER_TYPE(opov)) {
                bc_Panic(BCERROR_RETURN_TYPE_NOT_EQUAL_NEGATIVE_OPERATOR_T,
                         bc_Ref2Str(bc_GetTypeName(tp)),
                         bc_OperatorToString(opov->Type));
                return true;
        }
        return false;
}
