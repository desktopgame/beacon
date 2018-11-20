#include "storage.h"
#include <stdlib.h>
#include <string.h>
/*
static void* safe_malloc(size_t size);
static Unit* new_unit(Storage* self, size_t size, const char* filename, int lineno);
static void get_next_storage(Storage* self, size_t size);
static void set_unit_tag(Unit* self, UnitTag tag);
static UnitTag get_unit_tag(Unit* self);

Storage* NewStorage(size_t pool_size) {
	Storage* ret = safe_malloc(sizeof(Storage));
	ret->Head = NULL;
	ret->Pool = safe_malloc(pool_size);
	ret->PoolSize = pool_size;
	ret->Next = NULL;
	return ret;
}

void* keep(Storage* self, size_t keep_size, const char* filename, int lineno) {
	//このストレージは満タン
	if((GetKeepSize(self) + keep_size + sizeof(UnitTag)) >= self->PoolSize) {
		get_next_storage(self, keep_size);
		return keep(self->Next, keep_size, filename, lineno);
	}
	Unit* u = new_unit(self, keep_size, filename, lineno);
	return NULL;
}

void* re_size(Storage* self, void* area, size_t new_size, const char* filename, int lineno) {
	return NULL;
}

void un_keep(Storage* self, void* area, const char* filename, int lineno) {
}

void SetUnitFileName(Unit* self, const char* filename) {
	#if DEBUG
	self->FileName = filename;
	#endif
}

const char* GetUnitFileName(Unit* self) {
	#if DEBUG
	return self->FileName;
	#else
	return NULL;
	#endif
}

void SetUnitLineno(Unit* self, int lineno) {
	#if DEBUG
	self->Lineno = lineno;
	#endif
}

int GetUnitLineno(Unit* self) {
	#if DEBUG
	return self->Lineno;
	#else
	return -1;
	#endif
}

size_t GetKeepSize(Storage* self) {
	Unit* ptr = self->Head;
	size_t sum = 0;
	while(ptr != NULL) {
		sum += (ptr->UserSize + sizeof(UnitTag));
		ptr = ptr->Next;
	}
	return sum;
}

void DeleteStorage(Storage* self) {
}
//private
static void* safe_malloc(size_t size) {
	void* ret = malloc(size);
	if(ret == NULL) {
		abort();
	}
	return ret;
}

static Unit* new_unit(Storage* self, size_t size, const char* filename, int lineno) {
	//位置情報設定
	Unit* ret = safe_malloc(sizeof(Unit));
	SetUnitFileName(ret, filename);
	SetUnitLineno(ret, lineno);
	ret->Next = NULL;
	//pool_atの一番最後までいく
	unsigned char* pool_at = (unsigned char*)self->Pool;
	pool_at += GetKeepSize(self);
	//タグをつける
	ret->Memory = (void*)pool_at;
	ret->UserSize = size;
	set_unit_tag(ret, (UnitTag)ret);
	return ret;
}

static void get_next_storage(Storage* self, size_t size) {
	//reallocでは先頭ポインタが変わってしまう
	//->Unitが壊れる
	if(self->Next != NULL) { return; }
	size_t alloc = self->PoolSize;
	if(size > alloc) {
		alloc = size;
	}
	Storage* next = NewStorage(alloc);
	self->Next = next;
}

static void set_unit_tag(Unit* self, UnitTag tag) {
	unsigned char* raw = (unsigned char*)self->Memory;
	unsigned char* area = (raw + self->UserSize);
	void* varea = (void*)area;
	*((UnitTag*)varea) = tag;
}

static UnitTag get_unit_tag(Unit* self) {
	unsigned char* raw = (unsigned char*)self->Memory;
	unsigned char* area = (raw + self->UserSize);
	return *((UnitTag*)area);
}
 * */