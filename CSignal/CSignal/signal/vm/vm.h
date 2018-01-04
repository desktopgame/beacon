#pragma once
#ifndef SIGNAL_VM_VM_H
#define SIGNAL_VM_VM_H
#include "opcode.h"
#include "../util/stack.h"
#include "../util/vector.h"
#include "enviroment.h"

/**
 * 実行時の情報を格納する構造体.
 */
typedef struct vm {
	vector* value_stack;
	vector* ref_stack;
	struct vm* parent;
	int level;
} vm;

/**
 * 新しい仮想マシンを作成します.
 * @return
 */
vm* vm_new();

/**
 * 親を指定して仮想マシンを作成します.
 * @param parent
 * @return
 */
vm* vm_sub(vm* parent);

/**
 * 指定のバイトコードを実行します.
 * @param self
 * @param env
 */
void vm_execute(vm* self, enviroment* env);

/**
 * 仮想マシンを開放します.
 * @param self
 */
void vm_delete(vm* self);
#endif // !SIGNAL_VM_VM_H
