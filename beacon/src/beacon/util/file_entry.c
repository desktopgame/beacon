#include "file_entry.h"
#include "mem.h"
#include "text.h"

file_entry* file_entry_dup(const char* filename) {
	return file_entry_ref(text_strdup(filename));
}

file_entry* file_entry_ref(char* filename) {
	file_entry* ret = (file_entry*)MEM_MALLOC(sizeof(file_entry));
	ret->filename = filename;
	return ret;
}

void file_entry_delete(file_entry* self) {
	MEM_FREE(self->filename);
	MEM_FREE(self);
}