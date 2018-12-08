#include "io.h"
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#if defined(_MSC_VER)
#include <Windows.h>
#else
#include <dirent.h>
#endif

#include <sys/stat.h>
#include "../util/mem.h"
#include "file_entry.h"
#include "string_buffer.h"
#include "text.h"

#if defined(__clang__)
#include <unistd.h>
#endif

// proto
static void delete_file_entry(bc_VectorItem item);

void bc_Printi(int depth) { bc_Fprinti(stdout, depth); }

void bc_Fprinti(FILE* fp, int depth) {
        for (int i = 0; i < depth; i++) {
                fprintf(fp, "    ");
        }
}

void bc_Printfln(const char* fmt, ...) {
        va_list ap;
        va_start(ap, fmt);
        int ret = vprintf(fmt, ap);
        printf("\n");
        va_end(ap);
}

void bc_Println() { printf("\n"); }

void bc_CreateFile(const char* filename) {
        assert(!bc_ExistsFile(filename));
#if defined(_MSC_VER)
        FILE* fp;
        errno_t err = fopen_s(&fp, filename, "a");
        if (err) {
                return NULL;
        }
        fclose(fp);
#else
        FILE* fp = fopen(filename, "a");
        if (fp) {
                fclose(fp);
        }
#endif
}

bool bc_ExistsFile(const char* filename) {
#if defined(_MSC_VER)
        FILE* fp;
        errno_t err = fopen_s(&fp, filename, "r");
        if (!err) {
                fclose(fp);
        }
        return !err;
#else
        FILE* fp = fopen(filename, "r");
        if (!fp) {
                return false;
        }
        fclose(fp);
        return true;
#endif
}

bool bc_DeleteFile(const char* filename) { return remove(filename); }

char* bc_ReadText(const char* filename) {
        assert(bc_ExistsFile(filename));
        bc_Buffer* buff = bc_NewBuffer();
#if defined(_MSC_VER)
        FILE* fp;
        errno_t err = fopen_s(&fp, filename, "r");
        if (err) {
                // error
                return NULL;
        }
#else
        FILE* fp = fopen(filename, "r");
        if (!fp) {
                return NULL;
        }
#endif
        while (1) {
                char c = fgetc(fp);
                if (c == EOF) {
                        break;
                }
                bc_AppendBuffer(buff, c);
        }
        char* ret = bc_ReleaseBuffer(buff);
        fclose(fp);
        return ret;
}

void bc_WriteText(const char* filename, const char* text) {
        assert(bc_ExistsFile(filename));
#if defined(_MSC_VER)
        FILE* fp;
        errno_t err = fopen_s(&fp, filename, "w");
        if (err) {
                // error
                return;
        }
#else
        FILE* fp = fopen(filename, "w");
        if (!fp) {
                return;
        }
#endif
        int len = strlen(text);
        for (int i = 0; i < len; i++) {
                char c = text[i];
                fputc(c, fp);
        }
        fclose(fp);
}

void bc_GetCurrentPath(char* block, int len) {
        memset(block, '\0', len);
        getcwd(block, len);
        for (int i = 0; i < len; i++) {
                char c = block[i];
#if defined(_WIN32)
                if (c == '\\') {
                        block[i] = '/';
                }
#endif
                if (c == '\0') {
                        block[i] = '/';
                        break;
                }
        }
}

char* bc_GetAbsolutePath(const char* target) {
#if defined(_WIN32)
        char full[_MAX_PATH];
        if (_fullpath(full, target, _MAX_PATH) != NULL) {
                char* ret = bc_Strdup(full);
                char* iter = ret;
                while ((*iter) != '\0') {
                        if ((*iter) == '\\') {
                                (*iter) = '/';
                        }
                        iter++;
                }
                return ret;
        }
        return NULL;
#else
        char full[256] = {0};
        bc_GetCurrentPath(full, 256);
        return bc_ConcatString(full, target);
#endif
}

