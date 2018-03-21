#include "il_factor_name_reference_impl.h"
#include "../../util/mem.h"
#include "../il_type_argument.h"
#include "il_factor_variable_impl.h"

//proto
static void il_factor_name_reference_find(il_factor_name_reference* self, struct enviroment* env, il_load_cache* cache, il_ehandler* eh);
static void il_factor_name_reference_delete_type_argument(vector_item item);

il_factor* il_factor_wrap_name_reference(il_factor_name_reference* self) {
	il_factor* ret = (il_factor*)MEM_MALLOC(sizeof(il_factor));
	ret->type = ilfactor_name_reference;
	ret->u.name_reference_ = self;
	self->parent = ret;
	return ret;
}

il_factor_name_reference* il_factor_name_reference_new() {
	il_factor_name_reference* ret = (il_factor_name_reference*)MEM_MALLOC(sizeof(il_factor_name_reference));
	ret->fqcn = generic_cache_new();
	ret->type_argument_list = vector_new();
	ret->parent = NULL;
	return ret;
}

void il_factor_name_reference_generate(il_factor_name_reference* self, struct enviroment* env, il_load_cache* cache) {
	il_factor_name_reference_find(self, env,cache, NULL);
	il_factor_generate(self->parent, env, cache);
	il_factor_name_reference_delete(self);
}

void il_factor_name_reference_load(il_factor_name_reference* self, struct enviroment* env, il_load_cache* cache, il_ehandler* eh) {
	il_factor_name_reference_find(self, env,cache, eh);
	il_factor_load(self->parent, env, cache, eh);
	il_factor_name_reference_delete(self);
}

generic_type* il_factor_name_reference_eval(il_factor_name_reference* self, struct enviroment* env, il_load_cache* cache) {
	il_factor_name_reference_find(self, env, cache, NULL);
	generic_type* ret = il_factor_eval(self->parent, env,cache);
	il_factor_name_reference_delete(self);
	return ret;
}

void il_factor_name_reference_delete(il_factor_name_reference* self) {
	generic_cache_delete(self->fqcn);
	vector_delete(self->type_argument_list, il_factor_name_reference_delete_type_argument);
	MEM_FREE(self);
}

//private
static void il_factor_name_reference_find(il_factor_name_reference* self, struct enviroment* env, il_load_cache* cache, il_ehandler* eh) {
	//名前空間付きで宣言されているなら
	if(self->fqcn->fqcn->scope_vec->length > 0) {
		//この時点で静的フィールドへのアクセスか
		//静的メソッドの呼び出しであることは明らかだが、
		//この時点では解決できない(より上位で解決する)
		return;
	}
	//変数名のみなら
	il_factor_variable* ilvar = il_factor_variable_new(self->fqcn->fqcn->name);
	//入れ替える
	vector_delete(ilvar->type_argument_list, vector_deleter_null);
	ilvar->type_argument_list = self->type_argument_list;
	self->type_argument_list = NULL;

	self->parent->type = ilfactor_variable;
	self->parent->u.variable_ = ilvar;
}


static void il_factor_name_reference_delete_type_argument(vector_item item) {
	il_type_argument* e = (il_type_argument*)item;
	il_type_argument_delete(e);
}
