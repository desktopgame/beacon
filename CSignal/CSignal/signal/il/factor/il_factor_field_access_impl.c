#include "il_factor_field_access_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../util/logger.h"
#include "../../env/type_interface.h"
#include "../../env/type_impl.h"
#include "../../env/namespace.h"
#include "../../env/field.h"
#include "il_factor_variable_impl.h"
#include <stdio.h>
#include <assert.h>

//proto
static void il_factor_field_access_find(il_factor_field_access * self, enviroment * env);

il_factor * il_factor_wrap_field_access(il_factor_field_access * self) {
	il_factor* ret = (il_factor*)MEM_MALLOC(sizeof(il_factor));
	ret->type = ilfactor_field_access;
	ret->u.field_access_ = self;
	return ret;
}

il_factor_field_access * il_factor_field_access_new(const char * name) {
	il_factor_field_access* ret = (il_factor_field_access*)MEM_MALLOC(sizeof(il_factor_field_access));
	ret->name = text_strdup(name);
	ret->fact = NULL;
	ret->f = NULL;
	ret->fieldIndex = -1;
	return ret;
}

void il_factor_field_access_dump(il_factor_field_access * self, int depth) {
	text_putindent(depth);
	text_printf("field access %s", self->name);
	text_putline();
	il_factor_dump(self->fact, depth + 1);
}

void il_factor_field_access_generate(il_factor_field_access * self, enviroment * env) {
	il_factor_field_access_find(self, env);
	
	if (modifier_is_static(self->f->modifier)) {
		opcode_buf_add(env->buf, op_get_static);
		opcode_buf_add(env->buf, self->f->parent->absoluteIndex);
		opcode_buf_add(env->buf, self->fieldIndex);
	} else {
		il_factor_generate(self->fact, env);

		opcode_buf_add(env->buf, op_get_field);
		opcode_buf_add(env->buf, self->fieldIndex);
	}
}

void il_factor_field_access_load(il_factor_field_access * self, enviroment * env, il_ehandler * eh) {
}

type * il_factor_field_access_eval(il_factor_field_access * self, enviroment * env) {
	il_factor_field_access_find(self, env);
	return self->f->type;
}

void il_factor_field_access_delete(il_factor_field_access * self) {
	il_factor_delete(self->fact);
	MEM_FREE(self->name);
	MEM_FREE(self);
}

//private
static void il_factor_field_access_find(il_factor_field_access * self, enviroment * env) {
	//*
	int temp = 0;
	//TEST(env->toplevel);
	//ここでもしfactがvariableなら、
	//対応するクラス名があるか調べる
	//あったならfactは開放して、f/fieldIndexも再検索
	if (self->fact->type == ilfactor_variable) {
		il_factor_variable* var = self->fact->u.variable_;
		namespace_* top = (namespace_*)vector_top(env->namespace_vec);
		class_* cls = NULL;
		if (top != NULL) {
			cls = namespace_get_class(top, var->name);
		}
		if (cls == NULL) {
			cls = namespace_get_class(namespace_lang(), var->name);
		}
		//クラスが見つかった
		if (cls != NULL) {
			//静的フィールド
			self->f = class_find_sfield_tree(cls, self->name, &temp);
			self->fieldIndex = temp;
		} else {
			//クラスではなかったので変数として扱う
			self->f = class_find_field_tree(cls, self->name, &temp);
			TEST(self->f == NULL);
			self->fieldIndex = temp;
		}
	//variableではない(戻り値や式の結果)
	//
	} else {
		type* tp = il_factor_eval(self->fact, env);
		assert(tp->tag == type_class);
		self->f = class_find_field_tree(tp->u.class_, self->name, &temp);
		TEST(self->f == NULL);
		self->fieldIndex = temp;
	}
	//*/
	//TEST(env->toplevel);
//	class_find_fie
}