#include "vm.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "label.h"
#include "../env/class.h"
#include "../env/method.h"
#include "../env/object.h"
#include "../env/constructor.h"
#include "../env/script_context.h"
#include "../util/logger.h"
#include "../util/mem.h"
#include "../util/vector.h"
//proto
static int stack_topi(vm* self);
static double stack_topd(vm* self);
static char stack_topc(vm* self);
static char* stack_tops(vm* self);

static int stack_popi(vm* self);
static double stack_popd(vm* self);
static char stack_popc(vm* self);
static char* stack_pops(vm* self);

//Stack Top
#define STI(a) stack_topi(a)
#define STD(a) stack_topd(a)
#define STC(a) stack_topc(a)
#define STS(a) stack_tops(a)

//Stack Pop
#define SPI(a) stack_popi(a);
#define SPD(a) stack_popd(a);
#define SPC(a) stack_popc(a);
#define SPS(a) stack_pops(a);

//Reference Store


vm * vm_new() {
	vm* ret = (vm*)MEM_MALLOC(sizeof(vm));
	ret->value_stack = vector_new();
	ret->ref_stack = vector_new();
	ret->parent = NULL;
	ret->level = 0;
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
		op_byte b = (op_byte)enviroment_source_at(env, i);
		switch (b) {
			//eval
			case op_add:
			{
				int a = SPI(self);
				int b = SPI(self);
				vector_push(self->value_stack, (a + b));
				INFO("add");
				break;
			}
			case op_sub:
			{
				int a = SPI(self);
				int b = SPI(self);
				vector_push(self->value_stack, (a - b));
				break;
			}
			case op_mul:
			{
				int a = SPI(self);
				int b = SPI(self);
				vector_push(self->value_stack, (a * b));
				break;
			}
			case op_div:
			{
				int a = SPI(self);
				int b = SPI(self);
				vector_push(self->value_stack, (a / b));
				break;
			}
			case op_mod:
			{
				int a = SPI(self);
				int b = SPI(self);
				vector_push(self->value_stack, (a % b));
				break;
			}
			case op_bit_or:
			{
				break;
			}
			case op_logic_or:
			{
				break;
			}
			case op_bit_and:
			{
				break;
			}
			case op_logic_and:
			{
				break;
			}
			case op_not:
			{
				break;
			}
			case op_neg:
			{
				break;
			}
			//push const
			case op_consti:
			{
				int index = (int)enviroment_source_at(env, ++i);
				object* o = (object*)enviroment_constant_int_at(env, index);
				vector_push(self->value_stack, o);
				INFO("push consti");
				break;
			}
			case op_constd:
			{
				break;
			}

			case op_constc:
			{
				break;
			}

			case op_consts:
			{
				int index = (int)enviroment_source_at(env, ++i);
				char* cs = enviroment_constant_string_at(env, index);
				vector_push(self->value_stack, cs);
				INFO("push consts");
				break;
			}
			case op_static_method:
			{
				int absClassIndex = (int)enviroment_source_at(env, ++i);
				int methodIndex = (int)enviroment_source_at(env, ++i);
				class_* cls = (class_*)vector_at(ctx->class_vec, absClassIndex);
				method* m = class_method_by_index(cls, methodIndex);
				//いらない
				opcode code = (opcode)enviroment_source_at(env, ++i);
				assert(code == op_invokestatic);
				method_execute(m, self, env);
				break;
			}
			case op_method:
			{
				int index = (int)enviroment_source_at(env, ++i);
				opcode code = (opcode)enviroment_source_at(env, ++i);
				object* o = (object*)vector_top(self->value_stack);
				method* m = class_method_by_index(o->classz, index);
				assert(code == op_invokevirtual ||
					   code == op_invokespecial);
				method_execute(m, self, env);
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
				class_* cls = (class_*)vector_at(ctx->class_vec, absClsIndex);
				object* obj = (object*)vector_top(self->value_stack);
				class_alloc_fields(cls, obj);
				break;
			}
			case op_new_instance:
			{
				//生成するクラスとコンストラクタを特定
				int absClsIndex = (int)enviroment_source_at(env, ++i);
				int constructorIndex = (int)enviroment_source_at(env, ++i);
				class_* cls = (class_*)vector_at(ctx->class_vec, absClsIndex);
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
				int fieldIndex = (int)enviroment_source_at(env, ++i);
				object* val = (object*)vector_at(sourceObject->u.field_vec, fieldIndex);
				vector_push(self->value_stack, val);
				break;
			}

			case op_put_static:
			{
				break;
			}

			case op_get_static:
			{
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
			case op_invokevirtual:
			{
				break;
			}

			case op_invokestatic:
			{
				break;
			}

			case op_invokespecial:
			{
				break;
			}

			case op_invokeinterface:
			{
				break;
			}

			case op_return:
			{
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

			//goto
			case op_goto:
			{
				label* l = (label*)enviroment_source_at(env, ++i);
				i = l->cursor;
				break;
			}

			case op_goto_if_true:
			{
				int v = vector_pop(self->value_stack);
				label* l = (label*)enviroment_source_at(env, ++i);
				if (v) {
					i = l->cursor;
				}
				break;
			}

			case op_goto_if_false:
			{
				int v = vector_pop(self->value_stack);
				label* l = (label*)enviroment_source_at(env, ++i);
				if (!v) {
					i = l->cursor;
				}
				break;
			}

			default:
				break;
		}
	}
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
	return (int)vector_top(self->value_stack);
}

static double stack_topd(vm* self) {
	double* d = (double*)vector_top(self->value_stack);
	return (*d);
}

static char stack_topc(vm* self) {
	char c = (char)vector_top(self->value_stack);
	return c;
}

static char* stack_tops(vm* self) {
	char* s = (char*)vector_top(self->value_stack);
	return s;
}


static int stack_popi(vm* self) {
	return (int)vector_pop(self->value_stack);
}

static double stack_popd(vm* self) {
	double* d = (double*)vector_pop(self->value_stack);
	return (*d);
}

static char stack_popc(vm* self) {
	char c = (char)vector_pop(self->value_stack);
	return c;
}

static char* stack_pops(vm* self) {
	char* s = (char*)vector_pop(self->value_stack);
	return s;
}