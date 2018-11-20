#include "vm.h"
#include "frame.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "label.h"
#include "vm_trace.h"
#include "../env/class_loader.h"
#include "../env/type_interface.h"
#include "../env/TYPE_IMPL.h"
#include "../env/field.h"
#include "../env/method.h"
#include "../env/object.h"
#include "../env/TYPE_IMPL.h"
#include "../env/constructor.h"
#include "../env/script_context.h"
#include "../env/operator_overload.h"
#include "../env/property.h"
#include "../env/coroutine.h"
#include "../lib/beacon/lang/bc_array.h"
#include "../thread/thread.h"
#include "../util/mem.h"
#include "../util/string_buffer.h"
#include "../util/vector.h"
#include "../util/text.h"
#include "../lib/bc_library_interface.h"
#include "line_range.h"
#include "defer_context.h"
#include "../env/heap.h"
#include "../env/exception.h"
#include "../env/generic_type.h"
#include "yield_context.h"
#if defined(_MSC_VER)
#pragma warning(disable:4996)
#endif
//proto
static void vm_run(bc_Frame* self, bc_Enviroment * env, int pos, int deferStart);
static int stack_topi(bc_Frame* self);
static double stack_topd(bc_Frame* self);
static char stack_topc(bc_Frame* self);
static char* stack_tops(bc_Frame* self);
static bool stack_topb(bc_Frame* self);

static int stack_popi(bc_Frame* self);
static double stack_popd(bc_Frame* self);
static char stack_popc(bc_Frame* self);
static char* stack_pops(bc_Frame* self);
static bool stack_popb(bc_Frame* self);
static void remove_from_parent(bc_Frame* self);
static void frame_markStatic(bc_Field* item);
static void vm_delete_defctx(VectorItem e);
static bool throw_npe(bc_Frame* self, bc_Object* o);
static char* create_error_message(bc_Frame* self, bc_Enviroment* env, int pc);
static StringView gVMError = ZERO_VIEW;

//Stack Top
#define STI(a) stack_topi(a)
#define STD(a) stack_topd(a)
#define STC(a) stack_topc(a)
#define STS(a) stack_tops(a)
#define STB(a) stack_topb(a)

//Stack Pop
#define SPI(a) stack_popi(a)
#define SPD(a) stack_popd(a)
#define SPC(a) stack_popc(a)
#define SPS(a) stack_pops(a)
#define SPB(a) stack_popb(a)

//Reference Store




void bc_ExecuteVM(bc_Frame* self, bc_Enviroment* env) {
	bc_ResumeVM(self, env, 0);
}

void bc_ResumeVM(bc_Frame* self, bc_Enviroment * env, int pos) {
	self->DeferList = NewVector();
	vm_run(self, env, pos, -1);
	while(self->DeferList->Length > 0) {
		bc_DeferContext* defctx = (bc_DeferContext*)PopVector(self->DeferList);
		bc_Label* offset = defctx->Offset;
		Vector* save = self->VariableTable;
		self->VariableTable = defctx->VariableTable;
		vm_run(self, env, offset->Cursor, offset->Cursor);
		self->VariableTable = save;
		bc_DeleteDeferContext(defctx);
	}
	DeleteVector(self->DeferList, VectorDeleterOfNull);
	self->DeferList = NULL;
}

void bc_NativeThrowVM(bc_Frame* self, bc_Object * exc) {
	self->Exception = exc;

	bc_ThrowVM(self, exc);
	ScriptThread* th = GetCurrentSGThread(bc_GetCurrentScriptContext());
	//空ならプログラムを終了
	if (IsEmptyVector(th->TraceStack)) {
		bc_TerminateVM(self);
	//どこかでキャッチしようとしている
	} else {
		int temp = 0;
		bc_ValidateVM(self, self->ContextRef->Bytecode->Instructions->Length, &temp);
		self->NativeThrowPos = temp;
	}
}

void bc_ThrowVM(bc_Frame* self, bc_Object * exc) {
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
	if(self->Exception != NULL) {
		self->Exception->Paint = PAINT_UNMARKED_T;
		self->Exception = NULL;
	}
}

bool bc_ValidateVM(bc_Frame* self, int source_len, int* pcDest) {
	ScriptThread* th = GetCurrentSGThread(bc_GetCurrentScriptContext());
	bc_VMTrace* trace = (bc_VMTrace*)TopVector(th->TraceStack);
	self->IsValidate = true;
	//汚染
	bc_Frame* p = self->Parent;
	while(p != NULL) {
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
		} else *pcDest = trace->PC;
		self->IsValidate = false;
		return true;
	//ここではないので終了
	} else {
		trace->JumpLevel++;
		*pcDest = source_len;
		return false;
	}
}

void bc_TerminateVM(bc_Frame* self) {
	GetMainSGThread()->IsVMCrushByException = true;
	bc_Frame* temp = self;
	do {
		temp->IsTerminate = true;
		temp = temp->Parent;
	} while (temp != NULL);
}

void bc_UncaughtVM(bc_Frame* self, bc_Enviroment* env, int pc) {
	char* message = create_error_message(self, env, pc);
	bc_ScriptContext* sctx = bc_GetCurrentScriptContext();
	if(sctx->IsPrintError) {
		fprintf(stderr, "%s", message);
	}
	gVMError = InternString(message);
	MEM_FREE(message);
	bc_CatchVM(bc_GetRootFrame(self));
	bc_CollectHeap(bc_GetHeap());
}

StringView bc_GetVMErrorMessage() {
	return gVMError;
}


