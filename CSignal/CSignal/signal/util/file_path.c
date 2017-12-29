#include "file_path.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "text.h"
#include "../util/mem.h"

//proto
static file_path* file_path_new_impl(char * name);
static char* file_path_dump_impl(file_path * self, char separator);
static void file_path_delete_tree_impl(file_path * self, bool delete_parent);

file_path* file_path_new(const char * name) {
	return file_path_new_impl(text_strdup(name));
}

file_path * file_path_new_nodup(char * name) {
	return file_path_new_impl(name);
}

file_path * file_path_parse(const char * source, char separator) {
	int len = strlen(source);
	int bufferSize = 16;
	int pointee = 0;
	char* buff = (char*)MEM_MALLOC(sizeof(char) * bufferSize);
	buff[bufferSize - 1] = '\0';
	file_path* root = NULL;
	for (int i = 0; i < len; i++) {
		char ch = source[i];
		//区切り文字なら
		if (ch == separator) {
			//事前に確保していたバッファーが大きすぎた場合
			int usedBufferSize = (i - pointee);
			if (pointee == 0) {
				usedBufferSize = i;
			}
			char* packedBuffer = NULL;
			if (usedBufferSize < bufferSize) {
				//最低限必要な領域をコピー
				packedBuffer = (char*)MEM_MALLOC((sizeof(char) * usedBufferSize) + 0);
				for (int i = 0; i < usedBufferSize; i++) {
					packedBuffer[i] = buff[i];
				}
				packedBuffer[usedBufferSize + 0] = '\0';
				//バックバッファーを破棄
				MEM_FREE(buff);
			} else packedBuffer = text_strdup(buff);
			//一つパスを進める
			if (root == NULL) {
				root = file_path_new_nodup(packedBuffer);
			} else {
				root = file_path_append_path(root, file_path_new_nodup(packedBuffer));
			}
			//バッファーをもとに戻す
			bufferSize = 16;
			buff = (char*)MEM_MALLOC(sizeof(char) * bufferSize);
			buff[bufferSize - 1] = '\0';
			pointee = i + 1;
		//それ以外ならバッファーへ追加
		} else {
			int index = i - pointee;
			//バッファーが足りなくなったので再確保
			if (index >= bufferSize) {
				int newBufferSize = bufferSize + (bufferSize / 2);
				char* temp = (char*)MEM_REALLOC(buff, sizeof(char) * newBufferSize);
				bufferSize = newBufferSize;
				buff = temp;
				assert(temp != NULL);
			}
			//printf("push %c\n", ch);
			buff[index] = ch;
		}
	}
	//最後に現れたパスの区切り文字が文字の終端でない
	//例えば foo/bar/xxx のような場合、
	//最後の xxx を解析出来ないので、
	//ここではそのケースに対応する。
	if (pointee < len) {
		int remine = len - pointee;
		char* tail = (char*)MEM_MALLOC((sizeof(char) * remine) + 1);
		for (int i = pointee; i < len; i++) {
			char ch = source[i];
			tail[i - pointee] = ch;
		}
		tail[remine] = '\0';
		root = file_path_append_path(root, file_path_new_nodup(tail));
		MEM_FREE(buff);
	}
	return root;
}

file_path * file_path_append(file_path * self, const char * name) {
	return file_path_append_path(self, file_path_new(name));
}

file_path * file_path_append_path(file_path * self, file_path * next) {
	//file_path* ret = file_path_new(name);
	next->parent = self;
	self->ref_count++;
	return next;
}

char * file_path_to_string(file_path * self, char separator) {
	assert(self != NULL);
	char* ret = file_path_dump_impl(self, separator);
	return ret;
}

void file_path_dump(file_path * self, char separator) {
	char* tmp = file_path_to_string(self, separator);
	printf("%s", tmp);
	text_putline();
	MEM_FREE(tmp);
}

void file_path_delete(file_path * self) {
	file_path_delete_tree_impl(self, false);
}

void file_path_delete_tree(file_path * self) {
	file_path_delete_tree_impl(self, true);
}

//private
static file_path* file_path_new_impl(char * name) {
	file_path* ret = (file_path*)MEM_MALLOC(sizeof(file_path));
	ret->parent = NULL;
	ret->name = name;
	ret->ref_count = 0;
	return ret;
}

static char* file_path_dump_impl(file_path * self, char separator) {
	char* block = NULL;
	int leftLen = 0;
	if (self->parent != NULL) {
		block = file_path_dump_impl(self->parent, separator);
		leftLen = strlen(block);
	}
	int len = strlen(self->name);
	char* temp = (char*)MEM_REALLOC(block, leftLen + len + 2);
	for (int i = leftLen; i < leftLen + len; i++) {
		temp[i] = self->name[i - leftLen];
	}
	temp[leftLen + len] = separator;
	temp[leftLen + len + 1] = '\0';
	return temp;
}

static void file_path_delete_tree_impl(file_path * self, bool delete_parent) {
	//assert(self->ref_count == 0);
	if (self->parent) {
		self->parent->ref_count--;
		if (delete_parent &&
			self->parent->ref_count == 0) {
			file_path_delete_tree(self->parent);
		}
		self->parent = NULL;
	}
	printf("free %s\n", self->name);
	MEM_FREE(self->name);
	self->name = NULL;
	MEM_FREE(self);
}