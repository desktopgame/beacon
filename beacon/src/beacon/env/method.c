#include "method.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../env/class_loader.h"
#include "../il/call_context.h"
#include "../il/il_stmt_impl.h"
#include "../thread/thread.h"
#include "../util/mem.h"
#include "../util/string_buffer.h"
#include "../util/text.h"
#include "../vm/vm.h"
#include "TYPE_IMPL.h"
#include "constructor.h"
#include "coroutine.h"
#include "generic_type.h"
#include "namespace.h"
#include "object.h"
#include "parameter.h"
#include "type_interface.h"
#include "type_parameter.h"

#if defined(_MSC_VER)
#pragma warning(disable : 4996)
#endif

// proto
static void delete_parameter(bc_VectorItem item);
static void delete_type_parameter(bc_VectorItem item);
static void method_count(bc_ILStatement* s, int* yeild_ret, int* ret);
static bc_Constructor* create_delegate_ctor(bc_Method* self, bc_Type* ty,
                                            bc_ClassLoader* cll, int op_len);
static bc_Method* create_has_next(bc_Method* self, bc_Type* ty,
                                  bc_ClassLoader* cll, bc_Vector* stmt_list,
                                  int* out_op_len);
static bc_Method* create_next(bc_Method* self, bc_Type* ty, bc_ClassLoader* cll,
                              bc_GenericType* a, bc_Vector* stmt_list,
                              int* out_op_len);
static bc_Vector* method_vm_args(bc_Method* self, bc_Frame* fr, bc_Frame* a);
static bc_Vector* method_vm_typeargs(bc_Method* self, bc_Frame* fr,
                                     bc_Frame* a);

bc_Method* bc_MallocMethod(bc_StringView name, const char* filename,
                           int lineno) {
        bc_Method* ret =
            (bc_Method*)bc_MXMalloc(sizeof(bc_Method), filename, lineno);
        ret->Index = -1;
        ret->Name = name;
        ret->Parameters = bc_MallocVector(filename, lineno);
        ret->Type = METHOD_TYPE_SCRIPT_T;
        ret->TypeParameters = bc_MallocVector(filename, lineno);
        ret->ReturnGType = NULL;
        bc_InitMember((bc_Member*)ret);
        return ret;
}

void bc_ExecuteMethod(bc_Method* self, bc_Frame* fr, bc_Enviroment* env) {
#if defined(DEBUG)
        const char* namestr = bc_Ref2Str(self->Name);
        if (self->Name == bc_InternString("writeLine")) {
                int a = 0;
        }
#endif
        if (self->Type == METHOD_TYPE_SCRIPT_T) {
                bc_ExecuteScriptMethod(self->Kind.Script, self, fr, env);
        } else if (self->Type == METHOD_TYPE_NATIVE_T) {
                bc_Frame* a = bc_SubFrame(fr);
                bc_CallFrame* cfr = NULL;
                bc_Vector* aArgs = NULL;
                bc_Vector* aTArgs = NULL;
                //レシーバも
                if (!bc_IsStaticModifier(BC_MEMBER_MODIFIER(self))) {
                        bc_Object* receiver_obj = bc_PopVector(fr->ValueStack);
                        bc_AssignVector(a->VariableTable, 0, receiver_obj);
                        cfr = bc_PushCallContext(bc_GetScriptThreadContext(),
                                                 FRAME_INSTANCE_INVOKE_T);
                        cfr->Kind.InstanceInvoke.Receiver = receiver_obj->GType;
                        aArgs = cfr->Kind.InstanceInvoke.Args =
                            method_vm_args(self, fr, a);
                        aTArgs = cfr->Kind.InstanceInvoke.TypeArgs =
                            method_vm_typeargs(self, fr, a);
                } else {
                        cfr = bc_PushCallContext(bc_GetScriptThreadContext(),
                                                 FRAME_STATIC_INVOKE_T);
                        aArgs = cfr->Kind.StaticInvoke.Args =
                            method_vm_args(self, fr, a);
                        aTArgs = cfr->Kind.StaticInvoke.TypeArgs =
                            method_vm_typeargs(self, fr, a);
                }
                bc_ExecuteNativeMethod(self->Kind.Native, self, a, env);
                //戻り値を残す
                //例外によって終了した場合には戻り値がない
                if (self->ReturnGType != BC_TYPE_VOID->GenericSelf &&
                    a->ValueStack->Length > 0) {
                        bc_PushVector(fr->ValueStack,
                                      bc_PopVector(a->ValueStack));
                }
                bc_DeleteVector(aArgs, bc_VectorDeleterOfNull);
                bc_DeleteVector(aTArgs, bc_VectorDeleterOfNull);
                bc_PopCallContext(bc_GetScriptThreadContext());
                bc_DeleteFrame(a);
        }
}

