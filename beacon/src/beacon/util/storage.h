#ifndef BEACON_UTIL_STORAGE_H
#define BEACON_UTIL_STORAGE_H
#include <stdlib.h>
/*
typedef uintptr_t UnitTag;

typedef struct Unit {
	#if DEBUG
	const char* FileName;
	int Lineno;
	#endif
	void* Memory;
	size_t UserSize;
	struct Unit* Next;
} Unit;

typedef struct Storage {
	Unit* Head;
	void* Pool;
	size_t PoolSize;
	struct Storage* Next;
} Storage;

#define NewStorage1024() (NewStorage(1024))
Storage* NewStorage(size_t pool_size);

#define Keep(self, keep_size) (keep(self, keep_size, __FILE__, __LINE__))
void* keep(Storage* self, size_t keep_size, const char* filename, int lineno);

#define ReSize(self, area, new_size) (re_size(self, area, new_size, __FILE__, __LINE__))
void* re_size(Storage* self, void* area, size_t new_size, const char* filename, int lineno);

#define UnKeep(self, area) (un_keep(self, area, __FILE__, __LINE__))
void un_keep(Storage* self, void* area, const char* filename, int lineno);

Unit* PtrToUnit(void* area);

void SetUnitFileName(Unit* self, const char* filename);

const char* GetUnitFileName(Unit* self);

void SetUnitLineno(Unit* self, int lineno);

int GetUnitLineno(Unit* self);

size_t GetKeepSize(Storage* self);

void DeleteStorage(Storage* self);
 */
#endif