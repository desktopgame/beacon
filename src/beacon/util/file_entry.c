#include "file_entry.h"
#include "mem.h"
#include "text.h"

bc_FileEntry* bc_NewFileEntry(const char* filename) {
        return bc_RefFileEntry(bc_Strdup(filename));
}

bc_FileEntry* bc_RefFileEntry(char* filename) {
        bc_FileEntry* ret = (bc_FileEntry*)MEM_MALLOC(sizeof(bc_FileEntry));
        ret->FileName = filename;
        return ret;
}

void bc_DeleteFileEntry(bc_FileEntry* self) {
        MEM_FREE(self->FileName);
        MEM_FREE(self);
}