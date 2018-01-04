#include "il_factor_field_access_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/class.h"
#include "../../env/field.h"
#include <stdio.h>


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
	printf("field access %s", self->name);
	text_putline();
	il_factor_dump(self->fact, depth + 1);
}

void il_factor_field_access_generate(il_factor_field_access * self, enviroment * env) {
	il_factor_field_access_find(self, env);
	il_factor_generate(self->fact, env);
	opcode_buf_add(env->buf, op_get_field);
	opcode_buf_add(env->buf, self->fieldIndex);
}

class_ * il_factor_field_access_eval(il_factor_field_access * self, enviroment * env) {
	il_factor_field_access_find(self, env);
	return self->f->type;
}

void il_factor_field_access_delete(il_factor_field_access * self) {
}

//private
static void il_factor_field_access_find(il_factor_field_access * self, enviroment * env) {
	class_* cls = il_factor_eval(self->fact, env);
	int temp = 0;
	//ここでもしfactがvariableなら、
	//対応するクラス名があるか調べる
	//あったならfactは開放して、f/fieldIndexも再検索
	self->f = class_find_field(cls, self->name, &temp);
	self->fieldIndex = temp;
//	class_find_fie
}