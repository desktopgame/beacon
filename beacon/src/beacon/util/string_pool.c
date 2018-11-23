#include "string_pool.h"
#include <assert.h>
#include "mem.h"
#include "text.h"
#include "tree_map.h"
#include "vector.h"

static bc_TreeMap* gMap = NULL;
static bc_Vector* gVec = NULL;

#define HEADER (2)

void bc_InitStringPool() {
        assert(gMap == NULL);
        assert(gVec == NULL);
        gMap = bc_NewTreeMap();
        gVec = bc_NewVector();
}

bc_StringView bc_InternString(const char* str) {
        assert(gMap != NULL);
        assert(gVec != NULL);
        bc_TreeMap* cell = bc_GetTreeMapCell(gMap, str);
        if (cell == NULL) {
                cell = bc_PutTreeMap(gMap, str, (void*)(gVec->Length + HEADER));
                bc_PushVector(gVec, cell->Key);
        }
        if (cell == gMap) {
                return BC_ZERO_VIEW;
        }
        assert(cell->Item != 0);
        return (bc_StringView)cell->Item;
}

bc_StringView bc_InternString2(bc_Buffer* buffer) {
        char* raw = bc_ReleaseBuffer(buffer);
        bc_StringView sv = bc_InternString(raw);
        MEM_FREE(raw);
        assert(sv != 0);
        return sv;
}

bc_StringView bc_ConcatIntern(const char* head, bc_StringView foot) {
        //連結する
        const char* footstr = bc_Ref2Str(foot);
        bc_Buffer* buf = bc_NewBuffer();
        bc_AppendsBuffer(buf, head);
        bc_AppendsBuffer(buf, footstr);
        char* retstr = bc_ReleaseBuffer(buf);
        bc_StringView ret = bc_InternString(retstr);
        MEM_FREE(retstr);
        return ret;
}

bc_StringView bc_Str2Ref(const char* str) {
        bc_TreeMap* cell = bc_GetTreeMapCell(gMap, str);
        if (cell == gMap) {
                return BC_ZERO_VIEW;
        }
        return (bc_StringView)cell->Item;
}

const char* bc_Ref2Str(bc_StringView ref) {
        if (ref == BC_NULL_VIEW) {
                return NULL;
        }
        if (ref == BC_ZERO_VIEW) {
                return "";
        }
        const char* str = (const char*)bc_AtVector(gVec, ref - HEADER);
        return str;
}

void bc_DumpStringPool(FILE* fp) {
        assert(gMap != NULL);
        assert(gVec != NULL);
        fprintf(fp, "string pool---\n");
        for (int i = 0; i < gVec->Length; i++) {
                char* e = (char*)bc_AtVector(gVec, i);
                fprintf(fp, "    [%d] = %s\n", i, e);
        }
}

void bc_DestroyStringPool() {
        bc_DeleteTreeMap(gMap, bc_TreeMapDeleterOfNull);
        bc_DeleteVector(gVec, bc_VectorDeleterOfNull);
        gMap = NULL;
        gVec = NULL;
}
#undef HEADER