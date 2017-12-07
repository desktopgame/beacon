#include "io.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

void io_new_file(const char * filename) {
	assert(!io_exists(filename));
	FILE* fp;
	errno_t err = fopen_s(&fp, filename, "a");
	if (err) {
		return NULL;
	}
	fclose(fp);
	return fp;
}

bool io_exists(const char * filename) {
	FILE* fp;
	errno_t err = fopen_s(&fp, filename, "r");
	if (!err) {
		fclose(fp);
	}
	return !err;
}

char * io_read_text(const char * filename) {
	assert(io_exists(filename));
	FILE* fp;
	errno_t err = fopen_s(&fp, filename, "r");
	if (err) {
		//error
		return NULL;
	}
	int buffer_size = 16;
	int length = 0;
	char* ret = (char*)malloc(sizeof(char) * buffer_size);
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
			char* temp = (char*)realloc(ret, sizeof(char) * buffer_size);
			//FIXME:再確保失敗時
			ret = temp;
		}
	}
	//多めに確保しすぎた
	if (length < buffer_size) {
		char* copy = (char*)malloc(sizeof(char) * length);
		for (int i = 0; i < length; i++) {
			copy[i] = ret[i];
		}
		free(ret);
		ret = copy;
	}
	fclose(fp);
	return ret;
}

void io_write_text(const char * filename, const char * text) {
	assert(io_exists(filename));
	FILE* fp;
	errno_t err = fopen_s(&fp, filename, "w");
	if (err) {
		//error
		return;
	}
	int len = strlen(text);
	for (int i = 0; i < len; i++) {
		char c = text[i];
		//printf("%c", c);
		fputc(c, fp);
	}
	fclose(fp);
}
