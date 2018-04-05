#include "il_factor_member_op_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../util/xassert.h"
#include "../../env/generic_cache.h"
#include "../../env/type_interface.h"
#include "../../env/type/class_impl.h"
#include "../../env/field.h"
#include "../../vm/enviroment.h"

//proto
static void il_factor_member_op_check(il_factor_member_op* self, enviroment* env, il_context* ilctx);
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
	text_printf("member %s", self->name);
	il_factor_dump(self->fact, depth + 1);
	for(int i=0; i<self->type_args->length; i++) {
		generic_cache* e = (generic_cache*)vector_at(self->type_args, i);
		generic_cache_dump(e, depth + 1);
	}
}

void il_factor_member_op_load(il_factor_member_op* self, enviroment* env, il_context* ilctx, il_ehandler* eh) {
	il_factor_load(self->fact, env, ilctx, eh);
	il_factor_member_op_check(self, env, ilctx);
}

void il_factor_member_op_generate(il_factor_member_op* self, enviroment* env, il_context* ilctx) {
	il_factor_generate(self->fact, env, ilctx);
	opcode_buf_add(env->buf, op_get_field);
	opcode_buf_add(env->buf, self->index);
}

generic_type* il_factor_member_op_eval(il_factor_member_op* self, enviroment* env, il_context* ilctx) {
	il_factor_member_op_check(self, env, ilctx);
//	XSTREQ(self->name, "charArray");
	assert(self->fact != NULL);
	if(self->f->vtype.tag == virtualtype_default) {
		generic_type* a = self->f->vtype.u.gtype;
		if(a->type_args_list->length > 0) {
			generic_type* cc = (generic_type*)vector_at(a->type_args_list, 0);
			int xx = 0;
		}
		return self->f->vtype.u.gtype;
	}
	generic_type* a = il_factor_eval(self->fact, env, ilctx);
	return vector_at(a->type_args_list, self->f->vtype.u.index);
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
static void il_factor_member_op_check(il_factor_member_op* self, enviroment* env, il_context* ilctx) {
	if(self->index != -1) {
		return;
	}
	//XSTREQ(self->name, "charArray");
	il_factor* fact = self->fact;
	generic_type* gtype = il_factor_eval(fact, env, ilctx);
	type* ctype = gtype->core_type;
	assert(ctype->tag == type_class);
	int temp = -1;
	self->f = class_find_field_tree(TYPE2CLASS(ctype), self->name, &temp);
	self->index = temp;
	if(self->f->vtype.tag == virtualtype_default) {
		generic_type* a = self->f->vtype.u.gtype;
		int aa = 0;
	}
	assert(temp != -1);
}

static void il_factor_member_op_typearg_delete(vector_item item) {
	generic_cache* e = (generic_cache*)item;
	generic_cache_delete(e);
}