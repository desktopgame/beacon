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

file_entry* file_entry_dup(const char* filename);

file_entry* file_entry_ref(char* filename);

void file_entry_delete(file_entry* self);
#endif