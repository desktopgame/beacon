#include "file_entry.h"
#include "mem.h"
#include "text.h"

FileEntry* NewFileEntry(const char* filename) {
	return RefFileEntry(text_strdup(filename));
}

FileEntry* RefFileEntry(char* filename) {
	FileEntry* ret = (FileEntry*)MEM_MALLOC(sizeof(FileEntry));
	ret->filename = filename;
	return ret;
}

void DeleteFileEntry(FileEntry* self) {
	MEM_FREE(self->filename);
	MEM_FREE(self);
}