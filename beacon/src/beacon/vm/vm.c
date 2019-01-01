#include "vm.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../env/TYPE_IMPL.h"
#include "../env/class_loader.h"
#include "../env/constructor.h"
#include "../env/coroutine.h"
#include "../env/exception.h"
#include "../env/field.h"
#include "../env/generic_type.h"
#include "../env/heap.h"
#include "../env/method.h"
#include "../env/object.h"
#include "../env/operator_overload.h"
#include "../env/property.h"
#include "../env/script_context.h"
#include "../env/type_interface.h"
#include "../lib/bc_library_interface.h"
#include "../lib/beacon/lang/array.h"
#include "../util/mem.h"
#include "../util/string_buffer.h"
#include "../util/text.h"
#include "../util/vector.h"
#include "defer_context.h"
#include "frame.h"
#include "label.h"
#include "line_range.h"
#include "script_thread.h"
#include "vm_trace.h"
#include "yield_context.h"
#if defined(_MSC_VER)
#pragma warning(disable : 4996)
#endif
// proto
static void vm_run(bc_Frame* self, bc_Enviroment* env, int pos, int deferStart);
static void pushv(bc_Frame* self, bc_Object* a);
static bc_Object* popv(bc_Frame* self);
static bc_Object* topv(bc_Frame* self);
static void setv(bc_Frame* self, int index, bc_Object* o);
static bc_Object* getv(bc_Frame* self, int index);
static int topvi(bc_Frame* self);
static double topvd(bc_Frame* self);
static char topvc(bc_Frame* self);
static char* topvs(bc_Frame* self);
static bool topvb(bc_Frame* self);

static int popvi(bc_Frame* self);
static double popvd(bc_Frame* self);
static char popvc(bc_Frame* self);
static char* popvs(bc_Frame* self);
static bool popvb(bc_Frame* self);
static void remove_from_parent(bc_Frame* self);
static void frame_markStatic(bc_Field* item);
static void vm_delete_defctx(bc_VectorItem e);
static bool throw_npe(bc_Frame* self, bc_Object* o);
static char* create_error_message(bc_Frame* self, bc_Enviroment* env, int pc);
static bc_StringView gVMError = BC_ZERO_VIEW;
static bool validate(bc_Frame* self, int source_len, int* pcDest);
static void terminate(bc_Frame* self);
static void uncaught(bc_Frame* self, bc_Enviroment* env, int pc);
static void mark_exception(bc_Frame* self, bc_Object* exc);

// Stack Top
#define STI(a) topvi(a)
#define STD(a) topvd(a)
#define STC(a) topvc(a)
#define STS(a) topvs(a)
#define STB(a) topvb(a)

// Stack Pop
#define SPI(a) popvi(a)
#define SPD(a) popvd(a)
#define SPC(a) popvc(a)
#define SPS(a) popvs(a)
#define SPB(a) popvb(a)

// Reference Store

void bc_ExecuteVM(bc_Frame* self, bc_Enviroment* env) {
        bc_ResumeVM(self, env, 0);
}

void bc_ResumeVM(bc_Frame* self, bc_Enviroment* env, int pos) {
        self->DeferList = bc_NewVector();
        vm_run(self, env, pos, -1);
        while (self->DeferList->Length > 0) {
                bc_DeferContext* defctx =
                    (bc_DeferContext*)bc_PopVector(self->DeferList);
                bc_Label* offset = defctx->Offset;
                bc_Vector* save = self->VariableTable;
                self->VariableTable = defctx->VariableTable;
                vm_run(self, env, offset->Cursor, offset->Cursor);
                self->VariableTable = save;
                bc_DeleteDeferContext(defctx);
        }
        bc_DeleteVector(self->DeferList, bc_VectorDeleterOfNull);
        self->DeferList = NULL;
}

void bc_ThrowVM(bc_Frame* self, bc_Object* exc) {
        bc_Frame* temp = self;
        do {
                temp->Exception = exc;
                temp = temp->Parent;
        } while (temp != NULL);
}

void bc_CatchVM(bc_Frame* self) {
        if (self == NULL) {
                return;
        }
        if (self->Parent != NULL) {
                bc_CatchVM(self->Parent);
        }
        self->IsValidate = false;
        if (self->Exception != NULL) {
                self->Exception->Paint = PAINT_UNMARKED_T;
                self->Exception = NULL;
        }
}

bc_StringView bc_GetVMErrorMessage() { return gVMError; }

