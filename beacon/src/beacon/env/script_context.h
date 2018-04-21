#pragma once
#ifndef BEACON_ENV_SCRIPT_CONTEXT_H
#define BEACON_ENV_SCRIPT_CONTEXT_H
#include <stdbool.h>
#include "../util/stack.h"
#include "../util/tree_map.h"
#include "../util/vector.h"
struct heap;
struct object;
struct class_loader;

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
	stack* parser_stack;
	tree_map* namespace_map;
	tree_map* class_loader_map;
	vector* thread_vec;
	struct class_loader* bootstrap_class_loader;
	//通し番号でクラスを参照するためのベクター
	vector* type_vec;
	vector* all_generic_vec;
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
#endif // !SIGNAL_ENV_SCRIPT_CONTEXT_H
