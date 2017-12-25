#include "vm.h"
#include <stdlib.h>
#include <assert.h>
#include "../util/logger.h"
//proto


vm * vm_new() {
	vm* ret = (vm*)malloc(sizeof(vm));
	ret->value_stack = vector_new();
	ret->constant_pool = vector_new();
	//ret->poolLength = 0;
	//ret->pool = constant_pool_new();
	//ret->operand_stack = operand_stack_new();
	//ret->operand_active = ret->operand_stack;
	return ret;
}

void vm_execute(vm * self, vector* source) {
	int source_len = source->length;
	for (int i = 0; i < source_len; i++) {
		op_byte b = vector_at(source, i);
		switch (b) {
			case op_add:
			{
				int a = (int)vector_pop(self->value_stack);
				int b = (int)vector_pop(self->value_stack);
				vector_push(self->value_stack, (a + b));
				INFO("add");
				break;
			}
			case op_sub:
			{
				int a = (int)vector_pop(self->value_stack);
				int b = (int)vector_pop(self->value_stack);
				vector_push(self->value_stack, (a - b));
				break;
			}
			case op_mul:
			{
				int a = (int)vector_pop(self->value_stack);
				int b = (int)vector_pop(self->value_stack);
				vector_push(self->value_stack, (a * b));
				break;
			}
			case op_div:
			{
				int a = (int)vector_pop(self->value_stack);
				int b = (int)vector_pop(self->value_stack);
				vector_push(self->value_stack, (a / b));
			}
			case op_mod:
			{
				int a = (int)vector_pop(self->value_stack);
				int b = (int)vector_pop(self->value_stack);
				vector_push(self->value_stack, (a % b));
				break;
			}

			case op_bit_or:
			case op_logic_or:

			case op_bit_and:
			case op_logic_and:

			case op_consti:
			{
				int index = vector_at(source, ++i);
				int cv = (int)vector_at(self->constant_pool, index);
				vector_push(self->value_stack, cv);
				INFO("push consti");
				break;
			}
			case op_constd:
			case op_constc:
			case op_consts:
			default:
				break;
		}
	}
}

void vm_delete(vm * self) {
	//constant_pool_delete(self->pool);
	//operand_stack_delete(self->operand_stack);
	vector_delete(self->constant_pool, vector_deleter_null);
	vector_delete(self->value_stack, vector_deleter_null);
	free(self);
}