// private
static void vm_run(bc_Frame* self, bc_Enviroment* env, int pos,
                   int deferStart) {
        assert(env != NULL);
        bc_ScriptContext* ctx = bc_GetScriptContext();
        int source_len = env->Bytecode->Instructions->Length;
        self->ContextRef = env;
        for (int IDX = pos; IDX < source_len; IDX++) {
                //このVMの子要素で例外がスローされ、
                //それを子要素自身で処理できなかった場合には、
                //自分で処理を試みます。
                if (self->IsValidate) {
                        if (!validate(self, source_len, &IDX)) {
                                break;
                        }
                }
                if (self->IsTerminate) {
                        break;
                }
                self->PC = IDX;
                bc_Opcode b = (bc_Opcode)bc_GetEnviromentSourceAt(env, IDX);
                switch (b) {
                        // int & int
                        case OP_IADD:
                                pushv(self,
                                      bc_GetIntObject(SPI(self) + SPI(self)));
                                break;
                        case OP_ISUB:
                                pushv(self,
                                      bc_GetIntObject(SPI(self) - SPI(self)));
                                break;
                        case OP_IMUL:
                                pushv(self,
                                      bc_GetIntObject(SPI(self) * SPI(self)));
                                break;
                        case OP_IDIV: {
                                int a = SPI(self);
                                int b = SPI(self);
                                assert(b != 0);
                                pushv(self, bc_GetIntObject(a / b));
                                break;
                        }
                        case OP_IMOD:
                                pushv(self,
                                      bc_GetIntObject(SPI(self) % SPI(self)));
                                break;
                        case OP_IBIT_OR: {
                                int a = SPI(self);
                                int b = SPI(self);
                                pushv(self, bc_GetIntObject(a | b));
                                break;
                        }
                        case OP_ILOGIC_OR: {
                                int a = SPI(self);
                                int b = SPI(self);
                                pushv(self, bc_GetIntObject(a || b));
                                break;
                        }
                        case OP_IBIT_AND: {
                                int a = SPI(self);
                                int b = SPI(self);
                                pushv(self, bc_GetIntObject(a & b));
                                break;
                        }
                        case OP_ILOGIC_AND: {
                                // SPI(self) をそのまま埋めると正常に動作しない
                                //おそらくマクロの展開によるもの
                                //短絡評価のせいだった
                                int a = SPI(self);
                                int b = SPI(self);
                                pushv(self, bc_GetIntObject(a && b));
                                break;
                        }
                        case OP_IEQ:
                                pushv(self,
                                      bc_GetBoolObject(SPI(self) == SPI(self)));
                                break;
                        case OP_INOTEQ:
                                pushv(self,
                                      bc_GetBoolObject(SPI(self) != SPI(self)));
                                break;
                        case OP_IGT:
                                pushv(self,
                                      bc_GetBoolObject(SPI(self) > SPI(self)));
                                break;
                        case OP_IGE:
                                pushv(self,
                                      bc_GetBoolObject(SPI(self) >= SPI(self)));
                                break;
                        case OP_ILT: {
                                bc_Object* a_ = popv(self);
                                bc_Object* b_ = popv(self);
                                pushv(self,
                                      bc_GetBoolObject(bc_ObjectToInt(a_) <
                                                       bc_ObjectToInt(b_)));
                                break;
                        }
                        case OP_ILE:
                                pushv(self,
                                      bc_GetBoolObject(SPI(self) <= SPI(self)));
                                break;
                        case OP_ILSH:
                                pushv(self,
                                      bc_GetIntObject(SPI(self) << SPI(self)));
                                break;
                        case OP_IRSH:
                                pushv(self,
                                      bc_GetIntObject(SPI(self) >> SPI(self)));
                                break;
                        case OP_IEXCOR:
                                pushv(self,
                                      bc_GetIntObject(SPI(self) ^ SPI(self)));
                                break;
                        case OP_IFLIP:
                                pushv(self, bc_GetIntObject(~SPI(self)));
                                break;
                        case OP_CEQ:
                                pushv(self,
                                      bc_GetBoolObject(SPC(self) == SPC(self)));
                                break;
                        case OP_CNOTEQ:
                                pushv(self,
                                      bc_GetBoolObject(SPC(self) != SPC(self)));
                                break;
                        case OP_CGT:
                                pushv(self,
                                      bc_GetBoolObject(SPC(self) > SPC(self)));
                                break;
                        case OP_CGE:
                                pushv(self,
                                      bc_GetBoolObject(SPC(self) >= SPC(self)));
                                break;
                        case OP_CLT:
                                pushv(self,
                                      bc_GetBoolObject(SPC(self) < SPC(self)));
                                break;
                        case OP_CLE:
                                pushv(self,
                                      bc_GetBoolObject(SPC(self) <= SPC(self)));
                                break;
                                // double & double
                        case OP_DADD:
                                pushv(self,
                                      bc_NewDouble(SPD(self) + SPD(self)));
                                break;
                        case OP_DSUB:
                                pushv(self,
                                      bc_NewDouble(SPD(self) - SPD(self)));
                                break;
                        case OP_DMUL:
                                pushv(self,
                                      bc_NewDouble(SPD(self) * SPD(self)));
                                break;
                        case OP_DDIV:
                                pushv(self,
                                      bc_NewDouble(SPD(self) / SPD(self)));
                                break;
                        case OP_DMOD:
                                pushv(self,
                                      bc_NewDouble((double)((int)SPD(self) %
                                                            (int)SPD(self))));
                                break;
                        case OP_DEQ:
                                pushv(self,
                                      bc_GetBoolObject(SPD(self) == SPD(self)));
                                break;
                        case OP_DNOTEQ:
                                pushv(self,
                                      bc_GetBoolObject(SPD(self) != SPD(self)));
                                break;
                        case OP_DGT:
                                pushv(self,
                                      bc_GetBoolObject(SPD(self) > SPD(self)));
                                break;
                        case OP_DGE:
                                pushv(self,
                                      bc_GetBoolObject(SPD(self) >= SPD(self)));
                                break;
                        case OP_DLT:
                                pushv(self,
                                      bc_GetBoolObject(SPD(self) < SPD(self)));
                                break;
                        case OP_DLE:
                                pushv(self,
                                      bc_GetBoolObject(SPD(self) <= SPD(self)));
                                break;
                        case OP_INEG:
                                pushv(self, bc_GetIntObject(-SPI(self)));
                                break;
                        case OP_DNEG:
                                pushv(self, bc_NewDouble(-SPD(self)));
                                break;
                        case OP_BNOT: {
                                bool a = SPB(self);
                                pushv(self, bc_GetBoolObject(!a));
                                break;
                        }
                                // TODO:短絡評価していない
                        case OP_BBIT_OR: {
                                bool ab = SPB(self);
                                bool bb = SPB(self);
                                pushv(self, bc_GetBoolObject(ab | bb));
                                break;
                        }
                        case OP_BLOGIC_OR: {
                                bool ab = SPB(self);
                                bool bb = SPB(self);
                                pushv(self, bc_GetBoolObject(ab || bb));
                                break;
                        }
                        case OP_BBIT_AND: {
                                bool ab = SPB(self);
                                bool bb = SPB(self);
                                pushv(self, bc_GetBoolObject(ab & bb));
                                break;
                        }
                        case OP_BLOGIC_AND: {
                                bool ab = SPB(self);
                                bool bb = SPB(self);
                                pushv(self, bc_GetBoolObject(ab && bb));
                                break;
                        }
                        case OP_BEXCOR:
                                pushv(self,
                                      bc_GetBoolObject(SPB(self) ^ SPB(self)));
                                break;
                        case OP_BFLIP:
                                pushv(self, bc_GetBoolObject(~SPB(self)));
                                break;
                                // push const
                        case OP_SHCONST: {
                                int index =
                                    (int)bc_GetEnviromentSourceAt(env, ++IDX);
                                bc_Object* o =
                                    (bc_Object*)bc_GetEnviromentCShortAt(env,
                                                                         index);
                                pushv(self, o);
                                break;
                        }
                        case OP_ICONST: {
                                int index =
                                    (int)bc_GetEnviromentSourceAt(env, ++IDX);
                                bc_Object* o =
                                    (bc_Object*)bc_GetEnviromentCIntAt(env,
                                                                       index);
                                bc_Integer* i = o;
                                pushv(self, o);
                                break;
                        }
                        case OP_LCONST: {
                                int index =
                                    (int)bc_GetEnviromentSourceAt(env, ++IDX);
                                bc_Object* o =
                                    (bc_Object*)bc_GetEnviromentCLongAt(env,
                                                                        index);
                                pushv(self, o);
                                break;
                        }
                        case OP_FCONST: {
                                int fci =
                                    (int)bc_GetEnviromentSourceAt(env, ++IDX);
                                bc_Object* fobj =
                                    bc_GetEnviromentCFloatAt(env, fci);
                                bc_Float* flo = fobj;
                                pushv(self, fobj);
                                break;
                        }
                        case OP_DCONST: {
                                int index =
                                    (int)bc_GetEnviromentSourceAt(env, ++IDX);
                                bc_Object* d =
                                    bc_GetEnviromentCDoubleAt(env, index);
                                pushv(self, d);
                                break;
                        }
                        case OP_CCONST: {
                                int index =
                                    (int)bc_GetEnviromentSourceAt(env, ++IDX);
                                bc_Object* c =
                                    bc_GetEnviromentCCharAt(env, index);
                                pushv(self, c);
                                break;
                        }
                        case OP_SCONST: {
                                int index =
                                    (int)bc_GetEnviromentSourceAt(env, ++IDX);
                                bc_Object* cs =
                                    bc_GetEnviromentCStringAt(env, index);
                                pushv(self, cs);
                                break;
                        }
                        case OP_TRUE: {
                                pushv(self, bc_GetTrueObject());
                                break;
                        }
                        case OP_FALSE: {
                                pushv(self, bc_GetFalseObject());
                                break;
                        }
                        case OP_NULL: {
                                pushv(self, bc_GetNullObject());
                                break;
                        }
                        case OP_RETURN: {
                                IDX = source_len;
                                break;
                        }
                        case OP_THROW: {
                                //例外は呼び出し全てへ伝播
                                bc_Object* e = popv(self);
                                bc_ThrowVM(self, e);
                                bc_ScriptThread* th =
                                    bc_GetCurrentScriptThread();
                                //空ならプログラムを終了
                                if (bc_IsEmptyVector(th->TraceStack)) {
                                        terminate(self);
                                        //どこかでキャッチしようとしている
                                } else {
                                        validate(self, source_len, &IDX);
                                }
                                break;
                        }
                        case OP_TRY_ENTER: {
                                bc_ScriptThread* th =
                                    bc_GetCurrentScriptThread();
                                bc_VMTrace* trace = bc_NewVMTrace(self);
                                trace->PC = IDX;  // goto
                                bc_PushVector(th->TraceStack, trace);
                                // goto
                                IDX++;
                                // label
                                IDX++;
                                //これ以降は通常のステートメント...
                                break;
                        }
                        case OP_TRY_EXIT: {
                                bc_ScriptThread* th =
                                    bc_GetCurrentScriptThread();
                                bc_VMTrace* trace =
                                    (bc_VMTrace*)bc_PopVector(th->TraceStack);
                                bc_DeleteVMTrace(trace);
                                break;
                        }
                        case OP_TRY_CLEAR: {
                                bc_ScriptThread* th =
                                    bc_GetCurrentScriptThread();
                                bc_CatchVM(self);
                                bc_VMTrace* trace =
                                    (bc_VMTrace*)bc_PopVector(th->TraceStack);
                                bc_DeleteVMTrace(trace);
                                break;
                        }
                        case OP_HEXCEPTION: {
                                pushv(self, self->Exception);
                                break;
                        }
                        case OP_INSTANCEOF: {
                                bc_GenericType* gtype =
                                    (bc_GenericType*)bc_PopVector(
                                        self->TypeArgs);
                                bc_Object* v = popv(self);
                                int dist =
                                    bc_CdistanceGenericType(gtype, v->GType);
                                bc_Object* b = bc_GetBoolObject(dist >= 0);
                                pushv(self, b);
                                break;
                        }
                        case OP_DUP:
                                pushv(self, topv(self));
                                break;
                        case OP_POP:
                                popv(self);
                                break;
                        case OP_NOP:
                                /* no operation */
                                break;
                        case OP_NEW_OBJECT: {
                                //コンストラクタをさかのぼり、
                                //トップレベルまで到達するとこの処理によって生成が行われます。
                                // FIXME:???
                                bc_Object* o =
                                    bc_NewObject(NULL, self->ObjectSize);
                                assert(o->Paint != PAINT_ONEXIT_T);
                                pushv(self, o);
                                //これを this とする
                                setv(self, 0, o);
                                break;
                        }
                        case OP_ALLOC_FIELD: {
                                int absClsIndex =
                                    (int)bc_GetEnviromentSourceAt(env, ++IDX);
                                bc_Type* tp = (bc_Type*)bc_AtVector(
                                    ctx->TypeList, absClsIndex);
                                bc_Class* cls = BC_TYPE2CLASS(tp);
                                bc_Object* obj = topv(self);
                                //仮想関数テーブル更新
                                bc_CreateVTableClass(cls);
                                bc_Type* clsP = cls->Parent;
                                obj->GType = bc_RefGenericType(clsP);
                                obj->VPtr = cls->VT;
                                //ジェネリック型を実体化
                                if (cls->TypeParameters->Length == 0) {
                                        obj->GType = tp->GenericSelf;
                                } else {
                                        bc_GenericType* g =
                                            bc_NewGenericType(tp);
                                        for (int i = 0;
                                             i < cls->TypeParameters->Length;
                                             i++) {
                                                bc_AddArgsGenericType(
                                                    g,
                                                    (bc_GenericType*)
                                                        bc_AtVector(
                                                            self->TypeArgs, i));
                                        }
                                        obj->GType = g;
                                }
                                assert(obj->GType != NULL);
                                //フィールドの割り当て
                                bc_AllocFieldsClass(cls, obj, self);
                                assert(obj->GType != NULL);
                                break;
                        }
                        case OP_NEW_INSTANCE: {
                                //生成するクラスとコンストラクタを特定
                                int absClsIndex =
                                    (int)bc_GetEnviromentSourceAt(env, ++IDX);
                                int constructorIndex =
                                    (int)bc_GetEnviromentSourceAt(env, ++IDX);
                                bc_Type* tp = (bc_Type*)bc_AtVector(
                                    ctx->TypeList, absClsIndex);
                                assert(tp->Tag == TYPE_CLASS_T);
                                bc_Class* cls = BC_TYPE2CLASS(tp);
#if defined(DEBUG)
                                const char* clsname = bc_Ref2Str(cls->Name);
#endif
                                bc_Constructor* ctor =
                                    bc_LookupConstructor(cls, constructorIndex);
                                //新しいVMでコンストラクタを実行
                                //また、現在のVMから実引数をポップ
                                bc_Frame* sub = bc_SubFrame(self);
                                sub->Receiver = tp;
                                bc_CallFrame* cfr = bc_PushCallFrame(
                                    bc_GetScriptThreadContext(), NULL,
                                    bc_NewVector(), bc_NewVector());
                                for (int i = 0; i < ctor->Parameters->Length;
                                     i++) {
                                        bc_VectorItem e = popv(self);
                                        bc_Object* o = (bc_Object*)e;
                                        pushv(sub, e);
                                        bc_AssignVector(
                                            cfr->Args,
                                            (ctor->Parameters->Length - i),
                                            o->GType);
                                }
                                //コンストラクタに渡された型引数を引き継ぐ
                                int typeparams = cls->TypeParameters->Length;
                                for (int i = 0; i < typeparams; i++) {
                                        bc_VectorItem e =
                                            bc_PopVector(self->TypeArgs);
                                        bc_AssignVector(sub->TypeArgs,
                                                        (typeparams - i) - 1,
                                                        e);
                                        bc_AssignVector(
                                            cfr->TypeArgs,
                                            (cls->TypeParameters->Length - i),
                                            e);
                                }
                                // bc_Printi(self->level);
                                // bc_Printfln("[ %s#new ]",
                                // GetTypeName(ctor->Parent));
                                // DumpEnviromentOp(ctor->env,
                                // sub->level);
                                // DumpOpcodeBuf(ctor->env->Bytecode,
                                // sub->level);
                                bc_ExecuteVM(sub, ctor->Env);
                                bc_DeleteVector(cfr->Args,
                                                bc_VectorDeleterOfNull);
                                bc_DeleteVector(cfr->TypeArgs,
                                                bc_VectorDeleterOfNull);
                                bc_PopCallFrame(bc_GetScriptThreadContext());
                                //コンストラクタを実行した場合、
                                // Objectがスタックのトップに残っているはず
                                bc_VectorItem returnV = topv(sub);
                                bc_Object* returnO = (bc_Object*)returnV;
                                pushv(self, returnV);
                                bc_DeleteFrame(sub);
                                break;
                        }
                        case OP_CHAIN_THIS:
                        case OP_CHAIN_SUPER: {
                                int absClsIndex =
                                    (int)bc_GetEnviromentSourceAt(env, ++IDX);
                                int ctorIndex =
                                    (int)bc_GetEnviromentSourceAt(env, ++IDX);
                                int allocSize =
                                    (int)bc_GetEnviromentSourceAt(env, ++IDX);
                                if (allocSize < self->ObjectSize) {
                                        allocSize = self->ObjectSize;
                                }
                                bc_Type* tp = (bc_Type*)bc_AtVector(
                                    ctx->TypeList, absClsIndex);
                                assert(tp->Tag == TYPE_CLASS_T);
                                bc_Class* cls = tp->Kind.Class;
                                bc_Constructor* ctor =
                                    (bc_Constructor*)bc_AtVector(
                                        cls->Constructors, ctorIndex);
                                //コンストラクタを実行するためのVMを作成
                                bc_Frame* sub = bc_SubFrame(self);
                                sub->ObjectSize = allocSize;
                                sub->Receiver = tp;
                                bc_CallFrame* cfr = bc_PushCallFrame(
                                    bc_GetScriptThreadContext(), NULL,
                                    bc_NewVector(), bc_NewVector());
                                //チェインコンストラクタに渡された実引数をプッシュ
                                for (int i = 0; i < ctor->Parameters->Length;
                                     i++) {
                                        bc_Object* o = popv(self);
                                        pushv(sub, o);
                                        bc_AssignVector(
                                            cfr->Args,
                                            (ctor->Parameters->Length - i),
                                            o->GType);
                                }
                                for (int i = 0; i < self->TypeArgs->Length;
                                     i++) {
                                        bc_PushVector(cfr->TypeArgs,
                                                      self->TypeArgs);
                                }
                                bc_ExecuteVM(sub, ctor->Env);
                                bc_DeleteVector(cfr->Args,
                                                bc_VectorDeleterOfNull);
                                bc_DeleteVector(cfr->TypeArgs,
                                                bc_VectorDeleterOfNull);
                                bc_PopCallFrame(bc_GetScriptThreadContext());
                                //コンストラクタを実行した場合、
                                // Objectがスタックのトップに残っているはず
                                bc_VectorItem returnV = topv(sub);
                                bc_Object* returnO = (bc_Object*)returnV;
                                setv(self, 0, returnV);
                                pushv(self, returnV);

                                bc_DeleteFrame(sub);
                                // AllocFieldsClass(cls, returnO);
                                break;
                        }
                        case OP_THIS: {
                                pushv(self, getv(self, 0));
                                break;
                        }
                        case OP_SUPER: {
                                bc_Object* a = getv(self, 0);
                                bc_Object* super = bc_CloneObject(a);
                                super->GType =
                                    BC_TYPE2CLASS(bc_GENERIC2TYPE(a->GType))
                                        ->SuperClass;
                                super->VPtr =
                                    BC_TYPE2CLASS(
                                        bc_GENERIC2TYPE(
                                            BC_TYPE2CLASS(
                                                bc_GENERIC2TYPE(a->GType))
                                                ->SuperClass))
                                        ->VT;
                                pushv(self, super);
                                break;
                        }
                        // store,load
                        case OP_PUT_FIELD: {
                                bc_Object* assignValue = popv(self);
                                bc_Object* assignTarget = popv(self);
                                if (throw_npe(self, assignTarget)) {
                                        break;
                                }
                                assignTarget->Update = true;
                                // assert(assignTarget->Tag ==
                                // OBJECT_REF_T);
                                int fieldIndex =
                                    (int)bc_GetEnviromentSourceAt(env, ++IDX);
                                bc_AssignVector(assignTarget->Fields,
                                                fieldIndex, assignValue);
                                break;
                        }

                        case OP_GET_FIELD: {
                                bc_Object* sourceObject = popv(self);
                                if (throw_npe(self, sourceObject)) {
                                        break;
                                }
                                int fieldIndex =
                                    (int)bc_GetEnviromentSourceAt(env, ++IDX);
                                bc_Object* val = (bc_Object*)bc_AtVector(
                                    sourceObject->Fields, fieldIndex);
                                pushv(self, val);
                                break;
                        }

                        case OP_PUT_STATIC: {
                                int absClsIndex =
                                    (int)bc_GetEnviromentSourceAt(env, ++IDX);
                                int fieldIndex =
                                    (int)bc_GetEnviromentSourceAt(env, ++IDX);
                                bc_Type* tp = (bc_Type*)bc_AtVector(
                                    ctx->TypeList, absClsIndex);
                                bc_Class* cls = tp->Kind.Class;
                                bc_Field* f =
                                    bc_LookupStaticField(cls, fieldIndex);
                                bc_Object* sv = popv(self);
                                f->StaticValue = sv;
                                break;
                        }

                        case OP_GET_STATIC: {
                                int absClsIndex =
                                    (int)bc_GetEnviromentSourceAt(env, ++IDX);
                                int fieldIndex =
                                    (int)bc_GetEnviromentSourceAt(env, ++IDX);
                                bc_Type* cls = (bc_Type*)bc_AtVector(
                                    ctx->TypeList, absClsIndex);
                                bc_Field* f = bc_LookupStaticField(
                                    cls->Kind.Class, fieldIndex);
                                pushv(self, f->StaticValue);
                                break;
                        }
                        case OP_PUT_PROPERTY: {
                                bc_Object* assignValue = popv(self);
                                bc_Object* assignTarget = popv(self);
                                if (throw_npe(self, assignTarget)) {
                                        break;
                                }
                                int propIndex =
                                    (int)bc_GetEnviromentSourceAt(env, ++IDX);
                                bc_Property* pro = bc_LookupProperty(
                                    BC_TYPE2CLASS(
                                        bc_GENERIC2TYPE(assignTarget->GType)),
                                    propIndex);
                                //プロパティを実行
                                bc_Frame* sub = bc_SubFrame(self);
                                sub->Receiver = BC_MEMBER_TYPE(pro);
                                pushv(sub, assignValue);
                                pushv(sub, assignTarget);
                                bc_ExecuteVM(sub, pro->Set->Env);
                                bc_DeleteFrame(sub);
                                break;
                        }
                        case OP_GET_PROPERTY: {
                                bc_Object* sourceObject = popv(self);
                                if (throw_npe(self, sourceObject)) {
                                        break;
                                }
                                int propIndex =
                                    (int)bc_GetEnviromentSourceAt(env, ++IDX);
                                bc_Property* pro = bc_LookupProperty(
                                    BC_TYPE2CLASS(
                                        bc_GENERIC2TYPE(sourceObject->GType)),
                                    propIndex);
                                //プロパティを実行
                                bc_Frame* sub = bc_SubFrame(self);
                                sub->Receiver = BC_MEMBER_TYPE(pro);
                                pushv(sub, sourceObject);
                                bc_ExecuteVM(sub, pro->Get->Env);
                                //戻り値をスタックに残す
                                bc_VectorItem returnV = topv(sub);
                                bc_Object* returnO = (bc_Object*)returnV;
                                setv(self, 0, returnV);
                                pushv(self, returnV);
                                bc_DeleteFrame(sub);
                                break;
                        }
                        case OP_PUT_STATIC_PROPERTY: {
                                bc_Object* sv = popv(self);
                                int absClsIndex =
                                    (int)bc_GetEnviromentSourceAt(env, ++IDX);
                                int propIndex =
                                    (int)bc_GetEnviromentSourceAt(env, ++IDX);
                                bc_Type* tp = (bc_Type*)bc_AtVector(
                                    ctx->TypeList, absClsIndex);
                                bc_Class* cls = tp->Kind.Class;
                                bc_Property* p =
                                    bc_LookupStaticProperty(cls, propIndex);
                                //プロパティを実行
                                bc_Frame* sub = bc_SubFrame(self);
                                sub->Receiver = NULL;
                                pushv(sub, sv);
                                bc_ExecuteVM(sub, p->Set->Env);
                                bc_DeleteFrame(sub);
                                break;
                        }
                        case OP_GET_STATIC_PROPERTY: {
                                bc_Object* sv = popv(self);
                                int absClsIndex =
                                    (int)bc_GetEnviromentSourceAt(env, ++IDX);
                                int propIndex =
                                    (int)bc_GetEnviromentSourceAt(env, ++IDX);
                                bc_Type* tp = (bc_Type*)bc_AtVector(
                                    ctx->TypeList, absClsIndex);
                                bc_Class* cls = tp->Kind.Class;
                                bc_Property* p =
                                    bc_LookupStaticProperty(cls, propIndex);
                                //プロパティを実行
                                bc_Frame* sub = bc_SubFrame(self);
                                sub->Receiver = NULL;
                                bc_ExecuteVM(sub, p->Get->Env);
                                //戻り値をスタックに残す
                                bc_VectorItem returnV = topv(sub);
                                bc_Object* returnO = (bc_Object*)returnV;
                                setv(self, 0, returnV);
                                pushv(self, returnV);
                                bc_DeleteFrame(sub);
                                break;
                        }
                        case OP_STORE: {
                                int index =
                                    (int)bc_GetEnviromentSourceAt(env, ++IDX);
                                bc_VectorItem e = popv(self);
                                bc_Object* o = (bc_Object*)e;
                                assert(o != NULL);
                                setv(self, index, e);
                                // INFO("store");
                                break;
                        }
                        case OP_LOAD: {
                                int index =
                                    (int)bc_GetEnviromentSourceAt(env, ++IDX);
                                bc_VectorItem e = getv(self, index);
                                bc_Object* o = (bc_Object*)e;
                                assert(o != NULL);
                                pushv(self, e);
                                // INFO("load");
                                break;
                        }
                        case OP_DOWN_AS: {
                                bc_Object* o = popv(self);
                                bc_GenericType* a =
                                    bc_PopVector(self->TypeArgs);
                                a = bc_CapplyGenericType(
                                    a, bc_GetScriptThreadContext());
                                if (a->CoreType->Tag == TYPE_INTERFACE_T) {
                                        bc_Interface* inter = BC_TYPE2INTERFACE(
                                            bc_GENERIC2TYPE(a));
                                        bc_Vector* inter_list =
                                            bc_GetInterfaceTreeClass(
                                                BC_TYPE2CLASS(
                                                    bc_GENERIC2TYPE(o->GType)));
                                        int iter =
                                            bc_FindVector(inter_list, inter);
                                        bc_DeleteVector(inter_list,
                                                        bc_VectorDeleterOfNull);
                                        if (iter == -1) {
                                                pushv(self, bc_GetNullObject());
                                        } else {
                                                pushv(self, o);
                                        }
                                        break;
                                }
                                if (bc_CdistanceGenericType(o->GType, a) < 0) {
                                        pushv(self, bc_GetNullObject());
                                } else {
                                        // o = CloneObject(o);
                                        // o->GType = a;
                                        pushv(self, o);
                                }
                                break;
                        }
                        case OP_UP_AS: {
                                bc_Object* o = popv(self);
                                bc_GenericType* a =
                                    bc_PopVector(self->TypeArgs);
                                a = bc_CapplyGenericType(
                                    a, bc_GetScriptThreadContext());
                                assert(a->CoreType != NULL);
                                if (a->CoreType->Tag == TYPE_CLASS_T) {
                                        pushv(self, o);
                                } else if (a->CoreType->Tag ==
                                           TYPE_INTERFACE_T) {
                                        bc_Interface* inter = BC_TYPE2INTERFACE(
                                            bc_GENERIC2TYPE(a));
                                        bc_Vector* inter_list =
                                            bc_GetInterfaceTreeClass(
                                                BC_TYPE2CLASS(
                                                    bc_GENERIC2TYPE(o->GType)));
                                        int iter =
                                            bc_FindVector(inter_list, inter);
                                        bc_DeleteVector(inter_list,
                                                        bc_VectorDeleterOfNull);
                                        if (iter == -1) {
                                                pushv(self, bc_GetNullObject());
                                        } else {
                                                pushv(self, o);
                                        }
                                }
                                break;
                        }
                        // invoke
                        case OP_INVOKEINTERFACE: {
                                int absClassIndex =
                                    (int)bc_GetEnviromentSourceAt(env, ++IDX);
                                int methodIndex =
                                    (int)bc_GetEnviromentSourceAt(env, ++IDX);
                                bc_Type* tp =
                                    bc_AtVector(ctx->TypeList, absClassIndex);
                                bc_Object* o = topv(self);
                                if (throw_npe(self, o)) {
                                        break;
                                }
                                bc_Method* m = bc_GetImplMethodClass(
                                    o->GType->CoreType->Kind.Class, tp,
                                    methodIndex);
                                bc_CallContext* cctx =
                                    bc_GetScriptThreadContext();
                                bc_ExecuteMethod(m, self, env);
                                break;
                        }
                        case OP_INVOKESTATIC: {
                                int absClassIndex =
                                    (int)bc_GetEnviromentSourceAt(env, ++IDX);
                                int methodIndex =
                                    (int)bc_GetEnviromentSourceAt(env, ++IDX);
                                bc_Type* cls = (bc_Type*)bc_AtVector(
                                    ctx->TypeList, absClassIndex);
                                bc_Method* m = bc_LookupStaticMethod(
                                    cls->Kind.Class, methodIndex);
#if defined(DEBUG)
                                const char* clsname =
                                    bc_Ref2Str(bc_GetTypeName(cls));
                                const char* mname = bc_Ref2Str(m->Name);
#endif
                                bc_ExecuteMethod(m, self, env);
                                break;
                        }
                        case OP_INVOKEVIRTUAL: {
                                int index =
                                    (int)bc_GetEnviromentSourceAt(env, ++IDX);
                                bc_Object* o = topv(self);
                                if (throw_npe(self, o)) {
                                        break;
                                }
                                bc_Method* m = bc_LookupMethod(
                                    BC_TYPE2CLASS(bc_GENERIC2TYPE(o->GType)),
                                    index);
                                bc_ExecuteMethod(m, self, env);
                                break;
                        }
                        case OP_INVOKESPECIAL: {
                                // privateメソッドには常にレシーバがいないはず
                                //オブジェクトから直接型を取り出してしまうと具象すぎる
                                int index =
                                    (int)bc_GetEnviromentSourceAt(env, ++IDX);
                                bc_Object* o = topv(self);
                                if (throw_npe(self, o)) {
                                        break;
                                }
                                bc_Class* cl =
                                    BC_TYPE2CLASS(o->GType->CoreType);
                                if (self->Receiver != NULL) {
                                        cl = BC_TYPE2CLASS(self->Receiver);
                                }
                                bc_Method* m =
                                    (bc_Method*)bc_AtVector(cl->Methods, index);
                                bc_ExecuteMethod(m, self, env);
                                break;
                        }
                        case OP_INVOKEOPERATOR: {
                                int index =
                                    (int)bc_GetEnviromentSourceAt(env, ++IDX);
                                bc_Object* o = topv(self);
                                bc_Class* cl =
                                    BC_TYPE2CLASS(o->GType->CoreType);
#if defined(DEBUG)
                                char* clname = bc_Ref2Str(cl->Name);
#endif
                                bc_CreateOperatorVTClass(cl);
                                bc_OperatorOverload* operator_ov =
                                    (bc_OperatorOverload*)bc_AtVector(
                                        cl->OVT->Operators, index);
                                bc_ExecuteOperatorOverload(operator_ov, self,
                                                           env);
                                break;
                        }
                        case OP_CORO_INIT: {
                                bc_Object* obj = getv(self, 0);
                                int param_len =
                                    (int)bc_GetEnviromentSourceAt(env, ++IDX);
                                int op_len =
                                    (int)bc_GetEnviromentSourceAt(env, ++IDX);
                                bc_YieldContext* yctx = bc_NewYieldContext();
                                yctx->YieldOffset = 0;
                                yctx->YieldCount = 0;
                                yctx->Length = op_len;
                                yctx->Parameters = bc_NewVector();
                                // iterate(int, int) の int, int
                                // を受け取る
                                yctx->Source = getv(self, 1);
#if defined(DEBUG)
                                const char* yname =
                                    bc_GetObjectName(yctx->Source);
#endif
                                for (int i = 2; i < param_len + 1; i++) {
                                        bc_Object* a = getv(self, i);
                                        assert(a != NULL);
                                        bc_PushVector(yctx->Parameters, a);
                                }
                                bc_Coroutine* cor = (bc_Coroutine*)obj;
                                //暗黙的に生成されるイテレータ実装クラスのコンストラクタは、
                                //必ず最後に iterate()
                                //を定義したクラスのオブジェクトを受け取る。
                                cor->Context = yctx;
                                obj->Flags = obj->Flags | OBJECT_FLG_COROUTINE;
                                break;
                        }
                        case OP_CORO_NEXT: {
                                bc_Object* obj = self->Coroutine;
                                bc_Object* ret = popv(self);
                                bc_Coroutine* cor = (bc_Coroutine*)obj;
                                assert((obj->Flags & OBJECT_FLG_COROUTINE) > 0);
                                bc_YieldContext* yctx = cor->Context;
                                //この実行コードが
                                //前回からの再開によって開始した場合、それを元に戻す
                                if (yctx->VariableTable != NULL) {
                                        self->VariableTable =
                                            yctx->VariableTable;
                                        self->ValueStack = yctx->ValueStack;
                                }
                                assert(ret != NULL);
                                yctx->Stock = ret;
                                //最初に実行された yield return
                                //に時点でコピーする
                                if (yctx->VariableTable == NULL) {
                                        yctx->BackupVariableTable =
                                            bc_CloneVector(self->VariableTable);
                                        yctx->BackupValueStack = bc_NewVector();
                                }
                                yctx->YieldOffset = IDX + 1;
                                yctx->YieldCount++;
                                IDX = source_len;
                                //まだ実行できる?
                                bc_Object* hasNext = bc_GetBoolObject(
                                    yctx->YieldOffset < yctx->Length);
                                pushv(self, hasNext);
                                break;
                        }
                        case OP_CORO_EXIT: {
                                bc_Object* obj = self->Coroutine;
                                assert((obj->Flags | OBJECT_FLG_COROUTINE) > 0);
                                bc_Coroutine* cor = (bc_Coroutine*)obj;
                                bc_YieldContext* yctx = cor->Context;
                                IDX = source_len;
                                yctx->YieldOffset = source_len;
                                if (yctx->VariableTable != NULL) {
                                        self->VariableTable =
                                            yctx->VariableTable;
                                        self->ValueStack = yctx->ValueStack;
                                }
                                pushv(self, bc_GetFalseObject());
                                break;
                        }
                        case OP_CORO_RESUME: {
                                bc_Object* obj = self->Coroutine;
                                assert((obj->Flags & OBJECT_FLG_COROUTINE) > 0);
                                bc_Coroutine* cor = (bc_Coroutine*)obj;
                                bc_YieldContext* yctx = cor->Context;
                                //前回の位置が記録されているのでそこから
                                if (yctx->YieldOffset != 0) {
                                        IDX = yctx->YieldOffset - 1;
                                        yctx->VariableTable =
                                            self->VariableTable;
                                        yctx->ValueStack = self->ValueStack;
                                        self->VariableTable =
                                            yctx->BackupVariableTable;
                                        self->ValueStack =
                                            yctx->BackupValueStack;
                                }
                                break;
                        }
                        case OP_CORO_CURRENT: {
                                bc_Object* obj = self->Coroutine;
                                bc_Coroutine* cor = (bc_Coroutine*)obj;
                                assert((obj->Flags & OBJECT_FLG_COROUTINE) > 0);
                                bc_YieldContext* yctx = cor->Context;
                                pushv(self, yctx->Stock);
                                break;
                        }
                        case OP_CORO_SWAP_SELF: {
                                assert(self->Coroutine == NULL);
                                bc_Object* obj = getv(self, 0);
                                assert((obj->Flags & OBJECT_FLG_COROUTINE) > 0);
                                bc_Coroutine* cor = (bc_Coroutine*)obj;
                                bc_YieldContext* yctx = cor->Context;
                                if (yctx->IsCached) {
                                        self->Coroutine = obj;
                                        break;
                                }
#if defined(DEBUG)
                                const char* oname = bc_GetObjectName(obj);
                                const char* yname =
                                    bc_GetObjectName(yctx->Source);
#endif
                                //[0] = Array
                                //[1] = ArrayIterator
                                setv(self, 0, yctx->Source);
                                assert(yctx->Source != NULL);
                                for (int i = 0; i < yctx->Parameters->Length;
                                     i++) {
                                        bc_Object* e =
                                            bc_AtVector(yctx->Parameters, i);
                                        assert(e != NULL);
                                        setv(self, i + 1, e);
                                }
                                self->Coroutine = obj;
                                yctx->IsCached = true;
                                break;
                        }
                        case OP_GENERIC_ADD: {
                                // TODO:ここで親フレームを遡るように
                                //ジェネリックタイプを作成する
                                int depth = 0;
                                int pos = IDX;
                                bc_Vector* stack = bc_NewVector();
                                bc_Vector* counts = bc_NewVector();
                                bc_GenericType* ret = NULL;
                                while (1) {
                                        int code =
                                            (int)bc_GetEnviromentSourceAt(
                                                env, ++IDX);
                                        if (code == OP_GENERIC_ENTER) {
                                                int count = (int)
                                                    bc_GetEnviromentSourceAt(
                                                        env, ++IDX);
                                                depth++;
                                                bc_PushVector(counts, count);
                                                // PushVector(stack,
                                                // NewGenericType(NULL));
                                        } else if (code == OP_GENERIC_EXIT) {
                                                depth--;
                                                int count =
                                                    (int)bc_PopVector(counts);
                                                bc_GenericType* head =
                                                    bc_AtVector(stack, 0);
                                                for (int i = 0; i < count;
                                                     i++) {
                                                        bc_AddArgsGenericType(
                                                            head,
                                                            (bc_GenericType*)
                                                                bc_PopVector(
                                                                    stack));
                                                }
                                                if (depth == 0) {
                                                        assert(stack->Length ==
                                                               1);
                                                        ret = head;
                                                        break;
                                                }
                                        } else if (
                                            code == OP_GENERIC_UNIQUE_TYPE ||
                                            code == OP_GENERIC_INSTANCE_TYPE ||
                                            code == OP_GENERIC_STATIC_TYPE) {
                                                assert(depth > 0);
                                                int arg = (int)
                                                    bc_GetEnviromentSourceAt(
                                                        env, ++IDX);
                                                bc_GenericType* a = NULL;
                                                if (code ==
                                                    OP_GENERIC_UNIQUE_TYPE) {
                                                        a = bc_NewGenericType(
                                                            (bc_Type*)bc_AtVector(
                                                                ctx->TypeList,
                                                                arg));
                                                } else if (
                                                    code ==
                                                    OP_GENERIC_INSTANCE_TYPE) {
                                                        bc_Object* receiver =
                                                            (bc_Object*)bc_AtVector(
                                                                self->VariableTable,
                                                                0);
                                                        a = (bc_GenericType*)
                                                            bc_AtVector(
                                                                receiver->GType
                                                                    ->TypeArgs,
                                                                arg);
                                                } else if (
                                                    code ==
                                                    OP_GENERIC_STATIC_TYPE) {
                                                        a = (bc_GenericType*)
                                                            bc_AtVector(
                                                                self->TypeArgs,
                                                                arg);
                                                }
                                                bc_PushVector(stack, a);
                                        }
                                }
                                assert(ret != NULL);
                                bc_PushVector(self->TypeArgs, ret);
                                bc_DeleteVector(stack, bc_VectorDeleterOfNull);
                                bc_DeleteVector(counts, bc_VectorDeleterOfNull);
                                break;
                        }
                        case OP_GENERIC_ENTER:
                        case OP_GENERIC_UNIQUE_TYPE:
                        case OP_GENERIC_INSTANCE_TYPE:
                        case OP_GENERIC_STATIC_TYPE:
                        case OP_GENERIC_EXIT:
                                assert(false);
                                break;
                        // defer
                        case OP_DEFER_ENTER: {
                                break;
                        }
                        case OP_DEFER_EXIT: {
                                if (pos == deferStart) {
                                        IDX = source_len;
                                }
                                break;
                        }
                        case OP_DEFER_REGISTER: {
                                bc_Label* offset =
                                    (bc_Label*)bc_GetEnviromentSourceAt(env,
                                                                        ++IDX);
                                bc_Vector* bind =
                                    bc_CloneVector(self->VariableTable);
                                bc_DeferContext* defctx = bc_NewDeferContext();
                                defctx->Offset = offset;
                                defctx->VariableTable = bind;
                                bc_PushVector(self->DeferList, defctx);
                                break;
                        }
                        case OP_BREAKPOINT: {
                                break;
                        }

                        // goto
                        case OP_GOTO: {
                                bc_Label* l =
                                    (bc_Label*)bc_GetEnviromentSourceAt(env,
                                                                        ++IDX);
                                IDX = l->Cursor;
                                break;
                        }

                        case OP_GOTO_IF_TRUE: {
                                bool v = SPB(self);
                                bc_Label* l =
                                    (bc_Label*)bc_GetEnviromentSourceAt(env,
                                                                        ++IDX);
                                if (v) {
                                        IDX = l->Cursor;
                                }
                                break;
                        }

                        case OP_GOTO_IF_FALSE: {
                                bool v = SPB(self);
                                bc_Label* l =
                                    (bc_Label*)bc_GetEnviromentSourceAt(env,
                                                                        ++IDX);
                                int a = l->Cursor;
                                if (!v) {
                                        IDX = l->Cursor;
                                }
                                break;
                        }

                        default:
                                break;
                }
                //ネイティブメソッドからスローされた例外を検出
                if (self->NativeThrowPos != -1) {
                        IDX = self->NativeThrowPos;
                        self->NativeThrowPos = -1;
                }
                //キャッチされなかった例外によって終了する
                bc_ScriptThread* thr = bc_GetMainScriptThread();
                if (self->IsTerminate && !thr->IsVMDump) {
                        uncaught(self, env, IDX);
                        thr->IsVMDump = true;
                        break;
                }
        }
}

