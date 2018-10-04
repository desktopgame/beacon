#include "string_pool.h"
#include "tree_map.h"
#include "vector.h"
#include "text.h"
#include "mem.h"
#include "string_buffer.h"
#include <assert.h>

static tree_map* gMap = NULL;
static Vector* gVec = NULL;

#define HEADER (2)

void InitStringPool() {
	assert(gMap == NULL);
	assert(gVec == NULL);
	gMap = NewTreeMap();
	gVec = NewVector();
}

string_view InternString(const char* str) {
	assert(gMap != NULL);
	assert(gVec != NULL);
	tree_map* cell = GetTreeMapCell(gMap, str);
	if(cell == NULL) {
		cell = PutTreeMap(gMap, str, (void*)(gVec->length + HEADER));
		PushVector(gVec, cell->key);
	}
	if(cell == gMap) {
		return ZERO_VIEW;
	}
	assert(cell->item != 0);
	return (string_view)cell->item;
}

string_view InternString2(string_buffer* buffer) {
	char* raw = ReleaseBuffer(buffer);
	string_view sv = InternString(raw);
	MEM_FREE(raw);
	assert(sv != 0);
	return sv;
}

string_view ConcatIntern(const char* head, string_view foot) {
	//連結する
	const char* footstr = Ref2Str(foot);
	string_buffer* buf = NewBuffer();
	AppendsBuffer(buf, head);
	AppendsBuffer(buf, footstr);
	char* retstr = ReleaseBuffer(buf);
	string_view ret = InternString(retstr);
	MEM_FREE(retstr);
	return ret;
}

string_view Str2Ref(const char* str) {
	tree_map* cell = GetTreeMapCell(gMap, str);
	if(cell == gMap) {
		return ZERO_VIEW;
	}
	return (string_view)cell->item;
}

const char* Ref2Str(string_view ref) {
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
	for(int i=0; i<gVec->length; i++) {
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