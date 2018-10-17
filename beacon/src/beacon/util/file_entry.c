#include "file_entry.h"
#include "mem.h"
#include "text.h"

FileEntry* NewFileEntry(const char* filename) {
	return RefFileEntry(Strdup(filename));
}

FileEntry* RefFileEntry(char* filename) {
	FileEntry* ret = (FileEntry*)MEM_MALLOC(sizeof(FileEntry));
	ret->FileName = filename;
	return ret;
}

void DeleteFileEntry(FileEntry* self) {
	MEM_FREE(self->FileName);
	MEM_FREE(self);
}