static void pushv(bc_Frame* self, bc_Object* a) {
        bc_PushVector(self->ValueStack, NON_NULL(a));
}

static bc_Object* popv(bc_Frame* self) {
        return (bc_Object*)bc_PopVector(self->ValueStack);
}

static bc_Object* topv(bc_Frame* self) {
        return (bc_Object*)bc_TopVector(self->ValueStack);
}

static void setv(bc_Frame* self, int index, bc_Object* o) {
        bc_AssignVector(self->VariableTable, index, o);
}

static bc_Object* getv(bc_Frame* self, int index) {
        return (bc_Object*)bc_AtVector(self->VariableTable, index);
}

static int topvi(bc_Frame* self) {
        bc_Object* ret = topv(self);
        assert(bc_IsIntValue(ret));
        return ((bc_Integer*)ret)->Value;
}

static double topvd(bc_Frame* self) {
        bc_Object* ret = topv(self);
        assert(bc_IsDoubleValue(ret));
        return ((bc_Double*)ret)->Value;
}

static char topvc(bc_Frame* self) {
        bc_Object* ret = topv(self);
        assert(bc_IsCharValue(ret));
        return ((bc_Char*)ret)->Value;
}

static char* topvs(bc_Frame* self) {
        bc_Object* ret = topv(self);
        bc_IsStringValue(ret);
        return bc_GetRawString(ret)->Text;
}