bool bc_IsOverridedMethod(bc_Method* superM, bc_Method* subM,
                          bc_CallContext* cctx) {
        //名前が違うか引数の数が違う
        if (superM->Name != subM->Name ||
            superM->Parameters->Length != subM->Parameters->Length) {
                return false;
        }
        bc_GenericType* bl =
            bc_BaselineType(BC_MEMBER_TYPE(superM), BC_MEMBER_TYPE(subM));
        assert(bl != NULL);
        //全ての引数を比較
        for (int i = 0; i < superM->Parameters->Length; i++) {
                bc_Parameter* superP =
                    ((bc_Parameter*)bc_AtVector(superM->Parameters, i));
                bc_Parameter* subP =
                    ((bc_Parameter*)bc_AtVector(subM->Parameters, i));
                bc_GenericType* superGT = superP->GType;
                bc_GenericType* subGT = subP->GType;

                bc_CallFrame* cfr = bc_PushCallContext(cctx, FRAME_RESOLVE_T);
                cfr->Kind.Resolve.GType = bl;
                bc_GenericType* superGT2 = bc_ApplyGenericType(superGT, cctx);
                bc_PopCallContext(cctx);
                //		assert(!GenericType_equals(superGT, superGT2));

                //		GenericType_diff(superGT, superGT2);
                if (bc_DistanceGenericType(superGT2, subGT, cctx) != 0) {
                        return false;
                }
        }
        bc_GenericType* superRet = superM->ReturnGType;
        bc_GenericType* subRet = subM->ReturnGType;
        bc_CallFrame* cfr = bc_PushCallContext(cctx, FRAME_RESOLVE_T);
        cfr->Kind.Resolve.GType = bl;
        bc_GenericType* superRet2 = bc_ApplyGenericType(superRet, cctx);
        //	GenericType_diff(superRet, superRet2);
        //	assert(!GenericType_equals(superRet, superRet2));
        int ret = bc_DistanceGenericType(superRet2, subRet, cctx);
        bc_PopCallContext(cctx);
        return ret != -1;
}

int bc_GetGenericIndexForMethod(bc_Method* self, bc_StringView namev) {
        int ret = -1;
        for (int i = 0; i < self->TypeParameters->Length; i++) {
                bc_TypeParameter* e =
                    (bc_TypeParameter*)bc_AtVector(self->TypeParameters, i);
                if (e->Name == namev) {
                        ret = i;
                        break;
                }
        }
        return ret;
}

void bc_DeleteMethod(bc_Method* self) {
        bc_DeleteVector(self->TypeParameters, delete_type_parameter);
        bc_DeleteVector(self->Parameters, delete_parameter);
        if (self->Type == METHOD_TYPE_SCRIPT_T) {
                bc_DeleteScriptMethod(self->Kind.Script);
        } else if (self->Type == METHOD_TYPE_NATIVE_T) {
                bc_DeleteNativeMethod(self->Kind.Native);
        }
        MEM_FREE(self);
}

