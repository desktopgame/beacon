#include "il_factor_assign_op_impl.h"
#include "../../env/TYPE_IMPL.h"
#include "../../env/field.h"
#include "../../env/property.h"
#include "../../env/property_body.h"
#include "../../il/il_argument.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../vm/generate.h"
#include "../../vm/symbol_entry.h"
#include "../il_factor_impl.h"

static void assign_by_namebase(bc_ILAssignOp* self, bc_Enviroment* env,
                               bc_CallContext* cctx);
static void assign_to_field(bc_ILAssignOp* self, bc_ILFactor* receiver,
                            bc_ILFactor* source, bc_StringView namev,
                            bc_Enviroment* env, bc_CallContext* cctx);
static void assign_to_Property(bc_ILAssignOp* self, bc_Enviroment* env,
                               bc_CallContext* cctx);
static void assign_to_array(bc_ILAssignOp* self, bc_Enviroment* env,
                            bc_CallContext* cctx);
static void assign_by_call(bc_ILAssignOp* self, bc_Enviroment* env,
                           bc_CallContext* cctx);
static void assign_by_invoke(bc_ILInvoke* lhs, bc_ILFactor* rhs,
                             bc_Enviroment* env, bc_CallContext* cctx);
static void assign_by_invoke_bound(bc_ILInvokeBound* lhs, bc_ILFactor* rhs,
                                   bc_Enviroment* env, bc_CallContext* cctx);
static void check_final(bc_ILFactor* receiver, bc_ILFactor* source,
                        bc_StringView namev, bc_Enviroment* env,
                        bc_CallContext* cctx);
static bool can_assign_to_field(bc_Field* f, bc_ILAssignOp* self,
                                bc_Enviroment* env, bc_CallContext* cctx);
static void generate_assign_to_variable(bc_ILAssignOp* self, bc_Enviroment* env,
                                        bc_CallContext* cctx);
static void generate_assign_to_variable_local(bc_ILAssignOp* self,
                                              bc_Enviroment* env,
                                              bc_CallContext* cctx);

bc_ILFactor* bc_WrapILAssignOp(bc_ILAssignOp* self) {
        bc_ILFactor* ret = bc_NewILFactor(ILFACTOR_ASSIGN_T);
        ret->Kind.AssignOp = self;
        return ret;
}

bc_ILAssignOp* bc_NewILAssignOp() {
        bc_ILAssignOp* ret = (bc_ILAssignOp*)MEM_MALLOC(sizeof(bc_ILAssignOp));
        ret->Left = NULL;
        ret->Right = NULL;
        return ret;
}

void bc_LoadILAssignOp(bc_ILAssignOp* self, bc_Enviroment* env,
                       bc_CallContext* cctx) {
        bc_LoadILFactor(self->Left, env, cctx);
        bc_LoadILFactor(self->Right, env, cctx);
        // voidは代入できない
        bc_GenericType* gret = bc_EvalILFactor(self->Right, env, cctx);
        BC_ERROR();
        if (gret->CoreType != NULL && gret->CoreType == BC_TYPE_VOID) {
                bc_Panic(BCERROR_VOID_ASSIGN_T);
                return;
        }
}

void bc_GenerateILAssignOp(bc_ILAssignOp* self, bc_Enviroment* env,
                           bc_CallContext* cctx) {
        if (self->Left->Type == ILFACTOR_VARIABLE_T) {
                generate_assign_to_variable(self, env, cctx);
                // NOTE:constかどうかの検査
                // foo.bar = xxx
        } else if (self->Left->Type == ILFACTOR_MEMBER_OP_T) {
                bc_ILMemberOp* ilmem = self->Left->Kind.MemberOp;
                bc_ILFactor* ilsrc = ilmem->Source;
                if (ilsrc->Type == ILFACTOR_VARIABLE_T) {
                        assign_by_namebase(self, env, cctx);
                        //インスタンスフィールドへの代入
                } else {
                        assign_to_field(self, ilmem->Source, self->Right,
                                        ilmem->Name, env, cctx);
                }
        } else if (self->Left->Type == ILFACTOR_PROPERTY_T) {
                assign_to_Property(self, env, cctx);
        } else if (self->Left->Type == ILFACTOR_SUBSCRIPT_T) {
                assign_to_array(self, env, cctx);
        } else if (self->Left->Type == ILFACTOR_CALL_OP_T) {
                assign_by_call(self, env, cctx);
        } else {
                assert(false);
        }
}