static bool topvb(bc_Frame* self) {
        bc_Object* ret = topv(self);
        assert(bc_IsBoolValue(ret));
        return ((bc_Bool*)ret)->Value;
}

static int popvi(bc_Frame* self) {
        bc_Object* ret = popv(self);
        assert(bc_IsIntValue(ret));
        return ((bc_Integer*)ret)->Value;
}

static double popvd(bc_Frame* self) {
        bc_Object* ret = popv(self);
        assert(bc_IsDoubleValue(ret));
        return ((bc_Double*)ret)->Value;
}

static char popvc(bc_Frame* self) {
        bc_Object* ret = popv(self);
        assert(bc_IsCharValue(ret));
        return ((bc_Char*)ret)->Value;
}

static char* popvs(bc_Frame* self) {
        bc_Object* ret = popv(self);
        assert(bc_IsStringValue(ret));
        return bc_GetRawString(ret)->Text;
}

static bool popvb(bc_Frame* self) {
        bc_Object* ret = popv(self);
        assert(bc_IsBoolValue(ret));
        return ((bc_Bool*)ret)->Value;
}

static bool throw_npe(bc_Frame* self, bc_Object* o) {
        if (bc_IsNullValue(o)) {
                mark_exception(
                    self, bc_NewSimplefException(self, "NullPointerException"));
                return true;
        }
        return false;
}

