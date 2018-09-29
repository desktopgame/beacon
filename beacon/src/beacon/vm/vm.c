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
static void vm_run(frame * self, enviroment * env, int pos, int deferStart);
static int stack_topi(frame* self);
static double stack_topd(frame* self);
static char stack_topc(frame* self);
static char* stack_tops(frame* self);
static bool stack_topb(frame* self);

static int stack_popi(frame* self);
static double stack_popd(frame* self);
static char stack_popc(frame* self);
static char* stack_pops(frame* self);
static bool stack_popb(frame* self);
static void remove_from_parent(frame* self);
static void frame_markStatic(field* item);
static void vm_delete_defctx(VectorItem e);
static bool throw_npe(frame* self, object* o);
static char* create_error_message(frame * self, enviroment* env, int pc);
static string_view gVMError = ZERO_VIEW;

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




void ExecuteVM(frame* self, enviroment* env) {
	ResumeVM(self, env, 0);
}

void ResumeVM(frame * self, enviroment * env, int pos) {
	self->defer_vec = NewVector();
	vm_run(self, env, pos, -1);
	while(self->defer_vec->length > 0) {
		defer_context* defctx = (defer_context*)PopVector(self->defer_vec);
		label* offset = defctx->offset;
		Vector* save = self->ref_stack;
		self->ref_stack = defctx->variable_vec;
		vm_run(self, env, offset->cursor, offset->cursor);
		self->ref_stack = save;
		DeleteDeferContext(defctx);
	}
	DeleteVector(self->defer_vec, VectorDeleterOfNull);
	self->defer_vec = NULL;
}

void NativeThrowVM(frame * self, object * exc) {
	self->exception = exc;

	ThrowVM(self, exc);
	sg_thread* th = sg_thread_current(script_context_get_current());
	//空ならプログラムを終了
	if (IsEmptyVector(th->trace_stack)) {
		TerminateVM(self);
	//どこかでキャッチしようとしている
	} else {
		int temp = 0;
		ValidateVM(self, self->context_ref->buf->source_vec->length, &temp);
		self->native_throw_pos = temp;
	}
}

void ThrowVM(frame * self, object * exc) {
	frame* temp = self;
	do {
		temp->exception = exc;
		temp = temp->parent;
	} while (temp != NULL);
}

void CatchVM(frame * self) {
	if (self == NULL) {
		return;
	}
	if (self->parent != NULL) {
		CatchVM(self->parent);
	}
	self->validate = false;
	if(self->exception != NULL) {
		self->exception->paint = PAINT_UNMARKED_T;
		self->exception = NULL;
	}
}

bool ValidateVM(frame* self, int source_len, int* pcDest) {
	sg_thread* th = sg_thread_current(script_context_get_current());
	vm_trace* trace = (vm_trace*)TopVector(th->trace_stack);
	self->validate = true;
	//汚染
	frame* p = self->parent;
	while(p != NULL) {
		p->validate = true;
		p = p->parent;
	}
	//ここなので catch節 へ向かう
	if (trace->fr == self) {
		//ここでジャンプレベルを確認するのは
		//例えば
		// try { throw ... } catch { ... }
		//と、
		// try { throwFunc() ... } catch { ... }
		//では、
		//プログラムカウンタの位置が異なるためです。
		//
		if (trace->jump_level > 0) {
			*pcDest = trace->pc + 1;
		} else *pcDest = trace->pc;
		self->validate = false;
		return true;
	//ここではないので終了
	} else {
		trace->jump_level++;
		*pcDest = source_len;
		return false;
	}
}

void TerminateVM(frame * self) {
	sg_thread_main()->vm_crush_by_exception = true;
	frame* temp = self;
	do {
		temp->terminate = true;
		temp = temp->parent;
	} while (temp != NULL);
}

void UncaughtVM(frame * self, enviroment* env, int pc) {
	char* message = create_error_message(self, env, pc);
	script_context* sctx = script_context_get_current();
	if(sctx->print_error) {
		fprintf(stderr, "%s", message);
	}
	gVMError = InternString(message);
	MEM_FREE(message);
	CatchVM(GetRootFrame(self));
	heap_gc(heap_get());
}

string_view GetVMErrorMessage() {
	return gVMError;
}


