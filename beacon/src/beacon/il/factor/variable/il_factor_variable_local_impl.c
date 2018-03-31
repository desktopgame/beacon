#include "il_factor_variable_local_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../env/generic_type.h"
#include "../../../vm/enviroment.h"
#include "../../../vm/symbol_entry.h"

il_factor_variable_local* il_factor_variable_local_new(const char* name) {
	il_factor_variable_local* ret = (il_factor_variable_local*)MEM_MALLOC(sizeof(il_factor_variable_local));
	ret->name = text_strdup(name);
	ret->entry = NULL;
	ret->type_args = NULL;
	return ret;
}

void il_factor_variable_local_generate(il_factor_variable_local* self, enviroment* env, il_load_cache* cache) {
	opcode_buf_add(env->buf, (vector_item)op_load);
	opcode_buf_add(env->buf, (vector_item)self->entry->index);
}

void il_factor_variable_local_load(il_factor_variable_local * self, enviroment * env, il_load_cache* cache, il_ehandler* eh) {

}

generic_type* il_factor_variable_local_eval(il_factor_variable_local * self, enviroment * env, il_load_cache* cache) {
	return self->entry->gtype;
}

void il_factor_variable_local_delete(il_factor_variable_local* self) {
	MEM_FREE(self->name);
	MEM_FREE(self);
}