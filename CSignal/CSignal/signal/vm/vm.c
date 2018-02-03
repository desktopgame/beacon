#include "vm.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "label.h"
#include "vm_trace.h"
#include "../env/type_interface.h"
#include "../env/type_impl.h"
#include "../env/field.h"
#include "../env/method.h"
#include "../env/object.h"
#include "../env/constructor.h"
#include "../env/script_context.h"
#include "../thread/thread.h"
#include "../util/logger.h"
#include "../util/mem.h"
#include "../util/vector.h"
#include "../util/text.h"
//proto
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
	return ret;
}

vm * vm_sub(vm * parent) {
	vm* ret = vm_new();
	ret->parent = parent;
	ret->level = parent->level + 1;
	return ret;
}

void vm_execute(vm* self, enviroment* env) {
	script_context* ctx = script_context_get_current();
	int source_len = env->buf->source->length;
	for (int i = 0; i < source_len; i++) {
		//このVMの子要素で例外がスローされ、
		//それを子要素自身で処理できなかった場合には、
		//自分で処理を試みます。
		if (self->validate) {
			if (!vm_validate(self, source_len, &i)) {
				break;
			}
		}
		op_byte b = (op_byte)enviroment_source_at(env, i);
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
				vector_push(self->value_stack, object_bool_new(SPI(self) == SPI(self)));
				break;
			case op_inoteq:
				vector_push(self->value_stack, object_bool_new(SPI(self) != SPI(self)));
				break;
			case op_igt:
				vector_push(self->value_stack, object_bool_new(SPI(self) > SPI(self)));
				break;
			case op_ige:
				vector_push(self->value_stack, object_bool_new(SPI(self) >= SPI(self)));
				break;
			case op_ilt:
				vector_push(self->value_stack, object_bool_new(SPI(self) < SPI(self)));
				break;
			case op_ile:
				vector_push(self->value_stack, object_bool_new(SPI(self) <= SPI(self)));
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
				vector_push(self->value_stack, object_bool_new(SPD(self) == SPD(self)));
				break;
			case op_dnoteq:
				vector_push(self->value_stack, object_bool_new(SPD(self) != SPD(self)));
				break;
			case op_dgt:
				vector_push(self->value_stack, object_bool_new(SPD(self) > SPD(self)));
				break;
			case op_dge:
				vector_push(self->value_stack, object_bool_new(SPD(self) >= SPD(self)));
				break;
			case op_dlt:
				vector_push(self->value_stack, object_bool_new(SPD(self) < SPD(self)));
				break;
			case op_dle:
				vector_push(self->value_stack, object_bool_new(SPD(self) <= SPD(self)));
				break;
			case op_ineg:
				vector_push(self->value_stack, object_int_new(-SPI(self)));
				break;
			case op_dneg:
				vector_push(self->value_stack, object_double_new(-SPD(self)));
				break;
			case op_bnot:
				vector_push(self->value_stack, object_bool_new(!SPB(self)));
				break;
			//push const
			case op_consti:
			{
				int index = (int)enviroment_source_at(env, ++i);
				object* o = (object*)enviroment_constant_int_at(env, index);
				vector_push(self->value_stack, o);
				break;
			}
			case op_constd:
			{
				int index = (int)enviroment_source_at(env, ++i);
				object* d = enviroment_constant_double_at(env, index);
				vector_push(self->value_stack, d);
				break;
			}
			case op_constc:
			{
				int index = (int)enviroment_source_at(env, ++i);
				object* c = enviroment_constant_char_at(env, index);
				vector_push(self->value_stack, c);
				break;
			}
			case op_consts:
			{
				int index = (int)enviroment_source_at(env, ++i);
				object* cs = enviroment_constant_string_at(env, index);
				vector_push(self->value_stack, cs);
				break;
			}
			case op_true:
			{
				vector_push(self->value_stack, object_true());
				break;
			}
			case op_false:
			{
				vector_push(self->value_stack, object_false());
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
				if (stack_empty(th->trace_stack)) {
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
				stack_push(th->trace_stack, trace);
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
				vm_trace* trace = (vm_trace*)stack_pop(th->trace_stack);
				vm_trace_delete(trace);
				break;
			}
			case op_try_clear:
			{
				sg_thread* th = sg_thread_current();
				vm_catch(self);
				vm_trace* trace = (vm_trace*)stack_pop(th->trace_stack);
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
				int dist = type_distance(v->type, tp);
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
				opcode_buf_dump(ctor->env->buf, sub->level);
				vm_execute(sub, ctor->env);
				//コンストラクタを実行した場合、
				//objectがスタックのトップに残っているはず
				vector_item returnV = vector_top(sub->value_stack);
				object* returnO = (object*)returnV;
				vector_push(self->value_stack, returnV);
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
				opcode_buf_dump(ctor->env->buf, sub->level);
				vm_execute(sub, ctor->env);
				vm_delete(sub);
				//コンストラクタを実行した場合、
				//objectがスタックのトップに残っているはず
				vector_item returnV = vector_top(sub->value_stack);
				object* returnO = (object*)returnV;
				vector_assign(self->ref_stack, 0, returnV);
				vector_push(self->value_stack, returnV);
				//class_alloc_fields(cls, returnO);
				break;
			}
			case op_this:
			{
				vector_push(self->value_stack,vector_at(self->ref_stack,0));
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
				assert(assignTarget->type == object_ref);
				int fieldIndex = (int)enviroment_source_at(env, ++i);
				vector_assign(assignTarget->u.field_vec, fieldIndex, assignValue);
				break;
			}

			case op_get_field:
			{
				object* sourceObject = (object*)vector_pop(self->value_stack);
				assert(sourceObject->type == object_ref);
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
				f->static_value = (object*)vector_pop(self->value_stack);
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
				INFO("store");
				break;
			}
			case op_load:
			{
				int index = (int)enviroment_source_at(env, ++i);
				vector_item e = vector_at(self->ref_stack, index);
				object*  o = (object*)e;
				vector_push(self->value_stack, e);
				INFO("load");
				break;
			}
			//invoke
			case op_lookup:
			{
				int absClsIndex = (int)enviroment_source_at(env, ++i);
				object* o = (object*)vector_top(self->value_stack);
				type* tp = (type*)vector_at(ctx->type_vec, absClsIndex);
				o->vptr = vtable_lookup(o->vptr, type_vtable(tp));
				break;
			}
			case op_invokeinterface:
			{
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
				break;
			}
			case op_invokevirtual:
			case op_invokespecial:
			{
				int index = (int)enviroment_source_at(env, ++i);
			//	opcode code = (opcode)enviroment_source_at(env, ++i);
				object* o = (object*)vector_top(self->value_stack);
				//method* m = (method*)vector_at(o->vptr->elements, index);
				method* m = class_get_method(o, index);
			//	assert(code == op_invokevirtual ||
			//		   code == op_invokespecial);
				method_execute(m, self, env);
				break;
			}
			//debug
			case op_printi:
			{
				int i = SPI(self);
				printf("int: %d\n", i);
				INFO("printi");
				break;
			}

			case op_printd:
			{
				double d = SPD(self);
				printf("double: %f\n", d);
				INFO("printd");
				break;
			}

			case op_prints:
			{
				char* s = SPS(self);
				printf("string: %s\n", s);
				INFO("prints");
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
		//キャッチされなかった例外によって終了する
		if (self->terminate) {
			vm_uncaught(self);
			break; 
		}
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
	vm* temp = self;
	do {
		temp->exception = NULL;
		temp = temp->parent;
	} while (temp != NULL);
}

bool vm_validate(vm* self, int source_len, int* pcDest) {
	sg_thread* th = sg_thread_current();
	vm_trace* trace = (vm_trace*)stack_top(th->trace_stack);
	//ここなので catch節 へ向かう
	if (trace->v == self) {
		*pcDest = trace->pc;
		return true;
	//ここではないので終了
	} else {
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

void vm_uncaught(vm * self) {
	text_printfln("terminate... %d", self->level);
}

void vm_delete(vm * self) {
	//constant_pool_delete(self->pool);
	//operand_stack_delete(self->operand_stack);
	//vector_delete(self->value_stack, vector_deleter_null);
	//vector_delete(self->ref_stack, vector_deleter_null);
	MEM_FREE(self);
}

//private
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
	return ret->u.string_;
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
	return ret->u.string_;
}

static bool stack_popb(vm* self) {
	object* ret = (object*)vector_pop(self->value_stack);
	assert(ret->tag == object_bool);
	return ret->u.bool_;
}