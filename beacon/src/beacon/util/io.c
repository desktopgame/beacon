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
static void io_file_entry_delete(vector_item item);

void io_printi(int depth) {
	io_fprinti(stdout, depth);
}

void io_fprinti(FILE* fp, int depth) {
	for(int i=0; i<depth; i++) {
		fprintf(fp, "    ");
	}
}

void io_printfln(const char* fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	int ret = vprintf(fmt, ap);
	printf("\n");
	va_end(ap);
}

void io_println() {
	printf("\n");
}

void io_new_file(const char * filename) {
	assert(!io_exists(filename));
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

bool io_exists(const char * filename) {
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

bool io_delete(const char * filename) {
	return remove(filename);
}

char * io_read_text(const char * filename) {
	assert(io_exists(filename));
	string_buffer* buff = string_buffer_new();
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
		string_buffer_append(buff, c);
	}
	char* ret = string_buffer_release(buff);
	fclose(fp);
	return ret;
}

void io_write_text(const char * filename, const char * text) {
	assert(io_exists(filename));
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

void io_current_path(char* block, int len) {
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

char * io_absolute_path(const char * target) {
#if defined(_WIN32)
	char full[_MAX_PATH];
	if (_fullpath(full, target, _MAX_PATH) != NULL) {
		char* ret = text_strdup(full);
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
	io_current_path(full, 256);
	return text_concat(full, target);
#endif
}

char* io_resolve_script_path(const char* target) {
	string_buffer* sb = string_buffer_new();
	char full[256] = {0};
	io_current_path(full, 256);
	string_buffer_appends(sb, full);
	string_buffer_appends(sb, "script-lib/");
	string_buffer_appends(sb, target);
	return string_buffer_release(sb);
}

vector* io_list_files(const char* dirname) {
#if defined(_MSC_VER)
	//ワイルドカード指定ですべてのファイルを取得する
	string_buffer* buf = string_buffer_new();
	string_buffer_appends(buf, dirname);
	string_buffer_appends(buf, "/*.*");
	char* pattern = string_buffer_release(buf);
	vector* v = vector_new();
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
		e->filename = io_join_path(dirname, ffd.cFileName);
		e->is_file = true;
		vector_push(v, e);
	} while (FindNextFile(h, &ffd));
	FindClose(h);
	qsort(v->memory, v->length, sizeof(void*), io_list_files_sort);
	return v;
#else
	vector* ret = vector_new();
	DIR *dir = opendir(dirname);
	struct dirent *dp;
	struct stat fi;

	for (dp = readdir(dir); dp != NULL; dp = readdir(dir)) {
		if (dp->d_name[0] != '.') {
			char* fullp = io_join_path(dirname, dp->d_name);
			file_entry* ent = file_entry_ref(fullp);
			stat(fullp, &fi);
			ent->is_file = !S_ISDIR(fi.st_mode);
			vector_push(ret, ent);
		}
	}
	closedir(dir);
	qsort(ret->memory, ret->length, sizeof(void*), io_list_files_sort);
	return ret;
#endif
}

int io_list_files_sort(const void* a, const void* b) {
	file_entry* aF = *(file_entry**)a;
	file_entry* bF = *(file_entry**)b;
	return strcmp(aF->filename, bF->filename);
}

void io_list_files_delete(vector* files) {
	vector_delete(files, io_file_entry_delete);
}

bool io_extension(const char* filename, const char* ext) {
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

char* io_join_path(const char* a, const char* b) {
	string_buffer* buf = string_buffer_new();
	string_buffer_appends(buf, a);
	string_buffer_append(buf, '/');
	string_buffer_appends(buf, b);
	return string_buffer_release(buf);
}

//private
static void io_file_entry_delete(vector_item item) {
	file_entry* e = (file_entry*)item;
	file_entry_delete(e);
}