bc_GenericType* bc_EvalILAssignOp(bc_ILAssignOp* self, bc_Enviroment* env,
                                  bc_CallContext* cctx) {
        return bc_EvalILFactor(self->Right, env, cctx);
}

void bc_DeleteILAssignOp(bc_ILAssignOp* self) {
        bc_DeleteILFactor(self->Left);
        bc_DeleteILFactor(self->Right);
        MEM_FREE(self);
}
// private
static void assign_by_namebase(bc_ILAssignOp* self, bc_Enviroment* env,
                               bc_CallContext* cctx) {
        bc_ILMemberOp* ilmem = self->Left->Kind.MemberOp;
        bc_ILFactor* ilsrc = ilmem->Source;
        bc_ILVariable* ilvar = ilsrc->Kind.Variable;
        // staticなフィールドへの代入
        if (ilvar->Type == ILVARIABLE_TYPE_STATIC_T) {
                bc_Class* cls = BC_TYPE2CLASS(
                    bc_ResolveContext(cctx, ilvar->Kind.Static->FQCN));
                int temp = -1;
                bc_SearchOption opt = cls->Parent == bc_GetTypeByContext(cctx)
                                          ? MATCH_ALL
                                          : MATCH_PUBLIC_ONLY;
                bc_Field* sf =
                    bc_FindField(cls->StaticFields, ilmem->Name, opt, &temp);
                assert(temp != -1);
                bc_GenerateILFactor(self->Right, env, cctx);
                bc_GeneratePutField(env->Bytecode, sf, temp);
                //指定の静的フィールドにアクセスできない
                if (!bc_IsAccessibleFieldClass(bc_GetClassByContext(cctx),
                                               sf)) {
                        bc_Panic(BCERROR_CAN_T_ACCESS_FIELD_T,
                                 bc_Ref2Str(bc_GetTypeName(cls->Parent)),
                                 bc_Ref2Str(sf->Name));
                        return;
                }
                // finalなので書き込めない
                if (bc_IsFinalModifier(BC_MEMBER_MODIFIER(sf))) {
                        bc_Panic(BCERROR_ASSIGN_TO_FINAL_FIELD_T,
                                 bc_Ref2Str(bc_GetTypeName(cls->Parent)),
                                 bc_Ref2Str(sf->Name));
                        return;
                }
                //型の互換性を検査
                if (!can_assign_to_field(sf, self, env, cctx)) {
                        return;
                }
        } else {
                assign_to_field(self, ilmem->Source, self->Right, ilmem->Name,
                                env, cctx);
        }
}

static void assign_to_field(bc_ILAssignOp* self, bc_ILFactor* receiver,
                            bc_ILFactor* source, bc_StringView namev,
                            bc_Enviroment* env, bc_CallContext* cctx) {
        bc_GenericType* gt = bc_EvalILFactor(receiver, env, cctx);
        bc_Class* cls = BC_TYPE2CLASS(gt->CoreType);
        int temp = -1;
        bc_Field* f = bc_FindTreeFieldClass(cls, namev, &temp);
        assert(temp != -1);
        bc_GenerateILFactor(receiver, env, cctx);
        bc_GenerateILFactor(source, env, cctx);
        bc_GeneratePutField(env->Bytecode, f, temp);
        //型の互換性を検査
        if (!can_assign_to_field(f, self, env, cctx)) {
                return;
        }
        //指定のインスタンスフィールドにアクセスできない
        if (!bc_IsAccessibleFieldClass(bc_GetClassByContext(cctx), f)) {
                bc_Panic(BCERROR_CAN_T_ACCESS_FIELD_T,
                         bc_Ref2Str(bc_GetTypeName(cls->Parent)),
                         bc_Ref2Str(f->Name));
        }
        check_final(receiver, source, namev, env, cctx);
}

