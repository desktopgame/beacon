#include "vm.h"
#include "frame.h"
#include <stdlib.h>
#include <stdio.h>
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
#include "../lib/beacon/lang/bc_array.h"
#include "../thread/thread.h"
#include "../util/mem.h"
#include "../util/string_buffer.h"
#include "../util/vector.h"
#include "../util/text.h"
#include "../lib/beacon/lang/bc_string.h"
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
static void vm_run(Frame* self, Enviroment * env, int pos, int deferStart);
static int stack_topi(Frame* self);
static double stack_topd(Frame* self);
static char stack_topc(Frame* self);
static char* stack_tops(Frame* self);
static bool stack_topb(Frame* self);

static int stack_popi(Frame* self);
static double stack_popd(Frame* self);
static char stack_popc(Frame* self);
static char* stack_pops(Frame* self);
static bool stack_popb(Frame* self);
static void remove_from_parent(Frame* self);
static void frame_markStatic(field* item);
static void vm_delete_defctx(VectorItem e);
static bool throw_npe(Frame* self, object* o);
static char* create_error_message(Frame* self, Enviroment* env, int pc);
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




void ExecuteVM(Frame* self, Enviroment* env) {
	ResumeVM(self, env, 0);
}

void ResumeVM(Frame* self, Enviroment * env, int pos) {
	self->DeferList = NewVector();
	vm_run(self, env, pos, -1);
	while(self->DeferList->Length > 0) {
		DeferContext* defctx = (DeferContext*)PopVector(self->DeferList);
		Label* offset = defctx->Offset;
		Vector* save = self->VariableTable;
		self->VariableTable = defctx->VariableTable;
		vm_run(self, env, offset->Cursor, offset->Cursor);
		self->VariableTable = save;
		DeleteDeferContext(defctx);
	}
	DeleteVector(self->DeferList, VectorDeleterOfNull);
	self->DeferList = NULL;
}

void NativeThrowVM(Frame* self, object * exc) {
	self->Exception = exc;

	ThrowVM(self, exc);
	ScriptThread* th = GetCurrentSGThread(GetCurrentScriptContext());
	//空ならプログラムを終了
	if (IsEmptyVector(th->TraceStack)) {
		TerminateVM(self);
	//どこかでキャッチしようとしている
	} else {
		int temp = 0;
		ValidateVM(self, self->ContextRef->Bytecode->Instructions->Length, &temp);
		self->NativeThrowPos = temp;
	}
}

void ThrowVM(Frame* self, object * exc) {
	Frame* temp = self;
	do {
		temp->Exception = exc;
		temp = temp->Parent;
	} while (temp != NULL);
}

void CatchVM(Frame* self) {
	if (self == NULL) {
		return;
	}
	if (self->Parent != NULL) {
		CatchVM(self->Parent);
	}
	self->IsValidate = false;
	if(self->Exception != NULL) {
		self->Exception->paint = PAINT_UNMARKED_T;
		self->Exception = NULL;
	}
}