static char* create_error_message(bc_Frame* self, bc_Enviroment* env, int pc) {
        bc_Buffer* sbuf = bc_NewBuffer();
        bc_LineRange* lr = bc_FindLineRange(env->LineRangeTable, pc);
        int line = -1;
        if (lr != NULL) {
                line = lr->Lineno;
        }
        //例外のメッセージを取得
        bc_Type* exceptionT = bc_FindTypeFromNamespace(
            bc_GetLangNamespace(NULL), bc_InternString("Exception"));
        int temp = -1;
        bc_ResolveField(exceptionT->Kind.Class, bc_InternString("message"),
                        &temp);
        bc_Object* ex = self->Exception;
        bc_Object* msg = bc_AtVector(ex->Fields, temp);
        bc_Buffer* cstr = ((bc_String*)msg)->Buffer;

        char block[256] = {0};
        sprintf(block, "file: %s <%d>", env->ContextRef->FileName, line);
        bc_AppendsBuffer(sbuf, block);
        bc_AppendBuffer(sbuf, '\n');
        bc_AppendsBuffer(sbuf, cstr->Text);
        bc_AppendBuffer(sbuf, '\n');
        //スタックトレースの表示
        bc_Type* stackTraceElementT = bc_FindTypeFromNamespace(
            bc_GetLangNamespace(NULL), bc_InternString("StackTraceElement"));
        // Exception#stackTraceを取得
        temp = -1;
        bc_ResolveField(exceptionT->Kind.Class, bc_InternString("stackTrace"),
                        &temp);
        bc_Object* stackTraceObj = bc_AtVector(ex->Fields, temp);
        // StackTraceElement#fileName
        // StackTraceElement#lineIndex を取得
        int fileNameptr = -1;
        int lineIndexptr = -1;
        bc_ResolveField(stackTraceElementT->Kind.Class,
                        bc_InternString("fileName"), &fileNameptr);
        bc_ResolveField(stackTraceElementT->Kind.Class,
                        bc_InternString("lineIndex"), &lineIndexptr);
        int stackLen = bc_GetArrayLength(stackTraceObj);
        for (int i = 0; i < stackLen; i++) {
                bc_Object* e = bc_GetElementAt(stackTraceObj, i);
                bc_Object* fileNameObj = bc_AtVector(e->Fields, fileNameptr);
                bc_Object* lineIndexObj = bc_AtVector(e->Fields, lineIndexptr);
                sprintf(block, "    @%d: %s\n", bc_ObjectToInt(lineIndexObj),
                        bc_GetRawString(fileNameObj)->Text);
                bc_AppendsBuffer(sbuf, block);
        }
        return bc_ReleaseBuffer(sbuf);
}

