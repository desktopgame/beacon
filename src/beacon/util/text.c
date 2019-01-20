#include "text.h"
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <glib.h>
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
static char* read_digits(const char* literal, const char* ending, char* block,
                         int block_size);
static bool contains_char(const char* source, char a);
static FILE* text_fp = NULL;
static FILE* fake_stdout = NULL;
static FILE* real_stdout = NULL;

short bc_StrToShort(const char* literal) {
        char block[16] = {0};
        read_digits(literal, "sS", block, 16);
        short ret = atoi(block);
        return ret;
}

int bc_StrToInt(const char* literal) {
        char block[16] = {0};
        read_digits(literal, "iI", block, 16);
        int ret = atoi(block);
        return ret;
}

long bc_StrToLong(const char* literal) {
        char block[32] = {0};
        read_digits(literal, "lL", block, 32);
        long ret = atol(block);
        return ret;
}

float bc_StrToFloat(const char* literal) {
        char block[16] = {0};
        read_digits(literal, "fF", block, 16);
        float ret = (float)atof(block);
        return ret;
}

double bc_StrToDouble(const char* literal) {
        char block[32] = {0};
        read_digits(literal, "dD", block, 32);
        double ret = atof(block);
        return ret;
}

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

char* bc_ReadLine() { return read_line_impl(stdin); }

char* bc_FreadLine(FILE* fp) { return read_line_impl(fp); }

int bc_GetLastPathComponent(const char* src, char path, char buffer[],
                            int bufsize) {
        memset(buffer, '\0', bufsize);
        int len = strlen(src);
        int pos = len;
        //最後のパスの位置を取得
        for (int i = 0; i < len; i++) {
                char c = src[i];
                if (c == '\0') {
                        break;
                }
                if (c == path) {
                        pos = i + 1;
                        continue;
                }
        }
        int range = len - pos;
        if (range < bufsize) {
                for (int i = 0; i < range; i++) {
                        buffer[i] = src[pos + i];
                }
        } else if (range >= bufsize) {
                g_error("text#bc_GetLastPathComponent");
        }
        return range;
}

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

static char* read_digits(const char* literal, const char* ending, char* block,
                         int block_size) {
        int end = 0;
        for (int i = 0; i < block_size; i++) {
                if (literal[i] == '\0') {
                        end = i + 1;
                        break;
                } else if (contains_char(ending, literal[i])) {
                        end = i + 1;
                        break;
                } else {
                        block[i] = literal[i];
                }
        }
        for (int i = end; i < block_size; i++) {
                block[i] = '\0';
        }
        return block;
}

static bool contains_char(const char* source, char a) {
        for (int i = 0;; i++) {
                if (source[i] == '\0') {
                        break;
                }
                if (source[i] == a) {
                        return true;
                }
        }
        return false;
}