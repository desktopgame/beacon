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
 * beacon言語のあらゆるオブジェクトのトップレベル.
 * ホスト言語から異なる環境のスクリプトを実行するためにこの方法を使用します。
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
	bool print_error;
	struct heap* heap;
	struct object* true_obj;
	struct object* false_obj;
	struct object* null_obj;
} script_context;

/**
 * スクリプトコンテキストを登録するためのスクリプトコンテキストを作成します.
 * このとき現在のコンテキストは上書きされます。
 * 既に作成されている場合は何もしません。
 * @return
 */
script_context* script_context_open();

/**
 * 現在のスクリプトコンテキストを返します.
 * この呼び出しは同期される必要があります。
 * @return
 */
script_context* script_context_get_current();

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
