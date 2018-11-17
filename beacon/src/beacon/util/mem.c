#include "mem.h"
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include "io.h"

static const char* gDBF = "mdb.dat";
static bc_Slot* gMXHead = NULL;
static int gAll = 0;
static int* gBreakPoints = NULL;
static int gBreakPointsSize = 0;
static int gBreakPointsCapa = 0;
static int gStack = 0;
static bc_Slot* new_slot();
static void location_slot(bc_Slot* self, const char* filename, int lineno);
static bc_Slot* get_last();
static bc_Slot* push_slot();
static bc_Slot* get_free_slot();
static bc_Slot* get_more_slot(int stock);
static bc_Slot* get_owner_slot(void* area);
static int delete_slot(bc_Slot* self);
static void* get_layout(bc_Slot* self, size_t offset);
static void* get_aligned(bc_Slot* self);
static void set_self(bc_Slot* self);
static bc_Slot* get_self(void* area);
static void init_bp();
static void destroy_bp();
static void reserve_bp();
static void push_bp(int i);
static bool include_bp(int t);
static void attach_bp(bc_Slot* self);
static int save_bp();
static int collect_leaks_bp(bc_Slot* self);
static void write_bp(FILE* fp, bc_Slot* self);
static void load_bp();

#define INIT (0xCC)
#define BORDER (0xCD)
#define POINTER_SIZE (sizeof(uintptr_t))
#define BORDER_SIZE (4)
#define REAL_SIZE(size) (size + (BORDER_SIZE * 2) + POINTER_SIZE)

void bc_InitMX() {
	assert(gMXHead == NULL);
	assert(gBreakPoints == NULL);
	gMXHead = new_slot();
	init_bp();
	for(int i=0; i<1000; i++) {
		push_slot();
	}
	//すでに存在するなら監視
	if(!ExistsFile(gDBF)) {
		return;
	}
	load_bp();
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
	attach_bp(slot);
	gStack++;
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
	if(block == NULL) { return; }
	gStack--;
	bc_Slot* c = get_owner_slot(block);
	if(c == NULL) {
		return;
	}
	c->Size = 0;
	free(c->UserArea);
	c->UserArea = NULL;
	c->Count = -1;
	location_slot(c, filename, lineno);
}

void* bc_MXBind(const void* block,size_t size,  const char* filename, int lineno) {
	bc_Slot* slot = get_free_slot();
	slot->Size = size;
	slot->UserArea = SafeMalloc(REAL_SIZE(size));
	memcpy(get_aligned(slot), block, size);
	set_self(slot);
	location_slot(slot, filename, lineno);
	attach_bp(slot);
	gStack++;
	return get_aligned(slot);
}

void bc_DestroyMX() {
	//すでに存在するなら削除
	if(ExistsFile(gDBF)) {
		bc_DeleteFile(gDBF);
	}
	save_bp();
	delete_slot(gMXHead);
	gMXHead = NULL;
	destroy_bp();
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
	ret->Count = -1;
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

static int delete_slot(bc_Slot* self) {
	if(self == NULL) { return 0; }
	int sum = 0;
	bc_Slot* iter = self;
	while(iter != NULL) {
		bc_Slot* temp = iter->Next;
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

static void init_bp() {
	assert(gBreakPoints == NULL);
	gBreakPoints = SafeMalloc(sizeof(int) * 16);
	gBreakPointsCapa = 16;
	gBreakPointsSize = 0;
}

static void destroy_bp() {
	free(gBreakPoints);
	gBreakPointsCapa = 0;
	gBreakPointsSize = 0;
}

static void reserve_bp() {
	assert(gBreakPoints != NULL);
	int ns = gBreakPointsCapa + (gBreakPointsCapa / 2);
	void* p = SafeRealloc(gBreakPoints, sizeof(int) * ns);
	gBreakPoints = (int*)p;
	gBreakPointsCapa = ns;
}

static void push_bp(int i) {
	if(gBreakPointsSize >= gBreakPointsCapa) {
		reserve_bp();
	}
	gBreakPoints[gBreakPointsSize] = i;
	gBreakPointsSize++;
}

static bool include_bp(int t) {
	for(int i=0; i<gBreakPointsSize; i++) {
		if(gBreakPoints[i] == t) {
			return true;
		}
	}
	return false;
}

static void attach_bp(bc_Slot* self) {
	self->Count = gAll;
	if(include_bp(self->Count)) {
		if(ExistsFile(gDBF)) { bc_DeleteFile(gDBF); }
		abort();
	}
	gAll++;
}

static int save_bp() {
	FILE* fp = fopen(gDBF, "wb");
	int leaks = collect_leaks_bp(gMXHead);
	fwrite(&leaks, sizeof(int), 1, fp);
	write_bp(fp, gMXHead);
	if(leaks == 0) {
		printf("not detected memory leaks\n");
	} else {
		printf("detected memory leaks: %d\n", leaks);
	}
	printf("malloc/free: %d\n", gStack);
	fclose(fp);
	return leaks;
}

static int collect_leaks_bp(bc_Slot* self) {
	bc_Slot* iter = self;
	int sum = 0;
	while(iter != NULL) {
		sum += (iter->Size == 0 ? 0 : 1);
		iter = iter->Next;
	}
	return sum;
}

static void write_bp(FILE* fp, bc_Slot* self) {
	bc_Slot* iter = self;
	while(iter != NULL) {
		if(iter->Size == 0) {
			iter = iter->Next;
			continue;
		}
		int fnlen = strlen(iter->FileName) + 1;
		fwrite(&iter->Count, sizeof(int), 1, fp);
		fwrite(&iter->Lineno, sizeof(int), 1, fp);
		fwrite(&fnlen, sizeof(int), 1, fp);
		fwrite(iter->FileName, sizeof(char), fnlen, fp);
		iter = iter->Next;
	}
}

static void load_bp() {
	FILE* fp = fopen(gDBF, "rb");
	int leaks = 0;
	fread(&leaks, sizeof(int), 1, fp);
	for(int i=0; i<leaks; i++) {
		int count;
		int lineno;
		int fnlen;
		char* fn = NULL;
		fread(&count, sizeof(int), 1, fp);
		fread(&lineno, sizeof(int), 1, fp);
		fread(&fnlen, sizeof(int), 1, fp);
		fn = SafeMalloc(sizeof(char) * fnlen);
		memset(fn, '\0', fnlen);
		fread(fn, sizeof(char), fnlen, fp);
		printf("<%d> :%d: %s\n", count, lineno, fn);
		free(fn);
		push_bp(count);
	}
	fclose(fp);
}