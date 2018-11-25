#include "generic_type.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../env/object.h"
#include "../il/il_type_argument.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../vm/frame.h"
#include "TYPE_IMPL.h"
#include "constructor.h"
#include "fqcn_cache.h"
#include "script_context.h"
#include "type_interface.h"
#include "type_parameter.h"

// proto
static bc_GenericType* apply_impl(bc_GenericType* self, bc_CallContext* cctx,
                                  bc_Frame* fr);
static int distance_impl(bc_GenericType* self, bc_GenericType* other,
                         bc_Frame* fr, bc_CallContext* cctx);
static int distance_nogeneric(bc_GenericType* self, bc_GenericType* other,
                              bc_Frame* fr, bc_CallContext* cctx);
static int distance_class(int dist, bc_GenericType* self, bc_GenericType* other,
                          bc_Frame* fr, bc_CallContext* cctx);
static int distance_interface(int dist, bc_GenericType* self,
                              bc_GenericType* other, bc_Frame* fr,
                              bc_CallContext* cctx);
static bc_Vector* apply_by_hierarchy(bc_GenericType* impl_baseline,
                                     bc_GenericType* impl);
static bc_GenericType* typeargs_at(bc_CallContext* cctx, bc_Frame* fr,
                                   int index);
static bc_GenericType* receiver_at(bc_CallContext* cctx, bc_Frame* fr,
                                   int index);
static void delete_self(bc_VectorItem item);
static void delete_recursive_self(bc_VectorItem item);
static void recursive_mark(bc_GenericType* a);
static bc_GenericType* get_generic(bc_GenericType* a);
static bc_GenericType* expand_generic_once(bc_GenericType* self,
                                           bc_GenericType* receiver,
                                           bc_Vector* type_args,
                                           bc_ExecutePhase phase);
static bc_GenericType* void_to_generic(void* value, bc_ExecutePhase phase);
/*
GenericType * NewGenericType(Type* CoreType) {

}
*/

bc_GenericType* bc_RefGenericType(bc_Type* CoreType) {
        if (CoreType == NULL) {
                return bc_NewGenericType(CoreType);
        }
        return CoreType->GenericSelf;
}

bc_GenericType* bc_MallocGenericType(struct bc_Type* CoreType,
                                     const char* filename, int lineno) {
        bc_GenericType* ret = (bc_GenericType*)bc_MXMalloc(
            sizeof(bc_GenericType), filename, lineno);
        ret->CoreType = CoreType;
        ret->TypeArgs = bc_NewVector();
        ret->VirtualTypeIndex = -1;
        ret->Tag = GENERIC_TYPE_TAG_NONE_T;
        ret->IsCtorParameter = false;
        //現在のスクリプトコンテキストに登録
        bc_ScriptContext* ctx = bc_GetCurrentScriptContext();
        bc_PushVector(ctx->AllGenericList, ret);
        return ret;
}

bc_GenericType* bc_CloneGenericType(bc_GenericType* self, bool recursive) {
        bc_GenericType* a = bc_NewGenericType(self->CoreType);
        //再帰的に複製する場合
        if (recursive) {
                for (int i = 0; i < self->TypeArgs->Length; i++) {
                        bc_GenericType* e = bc_AtVector(self->TypeArgs, i);
                        bc_AddArgsGenericType(a, bc_CloneGenericType(e, true));
                }
        }
        //属性を複製
        a->Tag = self->Tag;
        a->VirtualTypeIndex = self->VirtualTypeIndex;
        if (a->Tag == GENERIC_TYPE_TAG_CLASS_T) {
                a->Kind.Type = self->Kind.Type;
        } else if (a->Tag == GENERIC_TYPE_TAG_METHOD_T) {
                a->Kind.Method = self->Kind.Method;
        }
        return a;
}

