#pragma once
#ifndef BEACON_VM_VM_H
#define BEACON_VM_VM_H
#include "opcode.h"
#include "../util/stack.h"
#include "../util/vector.h"
#include "enviroment.h"
#include "frame.h"

/**
 * 指定のバイトコードを実行します.
 * @param self
 * @param env
 */
void vm_execute(frame* self, enviroment* env);

/**
 * 開始位置を指定して指定のバイトコードを実行します.
 * @param self
 * @param env
 * @param pos
 */
void vm_resume(frame* self, enviroment* env, int pos);

/**
 * ネイティブメソッドから例外をスローする場合にはこちらを使用します.
 * @param self
 * @param exc
 */
void vm_native_throw(frame* self, struct object* exc);

/**
 * selfを起点としてたどれるVM全てに例外を伝播します.
 * @param self
 * @param exc
 */
void vm_throw(frame* self, struct object* exc);

/**
 * selfを起点としてたどれるVM全ての例外フラグをクリアします.
 * @param self NULLのときは何もしません。
 */
void vm_catch(frame* self);

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
bool vm_validate(frame* self, int source_len, int* pcDest);

/**
 * selfを起点としてたどれるVM全ての terminate を true にします.
 * 実行中のVMはこのフラグによって終了します。
 * @param self
 */
void vm_terminate(frame* self);

/**
 * 捕捉されなかった例外によってこのVMが終了するとき、
 * コールスタックの深いところから先に呼び出されます.
 * ここでどの関数呼び出しでエラーが発生したかを出力します。
 * @param self
 * @param env
 * @param pc
 */
void vm_uncaught(frame* self, enviroment* env, int pc);

/**
 * VMがキャッチされなかった例外によって終了した時、
 * そのメッセージを返します.
 * @return
 */
string_view vm_error_message();
#endif // !SIGNAL_VM_VM_H
