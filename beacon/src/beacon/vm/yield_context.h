#ifndef BEACON_VM_YIELD_CONTEXT_H
#define BEACON_VM_YIELD_CONTEXT_H
#include "../util/vector.h"
struct object;

typedef struct yield_context {
	vector* backup_ref_stack;
	vector* backup_value_stack;
	vector* vm_ref_stack;
	vector* vm_value_stack;
	vector* parameter_vec;
	struct object* source_obj;
	struct object* stock_obj;
	bool cached;
	int yield_count;
	int yield_offset;
	int len;
} yield_context;

#define yield_context_new() (yield_context_malloc(__FILE__, __LINE__))
yield_context* yield_context_malloc(const char* filename, int lineno);

void yield_context_clear_backup(yield_context* self);

void yield_context_delete(yield_context* self);
#endif