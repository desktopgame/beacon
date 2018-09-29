#ifndef BEACON_VM_YIELD_CONTEXT_H
#define BEACON_VM_YIELD_CONTEXT_H
#include "../util/vector.h"
struct object;

typedef struct yield_context {
	Vector* backup_ref_stack;
	Vector* backup_value_stack;
	Vector* vm_ref_stack;
	Vector* vm_value_stack;
	Vector* parameter_vec;
	struct object* source_obj;
	struct object* stock_obj;
	bool cached;
	int yield_count;
	int yield_offset;
	int len;
} yield_context;

#define NewYieldContext() (MallocYieldContext(__FILE__, __LINE__))
yield_context* MallocYieldContext(const char* filename, int lineno);

void ClearBackupYieldContext(yield_context* self);

void DeleteYieldContext(yield_context* self);
#endif