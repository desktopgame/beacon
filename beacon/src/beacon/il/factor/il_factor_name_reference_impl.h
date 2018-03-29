#ifndef BEACON_IL_IL_FACTOR_NAME_REFERENCE_H
#define BEACON_IL_IL_FACTOR_NAME_REFERENCE_H
#include "../../env/generic_cache.h"
#include "../../util/vector.h"
#include "../il_factor_interface.h"

struct enviroment;

typedef struct il_factor_name_reference {
	il_factor* parent;
	generic_cache* fqcn;
	vector* type_argument_list;
} il_factor_name_reference;

il_factor* il_factor_wrap_name_reference(il_factor_name_reference* self);

il_factor_name_reference* il_factor_name_reference_new();

void il_factor_name_reference_generate(il_factor_name_reference* self, struct enviroment* env, il_load_cache* cache);

void il_factor_name_reference_load(il_factor_name_reference* self, struct enviroment* env, il_load_cache* cache, il_ehandler* eh);

generic_type* il_factor_name_reference_eval(il_factor_name_reference* self, struct enviroment* env, il_load_cache* cache);

void il_factor_name_reference_delete(il_factor_name_reference* self);
#endif
