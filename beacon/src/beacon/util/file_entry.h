#ifndef BEACON_UTIL_FILE_ENTRY_H
#define BEACON_UTIL_FILE_ENTRY_H
#include <stdbool.h>
/**
 * ファイルを表す構造体.
 * フルパスを表します。
 */
typedef struct FileEntry_t {
	char* filename;
	bool is_file;
} FileEntry;

/**
 * 文字列を複製して新しいエントリを作成します.
 * @param filename
 * @return
 */
FileEntry* NewFileEntry(const char* filename);

/**
 * 文字列を参照して新しいエントリを作成します.
 * @param filename DeleteFileEntry によって解放されます。
 * @return
 */
FileEntry* RefFileEntry(char* filename);

/**
 * エントリを解放します.
 * @param self
 */
void DeleteFileEntry(FileEntry* self);
#endif
