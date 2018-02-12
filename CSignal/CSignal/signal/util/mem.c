#include <stdlib.h>
#include <stdio.h>
#include "mem.h"
#include "logger.h"
#include "text.h"

#include <crtdbg.h>
#include <assert.h>
#include <string.h>

//private struct
typedef struct slot {
	char* filename;
	int lineno;
	int index;
	void* arena;
	size_t size;
	struct slot* prev;
	struct slot* next;
} slot;

static void* defaultRealloc(void * block, size_t newSize, const char * filename, int lineno);
static slot* slot_new();
static void slot_init(const char* filename, int lineno, void* arena, size_t size);
static void slot_add(slot* head, slot* a);
static void* slot_realloc(slot* head, void* arena, size_t newSize);
static void slot_remove(slot* head, void* arena);
static void slot_dump(slot* self);
static void slot_destroy(slot* self);
static void mem_input();
static char* mem_readline();

static slot* gSlotHead = NULL;
static bool gMemTrace = false;
static int gMemCounter = 0;
static int gMemNotFoundRealloc = 0;
static int gMemNotFoundFree = 0;
static int gMemUsedMemory = 0;
static int gMemBreak = -1;

void * mem_malloc(size_t size, const char * filename, int lineno) {
	void* ret = malloc(size);
#if defined(DEBUG)
	if (gMemTrace) {
		slot_init(filename, lineno, ret, size);
	}
#endif
	if (ret == NULL) {
		sg_log(log_fatal, filename, lineno, "failed malloc");
	}
	return ret;
}

void * mem_realloc(void * block, size_t newSize, const char * filename, int lineno) {
#if defined(DEBUG)
	if (gMemTrace) {
		return slot_realloc(gSlotHead, block, newSize);
	} else {
		return defaultRealloc(block, newSize, filename, lineno);
	}
#else
	return defaultRealloc(block, newSize, filename, lineno);
#endif
}

void mem_free(void * block, const char * filename, int lineno) {
#if defined(DEBUG)
	if (gMemTrace) {
		slot_remove(gSlotHead, block);
	}
#endif
	free(block);
}

void mem_dump() {
#if defined(DEBUG)
	if (!gMemTrace) {
		return;
	}
	text_printfln(" - memory leaks(%d) -", gMemCounter);
	text_printfln("    used memory(%d)", gMemUsedMemory);
	text_printfln("    not found realloc(%d)", gMemNotFoundRealloc);
	text_printfln("    not found free(%d)", gMemNotFoundFree);

	slot* ptr = gSlotHead;
	while (ptr != NULL) {
		text_printf("    ");
		slot_dump(ptr);
		text_printf("\n");
		ptr = ptr->next;
	}
#endif
}

void mem_set_trace(bool trace) {
	gMemTrace = trace;
}

bool mem_get_trace() {
	return gMemTrace;
}

void mem_break(int count) {
	gMemBreak = count;
}

void mem_destroy() {
#if defined(DEBUG)
	if (!gMemTrace) {
		return;
	}
	slot_destroy(gSlotHead->next);
	gSlotHead = NULL;
#endif
}

//private
static void* defaultRealloc(void * block, size_t newSize, const char * filename, int lineno) {
	void* ret = realloc(block, newSize);
	if (ret == NULL) {
		sg_log(log_fatal, filename, lineno, "failed realloc");
	}
	//allocCount++;
	return ret;
}

static slot* slot_new() {
	slot* ret = (slot*)malloc(sizeof(slot));
	ret->filename = NULL;
	ret->lineno = -1;
	ret->size = -1;
	ret->prev = NULL;
	ret->next = NULL;
	ret->index = 0;
	return ret;
}

