#ifndef BEACON_IL_IL_STMT_THROW_H
#define BEACON_IL_IL_STMT_THROW_H
#include "../il_factor_interface.h"
#include "../il_stmt_interface.h"

struct enviroment;

typedef struct il_stmt_throw {
	il_factor* fact;
} il_stmt_throw;

il_stmt* il_stmt_wrap_throw(il_stmt_throw* self);

il_stmt_throw* il_stmt_throw_new();

void il_stmt_throw_dump(il_stmt_throw* self, int depth);

void il_stmt_throw_generate(il_stmt_throw* self, struct enviroment* env);

void il_stmt_throw_load(il_stmt_throw* self, struct enviroment* env);

void il_stmt_throw_delete(il_stmt_throw* self);
#endif
