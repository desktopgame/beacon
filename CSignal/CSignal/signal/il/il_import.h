#ifndef SIGNAL_IL_IL_IMPORT_H
#define SIGNAL_IL_IL_IMPORT_H
/**
 * インポート宣言を表す要素.
 */
typedef struct il_import {
	char* path;
} il_import;

/**
 * 指定のパスをインポートするインポート宣言を作成します.
 * 引数は呼び出し側で解放してください。
 * @param path
 * @return
 */
il_import* il_import_new(const char* path);

/**
 * このインポート宣言と包含された文字列を解放します.
 * @param self
 */
void il_import_delete(il_import* self);
#endif // !SIGNAL_IL_IL_IMPORT_H