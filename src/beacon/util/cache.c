#include "cache.h"
#include <assert.h>
#include "mem.h"

static bc_Cache* bc_malloc_cache();
static bc_Cache* bc_reserve_cache(bc_Cache* tail, int count);

bc_Cache* bc_NewCache(int capacity) {
        assert(capacity != 0);
        bc_Cache* ret = bc_malloc_cache();
        bc_Cache* iter = ret;
        for (int i = 0; i < capacity; i++) {
                iter->Next = bc_malloc_cache();
                iter = iter->Next;
        }
        return ret;
}

void bc_StoreCache(bc_Cache* self, void* data) {
        // assert(data != NULL);
        bc_Cache* iter = self;
        bc_Cache* last = iter;
        int count = 0;
        while (iter != NULL) {
                if (iter->Data == NULL) {
                        iter->Data = data;
                        break;
                }
                count++;
                last = iter;
                iter = iter->Next;
        }
        if (iter == NULL) {
                iter = bc_reserve_cache(last, (count / 2) + 1);
                iter->Data = data;
        }
}

void bc_EraseCache(bc_Cache* self, void* data) {
        bc_Cache* iter = self;
        while (iter != NULL) {
                if (iter->Data == data) {
                        iter->Data = NULL;
                        break;
                }
                iter = iter->Next;
        }
}

void bc_EraseCacheAll(bc_Cache* self) {
        bc_Cache* iter = self;
        while (iter != NULL) {
                iter->Data = NULL;
                iter = iter->Next;
        }
}

void bc_DeleteCache(bc_Cache* self, bc_CacheDataDeleter deleter) {
        bc_Cache* iter = self;
        while (iter != NULL) {
                bc_Cache* next = iter->Next;
                deleter(iter->Data);
                MEM_FREE(iter);
                iter = next;
        }
}
// private
static bc_Cache* bc_malloc_cache() {
        bc_Cache* ret = MEM_MALLOC(sizeof(bc_Cache));
        ret->Next = NULL;
        ret->Data = NULL;
        return ret;
}

static bc_Cache* bc_reserve_cache(bc_Cache* tail, int count) {
        assert(count != 0);
        //先頭を返す
        bc_Cache* next = bc_malloc_cache();
        bc_Cache* iter = next;
        tail->Next = next;
        count--;
        if (count <= 0) {
                return next;
        }
        while (count > 0) {
                count--;
                bc_Cache* temp = bc_malloc_cache();
                iter->Next = temp;
                iter = temp;
        }
        return next;
}