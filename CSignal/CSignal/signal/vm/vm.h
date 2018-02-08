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
	//ネイティブメソッドから例外がスローされたとき、
	//復帰先のプログラムカウンタを記録しておく変数です。
	//通常例外はVMの処理中に発生しますが、
	//ネイティブメソッドの場合は処理の流れを中断して
	//関数ポインタで処理を実行します。
	//このとき現在のプログラムカウンタをそのまま置き換えることが出来ません。
	//(通常の例外であれば、forループからそのままプログラムカウンタを変更出来る。)
	//この変数はVMがインストラクションを実行したあと毎回確認され、
	//-1以外の値を格納している場合には現在のプログラムカウンタを上書きし、
	//この変数自体を-1にリセットします。
	int nativeThrowPos;
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
 * ネイティブメソッドから例外をスローする場合にはこちらを使用します.
 * @param self
 * @param exc
 */
void vm_native_throw(vm* self, struct object* exc);

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
