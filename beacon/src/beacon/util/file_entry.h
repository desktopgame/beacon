#ifndef BEACON_UTIL_FILE_ENTRY_H
#define BEACON_UTIL_FILE_ENTRY_H
#include <stdbool.h>
/**
 * ファイルを表す構造体.
 * フルパスを表します。
 */
typedef struct file_entry {
	char* filename;
	bool is_file;
} file_entry;

/**
 * 文字列を複製して新しいエントリを作成します.
 * @param filename
 * @return
 */
file_entry* file_entry_dup(const char* filename);

/**
 * 文字列を参照して新しいエントリを作成します.
 * @param filename file_entry_delete によって解放されます。
 * @return
 */
file_entry* file_entry_ref(char* filename);

/**
 * エントリを解放します.
 * @param self
 */
void file_entry_delete(file_entry* self);
#endif
