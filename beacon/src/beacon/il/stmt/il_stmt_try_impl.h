#ifndef BEACON_IL_IL_STMT_TRY_H
#define BEACON_IL_IL_STMT_TRY_H
#include "../../util/vector.h"
#include "../../env/generic_cache.h"
#include "../il_stmt_interface.h"

struct enviroment;

typedef struct il_stmt_try {
	vector* statement_list;
	vector* catch_list;
} il_stmt_try;

typedef struct il_stmt_catch {
	generic_cache* fqcn;
	char* name;
	vector* statement_list;
} il_stmt_catch;

il_stmt* il_stmt_wrap_try(il_stmt_try* self);

il_stmt_try* il_stmt_try_new();

il_stmt_catch* il_stmt_catch_new(const char* name);

void il_stmt_try_dump(il_stmt_try* self, int depth);

void il_stmt_catch_dump(il_stmt_catch* self, int depth);

void il_stmt_try_generate(il_stmt_try* self, struct enviroment* env);

void il_stmt_catch_generate(il_stmt_catch* self, struct enviroment* env);

void il_stmt_try_load(il_stmt_try* self, struct enviroment* env);

void il_stmt_catch_load(il_stmt_catch* self, struct enviroment* env);

void il_stmt_catch_delete(il_stmt_catch* self);

void il_stmt_try_delete(il_stmt_try* self);
#endif