//private
static void vm_run(frame * self, enviroment * env, int pos, int deferStart) {
	assert(env != NULL);
	script_context* ctx = script_context_get_current();
	int source_len = env->buf->source_vec->length;
	self->context_ref = env;
	heap* he = heap_get();
	for (int IDX = pos; IDX < source_len; IDX++) {
		//このVMの子要素で例外がスローされ、
		//それを子要素自身で処理できなかった場合には、
		//自分で処理を試みます。
		if (self->validate) {
			if (!ValidateVM(self, source_len, &IDX)) {
				break;
			}
		}
		if(self->terminate) {
			break;
		}
		self->pc = IDX;
		opcode b = (opcode)GetEnviromentSourceAt(env, IDX);
		switch (b) {
			//int & int
			case OP_IADD:
				PushVector(self->value_stack, NON_NULL(object_int_get(SPI(self) + SPI(self))));
				break;
			case OP_ISUB:
				PushVector(self->value_stack, NON_NULL(object_int_get(SPI(self) - SPI(self))));
				break;
			case OP_IMUL:
				PushVector(self->value_stack, NON_NULL(object_int_get(SPI(self) * SPI(self))));
				break;
			case OP_IDIV:
			{
				int a = SPI(self);
				int b = SPI(self);
				assert(b != 0);
				PushVector(self->value_stack, NON_NULL(object_int_get(a / b)));
				break;
			}
			case OP_IMOD:
				PushVector(self->value_stack, NON_NULL(object_int_get(SPI(self) % SPI(self))));
				break;
			case OP_IBIT_OR:
			{
				int a = SPI(self);
				int b = SPI(self);
				PushVector(self->value_stack, NON_NULL(object_int_get(a | b)));
				break;
			}
			case OP_ILOGIC_OR:
			{
				int a = SPI(self);
				int b = SPI(self);
				PushVector(self->value_stack, NON_NULL(object_int_get(a || b)));
				break;
			}
			case OP_IBIT_AND:
			{
				int a = SPI(self);
				int b = SPI(self);
				PushVector(self->value_stack, NON_NULL(object_int_get(a & b)));
				break;
			}
			case OP_ILOGIC_AND:
			{
				//SPI(self) をそのまま埋めると正常に動作しない
				//おそらくマクロの展開によるもの
				//短絡評価のせいだった
				int a = SPI(self);
				int b = SPI(self);
				PushVector(self->value_stack, NON_NULL(object_int_get(a && b)));
				break;
			}
			case OP_IEQ:
				PushVector(self->value_stack, NON_NULL(object_bool_get(SPI(self) == SPI(self))));
				break;
			case OP_INOTEQ:
				PushVector(self->value_stack, NON_NULL(object_bool_get(SPI(self) != SPI(self))));
				break;
			case OP_IGT:
				PushVector(self->value_stack, NON_NULL(object_bool_get(SPI(self) > SPI(self))));
				break;
			case OP_IGE:
				PushVector(self->value_stack, NON_NULL(object_bool_get(SPI(self) >= SPI(self))));
				break;
			case OP_ILT:
			{
				object* a_ = PopVector(self->value_stack);
				object* b_ = PopVector(self->value_stack);
				PushVector(self->value_stack, NON_NULL(object_bool_get(OBJ2INT(a_) < OBJ2INT(b_))));
				//PushVector(self->value_stack, object_bool_get(SPI(self) < SPI(self)));
				break;
			}
			case OP_ILE:
				PushVector(self->value_stack, NON_NULL(object_bool_get(SPI(self) <= SPI(self))));
				break;
			case OP_ILSH:
				PushVector(self->value_stack, NON_NULL(object_int_get(SPI(self) << SPI(self))));
				break;
			case OP_IRSH:
				PushVector(self->value_stack, NON_NULL(object_int_get(SPI(self) >> SPI(self))));
				break;
			case OP_IEXCOR:
				PushVector(self->value_stack, NON_NULL(object_int_get(SPI(self) ^ SPI(self))));
				break;
			case OP_IFLIP:
				PushVector(self->value_stack, NON_NULL(object_int_get(~SPI(self))));
				break;
			case OP_CEQ:
				PushVector(self->value_stack, NON_NULL(object_bool_get(SPC(self) == SPC(self))));
				break;
			case OP_CNOTEQ:
				PushVector(self->value_stack, NON_NULL(object_bool_get(SPC(self) != SPC(self))));
				break;
			case OP_CGT:
				PushVector(self->value_stack, NON_NULL(object_bool_get(SPC(self) > SPC(self))));
				break;
			case OP_CGE:
				PushVector(self->value_stack, NON_NULL(object_bool_get(SPC(self) >= SPC(self))));
				break;
			case OP_CLT:
				PushVector(self->value_stack, NON_NULL(object_bool_get(SPC(self) < SPC(self))));
				break;
			case OP_CLE:
				PushVector(self->value_stack, NON_NULL(object_bool_get(SPC(self) <= SPC(self))));
				break;
				//double & double
			case OP_DADD:
				PushVector(self->value_stack, NON_NULL(object_double_new(SPD(self) + SPD(self))));
				break;
			case OP_DSUB:
				PushVector(self->value_stack, NON_NULL(object_double_new(SPD(self) - SPD(self))));
				break;
			case OP_DMUL:
				PushVector(self->value_stack, NON_NULL(object_double_new(SPD(self) * SPD(self))));
				break;
			case OP_DDIV:
				PushVector(self->value_stack, NON_NULL(object_double_new(SPD(self) / SPD(self))));
				break;
			case OP_DMOD:
				PushVector(self->value_stack, NON_NULL(object_double_new((double)((int)SPD(self) % (int)SPD(self)))));
				break;
			case OP_DEQ:
				PushVector(self->value_stack, NON_NULL(object_bool_get(SPD(self) == SPD(self))));
				break;
			case OP_DNOTEQ:
				PushVector(self->value_stack, NON_NULL(object_bool_get(SPD(self) != SPD(self))));
				break;
			case OP_DGT:
				PushVector(self->value_stack, NON_NULL(object_bool_get(SPD(self) > SPD(self))));
				break;
			case OP_DGE:
				PushVector(self->value_stack, NON_NULL(object_bool_get(SPD(self) >= SPD(self))));
				break;
			case OP_DLT:
				PushVector(self->value_stack, NON_NULL(object_bool_get(SPD(self) < SPD(self))));
				break;
			case OP_DLE:
				PushVector(self->value_stack, NON_NULL(object_bool_get(SPD(self) <= SPD(self))));
				break;
			case OP_INEG:
				PushVector(self->value_stack, NON_NULL(object_int_get(-SPI(self))));
				break;
			case OP_DNEG:
				PushVector(self->value_stack, NON_NULL(object_double_new(-SPD(self))));
				break;
			case OP_BNOT:
			{
				bool a = SPB(self);
				PushVector(self->value_stack, NON_NULL(object_bool_get(!a)));
				break;
			}
				//TODO:短絡評価していない
			case OP_BBIT_OR:
			{
				bool ab = SPB(self);
				bool bb = SPB(self);
				PushVector(self->value_stack, NON_NULL(object_bool_get(ab | bb)));
				break;
			}
			case OP_BLOGIC_OR:
			{
				bool ab = SPB(self);
				bool bb = SPB(self);
				PushVector(self->value_stack, NON_NULL(object_bool_get(ab || bb)));
				break;
			}
			case OP_BBIT_AND:
			{
				bool ab = SPB(self);
				bool bb = SPB(self);
				PushVector(self->value_stack,NON_NULL( object_bool_get(ab & bb)));
				break;
			}
			case OP_BLOGIC_AND:
			{
				bool ab = SPB(self);
				bool bb = SPB(self);
				PushVector(self->value_stack, NON_NULL(object_bool_get(ab && bb)));
				break;
			}
			case OP_BEXCOR:
				PushVector(self->value_stack, NON_NULL(object_bool_get(SPB(self) ^ SPB(self))));
				break;
			case OP_BFLIP:
				PushVector(self->value_stack, NON_NULL(object_bool_get(~SPB(self))));
				break;
				//push const
			case OP_ICONST:
			{
				int index = (int)GetEnviromentSourceAt(env, ++IDX);
				object* o = (object*)GetEnviromentCIntAt(env, index);
				PushVector(self->value_stack, NON_NULL(o));
				break;
			}
			case OP_DCONST:
			{
				int index = (int)GetEnviromentSourceAt(env, ++IDX);
				object* d = GetEnviromentCDoubleAt(env, index);
				PushVector(self->value_stack, NON_NULL(d));
				break;
			}
			case OP_CCONST:
			{
				int index = (int)GetEnviromentSourceAt(env, ++IDX);
				object* c = GetEnviromentCCharAt(env, index);
				PushVector(self->value_stack, NON_NULL(c));
				break;
			}
			case OP_SCONST:
			{
				int index = (int)GetEnviromentSourceAt(env, ++IDX);
				object* cs = GetEnviromentCStringAt(env, index);
				PushVector(self->value_stack, NON_NULL(cs));
				break;
			}
			case OP_TRUE:
			{
				PushVector(self->value_stack, object_get_true());
				break;
			}
			case OP_FALSE:
			{
				PushVector(self->value_stack, object_get_false());
				break;
			}
			case OP_NULL:
			{
				PushVector(self->value_stack, object_get_null());
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
				object* e = (object*)PopVector(self->value_stack);
				ThrowVM(self, e);
				sg_thread* th = sg_thread_current(script_context_get_current());
				//空ならプログラムを終了
				if (IsEmptyVector(th->trace_stack)) {
					TerminateVM(self);
					//どこかでキャッチしようとしている
				} else {
					ValidateVM(self, source_len, &IDX);
				}
				break;
			}
			case OP_TRY_ENTER:
			{
				sg_thread* th = sg_thread_current(script_context_get_current());
				vm_trace* trace = NewVMTrace(self);
				trace->pc = IDX; //goto
				PushVector(th->trace_stack, trace);
				//goto
				IDX++;
				//label
				IDX++;
				//これ以降は通常のステートメント...
				break;
			}
			case OP_TRY_EXIT:
			{
				sg_thread* th = sg_thread_current(script_context_get_current());
				vm_trace* trace = (vm_trace*)PopVector(th->trace_stack);
				DeleteVMTrace(trace);
				break;
			}
			case OP_TRY_CLEAR:
			{
				sg_thread* th = sg_thread_current(script_context_get_current());
				CatchVM(self);
				vm_trace* trace = (vm_trace*)PopVector(th->trace_stack);
				DeleteVMTrace(trace);
				break;
			}
			case OP_HEXCEPTION:
			{
				PushVector(self->value_stack, NON_NULL(self->exception));
				break;
			}
			case OP_INSTANCEOF:
			{
				generic_type* gtype = (generic_type*)PopVector(self->type_args_vec);
				object* v = (object*)PopVector(self->value_stack);
				//generic_type_print(gtype);
				//Printfln("");
				//generic_type_print(v->gtype);
				//Printfln("");
				int dist = generic_type_distance(gtype, v->gtype, sg_thread_context());
				object* b = object_bool_get(dist >= 0);
				PushVector(self->value_stack, b);
				break;
			}
			case OP_DUP:
				PushVector(self->value_stack, TopVector(self->value_stack));
				break;
			case OP_POP:
				PopVector(self->value_stack);
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
				PushVector(self->value_stack, NON_NULL(o));
				//これを this とする
				AssignVector(self->ref_stack, 0, o);
				break;
			}
			case OP_ALLOC_FIELD:
			{
				int absClsIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				type* tp = (type*)AtVector(ctx->type_vec, absClsIndex);
				class_* cls = TYPE2CLASS(tp);
				object* obj = (object*)TopVector(self->value_stack);
				//仮想関数テーブル更新
				class_create_vtable(cls);
				obj->gtype = generic_type_ref(cls->parent);
				obj->vptr = cls->vt;
				//ジェネリック型を実体化
				if(cls->type_parameter_list->length == 0) {
					obj->gtype = tp->generic_self;
				} else {
					generic_type* g = generic_type_new(tp);
					for(int i=0; i<cls->type_parameter_list->length; i++) {
						generic_type_addargs(g, (generic_type*)AtVector(self->type_args_vec, i));
					}
					obj->gtype = g;
				}
				//フィールドの割り当て
				class_alloc_fields(cls, obj, self);
				assert(obj->gtype != NULL);
				break;
			}
			case OP_NEW_INSTANCE:
			{
				//生成するクラスとコンストラクタを特定
				int absClsIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				int constructorIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				type* tp = (type*)AtVector(ctx->type_vec, absClsIndex);
				assert(tp->tag == TYPE_CLASS_T);
				class_* cls = TYPE2CLASS(tp);
				#if defined(DEBUG)
				const char* clsname = Ref2Str(cls->namev);
				#endif
				constructor* ctor = (constructor*)AtVector(cls->constructor_list, constructorIndex);
				//新しいVMでコンストラクタを実行
				//また、現在のVMから実引数をポップ
				frame* sub = SubFrame(self);
				sub->receiver = tp;
				call_frame* cfr = call_context_push(sg_thread_context(), FRAME_STATIC_INVOKE_T);
				cfr->u.static_invoke.args = NewVector();
				cfr->u.static_invoke.typeargs = NewVector();
				for (int i = 0; i < ctor->parameter_list->length; i++) {
					VectorItem e = PopVector(self->value_stack);
					object* o = (object*)e;
					PushVector(sub->value_stack, NON_NULL(e));
					AssignVector(cfr->u.static_invoke.args, (ctor->parameter_list->length - i), o->gtype);
				}
				//コンストラクタに渡された型引数を引き継ぐ
				int typeparams = cls->type_parameter_list->length;
				for(int i=0; i<typeparams; i++) {
					VectorItem e = PopVector(self->type_args_vec);
					AssignVector(sub->type_args_vec, (typeparams - i) - 1, e);
					AssignVector(cfr->u.static_invoke.typeargs, (cls->type_parameter_list->length - i), e);
				}
				//Printi(self->level);
				//Printfln("[ %s#new ]", type_name(ctor->parent));
				//DumpEnviromentOp(ctor->env, sub->level);
				//DumpOpcodeBuf(ctor->env->buf, sub->level);
				ExecuteVM(sub, ctor->env);
				DeleteVector(cfr->u.static_invoke.args, VectorDeleterOfNull);
				DeleteVector(cfr->u.static_invoke.typeargs, VectorDeleterOfNull);
				call_context_pop(sg_thread_context());
				//コンストラクタを実行した場合、
				//objectがスタックのトップに残っているはず
				VectorItem returnV = TopVector(sub->value_stack);
				object* returnO = (object*)returnV;
				PushVector(self->value_stack, NON_NULL(returnV));
				DeleteFrame(sub);
				break;
			}
			case OP_CHAIN_THIS:
			case OP_CHAIN_SUPER:
			{
				int absClsIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				int ctorIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				type* tp = (type*)AtVector(ctx->type_vec, absClsIndex);
				assert(tp->tag == TYPE_CLASS_T);
				class_* cls = tp->u.class_;
				constructor* ctor = (constructor*)AtVector(cls->constructor_list, ctorIndex);
				//コンストラクタを実行するためのVMを作成
				frame* sub = SubFrame(self);
				sub->receiver = tp;
				call_frame* cfr = call_context_push(sg_thread_context(), FRAME_STATIC_INVOKE_T);
				cfr->u.static_invoke.args = NewVector();
				cfr->u.static_invoke.typeargs = NewVector();
				//チェインコンストラクタに渡された実引数をプッシュ
				for (int i = 0; i < ctor->parameter_list->length; i++) {
					object* o = (object*)PopVector(self->value_stack);
					PushVector(sub->value_stack, NON_NULL(o));
					AssignVector(cfr->u.static_invoke.args, (ctor->parameter_list->length - i), o->gtype);
				}
				for(int i=0; i<self->type_args_vec->length; i++) {
					PushVector(cfr->u.static_invoke.typeargs, self->type_args_vec);
				}
				//		DumpEnviromentOp(ctor->env, sub->level);
				//DumpOpcodeBuf(ctor->env->buf, sub->level);
				ExecuteVM(sub, ctor->env);
				DeleteVector(cfr->u.static_invoke.args, VectorDeleterOfNull);
				DeleteVector(cfr->u.static_invoke.typeargs, VectorDeleterOfNull);
				call_context_pop(sg_thread_context());
				//コンストラクタを実行した場合、
				//objectがスタックのトップに残っているはず
				VectorItem returnV = TopVector(sub->value_stack);
				object* returnO = (object*)returnV;
				AssignVector(self->ref_stack, 0, returnV);
				PushVector(self->value_stack, NON_NULL(returnV));

				DeleteFrame(sub);
				//class_alloc_fields(cls, returnO);
				break;
			}
			case OP_THIS:
			{
				PushVector(self->value_stack, AtVector(self->ref_stack, 0));
				break;
			}
			case OP_SUPER:
			{
				object* a = AtVector(self->ref_stack, 0);
				object* super = object_clone(a);
				super->gtype = TYPE2CLASS(GENERIC2TYPE(a->gtype))->super_class;
				super->vptr = TYPE2CLASS(GENERIC2TYPE(TYPE2CLASS(GENERIC2TYPE(a->gtype))->super_class))->vt;
				PushVector(self->value_stack, super);
				break;
			}
			//store,load
			case OP_PUT_FIELD:
			{
				object* assignValue = (object*)PopVector(self->value_stack);
				object* assignTarget = (object*)PopVector(self->value_stack);
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
				object* sourceObject = (object*)PopVector(self->value_stack);
				if(throw_npe(self, sourceObject)) {
					break;
				}
				//assert(sourceObject->tag == OBJECT_REF_T);
				//int absClsIndex = (int)GetEnviromentSourceAt(env, ++i);
				int fieldIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				object* val = (object*)AtVector(sourceObject->u.field_vec, fieldIndex);
				PushVector(self->value_stack, val);
				break;
			}

			case OP_PUT_STATIC:
			{
				int absClsIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				int fieldIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				type* tp = (type*)AtVector(ctx->type_vec, absClsIndex);
				class_* cls = tp->u.class_;
				field* f = class_get_sfield(cls, fieldIndex);
				object* sv = (object*)PopVector(self->value_stack);
				f->static_value = sv;
				break;
			}

			case OP_GET_STATIC:
			{
				int absClsIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				int fieldIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				type* cls = (type*)AtVector(ctx->type_vec, absClsIndex);
				field* f = class_get_sfield(cls->u.class_, fieldIndex);
				PushVector(self->value_stack, NON_NULL(f->static_value));
				break;
			}
			case OP_PUT_PROPERTY:
			{
				object* assignValue = (object*)PopVector(self->value_stack);
				object* assignTarget = (object*)PopVector(self->value_stack);
				if(throw_npe(self, assignTarget)) {
					break;
				}
				assert(assignTarget->tag == OBJECT_REF_T);
				int propIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				property* pro = class_get_property(TYPE2CLASS(GENERIC2TYPE(assignTarget->gtype)), propIndex);
				//プロパティを実行
				frame* sub = SubFrame(self);
				sub->receiver = pro->parent;
				PushVector(sub->value_stack, assignValue);
				PushVector(sub->value_stack, assignTarget);
				ExecuteVM(sub, pro->set->env);
				DeleteFrame(sub);
				break;
			}
			case OP_GET_PROPERTY:
			{
				object* sourceObject = (object*)PopVector(self->value_stack);
				if(throw_npe(self, sourceObject)) {
					break;
				}
				int propIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				property* pro = class_get_property(TYPE2CLASS(GENERIC2TYPE(sourceObject->gtype)), propIndex);
				//プロパティを実行
				frame* sub = SubFrame(self);
				sub->receiver = pro->parent;
				PushVector(sub->value_stack, sourceObject);
				ExecuteVM(sub, pro->get->env);
				//戻り値をスタックに残す
				VectorItem returnV = TopVector(sub->value_stack);
				object* returnO = (object*)returnV;
				AssignVector(self->ref_stack, 0, returnV);
				PushVector(self->value_stack, returnV);
				DeleteFrame(sub);
				break;
			}
			case OP_PUT_STATIC_property:
			{
				object* sv = (object*)PopVector(self->value_stack);
				int absClsIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				int propIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				type* tp = (type*)AtVector(ctx->type_vec, absClsIndex);
				class_* cls = tp->u.class_;
				property * p = class_get_sproperty(cls, propIndex);
				//プロパティを実行
				frame* sub = SubFrame(self);
				sub->receiver = NULL;
				PushVector(sub->value_stack, sv);
				ExecuteVM(sub, p->set->env);
				DeleteFrame(sub);
				break;
			}
			case OP_GET_STATIC_property:
			{
				object* sv = (object*)PopVector(self->value_stack);
				int absClsIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				int propIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				type* tp = (type*)AtVector(ctx->type_vec, absClsIndex);
				class_* cls = tp->u.class_;
				property * p = class_get_sproperty(cls, propIndex);
				//プロパティを実行
				frame* sub = SubFrame(self);
				sub->receiver = NULL;
				ExecuteVM(sub, p->get->env);
				//戻り値をスタックに残す
				VectorItem returnV = TopVector(sub->value_stack);
				object* returnO = (object*)returnV;
				AssignVector(self->ref_stack, 0, returnV);
				PushVector(self->value_stack, returnV);
				DeleteFrame(sub);
				break;
			}
			case OP_STORE:
			{
				int index = (int)GetEnviromentSourceAt(env, ++IDX);
				VectorItem e = PopVector(self->value_stack);
				object* o = (object*)e;
				assert(o != NULL);
				AssignVector(self->ref_stack, index, e);
				//INFO("store");
				break;
			}
			case OP_LOAD:
			{
				int index = (int)GetEnviromentSourceAt(env, ++IDX);
				VectorItem e = AtVector(self->ref_stack, index);
				object*  o = (object*)e;
				assert(o != NULL);
				PushVector(self->value_stack, e);
				//INFO("load");
				break;
			}
			case OP_DOWN_AS:
			{
				object* o = PopVector(self->value_stack);
				generic_type* a = PopVector(self->type_args_vec);
				a = generic_type_apply(a, sg_thread_context());
				if(a->core_type->tag == TYPE_INTERFACE_T) {
					interface_* inter = TYPE2INTERFACE(GENERIC2TYPE(a));
					Vector* inter_list = class_get_interface_tree(TYPE2CLASS(GENERIC2TYPE(o->gtype)));
					int iter = FindVector(inter_list, inter);
					DeleteVector(inter_list, VectorDeleterOfNull);
					if(iter == -1) {
						PushVector(self->value_stack, object_get_null());
					} else {
						PushVector(self->value_stack, o);
					}
					break;
				}
				if(generic_type_distance(o->gtype, a, sg_thread_context()) < 0) {
					PushVector(self->value_stack, object_get_null());
				} else {
					//o = object_clone(o);
					//o->gtype = a;
					PushVector(self->value_stack, o);
				}
				break;
			}
			case OP_UP_AS:
			{
				object* o = PopVector(self->value_stack);
				generic_type* a = PopVector(self->type_args_vec);
				a = generic_type_apply(a, sg_thread_context());
				assert(a->core_type != NULL);
				if(a->core_type->tag == TYPE_CLASS_T) {
					PushVector(self->value_stack, o);
				} else if(a->core_type->tag == TYPE_INTERFACE_T) {
					interface_* inter = TYPE2INTERFACE(GENERIC2TYPE(a));
					Vector* inter_list = class_get_interface_tree(TYPE2CLASS(GENERIC2TYPE(o->gtype)));
					int iter = FindVector(inter_list, inter);
					DeleteVector(inter_list, VectorDeleterOfNull);
					if(iter == -1) {
						PushVector(self->value_stack, object_get_null());
					} else {
						PushVector(self->value_stack, o);
					}
				}
				break;
			}
			//invoke
			case OP_INVOKEINTERFACE:
			{
				int absClassIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				int methodIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				type* tp = AtVector(ctx->type_vec, absClassIndex);
				object* o = (object*)TopVector(self->value_stack);
				if(throw_npe(self, o)) {
					break;
				}
				method* m = class_get_impl_method(o->gtype->core_type->u.class_, tp, methodIndex);
				call_context* cctx = sg_thread_context();
				method_execute(m, self, env);
				break;
			}
			case OP_INVOKESTATIC:
			{
				int absClassIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				int methodIndex = (int)GetEnviromentSourceAt(env, ++IDX);
				type* cls = (type*)AtVector(ctx->type_vec, absClassIndex);
				method* m = class_get_smethod(cls->u.class_, methodIndex);
				#if defined(DEBUG)
				const char* clsname = Ref2Str(type_name(cls));
				const char* mname = Ref2Str(m->namev);
				#endif
				method_execute(m, self, env);
				break;
			}
			case OP_INVOKEVIRTUAL:
			{
				int index = (int)GetEnviromentSourceAt(env, ++IDX);
				object* o = (object*)TopVector(self->value_stack);
				if(throw_npe(self, o)) {
					break;
				}
				method* m = class_get_method(o, index);
				method_execute(m, self, env);
				break;
			}
			case OP_INVOKESPECIAL:
			{
				//privateメソッドには常にレシーバがいないはず
				//オブジェクトから直接型を取り出してしまうと具象すぎる
				int index = (int)GetEnviromentSourceAt(env, ++IDX);
				object* o = (object*)TopVector(self->value_stack);
				if(throw_npe(self, o)) {
					break;
				}
				class_* cl = TYPE2CLASS(o->gtype->core_type);
				if(self->receiver != NULL) {
					cl = TYPE2CLASS(self->receiver);
				}
				method* m = (method*)AtVector(cl->method_list, index);
				method_execute(m, self, env);
				break;
			}
			case OP_INVOKEOPERATOR:
			{
				int index = (int)GetEnviromentSourceAt(env, ++IDX);
				object* o = (object*)TopVector(self->value_stack);
				class_* cl = TYPE2CLASS(o->gtype->core_type);
				#if defined(DEBUG)
				char* clname = Ref2Str(cl->namev);
				#endif
				class_create_operator_vt(cl);
				operator_overload* operator_ov = (operator_overload*)AtVector(cl->ovt->vec, index);
				operator_overload_execute(operator_ov, self, env);
				break;
			}
			case OP_CORO_INIT:
			{
				object* o = (object*)AtVector(self->ref_stack, 0);
				if(o->native_slot_vec == NULL) {
					o->native_slot_vec = NewVector();
				}
				int param_len = (int)GetEnviromentSourceAt(env, ++IDX);
				int op_len = (int)GetEnviromentSourceAt(env, ++IDX);
				yield_context* yctx = NewYieldContext();
				yctx->yield_offset = 0;
				yctx->yield_count = 0;
				yctx->len = op_len;
				yctx->parameter_vec = NewVector();
				//iterate(int, int) の int, int を受け取る
				yctx->source_obj = AtVector(self->ref_stack, 1);
				#if defined(DEBUG)
				const char* yname = object_name(yctx->source_obj);
				#endif
				for(int i=2; i<param_len + 1; i++) {
					object* a = AtVector(self->ref_stack, i);
					assert(a != NULL);
					PushVector(yctx->parameter_vec, a);
				}
				//暗黙的に生成されるイテレータ実装クラスのコンストラクタは、
				//必ず最後に iterate() を定義したクラスのオブジェクトを受け取る。
				PushVector(o->native_slot_vec, yctx);
				o->is_coroutine = true;
				break;
			}
			case OP_CORO_NEXT:
			{
				object* o = self->coroutine;
				object* ret = (object*)PopVector(self->value_stack);
				assert(o->is_coroutine);
				yield_context* yctx = (yield_context*)AtVector(o->native_slot_vec, 0);
				//この実行コードが
				//前回からの再開によって開始した場合、それを元に戻す
				if(yctx->vm_ref_stack != NULL) {
					self->ref_stack = yctx->vm_ref_stack;
					self->value_stack = yctx->vm_value_stack;
				}
				assert(ret != NULL);
				yctx->stock_obj = ret;
				//最初に実行された yield return に時点でコピーする
				if(yctx->vm_ref_stack == NULL) {
					yctx->backup_ref_stack = CloneVector(self->ref_stack);
					yctx->backup_value_stack = NewVector();
				}
				yctx->yield_offset = IDX + 1;
				yctx->yield_count++;
				IDX = source_len;
				//まだ実行できる?
				object* hasNext = object_bool_get(yctx->yield_offset < yctx->len);
				PushVector(self->value_stack, hasNext);
				break;
			}
			case OP_CORO_EXIT:
			{
				object* o = self->coroutine;
				assert(o->is_coroutine);
				yield_context* yctx = (yield_context*)AtVector(o->native_slot_vec, 0);
				IDX = source_len;
				yctx->yield_offset = source_len;
				if(yctx->vm_ref_stack != NULL) {
					self->ref_stack = yctx->vm_ref_stack;
					self->value_stack = yctx->vm_value_stack;
				}
				PushVector(self->value_stack, object_get_false());
				break;
			}
			case OP_CORO_RESUME:
			{
				object* o = self->coroutine;
				assert(o->is_coroutine);
				yield_context* yctx = (yield_context*)AtVector(o->native_slot_vec, 0);
				//前回の位置が記録されているのでそこから
				if(yctx->yield_offset != 0) {
					IDX = yctx->yield_offset - 1;
					yctx->vm_ref_stack = self->ref_stack;
					yctx->vm_value_stack = self->value_stack;
					self->ref_stack = yctx->backup_ref_stack;
					self->value_stack = yctx->backup_value_stack;
				}
				break;
			}
			case OP_CORO_CURRENT:
			{
				object* o = self->coroutine;
				assert(o->is_coroutine);
				yield_context* yctx = (yield_context*)AtVector(o->native_slot_vec, 0);
				PushVector(self->value_stack, yctx->stock_obj);
				break;
			}
			case OP_CORO_SWAP_SELF:
			{
				assert(self->coroutine == NULL);
				object* o = (object*)AtVector(self->ref_stack, 0);
				assert(o->is_coroutine);
				yield_context* yctx = AtVector(o->native_slot_vec, 0);
				if(yctx->cached) {
					self->coroutine = o;
					break;
				}
				#if defined(DEBUG)
				const char* oname = object_name(o);
				const char* yname = object_name(yctx->source_obj);
				#endif
				//[0] = Array
				//[1] = ArrayIterator
				AssignVector(self->ref_stack, 0, yctx->source_obj);
				assert(yctx->source_obj != NULL);
				for(int i=0; i<yctx->parameter_vec->length; i++) {
					object* e = AtVector(yctx->parameter_vec, i);
					assert(e != NULL);
					AssignVector(self->ref_stack, i + 1, e);
				}
				self->coroutine = o;
				yctx->cached = true;
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
						//PushVector(stack, generic_type_new(NULL));
					} else if(code == OP_GENERIC_EXIT) {
						depth--;
						int count = (int)PopVector(counts);
						generic_type* head = AtVector(stack, 0);
						for(int i=0; i<count; i++) {
							generic_type_addargs(head, (generic_type*)PopVector(stack));
						}
						if(depth == 0) {
							assert(stack->length == 1);
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
							a = generic_type_new((type*)AtVector(ctx->type_vec, arg));
						} else if(code == OP_GENERIC_INSTANCE_TYPE) {
							object* receiver = (object*)AtVector(self->ref_stack, 0);
							a = (generic_type*)AtVector(receiver->gtype->type_args_list, arg);
						} else if(code == OP_GENERIC_STATIC_TYPE) {
							a = (generic_type*)AtVector(self->type_args_vec, arg);
						}
						PushVector(stack, a);
					}
				}
				assert(ret != NULL);
				PushVector(self->type_args_vec, ret);
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
				label* offset = (label*)GetEnviromentSourceAt(env, ++IDX);
				Vector* bind = CloneVector(self->ref_stack);
				defer_context* defctx = NewDeferContext();
				defctx->offset = offset;
				defctx->variable_vec = bind;
				PushVector(self->defer_vec, defctx);
				break;
			}
			case OP_BREAKPOINT:
			{
				break;
			}

			//goto
			case OP_GOTO:
			{
				label* l = (label*)GetEnviromentSourceAt(env, ++IDX);
				IDX = l->cursor;
				break;
			}

			case OP_GOTO_if_true:
			{
				bool v = SPB(self);
				label* l = (label*)GetEnviromentSourceAt(env, ++IDX);
				if (v) {
					IDX = l->cursor;
				}
				break;
			}

			case OP_GOTO_if_false:
			{
				bool v = SPB(self);
				label* l = (label*)GetEnviromentSourceAt(env, ++IDX);
				int a = l->cursor;
				if (!v) {
					IDX = l->cursor;
				}
				break;
			}

			default:
				break;
		}
		//ネイティブメソッドからスローされた例外を検出
		if (self->native_throw_pos != -1) {
			IDX = self->native_throw_pos;
			self->native_throw_pos = -1;
		}
		//キャッチされなかった例外によって終了する
		sg_thread* thr = sg_thread_main();
		if (self->terminate && !thr->vm_dump) {
			UncaughtVM(self, env, IDX);
			thr->vm_dump = true;
			break;
		}
	}
}