char* bc_ResolveScriptPath(const char* target) {
        bc_Buffer* sb = bc_NewBuffer();
        char full[256] = {0};
        bc_GetCurrentPath(full, 256);
        bc_AppendsBuffer(sb, full);
        bc_AppendsBuffer(sb, "script-lib/");
        bc_AppendsBuffer(sb, target);
        return bc_ReleaseBuffer(sb);
}

char* bc_ResolveCurrentPath(const char* target) {
        bc_Buffer* sb = bc_NewBuffer();
        char full[256] = {0};
        bc_GetCurrentPath(full, 256);
        bc_AppendsBuffer(sb, full);
        // bc_AppendsBuffer(sb, "script-lib/");
        bc_AppendsBuffer(sb, target);
        return bc_ReleaseBuffer(sb);
}

bc_Vector* bc_GetFiles(const char* dirname) {
#if defined(_MSC_VER)
        //ワイルドカード指定ですべてのファイルを取得する
        bc_Buffer* buf = bc_NewBuffer();
        bc_AppendsBuffer(buf, dirname);
        bc_AppendsBuffer(buf, "/*.*");
        char* pattern = bc_ReleaseBuffer(buf);
        bc_Vector* v = bc_NewVector();
        WIN32_FIND_DATA ffd;
        HANDLE h = FindFirstFile(pattern, &ffd);
        MEM_FREE(pattern);
        //取得できなかったので終了
        if (h == INVALID_HANDLE_VALUE) {
                return v;
        }
        do {
                if ((ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                        continue;
                }
                bc_FileEntry* e = MEM_MALLOC(sizeof(bc_FileEntry));
                e->FileName = bc_ConcatPath(dirname, ffd.cFileName);
                e->IsFile = true;
                bc_PushVector(v, e);
        } while (FindNextFile(h, &ffd));
        FindClose(h);
        qsort(v->Memory, v->Length, sizeof(void*), bc_SortFiles);
        return v;
#else
        bc_Vector* ret = bc_NewVector();
        DIR* dir = opendir(dirname);
        struct dirent* dp;
        struct stat fi;

        for (dp = readdir(dir); dp != NULL; dp = readdir(dir)) {
                if (dp->d_name[0] != '.') {
                        char* path = bc_ConcatPath(dirname, dp->d_name);
                        bc_FileEntry* entry = bc_RefFileEntry(path);
                        stat(path, &fi);
                        entry->IsFile = !S_ISDIR(fi.st_mode);
                        bc_PushVector(ret, entry);
                }
        }
        closedir(dir);
        qsort(ret->Memory, ret->Length, sizeof(void*), bc_SortFiles);
        return ret;
#endif
}

int bc_SortFiles(const void* a, const void* b) {
        bc_FileEntry* aF = *(bc_FileEntry**)a;
        bc_FileEntry* bF = *(bc_FileEntry**)b;
        return strcmp(aF->FileName, bF->FileName);
}

void bc_DeleteFiles(bc_Vector* files) {
        bc_DeleteVector(files, delete_file_entry);
}

bool bc_IsMatchExtension(const char* filename, const char* ext) {
        int fn_len = strlen(filename);
        int ext_len = strlen(ext);
        int mat_len = 0;
        for (int i = 0; i < fn_len; i++) {
                int offset = fn_len - i;
                char c = filename[fn_len - (i + 1)];
                if (c == '.') {
                        break;
                } else {
                        if (i >= ext_len) {
                                return false;
                        }
                        if (ext[ext_len - (i + 1)] != c) {
                                return false;
                        }
                        mat_len++;
                }
        }
        return mat_len == ext_len;
}

char* bc_ConcatPath(const char* a, const char* b) {
        bc_Buffer* buf = bc_NewBuffer();
        bc_AppendsBuffer(buf, a);
        bc_AppendBuffer(buf, '/');
        bc_AppendsBuffer(buf, b);
        return bc_ReleaseBuffer(buf);
}

// private
static void delete_file_entry(bc_VectorItem item) {
        bc_FileEntry* e = (bc_FileEntry*)item;
        bc_DeleteFileEntry(e);
}