/**
 * 現在のスレッドのトレース・スタックのトップに
 * 記録されたVMと自身が一致しているなら、
 * 自身に含まれる catch節 へジャンプします。
 * 異なるなら自身を終了して親の validate を trueにします。
 * validate が true のVM は、
 * 通常のインストラクションを実行する前にこの関数を呼び出します。
 * @param self
 * @param source_len
 * @param pcDest
 * @return このVMで処理できるなら true.
 */
static bool validate(bc_Frame* self, int source_len, int* pcDest) {
        bc_ScriptThread* th = bc_GetCurrentScriptThread();
        bc_VMTrace* trace = (bc_VMTrace*)bc_TopVector(th->TraceStack);
        self->IsValidate = true;
        //汚染
        bc_Frame* p = self->Parent;
        while (p != NULL) {
                p->IsValidate = true;
                p = p->Parent;
        }
        //ここなので catch節 へ向かう
        if (trace->SnapShot == self) {
                //ここでジャンプレベルを確認するのは
                //例えば
                // try { throw ... } catch { ... }
                //と、
                // try { throwFunc() ... } catch { ... }
                //では、
                //プログラムカウンタの位置が異なるためです。
                //
                if (trace->JumpLevel > 0) {
                        *pcDest = trace->PC + 1;
                } else
                        *pcDest = trace->PC;
                self->IsValidate = false;
                return true;
                //ここではないので終了
        } else {
                trace->JumpLevel++;
                *pcDest = source_len;
                return false;
        }
}

