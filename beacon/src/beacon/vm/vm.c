#include "vm.h"
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
#include "../thread/thread.h"
#include "../util/mem.h"
#include "../util/xassert.h"
#include "../util/string_buffer.h"
#include "../util/vector.h"
#include "../util/text.h"
#include "../lib/beacon/lang/bc_string.h"
#include "line_range.h"
#include "../env/heap.h"
#include "../env/generic_type.h"
//proto
static void vm_run(vm * self, enviroment * env, int pos, int deferStart);
static int stack_topi(vm* self);
static double stack_topd(vm* self);
static char stack_topc(vm* self);
static char* stack_tops(vm* self);
static bool stack_topb(vm* self);

static int stack_popi(vm* self);
static double stack_popd(vm* self);
static char stack_popc(vm* self);
static char* stack_pops(vm* self);
static bool stack_popb(vm* self);
static void remove_from_parent(vm* self);
static void vm_markStatic(field* item);
static void vm_markallImpl(vm* self);

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


vm * vm_new() {
	vm* ret = (vm*)MEM_MALLOC(sizeof(vm));
	ret->value_stack = vector_new();
	ret->ref_stack = vector_new();
	ret->parent = NULL;
	ret->level = 0;
	ret->terminate = false;
	ret->validate = false;
	ret->native_throw_pos = -1;
	ret->exception = NULL;
	ret->children_vec = vector_new();
	ret->defer_at = 0;
	ret->defer_vec = vector_new();
	return ret;
}

vm * vm_sub(vm * parent) {
	vm* ret = vm_new();
	ret->parent = parent;
	ret->level = parent->level + 1;
	ret->context_ref = parent->context_ref;

	vector_push(parent->children_vec, ret);
	return ret;
}

void vm_execute(vm* self, enviroment* env) {
	vm_resume(self, env, 0);
}

void vm_resume(vm * self, enviroment * env, int pos) {
	vm_run(self, env, pos, -1);
	while(self->defer_vec->length > 0) {
		label* e = (label*)vector_pop(self->defer_vec);
		vm_run(self, env, e->cursor, e->cursor);
	}
	vector_clear(self->defer_vec);
}

