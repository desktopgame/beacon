#include "vm.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "label.h"
#include "../util/logger.h"
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
	vm* ret = (vm*)malloc(sizeof(vm));
	ret->value_stack = vector_new();
	ret->ref_stack = vector_new();
	//ret->poolLength = 0;
	//ret->pool = constant_pool_new();
	//ret->operand_stack = operand_stack_new();
	//ret->operand_active = ret->operand_stack;
	return ret;
}

void vm_execute(vm* self, enviroment* env) {
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
				break;

			case op_logic_or:
				break;

			case op_bit_and:
				break;

			case op_logic_and:
				break;

			//push const
			case op_consti:
			{
				int index = (int)enviroment_source_at(env, ++i);
				int cv = (int)enviroment_constant_at(env, index);
				vector_push(self->value_stack, cv);
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
				char* cs = (char*)enviroment_constant_at(env, index);
				vector_push(self->value_stack, cs);
				INFO("push consts");
				break;
			}
			
			case op_method:
			{
				int index = (int)enviroment_source_at(env, ++i);
			}
				break;

			case op_dup:
				vector_push(self->value_stack, vector_top(self->value_stack));
				break;
			case op_pop:
				vector_pop(self->value_stack);
				break;
			case op_nop:
				/* no operation */
				break;

			//store,load
			case op_put_field:
			{
				int index = (int)enviroment_source_at(env, ++i);
				break;
			}

			case op_get_field:
			{
				int index = (int)enviroment_source_at(env, ++i);
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
				vector_assign(self->ref_stack, index, vector_pop(self->value_stack));
				INFO("store");
				break;
			}

			case op_load:
			{
				int index = (int)enviroment_source_at(env, ++i);
				vector_item e = vector_at(self->ref_stack, index);
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
	vector_delete(self->value_stack, vector_deleter_null);
	vector_delete(self->ref_stack, vector_deleter_null);
	free(self);
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