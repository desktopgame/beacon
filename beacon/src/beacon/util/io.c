#include "io.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
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

bool io_exists_s(const char* filename) {
	errno = 0;
	bool ret = io_exists(filename);
	int tmp = errno;
	if(!ret) {
		perror("fopen error  ");
		text_printf("path: %s", filename);
	}
	return ret;
}

bool io_delete(const char * filename) {
	return remove(filename);
}

char * io_read_text(const char * filename) {
	assert(io_exists_s(filename));
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
		//text_printf("%c", c);
		fputc(c, fp);
	}
	fclose(fp);
}

char * io_absolute_path(const char * target) {
#if defined(_WIN32)
	char full[_MAX_PATH];
	if (_fullpath(full, target, _MAX_PATH) != NULL) {
		return text_strdup(full);
	}
	return NULL;
#else
	char full[256] = {0};
	memset(full, '\0', 256);
	getcwd(full, 256);
	for(int i=0; i<256; i++) {
		char c = full[i];
		if(c == '\0') {
			full[i] = '/';
			break;
		}
	}
	char* a = text_concat(full, target);
	//text_printf("path %s", a);
	//return text_strdup(a);
	return a;
#endif
}

vector* io_list_files(const char* dirname) {
	vector* ret = vector_new();
	DIR *dir = opendir(dirname);
	struct dirent *dp;
	struct stat fi;

	for (dp = readdir(dir); dp != NULL; dp = readdir(dir)) {
		if (dp->d_name[0] != '.') {
			char* fullp = io_join_path(dirname, dp->d_name);
			file_entry* ent = file_entry_ref(fullp);
			//joinpath(path2, dirname, dp->d_name);
			stat(fullp, &fi);
			ent->is_file = !S_ISDIR(fi.st_mode);
			vector_push(ret, ent);
		}
	}
	closedir(dir);
	qsort(ret->memory, ret->length, sizeof(void*), io_list_files_sort);
	//vector_sort(ret, io_list_files_sort);
	return ret;
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
	int len = strlen(filename);
	string_buffer* buf = string_buffer_new();
	for(int i=(len-1); i>=0; i--) {
		char ch = filename[i];
		if(ch == '.') {
			break;
		}
		string_buffer_prepend(buf, ch);
	}
	char* real_ext = string_buffer_release(buf);
	bool ret = !(strcmp(ext, real_ext));
	MEM_FREE(real_ext);
	return ret;
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