bc_StringView bc_MangleMethod(bc_Method* self) {
        bc_Buffer* ret = bc_NewBuffer();
        bc_AppendsBuffer(ret, bc_Ref2Str(self->Name));
        //引数が一つもないので終了
        if (self->Parameters->Length == 0) {
                char* raw = bc_ReleaseBuffer(ret);
                bc_StringView sv = bc_InternString(raw);
                MEM_FREE(raw);
                return sv;
        }
        for (int i = 0; i < self->Parameters->Length; i++) {
                bc_Parameter* e =
                    (bc_Parameter*)bc_AtVector(self->Parameters, i);
                bc_GenericType* gt = e->GType;
                bc_AppendBuffer(ret, '_');
                if (gt->CoreType == NULL) {
                        //ジェネリックの場合は methodname_c0 のように
                        //何番目の型変数であるかを入れる
                        if (gt->Tag == GENERIC_TYPE_TAG_CLASS_T) {
                                bc_AppendBuffer(ret, 'c');
                        } else if (gt->Tag == GENERIC_TYPE_TAG_METHOD_T) {
                                bc_AppendBuffer(ret, 'm');
                        } else {
                                assert(false);
                        }
                        //数値 -> 文字
                        char buff[256];
                        memset(buff, '\0', 256);
                        sprintf(buff, "%d", gt->VirtualTypeIndex);
                        bc_AppendsBuffer(ret, buff);
                } else {
                        bc_AppendsBuffer(
                            ret, bc_Ref2Str(bc_GetTypeFullName(gt->CoreType)));
                }
        }
        char* raw = bc_ReleaseBuffer(ret);
        bc_StringView sv = bc_InternString(raw);
        MEM_FREE(raw);
        return sv;
}

bc_StringView bc_GetMethodUniqueName(bc_Method* self) {
        bc_Buffer* ret = bc_NewBuffer();
        bc_AppendsBuffer(ret,
                         bc_Ref2Str(bc_GetTypeFullName(BC_MEMBER_TYPE(self))));
        bc_AppendsBuffer(ret, bc_Ref2Str(bc_MangleMethod(self)));
        char* raw = bc_ReleaseBuffer(ret);
        bc_StringView sv = bc_InternString(raw);
        MEM_FREE(raw);
        return sv;
}

bool bc_IsCoroutineMethod(bc_Method* self) {
        bc_Type* iteratorT = bc_FindTypeFromNamespace(
            bc_GetLangNamespace(), bc_InternString("Iterator"));
        return (iteratorT && self->ReturnGType->CoreType == iteratorT);
}

bool bc_IsYieldMethod(bc_Method* self, bc_Vector* stmt_list, bool* error) {
        (*error) = false;
        if (self->Type != METHOD_TYPE_SCRIPT_T || !bc_IsCoroutineMethod(self)) {
                return false;
        }
        int yield_ret = 0;
        int ret = 0;
        for (int i = 0; i < stmt_list->Length; i++) {
                int yrtemp = 0;
                int rtemp = 0;
                bc_ILStatement* e = (bc_ILStatement*)bc_AtVector(stmt_list, i);
                method_count(e, &yrtemp, &rtemp);
                yield_ret += yrtemp;
                ret += rtemp;
        }
        // yield return, return の混在
        if (yield_ret > 0 && ret > 0) {
                (*error) = true;
                return true;
        }
        return yield_ret > 0 ? true : false;
}

bc_Type* bc_CreateIteratorTypeFromMethod(bc_Method* self, bc_ClassLoader* cll,
                                         bc_Vector* stmt_list) {
        bc_CallContext* lCctx = bc_NewCallContext(CALL_CTOR_T);
        bc_CallFrame* lCfr = bc_PushCallContext(lCctx, FRAME_RESOLVE_T);
        lCfr->Kind.Resolve.GType = self->ReturnGType;
        bc_StringView iterName = bc_GetMethodUniqueName(self);
        bc_Type* iterT = bc_FindTypeFromNamespace(bc_GetLangNamespace(),
                                                  bc_InternString("Iterator"));
        //イテレータの実装クラスを登録
        bc_GenericType* iterImplGT =
            bc_ApplyGenericType(self->ReturnGType, lCctx);
        bc_Class* iterImplC = bc_NewClassProxy(iterImplGT, iterName);
        bc_Type* iterImplT = bc_WrapClass(iterImplC);
        bc_AddTypeNamespace(bc_GetPlaceholderNamespace(), iterImplT);
        bc_InitGenericSelf(iterImplT, 0);
        //イテレータのコンストラクタ追加
        int op_len = 0;
        bc_AddMethodClass(iterImplC, create_has_next(self, iterImplT, cll,
                                                     stmt_list, &op_len));
        bc_AddMethodClass(
            iterImplC, create_next(self, iterImplT, cll,
                                   bc_AtVector(self->ReturnGType->TypeArgs, 0),
                                   stmt_list, &op_len));
        bc_AddConstructorClass(
            iterImplC, create_delegate_ctor(self, iterImplT, cll, op_len));
        bc_PopCallContext(lCctx);
        bc_DeleteCallContext(lCctx);
        return iterImplT;
}

