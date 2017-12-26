#pragma once
#ifndef SIGNAL_VM_VM_H
#define SIGNAL_VM_VM_H
#include "opcode.h"
#include "../util/stack.h"
#include "../util/vector.h"

/**
 * 実行時の情報を格納する構造体.
 */
typedef struct vm {
//	value_stack* value_stack;
	vector* value_stack;
	vector* ref_stack;
	vector* constant_pool;
//	int poolLength;
//	constant_pool* pool;
//	operand_stack* operand_stack;
//	operand_stack* operand_active;
} vm;

/**
 * 新しい仮想マシンを作成します.
 * @return
 */
vm* vm_new();

/**
 * 指定のバイトコードを実行します.
 * @param self
 * @param source
 */
void vm_execute(vm* self, vector* source);

/**
 * 仮想マシンを開放します.
 * @param self
 */
void vm_delete(vm* self);
#endif // !SIGNAL_VM_VM_H
