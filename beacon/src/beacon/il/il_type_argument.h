#ifndef SIGNAL_IL_IL_TYPE_ARGUMENT_H
#define SIGNAL_IL_IL_TYPE_ARGUMENT_H
#include "../env/generic_cache.h"
#include "../util/vector.h"

typedef struct il_type_argument {
	generic_cache* gcache;
} il_type_argument;

il_type_argument* il_type_argument_new();

void il_type_argument_print(vector* iltype_args);

void il_type_argument_delete(il_type_argument* self);
#endif