static void assign_to_Property(bc_ILAssignOp* self, bc_Enviroment* env,
                               bc_CallContext* cctx) {
        bc_ILPropertyAccess* prop = self->Left->Kind.PropertyAccess;
        bc_Property* pp = prop->Property;
        bool is_static =
            bc_IsStaticModifier(BC_MEMBER_MODIFIER(prop->Property));
        BC_ERROR();
        //プロパティへアクセスできない
        if (!bc_IsAccessiblePropertyClass(bc_GetClassByContext(cctx), pp)) {
                bc_Panic(BCERROR_CAN_T_ACCESS_FIELD_T,
                         bc_Ref2Str(bc_GetTypeName(BC_MEMBER_TYPE(pp))),
                         bc_Ref2Str(pp->Name));
                return;
        }
        if (!bc_IsAccessiblePropertyAccessorClass(bc_GetClassByContext(cctx),
                                                  pp->Set)) {
                bc_Panic(BCERROR_CAN_T_ACCESS_FIELD_T,
                         bc_Ref2Str(bc_GetTypeName(BC_MEMBER_TYPE(pp))),
                         bc_Ref2Str(pp->Name));
                return;
        }
        if (bc_CdistanceGenericType(prop->Property->GType,
                                    bc_EvalILFactor(self->Right, env, cctx)) <
            0) {
                bc_Panic(
                    BCERROR_ASSIGN_NOT_COMPATIBLE_PROPERTY_T,
                    bc_Ref2Str(bc_GetTypeName(BC_MEMBER_TYPE(prop->Property))),
                    bc_Ref2Str(prop->Property->Name));
                return;
        }
        //省略記法なら初期化されてるかチェック
        if (pp->IsShort && !bc_IsStaticModifier(BC_MEMBER_MODIFIER(pp))) {
                check_final(prop->Source, self->Right,
                            prop->Property->SourceRef->Name, env, cctx);
        }
        BC_ERROR();
        if (!is_static) {
                bc_GenerateILFactor(prop->Source, env, cctx);
        }
        bc_GenerateILFactor(self->Right, env, cctx);
        bc_GeneratePutProperty(env->Bytecode, pp, prop->Index);
}

static void assign_to_array(bc_ILAssignOp* self, bc_Enviroment* env,
                            bc_CallContext* cctx) {
        bc_ILSubscript* subs = self->Left->Kind.Subscript;
        bc_GenerateILFactor(subs->Receiver, env, cctx);
        bc_GenerateILFactor(subs->Position, env, cctx);
        bc_AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
        bc_AddOpcodeBuf(env->Bytecode, subs->Operator);
}

static void assign_by_call(bc_ILAssignOp* self, bc_Enviroment* env,
                           bc_CallContext* cctx) {
        bc_ILCallOp* call = self->Left->Kind.Call;
        if (call->Type == ILCALL_TYPE_INVOKE_STATIC_T) {
                bc_Panic(BCERROR_LHS_IS_NOT_SUBSCRIPT_T,
                         bc_Ref2Str(call->Kind.InvokeStatic->Name));
                return;
        }
        if (call->Type == ILCALL_TYPE_INVOKE_T) {
                assign_by_invoke(call->Kind.Invoke, self->Right, env, cctx);
        } else if (call->Type == ILCALL_TYPE_INVOKE_BOUND_T) {
                assign_by_invoke_bound(call->Kind.InvokeBound, self->Right, env,
                                       cctx);
        } else {
                assert(false);
        }
}

static void assign_by_invoke(bc_ILInvoke* lhs, bc_ILFactor* rhs,
                             bc_Enviroment* env, bc_CallContext* cctx) {
        int temp = -1;
        if (lhs->tag != INSTANCE_INVOKE_SUBSCRIPT_T) {
                bc_Panic(BCERROR_ASSIGN_TO_INVOKE_T, bc_Ref2Str(lhs->namev));
                return;
        }
        bc_FindSetILInvoke(lhs, rhs, env, cctx, &temp);
        for (int i = 0; i < lhs->args->Length; i++) {
                bc_ILArgument* arg = bc_AtVector(lhs->args, i);
                bc_GenerateILFactor(arg->Factor, env, cctx);
        }
        bc_GenerateILFactor(rhs, env, cctx);
        bc_GenerateILFactor(lhs->receiver, env, cctx);
        bc_AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
        bc_AddOpcodeBuf(env->Bytecode, temp);
        bc_AddOpcodeBuf(env->Bytecode, OP_NOP);
}

