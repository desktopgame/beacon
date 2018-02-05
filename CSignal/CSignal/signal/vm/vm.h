#pragma once
#ifndef SIGNAL_VM_VM_H
#define SIGNAL_VM_VM_H
#include "opcode.h"
#include "../util/stack.h"
#include "../util/vector.h"
#include "enviroment.h"
struct object;
/**
 * 実行時の情報を格納する構造体.
 */
typedef struct vm {
	vector* value_stack;
	vector* ref_stack;
	struct vm* parent;
	struct object* exception;
	int level;
	int pc;
	enviroment* contextRef;
	bool validate;
	bool terminate;
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
 * selfを起点としてたどれるVM全てに例外を伝播します.
 * @param self
 * @param exc
 */
void vm_throw(vm* self, struct object* exc);

/**
 * selfを起点としてたどれるVM全ての例外フラグをクリアします.
 * @param self NULLのときは何もしません。
 */
void vm_catch(vm* self);

/**
 * 現在のスレッドのトレース・スタックのトップに
 * 記録されたVMと自身が一致しているなら、
 * 自身に含まれる catch節 へジャンプします。
 * 異なるなら自身を終了して親の validate を trueにします。
 * validate が true のVM は、
 * 通常のインストラクションを実行する前にこの関数を呼び出します。
 * @param self
 * @param source_len
 * @param pcDest
 * @return このVMで処理できるなら true.
 */
bool vm_validate(vm* self, int source_len, int* pcDest);

/**
 * selfを起点としてたどれるVM全ての terminate を true にします.
 * 実行中のVMはこのフラグによって終了します。
 * @param self
 */
void vm_terminate(vm* self);

/**
 * 捕捉されなかった例外によってこのVMが終了するとき、
 * コールスタックの深いところから先に呼び出されます.
 * ここでどの関数呼び出しでエラーが発生したかを出力します。
 * @param self
 * @param env
 * @param pc
 */
void vm_uncaught(vm* self, enviroment* env, int pc);

/**
 * 仮想マシンを開放します.
 * @param self
 */
void vm_delete(vm* self);
#endif // !SIGNAL_VM_VM_H