static int stack_topi(frame* self) {
	object* ret = (object*)TopVector(self->value_stack);
	assert(ret->tag == OBJECT_INT_T);
	return ret->u.int_;
}

static double stack_topd(frame* self) {
	object* ret = (object*)TopVector(self->value_stack);
	assert(ret->tag == OBJECT_DOUBLE_T);
	return ret->u.double_;
}

static char stack_topc(frame* self) {
	object* ret = (object*)TopVector(self->value_stack);
	assert(ret->tag == OBJECT_CHAR_T);
	return ret->u.char_;
}

static char* stack_tops(frame* self) {
	object* ret = (object*)TopVector(self->value_stack);
	assert(ret->tag == OBJECT_STRING_T);
	return bc_string_raw(ret)->text;
}

static bool stack_topb(frame* self) {
	object* ret = (object*)TopVector(self->value_stack);
	assert(ret->tag == OBJECT_BOOL_T);
	return ret->u.bool_;
}


static int stack_popi(frame* self) {
	object* ret = (object*)PopVector(self->value_stack);
	assert(ret->tag == OBJECT_INT_T);
	return ret->u.int_;
}

static double stack_popd(frame* self) {
	object* ret = (object*)PopVector(self->value_stack);
	assert(ret->tag == OBJECT_DOUBLE_T);
	return ret->u.double_;
}

