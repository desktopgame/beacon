#pragma once
#ifndef SIGNAL_ENV_SCRIPT_CONTEXT_H
#define SIGNAL_ENV_SCRIPT_CONTEXT_H
#include "../util/stack.h"
#include "../util/tree_map.h"
struct heap;

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
	stack* parserStack;
	tree_map* namespaceMap;
	tree_map* classLoaderMap;
	struct heap* heap;
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
 * 新しいスクリプトコンテキストを作成して返します.
 * @return
 */
script_context* script_context_new();

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
#endif // !SIGNAL_ENV_SCRIPT_CONTEXT_H