bool ValidateVM(Frame* self, int source_len, int* pcDest) {
	ScriptThread* th = GetCurrentSGThread(GetCurrentScriptContext());
	VMTrace* trace = (VMTrace*)TopVector(th->TraceStack);
	self->IsValidate = true;
	//汚染
	Frame* p = self->Parent;
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

void TerminateVM(Frame* self) {
	GetMainSGThread()->IsVMCrushByException = true;
	Frame* temp = self;
	do {
		temp->IsTerminate = true;
		temp = temp->Parent;
	} while (temp != NULL);
}

void UncaughtVM(Frame* self, Enviroment* env, int pc) {
	char* message = create_error_message(self, env, pc);
	ScriptContext* sctx = GetCurrentScriptContext();
	if(sctx->print_error) {
		fprintf(stderr, "%s", message);
	}
	gVMError = InternString(message);
	MEM_FREE(message);
	CatchVM(GetRootFrame(self));
	CollectHeap(GetHeap());
}

StringView GetVMErrorMessage() {
	return gVMError;
}


//private
static void vm_run(Frame* self, Enviroment * env, int pos, int deferStart) {
	assert(env != NULL);
	ScriptContext* ctx = GetCurrentScriptContext();
	int source_len = env->Bytecode->Instructions->Length;
	self->ContextRef = env;
	Heap* he = GetHeap();
	for (int IDX = pos; IDX < source_len; IDX++) {
		//このVMの子要素で例外がスローされ、
		//それを子要素自身で処理できなかった場合には、
		//自分で処理を試みます。
		if (self->IsValidate) {
			if (!ValidateVM(self, source_len, &IDX)) {
				break;
			}
		}
		if(self->IsTerminate) {
			break;
		}
		self->PC = IDX;
		Opcode b = (Opcode)GetEnviromentSourceAt(env, IDX);
		switch (b) {
			//int & int
			case OP_IADD:
				PushVector(self->ValueStack, NON_NULL(GetIntObject(SPI(self) + SPI(self))));
				break;
			case OP_ISUB:
				PushVector(self->ValueStack, NON_NULL(GetIntObject(SPI(self) - SPI(self))));
				break;
			case OP_IMUL:
				PushVector(self->ValueStack, NON_NULL(GetIntObject(SPI(self) * SPI(self))));
				break;
			case OP_IDIV:
			{
				int a = SPI(self);
				int b = SPI(self);
				assert(b != 0);
				PushVector(self->ValueStack, NON_NULL(GetIntObject(a / b)));
				break;
			}
			case OP_IMOD:
				PushVector(self->ValueStack, NON_NULL(GetIntObject(SPI(self) % SPI(self))));
				break;
			case OP_IBIT_OR:
			{
				int a = SPI(self);
				int b = SPI(self);
				PushVector(self->ValueStack, NON_NULL(GetIntObject(a | b)));
				break;
			}
			case OP_ILOGIC_OR:
			{
				int a = SPI(self);
				int b = SPI(self);
				PushVector(self->ValueStack, NON_NULL(GetIntObject(a || b)));
				break;
			}
			case OP_IBIT_AND:
			{
				int a = SPI(self);
				int b = SPI(self);
				PushVector(self->ValueStack, NON_NULL(GetIntObject(a & b)));
				break;
			}
			case OP_ILOGIC_AND:
			{
				//SPI(self) をそのまま埋めると正常に動作しない
				//おそらくマクロの展開によるもの
				//短絡評価のせいだった
				int a = SPI(self);
				int b = SPI(self);
				PushVector(self->ValueStack, NON_NULL(GetIntObject(a && b)));
				break;
			}
			case OP_IEQ:
				PushVector(self->ValueStack, NON_NULL(GetBoolObject(SPI(self) == SPI(self))));
				break;
			case OP_INOTEQ:
				PushVector(self->ValueStack, NON_NULL(GetBoolObject(SPI(self) != SPI(self))));
				break;
			case OP_IGT:
				PushVector(self->ValueStack, NON_NULL(GetBoolObject(SPI(self) > SPI(self))));
				break;
			case OP_IGE:
				PushVector(self->ValueStack, NON_NULL(GetBoolObject(SPI(self) >= SPI(self))));
				break;
			case OP_ILT:
			{
				object* a_ = PopVector(self->ValueStack);
				object* b_ = PopVector(self->ValueStack);
				PushVector(self->ValueStack, NON_NULL(GetBoolObject(OBJ2INT(a_) < OBJ2INT(b_))));
				//PushVector(self->ValueStack, GetBoolObject(SPI(self) < SPI(self)));
				break;
			}
			case OP_ILE:
				PushVector(self->ValueStack, NON_NULL(GetBoolObject(SPI(self) <= SPI(self))));
				break;
			case OP_ILSH:
				PushVector(self->ValueStack, NON_NULL(GetIntObject(SPI(self) << SPI(self))));
				break;
			case OP_IRSH:
				PushVector(self->ValueStack, NON_NULL(GetIntObject(SPI(self) >> SPI(self))));
				break;
			case OP_IEXCOR:
				PushVector(self->ValueStack, NON_NULL(GetIntObject(SPI(self) ^ SPI(self))));
				break;
			case OP_IFLIP:
				PushVector(self->ValueStack, NON_NULL(GetIntObject(~SPI(self))));
				break;
			case OP_CEQ:
				PushVector(self->ValueStack, NON_NULL(GetBoolObject(SPC(self) == SPC(self))));
				break;
			case OP_CNOTEQ:
				PushVector(self->ValueStack, NON_NULL(GetBoolObject(SPC(self) != SPC(self))));
				break;
			case OP_CGT:
				PushVector(self->ValueStack, NON_NULL(GetBoolObject(SPC(self) > SPC(self))));
				break;
			case OP_CGE:
				PushVector(self->ValueStack, NON_NULL(GetBoolObject(SPC(self) >= SPC(self))));
				break;
			case OP_CLT:
				PushVector(self->ValueStack, NON_NULL(GetBoolObject(SPC(self) < SPC(self))));
				break;
			case OP_CLE:
				PushVector(self->ValueStack, NON_NULL(GetBoolObject(SPC(self) <= SPC(self))));
				break;
				//double & double
			case OP_DADD:
				PushVector(self->ValueStack, NON_NULL(object_double_new(SPD(self) + SPD(self))));
				break;
			case OP_DSUB:
				PushVector(self->ValueStack, NON_NULL(object_double_new(SPD(self) - SPD(self))));
				break;
			case OP_DMUL:
				PushVector(self->ValueStack, NON_NULL(object_double_new(SPD(self) * SPD(self))));
				break;
			case OP_DDIV:
				PushVector(self->ValueStack, NON_NULL(object_double_new(SPD(self) / SPD(self))));
				break;
			case OP_DMOD:
				PushVector(self->ValueStack, NON_NULL(object_double_new((double)((int)SPD(self) % (int)SPD(self)))));
				break;
			case OP_DEQ:
				PushVector(self->ValueStack, NON_NULL(GetBoolObject(SPD(self) == SPD(self))));
				break;
			case OP_DNOTEQ:
				PushVector(self->ValueStack, NON_NULL(GetBoolObject(SPD(self) != SPD(self))));
				break;
			case OP_DGT:
				PushVector(self->ValueStack, NON_NULL(GetBoolObject(SPD(self) > SPD(self))));
				break;
			case OP_DGE:
				PushVector(self->ValueStack, NON_NULL(GetBoolObject(SPD(self) >= SPD(self))));
				break;
			case OP_DLT:
				PushVector(self->ValueStack, NON_NULL(GetBoolObject(SPD(self) < SPD(self))));
				break;
			case OP_DLE:
				PushVector(self->ValueStack, NON_NULL(GetBoolObject(SPD(self) <= SPD(self))));
				break;
			case OP_INEG:
				PushVector(self->ValueStack, NON_NULL(GetIntObject(-SPI(self))));
				break;
			case OP_DNEG:
				PushVector(self->ValueStack, NON_NULL(object_double_new(-SPD(self))));
				break;
			case OP_BNOT:
			{
				bool a = SPB(self);
				PushVector(self->ValueStack, NON_NULL(GetBoolObject(!a)));
				break;
			}
				//TODO:短絡評価していない
			case OP_BBIT_OR:
			{
				bool ab = SPB(self);
				bool bb = SPB(self);
				PushVector(self->ValueStack, NON_NULL(GetBoolObject(ab | bb)));
				break;
			}
			case OP_BLOGIC_OR:
			{
				bool ab = SPB(self);
				bool bb = SPB(self);
				PushVector(self->ValueStack, NON_NULL(GetBoolObject(ab || bb)));
				break;
			}
			case OP_BBIT_AND:
			{
				bool ab = SPB(self);
				bool bb = SPB(self);
				PushVector(self->ValueStack,NON_NULL( GetBoolObject(ab & bb)));
				break;
			}
			case OP_BLOGIC_AND:
			{
				bool ab = SPB(self);
				bool bb = SPB(self);
				PushVector(self->ValueStack, NON_NULL(GetBoolObject(ab && bb)));
				break;
			}
			case OP_BEXCOR:
				PushVector(self->ValueStack, NON_NULL(GetBoolObject(SPB(self) ^ SPB(self))));
				break;
			case OP_BFLIP:
				PushVector(self->ValueStack, NON_NULL(GetBoolObject(~SPB(self))));
				break;
				//push const
			case OP_ICONST:
			{
				int index = (int)GetEnviromentSourceAt(env, ++IDX);
				object* o = (object*)GetEnviromentCIntAt(env, index);
				PushVector(self->ValueStack, NON_NULL(o));
				break;
			}
			case OP_DCONST:
			{
				int index = (int)GetEnviromentSourceAt(env, ++IDX);
				object* d = GetEnviromentCDoubleAt(env, index);
				PushVector(self->ValueStack, NON_NULL(d));
				break;
			}
			case OP_CCONST:
			{
				int index = (int)GetEnviromentSourceAt(env, ++IDX);
				object* c = GetEnviromentCCharAt(env, index);
				PushVector(self->ValueStack, NON_NULL(c));
				break;
			}
			case OP_SCONST:
			{
				int index = (int)GetEnviromentSourceAt(env, ++IDX);
				object* cs = GetEnviromentCStringAt(env, index);
				PushVector(self->ValueStack, NON_NULL(cs));
				break;
			}
			case OP_TRUE:
			{
				PushVector(self->ValueStack, GetTrueObject());
				break;
			}
			case OP_FALSE:
			{
				PushVector(self->ValueStack, GetFalseObject());
				break;
			}
			case OP_NULL:
			{
				PushVector(self->ValueStack, GetNullObject());
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
				object* e = (object*)PopVector(self->ValueStack);
				ThrowVM(self, e);
				ScriptThread* th = GetCurrentSGThread(GetCurrentScriptContext());
				//空ならプログラムを終了
				if (IsEmptyVector(th->TraceStack)) {
					TerminateVM(self);
					//どこかでキャッチしようとしている
				} else {
					ValidateVM(self, source_len, &IDX);
				}
				break;
			}
			case OP_TRY_ENTER:
			{
				ScriptThread* th = GetCurrentSGThread(GetCurrentScriptContext());
				VMTrace* trace = NewVMTrace(self);
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
				ScriptThread* th = GetCurrentSGThread(GetCurrentScriptContext());
				VMTrace* trace = (VMTrace*)PopVector(th->TraceStack);
				DeleteVMTrace(trace);
				break;
			}
			case OP_TRY_CLEAR:
			{
				ScriptThread* th = GetCurrentSGThread(GetCurrentScriptContext());
				CatchVM(self);
				VMTrace* trace = (VMTrace*)PopVector(th->TraceStack);
				DeleteVMTrace(trace);
				break;
			}
			case OP_HEXCEPTION:
			{
				PushVector(self->ValueStack, NON_NULL(self->Exception));
				break;
			}
			case OP_INSTANCEOF:
			{
				generic_type* gtype = (generic_type*)PopVector(self->TypeArgs);
				object* v = (object*)PopVector(self->ValueStack);
				//PrintGenericType(gtype);
				//Printfln("");
				//PrintGenericType(v->gtype);
				//Printfln("");
				int dist = DistanceGenericType(gtype, v->gtype, GetSGThreadCContext());
				object* b = GetBoolObject(dist >= 0);
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
				object* o = object_ref_new();
				assert(o->paint != PAINT_ONEXIT_T);
				PushVector(self->ValueStack, NON_NULL(o));
				//これを this とする
				AssignVector(self->VariableTable, 0, o);
				break;
			}
			case OP_ALLOC_FIELD:
			{
				int absClsIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				type* tp = (type*)AtVector(ctx->TypeList, absClsIndex);
				class_* cls = TYPE2CLASS(tp);
				object* obj = (object*)TopVector(self->ValueStack);
				//仮想関数テーブル更新
				CreateVTableClass(cls);
				obj->gtype = RefGenericType(cls->parent);
				obj->vptr = cls->vt;
				//ジェネリック型を実体化
				if(cls->GetParameterListType->Length == 0) {
					obj->gtype = tp->generic_self;
				} else {
					generic_type* g = generic_NewType(tp);
					for(int i=0; i<cls->GetParameterListType->Length; i++) {
						AddArgsGenericType(g, (generic_type*)AtVector(self->TypeArgs, i));
					}
					obj->gtype = g;
				}
				//フィールドの割り当て
				AllocFieldsClass(cls, obj, self);
				assert(obj->gtype != NULL);
				break;
			}
			case OP_NEW_INSTANCE:
			{
				//生成するクラスとコンストラクタを特定
				int absClsIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				int constructorIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				type* tp = (type*)AtVector(ctx->TypeList, absClsIndex);
				assert(tp->tag == TYPE_CLASS_T);
				class_* cls = TYPE2CLASS(tp);
				#if defined(DEBUG)
				const char* clsname = Ref2Str(cls->namev);
				#endif
				constructor* ctor = (constructor*)AtVector(cls->constructor_list, constructorIndex);
				//新しいVMでコンストラクタを実行
				//また、現在のVMから実引数をポップ
				Frame* sub = SubFrame(self);
				sub->Receiver = tp;
				CallFrame* cfr = PushCallContext(GetSGThreadCContext(), FRAME_STATIC_INVOKE_T);
				cfr->Kind.StaticInvoke.Args = NewVector();
				cfr->Kind.StaticInvoke.TypeArgs = NewVector();
				for (int i = 0; i < ctor->parameter_list->Length; i++) {
					VectorItem e = PopVector(self->ValueStack);
					object* o = (object*)e;
					PushVector(sub->ValueStack, NON_NULL(e));
					AssignVector(cfr->Kind.StaticInvoke.Args, (ctor->parameter_list->Length - i), o->gtype);
				}
				//コンストラクタに渡された型引数を引き継ぐ
				int typeparams = cls->GetParameterListType->Length;
				for(int i=0; i<typeparams; i++) {
					VectorItem e = PopVector(self->TypeArgs);
					AssignVector(sub->TypeArgs, (typeparams - i) - 1, e);
					AssignVector(cfr->Kind.StaticInvoke.TypeArgs, (cls->GetParameterListType->Length - i), e);
				}
				//Printi(self->level);
				//Printfln("[ %s#new ]", GetTypeName(ctor->Parent));
				//DumpEnviromentOp(ctor->env, sub->level);
				//DumpOpcodeBuf(ctor->env->Bytecode, sub->level);
				ExecuteVM(sub, ctor->env);
				DeleteVector(cfr->Kind.StaticInvoke.Args, VectorDeleterOfNull);
				DeleteVector(cfr->Kind.StaticInvoke.TypeArgs, VectorDeleterOfNull);
				PopCallContext(GetSGThreadCContext());
				//コンストラクタを実行した場合、
				//objectがスタックのトップに残っているはず
				VectorItem returnV = TopVector(sub->ValueStack);
				object* returnO = (object*)returnV;
				PushVector(self->ValueStack, NON_NULL(returnV));
				DeleteFrame(sub);
				break;
			}
			case OP_CHAIN_THIS:
			case OP_CHAIN_SUPER:
			{
				int absClsIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				int ctorIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				type* tp = (type*)AtVector(ctx->TypeList, absClsIndex);
				assert(tp->tag == TYPE_CLASS_T);
				class_* cls = tp->u.class_;
				constructor* ctor = (constructor*)AtVector(cls->constructor_list, ctorIndex);
				//コンストラクタを実行するためのVMを作成
				Frame* sub = SubFrame(self);
				sub->Receiver = tp;
				CallFrame* cfr = PushCallContext(GetSGThreadCContext(), FRAME_STATIC_INVOKE_T);
				cfr->Kind.StaticInvoke.Args = NewVector();
				cfr->Kind.StaticInvoke.TypeArgs = NewVector();
				//チェインコンストラクタに渡された実引数をプッシュ
				for (int i = 0; i < ctor->parameter_list->Length; i++) {
					object* o = (object*)PopVector(self->ValueStack);
					PushVector(sub->ValueStack, NON_NULL(o));
					AssignVector(cfr->Kind.StaticInvoke.Args, (ctor->parameter_list->Length - i), o->gtype);
				}
				for(int i=0; i<self->TypeArgs->Length; i++) {
					PushVector(cfr->Kind.StaticInvoke.TypeArgs, self->TypeArgs);
				}
				//		DumpEnviromentOp(ctor->env, sub->level);
				//DumpOpcodeBuf(ctor->env->Bytecode, sub->level);
				ExecuteVM(sub, ctor->env);
				DeleteVector(cfr->Kind.StaticInvoke.Args, VectorDeleterOfNull);
				DeleteVector(cfr->Kind.StaticInvoke.TypeArgs, VectorDeleterOfNull);
				PopCallContext(GetSGThreadCContext());
				//コンストラクタを実行した場合、
				//objectがスタックのトップに残っているはず
				VectorItem returnV = TopVector(sub->ValueStack);
				object* returnO = (object*)returnV;
				AssignVector(self->VariableTable, 0, returnV);
				PushVector(self->ValueStack, NON_NULL(returnV));

				DeleteFrame(sub);
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
				object* a = AtVector(self->VariableTable, 0);
				object* super = CloneObject(a);
				super->gtype = TYPE2CLASS(GENERIC2TYPE(a->gtype))->super_class;
				super->vptr = TYPE2CLASS(GENERIC2TYPE(TYPE2CLASS(GENERIC2TYPE(a->gtype))->super_class))->vt;
				PushVector(self->ValueStack, super);
				break;
			}
			//store,load
			case OP_PUT_FIELD:
			{
				object* assignValue = (object*)PopVector(self->ValueStack);
				object* assignTarget = (object*)PopVector(self->ValueStack);
				if(throw_npe(self, assignTarget)) {
					break;
				}
				assert(assignTarget->tag == OBJECT_REF_T);
				int fieldIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				AssignVector(assignTarget->u.field_vec, fieldIndex, assignValue);
				break;
			}

			case OP_GET_FIELD:
			{
				object* sourceObject = (object*)PopVector(self->ValueStack);
				if(throw_npe(self, sourceObject)) {
					break;
				}
				//assert(sourceObject->tag == OBJECT_REF_T);
				//int absClsIndex = (int)GetEnviromentSourceAt(env, ++i);
				int fieldIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				object* val = (object*)AtVector(sourceObject->u.field_vec, fieldIndex);
				PushVector(self->ValueStack, val);
				break;
			}

			case OP_PUT_STATIC:
			{
				int absClsIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				int fieldIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				type* tp = (type*)AtVector(ctx->TypeList, absClsIndex);
				class_* cls = tp->u.class_;
				field* f = GetSFieldClass(cls, fieldIndex);
				object* sv = (object*)PopVector(self->ValueStack);
				f->static_value = sv;
				break;
			}

			case OP_GET_STATIC:
			{
				int absClsIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				int fieldIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				type* cls = (type*)AtVector(ctx->TypeList, absClsIndex);
				field* f = GetSFieldClass(cls->u.class_, fieldIndex);
				PushVector(self->ValueStack, NON_NULL(f->static_value));
				break;
			}
			case OP_PUT_PROPERTY:
			{
				object* assignValue = (object*)PopVector(self->ValueStack);
				object* assignTarget = (object*)PopVector(self->ValueStack);
				if(throw_npe(self, assignTarget)) {
					break;
				}
				assert(assignTarget->tag == OBJECT_REF_T);
				int propIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				Property* pro = GetPropertyClass(TYPE2CLASS(GENERIC2TYPE(assignTarget->gtype)), propIndex);
				//プロパティを実行
				Frame* sub = SubFrame(self);
				sub->Receiver = pro->Parent;
				PushVector(sub->ValueStack, assignValue);
				PushVector(sub->ValueStack, assignTarget);
				ExecuteVM(sub, pro->Set->Env);
				DeleteFrame(sub);
				break;
			}
			case OP_GET_PROPERTY:
			{
				object* sourceObject = (object*)PopVector(self->ValueStack);
				if(throw_npe(self, sourceObject)) {
					break;
				}
				int propIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				Property* pro = GetPropertyClass(TYPE2CLASS(GENERIC2TYPE(sourceObject->gtype)), propIndex);
				//プロパティを実行
				Frame* sub = SubFrame(self);
				sub->Receiver = pro->Parent;
				PushVector(sub->ValueStack, sourceObject);
				ExecuteVM(sub, pro->Get->Env);
				//戻り値をスタックに残す
				VectorItem returnV = TopVector(sub->ValueStack);
				object* returnO = (object*)returnV;
				AssignVector(self->VariableTable, 0, returnV);
				PushVector(self->ValueStack, returnV);
				DeleteFrame(sub);
				break;
			}
			case OP_PUT_STATIC_PROPERTY:
			{
				object* sv = (object*)PopVector(self->ValueStack);
				int absClsIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				int propIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				type* tp = (type*)AtVector(ctx->TypeList, absClsIndex);
				class_* cls = tp->u.class_;
				Property * p = GetSPropertyClass(cls, propIndex);
				//プロパティを実行
				Frame* sub = SubFrame(self);
				sub->Receiver = NULL;
				PushVector(sub->ValueStack, sv);
				ExecuteVM(sub, p->Set->Env);
				DeleteFrame(sub);
				break;
			}
			case OP_GET_STATIC_PROPERTY:
			{
				object* sv = (object*)PopVector(self->ValueStack);
				int absClsIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				int propIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				type* tp = (type*)AtVector(ctx->TypeList, absClsIndex);
				class_* cls = tp->u.class_;
				Property * p = GetSPropertyClass(cls, propIndex);
				//プロパティを実行
				Frame* sub = SubFrame(self);
				sub->Receiver = NULL;
				ExecuteVM(sub, p->Get->Env);
				//戻り値をスタックに残す
				VectorItem returnV = TopVector(sub->ValueStack);
				object* returnO = (object*)returnV;
				AssignVector(self->VariableTable, 0, returnV);
				PushVector(self->ValueStack, returnV);
				DeleteFrame(sub);
				break;
			}
			case OP_STORE:
			{
				int index = (int)GetEnviromentSourceAt(env, ++IDX);
				VectorItem e = PopVector(self->ValueStack);
				object* o = (object*)e;
				assert(o != NULL);
				AssignVector(self->VariableTable, index, e);
				//INFO("store");
				break;
			}
			case OP_LOAD:
			{
				int index = (int)GetEnviromentSourceAt(env, ++IDX);
				VectorItem e = AtVector(self->VariableTable, index);
				object*  o = (object*)e;
				assert(o != NULL);
				PushVector(self->ValueStack, e);
				//INFO("load");
				break;
			}
			case OP_DOWN_AS:
			{
				object* o = PopVector(self->ValueStack);
				generic_type* a = PopVector(self->TypeArgs);
				a = ApplyGenericType(a, GetSGThreadCContext());
				if(a->core_type->tag == TYPE_INTERFACE_T) {
					interface_* inter = TYPE2INTERFACE(GENERIC2TYPE(a));
					Vector* inter_list = GetInterfaceTreeClass(TYPE2CLASS(GENERIC2TYPE(o->gtype)));
					int iter = FindVector(inter_list, inter);
					DeleteVector(inter_list, VectorDeleterOfNull);
					if(iter == -1) {
						PushVector(self->ValueStack, GetNullObject());
					} else {
						PushVector(self->ValueStack, o);
					}
					break;
				}
				if(DistanceGenericType(o->gtype, a, GetSGThreadCContext()) < 0) {
					PushVector(self->ValueStack, GetNullObject());
				} else {
					//o = CloneObject(o);
					//o->gtype = a;
					PushVector(self->ValueStack, o);
				}
				break;
			}
			case OP_UP_AS:
			{
				object* o = PopVector(self->ValueStack);
				generic_type* a = PopVector(self->TypeArgs);
				a = ApplyGenericType(a, GetSGThreadCContext());
				assert(a->core_type != NULL);
				if(a->core_type->tag == TYPE_CLASS_T) {
					PushVector(self->ValueStack, o);
				} else if(a->core_type->tag == TYPE_INTERFACE_T) {
					interface_* inter = TYPE2INTERFACE(GENERIC2TYPE(a));
					Vector* inter_list = GetInterfaceTreeClass(TYPE2CLASS(GENERIC2TYPE(o->gtype)));
					int iter = FindVector(inter_list, inter);
					DeleteVector(inter_list, VectorDeleterOfNull);
					if(iter == -1) {
						PushVector(self->ValueStack, GetNullObject());
					} else {
						PushVector(self->ValueStack, o);
					}
				}
				break;
			}
			//invoke
			case OP_INVOKEINTERFACE:
			{
				int absClassIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				int methodIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				type* tp = AtVector(ctx->TypeList, absClassIndex);
				object* o = (object*)TopVector(self->ValueStack);
				if(throw_npe(self, o)) {
					break;
				}
				Method* m = GetImplMethodClass(o->gtype->core_type->u.class_, tp, methodIndex);
				CallContext* cctx = GetSGThreadCContext();
				ExecuteMethod(m, self, env);
				break;
			}
			case OP_INVOKESTATIC:
			{
				int absClassIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				int methodIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				type* cls = (type*)AtVector(ctx->TypeList, absClassIndex);
				Method* m = GetSMethodClass(cls->u.class_, methodIndex);
				#if defined(DEBUG)
				const char* clsname = Ref2Str(GetTypeName(cls));
				const char* mname = Ref2Str(m->Name);
				#endif
				ExecuteMethod(m, self, env);
				break;
			}
			case OP_INVOKEVIRTUAL:
			{
				int index = (int)GetEnviromentSourceAt(env, ++IDX);
				object* o = (object*)TopVector(self->ValueStack);
				if(throw_npe(self, o)) {
					break;
				}
				Method* m = GetMethodClass(o, index);
				ExecuteMethod(m, self, env);
				break;
			}
			case OP_INVOKESPECIAL:
			{
				//privateメソッドには常にレシーバがいないはず
				//オブジェクトから直接型を取り出してしまうと具象すぎる
				int index = (int)GetEnviromentSourceAt(env, ++IDX);
				object* o = (object*)TopVector(self->ValueStack);
				if(throw_npe(self, o)) {
					break;
				}
				class_* cl = TYPE2CLASS(o->gtype->core_type);
				if(self->Receiver != NULL) {
					cl = TYPE2CLASS(self->Receiver);
				}
				Method* m = (Method*)AtVector(cl->method_list, index);
				ExecuteMethod(m, self, env);
				break;
			}
			case OP_INVOKEOPERATOR:
			{
				int index = (int)GetEnviromentSourceAt(env, ++IDX);
				object* o = (object*)TopVector(self->ValueStack);
				class_* cl = TYPE2CLASS(o->gtype->core_type);
				#if defined(DEBUG)
				char* clname = Ref2Str(cl->namev);
				#endif
				CreateOperatorVTClass(cl);
				operator_overload* operator_ov = (operator_overload*)AtVector(cl->ovt->vec, index);
				ExecuteOperatorOverload(operator_ov, self, env);
				break;
			}
			case OP_CORO_INIT:
			{
				object* o = (object*)AtVector(self->VariableTable, 0);
				if(o->native_slot_vec == NULL) {
					o->native_slot_vec = NewVector();
				}
				int param_len = (int)GetEnviromentSourceAt(env, ++IDX);
				int op_len = (int)GetEnviromentSourceAt(env, ++IDX);
				YieldContext* yctx = NewYieldContext();
				yctx->YieldOffset = 0;
				yctx->YieldCount = 0;
				yctx->Length = op_len;
				yctx->Parameters = NewVector();
				//iterate(int, int) の int, int を受け取る
				yctx->Source = AtVector(self->VariableTable, 1);
				#if defined(DEBUG)
				const char* yname = GetObjectName(yctx->Source);
				#endif
				for(int i=2; i<param_len + 1; i++) {
					object* a = AtVector(self->VariableTable, i);
					assert(a != NULL);
					PushVector(yctx->Parameters, a);
				}
				//暗黙的に生成されるイテレータ実装クラスのコンストラクタは、
				//必ず最後に iterate() を定義したクラスのオブジェクトを受け取る。
				PushVector(o->native_slot_vec, yctx);
				o->is_coroutine = true;
				break;
			}
			case OP_CORO_NEXT:
			{
				object* o = self->Coroutine;
				object* ret = (object*)PopVector(self->ValueStack);
				assert(o->is_coroutine);
				YieldContext* yctx = (YieldContext*)AtVector(o->native_slot_vec, 0);
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
				object* hasNext = GetBoolObject(yctx->YieldOffset < yctx->Length);
				PushVector(self->ValueStack, hasNext);
				break;
			}
			case OP_CORO_EXIT:
			{
				object* o = self->Coroutine;
				assert(o->is_coroutine);
				YieldContext* yctx = (YieldContext*)AtVector(o->native_slot_vec, 0);
				IDX = source_len;
				yctx->YieldOffset = source_len;
				if(yctx->VariableTable != NULL) {
					self->VariableTable = yctx->VariableTable;
					self->ValueStack = yctx->ValueStack;
				}
				PushVector(self->ValueStack, GetFalseObject());
				break;
			}
			case OP_CORO_RESUME:
			{
				object* o = self->Coroutine;
				assert(o->is_coroutine);
				YieldContext* yctx = (YieldContext*)AtVector(o->native_slot_vec, 0);
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
				object* o = self->Coroutine;
				assert(o->is_coroutine);
				YieldContext* yctx = (YieldContext*)AtVector(o->native_slot_vec, 0);
				PushVector(self->ValueStack, yctx->Stock);
				break;
			}
			case OP_CORO_SWAP_SELF:
			{
				assert(self->Coroutine == NULL);
				object* o = (object*)AtVector(self->VariableTable, 0);
				assert(o->is_coroutine);
				YieldContext* yctx = AtVector(o->native_slot_vec, 0);
				if(yctx->IsCached) {
					self->Coroutine = o;
					break;
				}
				#if defined(DEBUG)
				const char* oname = GetObjectName(o);
				const char* yname = GetObjectName(yctx->Source);
				#endif
				//[0] = Array
				//[1] = ArrayIterator
				AssignVector(self->VariableTable, 0, yctx->Source);
				assert(yctx->Source != NULL);
				for(int i=0; i<yctx->Parameters->Length; i++) {
					object* e = AtVector(yctx->Parameters, i);
					assert(e != NULL);
					AssignVector(self->VariableTable, i + 1, e);
				}
				self->Coroutine = o;
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
				generic_type* ret = NULL;
				while(1) {
					int code = (int)GetEnviromentSourceAt(env, ++IDX);
					if(code == OP_GENERIC_ENTER) {
						int count = (int)GetEnviromentSourceAt(env, ++IDX);
						depth++;
						PushVector(counts, count);
						//PushVector(stack, generic_NewType(NULL));
					} else if(code == OP_GENERIC_EXIT) {
						depth--;
						int count = (int)PopVector(counts);
						generic_type* head = AtVector(stack, 0);
						for(int i=0; i<count; i++) {
							AddArgsGenericType(head, (generic_type*)PopVector(stack));
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
						int arg = (int)GetEnviromentSourceAt(env, ++IDX);
						generic_type* a = NULL;
						if(code == OP_GENERIC_UNIQUE_TYPE) {
							a = generic_NewType((type*)AtVector(ctx->TypeList, arg));
						} else if(code == OP_GENERIC_INSTANCE_TYPE) {
							object* receiver = (object*)AtVector(self->VariableTable, 0);
							a = (generic_type*)AtVector(receiver->gtype->type_args_list, arg);
						} else if(code == OP_GENERIC_STATIC_TYPE) {
							a = (generic_type*)AtVector(self->TypeArgs, arg);
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
				Label* offset = (Label*)GetEnviromentSourceAt(env, ++IDX);
				Vector* bind = CloneVector(self->VariableTable);
				DeferContext* defctx = NewDeferContext();
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
				Label* l = (Label*)GetEnviromentSourceAt(env, ++IDX);
				IDX = l->Cursor;
				break;
			}

			case OP_GOTO_IF_TRUE:
			{
				bool v = SPB(self);
				Label* l = (Label*)GetEnviromentSourceAt(env, ++IDX);
				if (v) {
					IDX = l->Cursor;
				}
				break;
			}

			case OP_GOTO_IF_FALSE:
			{
				bool v = SPB(self);
				Label* l = (Label*)GetEnviromentSourceAt(env, ++IDX);
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
			UncaughtVM(self, env, IDX);
			thr->IsVMDump = true;
			break;
		}
	}
}

static int stack_topi(Frame* self) {
	object* ret = (object*)TopVector(self->ValueStack);
	assert(ret->tag == OBJECT_INT_T);
	return ret->u.int_;
}

static double stack_topd(Frame* self) {
	object* ret = (object*)TopVector(self->ValueStack);
	assert(ret->tag == OBJECT_DOUBLE_T);
	return ret->u.double_;
}

static char stack_topc(Frame* self) {
	object* ret = (object*)TopVector(self->ValueStack);
	assert(ret->tag == OBJECT_CHAR_T);
	return ret->u.char_;
}

static char* stack_tops(Frame* self) {
	object* ret = (object*)TopVector(self->ValueStack);
	assert(ret->tag == OBJECT_STRING_T);
	return GetRawBCString(ret)->Text;
}

static bool stack_topb(Frame* self) {
	object* ret = (object*)TopVector(self->ValueStack);
	assert(ret->tag == OBJECT_BOOL_T);
	return ret->u.bool_;
}


static int stack_popi(Frame* self) {
	object* ret = (object*)PopVector(self->ValueStack);
	assert(ret->tag == OBJECT_INT_T);
	return ret->u.int_;
}

static double stack_popd(Frame* self) {
	object* ret = (object*)PopVector(self->ValueStack);
	assert(ret->tag == OBJECT_DOUBLE_T);
	return ret->u.double_;
}

static char stack_popc(Frame* self) {
	object* ret = (object*)PopVector(self->ValueStack);
	assert(ret->tag == OBJECT_CHAR_T);
	return ret->u.char_;
}

static char* stack_pops(Frame* self) {
	object* ret = (object*)PopVector(self->ValueStack);
	assert(ret->tag == OBJECT_STRING_T);
	return GetRawBCString(ret)->Text;
}

static bool stack_popb(Frame* self) {
	object* ret = (object*)PopVector(self->ValueStack);
	assert(ret->tag == OBJECT_BOOL_T);
	return ret->u.bool_;
}

static bool throw_npe(Frame* self, object* o) {
	if(o->tag == OBJECT_NULL_T) {
		NativeThrowVM(self, NewSimplefException(self, "NullPointerException"));
		return true;
	}
	return false;
}

static char* create_error_message(Frame* self, Enviroment* env, int pc) {
	Buffer* sbuf = NewBuffer();
	LineRange* lr = FindLineRange(env->LineRangeTable, pc);
	int line = -1;
	if (lr != NULL) {
		line = lr->Lineno;
	}
	//例外のメッセージを取得
	type* exceptionT = FindTypeFromNamespace(GetLangNamespace(), InternString("Exception"));
	int temp = -1;
	FindFieldClass(exceptionT->u.class_, InternString("message"), &temp);
	object* ex = self->Exception;
	object* msg = AtVector(ex->u.field_vec, temp);
	Buffer* cstr = AtVector(msg->native_slot_vec, 0);

	char block[256] = {0};
	sprintf(block, "file: %s <%d>", env->ContextRef->filename, line);
	AppendsBuffer(sbuf, block);
	AppendBuffer(sbuf, '\n');
	AppendsBuffer(sbuf, cstr->Text);
	AppendBuffer(sbuf, '\n');
	//スタックトレースの表示
	type* stackTraceElementT = FindTypeFromNamespace(GetLangNamespace(), InternString("StackTraceElement"));
	//Exception#stackTraceを取得
	temp = -1;
	FindFieldClass(exceptionT->u.class_, InternString("stackTrace"), &temp);
	object* stackTraceObj = AtVector(ex->u.field_vec, temp);
	//StackTraceElement#fileName
	//StackTraceElement#lineIndex を取得
	int fileNameptr = -1;
	int lineIndexptr = -1;
	FindFieldClass(stackTraceElementT->u.class_, InternString("fileName"), &fileNameptr);
	FindFieldClass(stackTraceElementT->u.class_, InternString("lineIndex"), &lineIndexptr);
	int stackLen = GetLengthBCArray(stackTraceObj);
	for(int i=0; i<stackLen; i++) {
		object* e = GetBCArray(stackTraceObj, i);
		object* fileNameObj = AtVector(e->u.field_vec, fileNameptr);
		object* lineIndexObj = AtVector(e->u.field_vec, lineIndexptr);
		sprintf(block, "    @%d: %s\n", OBJ2INT(lineIndexObj), GetRawBCString(fileNameObj)->Text);
		AppendsBuffer(sbuf, block);
	}
	return ReleaseBuffer(sbuf);
}