void bc_CollectGenericType() {
        bc_ScriptContext* ctx = bc_GetCurrentScriptContext();
        //マークを外す
        for (int i = 0; i < ctx->AllGenericList->Length; i++) {
                bc_GenericType* e =
                    (bc_GenericType*)bc_AtVector(ctx->AllGenericList, i);
                e->IsMark = false;
        }
        //全ての型に定義された自身を参照するための generic をマーク
        for (int i = 0; i < ctx->TypeList->Length; i++) {
                bc_Type* e = (bc_Type*)bc_AtVector(ctx->TypeList, i);
                recursive_mark(e->GenericSelf);
        }
        bc_Vector* alive = bc_NewVector();
        bc_Vector* dead = bc_NewVector();
        for (int i = 0; i < ctx->AllGenericList->Length; i++) {
                bc_GenericType* e =
                    (bc_GenericType*)bc_AtVector(ctx->AllGenericList, i);
                bc_PushVector((!e->IsMark ? dead : alive), e);
        }
        bc_DeleteVector(ctx->AllGenericList, bc_VectorDeleterOfNull);
        bc_DeleteVector(dead, delete_self);
        ctx->AllGenericList = alive;
}

void bc_LostownershipGenericType(bc_GenericType* a) {
        // enumはクラスの一種だが、
        // generic_Selfを持たない
        if (a == NULL) {
                return;
        }
        assert(a->CoreType != NULL);
        assert(a->CoreType->GenericSelf == a);
        delete_recursive_self(a);
}

void bc_AddArgsGenericType(bc_GenericType* self, bc_GenericType* a) {
        assert(a != NULL);
        bc_PushVector(self->TypeArgs, a);
}

int bc_DistanceGenericType(bc_GenericType* self, bc_GenericType* other,
                           bc_CallContext* cctx) {
        return distance_impl(self, other, NULL, cctx);
}

int bc_RDistanceGenericType(bc_GenericType* self, bc_GenericType* other,
                            bc_Frame* fr) {
        return distance_impl(self, other, fr, NULL);
}

void bc_PrintGenericType(bc_GenericType* self) {
        assert(self != NULL);
        //タグを出力
        switch (self->Tag) {
                case GENERIC_TYPE_TAG_NONE_T:
                        printf("::");
                        break;
                case GENERIC_TYPE_TAG_CLASS_T:
                        printf("@@");
                        break;
                case GENERIC_TYPE_TAG_METHOD_T:
                        printf("##");
                        break;
        }
        // T, Uなど
        if (self->VirtualTypeIndex != -1) {
                //(Array)[0]
                if (self->Tag == GENERIC_TYPE_TAG_CLASS_T) {
                        printf("(%s)",
                               bc_Ref2Str(bc_GetTypeName(self->Kind.Type)));
                        // copy[0]
                } else if (self->Tag == GENERIC_TYPE_TAG_METHOD_T) {
                        printf("(%s)", bc_Ref2Str(self->Kind.Method->Name));
                }
                printf("[%d]", self->VirtualTypeIndex);
                // Intなど
        } else {
                printf("%s", bc_Ref2Str(bc_GetTypeName(self->CoreType)));
        }
        if (self->IsCtorParameter) {
                printf("!!");
        }
        if (self->TypeArgs->Length == 0) {
                return;
        }
        //[...]
        printf("[");
        for (int i = 0; i < self->TypeArgs->Length; i++) {
                bc_GenericType* e =
                    (bc_GenericType*)bc_AtVector(self->TypeArgs, i);
                bc_PrintGenericType(e);
                if (i != self->TypeArgs->Length - 1) {
                        printf(",");
                }
        }
        printf("]");
}

void bc_GenerateGenericType(bc_GenericType* self, bc_Enviroment* env) {
        bc_AddOpcodeBuf(env->Bytecode, OP_GENERIC_ENTER);
        bc_AddOpcodeBuf(env->Bytecode, self->TypeArgs->Length);
        if (self->CoreType == NULL) {
                if (self->Tag == GENERIC_TYPE_TAG_CLASS_T) {
                        bc_AddOpcodeBuf(env->Bytecode,
                                        OP_GENERIC_INSTANCE_TYPE);
                        bc_AddOpcodeBuf(env->Bytecode, self->VirtualTypeIndex);
                        // assert(self->VirtualTypeIndex != -1);
                } else {
                        bc_AddOpcodeBuf(env->Bytecode, OP_GENERIC_STATIC_TYPE);
                        bc_AddOpcodeBuf(env->Bytecode, self->VirtualTypeIndex);
                }
        } else {
                bc_AddOpcodeBuf(env->Bytecode, OP_GENERIC_UNIQUE_TYPE);
                bc_AddOpcodeBuf(env->Bytecode, self->CoreType->AbsoluteIndex);
        }
        for (int i = 0; i < self->TypeArgs->Length; i++) {
                bc_GenericType* e =
                    (bc_GenericType*)bc_AtVector(self->TypeArgs, i);
                bc_GenerateGenericType(e, env);
        }
        bc_AddOpcodeBuf(env->Bytecode, OP_GENERIC_EXIT);
}

