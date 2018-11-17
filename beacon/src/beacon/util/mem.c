#include "mem.h"
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include "io.h"

static const char* gDBF = "mdb.dat";
static bc_Slot* gMXHead = NULL;
static int gBreak = -1;
static int gAll = 0;
static bc_Slot* new_slot();
static void location_slot(bc_Slot* self, const char* filename, int lineno);
static bc_Slot* get_last();
static bc_Slot* push_slot();
static bc_Slot* get_free_slot();
static bc_Slot* get_more_slot(int stock);
static bc_Slot* get_owner_slot(void* area);
static int delete_slot(FILE* fp, bc_Slot* self);
static void* get_layout(bc_Slot* self, size_t offset);
static void* get_aligned(bc_Slot* self);
static void set_self(bc_Slot* self);
static bc_Slot* get_self(void* area);

#define INIT (0xCC)
#define BORDER (0xCD)
#define POINTER_SIZE (sizeof(uintptr_t))
#define BORDER_SIZE (4)
#define REAL_SIZE(size) (size + (BORDER_SIZE * 2) + POINTER_SIZE)

void bc_InitMX() {
	assert(gMXHead == NULL);
	gMXHead = new_slot();
	for(int i=0; i<1000; i++) {
		push_slot();
	}
	//すでに存在するなら監視
	if(!ExistsFile(gDBF)) {
		return;
	}
	FILE* fp = fopen(gDBF, "rb");
	for(;;) {
		int count;
		int lineno;
		int fnlen;
		char* fn = NULL;
		bool hasNext = false;
		fread(&count, sizeof(int), 1, fp);
		fread(&lineno, sizeof(int), 1, fp);
		fread(&fnlen, sizeof(int), 1, fp);
		fn = SafeMalloc(sizeof(char) * fnlen);
		memset(fn, '\0', fnlen);
		fread(fn, sizeof(char), fnlen, fp);
		printf("<%d> :%d: %s\n", count, lineno, fn);
		free(fn);
		fread(&hasNext, sizeof(bool), 1, fp);
		bc_MXBreak(count);
		if(!hasNext) break;
	}
	fclose(fp);
}

void* bc_MXMalloc(size_t size, const char* filename, int lineno) {
	bc_Slot* slot = get_free_slot();
	void* area = SafeMalloc(REAL_SIZE(size));
	slot->Size = size;
	slot->UserArea = area;
	memset(area, INIT, REAL_SIZE(size));
	memset(area, BORDER, BORDER_SIZE);
	set_self(slot);
	memset(get_layout(slot, size + BORDER_SIZE + POINTER_SIZE), BORDER, BORDER_SIZE);
	location_slot(slot, filename, lineno);
	return get_aligned(slot);
}

void* bc_MXRealloc(void* block, size_t size, const char* filename, int lineno) {
	bc_Slot* c = get_owner_slot(block);
	if(c == NULL) {
		return SafeRealloc(block, size);
	}
	size_t old = c->Size;
	c->Size = size;
	c->UserArea = SafeRealloc(c->UserArea, REAL_SIZE(size));
	memset(c->UserArea, BORDER, BORDER_SIZE);
	memset(get_layout(c, size + BORDER_SIZE+ POINTER_SIZE), BORDER, BORDER_SIZE);
	set_self(c);
	if(size > old) {
	}
	location_slot(c, filename, lineno);
	return get_aligned(c);
}

void bc_MXFree(void* block, const char* filename, int lineno) {
	bc_Slot* c = get_owner_slot(block);
	if(c == NULL) {
		return;
	}
	c->Size = 0;
	free(c->UserArea);
	c->UserArea = NULL;
	location_slot(c, filename, lineno);
}

void* bc_MXBind(const void* block,size_t size,  const char* filename, int lineno) {
	bc_Slot* slot = get_free_slot();
	slot->Size = size;
	slot->UserArea = SafeMalloc(REAL_SIZE(size));
	memcpy(get_aligned(slot), block, size);
	set_self(slot);
	location_slot(slot, filename, lineno);
	return get_aligned(slot);
}

void bc_MXBreak(int index) {
	gBreak = index;
}

