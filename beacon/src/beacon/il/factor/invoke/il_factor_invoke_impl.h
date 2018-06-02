#ifndef BEACON_IL_IL_FACTOR_INVOKE_H
#define BEACON_IL_IL_FACTOR_INVOKE_H
#include "../../il_factor_interface.h"
struct enviroment;
struct generic_type;
struct method;

typedef struct il_factor_invoke {
	il_factor* receiver;
	vector* args;
	vector* type_args;
	char* name;
	int index;
	struct method* m;
	struct generic_type* resolved;
} il_factor_invoke;

il_factor_invoke* il_factor_invoke_new(const char* name);

void il_factor_invoke_dump(il_factor_invoke* self, int depth);

void il_factor_invoke_generate(il_factor_invoke* self, struct enviroment* env);

void il_factor_invoke_load(il_factor_invoke * self, struct enviroment * env);

struct generic_type* il_factor_invoke_eval(il_factor_invoke * self, struct enviroment * env);

char* il_factor_invoke_tostr(il_factor_invoke* self, struct enviroment* env);

void il_factor_invoke_delete(il_factor_invoke* self);
#endif