// Hash<String,List<Int>>
bc_GenericType* bc_ApplyGenericType(bc_GenericType* self,
                                    bc_CallContext* cctx) {
        return bc_ExpandGenericType(self, bc_GetReceiverCContext(cctx),
                                    bc_GetTypeArgsCContext(cctx),
                                    PHASE_COMPILE_TIME);
}

bc_GenericType* bc_RApplyGenericType(bc_GenericType* self, bc_CallContext* cctx,
                                     bc_Frame* fr) {
        return apply_impl(self, cctx, fr);
}

bc_GenericType* bc_ExpandGenericType(bc_GenericType* self,
                                     bc_GenericType* receiver,
                                     bc_Vector* type_args,
                                     bc_ExecutePhase phase) {
        bc_GenericType* ret =
            expand_generic_once(self, receiver, type_args, phase);
        //型変数を再帰的に展開
        for (int i = 0; i < self->TypeArgs->Length; i++) {
                bc_AddArgsGenericType(
                    ret, bc_ExpandGenericType(bc_AtVector(self->TypeArgs, i),
                                              receiver, type_args, phase));
        }
        return ret;
}

struct bc_Type* bc_GenericTypeToType(bc_GenericType* self) {
        return self->CoreType;
}

// private
static bc_GenericType* apply_impl(bc_GenericType* self, bc_CallContext* cctx,
                                  bc_Frame* fr) {
        int count = 0;
        //型変数なら変換
        bc_GenericType* ret = NULL;
        if (self->VirtualTypeIndex != -1) {
                count++;
                if (self->Tag == GENERIC_TYPE_TAG_CLASS_T) {
                        if (self->IsCtorParameter) {
                                ret = bc_CloneGenericType(
                                    typeargs_at(cctx, fr,
                                                self->VirtualTypeIndex),
                                    true);
                        } else {
                                ret = bc_CloneGenericType(
                                    receiver_at(cctx, fr,
                                                self->VirtualTypeIndex),
                                    true);
                        }
                } else if (self->Tag == GENERIC_TYPE_TAG_METHOD_T) {
                        ret = bc_CloneGenericType(
                            typeargs_at(cctx, fr, self->VirtualTypeIndex),
                            true);
                }
        } else {
                ret = bc_NewGenericType(self->CoreType);
                ret->Tag = self->Tag;
                ret->VirtualTypeIndex = self->VirtualTypeIndex;
        }
        assert(ret != NULL);
        for (int i = 0; i < self->TypeArgs->Length; i++) {
                bc_AddArgsGenericType(
                    ret,
                    bc_ApplyGenericType(bc_AtVector(self->TypeArgs, i), cctx));
        }
        return ret;
}

static int distance_impl(bc_GenericType* self, bc_GenericType* other,
                         bc_Frame* fr, bc_CallContext* cctx) {
        if (fr != NULL) {
                return distance_nogeneric(self, other, fr, cctx);
        }
        //要求されている型は T
        if (self->CoreType == NULL) {
                //提供されているのは T
                if (other->CoreType == NULL) {
                        return 0;
                        //提供されているのは具体的な型
                } else {
                        //具体的な型が T のルールを満たしているか？
                        return 0;
                }
                //提供している型は T
        } else if (other->CoreType == NULL) {
                //要求されているのは具体的な型
                if (self->CoreType != NULL) {
                        // Object型にのみ変換可能
                        if (self->CoreType == BC_TYPE_OBJECT) {
                                return 0;
                        }
                        // T が 具体的な型の要件を満たしているか？
                        return -1;
                        //要求されているのは T
                } else {
                        return 0;
                }
                //どちらも具体的な型
        } else {
                return distance_nogeneric(self, other, fr, cctx);
        }
}