void vm_native_throw(vm * self, object * exc) {
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

void vm_throw(vm * self, object * exc) {
	vm* temp = self;
	do {
		temp->exception = exc;
		temp = temp->parent;
	} while (temp != NULL);
}

void vm_catch(vm * self) {
	if (self == NULL) {
		return;
	}
	for (int i = 0; i < self->children_vec->length; i++) {
		vm* e = (vm*)vector_at(self->children_vec, i);
		vm_catch(e);
	}
	self->exception = NULL;
}

bool vm_validate(vm* self, int source_len, int* pcDest) {
	sg_thread* th = sg_thread_current();
	vm_trace* trace = (vm_trace*)vector_top(th->trace_stack);
	//ここなので catch節 へ向かう
	if (trace->v == self) {
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
		self->parent->validate = true;
		*pcDest = source_len;
		return false;
	}
}

void vm_terminate(vm * self) {
	vm* temp = self;
	do {
		temp->terminate = true;
		temp = temp->parent;
	} while (temp != NULL);
}

void vm_uncaught(vm * self, enviroment* env, int pc) {
	line_range* lr = line_range_find(env->line_rangeVec, pc);
	int line = -1;
	if (lr != NULL) {
		line = lr->lineno;
	}
	//例外のメッセージを取得
	type* tp = namespace_get_type(namespace_lang(), "Exception");
	int temp = -1;
	class_find_field(tp->u.class_, "message", &temp);
	object* ex = self->exception;
	object* msg = vector_at(ex->u.field_vec, temp);
	string_buffer* cstr = vector_at(msg->native_slot_vec, 0);

	text_printf("file: %s <%d>", env->context_ref->filename, line);
	text_printf("\n");
	text_printf("%s", cstr->text);
	text_printf("\n");
}

void vm_markall(vm * self) {
	//全ての静的フィールドをマークする
	script_context* ctx = script_context_get_current();
	script_context_static_each(ctx, vm_markStatic);
	//全ての子要素を巡回してマーキング
	vm_markallImpl(self);
}

void vm_delete(vm * self) {

	remove_from_parent(self);
	vector_clear(self->value_stack);
	vector_clear(self->ref_stack);

	heap_gc(heap_get());

	//constant_pool_delete(self->pool);
	//operand_stack_delete(self->operand_stack);
	vector_delete(self->value_stack, vector_deleter_null);
	vector_delete(self->ref_stack, vector_deleter_null);
	vector_delete(self->children_vec, vector_deleter_null);
	MEM_FREE(self);
}

//private
static void vm_run(vm * self, enviroment * env, int pos, int deferStart) {
	script_context* ctx = script_context_get_current();
	int source_len = env->buf->source->length;
	self->context_ref = env;
	for (int i = pos; i < source_len; i++) {
		//このVMの子要素で例外がスローされ、
		//それを子要素自身で処理できなかった場合には、
		//自分で処理を試みます。
		if (self->validate) {
			if (!vm_validate(self, source_len, &i)) {
				break;
			}
		}
		self->pc = i;
		opcode b = (opcode)enviroment_source_at(env, i);
		switch (b) {
			//int & int
			case op_iadd:
				vector_push(self->value_stack, object_int_new(SPI(self) + SPI(self)));
				break;
			case op_isub:
				vector_push(self->value_stack, object_int_new(SPI(self) - SPI(self)));
				break;
			case op_imul:
				vector_push(self->value_stack, object_int_new(SPI(self) * SPI(self)));
				break;
			case op_idiv:
				vector_push(self->value_stack, object_int_new(SPI(self) / SPI(self)));
				break;
			case op_imod:
				vector_push(self->value_stack, object_int_new(SPI(self) % SPI(self)));
				break;
			case op_ibit_or:
				vector_push(self->value_stack, object_int_new(SPI(self) | SPI(self)));
				break;
			case op_ilogic_or:
				vector_push(self->value_stack, object_int_new(SPI(self) || SPI(self)));
				break;
			case op_ibit_and:
				vector_push(self->value_stack, object_int_new(SPI(self) & SPI(self)));
				break;
			case op_ilogic_and:
				vector_push(self->value_stack, object_int_new(SPI(self) && SPI(self)));
				break;
			case op_ieq:
				vector_push(self->value_stack, object_bool_get(SPI(self) == SPI(self)));
				break;
			case op_inoteq:
				vector_push(self->value_stack, object_bool_get(SPI(self) != SPI(self)));
				break;
			case op_igt:
				vector_push(self->value_stack, object_bool_get(SPI(self) > SPI(self)));
				break;
			case op_ige:
				vector_push(self->value_stack, object_bool_get(SPI(self) >= SPI(self)));
				break;
			case op_ilt:
				vector_push(self->value_stack, object_bool_get(SPI(self) < SPI(self)));
				break;
			case op_ile:
				vector_push(self->value_stack, object_bool_get(SPI(self) <= SPI(self)));
				break;
				//double & double
			case op_dadd:
				vector_push(self->value_stack, object_double_new(SPD(self) + SPD(self)));
				break;
			case op_dsub:
				vector_push(self->value_stack, object_double_new(SPD(self) - SPD(self)));
				break;
			case op_dmul:
				vector_push(self->value_stack, object_double_new(SPD(self) * SPD(self)));
				break;
			case op_ddiv:
				vector_push(self->value_stack, object_double_new(SPD(self) / SPD(self)));
				break;
			case op_dmod:
				vector_push(self->value_stack, object_double_new((double)((int)SPD(self) % (int)SPD(self))));
				break;
			case op_deq:
				vector_push(self->value_stack, object_bool_get(SPD(self) == SPD(self)));
				break;
			case op_dnoteq:
				vector_push(self->value_stack, object_bool_get(SPD(self) != SPD(self)));
				break;
			case op_dgt:
				vector_push(self->value_stack, object_bool_get(SPD(self) > SPD(self)));
				break;
			case op_dge:
				vector_push(self->value_stack, object_bool_get(SPD(self) >= SPD(self)));
				break;
			case op_dlt:
				vector_push(self->value_stack, object_bool_get(SPD(self) < SPD(self)));
				break;
			case op_dle:
				vector_push(self->value_stack, object_bool_get(SPD(self) <= SPD(self)));
				break;
			case op_ineg:
				vector_push(self->value_stack, object_int_new(-SPI(self)));
				break;
			case op_dneg:
				vector_push(self->value_stack, object_double_new(-SPD(self)));
				break;
			case op_bnot:
				vector_push(self->value_stack, object_bool_get(!SPB(self)));
				break;
				//TODO:短絡評価していない
			case op_bbit_or:
				vector_push(self->value_stack, object_bool_get(SPB(self) | SPB(self)));
				break;
			case op_blogic_or:
				vector_push(self->value_stack, object_bool_get(SPB(self) || SPB(self)));
				break;
			case op_bbit_and:
				vector_push(self->value_stack, object_bool_get(SPB(self) & SPB(self)));
				break;
			case op_blogic_and:
				vector_push(self->value_stack, object_bool_get(SPB(self) && SPB(self)));
				break;
				//push const
			case op_iconst:
			{
				int index = (int)enviroment_source_at(env, ++i);
				object* o = (object*)enviroment_constant_int_at(env, index);
				vector_push(self->value_stack, o);
				break;
			}
			case op_dconst:
			{
				int index = (int)enviroment_source_at(env, ++i);
				object* d = enviroment_constant_double_at(env, index);
				vector_push(self->value_stack, d);
				break;
			}
			case op_cconst:
			{
				int index = (int)enviroment_source_at(env, ++i);
				object* c = enviroment_constant_char_at(env, index);
				vector_push(self->value_stack, c);
				break;
			}
			case op_sconst:
			{
				int index = (int)enviroment_source_at(env, ++i);
				object* cs = enviroment_constant_string_at(env, index);
				vector_push(self->value_stack, cs);
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
				i = source_len;
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
					vm_validate(self, source_len, &i);
				}
				break;
			}
			case op_try_enter:
			{
				sg_thread* th = sg_thread_current();
				vm_trace* trace = vm_trace_new(self);
				trace->pc = i; //goto
				vector_push(th->trace_stack, trace);
				//goto
				i++;
				//label
				i++;
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
				vector_push(self->value_stack, self->exception);
				break;
			}
			case op_instanceof:
			{
				int absClsIndex = (int)enviroment_source_at(env, ++i);
				type* tp = (type*)vector_at(ctx->type_vec, absClsIndex);
				object* v = (object*)vector_pop(self->value_stack);
				int dist = type_distance(v->gtype->core_type, tp);
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
				object* o = object_ref_new();
				vector_push(self->value_stack, o);
				//これを this とする
				vector_assign(self->ref_stack, 0, o);
				break;
			}
			case op_alloc_field:
			{
				int absClsIndex = (int)enviroment_source_at(env, ++i);
				type* cls = (type*)vector_at(ctx->type_vec, absClsIndex);
				object* obj = (object*)vector_top(self->value_stack);
				class_alloc_fields(cls->u.class_, obj);
				break;
			}
			case op_new_instance:
			{
				//生成するクラスとコンストラクタを特定
				int absClsIndex = (int)enviroment_source_at(env, ++i);
				int constructorIndex = (int)enviroment_source_at(env, ++i);
				type* tp = (type*)vector_at(ctx->type_vec, absClsIndex);
				assert(tp->tag == type_class);
				class_* cls = tp->u.class_;
				constructor* ctor = (constructor*)vector_at(cls->constructor_list, constructorIndex);
				//新しいVMでコンストラクタを実行
				//また、現在のVMから実引数をポップ
				vm* sub = vm_sub(self);
				for (int i = 0; i < ctor->parameter_list->length; i++) {
					vector_item e = vector_pop(self->value_stack);
					object* o = (object*)e;
					vector_push(sub->value_stack, e);
				}
				text_putindent(self->level);
				//text_printfln("[ %s#new ]", type_name(ctor->parent));
				//enviroment_op_dump(ctor->env, sub->level);
				opcode_buf_dump(ctor->env->buf, sub->level);
				vm_execute(sub, ctor->env);
				//コンストラクタを実行した場合、
				//objectがスタックのトップに残っているはず
				vector_item returnV = vector_top(sub->value_stack);
				object* returnO = (object*)returnV;
				vector_push(self->value_stack, returnV);
				vm_delete(sub);
				break;
			}
			case op_chain_this:
			case op_chain_super:
			{
				int absClsIndex = (int)enviroment_source_at(env, ++i);
				int ctorIndex = (int)enviroment_source_at(env, ++i);
				type* tp = (type*)vector_at(ctx->type_vec, absClsIndex);
				assert(tp->tag == type_class);
				class_* cls = tp->u.class_;
				constructor* ctor = (constructor*)vector_at(cls->constructor_list, ctorIndex);
				//コンストラクタを実行するためのVMを作成
				vm* sub = vm_sub(self);
				//チェインコンストラクタに渡された実引数をプッシュ
				for (int i = 0; i < ctor->parameter_list->length; i++) {
					object* o = (object*)vector_pop(self->value_stack);
					vector_push(sub->value_stack, o);
				}
				//		enviroment_op_dump(ctor->env, sub->level);
				opcode_buf_dump(ctor->env->buf, sub->level);
				vm_execute(sub, ctor->env);
				//コンストラクタを実行した場合、
				//objectがスタックのトップに残っているはず
				vector_item returnV = vector_top(sub->value_stack);
				object* returnO = (object*)returnV;
				vector_assign(self->ref_stack, 0, returnV);
				vector_push(self->value_stack, returnV);

				vm_delete(sub);
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
				int fieldIndex = (int)enviroment_source_at(env, ++i);
				vector_assign(assignTarget->u.field_vec, fieldIndex, assignValue);
				break;
			}

			case op_get_field:
			{
				object* sourceObject = (object*)vector_pop(self->value_stack);
				//assert(sourceObject->tag == object_ref);
				//int absClsIndex = (int)enviroment_source_at(env, ++i);
				int fieldIndex = (int)enviroment_source_at(env, ++i);
				object* val = (object*)vector_at(sourceObject->u.field_vec, fieldIndex);
				vector_push(self->value_stack, val);
				break;
			}

			case op_put_static:
			{
				int absClsIndex = (int)enviroment_source_at(env, ++i);
				int fieldIndex = (int)enviroment_source_at(env, ++i);
				type* tp = (type*)vector_at(ctx->type_vec, absClsIndex);
				class_* cls = tp->u.class_;
				field* f = class_get_sfield(cls, fieldIndex);
				object* sv = (object*)vector_pop(self->value_stack);
				f->static_value = sv;
				break;
			}

			case op_get_static:
			{
				int absClsIndex = (int)enviroment_source_at(env, ++i);
				int fieldIndex = (int)enviroment_source_at(env, ++i);
				type* cls = (type*)vector_at(ctx->type_vec, absClsIndex);
				field* f = class_get_sfield(cls->u.class_, fieldIndex);
				vector_push(self->value_stack, f->static_value);
				break;
			}
			case op_store:
			{
				int index = (int)enviroment_source_at(env, ++i);
				vector_item e = vector_pop(self->value_stack);
				object* o = (object*)e;
				vector_assign(self->ref_stack, index, e);
				//INFO("store");
				break;
			}
			case op_load:
			{
				//XBREAK(i == 7);
				int index = (int)enviroment_source_at(env, ++i);
				vector_item e = vector_at(self->ref_stack, index);
				object*  o = (object*)e;
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
				int absClassIndex = (int)enviroment_source_at(env, ++i);
				int methodIndex = (int)enviroment_source_at(env, ++i);
				type* tp = vector_at(ctx->type_vec, absClassIndex);
				object* o = (object*)vector_top(self->value_stack);
				method* m = class_get_impl_method(o->gtype->core_type->u.class_, tp, methodIndex);
				method_execute(m, self, env);
				break;
			}
			case op_invokestatic:
			{
				int absClassIndex = (int)enviroment_source_at(env, ++i);
				int methodIndex = (int)enviroment_source_at(env, ++i);
				type* cls = (type*)vector_at(ctx->type_vec, absClassIndex);
				//method* m = (method*)vector_at(cls->vt->elements, methodIndex);
				method* m = class_get_smethod(cls->u.class_, methodIndex);
				//いらない
				//	opcode code = (opcode)enviroment_source_at(env, ++i);
				//	assert(code == op_invokestatic);
				method_execute(m, self, env);
				break;
				//break;
			}
			case op_invokevirtual:
			{
				int index = (int)enviroment_source_at(env, ++i);
				object* o = (object*)vector_top(self->value_stack);
				method* m = class_get_method(o, index);
				method_execute(m, self, env);
				break;
			}
			case op_invokespecial:
			{
				int index = (int)enviroment_source_at(env, ++i);
				object* o = (object*)vector_top(self->value_stack);
				class_* cl = TYPE2CLASS(o->gtype->core_type);
				method* m = (method*)vector_at(cl->method_list, index);
				method_execute(m, self, env);
				break;
			}
			//defer
			case op_defer_enter:
			{
				break;
			}
			case op_defer_exit:
			{
				if(pos == deferStart) {
					i = source_len;
				}
				break;
			}
			case op_defer_register:
			{
				label* l = (label*)enviroment_source_at(env, ++i);
				vector_push(self->defer_vec, l);
				break;
			}
			//debug
			case op_printi:
			{
				int i = SPI(self);
				text_printf("int: %d\n", i);
				break;
			}

			case op_printd:
			{
				double d = SPD(self);
				text_printf("double: %f\n", d);
				break;
			}

			case op_prints:
			{
				char* s = SPS(self);
				text_printf("string: %s\n", s);
				break;
			}
			case op_breakpoint:
			{
				break;
			}

			//goto
			case op_goto:
			{
				label* l = (label*)enviroment_source_at(env, ++i);
				i = l->cursor;
				break;
			}

			case op_goto_if_true:
			{
				bool v = SPB(self);
				label* l = (label*)enviroment_source_at(env, ++i);
				if (v) {
					i = l->cursor;
				}
				break;
			}

			case op_goto_if_false:
			{
				bool v = SPB(self);
				label* l = (label*)enviroment_source_at(env, ++i);
				int a = l->cursor;
				if (!v) {
					i = l->cursor;
				}
				break;
			}

			default:
				break;
		}
		//ネイティブメソッドからスローされた例外を検出
		if (self->native_throw_pos != -1) {
			i = self->native_throw_pos;
			self->native_throw_pos = -1;
		}
		//キャッチされなかった例外によって終了する
		if (self->terminate) {
			vm_uncaught(self, env, i);
			break;
		}
	}
}

