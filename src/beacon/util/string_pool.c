#include "string_pool.h"
#include <assert.h>
#include <glib.h>
#include "mem.h"
#include "text.h"
#include "tree_map.h"
#include "vector.h"

static bc_TreeMap* gMap = NULL;
static bc_Vector* gVec = NULL;
static GRecMutex gPMtx;

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
        g_rec_mutex_lock(&gPMtx);
        bc_TreeMap* cell = bc_GetTreeMapCell(gMap, str);
        if (cell == NULL) {
                cell = bc_PutTreeMap(gMap, str, (void*)(gVec->Length + HEADER));
                bc_PushVector(gVec, cell->Key);
        }
        if (cell == gMap) {
                g_rec_mutex_unlock(&gPMtx);
                return BC_ZERO_VIEW;
        }
        assert(cell->Item != 0);
        bc_StringView ret = (bc_StringView)cell->Item;
        g_rec_mutex_unlock(&gPMtx);
        return ret;
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
        g_rec_mutex_lock(&gPMtx);
        bc_TreeMap* cell = bc_GetTreeMapCell(gMap, str);
        if (cell == gMap) {
                g_rec_mutex_unlock(&gPMtx);
                return BC_ZERO_VIEW;
        }
        bc_StringView ret = (bc_StringView)cell->Item;
        g_rec_mutex_unlock(&gPMtx);
        return ret;
}

const char* bc_Ref2Str(bc_StringView ref) {
        g_rec_mutex_lock(&gPMtx);
        if (ref == BC_NULL_VIEW) {
                g_rec_mutex_unlock(&gPMtx);
                return NULL;
        }
        if (ref == BC_ZERO_VIEW) {
                g_rec_mutex_unlock(&gPMtx);
                return "";
        }
        const char* str = (const char*)bc_AtVector(gVec, ref - HEADER);
        g_rec_mutex_unlock(&gPMtx);
        return str;
}

void bc_DumpStringPool(FILE* fp) {
        g_rec_mutex_lock(&gPMtx);
        assert(gMap != NULL);
        assert(gVec != NULL);
        fprintf(fp, "string pool---\n");
        for (int i = 0; i < gVec->Length; i++) {
                char* e = (char*)bc_AtVector(gVec, i);
                fprintf(fp, "    [%d] = %s\n", i, e);
        }
        g_rec_mutex_unlock(&gPMtx);
}

void bc_DestroyStringPool() {
        bc_DeleteTreeMap(gMap, bc_TreeMapDeleterOfNull);
        bc_DeleteVector(gVec, bc_VectorDeleterOfNull);
        gMap = NULL;
        gVec = NULL;
}
#undef HEADER