// private
static void delete_parameter(bc_VectorItem item) {
        bc_Parameter* e = (bc_Parameter*)item;
        bc_DeleteParameter(e);
}

static void delete_type_parameter(bc_VectorItem item) {
        bc_TypeParameter* e = (bc_TypeParameter*)item;
        bc_DeleteTypeParameter(e);
}

static void method_count(bc_ILStatement* s, int* yield_ret, int* ret) {
        switch (s->Type) {
                case ILSTMT_IF_T: {
                        // if() { ... }
                        bc_ILIf* sif = s->Kind.If;
                        for (int i = 0; i < sif->Body->Length; i++) {
                                method_count(
                                    (bc_ILStatement*)bc_AtVector(sif->Body, i),
                                    yield_ret, ret);
                        }
                        for (int i = 0; i < sif->ElifList->Length; i++) {
                                bc_ILElif* seif =
                                    (bc_ILElif*)bc_AtVector(sif->ElifList, i);
                                bc_Vector* body = seif->Body;
                                for (int j = 0; j < body->Length; j++) {
                                        method_count(
                                            (bc_ILStatement*)bc_AtVector(body,
                                                                         j),
                                            yield_ret, ret);
                                }
                        }
                        for (int i = 0; i < sif->Else->Body->Length; i++) {
                                bc_ILStatement* e =
                                    bc_AtVector(sif->Else->Body, i);
                                method_count(e, yield_ret, ret);
                        }
                        break;
                }
                case ILSTMT_PROC_T:
                case ILSTMT_VARIABLE_DECL_T:
                case ILSTMT_VARIABLE_INIT_T:
                        break;
                case ILSTMT_RETURN_T:
                        (*ret)++;
                        break;
                case ILSTMT_WHILE_T: {
                        bc_ILWhile* whi = s->Kind.While;
                        for (int i = 0; i < whi->Statements->Length; i++) {
                                bc_ILStatement* e =
                                    bc_AtVector(whi->Statements, i);
                                method_count(e, yield_ret, ret);
                        }
                        break;
                }
                case ILSTMT_BREAK_T:
                case ILSTMT_CONTINUE_T:
                case ILSTMT_INFERENCED_TYPE_INIT_T:
                        break;
                case ILSTMT_TRY_T: {
                        bc_ILTry* tr = s->Kind.Try;
                        for (int i = 0; i < tr->Statements->Length; i++) {
                                bc_ILStatement* e =
                                    (bc_ILStatement*)bc_AtVector(tr->Statements,
                                                                 i);
                                method_count(e, yield_ret, ret);
                        }
                        bc_Vector* catches = tr->Catches;
                        for (int i = 0; i < catches->Length; i++) {
                                bc_ILCatch* ce =
                                    (bc_ILCatch*)bc_AtVector(catches, i);
                                for (int j = 0; j < ce->Statements->Length;
                                     j++) {
                                        bc_ILStatement* e =
                                            (bc_ILStatement*)bc_AtVector(
                                                ce->Statements, j);
                                        method_count(e, yield_ret, ret);
                                }
                        }
                        break;
                }
                case ILSTMT_THROW_T:
                case ILSTMT_ASSERT_T:
                case ILSTMT_DEFER_T:
                        break;
                case ILSTMT_YIELD_RETURN_T:
                        (*yield_ret)++;
                        break;
                case ILSTMT_YIELD_BREAK_T:
                default:
                        // ERROR("ステートメントをダンプ出来ませんでした。");
                        break;
        }
}

