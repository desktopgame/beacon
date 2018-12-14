#include "string_buffer.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "mem.h"
#if defined(_MSC_VER)
#pragma warning(disable : 4996)
#endif
// proto
bc_Buffer* bc_MallocBuffer(const char* filename, int lineno) {
        bc_Buffer* ret = bc_MXMalloc(sizeof(bc_Buffer), filename, lineno);
        ret->Length = 0;
        ret->Capacity = 16;
        ret->Text = (char*)bc_MXMalloc(sizeof(char) * 16, filename, lineno);
        // memset(ret->Text, '\0', 16);
        return ret;
}

void bc_AppendBuffer(bc_Buffer* self, char c) {
        if (self->Length >= self->Capacity) {
                bc_ReserveBuffer(self);
        }
        self->Text[self->Length] = c;
        self->Length++;
}

void bc_AppendfBuffer(bc_Buffer* self, const char* fmt, ...) {
        va_list ap;
        va_start(ap, fmt);

        bc_VappendfBuffer(self, fmt, ap);
        va_end(ap);
}

void bc_VappendfBuffer(bc_Buffer* self, const char* fmt, va_list ap) {
#define BUFF_LEN (256)
        char block[BUFF_LEN];
        memset(block, '\0', BUFF_LEN);
        int res = vsprintf(block, fmt, ap);
        assert(res != -1);
        int len = strlen(block);
        for (int i = 0; i < len; i++) {
                char c = block[i];
                if (c == '\0') {
                        break;
                }
                bc_AppendBuffer(self, c);
        }

#undef BUFF_LEN
}

void bc_AppendsBuffer(bc_Buffer* self, const char* s) {
        for (int i = 0;; i++) {
                char c = s[i];
                if (c == '\0') break;
                bc_AppendBuffer(self, c);
        }
}

char* bc_ReleaseBuffer(bc_Buffer* self) {
        // bc_ShrinkBuffer(self);
        char* ret = self->Text;
        self->Text = NULL;
        MEM_FREE(self);
        return ret;
}

void bc_ReserveBuffer(bc_Buffer* self) {
        int newSize = self->Capacity + (self->Capacity / 2);
        char* temp = (char*)MEM_REALLOC(self->Text, newSize);
        assert(temp != NULL);
        //新しく確保された部分を 0埋め
        self->Text = temp;
        self->Capacity = newSize;
}

void bc_ShrinkBuffer(bc_Buffer* self) {
        if (self->Length == 0) {
                return;
        }
        char* temp = (char*)MEM_REALLOC(self->Text, self->Length + 1);
        assert(temp != NULL);
        temp[self->Length] = '\0';
        self->Text = temp;
        self->Capacity = self->Length;
}

bc_Buffer* bc_IndentBuffer(bc_Buffer* self, int lineIndex, int len) {
        bc_Buffer* buf = bc_NewBuffer();
        int linec = 0;
        int pos = 0;
        for (int i = 0; i < self->Length; i++) {
                char c = self->Text[i];
                if (pos == 0 &&
                    ((linec >= lineIndex && linec < (lineIndex + len)) ||
                     (lineIndex == -1 && len == -1))) {
                        bc_AppendsBuffer(buf, "    ");
                }
                if (c == '\n') {
                        linec++;
                        pos = 0;
                        bc_AppendBuffer(buf, '\n');
                } else {
                        bc_AppendBuffer(buf, c);
                        pos++;
                }
        }
        return buf;
}

void bc_DeleteBuffer(bc_Buffer* self) {
        if (self == NULL) {
                return;
        }
        MEM_FREE(self->Text);
        MEM_FREE(self);
}