static void assign_by_invoke_bound(bc_ILInvokeBound* lhs, bc_ILFactor* rhs,
                                   bc_Enviroment* env, bc_CallContext* cctx) {
        int temp = -1;
        bc_FindSetILInvokeBound(lhs, rhs, env, cctx, &temp);
        assert(lhs->Arguments->Length == 1);
        for (int i = 0; i < lhs->Arguments->Length; i++) {
                bc_ILArgument* arg = bc_AtVector(lhs->Arguments, i);
                bc_GenerateILFactor(arg->Factor, env, cctx);
        }
        bc_GenerateILFactor(rhs, env, cctx);
        // GenerateILFactor(lhs->receiver, env, cctx);
        bc_SubscriptDescriptor subs = lhs->Kind.Subscript;
        if (subs.Tag == SUBSCRIPT_LOCAL_T) {
                bc_AddOpcodeBuf(env->Bytecode, OP_LOAD);
                bc_AddOpcodeBuf(env->Bytecode, subs.Index);
        } else if (subs.Tag == SUBSCRIPT_FIELD_T) {
                bc_AddOpcodeBuf(env->Bytecode, OP_THIS);
                bc_GenerateGetField(env->Bytecode, subs.Kind.Field, subs.Index);
        } else if (subs.Tag == SUBSCRIPT_PROPERTY_T) {
                bc_AddOpcodeBuf(env->Bytecode, OP_THIS);
                bc_GenerateGetProperty(env->Bytecode, subs.Kind.Property,
                                       subs.Index);
        }
        bc_AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
        bc_AddOpcodeBuf(env->Bytecode, temp);
}

static bool can_assign_to_field(bc_Field* f, bc_ILAssignOp* self,
                                bc_Enviroment* env, bc_CallContext* cctx) {
        bc_GenericType* gt = bc_EvalILFactor(self->Right, env, cctx);
        int dist = bc_CdistanceGenericType(f->GType, gt);
        if (dist >= 0) {
                return true;
        } else {
                bc_Panic(BCERROR_ASSIGN_NOT_COMPATIBLE_FIELD_T,
                         bc_Ref2Str(bc_GetTypeName(BC_MEMBER_TYPE(f))),
                         bc_Ref2Str(f->Name));
                return false;
        }
}

static void check_final(bc_ILFactor* receiver, bc_ILFactor* source,
                        bc_StringView namev, bc_Enviroment* env,
                        bc_CallContext* cctx) {
        bc_GenericType* gt = bc_EvalILFactor(receiver, env, cctx);
        bc_Class* cls = BC_TYPE2CLASS(gt->CoreType);
        int temp = -1;
        bc_Field* f = bc_FindTreeFieldClass(cls, namev, &temp);
        assert(temp != -1);
        //コンストラクタ以外の場所では finalフィールドは初期化できない
        if (cctx->Tag != CALL_CTOR_T) {
                // finalなので書き込めない
                if (bc_IsFinalModifier(BC_MEMBER_MODIFIER(f))) {
                        bc_Panic(BCERROR_ASSIGN_TO_FINAL_FIELD_T,
                                 bc_Ref2Str(bc_GetTypeName(cls->Parent)),
                                 bc_Ref2Str(f->Name));
                }
        } else {
                //コンストラクタであっても static final の場合は書き込めない
                if (bc_IsFinalModifier(BC_MEMBER_MODIFIER(f)) &&
                    bc_IsStaticModifier(BC_MEMBER_MODIFIER(f))) {
                        bc_Panic(BCERROR_ASSIGN_TO_FINAL_FIELD_T,
                                 bc_Ref2Str(bc_GetTypeName(cls->Parent)),
                                 bc_Ref2Str(f->Name));
                }
                f->IsNotInitializedAtCtor = true;
        }
}

