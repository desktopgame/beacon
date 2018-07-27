#ifndef BEACON_IL_IL_IMPORT_H
#define BEACON_IL_IL_IMPORT_H
#include "../util/string_pool.h"
/**
 * インポート宣言を表す要素.
 */
typedef struct il_import {
	string_view pathv;
} il_import;

/**
 * 指定のパスをインポートするインポート宣言を作成します.
 * 引数は呼び出し側で解放してください。
 * @param pathv
 * @return
 */
il_import* il_import_new(string_view pathv);

/**
 * インポートの詳細を出力します.
 * @param self
 * @param depth
 */
void il_import_dump(il_import* self, int depth);

/**
 * このインポート宣言と包含された文字列を解放します.
 * @param self
 */
void il_import_delete(il_import* self);
#endif // !SIGNAL_IL_IL_IMPORT_H
