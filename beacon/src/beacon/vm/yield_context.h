#ifndef BEACON_VM_YIELD_CONTEXT_H
#define BEACON_VM_YIELD_CONTEXT_H
#include "../util/vector.h"
struct object;

typedef struct YieldContext {
	Vector* BackupVariableTable;
	Vector* BackupValueStack;
	Vector* VariableTable;
	Vector* ValueStack;
	Vector* Parameters;
	struct object* Source;
	struct object* Stock;
	bool IsCached;
	int YieldCount;
	int YieldOffset;
	int Length;
} YieldContext;

#define NewYieldContext() (MallocYieldContext(__FILE__, __LINE__))
YieldContext* MallocYieldContext(const char* filename, int lineno);

void ClearBackupYieldContext(YieldContext* self);

void DeleteYieldContext(YieldContext* self);
#endif