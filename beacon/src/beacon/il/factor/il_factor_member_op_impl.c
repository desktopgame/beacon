#include "il_factor_member_op_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../util/xassert.h"
#include "../../env/generic_cache.h"
#include "../../env/type_interface.h"
#include "../../env/type/class_impl.h"
#include "../../env/field.h"
#include "../../env/class_loader.h"
#include "../../env/import_manager.h"
#include "../../vm/enviroment.h"
#include "../../il/il_type_argument.h"
#include "../../il/il_factor_impl.h"

//proto
static void il_factor_member_op_check(il_factor_member_op* self, enviroment* env);
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
	ret->index = -1;
	return ret;
}

void il_factor_member_op_dump(il_factor_member_op* self, int depth) {
	text_putindent(depth);
	text_printfln("member %s", self->name);
	il_factor_dump(self->fact, depth + 1);
	for(int i=0; i<self->type_args->length; i++) {
		generic_cache* e = (generic_cache*)vector_at(self->type_args, i);
		generic_cache_dump(e, depth + 1);
	}
}

void il_factor_member_op_load(il_factor_member_op* self, enviroment* env) {
	il_factor_load(self->fact, env, ilctx);
	il_factor_member_op_check(self, env, ilctx);
}

void il_factor_member_op_generate(il_factor_member_op* self, enviroment* env) {
	if(modifier_is_static(self->f->modifier)) {
		opcode_buf_add(env->buf, op_get_static);
		opcode_buf_add(env->buf, self->f->parent->absolute_index);
		opcode_buf_add(env->buf, self->index);
	} else {
		il_factor_generate(self->fact, env, ilctx);
		opcode_buf_add(env->buf, op_get_field);
		opcode_buf_add(env->buf, self->index);
	}
}

generic_type* il_factor_member_op_eval(il_factor_member_op* self, enviroment* env) {
	il_factor_member_op_check(self, env, ilctx);
//	XSTREQ(self->name, "charArray");
	assert(self->fact != NULL);
	if(self->f->gtype->tag == generic_type_tag_none) {
		generic_type* a = self->f->gtype;
		return a;
	}
	generic_type* a = il_factor_eval(self->fact, env, ilctx);
	return vector_at(a->type_args_list, self->f->gtype->virtual_type_index);
}

char* il_factor_member_op_tostr(il_factor_member_op* self, enviroment* env) {
	string_buffer* sb = string_buffer_new();
	char* name = il_factor_tostr(self->fact, env, ilctx);
	string_buffer_appends(sb, name);
	string_buffer_append(sb, '.');
	string_buffer_appends(sb, self->name);
	MEM_FREE(name);
	return string_buffer_release(sb);
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
static void il_factor_member_op_check(il_factor_member_op* self, enviroment* env) {
	if(self->index != -1) {
		return;
	}
	//XSTREQ(self->name, "charArray");
	il_factor* fact = self->fact;
	generic_type* gtype = il_factor_eval(fact, env, ilctx);
	//ファクターから型が特定できない場合は
	//変数めいを型として静的フィールドで解決する
	if(gtype == NULL) {
		il_factor_variable* ilvar = IL_FACT2VAR(fact);
		generic_type* ref = import_manager_resolvef(ilctx->class_loader_ref->import_manager, ILCTX_NAMESPACE(ilctx), ilvar->u.static_->fqcn, ilctx);
		gtype = ref;

		type* ccT = gtype->core_type;
		assert(ccT->tag == type_class);
		int temp = -1;
		self->f = class_find_sfield_tree(TYPE2CLASS(ccT), self->name, &temp);
		self->index = temp;
		assert(self->f != NULL);
		assert(temp != -1);
		return;
	}
	//インスタンスフィールドを検索
	type* ctype = gtype->core_type;
	assert(ctype->tag == type_class);
	int temp = -1;
	self->f = class_find_field_tree(TYPE2CLASS(ctype), self->name, &temp);
	self->index = temp;
	assert(self->f != NULL);
	assert(temp != -1);
}

static void il_factor_member_op_typearg_delete(vector_item item) {
//	generic_cache* e = (generic_cache*)item;
//	generic_cache_delete(e);
	il_type_argument* e = (il_type_argument*)item;
	il_type_argument_delete(e);
}