#ifndef BEACON_IL_IL_STM_TRY_H
#define BEACON_IL_IL_STM_TRY_H
#include "../../util/vector.h"
#include "../../util/string_pool.h"
#include "../../env/generic_cache.h"
#include "../il_stmt_interface.h"

struct Enviroment;

typedef struct ILStatement_try {
	Vector* statement_list;
	Vector* catch_list;
} ILStatement_try;

typedef struct ILStatement_catch {
	GenericCache* fqcn;
	StringView namev;
	Vector* statement_list;
} ILStatement_catch;

ILStatement* WrapILTry(ILStatement_try* self);

ILStatement_try* NewILTry();

ILStatement_catch* NewILCatch(StringView namev);

void GenerateILTry(ILStatement_try* self, Enviroment* env, CallContext* cctx);

void GenerateILCatch(ILStatement_catch* self, Enviroment* env, CallContext* cctx);

void LoadILTry(ILStatement_try* self, Enviroment* env, CallContext* cctx);

void LoadILCatch(ILStatement_catch* self, Enviroment* env, CallContext* cctx);

void DeleteILCatch(ILStatement_catch* self);

void DeleteILTry(ILStatement_try* self);
#endif