static int stack_topi(vm* self) {
	object* ret = (object*)vector_top(self->value_stack);
	assert(ret->tag == object_int);
	return ret->u.int_;
}

static double stack_topd(vm* self) {
	object* ret = (object*)vector_top(self->value_stack);
	assert(ret->tag == object_double);
	return ret->u.double_;
}

static char stack_topc(vm* self) {
	object* ret = (object*)vector_top(self->value_stack);
	assert(ret->tag == object_char);
	return ret->u.char_;
}

static char* stack_tops(vm* self) {
	object* ret = (object*)vector_top(self->value_stack);
	assert(ret->tag == object_string);
	return bc_string_raw(ret)->text;
}

static bool stack_topb(vm* self) {
	object* ret = (object*)vector_top(self->value_stack);
	assert(ret->tag == object_bool);
	return ret->u.bool_;
}


static int stack_popi(vm* self) {
	object* ret = (object*)vector_pop(self->value_stack);
	assert(ret->tag == object_int);
	return ret->u.int_;
}

static double stack_popd(vm* self) {
	object* ret = (object*)vector_pop(self->value_stack);
	assert(ret->tag == object_double);
	return ret->u.double_;
}

static char stack_popc(vm* self) {
	object* ret = (object*)vector_pop(self->value_stack);
	assert(ret->tag == object_char);
	return ret->u.char_;
}

static char* stack_pops(vm* self) {
	object* ret = (object*)vector_pop(self->value_stack);
	assert(ret->tag == object_string);
	return bc_string_raw(ret)->text;
}

static bool stack_popb(vm* self) {
	object* ret = (object*)vector_pop(self->value_stack);
	assert(ret->tag == object_bool);
	return ret->u.bool_;
}

static void remove_from_parent(vm* self) {
	if (self->parent != NULL) {
		int idx = vector_find(self->parent->children_vec, self);
		vector_remove(self->parent->children_vec, idx);
	}
}

static void vm_markStatic(field* item) {
	object_markall(item->static_value);
}

static void vm_markallImpl(vm* self) {
	for (int i = 0; i < self->children_vec->length; i++) {
		vm* e = (vm*)vector_at(self->children_vec, i);
		vm_markallImpl(e);
	}
	for (int i = 0; i < self->value_stack->length; i++) {
		object* e = (object*)vector_at(self->value_stack, i);
		object_markall(e);
	}
	for (int i = 0; i < self->ref_stack->length; i++) {
		object* e = (object*)vector_at(self->ref_stack, i);
		object_markall(e);
	}
	//例外をマークする
	object_markall(self->exception);
}