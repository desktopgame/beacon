#include "il_factor_variable_local_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../env/generic_type.h"
#include "../../../env/type_impl.h"
#include "../../../env/field.h"
#include "../../../env/property.h"
#include "../../../vm/enviroment.h"
#include "../../../vm/symbol_entry.h"
#include "../../il_argument.h"
#include <string.h>
#include <stdio.h>

static void il_factor_variable_local_loadImpl(il_factor_variable_local * self, enviroment * env, call_context* cctx);
static void il_factor_variable_local_load_field(il_factor_variable_local * self, enviroment * env, call_context* cctx);
static void il_factor_variable_local_load_property(il_factor_variable_local * self, enviroment * env, call_context* cctx);
static void set_gtype(il_factor_variable_local * self, generic_type* gt);
static void il_factor_generate_field(il_factor_variable_local* self, enviroment* env, call_context* cctx);
static void il_factor_generate_property(il_factor_variable_local* self, enviroment* env, call_context* cctx);

il_factor_variable_local* il_factor_variable_local_new(string_view namev) {
	il_factor_variable_local* ret = (il_factor_variable_local*)MEM_MALLOC(sizeof(il_factor_variable_local));
	ret->namev = namev;
	ret->type = variable_local_undefined;
	ret->type_args = NULL;
	ret->gt = NULL;
	return ret;
}

void il_factor_variable_local_generate(il_factor_variable_local* self, enviroment* env, call_context* cctx) {
	il_factor_variable_local_load(self, env, cctx);
	assert(self->type != variable_local_undefined);
	if(self->type == variable_local_scope) {
		opcode_buf_add(env->buf, (vector_item)op_load);
		opcode_buf_add(env->buf, (vector_item)self->u.entry_->index);
	} else if(self->type == variable_local_field) {
		opcode_buf_add(env->buf, (vector_item)op_this);
		opcode_buf_add(env->buf, (vector_item)op_get_field);
		opcode_buf_add(env->buf, (vector_item)self->u.field_index);
	} else if(self->type == variable_local_property) {
		property* p = self->u.p_with_i.p;
		//FIXME:コピペ
		if(p->is_short) {
			il_factor_generate_field(self, env, cctx);
		} else {
			il_factor_generate_property(self, env, cctx);
		}
	}
}

void il_factor_variable_local_load(il_factor_variable_local * self, enviroment * env, call_context* cctx) {
	if(self->type != variable_local_undefined) {
		return;
	}
	il_factor_variable_local_loadImpl(self, env, cctx);
}

generic_type* il_factor_variable_local_eval(il_factor_variable_local * self, enviroment * env, call_context* cctx) {
	il_factor_variable_local_load(self, env, cctx);
	assert(self->type != variable_local_undefined);
	return self->gt;
}

char* il_factor_variable_local_tostr(il_factor_variable_local * self, enviroment * env) {
	return text_strdup(string_pool_ref2str(self->namev));
}

void il_factor_variable_local_delete(il_factor_variable_local* self) {
	vector_delete(self->type_args, vector_deleter_null);
//	generic_type_delete(self->gt);
	MEM_FREE(self);
}
//private
static void il_factor_variable_local_loadImpl(il_factor_variable_local * self, enviroment * env, call_context* cctx) {
	//NOTE:変数宣言の後にその変数を使用する場合、
	//factorはload時点でシンボルエントリーを取得しようとするが、
	//stmtはgenerate時点でシンボルテーブルへ書き込むので、
	//NULLになることがある。
	self->type = variable_local_scope;
	symbol_entry* ent = symbol_table_entry(env->sym_table, NULL, self->namev);
	//ローカル変数として解決出来なかったので、
	//フィールドとして解決する
	if(ent == NULL) {
		il_factor_variable_local_load_field(self, env, cctx);
	} else {
		self->u.entry_ = ent;
		self->gt = ent->gtype;
	}
}