void bc_DestroyMX() {
	//すでに存在するなら削除
	if(ExistsFile(gDBF)) {
		bc_DeleteFile(gDBF);
	}
	FILE* fp = fopen(gDBF, "wb");
	int leaks = delete_slot(fp, gMXHead);
	if(leaks == 0) {
		printf("not detected memory leaks\n");
	} else {
		printf("detected memory leaks: %d\n", leaks);
	}
	fclose(fp);
	gMXHead = NULL;
}

void* SafeMalloc(size_t size) {
	void* ret = malloc(size);
	if(ret == NULL) {
		abort();
	}
	memset(ret, 0, size);
	return ret;
}

void* SafeRealloc(void* block, size_t new_size) {
	void* ret = realloc(block, new_size);
	if(ret == NULL) {
		abort();
	}
	return ret;
}
//private
static bc_Slot* new_slot() {
	bc_Slot* ret = SafeMalloc(sizeof(bc_Slot));
	memset(ret, 0, sizeof(bc_Slot));
	ret->Next = NULL;
	ret->FileName = NULL;
	ret->Lineno = -1;
	ret->Size = 0;
	ret->UserArea = NULL;
	ret->Count = gAll;
	if(gAll == gBreak) {
		abort();
	}
	gAll++;
	return ret;
}
static void location_slot(bc_Slot* self, const char* filename, int lineno) {
	self->FileName = filename;
	self->Lineno = lineno;
}
static bc_Slot* get_last() {
	assert(gMXHead != NULL);
	bc_Slot* iter = gMXHead;
	while(true) {
		if(iter->Next == NULL) {
			break;
		}
		iter = iter->Next;
	}
	return iter;
}
static bc_Slot* push_slot() {
	bc_Slot* last = get_last();
	last->Next = new_slot();
	return last->Next;
}
static bc_Slot* get_free_slot() {
	assert(gMXHead != NULL);
	bc_Slot* iter = gMXHead;
	int stock = 0;
	while(iter != NULL) {
		if(iter->Size == 0) {
			break;
		}
		stock++;
		iter = iter->Next;
	}
	if(iter == NULL) {
		iter = get_more_slot(stock);
	}
	return iter;
}
static bc_Slot* get_more_slot(int stock) {
	bc_Slot* iter = push_slot();
	stock /= 2;
	if(stock > 1000) stock = 1000;
	while(stock--) push_slot();
	return iter;
}

static bc_Slot* get_owner_slot(void* area) {
	return get_self(area);
}
static int delete_slot(FILE* fp, bc_Slot* self) {
	if(self == NULL) { return 0; }
	int sum = 0;
	bc_Slot* iter = self;
	while(iter != NULL) {
		bc_Slot* temp = iter->Next;
		if(iter->Size > 0) {
			bool hasNext = temp != NULL;
			int fnlen = strlen(iter->FileName) + 1;
			fwrite(&iter->Count, sizeof(int), 1, fp);
			fwrite(&iter->Lineno, sizeof(int), 1, fp);
			fwrite(&fnlen, sizeof(int), 1, fp);
			fwrite(iter->FileName, sizeof(char), fnlen, fp);
			fwrite(&hasNext, sizeof(bool), 1, fp);
			sum++;
		}
		free(iter->UserArea);
		free(iter);
		iter = temp;
	}
	return sum;
}

static void* get_layout(bc_Slot* self, size_t offset) {
	unsigned char* e = (unsigned char*)self->UserArea;
	return (void*)(e + offset);
}

static void* get_aligned(bc_Slot* self) {
	return get_layout(self, BORDER_SIZE + POINTER_SIZE);
}

static void set_self(bc_Slot* self) {
	//メモリ自体に自分を含める
	void* memory = get_layout(self, BORDER_SIZE);
	uintptr_t* ptr = (uintptr_t*)memory;
	*ptr = (uintptr_t)self;
}

static bc_Slot* get_self(void* area) {
	if(area == NULL) {
		return NULL;
	}
	void* fixed = (area - POINTER_SIZE);
	uintptr_t ptr = *((uintptr_t*)fixed);
	return (bc_Slot*)ptr;
}