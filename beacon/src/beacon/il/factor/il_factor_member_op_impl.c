#include "il_factor_member_op_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/generic_cache.h"

//proto
static void il_factor_member_op_typearg_delete(vector_item item);

il_factor* il_factor_wrap_member_op(il_factor_member_op* self) {
	il_factor* ret = (il_factor*)MEM_MALLOC(sizeof(il_factor));
	ret->type = ilfactor_member_op;
	ret->u.member_ = self;
	return ret;
}

il_factor_member_op* il_factor_member_op_new(const char* name) {
	il_factor_member_op* ret = (il_factor_member_op*)MEM_MALLOC(sizeof(il_factor_member_op));
	ret->fact = NULL;
	ret->type_args = vector_new();
	ret->name = text_strdup(name);
	return ret;
}

void il_factor_member_op_dump(il_factor_member_op* self, int depth) {

}

void il_factor_member_op_load(il_factor_member_op* self, struct enviroment* env, il_load_cache* cache, il_ehandler* eh) {

}

void il_factor_member_op_generate(il_factor_member_op* self, struct enviroment* env, il_load_cache* cache) {

}

generic_type* il_factor_member_op_eval(il_factor_member_op* self, struct enviroment* env, il_load_cache* cache) {
	return NULL;
}

void il_factor_member_op_delete(il_factor_member_op* self) {
	il_factor_delete(self->fact);
	vector_delete(self->type_args, il_factor_member_op_typearg_delete);
	MEM_FREE(self->name);
	MEM_FREE(self);
}

il_factor_member_op* il_factor_cast_member_op(il_factor* fact) {
	assert(fact->type == ilfactor_member_op);
	return fact->u.member_;
}
//private
static void il_factor_member_op_typearg_delete(vector_item item) {
	generic_cache* e = (generic_cache*)item;
	generic_cache_delete(e);
}