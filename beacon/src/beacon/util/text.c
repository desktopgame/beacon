#include "text.h"
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../config.h"
#include "io.h"
#include "mem.h"
#include "string_buffer.h"

// proto
static char* text_strclone(const char* source);
static char* read_line_impl(FILE* fp);
static FILE* text_fp = NULL;
static FILE* fake_stdout = NULL;
static FILE* real_stdout = NULL;

short bc_StrToShort(const char* literal) { return atoi(literal); }

int bc_StrToInt(const char* literal) { return atoi(literal); }

long bc_StrToLong(const char* literal) { return atol(literal); }

float bc_StrToFloat(const char* literal) { return (float)atof(literal); }

double bc_StrToDouble(const char* literal) { return atof(literal); }

char* bc_Strdup(const char* source) {
        if (source == NULL) {
                return NULL;
        }
#if BC_DEBUG
        //\0を含める
        return bc_MXBind(source, (strlen(source) + 1) * sizeof(char), __FILE__,
                         __LINE__);
#else
        return strdup(source);
#endif
}

bool bc_IsBlankText(const char* str) {
        assert(str != NULL);
        int len = strlen(str);
        for (int i = 0; i < len; i++) {
                char e = str[i];
                if (e != ' ' && e != '\n' && !isspace(e)) {
                        return false;
                }
        }
        return true;
}

char* bc_ConcatString(const char* a, const char* b) {
#if defined(_MSC_VER)
        int alen = strlen(a);
        int blen = strlen(b);
        char* block = (char*)MEM_MALLOC((sizeof(char) * (alen + blen)) + 1);
        for (int i = 0; i < alen; i++) {
                block[i] = a[i];
        }
        for (int i = 0; i < blen; i++) {
                block[alen + i] = b[i];
        }
        block[alen + blen] = '\0';
        return block;
#else
        bc_Buffer* buff = bc_NewBuffer();
        bc_AppendsBuffer(buff, a);
        bc_AppendsBuffer(buff, b);
        char* ret = bc_ReleaseBuffer(buff);
        return ret;
#endif
}

char* bc_GetLineAt(const char* src, int lineno) {
        // printf("%s", src);
        // return NULL;
        if (src == NULL) {
                return NULL;
        }
        int len = strlen(src);
        int curLine = 0;
        bc_Buffer* buf = bc_NewBuffer();
        char* PTR = NULL;
        for (int i = 0; i < len; i++) {
                char c = src[i];
                if (c == '\0') {
                        break;
                }
                if (c == '\n') {
                        if (lineno == curLine) {
                                break;
                        }
                        curLine++;
                } else {
                        if (lineno == 0 || lineno == curLine) {
                                bc_AppendBuffer(buf, c);
                        }
                }
        }
        bc_ShrinkBuffer(buf);
        char* ret = buf->Text;
        MEM_FREE(buf);
        return ret;
}

char* bc_JoinString(bc_Vector* v, char* join) {
        if (v == NULL || v->Length == 0) {
                return NULL;
        }
        // FIXME:もうちょっと無駄をなくせるはず
        char* head = bc_Strdup((char*)bc_AtVector(v, 0));
        int ptr = strlen(head);
        for (int i = 1; i < v->Length; i++) {
                char* e = (char*)bc_AtVector(v, i);
                if (i <= (v->Length - 1) && join != NULL) {
                        char* conn = bc_ConcatString(head, join);
                        MEM_FREE(head);
                        head = conn;
                }
                char* ret = bc_ConcatString(head, e);
                MEM_FREE(head);
                head = ret;
        }
        return head;
}

bool bc_IsIncluded(const char* source, const char* text) {
        int pos = 0;
        int slen = strlen(source);
        int tlen = strlen(text);
        for (int i = 0; i < slen; i++) {
                char ch = source[i];
                int diff = tlen - pos;
                if (i + diff > slen) {
                        break;
                }
                if (ch == text[pos]) {
                        pos++;
                        if (pos == tlen) {
                                return true;
                        }
                } else {
                        pos = 0;
                }
        }
        return false;
}

char* bc_ReadLine() { return read_line_impl(stdin); }

char* bc_FreadLine(FILE* fp) { return read_line_impl(fp); }

// private
static char* text_strclone(const char* source) {
        int len = strlen(source);
        char* block = (char*)malloc(len + 1);
        for (int i = 0; i < len; i++) {
                block[i] = source[i];
        }
        block[len] = '\0';
        return block;
}

static char* read_line_impl(FILE* fp) {
        bc_Buffer* sb = bc_NewBuffer();
        while (1) {
                char ch = getc(fp);
                if (ch == '\0' || ch == '\n' || feof(fp)) {
                        break;
                }
                bc_AppendBuffer(sb, ch);
        }
        return bc_ReleaseBuffer(sb);
}