static void il_factor_variable_local_load_field(il_factor_variable_local * self, enviroment * env, call_context* cctx) {
	//対応するフィールドを検索
	self->type = variable_local_field;
	//NOTE:トップレベルではここが空なので、
	//定義されていない変数とみなせる？
	type* tp = call_context_type(cctx);
	if(tp->tag == type_interface/* この条件は構文規則からして満たさないはず */) {
		bc_error_throw(bcerror_undefined_variable, string_pool_ref2str(self->namev));
		return;
	}
	int temp = -1;
	field* f = class_find_field_tree(TYPE2CLASS(tp), self->namev, &temp);
	self->u.field_index = temp;
	self->type = variable_local_field;
	if(temp == -1) {
		il_factor_variable_local_load_property(self, env, cctx);
		return;
	//フィールドが見つかったなら可視性を確認する
	} else if(!class_accessible_field(call_context_class(cctx), f)) {
		bc_error_throw(bcerror_can_t_access_field, string_pool_ref2str(call_context_class(cctx)->namev), string_pool_ref2str(f->namev));
		return;
	}
	set_gtype(self, f->gtype);
}

static void il_factor_variable_local_load_property(il_factor_variable_local * self, enviroment * env, call_context* cctx) {
	int temp = -1;
	type* tp = call_context_type(cctx);
	property* p = class_find_property_tree(TYPE2CLASS(tp), self->namev, &temp);
	if(temp == -1) {
		bc_error_throw(bcerror_can_t_access_property, string_pool_ref2str(type_name(tp)), string_pool_ref2str(self->namev));
		return;
	}
	property_with_index pwi = {};
	pwi.p = p;
	pwi.index = temp;
	self->type = variable_local_property;
	self->u.p_with_i = pwi;
	//プロパティにアクセスできない
	if(!class_accessible_property(TYPE2CLASS(tp), p)) {
		bc_error_throw(bcerror_can_t_access_property, string_pool_ref2str(type_name(tp)), string_pool_ref2str(p->namev));
	}
	set_gtype(self, p->gtype);
}

static void set_gtype(il_factor_variable_local * self, generic_type* gt) {
	//generic_type* gt = f->gtype;
	//virtual_type vt = f->vtype;
	if(gt->tag == generic_type_tag_none) {
		self->gt = gt;
	} else if(gt->tag == generic_type_tag_class) {
		self->gt = generic_type_new(NULL);
		self->gt->tag = generic_type_tag_class;
		self->gt->virtual_type_index = gt->virtual_type_index;
	} else if(gt->tag == generic_type_tag_method) {
		self->gt = generic_type_new(NULL);
		self->gt->tag = generic_type_tag_method;
		self->gt->virtual_type_index = gt->virtual_type_index;
	}
}
//private
static void il_factor_generate_field(il_factor_variable_local* self, enviroment* env, call_context* cctx) {
	assert(self->type == variable_local_property);
	property* p = self->u.p_with_i.p;
	field* f = p->source_ref;
	if(modifier_is_static(f->modifier)) {
		opcode_buf_add(env->buf, op_get_static);
		opcode_buf_add(env->buf, f->parent->absolute_index);
		opcode_buf_add(env->buf, class_get_field_by_property(TYPE2CLASS(p->parent), p));
	} else {
		opcode_buf_add(env->buf, op_this);
		opcode_buf_add(env->buf, op_get_field);
		opcode_buf_add(env->buf, class_get_field_by_property(TYPE2CLASS(p->parent), p));
	}
}

static void il_factor_generate_property(il_factor_variable_local* self, enviroment* env, call_context* cctx) {
	assert(self->type == variable_local_property);
	property* p = self->u.p_with_i.p;
	int i = self->u.p_with_i.index;
	if(modifier_is_static(p->modifier)) {
		opcode_buf_add(env->buf, op_get_static_property);
		opcode_buf_add(env->buf, p->parent->absolute_index);
		opcode_buf_add(env->buf, i);
	} else {
		opcode_buf_add(env->buf, op_this);
		opcode_buf_add(env->buf, op_get_property);
		opcode_buf_add(env->buf, i);
	}
}