//private
static void vm_run(bc_Frame* self, bc_Enviroment * env, int pos, int deferStart) {
	assert(env != NULL);
	bc_ScriptContext* ctx = bc_GetCurrentScriptContext();
	int source_len = env->Bytecode->Instructions->Length;
	self->ContextRef = env;
	bc_Heap* he = bc_GetHeap();
	for (int IDX = pos; IDX < source_len; IDX++) {
		//このVMの子要素で例外がスローされ、
		//それを子要素自身で処理できなかった場合には、
		//自分で処理を試みます。
		if (self->IsValidate) {
			if (!bc_ValidateVM(self, source_len, &IDX)) {
				break;
			}
		}
		if(self->IsTerminate) {
			break;
		}
		self->PC = IDX;
		bc_Opcode b = (bc_Opcode)bc_GetEnviromentSourceAt(env, IDX);
		switch (b) {
			//int & int
			case OP_IADD:
				PushVector(self->ValueStack, NON_NULL(bc_GetIntObject(SPI(self) + SPI(self))));
				break;
			case OP_ISUB:
				PushVector(self->ValueStack, NON_NULL(bc_GetIntObject(SPI(self) - SPI(self))));
				break;
			case OP_IMUL:
				PushVector(self->ValueStack, NON_NULL(bc_GetIntObject(SPI(self) * SPI(self))));
				break;
			case OP_IDIV:
			{
				int a = SPI(self);
				int b = SPI(self);
				assert(b != 0);
				PushVector(self->ValueStack, NON_NULL(bc_GetIntObject(a / b)));
				break;
			}
			case OP_IMOD:
				PushVector(self->ValueStack, NON_NULL(bc_GetIntObject(SPI(self) % SPI(self))));
				break;
			case OP_IBIT_OR:
			{
				int a = SPI(self);
				int b = SPI(self);
				PushVector(self->ValueStack, NON_NULL(bc_GetIntObject(a | b)));
				break;
			}
			case OP_ILOGIC_OR:
			{
				int a = SPI(self);
				int b = SPI(self);
				PushVector(self->ValueStack, NON_NULL(bc_GetIntObject(a || b)));
				break;
			}
			case OP_IBIT_AND:
			{
				int a = SPI(self);
				int b = SPI(self);
				PushVector(self->ValueStack, NON_NULL(bc_GetIntObject(a & b)));
				break;
			}
			case OP_ILOGIC_AND:
			{
				//SPI(self) をそのまま埋めると正常に動作しない
				//おそらくマクロの展開によるもの
				//短絡評価のせいだった
				int a = SPI(self);
				int b = SPI(self);
				PushVector(self->ValueStack, NON_NULL(bc_GetIntObject(a && b)));
				break;
			}
			case OP_IEQ:
				PushVector(self->ValueStack, NON_NULL(bc_GetBoolObject(SPI(self) == SPI(self))));
				break;
			case OP_INOTEQ:
				PushVector(self->ValueStack, NON_NULL(bc_GetBoolObject(SPI(self) != SPI(self))));
				break;
			case OP_IGT:
				PushVector(self->ValueStack, NON_NULL(bc_GetBoolObject(SPI(self) > SPI(self))));
				break;
			case OP_IGE:
				PushVector(self->ValueStack, NON_NULL(bc_GetBoolObject(SPI(self) >= SPI(self))));
				break;
			case OP_ILT:
			{
				bc_Object* a_ = PopVector(self->ValueStack);
				bc_Object* b_ = PopVector(self->ValueStack);
				PushVector(self->ValueStack, NON_NULL(bc_GetBoolObject(bc_ObjectToInt(a_) < bc_ObjectToInt(b_))));
				//PushVector(self->ValueStack, GetBoolObject(SPI(self) < SPI(self)));
				break;
			}
			case OP_ILE:
				PushVector(self->ValueStack, NON_NULL(bc_GetBoolObject(SPI(self) <= SPI(self))));
				break;
			case OP_ILSH:
				PushVector(self->ValueStack, NON_NULL(bc_GetIntObject(SPI(self) << SPI(self))));
				break;
			case OP_IRSH:
				PushVector(self->ValueStack, NON_NULL(bc_GetIntObject(SPI(self) >> SPI(self))));
				break;
			case OP_IEXCOR:
				PushVector(self->ValueStack, NON_NULL(bc_GetIntObject(SPI(self) ^ SPI(self))));
				break;
			case OP_IFLIP:
				PushVector(self->ValueStack, NON_NULL(bc_GetIntObject(~SPI(self))));
				break;
			case OP_CEQ:
				PushVector(self->ValueStack, NON_NULL(bc_GetBoolObject(SPC(self) == SPC(self))));
				break;
			case OP_CNOTEQ:
				PushVector(self->ValueStack, NON_NULL(bc_GetBoolObject(SPC(self) != SPC(self))));
				break;
			case OP_CGT:
				PushVector(self->ValueStack, NON_NULL(bc_GetBoolObject(SPC(self) > SPC(self))));
				break;
			case OP_CGE:
				PushVector(self->ValueStack, NON_NULL(bc_GetBoolObject(SPC(self) >= SPC(self))));
				break;
			case OP_CLT:
				PushVector(self->ValueStack, NON_NULL(bc_GetBoolObject(SPC(self) < SPC(self))));
				break;
			case OP_CLE:
				PushVector(self->ValueStack, NON_NULL(bc_GetBoolObject(SPC(self) <= SPC(self))));
				break;
				//double & double
			case OP_DADD:
				PushVector(self->ValueStack, NON_NULL(NewDouble(SPD(self) + SPD(self))));
				break;
			case OP_DSUB:
				PushVector(self->ValueStack, NON_NULL(NewDouble(SPD(self) - SPD(self))));
				break;
			case OP_DMUL:
				PushVector(self->ValueStack, NON_NULL(NewDouble(SPD(self) * SPD(self))));
				break;
			case OP_DDIV:
				PushVector(self->ValueStack, NON_NULL(NewDouble(SPD(self) / SPD(self))));
				break;
			case OP_DMOD:
				PushVector(self->ValueStack, NON_NULL(NewDouble((double)((int)SPD(self) % (int)SPD(self)))));
				break;
			case OP_DEQ:
				PushVector(self->ValueStack, NON_NULL(bc_GetBoolObject(SPD(self) == SPD(self))));
				break;
			case OP_DNOTEQ:
				PushVector(self->ValueStack, NON_NULL(bc_GetBoolObject(SPD(self) != SPD(self))));
				break;
			case OP_DGT:
				PushVector(self->ValueStack, NON_NULL(bc_GetBoolObject(SPD(self) > SPD(self))));
				break;
			case OP_DGE:
				PushVector(self->ValueStack, NON_NULL(bc_GetBoolObject(SPD(self) >= SPD(self))));
				break;
			case OP_DLT:
				PushVector(self->ValueStack, NON_NULL(bc_GetBoolObject(SPD(self) < SPD(self))));
				break;
			case OP_DLE:
				PushVector(self->ValueStack, NON_NULL(bc_GetBoolObject(SPD(self) <= SPD(self))));
				break;
			case OP_INEG:
				PushVector(self->ValueStack, NON_NULL(bc_GetIntObject(-SPI(self))));
				break;
			case OP_DNEG:
				PushVector(self->ValueStack, NON_NULL(NewDouble(-SPD(self))));
				break;
			case OP_BNOT:
			{
				bool a = SPB(self);
				PushVector(self->ValueStack, NON_NULL(bc_GetBoolObject(!a)));
				break;
			}
				//TODO:短絡評価していない
			case OP_BBIT_OR:
			{
				bool ab = SPB(self);
				bool bb = SPB(self);
				PushVector(self->ValueStack, NON_NULL(bc_GetBoolObject(ab | bb)));
				break;
			}
			case OP_BLOGIC_OR:
			{
				bool ab = SPB(self);
				bool bb = SPB(self);
				PushVector(self->ValueStack, NON_NULL(bc_GetBoolObject(ab || bb)));
				break;
			}
			case OP_BBIT_AND:
			{
				bool ab = SPB(self);
				bool bb = SPB(self);
				PushVector(self->ValueStack,NON_NULL( bc_GetBoolObject(ab & bb)));
				break;
			}
			case OP_BLOGIC_AND:
			{
				bool ab = SPB(self);
				bool bb = SPB(self);
				PushVector(self->ValueStack, NON_NULL(bc_GetBoolObject(ab && bb)));
				break;
			}
			case OP_BEXCOR:
				PushVector(self->ValueStack, NON_NULL(bc_GetBoolObject(SPB(self) ^ SPB(self))));
				break;
			case OP_BFLIP:
				PushVector(self->ValueStack, NON_NULL(bc_GetBoolObject(~SPB(self))));
				break;
				//push const
			case OP_ICONST:
			{
				int index = (int)bc_GetEnviromentSourceAt(env, ++IDX);
				bc_Object* o = (bc_Object*)bc_GetEnviromentCIntAt(env, index);
				PushVector(self->ValueStack, NON_NULL(o));
				break;
			}
			case OP_DCONST:
			{
				int index = (int)bc_GetEnviromentSourceAt(env, ++IDX);
				bc_Object* d = bc_GetEnviromentCDoubleAt(env, index);
				PushVector(self->ValueStack, NON_NULL(d));
				break;
			}
			case OP_CCONST:
			{
				int index = (int)bc_GetEnviromentSourceAt(env, ++IDX);
				bc_Object* c = bc_GetEnviromentCCharAt(env, index);
				PushVector(self->ValueStack, NON_NULL(c));
				break;
			}
			case OP_SCONST:
			{
				int index = (int)bc_GetEnviromentSourceAt(env, ++IDX);
				bc_Object* cs = bc_GetEnviromentCStringAt(env, index);
				PushVector(self->ValueStack, NON_NULL(cs));
				break;
			}
			case OP_TRUE:
			{
				PushVector(self->ValueStack, bc_GetTrueObject());
				break;
			}
			case OP_FALSE:
			{
				PushVector(self->ValueStack, bc_GetFalseObject());
				break;
			}
			case OP_NULL:
			{
				PushVector(self->ValueStack, bc_GetNullObject());
				break;
			}
			case OP_RETURN:
			{
				IDX = source_len;
				break;
			}
			case OP_THROW:
			{
				//例外は呼び出し全てへ伝播
				bc_Object* e = (bc_Object*)PopVector(self->ValueStack);
				bc_ThrowVM(self, e);
				ScriptThread* th = GetCurrentSGThread(bc_GetCurrentScriptContext());
				//空ならプログラムを終了
				if (IsEmptyVector(th->TraceStack)) {
					bc_TerminateVM(self);
					//どこかでキャッチしようとしている
				} else {
					bc_ValidateVM(self, source_len, &IDX);
				}
				break;
			}
			case OP_TRY_ENTER:
			{
				ScriptThread* th = GetCurrentSGThread(bc_GetCurrentScriptContext());
				bc_VMTrace* trace = bc_NewVMTrace(self);
				trace->PC = IDX; //goto
				PushVector(th->TraceStack, trace);
				//goto
				IDX++;
				//label
				IDX++;
				//これ以降は通常のステートメント...
				break;
			}
			case OP_TRY_EXIT:
			{
				ScriptThread* th = GetCurrentSGThread(bc_GetCurrentScriptContext());
				bc_VMTrace* trace = (bc_VMTrace*)PopVector(th->TraceStack);
				bc_DeleteVMTrace(trace);
				break;
			}
			case OP_TRY_CLEAR:
			{
				ScriptThread* th = GetCurrentSGThread(bc_GetCurrentScriptContext());
				bc_CatchVM(self);
				bc_VMTrace* trace = (bc_VMTrace*)PopVector(th->TraceStack);
				bc_DeleteVMTrace(trace);
				break;
			}
			case OP_HEXCEPTION:
			{
				PushVector(self->ValueStack, NON_NULL(self->Exception));
				break;
			}
			case OP_INSTANCEOF:
			{
				bc_GenericType* gtype = (bc_GenericType*)PopVector(self->TypeArgs);
				bc_Object* v = (bc_Object*)PopVector(self->ValueStack);
				//PrintGenericType(gtype);
				//bc_Printfln("");
				//PrintGenericType(v->GType);
				//bc_Printfln("");
				int dist = bc_DistanceGenericType(gtype, v->GType, GetSGThreadCContext());
				bc_Object* b = bc_GetBoolObject(dist >= 0);
				PushVector(self->ValueStack, b);
				break;
			}
			case OP_DUP:
				PushVector(self->ValueStack, TopVector(self->ValueStack));
				break;
			case OP_POP:
				PopVector(self->ValueStack);
				break;
			case OP_NOP:
				/* no operation */
				break;
			case OP_NEW_OBJECT:
			{
				//コンストラクタをさかのぼり、
				//トップレベルまで到達するとこの処理によって生成が行われます。
				//FIXME:???
				bc_Object* o = bc_NewObject(self->ObjectSize);
				assert(o->Paint != PAINT_ONEXIT_T);
				PushVector(self->ValueStack, NON_NULL(o));
				//これを this とする
				AssignVector(self->VariableTable, 0, o);
				break;
			}
			case OP_ALLOC_FIELD:
			{
				int absClsIndex = (int)bc_GetEnviromentSourceAt(env, ++IDX);
				bc_Type* tp = (bc_Type*)AtVector(ctx->TypeList, absClsIndex);
				bc_Class* cls = BC_TYPE2CLASS(tp);
				bc_Object* obj = (bc_Object*)TopVector(self->ValueStack);
				//仮想関数テーブル更新
				bc_CreateVTableClass(cls);
				obj->GType = bc_RefGenericType(cls->Parent);
				obj->VPtr = cls->VT;
				//ジェネリック型を実体化
				if(cls->TypeParameters->Length == 0) {
					obj->GType = tp->GenericSelf;
				} else {
					bc_GenericType* g = bc_NewGenericType(tp);
					for(int i=0; i<cls->TypeParameters->Length; i++) {
						bc_AddArgsGenericType(g, (bc_GenericType*)AtVector(self->TypeArgs, i));
					}
					obj->GType = g;
				}
				assert(obj->GType != NULL);
				//フィールドの割り当て
				bc_AllocFieldsClass(cls, obj, self);
				assert(obj->GType != NULL);
				break;
			}
			case OP_NEW_INSTANCE:
			{
				//生成するクラスとコンストラクタを特定
				int absClsIndex = (int)bc_GetEnviromentSourceAt(env, ++IDX);
				int constructorIndex = (int)bc_GetEnviromentSourceAt(env, ++IDX);
				bc_Type* tp = (bc_Type*)AtVector(ctx->TypeList, absClsIndex);
				assert(tp->Tag == TYPE_CLASS_T);
				bc_Class* cls = BC_TYPE2CLASS(tp);
				#if defined(DEBUG)
				const char* clsname = Ref2Str(cls->Name);
				#endif
				bc_Constructor* ctor = (bc_Constructor*)AtVector(cls->Constructors, constructorIndex);
				//新しいVMでコンストラクタを実行
				//また、現在のVMから実引数をポップ
				bc_Frame* sub = bc_SubFrame(self);
				sub->Receiver = tp;
				CallFrame* cfr = PushCallContext(GetSGThreadCContext(), FRAME_STATIC_INVOKE_T);
				cfr->Kind.StaticInvoke.Args = NewVector();
				cfr->Kind.StaticInvoke.TypeArgs = NewVector();
				for (int i = 0; i < ctor->Parameters->Length; i++) {
					VectorItem e = PopVector(self->ValueStack);
					bc_Object* o = (bc_Object*)e;
					PushVector(sub->ValueStack, NON_NULL(e));
					AssignVector(cfr->Kind.StaticInvoke.Args, (ctor->Parameters->Length - i), o->GType);
				}
				//コンストラクタに渡された型引数を引き継ぐ
				int typeparams = cls->TypeParameters->Length;
				for(int i=0; i<typeparams; i++) {
					VectorItem e = PopVector(self->TypeArgs);
					AssignVector(sub->TypeArgs, (typeparams - i) - 1, e);
					AssignVector(cfr->Kind.StaticInvoke.TypeArgs, (cls->TypeParameters->Length - i), e);
				}
				//bc_Printi(self->level);
				//bc_Printfln("[ %s#new ]", GetTypeName(ctor->Parent));
				//DumpEnviromentOp(ctor->env, sub->level);
				//DumpOpcodeBuf(ctor->env->Bytecode, sub->level);
				bc_ExecuteVM(sub, ctor->Env);
				DeleteVector(cfr->Kind.StaticInvoke.Args, VectorDeleterOfNull);
				DeleteVector(cfr->Kind.StaticInvoke.TypeArgs, VectorDeleterOfNull);
				PopCallContext(GetSGThreadCContext());
				//コンストラクタを実行した場合、
				//Objectがスタックのトップに残っているはず
				VectorItem returnV = TopVector(sub->ValueStack);
				bc_Object* returnO = (bc_Object*)returnV;
				PushVector(self->ValueStack, NON_NULL(returnV));
				bc_DeleteFrame(sub);
				break;
			}
			case OP_CHAIN_THIS:
			case OP_CHAIN_SUPER:
			{
				int absClsIndex = (int)bc_GetEnviromentSourceAt(env, ++IDX);
				int ctorIndex = (int)bc_GetEnviromentSourceAt(env, ++IDX);
				int allocSize = (int)bc_GetEnviromentSourceAt(env, ++IDX);
				if(allocSize < self->ObjectSize) {
					allocSize = self->ObjectSize;
				}
				bc_Type* tp = (bc_Type*)AtVector(ctx->TypeList, absClsIndex);
				assert(tp->Tag == TYPE_CLASS_T);
				bc_Class* cls = tp->Kind.Class;
				bc_Constructor* ctor = (bc_Constructor*)AtVector(cls->Constructors, ctorIndex);
				//コンストラクタを実行するためのVMを作成
				bc_Frame* sub = bc_SubFrame(self);
				sub->ObjectSize = allocSize;
				sub->Receiver = tp;
				CallFrame* cfr = PushCallContext(GetSGThreadCContext(), FRAME_STATIC_INVOKE_T);
				cfr->Kind.StaticInvoke.Args = NewVector();
				cfr->Kind.StaticInvoke.TypeArgs = NewVector();
				//チェインコンストラクタに渡された実引数をプッシュ
				for (int i = 0; i < ctor->Parameters->Length; i++) {
					bc_Object* o = (bc_Object*)PopVector(self->ValueStack);
					PushVector(sub->ValueStack, NON_NULL(o));
					AssignVector(cfr->Kind.StaticInvoke.Args, (ctor->Parameters->Length - i), o->GType);
				}
				for(int i=0; i<self->TypeArgs->Length; i++) {
					PushVector(cfr->Kind.StaticInvoke.TypeArgs, self->TypeArgs);
				}
				//		DumpEnviromentOp(ctor->env, sub->level);
				//DumpOpcodeBuf(ctor->env->Bytecode, sub->level);
				bc_ExecuteVM(sub, ctor->Env);
				DeleteVector(cfr->Kind.StaticInvoke.Args, VectorDeleterOfNull);
				DeleteVector(cfr->Kind.StaticInvoke.TypeArgs, VectorDeleterOfNull);
				PopCallContext(GetSGThreadCContext());
				//コンストラクタを実行した場合、
				//Objectがスタックのトップに残っているはず
				VectorItem returnV = TopVector(sub->ValueStack);
				bc_Object* returnO = (bc_Object*)returnV;
				AssignVector(self->VariableTable, 0, returnV);
				PushVector(self->ValueStack, NON_NULL(returnV));

				bc_DeleteFrame(sub);
				//AllocFieldsClass(cls, returnO);
				break;
			}
			case OP_THIS:
			{
				PushVector(self->ValueStack, AtVector(self->VariableTable, 0));
				break;
			}
			case OP_SUPER:
			{
				bc_Object* a = AtVector(self->VariableTable, 0);
				bc_Object* super = bc_CloneObject(a);
				super->GType = BC_TYPE2CLASS(bc_GENERIC2TYPE(a->GType))->SuperClass;
				super->VPtr = BC_TYPE2CLASS(bc_GENERIC2TYPE(BC_TYPE2CLASS(bc_GENERIC2TYPE(a->GType))->SuperClass))->VT;
				PushVector(self->ValueStack, super);
				break;
			}
			//store,load
			case OP_PUT_FIELD:
			{
				bc_Object* assignValue = (bc_Object*)PopVector(self->ValueStack);
				bc_Object* assignTarget = (bc_Object*)PopVector(self->ValueStack);
				if(throw_npe(self, assignTarget)) {
					break;
				}
				//assert(assignTarget->Tag == OBJECT_REF_T);
				int fieldIndex = (int)bc_GetEnviromentSourceAt(env, ++IDX);
				AssignVector(assignTarget->Fields, fieldIndex, assignValue);
				break;
			}

			case OP_GET_FIELD:
			{
				bc_Object* sourceObject = (bc_Object*)PopVector(self->ValueStack);
				if(throw_npe(self, sourceObject)) {
					break;
				}
				//assert(sourceObject->Tag == OBJECT_REF_T);
				//int absClsIndex = (int)GetEnviromentSourceAt(env, ++i);
				int fieldIndex = (int)bc_GetEnviromentSourceAt(env, ++IDX);
				bc_Object* val = (bc_Object*)AtVector(sourceObject->Fields, fieldIndex);
				PushVector(self->ValueStack, val);
				break;
			}

			case OP_PUT_STATIC:
			{
				int absClsIndex = (int)bc_GetEnviromentSourceAt(env, ++IDX);
				int fieldIndex = (int)bc_GetEnviromentSourceAt(env, ++IDX);
				bc_Type* tp = (bc_Type*)AtVector(ctx->TypeList, absClsIndex);
				bc_Class* cls = tp->Kind.Class;
				bc_Field* f = bc_GetSFieldClass(cls, fieldIndex);
				bc_Object* sv = (bc_Object*)PopVector(self->ValueStack);
				f->StaticValue = sv;
				break;
			}

			case OP_GET_STATIC:
			{
				int absClsIndex = (int)bc_GetEnviromentSourceAt(env, ++IDX);
				int fieldIndex = (int)bc_GetEnviromentSourceAt(env, ++IDX);
				bc_Type* cls = (bc_Type*)AtVector(ctx->TypeList, absClsIndex);
				bc_Field* f = bc_GetSFieldClass(cls->Kind.Class, fieldIndex);
				PushVector(self->ValueStack, NON_NULL(f->StaticValue));
				break;
			}
			case OP_PUT_PROPERTY:
			{
				bc_Object* assignValue = (bc_Object*)PopVector(self->ValueStack);
				bc_Object* assignTarget = (bc_Object*)PopVector(self->ValueStack);
				if(throw_npe(self, assignTarget)) {
					break;
				}
				//assert(assignTarget->Tag == OBJECT_REF_T);
				int propIndex = (int)bc_GetEnviromentSourceAt(env, ++IDX);
				bc_Property* pro = bc_GetPropertyClass(BC_TYPE2CLASS(bc_GENERIC2TYPE(assignTarget->GType)), propIndex);
				//プロパティを実行
				bc_Frame* sub = bc_SubFrame(self);
				sub->Receiver = pro->Parent;
				PushVector(sub->ValueStack, assignValue);
				PushVector(sub->ValueStack, assignTarget);
				bc_ExecuteVM(sub, pro->Set->Env);
				bc_DeleteFrame(sub);
				break;
			}
			case OP_GET_PROPERTY:
			{
				bc_Object* sourceObject = (bc_Object*)PopVector(self->ValueStack);
				if(throw_npe(self, sourceObject)) {
					break;
				}
				int propIndex = (int)bc_GetEnviromentSourceAt(env, ++IDX);
				bc_Property* pro = bc_GetPropertyClass(BC_TYPE2CLASS(bc_GENERIC2TYPE(sourceObject->GType)), propIndex);
				//プロパティを実行
				bc_Frame* sub = bc_SubFrame(self);
				sub->Receiver = pro->Parent;
				PushVector(sub->ValueStack, sourceObject);
				bc_ExecuteVM(sub, pro->Get->Env);
				//戻り値をスタックに残す
				VectorItem returnV = TopVector(sub->ValueStack);
				bc_Object* returnO = (bc_Object*)returnV;
				AssignVector(self->VariableTable, 0, returnV);
				PushVector(self->ValueStack, returnV);
				bc_DeleteFrame(sub);
				break;
			}
			case OP_PUT_STATIC_PROPERTY:
			{
				bc_Object* sv = (bc_Object*)PopVector(self->ValueStack);
				int absClsIndex = (int)bc_GetEnviromentSourceAt(env, ++IDX);
				int propIndex = (int)bc_GetEnviromentSourceAt(env, ++IDX);
				bc_Type* tp = (bc_Type*)AtVector(ctx->TypeList, absClsIndex);
				bc_Class* cls = tp->Kind.Class;
				bc_Property * p = bc_GetSPropertyClass(cls, propIndex);
				//プロパティを実行
				bc_Frame* sub = bc_SubFrame(self);
				sub->Receiver = NULL;
				PushVector(sub->ValueStack, sv);
				bc_ExecuteVM(sub, p->Set->Env);
				bc_DeleteFrame(sub);
				break;
			}
			case OP_GET_STATIC_PROPERTY:
			{
				bc_Object* sv = (bc_Object*)PopVector(self->ValueStack);
				int absClsIndex = (int)bc_GetEnviromentSourceAt(env, ++IDX);
				int propIndex = (int)bc_GetEnviromentSourceAt(env, ++IDX);
				bc_Type* tp = (bc_Type*)AtVector(ctx->TypeList, absClsIndex);
				bc_Class* cls = tp->Kind.Class;
				bc_Property * p = bc_GetSPropertyClass(cls, propIndex);
				//プロパティを実行
				bc_Frame* sub = bc_SubFrame(self);
				sub->Receiver = NULL;
				bc_ExecuteVM(sub, p->Get->Env);
				//戻り値をスタックに残す
				VectorItem returnV = TopVector(sub->ValueStack);
				bc_Object* returnO = (bc_Object*)returnV;
				AssignVector(self->VariableTable, 0, returnV);
				PushVector(self->ValueStack, returnV);
				bc_DeleteFrame(sub);
				break;
			}
			case OP_STORE:
			{
				int index = (int)bc_GetEnviromentSourceAt(env, ++IDX);
				VectorItem e = PopVector(self->ValueStack);
				bc_Object* o = (bc_Object*)e;
				assert(o != NULL);
				AssignVector(self->VariableTable, index, e);
				//INFO("store");
				break;
			}
			case OP_LOAD:
			{
				int index = (int)bc_GetEnviromentSourceAt(env, ++IDX);
				VectorItem e = AtVector(self->VariableTable, index);
				bc_Object*  o = (bc_Object*)e;
				assert(o != NULL);
				PushVector(self->ValueStack, e);
				//INFO("load");
				break;
			}
			case OP_DOWN_AS:
			{
				bc_Object* o = PopVector(self->ValueStack);
				bc_GenericType* a = PopVector(self->TypeArgs);
				a = bc_ApplyGenericType(a, GetSGThreadCContext());
				if(a->CoreType->Tag == TYPE_INTERFACE_T) {
					bc_Interface* inter = BC_TYPE2INTERFACE(bc_GENERIC2TYPE(a));
					Vector* inter_list = bc_GetInterfaceTreeClass(BC_TYPE2CLASS(bc_GENERIC2TYPE(o->GType)));
					int iter = FindVector(inter_list, inter);
					DeleteVector(inter_list, VectorDeleterOfNull);
					if(iter == -1) {
						PushVector(self->ValueStack, bc_GetNullObject());
					} else {
						PushVector(self->ValueStack, o);
					}
					break;
				}
				if(bc_DistanceGenericType(o->GType, a, GetSGThreadCContext()) < 0) {
					PushVector(self->ValueStack, bc_GetNullObject());
				} else {
					//o = CloneObject(o);
					//o->GType = a;
					PushVector(self->ValueStack, o);
				}
				break;
			}
			case OP_UP_AS:
			{
				bc_Object* o = PopVector(self->ValueStack);
				bc_GenericType* a = PopVector(self->TypeArgs);
				a = bc_ApplyGenericType(a, GetSGThreadCContext());
				assert(a->CoreType != NULL);
				if(a->CoreType->Tag == TYPE_CLASS_T) {
					PushVector(self->ValueStack, o);
				} else if(a->CoreType->Tag == TYPE_INTERFACE_T) {
					bc_Interface* inter = BC_TYPE2INTERFACE(bc_GENERIC2TYPE(a));
					Vector* inter_list = bc_GetInterfaceTreeClass(BC_TYPE2CLASS(bc_GENERIC2TYPE(o->GType)));
					int iter = FindVector(inter_list, inter);
					DeleteVector(inter_list, VectorDeleterOfNull);
					if(iter == -1) {
						PushVector(self->ValueStack, bc_GetNullObject());
					} else {
						PushVector(self->ValueStack, o);
					}
				}
				break;
			}
			//invoke
			case OP_INVOKEINTERFACE:
			{
				int absClassIndex = (int)bc_GetEnviromentSourceAt(env, ++IDX);
				int methodIndex = (int)bc_GetEnviromentSourceAt(env, ++IDX);
				bc_Type* tp = AtVector(ctx->TypeList, absClassIndex);
				bc_Object* o = (bc_Object*)TopVector(self->ValueStack);
				if(throw_npe(self, o)) {
					break;
				}
				bc_Method* m = bc_GetImplMethodClass(o->GType->CoreType->Kind.Class, tp, methodIndex);
				CallContext* cctx = GetSGThreadCContext();
				bc_ExecuteMethod(m, self, env);
				break;
			}
			case OP_INVOKESTATIC:
			{
				int absClassIndex = (int)bc_GetEnviromentSourceAt(env, ++IDX);
				int methodIndex = (int)bc_GetEnviromentSourceAt(env, ++IDX);
				bc_Type* cls = (bc_Type*)AtVector(ctx->TypeList, absClassIndex);
				bc_Method* m = bc_GetSMethodClass(cls->Kind.Class, methodIndex);
				#if defined(DEBUG)
				const char* clsname = Ref2Str(bc_GetTypeName(cls));
				const char* mname = Ref2Str(m->Name);
				#endif
				bc_ExecuteMethod(m, self, env);
				break;
			}
			case OP_INVOKEVIRTUAL:
			{
				int index = (int)bc_GetEnviromentSourceAt(env, ++IDX);
				bc_Object* o = (bc_Object*)TopVector(self->ValueStack);
				if(throw_npe(self, o)) {
					break;
				}
				bc_Method* m = bc_GetMethodClass(o, index);
				bc_ExecuteMethod(m, self, env);
				break;
			}
			case OP_INVOKESPECIAL:
			{
				//privateメソッドには常にレシーバがいないはず
				//オブジェクトから直接型を取り出してしまうと具象すぎる
				int index = (int)bc_GetEnviromentSourceAt(env, ++IDX);
				bc_Object* o = (bc_Object*)TopVector(self->ValueStack);
				if(throw_npe(self, o)) {
					break;
				}
				bc_Class* cl = BC_TYPE2CLASS(o->GType->CoreType);
				if(self->Receiver != NULL) {
					cl = BC_TYPE2CLASS(self->Receiver);
				}
				bc_Method* m = (bc_Method*)AtVector(cl->Methods, index);
				bc_ExecuteMethod(m, self, env);
				break;
			}
			case OP_INVOKEOPERATOR:
			{
				int index = (int)bc_GetEnviromentSourceAt(env, ++IDX);
				bc_Object* o = (bc_Object*)TopVector(self->ValueStack);
				bc_Class* cl = BC_TYPE2CLASS(o->GType->CoreType);
				#if defined(DEBUG)
				char* clname = Ref2Str(cl->Name);
				#endif
				bc_CreateOperatorVTClass(cl);
				bc_OperatorOverload* operator_ov = (bc_OperatorOverload*)AtVector(cl->OVT->Operators, index);
				bc_ExecuteOperatorOverload(operator_ov, self, env);
				break;
			}
			case OP_CORO_INIT:
			{
				bc_Object* obj = (bc_Object*)AtVector(self->VariableTable, 0);
				int param_len = (int)bc_GetEnviromentSourceAt(env, ++IDX);
				int op_len = (int)bc_GetEnviromentSourceAt(env, ++IDX);
				bc_YieldContext* yctx = bc_NewYieldContext();
				yctx->YieldOffset = 0;
				yctx->YieldCount = 0;
				yctx->Length = op_len;
				yctx->Parameters = NewVector();
				//iterate(int, int) の int, int を受け取る
				yctx->Source = AtVector(self->VariableTable, 1);
				#if defined(DEBUG)
				const char* yname = bc_GetObjectName(yctx->Source);
				#endif
				for(int i=2; i<param_len + 1; i++) {
					bc_Object* a = AtVector(self->VariableTable, i);
					assert(a != NULL);
					PushVector(yctx->Parameters, a);
				}
				bc_Coroutine* cor = (bc_Coroutine*)obj;
				//暗黙的に生成されるイテレータ実装クラスのコンストラクタは、
				//必ず最後に iterate() を定義したクラスのオブジェクトを受け取る。
				cor->Context = yctx;
				obj->Flags = obj->Flags | OBJECT_FLG_COROUTINE;
				break;
			}
			case OP_CORO_NEXT:
			{
				bc_Object* obj = self->Coroutine;
				bc_Object* ret = (bc_Object*)PopVector(self->ValueStack);
				bc_Coroutine* cor = (bc_Coroutine*)obj;
				assert((obj->Flags & OBJECT_FLG_COROUTINE) > 0);
				bc_YieldContext* yctx = cor->Context;
				//この実行コードが
				//前回からの再開によって開始した場合、それを元に戻す
				if(yctx->VariableTable != NULL) {
					self->VariableTable = yctx->VariableTable;
					self->ValueStack = yctx->ValueStack;
				}
				assert(ret != NULL);
				yctx->Stock = ret;
				//最初に実行された yield return に時点でコピーする
				if(yctx->VariableTable == NULL) {
					yctx->BackupVariableTable = CloneVector(self->VariableTable);
					yctx->BackupValueStack = NewVector();
				}
				yctx->YieldOffset = IDX + 1;
				yctx->YieldCount++;
				IDX = source_len;
				//まだ実行できる?
				bc_Object* hasNext = bc_GetBoolObject(yctx->YieldOffset < yctx->Length);
				PushVector(self->ValueStack, hasNext);
				break;
			}
			case OP_CORO_EXIT:
			{
				bc_Object* obj = self->Coroutine;
				assert((obj->Flags | OBJECT_FLG_COROUTINE) > 0);
				bc_Coroutine* cor = (bc_Coroutine*)obj;
				bc_YieldContext* yctx = cor->Context;
				IDX = source_len;
				yctx->YieldOffset = source_len;
				if(yctx->VariableTable != NULL) {
					self->VariableTable = yctx->VariableTable;
					self->ValueStack = yctx->ValueStack;
				}
				PushVector(self->ValueStack, bc_GetFalseObject());
				break;
			}
			case OP_CORO_RESUME:
			{
				bc_Object* obj = self->Coroutine;
				assert((obj->Flags & OBJECT_FLG_COROUTINE) > 0);
				bc_Coroutine* cor = (bc_Coroutine*)obj;
				bc_YieldContext* yctx = cor->Context;
				//前回の位置が記録されているのでそこから
				if(yctx->YieldOffset != 0) {
					IDX = yctx->YieldOffset - 1;
					yctx->VariableTable = self->VariableTable;
					yctx->ValueStack = self->ValueStack;
					self->VariableTable = yctx->BackupVariableTable;
					self->ValueStack = yctx->BackupValueStack;
				}
				break;
			}
			case OP_CORO_CURRENT:
			{
				bc_Object* obj = self->Coroutine;
				bc_Coroutine* cor = (bc_Coroutine*)obj;
				assert((obj->Flags & OBJECT_FLG_COROUTINE) > 0);
				bc_YieldContext* yctx = cor->Context;
				PushVector(self->ValueStack, yctx->Stock);
				break;
			}
			case OP_CORO_SWAP_SELF:
			{
				assert(self->Coroutine == NULL);
				bc_Object* obj = (bc_Object*)AtVector(self->VariableTable, 0);
				assert((obj->Flags & OBJECT_FLG_COROUTINE) > 0);
				bc_Coroutine* cor = (bc_Coroutine*)obj;
				bc_YieldContext* yctx = cor->Context;
				if(yctx->IsCached) {
					self->Coroutine = obj;
					break;
				}
				#if defined(DEBUG)
				const char* oname = bc_GetObjectName(obj);
				const char* yname = bc_GetObjectName(yctx->Source);
				#endif
				//[0] = Array
				//[1] = ArrayIterator
				AssignVector(self->VariableTable, 0, yctx->Source);
				assert(yctx->Source != NULL);
				for(int i=0; i<yctx->Parameters->Length; i++) {
					bc_Object* e = AtVector(yctx->Parameters, i);
					assert(e != NULL);
					AssignVector(self->VariableTable, i + 1, e);
				}
				self->Coroutine = obj;
				yctx->IsCached = true;
				break;
			}
			case OP_GENERIC_ADD:
			{
				//TODO:ここで親フレームを遡るように
				//ジェネリックタイプを作成する
				int depth = 0;
				int pos = IDX;
				Vector* stack = NewVector();
				Vector* counts = NewVector();
				bc_GenericType* ret = NULL;
				while(1) {
					int code = (int)bc_GetEnviromentSourceAt(env, ++IDX);
					if(code == OP_GENERIC_ENTER) {
						int count = (int)bc_GetEnviromentSourceAt(env, ++IDX);
						depth++;
						PushVector(counts, count);
						//PushVector(stack, NewGenericType(NULL));
					} else if(code == OP_GENERIC_EXIT) {
						depth--;
						int count = (int)PopVector(counts);
						bc_GenericType* head = AtVector(stack, 0);
						for(int i=0; i<count; i++) {
							bc_AddArgsGenericType(head, (bc_GenericType*)PopVector(stack));
						}
						if(depth == 0) {
							assert(stack->Length == 1);
							ret = head;
							break;
						}
					} else if(code == OP_GENERIC_UNIQUE_TYPE ||
					          code == OP_GENERIC_INSTANCE_TYPE ||
							  code == OP_GENERIC_STATIC_TYPE) {
						assert(depth > 0);
						int arg = (int)bc_GetEnviromentSourceAt(env, ++IDX);
						bc_GenericType* a = NULL;
						if(code == OP_GENERIC_UNIQUE_TYPE) {
							a = bc_NewGenericType((bc_Type*)AtVector(ctx->TypeList, arg));
						} else if(code == OP_GENERIC_INSTANCE_TYPE) {
							bc_Object* receiver = (bc_Object*)AtVector(self->VariableTable, 0);
							a = (bc_GenericType*)AtVector(receiver->GType->TypeArgs, arg);
						} else if(code == OP_GENERIC_STATIC_TYPE) {
							a = (bc_GenericType*)AtVector(self->TypeArgs, arg);
						}
						PushVector(stack, a);
					}
				}
				assert(ret != NULL);
				PushVector(self->TypeArgs, ret);
				DeleteVector(stack, VectorDeleterOfNull);
				DeleteVector(counts, VectorDeleterOfNull);
				break;
			}
			case OP_GENERIC_ENTER:
			case OP_GENERIC_UNIQUE_TYPE:
			case OP_GENERIC_INSTANCE_TYPE:
			case OP_GENERIC_STATIC_TYPE:
			case OP_GENERIC_EXIT:
				assert(false);
				break;
			//defer
			case OP_DEFER_ENTER:
			{
				break;
			}
			case OP_DEFER_EXIT:
			{
				if(pos == deferStart) {
					IDX = source_len;
				}
				break;
			}
			case OP_DEFER_REGISTER:
			{
				bc_Label* offset = (bc_Label*)bc_GetEnviromentSourceAt(env, ++IDX);
				Vector* bind = CloneVector(self->VariableTable);
				bc_DeferContext* defctx = bc_NewDeferContext();
				defctx->Offset = offset;
				defctx->VariableTable = bind;
				PushVector(self->DeferList, defctx);
				break;
			}
			case OP_BREAKPOINT:
			{
				break;
			}

			//goto
			case OP_GOTO:
			{
				bc_Label* l = (bc_Label*)bc_GetEnviromentSourceAt(env, ++IDX);
				IDX = l->Cursor;
				break;
			}

			case OP_GOTO_IF_TRUE:
			{
				bool v = SPB(self);
				bc_Label* l = (bc_Label*)bc_GetEnviromentSourceAt(env, ++IDX);
				if (v) {
					IDX = l->Cursor;
				}
				break;
			}

			case OP_GOTO_IF_FALSE:
			{
				bool v = SPB(self);
				bc_Label* l = (bc_Label*)bc_GetEnviromentSourceAt(env, ++IDX);
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
		ScriptThread* thr = GetMainSGThread();
		if (self->IsTerminate && !thr->IsVMDump) {
			bc_UncaughtVM(self, env, IDX);
			thr->IsVMDump = true;
			break;
		}
	}
}

static int stack_topi(bc_Frame* self) {
	bc_Object* ret = (bc_Object*)TopVector(self->ValueStack);
	assert(bc_IsIntValue(ret));
	return ((Integer*)ret)->Value;
}

static double stack_topd(bc_Frame* self) {
	bc_Object* ret = (bc_Object*)TopVector(self->ValueStack);
	assert(bc_IsDoubleValue(ret));
	return ((Double*)ret)->Value;
}

static char stack_topc(bc_Frame* self) {
	bc_Object* ret = (bc_Object*)TopVector(self->ValueStack);
	assert(bc_IsCharValue(ret));
	return ((Char*)ret)->Value;
}

static char* stack_tops(bc_Frame* self) {
	bc_Object* ret = (bc_Object*)TopVector(self->ValueStack);
	bc_IsStringValue(ret);
	return GetRawString(ret)->Text;
}

static bool stack_topb(bc_Frame* self) {
	bc_Object* ret = (bc_Object*)TopVector(self->ValueStack);
	assert(bc_IsBoolValue(ret));
	return ((Bool*)ret)->Value;
}


static int stack_popi(bc_Frame* self) {
	bc_Object* ret = (bc_Object*)PopVector(self->ValueStack);
	assert(bc_IsIntValue(ret));
	return ((Integer*)ret)->Value;
}

static double stack_popd(bc_Frame* self) {
	bc_Object* ret = (bc_Object*)PopVector(self->ValueStack);
	assert(bc_IsDoubleValue(ret));
	return ((Double*)ret)->Value;
}

static char stack_popc(bc_Frame* self) {
	bc_Object* ret = (bc_Object*)PopVector(self->ValueStack);
	assert(bc_IsCharValue(ret));
	return ((Char*)ret)->Value;
}

static char* stack_pops(bc_Frame* self) {
	bc_Object* ret = (bc_Object*)PopVector(self->ValueStack);
	assert(bc_IsStringValue(ret));
	return GetRawString(ret)->Text;
}

static bool stack_popb(bc_Frame* self) {
	bc_Object* ret = (bc_Object*)PopVector(self->ValueStack);
	assert(bc_IsBoolValue(ret));
	return ((Bool*)ret)->Value;
}

static bool throw_npe(bc_Frame* self, bc_Object* o) {
	if(bc_IsNullValue(o)) {
		bc_NativeThrowVM(self, bc_NewSimplefException(self, "NullPointerException"));
		return true;
	}
	return false;
}

static char* create_error_message(bc_Frame* self, bc_Enviroment* env, int pc) {
	Buffer* sbuf = NewBuffer();
	bc_LineRange* lr = bc_FindLineRange(env->LineRangeTable, pc);
	int line = -1;
	if (lr != NULL) {
		line = lr->Lineno;
	}
	//例外のメッセージを取得
	bc_Type* exceptionT = bc_FindTypeFromNamespace(bc_GetLangNamespace(), InternString("Exception"));
	int temp = -1;
	bc_FindFieldClass(exceptionT->Kind.Class, InternString("message"), &temp);
	bc_Object* ex = self->Exception;
	bc_Object* msg = AtVector(ex->Fields, temp);
	Buffer* cstr = ((String*)msg)->Buffer;

	char block[256] = {0};
	sprintf(block, "file: %s <%d>", env->ContextRef->FileName, line);
	AppendsBuffer(sbuf, block);
	AppendBuffer(sbuf, '\n');
	AppendsBuffer(sbuf, cstr->Text);
	AppendBuffer(sbuf, '\n');
	//スタックトレースの表示
	bc_Type* stackTraceElementT = bc_FindTypeFromNamespace(bc_GetLangNamespace(), InternString("StackTraceElement"));
	//Exception#stackTraceを取得
	temp = -1;
	bc_FindFieldClass(exceptionT->Kind.Class, InternString("stackTrace"), &temp);
	bc_Object* stackTraceObj = AtVector(ex->Fields, temp);
	//StackTraceElement#fileName
	//StackTraceElement#lineIndex を取得
	int fileNameptr = -1;
	int lineIndexptr = -1;
	bc_FindFieldClass(stackTraceElementT->Kind.Class, InternString("fileName"), &fileNameptr);
	bc_FindFieldClass(stackTraceElementT->Kind.Class, InternString("lineIndex"), &lineIndexptr);
	int stackLen = GetArrayLength(stackTraceObj);
	for(int i=0; i<stackLen; i++) {
		bc_Object* e = GetElementAt(stackTraceObj, i);
		bc_Object* fileNameObj = AtVector(e->Fields, fileNameptr);
		bc_Object* lineIndexObj = AtVector(e->Fields, lineIndexptr);
		sprintf(block, "    @%d: %s\n", bc_ObjectToInt(lineIndexObj), GetRawString(fileNameObj)->Text);
		AppendsBuffer(sbuf, block);
	}
	return ReleaseBuffer(sbuf);
}