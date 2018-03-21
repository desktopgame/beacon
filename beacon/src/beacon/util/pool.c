#include "pool.h"
#include "mem.h"

#undef MEM_MALLOC
#undef MEM_REALLOC
#undef MEM_FREE

#define MEM_MALLOC(size) (malloc(size))
#define MEM_REALLOC(block, size) (realloc(block, size))
#define MEM_FREE(block) free(block)

//proto
static pool* pool_add(pool* self);

static const int gPoolSize = 1024;

pool * pool_new() {
	pool* ret = (pool*)MEM_MALLOC(sizeof(pool));
	ret->cursor = 0;
	ret->memory = MEM_MALLOC(gPoolSize);
	ret->prev = NULL;
	ret->next;
	return ret;
}

void * pool_ref(pool* self, size_t size) {
	if (size >= gPoolSize) {
		return NULL;
	}
	if (self->cursor + size >= gPoolSize) {
		return pool_ref(pool_add(self), size);
	}
	void* block = self->memory;
	self->cursor += size;
	return block;
}
//private
static pool* pool_add(pool* self) {
	if (self->next != NULL) {
		return pool_add(self);
	}
	pool* ret = pool_new();
	self->next = ret;
	ret->prev = self;
	return ret;
}