static bc_Constructor* create_delegate_ctor(bc_Method* self, bc_Type* ty,
                                            bc_ClassLoader* cll, int op_len) {
        //イテレータのコンストラクタを作成
        bc_Constructor* iterCons = bc_NewConstructor();
        bc_Enviroment* envIterCons = bc_NewEnviroment();
        //コルーチンを生成したオブジェクトを受け取るパラメータ追加
        bc_Parameter* coroOwnerParam =
            bc_NewParameter(bc_InternString("owner"));
        bc_PushVector(iterCons->Parameters, coroOwnerParam);
        envIterCons->ContextRef = cll;
        //コルーチンに渡された引数を引き継ぐパラメータ追加
        for (int i = 0; i < self->Parameters->Length; i++) {
                bc_Parameter* methP =
                    (bc_Parameter*)bc_AtVector(self->Parameters, i);
                bc_Parameter* consP = bc_NewParameter(methP->Name);
                consP->GType = methP->GType;
                bc_PushVector(iterCons->Parameters, consP);
        }
        for (int i = 0; i < iterCons->Parameters->Length; i++) {
                bc_Parameter* e =
                    (bc_Parameter*)bc_AtVector(iterCons->Parameters, i);
                bc_EntrySymbolTable(envIterCons->Symboles, e->GType, e->Name);
                //実引数を保存
                // 0番目は this のために開けておく
                bc_AddOpcodeBuf(envIterCons->Bytecode, (bc_VectorItem)OP_STORE);
                bc_AddOpcodeBuf(envIterCons->Bytecode, (bc_VectorItem)(i + 1));
        }
        //親クラスへ連鎖
        bc_AddOpcodeBuf(envIterCons->Bytecode, (bc_VectorItem)OP_CHAIN_SUPER);
        bc_AddOpcodeBuf(envIterCons->Bytecode, (bc_VectorItem)0);
        bc_AddOpcodeBuf(envIterCons->Bytecode, (bc_VectorItem)0);
        bc_AddOpcodeBuf(envIterCons->Bytecode,
                        (bc_VectorItem)sizeof(bc_Coroutine));
        //ここでsizeof(Coroutine) を渡すように
        //このクラスのフィールドを確保
        bc_AddOpcodeBuf(envIterCons->Bytecode, (bc_VectorItem)OP_ALLOC_FIELD);
        bc_AddOpcodeBuf(envIterCons->Bytecode,
                        (bc_VectorItem)ty->AbsoluteIndex);
        bc_AddOpcodeBuf(envIterCons->Bytecode, OP_CORO_INIT);
        bc_AddOpcodeBuf(envIterCons->Bytecode, iterCons->Parameters->Length);
        bc_AddOpcodeBuf(envIterCons->Bytecode, op_len);
        iterCons->Env = envIterCons;
        return iterCons;
}

static bc_Method* create_has_next(bc_Method* self, bc_Type* ty,
                                  bc_ClassLoader* cll, bc_Vector* stmt_list,
                                  int* out_op_len) {
        bc_Method* mt = bc_NewMethod(bc_InternString("moveNext"));
        mt->ReturnGType = BC_GENERIC_BOOL;
        BC_MEMBER_MODIFIER(mt) = MODIFIER_NONE_T;
        BC_MEMBER_ACCESS(mt) = ACCESS_PUBLIC_T;
        mt->Type = METHOD_TYPE_SCRIPT_T;
        bc_ScriptMethod* smt = bc_NewScriptMethod();
        bc_Enviroment* envSmt = bc_NewEnviroment();
        bc_CallContext* cctx = bc_NewCallContext(CALL_METHOD_T);
        cctx->Scope = BC_MEMBER_TYPE(self)->Location;
        cctx->Ty = BC_MEMBER_TYPE(self);
        cctx->Kind.Method = self;
        envSmt->ContextRef = cll;

        // iterate(int,int)のint,intを受け取る
        for (int i = 0; i < self->Parameters->Length; i++) {
                bc_Parameter* e = bc_AtVector(self->Parameters, i);
                bc_EntrySymbolTable(envSmt->Symboles, e->GType, e->Name);
                //実引数を保存
                // 0番目は this のために開けておく
                // AddOpcodeBuf(envSmt->Bytecode, (VectorItem)OP_STORE);
                // AddOpcodeBuf(envSmt->Bytecode, (VectorItem)(i + 1));
        }
        bc_AddOpcodeBuf(envSmt->Bytecode, (bc_VectorItem)OP_STORE);
        bc_AddOpcodeBuf(envSmt->Bytecode, (bc_VectorItem)0);
        bc_AddOpcodeBuf(envSmt->Bytecode, (bc_VectorItem)OP_CORO_SWAP_SELF);
        bc_AddOpcodeBuf(envSmt->Bytecode, (bc_VectorItem)OP_CORO_RESUME);
        for (int i = 0; i < stmt_list->Length; i++) {
                bc_ILStatement* e = (bc_ILStatement*)bc_AtVector(stmt_list, i);
                bc_LoadILStmt(e, envSmt, cctx);
        }
        for (int i = 0; i < stmt_list->Length; i++) {
                bc_ILStatement* e = (bc_ILStatement*)bc_AtVector(stmt_list, i);
                bc_GenerateILStmt(e, envSmt, cctx);
        }
        bc_AddOpcodeBuf(envSmt->Bytecode, OP_CORO_EXIT);
        if (bc_GetTypeName(BC_MEMBER_TYPE(self)) == bc_InternString("Base")) {
                //	DumpEnviromentOp(envSmt, 0);
        }
        (*out_op_len) = envSmt->Bytecode->Instructions->Length;
        bc_DeleteCallContext(cctx);
        smt->Env = envSmt;
        mt->Kind.Script = smt;
        BC_MEMBER_TYPE(mt) = ty;
        return mt;
}