/**
 * selfを起点としてたどれるVM全ての terminate を true にします.
 * 実行中のVMはこのフラグによって終了します。
 * @param self
 */
static void terminate(bc_Frame* self) {
        bc_GetMainScriptThread()->IsVMCrushByException = true;
        bc_Frame* temp = self;
        do {
                temp->IsTerminate = true;
                temp = temp->Parent;
        } while (temp != NULL);
}

/**
 * 捕捉されなかった例外によってこのVMが終了するとき、
 * コールスタックの深いところから先に呼び出されます.
 * ここでどの関数呼び出しでエラーが発生したかを出力します。
 * @param self
 * @param env
 * @param pc
 */
static void uncaught(bc_Frame* self, bc_Enviroment* env, int pc) {
        char* message = create_error_message(self, env, pc);
        bc_ScriptContext* sctx = bc_GetScriptContext();
        if (sctx->IsPrintError) {
                fprintf(stderr, "%s", message);
        }
        gVMError = bc_InternString(message);
        MEM_FREE(message);
        bc_CatchVM(bc_GetRootFrame(self));
        bc_CheckSTWRequest();
}

/**
 * selfより上の全てのフレームに例外を伝播します.
 * @param self
 * @param exc
 */
static void mark_exception(bc_Frame* self, bc_Object* exc) {
        self->Exception = exc;

        bc_ThrowVM(self, exc);
        bc_ScriptThread* th = bc_GetCurrentScriptThread();
        //空ならプログラムを終了
        if (bc_IsEmptyVector(th->TraceStack)) {
                terminate(self);
                //どこかでキャッチしようとしている
        } else {
                int temp = 0;
                validate(self, self->ContextRef->Bytecode->Instructions->Length,
                         &temp);
                self->NativeThrowPos = temp;
        }
}
