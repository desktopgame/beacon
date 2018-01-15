#include "il_factor_static_field_access_impl.h"
#include "../../util/mem.h"
#include "../../env/type_interface.h"
#include "../../env/type_impl.h"
#include "../../env/field.h"
#include "../../util/text.h"
#include <stdio.h>
#include <assert.h>

//proto
static void il_factor_static_field_access_find(il_factor_static_field_access * self, enviroment * env);

il_factor * il_factor_wrap_static_field_access(il_factor_static_field_access * self) {
	il_factor* ret = (il_factor*)MEM_MALLOC(sizeof(il_factor));
	ret->type = ilfactor_static_field_access;
	ret->u.static_field_access = self;
	return ret;
}

il_factor_static_field_access * il_factor_static_field_access_new(const char* name) {
	il_factor_static_field_access* ret = (il_factor_static_field_access*)MEM_MALLOC(sizeof(il_factor_static_field_access));
	ret->fqcn = fqcn_cache_new();
	ret->name = text_strdup(name);
	ret->f = NULL;
	ret->fieldIndex = -1;
	return ret;
}

void il_factor_static_field_access_dump(il_factor_static_field_access * self, int depth) {
	text_putindent(depth);
	printf("static field access(%s.%s)",type_name(self->f->parent), self->f->name);
	text_putline();
}

void il_factor_static_field_access_generate(il_factor_static_field_access * self, enviroment * env) {
	il_factor_static_field_access_find(self, env);
	opcode_buf_add(env->buf, (vector_item)op_get_static);
	opcode_buf_add(env->buf, (vector_item)self->f->parent->absoluteIndex);
	opcode_buf_add(env->buf, (vector_item)self->fieldIndex);
}

type * il_factor_static_field_access_eval(il_factor_static_field_access * self, enviroment * env) {
	il_factor_static_field_access_find(self, env);
	return self->f->type;
}

void il_factor_static_field_access_load(il_factor_static_field_access * self, enviroment * env, il_ehandler * eh) {
	il_factor_static_field_access_find(self, env);
}

void il_factor_static_field_access_delete(il_factor_static_field_access * self) {
	fqcn_cache_delete(self->fqcn);
	//il_factor_delete(self->f);
	MEM_FREE(self->name);
	MEM_FREE(self);
}

//private
static void il_factor_static_field_access_find(il_factor_static_field_access * self, enviroment * env) {
	int temp = 0;
	class_* cls = fqcn_class(self->fqcn, (namespace_*)vector_top(env->namespace_vec));
	//フィールドはクラスにしか定義出来ないので、
	//クラスが見つからなかったらエラー
	assert(cls != NULL);
	self->f = class_find_sfield_tree(cls, self->name, &temp);
	self->fieldIndex = temp;
}