#include "vm.h"
#include "frame.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "label.h"
#include "vm_trace.h"
#include "../env/class_loader.h"
#include "../env/type_interface.h"
#include "../env/type_impl.h"
#include "../env/field.h"
#include "../env/method.h"
#include "../env/object.h"
#include "../env/type_impl.h"
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
#include "../env/generic_type.h"
#include "yield_context.h"
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
static void frame_markallImpl(frame* self);
static void vm_delete_defctx(vector_item e);

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




void vm_execute(frame* self, enviroment* env) {
	vm_resume(self, env, 0);
}

void vm_resume(frame * self, enviroment * env, int pos) {
	self->defer_vec = vector_new();
	vm_run(self, env, pos, -1);
	while(self->defer_vec->length > 0) {
		defer_context* defctx = (defer_context*)vector_pop(self->defer_vec);
		label* offset = defctx->offset;
		vector* save = self->ref_stack;
		self->ref_stack = defctx->bind;
		vm_run(self, env, offset->cursor, offset->cursor);
		self->ref_stack = save;
		defer_context_delete(defctx);
	}
	vector_delete(self->defer_vec, vm_delete_defctx);
	self->defer_vec = NULL;
}

void vm_native_throw(frame * self, object * exc) {
	self->exception = exc;

	vm_throw(self, exc);
	sg_thread* th = sg_thread_current();
	//空ならプログラムを終了
	if (vector_empty(th->trace_stack)) {
		vm_terminate(self);
	//どこかでキャッチしようとしている
	} else {
		int temp = 0;
		vm_validate(self, self->context_ref->buf->source->length, &temp);
		self->native_throw_pos = temp;
	}
}

void vm_throw(frame * self, object * exc) {
	frame* temp = self;
	do {
		temp->exception = exc;
		temp = temp->parent;
	} while (temp != NULL);
}

void vm_catch(frame * self) {
	if (self == NULL) {
		return;
	}
	for (int i = 0; i < self->children_vec->length; i++) {
		frame* e = (frame*)vector_at(self->children_vec, i);
		vm_catch(e);
	}
	if(self->exception != NULL) {
		self->exception->paint = paint_unmarked;
		self->exception = NULL;
	}
}