static int distance_nogeneric(bc_GenericType* self, bc_GenericType* other,
                              bc_Frame* fr, bc_CallContext* cctx) {
        assert(self->CoreType != NULL);
        assert(other->CoreType != NULL);
        int dist = bc_DistanceType(self->CoreType, other->CoreType);
        assert(self->CoreType != NULL);
        assert(other->CoreType != NULL);
#if defined(DEBUG)
        const char* sname = bc_Ref2Str(bc_GetTypeName(self->CoreType));
        const char* oname = bc_Ref2Str(bc_GetTypeName(other->CoreType));
#endif
        // List : Dict みたいな型ならもうこの時点で次へ
        if (dist == -1) {
                return dist;
        }
        if (other->CoreType == BC_TYPE_NULL) {
                return 1;
        }
        if (self->CoreType->Tag == TYPE_CLASS_T) {
                return distance_class(dist, self, other, fr, cctx);
        } else if (self->CoreType->Tag == TYPE_INTERFACE_T) {
                return distance_interface(dist, self, other, fr, cctx);
        }
        return dist;
}

static int distance_class(int dist, bc_GenericType* self, bc_GenericType* other,
                          bc_Frame* fr, bc_CallContext* cctx) {
        // otherからselfまで辿る
        bc_Class* baseline = self->CoreType->Kind.Class;
        bc_Class* ptr = other->CoreType->Kind.Class;
        bc_GenericType* target = other;
        while (baseline != ptr) {
                target = ptr->SuperClass;
                ptr = ptr->SuperClass->CoreType->Kind.Class;
        }
        assert(target != NULL);
        assert(self->TypeArgs->Length == target->TypeArgs->Length);
        for (int i = 0; i < self->TypeArgs->Length; i++) {
                bc_GenericType* a = bc_AtVector(self->TypeArgs, i);
                bc_GenericType* b = bc_AtVector(target->TypeArgs, i);
                int calc = distance_impl(a, b, fr, cctx);
                if (calc == -1 || calc > 0) {
                        dist = -1;
                        break;
                }
        }
        return dist;
}

static int distance_interface(int dist, bc_GenericType* self,
                              bc_GenericType* other, bc_Frame* fr,
                              bc_CallContext* cctx) {
        if (other->CoreType->Tag == TYPE_CLASS_T) {
                //クラスからインターフェイスを探す
                bc_GenericType* impl_baseline = NULL;
                bc_GenericType* impl = bc_FindInterfaceTypeClass(
                    BC_TYPE2CLASS(bc_GENERIC2TYPE(other)),
                    (bc_GENERIC2TYPE(self)), &impl_baseline);
                if (impl_baseline == NULL) {
                        impl_baseline = other;
                }
                bc_Vector* gargs = apply_by_hierarchy(impl_baseline, impl);
                for (int i = 0; i < self->TypeArgs->Length; i++) {
                        bc_GenericType* a = bc_AtVector(self->TypeArgs, i);
                        bc_GenericType* b = bc_AtVector(gargs, i);
                        int calc = distance_impl(a, b, fr, cctx);
                        if (calc == -1 || calc > 0) {
                                dist = -1;
                                break;
                        }
                }
                bc_DeleteVector(gargs, bc_VectorDeleterOfNull);
                return dist;
        } else if (other->CoreType->Tag == TYPE_INTERFACE_T) {
                bc_GenericType* impl = bc_FindInterfaceInterface(
                    BC_TYPE2INTERFACE(bc_GENERIC2TYPE(other)),
                    (bc_GENERIC2TYPE(self)));
                if (impl == NULL) {
                        impl = other;
                }
                for (int i = 0; i < self->TypeArgs->Length; i++) {
                        bc_GenericType* a = bc_AtVector(self->TypeArgs, i);
                        bc_GenericType* b = bc_AtVector(impl->TypeArgs, i);
                        int calc = distance_impl(a, b, fr, cctx);
                        if (calc == -1 || calc > 0) {
                                dist = -1;
                                break;
                        }
                }
                // PrintGenericType(self); bc_Println();
                // PrintGenericType(other); bc_Println();
                // bc_Printfln("---");
                return dist;
        }
        return dist;
}

static bc_Vector* apply_by_hierarchy(bc_GenericType* impl_baseline,
                                     bc_GenericType* impl) {
        assert(impl_baseline->CoreType != NULL);
        bc_Vector* gargs = bc_NewVector();
        for (int i = 0; i < impl->TypeArgs->Length; i++) {
                bc_GenericType* e = bc_AtVector(impl->TypeArgs, i);
                if (e->CoreType == NULL) {
                        e = bc_AtVector(impl_baseline->TypeArgs,
                                        e->VirtualTypeIndex);
                }
                bc_PushVector(gargs, e);
        }
        return gargs;
}

