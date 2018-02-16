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
	//演算子や引数を記憶しておくためのスタックです
	vector* value_stack;

	//ローカル変数や引数を記憶しておくためのスタックです
	//0番目は this であることが保証されます。
	//その次には実引数が順番に並びます。
	vector* ref_stack;

	//このVMの子要素です。
	//VMを分ける必要があるのは主に例外のためです。
	//例えば 子VM はコンストラクタ/メソッドが実行されるたびに
	//新たに作成されます。
	//通常、VMのルートは Singal言語のエントリポイント、
	//つまりメインファイルとなります。
	//子要素を記憶しておく必要があるのは、
	//ガベージコレクションのためです。
	vector* childrenVec;

	//親VMです.
	//コンストラクタ/メソッドが終了した場合、
	//それを実行していたVMは開放され、
	//ガベージコレクションの対象にはならないべきです。
	//(ここで言及される "対象にならない" は開放されないという
	//意味ではなく、マークの対象にならないという意味です。)
	//実行中のVMを開放したのち、
	//親のVMの childrenVec からも削除される必要があるため
	//ここで親VMへの参照を持っています。
	struct vm* parent;

	//最後にスローされた例外です.
	struct object* exception;

	//VMの階層の深さです.
	//デバッグ用の情報です。
	int level;

	//現在実行中のインストラクションへの添え字をトレースします.
	//Program Counterの略です。
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

	//現在実行しているインストラクションの一覧や、
	//定数プールを提供している enviroment への参照です。
	//あくまで参照しているだけなので、
	//このVMが開放されてもこの enviroment は開放されません。
	enviroment* contextRef;

	//例外がスローされた最も深いVMからルートへ向かって true に切り替えられるフラグ.
	//例外がスローされた場合、
	//最寄りのキャッチ節を探索する必要がありますが、
	//例外のその性質上(呼び出し階層を飛び越えることが出来る)
	//実行中のVMだけでなく、自分を子要素としている親VMも
	//その探索対象となります。
	//現在最寄りのキャッチ節を探しているということを
	//オペコードによって静的に表すことはできないので、
	//この変数で親VMに通知します。
	//この変数はあらゆるインストラクションを実行するよりも前に、
	//毎回検査されます。
	bool validate;

	//例外がスローされたとき、
	//誰もそれをキャッチしようとしていないなら
	//即座に全てのVMを終了します。
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
 * 開始位置を指定して指定のバイトコードを実行します.
 * @param self
 * @param env
 * @param pos
 */
void vm_resume(vm* self, enviroment* env, int pos);

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
 * このVMの変数を全てマークします.
 * @param self
 */
void vm_markall(vm* self);

/**
 * 仮想マシンを開放します.
 * @param self
 */
void vm_delete(vm* self);
#endif // !SIGNAL_VM_VM_H
