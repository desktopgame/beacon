#pragma once
#ifndef BEACON_ENV_SCRIPT_CONTEXT_H
#define BEACON_ENV_SCRIPT_CONTEXT_H
#include <stdbool.h>
#include "../util/stack.h"
#include "../util/tree_map.h"
#include "../util/vector.h"
#include "../util/numeric_map.h"
struct Heap;
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
typedef struct ScriptContext {
	NumericMap* NamespaceMap;
	TreeMap* ClassLoaderMap;
	Vector* ThreadList;
	Vector* IncludeList;
	struct class_loader* BootstrapClassLoader;
	//通し番号でクラスを参照するためのベクター
	Vector* TypeList;
	Vector* AllGenericList;
	//整数のキャッシュ
	Vector* pos_int_vec;
	Vector* neg_int_vec;
	NumericMap* n_int_map;
	bool print_error;
	bool abort_on_error;
	struct Heap* heap;
	struct object* true_obj;
	struct object* false_obj;
	struct object* null_obj;
} ScriptContext;

/**
 * スクリプトコンテキストを登録するためのスクリプトコンテキストを作成します.
 * このとき現在のコンテキストは上書きされます。
 * 既に作成されている場合は何もしません。
 * @return
 */
ScriptContext* OpenScriptContext();

/**
 * 現在のスクリプトコンテキストを返します.
 * この呼び出しは同期される必要があります。
 * @return
 */
ScriptContext* GetCurrentScriptContext();

/**
 * スクリプトコンテキストを登録するためのスクリプトコンテキストと、
 * そこから参照可能な全てのスクリプトコンテキストを開放します.
 */
void CloseScriptContext();

/**
 * まだブートストラップクラスローダが起動していないなら起動します.
 * @param self
 */
void BootstrapScriptContext(ScriptContext* self);

/**
 * 全ての静的フィールドを訪問します.
 * @param self
 * @param act
 */
void EachStaticScriptContext(ScriptContext* self, static_each act);

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
void ClearScriptContext(ScriptContext* self);

/**
 * 指定の整数をキャッシュします.
 * @param self
 * @param i
 * @return
 */
struct object* IInternScriptContext(ScriptContext* self, int i);

/**
 * 現在のコンテキストでリテラルをキャッシュします.
 */
void CacheScriptContext();
#endif // !SIGNAL_ENV_SCRIPT_CONTEXT_H
