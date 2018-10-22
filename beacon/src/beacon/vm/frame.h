#ifndef BEACON_VM_FRAME_H
#define BEACON_VM_FRAME_H
#include "../util/stack.h"
#include "../util/vector.h"
#include "enviroment.h"
struct object;
struct type;
/**
 * 実行時の情報を格納する構造体.
 */
typedef struct Frame {
	//演算子や引数を記憶しておくためのスタックです
	Vector* ValueStack;

	//ローカル変数や引数を記憶しておくためのスタックです
	//0番目は this であることが保証されます。
	//その次には実引数が順番に並びます。
	Vector* VariableTable;

	//コンストラクタやメソッドの型引数を記憶するベクタ
	Vector* TypeArgs;

	//このVMの子要素です。
	//VMを分ける必要があるのは主に例外のためです。
	//例えば 子VM はコンストラクタ/メソッドが実行されるたびに
	//新たに作成されます。
	//通常、VMのルートは Singal言語のエントリポイント、
	//つまりメインファイルとなります。
	//子要素を記憶しておく必要があるのは、
	//ガベージコレクションのためです。
	Vector* Children;

	//親VMです.
	//コンストラクタ/メソッドが終了した場合、
	//それを実行していたVMは開放され、
	//ガベージコレクションの対象にはならないべきです。
	//(ここで言及される "対象にならない" は開放されないという
	//意味ではなく、マークの対象にならないという意味です。)
	//実行中のVMを開放したのち、
	//親のVMの childrenVec からも削除される必要があるため
	//ここで親VMへの参照を持っています。
	struct Frame* Parent;

	//最後にスローされた例外です.
	struct object* Exception;

	//コルーチンの実装クラスオブジェクトです.
	struct object* Coroutine;

	//メソッドを実行中のレシーバ型
	struct type* Receiver;

	//VMの階層の深さです.
	//デバッグ用の情報です。
	int Level;

	//現在実行中のインストラクションへの添え字をトレースします.
	//Program Counterの略です。
	int PC;

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
	int NativeThrowPos;

	//deferによる強制実行を記録するベクタ
	Vector* DeferList;

	//現在実行している強制実行
	int DeferAt;

	//現在実行しているインストラクションの一覧や、
	//定数プールを提供している enviroment への参照です。
	//あくまで参照しているだけなので、
	//このVMが開放されてもこの enviroment は開放されません。
	Enviroment* ContextRef;

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
	bool IsValidate;

	//例外がスローされたとき、
	//誰もそれをキャッチしようとしていないなら
	//即座に全てのVMを終了します。
	bool IsTerminate;
} Frame;

/**
 * 新しいフレームを作成します.
 * @return
 */
Frame* NewFrame();

/**
 * 親を指定してフレームを作成します.
 * @param parent
 * @return
 */
Frame* SubFrame(Frame* parent);

/**
 * このVMの変数を全てマークします.
 * @param self
 */
void MarkAllFrame(Frame* self);

/**
 * 仮想マシンを開放します.
 * @param self
 */
void DeleteFrame(Frame* self);

/**
 * フレームのルートを返します.
 * @param self
 * @return
 */
Frame* GetRootFrame(Frame* self);
#endif