static char stack_popc(frame* self) {
	object* ret = (object*)PopVector(self->value_stack);
	assert(ret->tag == OBJECT_CHAR_T);
	return ret->u.char_;
}

static char* stack_pops(frame* self) {
	object* ret = (object*)PopVector(self->value_stack);
	assert(ret->tag == OBJECT_STRING_T);
	return bc_string_raw(ret)->text;
}

static bool stack_popb(frame* self) {
	object* ret = (object*)PopVector(self->value_stack);
	assert(ret->tag == OBJECT_BOOL_T);
	return ret->u.bool_;
}

static bool throw_npe(frame* self, object* o) {
	if(o->tag == OBJECT_NULL_T) {
		NativeThrowVM(self, exception_new_simplef(self, "NullPointerException"));
		return true;
	}
	return false;
}

static char* create_error_message(frame * self, enviroment* env, int pc) {
	string_buffer* sbuf = NewBuffer();
	line_range* lr = FindLineRange(env->line_range_vec, pc);
	int line = -1;
	if (lr != NULL) {
		line = lr->lineno;
	}
	//例外のメッセージを取得
	type* exceptionT = namespace_get_type(namespace_lang(), InternString("Exception"));
	int temp = -1;
	class_find_field(exceptionT->u.class_, InternString("message"), &temp);
	object* ex = self->exception;
	object* msg = AtVector(ex->u.field_vec, temp);
	string_buffer* cstr = AtVector(msg->native_slot_vec, 0);

	char block[256] = {0};
	sprintf(block, "file: %s <%d>", env->context_ref->filename, line);
	AppendsBuffer(sbuf, block);
	AppendBuffer(sbuf, '\n');
	AppendsBuffer(sbuf, cstr->text);
	AppendBuffer(sbuf, '\n');
	//スタックトレースの表示
	type* stackTraceElementT = namespace_get_type(namespace_lang(), InternString("StackTraceElement"));
	//Exception#stackTraceを取得
	temp = -1;
	class_find_field(exceptionT->u.class_, InternString("stackTrace"), &temp);
	object* stackTraceObj = AtVector(ex->u.field_vec, temp);
	//StackTraceElement#fileName
	//StackTraceElement#lineIndex を取得
	int fileNameptr = -1;
	int lineIndexptr = -1;
	class_find_field(stackTraceElementT->u.class_, InternString("fileName"), &fileNameptr);
	class_find_field(stackTraceElementT->u.class_, InternString("lineIndex"), &lineIndexptr);
	int stackLen = bc_array_length(stackTraceObj);
	for(int i=0; i<stackLen; i++) {
		object* e = bc_array_get(stackTraceObj, i);
		object* fileNameObj = AtVector(e->u.field_vec, fileNameptr);
		object* lineIndexObj = AtVector(e->u.field_vec, lineIndexptr);
		sprintf(block, "    @%d: %s\n", OBJ2INT(lineIndexObj), bc_string_raw(fileNameObj)->text);
		AppendsBuffer(sbuf, block);
	}
	return ReleaseBuffer(sbuf);
}