static bc_Method* create_next(bc_Method* self, bc_Type* ty, bc_ClassLoader* cll,
                              bc_GenericType* a, bc_Vector* stmt_list,
                              int* out_op_len) {
        bc_Method* mt = bc_NewMethod(bc_InternString("current"));
        mt->ReturnGType = a;
        BC_MEMBER_MODIFIER(mt) = MODIFIER_NONE_T;
        BC_MEMBER_ACCESS(mt) = ACCESS_PUBLIC_T;
        mt->Type = METHOD_TYPE_SCRIPT_T;
        bc_ScriptMethod* smt = bc_NewScriptMethod();
        bc_Enviroment* envSmt = bc_NewEnviroment();
        bc_CallContext* cctx = bc_NewCallContext(CALL_METHOD_T);
        cctx->Scope = BC_MEMBER_TYPE(self)->Location;
        cctx->Ty = BC_MEMBER_TYPE(self);
        cctx->Kind.Method = mt;

        bc_AddOpcodeBuf(envSmt->Bytecode, (bc_VectorItem)OP_STORE);
        bc_AddOpcodeBuf(envSmt->Bytecode, (bc_VectorItem)0);
        bc_AddOpcodeBuf(envSmt->Bytecode, (bc_VectorItem)OP_CORO_SWAP_SELF);
        bc_AddOpcodeBuf(envSmt->Bytecode, (bc_VectorItem)OP_CORO_CURRENT);

        envSmt->ContextRef = cll;
        cctx->Scope = BC_MEMBER_TYPE(self)->Location;
        cctx->Ty = BC_MEMBER_TYPE(self);
        cctx->Kind.Method = self;
        smt->Env = envSmt;
        mt->Kind.Script = smt;
        BC_MEMBER_TYPE(mt) = ty;
        bc_DeleteCallContext(cctx);
        // DumpEnviromentOp(envSmt, 0);
        return mt;
}

static bc_Vector* method_vm_args(bc_Method* self, bc_Frame* fr, bc_Frame* a) {
        bc_Vector* args = bc_NewVector();
        //引数を引き継ぐ
        int len = self->Parameters->Length;
        for (int i = 0; i < len; i++) {
                bc_Object* ARG = bc_PopVector(fr->ValueStack);
                assert(ARG != NULL);
                bc_AssignVector(a->VariableTable, (len - i), ARG);
                bc_AssignVector(args, (len - i), ARG->GType);
        }
        return args;
}

static bc_Vector* method_vm_typeargs(bc_Method* self, bc_Frame* fr,
                                     bc_Frame* a) {
        //メソッドに渡された型引数を引き継ぐ
        bc_Vector* typeargs = bc_NewVector();
        int typeparams = self->TypeParameters->Length;
        for (int i = 0; i < typeparams; i++) {
                bc_VectorItem e = bc_PopVector(fr->TypeArgs);
                bc_AssignVector(a->TypeArgs, (typeparams - i) - 1, e);
                bc_AssignVector(typeargs, (typeparams - i) - 1, e);
        }
        return typeargs;
}