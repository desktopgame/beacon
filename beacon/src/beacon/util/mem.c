#include <stdlib.h>
#include <stdio.h>
#include "mem.h"
#include "text.h"

#if defined(_MSC_VER)
#include <crtdbg.h>
#endif

#include <assert.h>
#include <string.h>

#if defined(_WIN32)
#include <Windows.h>
#endif

/**
 * 確保されたメモリを管理する連結リスト.
 */
typedef struct slot {
	const char* filename;
	int lineno;
	int index;
	void* arena;
	size_t size;
	struct slot* prev;
	struct slot* next;
} slot;

static slot* slot_new(size_t size, void* arena, const char* filename, int lineno);
static slot* slot_find(void* arena);
static void slot_append(slot* arg);
static slot* slot_tail();
static void slot_cat(slot* left, slot* right);
static void* slot_realloc(void* block, size_t newSize, const char* filename, int lineno);
static void slot_free(void* block, const char* fillename, int lineno);
static void slot_delete(slot* self);
static void* fixed_realloc(void* block, size_t newSize);

static slot* gHead = NULL;
static slot* gTail = NULL;
static int gCount = 0;
static int gBreak = -1;

void * mem_malloc(size_t size, const char * filename, int lineno) {
	void* ret = malloc(size);
	memset(ret, 0, size);
	#if defined(DEBUG)
	slot_append(slot_new(size, ret, filename, lineno));
	#endif
	if(ret == NULL) {
		abort();
	}
	return ret;
}

void * mem_realloc(void * block, size_t newSize, const char * filename, int lineno) {
	#if defined(DEBUG)
	return slot_realloc(block, newSize, filename, lineno);
	#else
	return fixed_realloc(block, newSize);
	#endif
}

void mem_free(void * block, const char * filename, int lineno) {
	#if defined(DEBUG)
	slot_free(block, filename, lineno);
	#else
	free(block);
	#endif
}

void mem_dump() {
	#if defined(DEBUG)
	slot* iter = gHead;
	text_printf("mem dump---\n");
	while(iter != NULL) {
		text_printf("    %p %s<%d>\n", iter->arena, iter->filename, iter->lineno);
		iter = iter->next;
	}
	#endif
}

void mem_mark(void* p, size_t size, const char* filename, int lineno) {
	#if defined(DEBUG)
	slot_append(slot_new(size, p, filename, lineno));
	#endif
}

void mem_break(int count) {
	gBreak = count;
}

void mem_destroy() {
	#if defined(DEBUG)
	slot_delete(gHead);
	gHead = NULL;
	gCount = 0;
	gBreak = -1;
	#endif
}

//private
static slot* slot_new(size_t size, void* arena, const char* filename, int lineno) {
	slot* ret = malloc(sizeof(slot));
	ret->prev = NULL;
	ret->next = NULL;
	ret->arena = arena;
	ret->filename = filename;
	ret->lineno = lineno;
	return ret;
}

static slot* slot_find(void* arena) {
	if(gHead == NULL) {
		return NULL;
	}
	slot* iter = gHead;
	while(iter != NULL) {
		if(iter->arena == arena) {
			return iter;
		}
		iter = iter->next;
	}
	return NULL;
}

static void slot_append(slot* arg) {
	if(gHead == NULL) {
		gCount = 0;
		gHead = arg;
		arg->index = 0;
	} else {
		gCount++;
		slot_cat(slot_tail(), arg);
		arg->index = gCount;
		gTail = arg;
	}
}

static slot* slot_tail() {
	assert(gHead != NULL);
	if(gTail != NULL) {
		return gTail;
	}
	slot* iter = gHead;
	while(1) {
		slot* temp = iter;
		iter = iter->next;
		if(iter == NULL) {
			gTail = temp;
			return temp;
		}
	}
	return NULL;
}

static void slot_cat(slot* left, slot* right) {
	left->next = right;
	right->prev = left;
}

static void* slot_realloc(void* block, size_t newSize, const char* filename, int lineno) {
	//mem.h の malloc によって確保されたメモリではない
	slot* loc = slot_find(block);
	if(loc == NULL) {
		return fixed_realloc(block, newSize);
	}
	//mem.h の malloc によって確保された
	void* temp = fixed_realloc(block, newSize);
	loc->arena = temp;
	loc->filename = filename;
	loc->lineno = lineno;
	return temp;
}

static void slot_free(void* block, const char* fillename, int lineno) {
	//mem.h の malloc によって確保されたメモリではない
	slot* loc = slot_find(block);
	if(loc == NULL) {
		free(block);
		return;
	}
	//mem.h の malloc によって確保された
	if(loc->prev != NULL) {
		loc->prev->next = loc->next;
	}
	if(loc->next != NULL) {
		loc->next->prev = loc->prev;
	}
	if(loc == gHead) {
		gHead = loc->next;
	}
	loc->arena = NULL;
	loc->filename = NULL;
	gTail = NULL;
	free(block);
	free(loc);
}

static void slot_delete(slot* self) {
	if(self->next != NULL) {
		slot_delete(self->next);
	}
	if(self->prev != NULL) {
		self->prev->next = NULL;
	}
	free(self);
}

static void* fixed_realloc(void* block, size_t newSize) {
	void* ret = realloc(block, newSize);
	if(ret == NULL) {
		abort();
	}
	return ret;
}