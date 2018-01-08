#include "io.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "text.h"
#include "../util/mem.h"

#if defined(__clang__)
#include <unistd.h>
#endif

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

char * io_read_text(const char * filename) {
	assert(io_exists(filename));
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
	int buffer_size = 16;
	int length = 0;
	char* ret = (char*)MEM_MALLOC(sizeof(char) * buffer_size);
	while (1) {
		char c = fgetc(fp);
		if (c == EOF) {
			break;
		}
		ret[length] = c;
		length++;
		//予め確保していた領域をはみ出した
		if (length >= buffer_size) {
			buffer_size = buffer_size + (buffer_size / 2);
			char* temp = (char*)MEM_REALLOC(ret, sizeof(char) * buffer_size);
			//FIXME:再確保失敗時
			ret = temp;
		}
	}
	//多めに確保しすぎた
	if (length < buffer_size) {
		char* copy = (char*)MEM_MALLOC(sizeof(char) * length);
		for (int i = 0; i < length; i++) {
			copy[i] = ret[i];
		}
		MEM_FREE(ret);
		copy[length] = '\0';
		ret = copy;
	} else {
		ret[buffer_size] = '\0';
	}
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
		//printf("%c", c);
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
	printf("path %s", a);
	return text_strdup(a);
#endif
}
