#include "string_pool.h"
#include "tree_map.h"
#include "vector.h"
#include "text.h"
#include "mem.h"
#include "string_buffer.h"
#include <assert.h>

static tree_map* gMap = NULL;
static vector* gVec = NULL;
static void string_pool_string_delete(vector_item item);

#define HEADER (2)

void string_pool_init() {
	assert(gMap == NULL);
	assert(gVec == NULL);
	gMap = tree_map_new();
	gVec = vector_new();
}

string_view string_pool_intern(const char* str) {
	assert(gMap != NULL);
	assert(gVec != NULL);
	tree_map* cell = tree_map_cell(gMap, str);
	if(cell == NULL) {
		cell = tree_map_put(gMap, str, (void*)(gVec->length + HEADER));
		vector_push(gVec, text_strdup(str));
	}
	if(cell == gMap) {
		return ZERO_VIEW;
	}
	assert(cell->item != 0);
	return (string_view)cell->item;
}

string_view string_pool_intern2(string_buffer* buffer) {
	char* raw = string_buffer_release(buffer);
	string_view sv = string_pool_intern(raw);
	MEM_FREE(raw);
	assert(sv != 0);
	return sv;
}

string_view string_pool_str2ref(const char* str) {
	tree_map* cell = tree_map_cell(gMap, str);
	if(cell == gMap) {
		return ZERO_VIEW;
	}
	return (string_view)cell->item;
}

const char* string_pool_ref2str(string_view ref) {
	if(ref == ZERO_VIEW) {
		return "";
	}
	assert(ref != 0);
	const char* str = (const char*)vector_at(gVec, ref - HEADER);
	return str;
}

void string_pool_dump(FILE* fp) {
	assert(gMap != NULL);
	assert(gVec != NULL);
	fprintf(fp, "string pool---\n");
	for(int i=0; i<gVec->length; i++) {
		char* e = (char*)vector_at(gVec, i);
		fprintf(fp, "    [%d] = %s\n", i, e);
	}
}

void string_pool_destroy() {
	tree_map_delete(gMap, tree_map_deleter_null);
	vector_delete(gVec, string_pool_string_delete);
	gMap = NULL;
	gVec = NULL;
}
//private
static void string_pool_string_delete(vector_item item) {
	char* e = (char*)item;
	MEM_FREE(e);
}
#undef HEADER