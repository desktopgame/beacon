#pragma once
#ifndef BEACON_ENV_SCRIPT_CONTEXT_H
#define BEACON_ENV_SCRIPT_CONTEXT_H
#include <stdbool.h>
#include "../util/stack.h"
#include "../util/tree_map.h"
#include "../util/vector.h"
#include "../util/numeric_map.h"
struct heap;
struct object;
struct class_loader;
struct field;

/**
 * 静的フィールドを訪問するための関数ポインタ.
 * @param item
 */
typedef void(*static_each)(struct field* item);

/**
 * 唯一のスクリプトコンテキストを表すIDです.
 */
typedef unsigned long script_cid;

/**
 * スクリプトコンテキストは、
 * signal言語を構成するあらゆる要素のトップレベルです。
 * 名前空間やスレッドはどこからでもアクセス可能であるべきなので
 * グローバル空間に置きたいですが、
 * 例えばデバッグなどの用途のために複数のスクリプトを実行する必要がある場合に、
 * それらを共用するのは問題になる場合があります。
 * この言語の実装では、script_contextのみを唯一のグローバル変数として、
 * 付随するすべては script_context(あるいはそのフィールド)のフィールドとして持たせます。
 */
typedef struct script_context {
	numeric_map* namespace_nmap;
	tree_map* class_loader_map;
	vector* thread_vec;
	vector* include_vec;
	struct class_loader* bootstrap_class_loader;
	//通し番号でクラスを参照するためのベクター
	vector* type_vec;
	vector* all_generic_vec;
	//整数のキャッシュ
	vector* pos_int_vec;
	vector* neg_int_vec;
	numeric_map* n_int_map;
	struct heap* heap;
	struct object* oTrue;
	struct object* oFalse;
	struct object* oNull;
	struct script_context* prev;
	struct script_context* next;
} script_context;

/**
 * スクリプトコンテキストを登録するためのスクリプトコンテキストを作成します.
 * このとき現在のコンテキストは上書きされます。
 * 既に作成されている場合は何もしません。
 */
void script_context_open();

/**
 * 新しいコンテキストを作成して返します.
 * @return
 */
script_context* script_context_add();

/**
 * 指定の要素を連結リストから外して開放します.
 * @param self
 * @return
 */
script_context* script_context_remove(script_context* self);

/**
 * 末尾のコンテキストを返します.
 * @return
 */
script_context* script_context_back();

/**
 * 現在のスクリプトコンテキストに設定します.
 * この呼び出しは同期される必要があります。
 * @param self
 */
void script_context_set_current(script_context* self);

/**
 * 現在のスクリプトコンテキストを返します.
 * この呼び出しは同期される必要があります。
 * @return
 */
script_context* script_context_get_current();

/**
 * 任意のコンテキストを開放します.
 * @param self
 */
void script_context_delete(script_context* self);

/**
 * スクリプトコンテキストを登録するためのスクリプトコンテキストと、
 * そこから参照可能な全てのスクリプトコンテキストを開放します.
 */
void script_context_close();

/**
 * まだブートストラップクラスローダが起動していないなら起動します.
 * @param self
 */
void script_context_bootstrap(script_context* self);

/**
 * 新しいスクリプトコンテキストを開始したとき、
 * ブートストラップクラスローダを起動するなら true.
 * デフォルトで true です。
 * @param b
 */
void script_context_set_bootstrap(bool b);

/**
 * @return
 */
bool script_context_get_bootstrap();

/**
 * 全ての静的フィールドを訪問します.
 * @param self
 * @param act
 */
void script_context_static_each(script_context* self, static_each act);

/**
 * 全ての静的フィールドをクリアします.
 * 一つのコンテキストで複数回プログラムを実行する場合には、
 * これを呼び出す必要がある...場合もあります。
 * 一つのコンテキストで複数回実行するということは、
 * その回数分エントリポイントの定数プールも作成/破棄されることになります。
 * 静的フィールドが定数プールの値を参照したまま実行を終了した場合、
 * 次の実行でそのポインタがGCによってマークされることになります。
 * これはすでに解放されたポインタへのアクセスになってしまいます。
 * なので、複数回実行する場合にはこれを使用して静的フィールドをクリアします。
 * @param self
 */
void script_context_static_clear(script_context* self);

/**
 * 指定の整数をキャッシュします.
 * @param self
 * @param i
 * @return
 */
struct object* script_context_iintern(script_context* self, int i);

/**
 * 現在のコンテキストでリテラルをキャッシュします.
 */
void script_context_cache();
#endif // !SIGNAL_ENV_SCRIPT_CONTEXT_H