static bc_GenericType* typeargs_at(bc_CallContext* cctx, bc_Frame* fr,
                                   int index) {
        if (fr == NULL) {
                bc_Vector* type_args = bc_GetTypeArgsCContext(cctx);
                bc_ILTypeArgument* a = bc_AtVector(type_args, index);
                return a->GType;
        } else {
                bc_GenericType* a = bc_AtVector(fr->TypeArgs, index);
                return a;
        }
        return NULL;
}

static bc_GenericType* receiver_at(bc_CallContext* cctx, bc_Frame* fr,
                                   int index) {
        if (fr == NULL) {
                bc_GenericType* tp = bc_GetReceiverCContext(cctx);
                bc_GenericType* instanced = bc_AtVector(tp->TypeArgs, index);
                return instanced;
        } else {
                bc_Object* a = bc_AtVector(fr->VariableTable, 0);
                printf("receiver at: ");
                bc_PrintGenericType(a->GType);
                bc_Println();
                return bc_AtVector(a->GType->TypeArgs, index);
        }
        return NULL;
}

static bc_GenericType* get_generic(bc_GenericType* a) {
        /*
        if(a->VirtualTypeIndex == -1) {
                return a;
        }
        if(a->Tag == GENERIC_TYPE_TAG_CLASS_T) {
                GenericType* receiver = ccat_receiver(a->VirtualTypeIndex);
                a = receiver;
        } else if(a->Tag == GENERIC_TYPE_TAG_METHOD_T) {
                GenericType* at = AtVector(cctop_type_args(),
        a->VirtualTypeIndex); a = at;
        }
        return a;
        */
        return NULL;
}

static void delete_self(bc_VectorItem item) {
        bc_GenericType* e = (bc_GenericType*)item;
        bc_DeleteVector(e->TypeArgs, bc_VectorDeleterOfNull);
        MEM_FREE(e);
}

static void delete_recursive_self(bc_VectorItem item) {
        bc_GenericType* e = (bc_GenericType*)item;
        bc_DeleteVector(e->TypeArgs, delete_recursive_self);
        MEM_FREE(e);
}

static void recursive_mark(bc_GenericType* a) {
        if (a == NULL || a->IsMark) {
                return;
        }
        a->IsMark = true;
        for (int i = 0; i < a->TypeArgs->Length; i++) {
                recursive_mark((bc_GenericType*)bc_AtVector(a->TypeArgs, i));
        }
}

static bc_GenericType* expand_generic_once(bc_GenericType* self,
                                           bc_GenericType* receiver,
                                           bc_Vector* type_args,
                                           bc_ExecutePhase phase) {
        bc_GenericType* ret = NULL;
        //型引数がない場合
        if (self->VirtualTypeIndex == -1) {
                ret = bc_NewGenericType(self->CoreType);
                ret->Tag = self->Tag;
                ret->VirtualTypeIndex = self->VirtualTypeIndex;
                return ret;
        }
        //ある
        if (self->Tag == GENERIC_TYPE_TAG_CLASS_T) {
                if (self->IsCtorParameter) {
                        assert(type_args != NULL);
                        ret = bc_CloneGenericType(
                            void_to_generic(
                                bc_AtVector(type_args, self->VirtualTypeIndex),
                                phase),
                            true);
                } else {
                        assert(receiver->TypeArgs != NULL);
                        ret = bc_CloneGenericType(
                            bc_AtVector(receiver->TypeArgs,
                                        self->VirtualTypeIndex),
                            true);
                }
        } else if (self->Tag == GENERIC_TYPE_TAG_METHOD_T) {
                assert(type_args != NULL);
                ret = bc_CloneGenericType(
                    void_to_generic(
                        bc_AtVector(type_args, self->VirtualTypeIndex), phase),
                    true);
        }
        return ret;
}

static bc_GenericType* void_to_generic(void* value, bc_ExecutePhase phase) {
        switch (phase) {
                case PHASE_COMPILE_TIME:
                        return ((bc_ILTypeArgument*)value)->GType;
                case PHASE_RUN_TIME:
                        return ((bc_Object*)value)->GType;
        }
        return NULL;
}