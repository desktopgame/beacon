#include "il_factor_inc_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/type_interface.h"

il_factor * il_factor_wrap_inc(il_factor_inc * self) {
	il_factor* ret = (il_factor*)MEM_MALLOC(sizeof(il_factor));
	ret->type = ilfactor_inc;
	ret->u.inc_ = self;
	return ret;
}

il_factor_inc * il_factor_inc_new(fix_type type) {
	il_factor_inc* ret = (il_factor_inc*)MEM_MALLOC(sizeof(il_factor_inc));
	ret->type = type;
	ret->fact = NULL;
	return ret;
}

void il_factor_inc_dump(il_factor_inc * self, int depth) {
	text_putindent(depth);
	text_printf("++");
	text_putline();
	il_factor_dump(self->fact, depth + 1);
}

void il_factor_inc_generate(il_factor_inc * self, enviroment * env, il_load_cache* cache) {
	if (self->type == fixtype_pre) {
		il_factor_generate(self->fact, env, cache);
		opcode_buf_add(env->buf, op_inc);

	} else if (self->type == fixtype_post) {
		//FIXME:コピペ
		//
		il_factor_generate(self->fact, env, cache);
		//複製
		opcode_buf_add(env->buf, op_copy);
		//オリジナルをインクリメント
		opcode_buf_add(env->buf, op_swap);
		opcode_buf_add(env->buf, op_inc);
		//が、返すのはとりあえず複製
		//ここでオリジナルがスタックから消える
		opcode_buf_add(env->buf, op_pop);
	}
}

void il_factor_inc_load(il_factor_inc * self, enviroment * env, il_load_cache* cache, il_ehandler * eh) {
	il_factor_load(self->fact, env, cache, eh);
}

generic_type* il_factor_inc_eval(il_factor_inc * self, enviroment * env, il_load_cache* cache) {
	return il_factor_eval(self->fact, env, cache);
}

void il_factor_inc_delete(il_factor_inc * self) {
	il_factor_delete(self->fact);
	MEM_FREE(self);
}

il_factor_inc* il_factor_cast_inc(il_factor* fact) {
	assert(fact->type == ilfactor_inc);
	return fact->u.inc_;
}