bool vm_validate(frame* self, int source_len, int* pcDest) {
	sg_thread* th = sg_thread_current();
	vm_trace* trace = (vm_trace*)vector_top(th->trace_stack);
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

void vm_terminate(frame * self) {
	frame* temp = self;
	do {
		temp->terminate = true;
		temp = temp->parent;
	} while (temp != NULL);
}

void vm_uncaught(frame * self, enviroment* env, int pc) {
	line_range* lr = line_range_find(env->line_rangeVec, pc);
	int line = -1;
	if (lr != NULL) {
		line = lr->lineno;
	}
	//例外のメッセージを取得
	type* exceptionT = namespace_get_type(namespace_lang(), string_pool_intern("Exception"));
	int temp = -1;
	class_find_field(exceptionT->u.class_, string_pool_intern("message"), &temp);
	object* ex = self->exception;
	object* msg = vector_at(ex->u.field_vec, temp);
	string_buffer* cstr = vector_at(msg->native_slot_vec, 0);

	fprintf(stderr, "file: %s <%d>", env->context_ref->filename, line);
	fprintf(stderr, "\n");
	fprintf(stderr, "%s", cstr->text);
	fprintf(stderr, "\n");
	//スタックトレースの表示
	type* stackTraceElementT = namespace_get_type(namespace_lang(), string_pool_intern("StackTraceElement"));
	//Exception#stackTraceを取得
	temp = -1;
	class_find_field(exceptionT->u.class_, string_pool_intern("stackTrace"), &temp);
	object* stackTraceObj = vector_at(ex->u.field_vec, temp);
	//assert(stackTraceObj->tag == object_array);
	//StackTraceElement#fileName
	//StackTraceElement#lineIndex を取得
	int fileNameptr = -1;
	int lineIndexptr = -1;
	class_find_field(stackTraceElementT->u.class_, string_pool_intern("fileName"), &fileNameptr);
	class_find_field(stackTraceElementT->u.class_, string_pool_intern("lineIndex"), &lineIndexptr);
	int stackLen = bc_array_length(stackTraceObj);
	for(int i=0; i<stackLen; i++) {
		object* e = bc_array_get(stackTraceObj, i);
		object* fileNameObj = vector_at(e->u.field_vec, fileNameptr);
		object* lineIndexObj = vector_at(e->u.field_vec, lineIndexptr);
		fprintf(stderr, "    @%d: %s\n", OBJ2INT(lineIndexObj), bc_string_raw(fileNameObj)->text);
	}
	vm_catch(frame_root(self));
	heap_gc(heap_get(), gc_full);
}



//private
static void vm_run(frame * self, enviroment * env, int pos, int deferStart) {
	assert(env != NULL);
	script_context* ctx = script_context_get_current();
	int source_len = env->buf->source->length;
	self->context_ref = env;
	heap* he = heap_get();
	for (int IDX = pos; IDX < source_len; IDX++) {
		//このVMの子要素で例外がスローされ、
		//それを子要素自身で処理できなかった場合には、
		//自分で処理を試みます。
		if (self->validate) {
			if (!vm_validate(self, source_len, &IDX)) {
				break;
			}
		}
		self->pc = IDX;
		opcode b = (opcode)enviroment_source_at(env, IDX);
		switch (b) {
			//int & int
			case op_iadd:
				vector_push(self->value_stack, NON_NULL(object_int_get(SPI(self) + SPI(self))));
				break;
			case op_isub:
				vector_push(self->value_stack, NON_NULL(object_int_get(SPI(self) - SPI(self))));
				break;
			case op_imul:
				vector_push(self->value_stack, NON_NULL(object_int_get(SPI(self) * SPI(self))));
				break;
			case op_idiv:
			{
				int a = SPI(self);
				int b = SPI(self);
				assert(b != 0);
				vector_push(self->value_stack, NON_NULL(object_int_get(a / b)));
				break;
			}
			case op_imod:
				vector_push(self->value_stack, NON_NULL(object_int_get(SPI(self) % SPI(self))));
				break;
			case op_ibit_or:
				vector_push(self->value_stack, NON_NULL(object_int_get(SPI(self) | SPI(self))));
				break;
			case op_ilogic_or:
			{
				//SPI(self) をそのまま埋めると正常に動作しない
				//おそらくマクロの展開によるもの
				int a = SPI(self);
				int b = SPI(self);
				vector_push(self->value_stack, NON_NULL(object_int_get(a || b)));
				break;
			}
			case op_ibit_and:
				vector_push(self->value_stack, NON_NULL(object_int_get(SPI(self) & SPI(self))));
				break;
			case op_ilogic_and:
			{
				//SPI(self) をそのまま埋めると正常に動作しない
				//おそらくマクロの展開によるもの
				int a = SPI(self);
				int b = SPI(self);
				vector_push(self->value_stack, NON_NULL(object_int_get(a && b)));
				break;
			}
			case op_ieq:
				vector_push(self->value_stack, NON_NULL(object_bool_get(SPI(self) == SPI(self))));
				break;
			case op_inoteq:
				vector_push(self->value_stack, NON_NULL(object_bool_get(SPI(self) != SPI(self))));
				break;
			case op_igt:
				vector_push(self->value_stack, NON_NULL(object_bool_get(SPI(self) > SPI(self))));
				break;
			case op_ige:
				vector_push(self->value_stack, NON_NULL(object_bool_get(SPI(self) >= SPI(self))));
				break;
			case op_ilt:
			{
				object* a_ = vector_pop(self->value_stack);
				object* b_ = vector_pop(self->value_stack);
				vector_push(self->value_stack, NON_NULL(object_bool_get(OBJ2INT(a_) < OBJ2INT(b_))));
			}
				//vector_push(self->value_stack, object_bool_get(SPI(self) < SPI(self)));
				break;
			case op_ile:
				vector_push(self->value_stack, NON_NULL(object_bool_get(SPI(self) <= SPI(self))));
				break;
			case op_ilsh:
				vector_push(self->value_stack, NON_NULL(object_int_get(SPI(self) << SPI(self))));
				break;
			case op_irsh:
				vector_push(self->value_stack, NON_NULL(object_int_get(SPI(self) >> SPI(self))));
				break;
			case op_iexcor:
				vector_push(self->value_stack, NON_NULL(object_int_get(SPI(self) ^ SPI(self))));
				break;
			case op_iflip:
				vector_push(self->value_stack, NON_NULL(object_int_get(~SPI(self))));
				break;
			case op_ceq:
				vector_push(self->value_stack, NON_NULL(object_bool_get(SPC(self) == SPC(self))));
				break;
			case op_cnoteq:
				vector_push(self->value_stack, NON_NULL(object_bool_get(SPC(self) != SPC(self))));
				break;
			case op_cgt:
				vector_push(self->value_stack, NON_NULL(object_bool_get(SPC(self) > SPC(self))));
				break;
			case op_cge:
				vector_push(self->value_stack, NON_NULL(object_bool_get(SPC(self) >= SPC(self))));
				break;
			case op_clt:
				vector_push(self->value_stack, NON_NULL(object_bool_get(SPC(self) < SPC(self))));
				break;
			case op_cle:
				vector_push(self->value_stack, NON_NULL(object_bool_get(SPC(self) <= SPC(self))));
				break;
				//double & double
			case op_dadd:
				vector_push(self->value_stack, NON_NULL(object_double_new(SPD(self) + SPD(self))));
				break;
			case op_dsub:
				vector_push(self->value_stack, NON_NULL(object_double_new(SPD(self) - SPD(self))));
				break;
			case op_dmul:
				vector_push(self->value_stack, NON_NULL(object_double_new(SPD(self) * SPD(self))));
				break;
			case op_ddiv:
				vector_push(self->value_stack, NON_NULL(object_double_new(SPD(self) / SPD(self))));
				break;
			case op_dmod:
				vector_push(self->value_stack, NON_NULL(object_double_new((double)((int)SPD(self) % (int)SPD(self)))));
				break;
			case op_deq:
				vector_push(self->value_stack, NON_NULL(object_bool_get(SPD(self) == SPD(self))));
				break;
			case op_dnoteq:
				vector_push(self->value_stack, NON_NULL(object_bool_get(SPD(self) != SPD(self))));
				break;
			case op_dgt:
				vector_push(self->value_stack, NON_NULL(object_bool_get(SPD(self) > SPD(self))));
				break;
			case op_dge:
				vector_push(self->value_stack, NON_NULL(object_bool_get(SPD(self) >= SPD(self))));
				break;
			case op_dlt:
				vector_push(self->value_stack, NON_NULL(object_bool_get(SPD(self) < SPD(self))));
				break;
			case op_dle:
				vector_push(self->value_stack, NON_NULL(object_bool_get(SPD(self) <= SPD(self))));
				break;
			case op_ineg:
				vector_push(self->value_stack, NON_NULL(object_int_get(-SPI(self))));
				break;
			case op_dneg:
				vector_push(self->value_stack, NON_NULL(object_double_new(-SPD(self))));
				break;
			case op_bnot:
				vector_push(self->value_stack, NON_NULL(object_bool_get(!SPB(self))));
				break;
				//TODO:短絡評価していない
			case op_bbit_or:
				vector_push(self->value_stack, NON_NULL(object_bool_get(SPB(self) | SPB(self))));
				break;
			case op_blogic_or:
				vector_push(self->value_stack, NON_NULL(object_bool_get(SPB(self) || SPB(self))));
				break;
			case op_bbit_and:
				vector_push(self->value_stack,NON_NULL( object_bool_get(SPB(self) & SPB(self))));
				break;
			case op_blogic_and:
			{
				bool xa = SPB(self);
				bool xb = SPB(self);
				bool xx = xa && xb;
				vector_push(self->value_stack, NON_NULL(object_bool_get(xa && xb)));
				break;
			}
			case op_bexcor:
				vector_push(self->value_stack, NON_NULL(object_bool_get(SPB(self) ^ SPB(self))));
				break;
			case op_bflip:
				vector_push(self->value_stack, NON_NULL(object_bool_get(~SPB(self))));
				break;
				//push const
			case op_iconst:
			{
				int index = (int)enviroment_source_at(env, ++IDX);
				object* o = (object*)enviroment_constant_int_at(env, index);
				vector_push(self->value_stack, NON_NULL(o));
				break;
			}
			case op_dconst:
			{
				int index = (int)enviroment_source_at(env, ++IDX);
				object* d = enviroment_constant_double_at(env, index);
				vector_push(self->value_stack, NON_NULL(d));
				break;
			}
			case op_cconst:
			{
				int index = (int)enviroment_source_at(env, ++IDX);
				object* c = enviroment_constant_char_at(env, index);
				vector_push(self->value_stack, NON_NULL(c));
				break;
			}
			case op_sconst:
			{
				int index = (int)enviroment_source_at(env, ++IDX);
				object* cs = enviroment_constant_string_at(env, index);
				vector_push(self->value_stack, NON_NULL(cs));
				break;
			}
			case op_true:
			{
				vector_push(self->value_stack, object_get_true());
				break;
			}
			case op_false:
			{
				vector_push(self->value_stack, object_get_false());
				break;
			}
			case op_null:
			{
				vector_push(self->value_stack, object_get_null());
				break;
			}
			case op_return:
			{
				IDX = source_len;
				break;
			}
			case op_return_void:
			{
				IDX = source_len;
				break;
			}
			case op_throw:
			{
				//例外は呼び出し全てへ伝播
				object* e = (object*)vector_pop(self->value_stack);
				vm_throw(self, e);
				sg_thread* th = sg_thread_current();
				//空ならプログラムを終了
				if (vector_empty(th->trace_stack)) {
					vm_terminate(self);
					//どこかでキャッチしようとしている
				} else {
					vm_validate(self, source_len, &IDX);
				}
				break;
			}
			case op_try_enter:
			{
				sg_thread* th = sg_thread_current();
				vm_trace* trace = vm_trace_new(self);
				trace->pc = IDX; //goto
				vector_push(th->trace_stack, trace);
				//goto
				IDX++;
				//label
				IDX++;
				//これ以降は通常のステートメント...
				break;
			}
			case op_try_exit:
			{
				sg_thread* th = sg_thread_current();
				vm_trace* trace = (vm_trace*)vector_pop(th->trace_stack);
				vm_trace_delete(trace);
				break;
			}
			case op_try_clear:
			{
				sg_thread* th = sg_thread_current();
				vm_catch(self);
				vm_trace* trace = (vm_trace*)vector_pop(th->trace_stack);
				vm_trace_delete(trace);
				break;
			}
			case op_hexception:
			{
				vector_push(self->value_stack, NON_NULL(self->exception));
				break;
			}
			case op_instanceof:
			{
				generic_type* gtype = (generic_type*)vector_pop(self->type_args_vec);
				object* v = (object*)vector_pop(self->value_stack);
				//generic_type_print(gtype);
				//io_printfln("");
				//generic_type_print(v->gtype);
				//io_printfln("");
				int dist = generic_type_distance(gtype, v->gtype);
				object* b = object_bool_get(dist >= 0);
				vector_push(self->value_stack, b);
				break;
			}
			case op_dup:
				vector_push(self->value_stack, vector_top(self->value_stack));
				break;
			case op_pop:
				vector_pop(self->value_stack);
				break;
			case op_nop:
				/* no operation */
				break;
			case op_new_object:
			{
				//コンストラクタをさかのぼり、
				//トップレベルまで到達するとこの処理によって生成が行われます。
				//FIXME:???
				object* o = object_ref_new();
				assert(o->paint != paint_onexit);
				vector_push(self->value_stack, NON_NULL(o));
				//これを this とする
				vector_assign(self->ref_stack, 0, o);
				break;
			}
			case op_alloc_field:
			{
				int absClsIndex = (int)enviroment_source_at(env, ++IDX);
				type* tp = (type*)vector_at(ctx->type_vec, absClsIndex);
				class_* cls = TYPE2CLASS(tp);
				object* obj = (object*)vector_top(self->value_stack);
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
						generic_type_addargs(g, (generic_type*)vector_at(self->type_args_vec, i));
					}
					obj->gtype = g;
				}
				//フィールドの割り当て
				class_alloc_fields(cls, obj, self);
				assert(obj->gtype != NULL);
				break;
			}
			case op_new_instance:
			{
				//生成するクラスとコンストラクタを特定
				int absClsIndex = (int)enviroment_source_at(env, ++IDX);
				int constructorIndex = (int)enviroment_source_at(env, ++IDX);
				type* tp = (type*)vector_at(ctx->type_vec, absClsIndex);
				assert(tp->tag == type_class);
				class_* cls = TYPE2CLASS(tp);
				#if defined(DEBUG)
				const char* clsname = string_pool_ref2str(cls->namev);
				#endif
				constructor* ctor = (constructor*)vector_at(cls->constructor_list, constructorIndex);
				//新しいVMでコンストラクタを実行
				//また、現在のVMから実引数をポップ
				frame* sub = frame_sub(self);
				sub->receiver = tp;
				for (int i = 0; i < ctor->parameter_list->length; i++) {
					vector_item e = vector_pop(self->value_stack);
					object* o = (object*)e;
					vector_push(sub->value_stack, NON_NULL(e));
				}
				//コンストラクタに渡された型引数を引き継ぐ
				int typeparams = cls->type_parameter_list->length;
				for(int i=0; i<typeparams; i++) {
					vector_assign(sub->type_args_vec, (typeparams - i) - 1, vector_pop(self->type_args_vec));
				}
				//io_printi(self->level);
				//io_printfln("[ %s#new ]", type_name(ctor->parent));
				//enviroment_op_dump(ctor->env, sub->level);
				//opcode_buf_dump(ctor->env->buf, sub->level);
				vm_execute(sub, ctor->env);
				//コンストラクタを実行した場合、
				//objectがスタックのトップに残っているはず
				vector_item returnV = vector_top(sub->value_stack);
				object* returnO = (object*)returnV;
				vector_push(self->value_stack, NON_NULL(returnV));
				frame_delete(sub);
				break;
			}
			case op_chain_this:
			case op_chain_super:
			{
				int absClsIndex = (int)enviroment_source_at(env, ++IDX);
				int ctorIndex = (int)enviroment_source_at(env, ++IDX);
				type* tp = (type*)vector_at(ctx->type_vec, absClsIndex);
				assert(tp->tag == type_class);
				class_* cls = tp->u.class_;
				constructor* ctor = (constructor*)vector_at(cls->constructor_list, ctorIndex);
				//コンストラクタを実行するためのVMを作成
				frame* sub = frame_sub(self);
				sub->receiver = tp;
				//チェインコンストラクタに渡された実引数をプッシュ
				for (int i = 0; i < ctor->parameter_list->length; i++) {
					object* o = (object*)vector_pop(self->value_stack);
					vector_push(sub->value_stack, NON_NULL(o));
				}
				//		enviroment_op_dump(ctor->env, sub->level);
				//opcode_buf_dump(ctor->env->buf, sub->level);
				vm_execute(sub, ctor->env);
				//コンストラクタを実行した場合、
				//objectがスタックのトップに残っているはず
				vector_item returnV = vector_top(sub->value_stack);
				object* returnO = (object*)returnV;
				vector_assign(self->ref_stack, 0, returnV);
				vector_push(self->value_stack, NON_NULL(returnV));

				frame_delete(sub);
				//class_alloc_fields(cls, returnO);
				break;
			}
			case op_this:
			{
				vector_push(self->value_stack, vector_at(self->ref_stack, 0));
				break;
			}
			case op_super:
			{
				vector_push(self->value_stack, vector_at(self->ref_stack, 0));
				break;
			}
			//store,load
			case op_put_field:
			{
				object* assignValue = (object*)vector_pop(self->value_stack);
				object* assignTarget = (object*)vector_pop(self->value_stack);
				assert(assignTarget->tag == object_ref);
				int fieldIndex = (int)enviroment_source_at(env, ++IDX);
				vector_assign(assignTarget->u.field_vec, fieldIndex, assignValue);
				break;
			}

			case op_get_field:
			{
				object* sourceObject = (object*)vector_pop(self->value_stack);
				//assert(sourceObject->tag == object_ref);
				//int absClsIndex = (int)enviroment_source_at(env, ++i);
				int fieldIndex = (int)enviroment_source_at(env, ++IDX);
				object* val = (object*)vector_at(sourceObject->u.field_vec, fieldIndex);
				vector_push(self->value_stack, val);
				break;
			}

			case op_put_static:
			{
				int absClsIndex = (int)enviroment_source_at(env, ++IDX);
				int fieldIndex = (int)enviroment_source_at(env, ++IDX);
				type* tp = (type*)vector_at(ctx->type_vec, absClsIndex);
				class_* cls = tp->u.class_;
				field* f = class_get_sfield(cls, fieldIndex);
				object* sv = (object*)vector_pop(self->value_stack);
				f->static_value = sv;
				break;
			}

			case op_get_static:
			{
				int absClsIndex = (int)enviroment_source_at(env, ++IDX);
				int fieldIndex = (int)enviroment_source_at(env, ++IDX);
				type* cls = (type*)vector_at(ctx->type_vec, absClsIndex);
				field* f = class_get_sfield(cls->u.class_, fieldIndex);
				vector_push(self->value_stack, NON_NULL(f->static_value));
				break;
			}
			case op_put_property:
			{
				object* assignValue = (object*)vector_pop(self->value_stack);
				object* assignTarget = (object*)vector_pop(self->value_stack);
				assert(assignTarget->tag == object_ref);
				int propIndex = (int)enviroment_source_at(env, ++IDX);
				property* pro = class_get_property(TYPE2CLASS(GENERIC2TYPE(assignTarget->gtype)), propIndex);
				//プロパティを実行
				frame* sub = frame_sub(self);
				sub->receiver = pro->parent;
				vector_push(sub->value_stack, assignValue);
				vector_push(sub->value_stack, assignTarget);
				vm_execute(sub, pro->set->env);
				frame_delete(sub);
				break;
			}
			case op_get_property:
			{
				object* sourceObject = (object*)vector_pop(self->value_stack);
				int propIndex = (int)enviroment_source_at(env, ++IDX);
				property* pro = class_get_property(TYPE2CLASS(GENERIC2TYPE(sourceObject->gtype)), propIndex);
				//プロパティを実行
				frame* sub = frame_sub(self);
				sub->receiver = pro->parent;
				vector_push(sub->value_stack, sourceObject);
				vm_execute(sub, pro->get->env);
				//戻り値をスタックに残す
				vector_item returnV = vector_top(sub->value_stack);
				object* returnO = (object*)returnV;
				vector_assign(self->ref_stack, 0, returnV);
				vector_push(self->value_stack, returnV);
				frame_delete(sub);
				break;
			}
			case op_put_static_property:
			{
				object* sv = (object*)vector_pop(self->value_stack);
				int absClsIndex = (int)enviroment_source_at(env, ++IDX);
				int propIndex = (int)enviroment_source_at(env, ++IDX);
				type* tp = (type*)vector_at(ctx->type_vec, absClsIndex);
				class_* cls = tp->u.class_;
				property * p = class_get_sproperty(cls, propIndex);
				//プロパティを実行
				frame* sub = frame_sub(self);
				sub->receiver = NULL;
				vector_push(sub->value_stack, sv);
				vm_execute(sub, p->set->env);
				frame_delete(sub);
				break;
			}
			case op_get_static_property:
			{
				object* sv = (object*)vector_pop(self->value_stack);
				int absClsIndex = (int)enviroment_source_at(env, ++IDX);
				int propIndex = (int)enviroment_source_at(env, ++IDX);
				type* tp = (type*)vector_at(ctx->type_vec, absClsIndex);
				class_* cls = tp->u.class_;
				property * p = class_get_sproperty(cls, propIndex);
				//プロパティを実行
				frame* sub = frame_sub(self);
				sub->receiver = NULL;
				vm_execute(sub, p->get->env);
				//戻り値をスタックに残す
				vector_item returnV = vector_top(sub->value_stack);
				object* returnO = (object*)returnV;
				vector_assign(self->ref_stack, 0, returnV);
				vector_push(self->value_stack, returnV);
				frame_delete(sub);
				break;
			}
			case op_store:
			{
				int index = (int)enviroment_source_at(env, ++IDX);
				vector_item e = vector_pop(self->value_stack);
				object* o = (object*)e;
				assert(o != NULL);
				vector_assign(self->ref_stack, index, e);
				//INFO("store");
				break;
			}
			case op_load:
			{
				int index = (int)enviroment_source_at(env, ++IDX);
				vector_item e = vector_at(self->ref_stack, index);
				object*  o = (object*)e;
				assert(o != NULL);
				vector_push(self->value_stack, e);
				//INFO("load");
				break;
			}
			case op_inc:
			{
				object* o = vector_top(self->value_stack);
				object_inc(o);
				break;
			}
			case op_dec:
			{
				object* o = vector_top(self->value_stack);
				object_dec(o);
				break;
			}
			case op_copy:
			{
				object* o = vector_top(self->value_stack);
				vector_push(self->value_stack, object_copy(o));
				break;
			}
			case op_swap:
			{
				/*
				末尾の二つを入れ替える命令です。
				この命令は次のように実行されます。
				:
				|A|B|C|D|
				:
				first = D
				second = C
				|A|B|
				:
				|A|B|D|C|
				*/
				object* first = vector_pop(self->value_stack);
				object* second = vector_pop(self->value_stack);
				vector_push(self->value_stack, first);
				vector_push(self->value_stack, second);
				break;
			}
			//invoke
			case op_invokeinterface:
			{
				int absClassIndex = (int)enviroment_source_at(env, ++IDX);
				int methodIndex = (int)enviroment_source_at(env, ++IDX);
				type* tp = vector_at(ctx->type_vec, absClassIndex);
				object* o = (object*)vector_top(self->value_stack);
				method* m = class_get_impl_method(o->gtype->core_type->u.class_, tp, methodIndex);
				method_execute(m, self, env);
				break;
			}
			case op_invokestatic:
			{
				int absClassIndex = (int)enviroment_source_at(env, ++IDX);
				int methodIndex = (int)enviroment_source_at(env, ++IDX);
				type* cls = (type*)vector_at(ctx->type_vec, absClassIndex);
				method* m = class_get_smethod(cls->u.class_, methodIndex);
				#if defined(DEBUG)
				const char* clsname = string_pool_ref2str(type_name(cls));
				const char* mname = string_pool_ref2str(m->namev);
				#endif
				method_execute(m, self, env);
				break;
			}
			case op_invokevirtual:
			{
				int index = (int)enviroment_source_at(env, ++IDX);
				object* o = (object*)vector_top(self->value_stack);
				method* m = class_get_method(o, index);
				method_execute(m, self, env);
				break;
			}
			case op_invokespecial:
			{
				//privateメソッドには常にレシーバがいないはず
				//オブジェクトから直接型を取り出してしまうと具象すぎる
				int index = (int)enviroment_source_at(env, ++IDX);
				object* o = (object*)vector_top(self->value_stack);
				class_* cl = TYPE2CLASS(o->gtype->core_type);
				if(self->receiver != NULL) {
					cl = TYPE2CLASS(self->receiver);
				}
				method* m = (method*)vector_at(cl->method_list, index);
				method_execute(m, self, env);
				break;
			}
			case op_invokeoperator:
			{
				int index = (int)enviroment_source_at(env, ++IDX);
				object* o = (object*)vector_top(self->value_stack);
				class_* cl = TYPE2CLASS(o->gtype->core_type);
				operator_overload* operator_ov = (operator_overload*)vector_at(cl->operator_overload_list, index);
				operator_overload_execute(operator_ov, self, env);
				break;
			}
			case op_invokevirtual_lazy:
			{
				lazy_int* index = (lazy_int*)enviroment_source_at(env, ++IDX);
				object* o = (object*)vector_top(self->value_stack);
				method* m = class_get_method(o, index->value);
				method_execute(m, self, env);
				break;
			}
			case op_coro_init:
			{
				object* o = (object*)vector_at(self->ref_stack, 0);
				if(o->native_slot_vec == NULL) {
					o->native_slot_vec = vector_new();
				}
				int param_len = (int)enviroment_source_at(env, ++IDX);
				int op_len = (int)enviroment_source_at(env, ++IDX);
				yield_context* yctx = yield_context_new();
				yctx->yield_offset = 0;
				yctx->yield_count = 0;
				yctx->len = op_len;
				yctx->parameter_v = vector_new();
				//iterate(int, int) の int, int を受け取る
				yctx->sourceObject = vector_at(self->ref_stack, 1);
				#if defined(DEBUG)
				const char* yname = object_name(yctx->sourceObject);
				#endif
				for(int i=2; i<param_len + 1; i++) {
					object* a = vector_at(self->ref_stack, i);
					assert(a != NULL);
					vector_push(yctx->parameter_v, a);
				}
				//暗黙的に生成されるイテレータ実装クラスのコンストラクタは、
				//必ず最後に iterate() を定義したクラスのオブジェクトを受け取る。
				vector_push(o->native_slot_vec, yctx);
				o->is_coroutine = true;
				break;
			}
			case op_coro_next:
			{
				object* o = self->coroutine;
				object* ret = (object*)vector_pop(self->value_stack);
				assert(o->is_coroutine);
				yield_context* yctx = (yield_context*)vector_at(o->native_slot_vec, 0);
				//この実行コードが
				//前回からの再開によって開始した場合、それを元に戻す
				if(yctx->vm_ref_stack != NULL) {
					self->ref_stack = yctx->vm_ref_stack;
					self->value_stack = yctx->vm_value_stack;
				}
				assert(ret != NULL);
				yctx->stockObject = ret;
				//最初に実行された yield return に時点でコピーする
				if(yctx->vm_ref_stack == NULL) {
					yctx->backup_ref_stack = vector_clone(self->ref_stack);
					yctx->backup_value_stack = vector_new();
				}
				yctx->yield_offset = IDX + 1;
				yctx->yield_count++;
				IDX = source_len;
				//まだ実行できる?
				object* hasNext = object_bool_get(yctx->yield_offset < yctx->len);
				vector_push(self->value_stack, hasNext);
				break;
			}
			case op_coro_exit:
			{
				object* o = self->coroutine;
				assert(o->is_coroutine);
				yield_context* yctx = (yield_context*)vector_at(o->native_slot_vec, 0);
				IDX = source_len;
				yctx->yield_offset = source_len;
				if(yctx->vm_ref_stack != NULL) {
					self->ref_stack = yctx->vm_ref_stack;
					self->value_stack = yctx->vm_value_stack;
				}
				vector_push(self->value_stack, object_get_false());
				break;
			}
			case op_coro_resume:
			{
				object* o = self->coroutine;
				assert(o->is_coroutine);
				yield_context* yctx = (yield_context*)vector_at(o->native_slot_vec, 0);
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
			case op_coro_current:
			{
				object* o = self->coroutine;
				assert(o->is_coroutine);
				yield_context* yctx = (yield_context*)vector_at(o->native_slot_vec, 0);
				vector_push(self->value_stack, yctx->stockObject);
				break;
			}
			case op_coro_swap_self:
			{
				assert(self->coroutine == NULL);
				object* o = (object*)vector_at(self->ref_stack, 0);
				assert(o->is_coroutine);
				yield_context* yctx = vector_at(o->native_slot_vec, 0);
				if(yctx->cached) {
					self->coroutine = o;
					break;
				}
				#if defined(DEBUG)
				const char* oname = object_name(o);
				const char* yname = object_name(yctx->sourceObject);
				#endif
				//[0] = Array
				//[1] = ArrayIterator
				vector_assign(self->ref_stack, 0, yctx->sourceObject);
				assert(yctx->sourceObject != NULL);
				for(int i=0; i<yctx->parameter_v->length; i++) {
					object* e = vector_at(yctx->parameter_v, i);
					assert(e != NULL);
					vector_assign(self->ref_stack, i + 1, e);
				}
				self->coroutine = o;
				yctx->cached = true;
				break;
			}
			case op_generic_add:
			{
				//TODO:ここで親フレームを遡るように
				//ジェネリックタイプを作成する
				int depth = 0;
				int pos = IDX;
				vector* stack = vector_new();
				vector* counts = vector_new();
				generic_type* ret = NULL;
				while(1) {
					int code = (int)enviroment_source_at(env, ++IDX);
					if(code == op_generic_enter) {
						int count = (int)enviroment_source_at(env, ++IDX);
						depth++;
						vector_push(counts, count);
						//vector_push(stack, generic_type_new(NULL));
					} else if(code == op_generic_exit) {
						depth--;
						int count = (int)vector_pop(counts);
						generic_type* head = vector_at(stack, 0);
						for(int i=0; i<count; i++) {
							generic_type_addargs(head, (generic_type*)vector_pop(stack));
						}
						if(depth == 0) {
							assert(stack->length == 1);
							ret = head;
							break;
						}
					} else if(code == op_generic_unique_type ||
					          code == op_generic_instance_type ||
							  code == op_generic_static_type) {
						assert(depth > 0);
						int arg = (int)enviroment_source_at(env, ++IDX);
						generic_type* a = NULL;
						if(code == op_generic_unique_type) {
							a = generic_type_new((type*)vector_at(ctx->type_vec, arg));
						} else if(code == op_generic_instance_type) {
							object* receiver = (object*)vector_at(self->ref_stack, 0);
							a = (generic_type*)vector_at(receiver->gtype->type_args_list, arg);
						} else if(code == op_generic_static_type) {
							a = (generic_type*)vector_at(self->type_args_vec, arg);
						}
						vector_push(stack, a);
					}
				}
				assert(ret != NULL);
				vector_push(self->type_args_vec, ret);
				vector_delete(stack, vector_deleter_null);
				vector_delete(counts, vector_deleter_null);
				break;
			}
			case op_generic_enter:
			case op_generic_unique_type:
			case op_generic_instance_type:
			case op_generic_static_type:
			case op_generic_exit:
				assert(false);
				break;
			//defer
			case op_defer_enter:
			{
				break;
			}
			case op_defer_exit:
			{
				if(pos == deferStart) {
					IDX = source_len;
				}
				break;
			}
			case op_defer_register:
			{
				label* offset = (label*)enviroment_source_at(env, ++IDX);
				vector* bind = vector_clone(self->ref_stack);
				defer_context* defctx = defer_context_new();
				defctx->offset = offset;
				defctx->bind = bind;
				vector_push(self->defer_vec, defctx);
				break;
			}
			case op_breakpoint:
			{
				break;
			}

			//goto
			case op_goto:
			{
				label* l = (label*)enviroment_source_at(env, ++IDX);
				IDX = l->cursor;
				break;
			}

			case op_goto_if_true:
			{
				bool v = SPB(self);
				label* l = (label*)enviroment_source_at(env, ++IDX);
				if (v) {
					IDX = l->cursor;
				}
				break;
			}

			case op_goto_if_false:
			{
				bool v = SPB(self);
				label* l = (label*)enviroment_source_at(env, ++IDX);
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
		if (self->terminate) {
			vm_uncaught(self, env, IDX);
			break;
		}
	}
}

static int stack_topi(frame* self) {
	object* ret = (object*)vector_top(self->value_stack);
	assert(ret->tag == object_int);
	return ret->u.int_;
}

static double stack_topd(frame* self) {
	object* ret = (object*)vector_top(self->value_stack);
	assert(ret->tag == object_double);
	return ret->u.double_;
}

static char stack_topc(frame* self) {
	object* ret = (object*)vector_top(self->value_stack);
	assert(ret->tag == object_char);
	return ret->u.char_;
}

static char* stack_tops(frame* self) {
	object* ret = (object*)vector_top(self->value_stack);
	assert(ret->tag == object_string);
	return bc_string_raw(ret)->text;
}

static bool stack_topb(frame* self) {
	object* ret = (object*)vector_top(self->value_stack);
	assert(ret->tag == object_bool);
	return ret->u.bool_;
}


static int stack_popi(frame* self) {
	object* ret = (object*)vector_pop(self->value_stack);
	assert(ret->tag == object_int);
	return ret->u.int_;
}

static double stack_popd(frame* self) {
	object* ret = (object*)vector_pop(self->value_stack);
	assert(ret->tag == object_double);
	return ret->u.double_;
}

static char stack_popc(frame* self) {
	object* ret = (object*)vector_pop(self->value_stack);
	assert(ret->tag == object_char);
	return ret->u.char_;
}

static char* stack_pops(frame* self) {
	object* ret = (object*)vector_pop(self->value_stack);
	assert(ret->tag == object_string);
	return bc_string_raw(ret)->text;
}

static bool stack_popb(frame* self) {
	object* ret = (object*)vector_pop(self->value_stack);
	assert(ret->tag == object_bool);
	return ret->u.bool_;
}

static void vm_delete_defctx(vector_item e) {
	defer_context* defctx = (defer_context*)e;
	defer_context_delete(defctx);
}