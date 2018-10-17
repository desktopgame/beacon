#include "string_pool.h"
#include "tree_map.h"
#include "vector.h"
#include "text.h"
#include "mem.h"
#include <assert.h>

static TreeMap* gMap = NULL;
static Vector* gVec = NULL;

#define HEADER (2)

void InitStringPool() {
	assert(gMap == NULL);
	assert(gVec == NULL);
	gMap = NewTreeMap();
	gVec = NewVector();
}

StringView InternString(const char* str) {
	assert(gMap != NULL);
	assert(gVec != NULL);
	TreeMap* cell = GetTreeMapCell(gMap, str);
	if(cell == NULL) {
		cell = PutTreeMap(gMap, str, (void*)(gVec->Length + HEADER));
		PushVector(gVec, cell->Key);
	}
	if(cell == gMap) {
		return ZERO_VIEW;
	}
	assert(cell->Item != 0);
	return (StringView)cell->Item;
}

StringView InternString2(Buffer* buffer) {
	char* raw = ReleaseBuffer(buffer);
	StringView sv = InternString(raw);
	MEM_FREE(raw);
	assert(sv != 0);
	return sv;
}

StringView ConcatIntern(const char* head, StringView foot) {
	//連結する
	const char* footstr = Ref2Str(foot);
	Buffer* buf = NewBuffer();
	AppendsBuffer(buf, head);
	AppendsBuffer(buf, footstr);
	char* retstr = ReleaseBuffer(buf);
	StringView ret = InternString(retstr);
	MEM_FREE(retstr);
	return ret;
}

StringView Str2Ref(const char* str) {
	TreeMap* cell = GetTreeMapCell(gMap, str);
	if(cell == gMap) {
		return ZERO_VIEW;
	}
	return (StringView)cell->Item;
}

const char* Ref2Str(StringView ref) {
	if(ref == NULL_VIEW) {
		return NULL;
	}
	if(ref == ZERO_VIEW) {
		return "";
	}
	const char* str = (const char*)AtVector(gVec, ref - HEADER);
	return str;
}

void DumpStringPool(FILE* fp) {
	assert(gMap != NULL);
	assert(gVec != NULL);
	fprintf(fp, "string pool---\n");
	for(int i=0; i<gVec->Length; i++) {
		char* e = (char*)AtVector(gVec, i);
		fprintf(fp, "    [%d] = %s\n", i, e);
	}
}

void DestroyStringPool() {
	DeleteTreeMap(gMap, TreeMapDeleterOfNull);
	DeleteVector(gVec, VectorDeleterOfNull);
	gMap = NULL;
	gVec = NULL;
}
#undef HEADER