static void slot_init(const char* filename, int lineno, void* arena, size_t size) {
	//スロットの作成
	assert(arena != NULL);
	slot* ptr = NULL;
	if (gSlotHead == NULL) {
		gSlotHead = slot_new();
		ptr = gSlotHead;
		gMemCounter = 0;
		gMemNotFoundRealloc = 0;
		gMemNotFoundFree = 0;
		gMemUsedMemory = size;
	} else {
		ptr = slot_new();
		slot_add(gSlotHead, ptr);

		gMemCounter++;
		gMemUsedMemory += size;
		ptr->index = gMemCounter;
		if (ptr->index == gMemBreak) {
			mem_input();
		}
	}
	ptr->filename = filename;
	ptr->lineno = lineno;
	ptr->arena = arena;
	ptr->size = size;
}

static void slot_add(slot* head, slot* a) {
	slot* ptr = head;
	while (ptr->next != NULL) {
		assert((ptr != NULL && ptr->arena != NULL));
		ptr = ptr->next;
	}
	ptr->next = a;
	a->prev = ptr;
}

static void* slot_realloc(slot* head, void* arena, size_t newSize) {
	slot* ptr = head;
	while (ptr->arena != arena) {
		ptr = ptr->next;
		//mem_malloc以外で確保されたメモリ
		if (ptr == NULL) {
			void* ret = realloc(arena, newSize);
			assert(ret != NULL);
			gMemNotFoundRealloc++;
			return ret;
		}
	}
	void* temp = realloc(arena, newSize);
	assert(temp != NULL);
	//縮んだ
	if (ptr->size > newSize) {
		gMemUsedMemory -= (ptr->size - newSize);
	//拡大した
	} else if (ptr->size < newSize) {
		gMemUsedMemory += (newSize - ptr->size);
	}
	ptr->arena = temp;
	ptr->size = newSize;
	return temp;
}

static void slot_remove(slot* head, void* arena) {
	if (head == NULL) {
		return;
	}
	slot* ptr = head;
	while (ptr->arena != arena) {
		ptr = ptr->next;
		//mem_malloc以外で確保されたメモリ
		if (ptr == NULL) {
			gMemNotFoundFree++;
			return;
		}
	}
	if (ptr->prev != NULL) {
		ptr->prev->next = ptr->next;
	}
	if (ptr->next != NULL) {
		ptr->next->prev = ptr->prev;
	}
	gMemCounter--;
	gMemUsedMemory -= ptr->size;
	free(ptr);
	assert(gMemCounter >= 0);
}

static void slot_dump(slot* self) {
	text_printf("%p", self->arena);
	text_printf("(%d)", self->size);
	text_printf("@%d", self->index);
	text_printf(" %s", self->filename);
	text_printf("<%d>", self->lineno);
}

static void slot_destroy(slot* self) {
	if (self == NULL) {
		return;
	}
	slot* ptr = self;
	while (true) {
		ptr->filename = NULL;

		slot* next = NULL;
		if (ptr->next == NULL) {
			free(ptr);
		} else {
			slot* temp = ptr->next;
			free(ptr);
			next = temp;
		}
		if (next == NULL) {
			break;
		}
		ptr = next;
	}
}

static void mem_input() {
	int breakNow = 1;
	text_printfln("stop program!");
	while (breakNow != 0) {
		char* line = mem_readline();
		bool breakLoop = false;
		//コマンドを解釈
		if (!strcmp(line, "stop")) {
			breakLoop = true;
		} else if(!strcmp(line, "ignore")) {
			breakLoop = true;
		} else {
			text_printfln("undefined command: %s", line);
		}
		free(line);
		if (breakLoop) {
			break;
		}
	}
}

static char* mem_readline() {
	char* line = malloc(sizeof(char) * 16);
	int offs = 0;
	int len = 16;
	while (true) {
		char c = getc(stdin);
		//改行文字なら終了
		if (c == '\n') {
			break;
		}
		//まだバッファに余りがあある
		if (offs < len) {
			line[offs] = c;
			offs++;
		//もうないので拡張
		} else if (offs >= len) {
			int newLen = len + (len / 2);
			void* temp = realloc(line, sizeof(char) * newLen);
			assert(temp != NULL);
			line = temp;

			line[offs] = c;
			len = newLen;
			offs++;
		}
	}
	return line;
}