static void generate_assign_to_variable(bc_ILAssignOp* self, bc_Enviroment* env,
                                        bc_CallContext* cctx) {
        assert(self->Left->Type == ILFACTOR_VARIABLE_T);
        bc_ILVariable* ilvar = self->Left->Kind.Variable;
        if (ilvar->Type == ILVARIABLE_TYPE_LOCAL_T) {
                generate_assign_to_variable_local(self, env, cctx);
        }
}

static void generate_assign_to_variable_local(bc_ILAssignOp* self,
                                              bc_Enviroment* env,
                                              bc_CallContext* cctx) {
        bc_ILVariable* ilvar = self->Left->Kind.Variable;
        bc_ILVariableLocal* illoc = ilvar->Kind.Local;
        // src のような名前がローカル変数を示す場合
        if (illoc->Type == VARIABLE_LOCAL_SCOPE_T) {
#if defined(DEBUG)
                const char* vname = bc_Ref2Str(ilvar->FQCN->Name);
#endif
                bc_SymbolEntry* e =
                    bc_EntrySymbolTable(env->Symboles, NULL, ilvar->FQCN->Name);
                // e==NULL の時変数がない
                bc_GenerateILFactor(self->Right, env, cctx);
                bc_AddOpcodeBuf(env->Bytecode, OP_STORE);
                bc_AddOpcodeBuf(env->Bytecode, e->Index);
                if (bc_CdistanceGenericType(
                        e->GType, bc_EvalILFactor(self->Right, env, cctx)) <
                    0) {
                        bc_Panic(BCERROR_ASSIGN_NOT_COMPATIBLE_LOCAL_T,
                                 bc_Ref2Str(ilvar->FQCN->Name));
                        return;
                }
                // src のような名前がフィールドを示す場合
        } else if (illoc->Type == VARIABLE_LOCAL_FIELD_T) {
                int temp = -1;
                bc_Field* f = bc_FindTreeFieldClass(bc_GetClassByContext(cctx),
                                                    illoc->Name, &temp);
                if (temp == -1) {
                        f = bc_FindTreeSFieldClass(bc_GetClassByContext(cctx),
                                                   illoc->Name, &temp);
                }
                assert(temp != -1);
                //フィールドはstaticでないが
                //現在のコンテキストはstaticなので this にアクセスできない
                if (!bc_IsStaticModifier(BC_MEMBER_MODIFIER(f)) &&
                    bc_IsStaticContext(cctx)) {
                        bc_Panic(BCERROR_ACCESS_TO_THIS_AT_STATIC_METHOD_T,
                                 bc_Ref2Str(bc_GetTypeName(BC_MEMBER_TYPE(f))),
                                 bc_Ref2Str(f->Name));
                        return;
                }
                if (!bc_IsStaticModifier(BC_MEMBER_MODIFIER(f))) {
                        bc_AddOpcodeBuf(env->Bytecode, OP_THIS);
                }
                bc_GenerateILFactor(self->Right, env, cctx);
                bc_GeneratePutField(env->Bytecode, f, temp);
                // assert(!IsStaticModifier(f->modifier));
                // src のような名前がプロパティを示す場合
        } else if (illoc->Type == VARIABLE_LOCAL_PROPERTY_T) {
                int temp = -1;
                bc_Property* p = bc_ResolveProperty(bc_GetClassByContext(cctx),
                                                    illoc->Name, &temp);
                assert(temp != -1);
                //フィールドはstaticでないが
                //現在のコンテキストはstaticなので this にアクセスできない
                if (!bc_IsStaticModifier(BC_MEMBER_MODIFIER(p)) &&
                    bc_IsStaticContext(cctx)) {
                        bc_Panic(BCERROR_ACCESS_TO_THIS_AT_STATIC_METHOD_T,
                                 bc_Ref2Str(bc_GetTypeName(BC_MEMBER_TYPE(p))),
                                 bc_Ref2Str(p->Name));
                        return;
                }
                if (!bc_IsStaticModifier(BC_MEMBER_MODIFIER(p))) {
                        bc_AddOpcodeBuf(env->Bytecode, OP_THIS);
                }
                bc_GenerateILFactor(self->Right, env, cctx);
                bc_GeneratePutProperty(env->Bytecode, p, temp);
                assert(!bc_IsStaticModifier(BC_MEMBER_MODIFIER(p)));
        }
}