#include "io.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#if defined(_MSC_VER)
#include <Windows.h>
#else
#include <dirent.h>
#endif

#include <sys/stat.h>
#include "text.h"
#include "file_entry.h"
#include "../util/mem.h"
#include "string_buffer.h"

#if defined(__clang__)
#include <unistd.h>
#endif

//proto
static void FileEntryDeleter(VectorItem item);

void Printi(int depth) {
	Fprinti(stdout, depth);
}

void Fprinti(FILE* fp, int depth) {
	for(int i=0; i<depth; i++) {
		fprintf(fp, "    ");
	}
}

void Printfln(const char* fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	int ret = vprintf(fmt, ap);
	printf("\n");
	va_end(ap);
}

void Println() {
	printf("\n");
}

void NewFile(const char * filename) {
	assert(!ExistsFile(filename));
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

bool ExistsFile(const char * filename) {
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

bool DeleteFile(const char * filename) {
	return remove(filename);
}

char * ReadText(const char * filename) {
	assert(ExistsFile(filename));
	Buffer* buff = NewBuffer();
#if defined(_MSC_VER)
	FILE* fp;
	errno_t err = fopen_s(&fp, filename, "r");
	if (err) {
		//error
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
		AppendBuffer(buff, c);
	}
	char* ret = ReleaseBuffer(buff);
	fclose(fp);
	return ret;
}

void WriteText(const char * filename, const char * text) {
	assert(ExistsFile(filename));
#if defined(_MSC_VER)
	FILE* fp;
	errno_t err = fopen_s(&fp, filename, "w");
	if (err) {
		//error
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

void GetCurrentPath(char* block, int len) {
	memset(block, '\0', len);
	getcwd(block, len);
	for(int i=0; i<len; i++) {
		char c = block[i];
#if defined(_WIN32)
		if (c == '\\') {
			block[i] = '/';
		}
#endif
		if(c == '\0') {
			block[i] = '/';
			break;
		}
	}
}

char * GetAbsolutePath(const char * target) {
#if defined(_WIN32)
	char full[_MAX_PATH];
	if (_fullpath(full, target, _MAX_PATH) != NULL) {
		char* ret = Strdup(full);
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
	GetCurrentPath(full, 256);
	return ConcatString(full, target);
#endif
}

char* ResolveScriptPath(const char* target) {
	Buffer* sb = NewBuffer();
	char full[256] = {0};
	GetCurrentPath(full, 256);
	AppendsBuffer(sb, full);
	AppendsBuffer(sb, "script-lib/");
	AppendsBuffer(sb, target);
	return ReleaseBuffer(sb);
}

Vector* GetFiles(const char* dirname) {
#if defined(_MSC_VER)
	//ワイルドカード指定ですべてのファイルを取得する
	string_buffer* buf = NewBuffer();
	AppendsBuffer(buf, dirname);
	AppendsBuffer(buf, "/*.*");
	char* pattern = ReleaseBuffer(buf);
	Vector* v = NewVector();
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
		file_entry* e = MEM_MALLOC(sizeof(file_entry));
		e->filename = ConcatPath(dirname, ffd.cFileName);
		e->is_file = true;
		PushVector(v, e);
	} while (FindNextFile(h, &ffd));
	FindClose(h);
	qsort(v->memory, v->Length, sizeof(void*), GetFiles_sort);
	return v;
#else
	Vector* ret = NewVector();
	DIR *dir = opendir(dirname);
	struct dirent *dp;
	struct stat fi;

	for (dp = readdir(dir); dp != NULL; dp = readdir(dir)) {
		if (dp->d_name[0] != '.') {
			char* path = ConcatPath(dirname, dp->d_name);
			FileEntry* entry = RefFileEntry(path);
			stat(path, &fi);
			entry->IsFile = !S_ISDIR(fi.st_mode);
			PushVector(ret, entry);
		}
	}
	closedir(dir);
	qsort(ret->Memory, ret->Length, sizeof(void*), SortFiles);
	return ret;
#endif
}

int SortFiles(const void* a, const void* b) {
	FileEntry* aF = *(FileEntry**)a;
	FileEntry* bF = *(FileEntry**)b;
	return strcmp(aF->FileName, bF->FileName);
}

void DeleteFiles(Vector* files) {
	DeleteVector(files, FileEntryDeleter);
}

bool IsMatchExtension(const char* filename, const char* ext) {
	int fn_len = strlen(filename);
	int ext_len = strlen(ext);
	int mat_len = 0;
	for(int i=0; i<fn_len; i++) {
		int offset = fn_len - i;
		char c = filename[fn_len-(i+1)];
		if(c == '.') {
			break;
		} else {
			if(i >= ext_len) {
				return false;
			}
			if(ext[ext_len-(i+1)] != c) {
				return false;
			}
			mat_len++;
		}
	}
	return mat_len == ext_len;
}

char* ConcatPath(const char* a, const char* b) {
	Buffer* buf = NewBuffer();
	AppendsBuffer(buf, a);
	AppendBuffer(buf, '/');
	AppendsBuffer(buf, b);
	return ReleaseBuffer(buf);
}

//private
static void FileEntryDeleter(VectorItem item) {
	FileEntry* e = (FileEntry*)item;
	DeleteFileEntry(e);
}